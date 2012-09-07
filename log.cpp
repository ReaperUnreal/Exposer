#include "main.h"

//class LogFilter : public Filter
LogFilter::LogFilter(float parm) : p(parm), mult1(3.3f /* 1 / log10(1 + 1) */), exponent(0.23f /* log10(0.85) / log10(0.5) */), Lmax(0.5f)
{
}

void LogFilter::filter(Image &im)
{
   //calculate Lmax first
   int num = im.getWidth() * im.getHeight();
   float *data = im.getData();
   Lmax = 0.299f * *data + 0.587f * *(data + 1) + 0.114 * *(data + 2);
   for(int i = 0; i < num; i++, data += 3)
   {
      //the following formula from util.h
      float L = 0.299f * *data + 0.587f * *(data + 1) + 0.114 * *(data + 2);
      if(L > Lmax) Lmax = L;
   }

   //calculate all the constants I can
   mult1 = 1.0f / log10f(1.0f + Lmax);
   exponent = log10f(p) / log10f(0.5f);

   printf("Lmax = %0.3f\n", Lmax);
   printf("mult1 = %0.3f\n", mult1);
   printf("exponent = %0.3f\n", exponent);

   applyColor(im);
}

void LogFilter::filterfunc(Color &c)
{
   Color yuv = c.RGBtoYUV();

   float first = log10f(1.0f + yuv.y) * mult1;
   float second = log10f(2.0f + 8.0f * powf(yuv.y / Lmax, exponent));

   float ld = first / second; //actually written as first * 1/second
   yuv.y = ld;

   c = yuv.YUVtoRGB();
}
