#include "main.h"

//class ConstSigmoidFilter : public Filter
ConstSigmoidFilter::ConstSigmoidFilter(float ssc, float exp) : semiSatConst(ssc), n(exp)
{
}

void ConstSigmoidFilter::filter(Image &im)
{
	printf("Semi-Saturation Constant = %0.3f\n", semiSatConst);
   printf("Exponent = %0.3f\n", n);
   f = powf(semiSatConst, n);
	apply(im);
}

void ConstSigmoidFilter::filterfunc(float *r, float *g, float *b)
{
   *r = *r / (*r + f);
   *g = *g / (*g + f);
   *b = *b / (*b + f);
}

//class ConstSigmoidLFilter : public Filter
ConstSigmoidLFilter::ConstSigmoidLFilter(float ssc, float exp) : semiSatConst(ssc), n(exp)
{
}

void ConstSigmoidLFilter::filter(Image &im)
{
	printf("Semi-Saturation Constant = %0.3f\n", semiSatConst);
   printf("Exponent = %0.3f\n", n);
   f = powf(semiSatConst, n);
	applyColor(im);
}

void ConstSigmoidLFilter::filterfunc(Color &c)
{
   Color yuv = c.RGBtoYUV();
   yuv.y = yuv.y / (yuv.y + f);
   c = yuv.YUVtoRGB();
}

//class ConstSigmoidAverageFilter : public Filter
ConstSigmoidAverageFilter::ConstSigmoidAverageFilter(float kval, float exp) : n(exp), Lv(0.0f), k(kval), f(0.0f)
{
}

void ConstSigmoidAverageFilter::filter(Image &im)
{
   //calculate Lv first
   int num = im.getWidth() * im.getHeight();
   float *data = im.getData();
   float sum = 0.0f;
   for(int i = 0; i < num; i++, data += 3)
   {
      //the following formula from util.h
      float L = 0.299f * *data + 0.587f * *(data + 1) + 0.114 * *(data + 2);
      float val = logf(EPSILON + L);
      sum += val;
   }
   sum /= static_cast<float>(num);
   Lv = expf(sum);

   f = powf(Lv / k, n);

   printf("Lvbar = %0.3f\n", Lv);
   printf("Exponent = %0.3f\n", n);
   printf("k = %0.3f\n", k);
   printf("f = %0.3f\n", f);

   applyColor(im);
}

void ConstSigmoidAverageFilter::filterfunc(Color &c)
{
   Color yuv = c.RGBtoYUV();
   yuv.y = yuv.y / (yuv.y + f);
   c = yuv.YUVtoRGB();
}

//class ConstSigmoidInterpolatedFilter : public Filter
ConstSigmoidInterpolatedFilter::ConstSigmoidInterpolatedFilter(float contrast) : a(contrast), Lv(0.0f), n(1.0f)
{
}

void ConstSigmoidInterpolatedFilter::filter(Image &im)
{
   //calculate Lv first
   int num = im.getWidth() * im.getHeight();
   float *data = im.getData();
   float sum = 0.0f;
   float Lmax = 0.299f * *data + 0.587f * *(data + 1) + 0.114 * *(data + 2);
   float Lmin = Lmax;
   for(int i = 0; i < num; i++, data += 3)
   {
      //the following formula from util.h
      float L = 0.299f * *data + 0.587f * *(data + 1) + 0.114 * *(data + 2);

      if(L > Lmax) Lmax = L;
      if(L < Lmin) Lmin = L;

      float val = logf(EPSILON + L);
      sum += val;
   }
   sum /= static_cast<float>(num);
   Lv = expf(sum);

   //compute the exponent
   n = 0.3f + 0.7f * powf((Lmax - Lv) / (Lmax - Lmin), 1.4f);

   printf("Lvbar = %0.3f\n", Lv);
   printf("Lmax = %0.3f\n", Lmax);
   printf("Lmin = %0.3f\n", Lmin);
   printf("a = %0.3f\n", a);
   printf("Exponent = %0.3f\n", n);

   applyColor(im);
}

void ConstSigmoidInterpolatedFilter::filterfunc(Color &c)
{
   Color yuv = c.RGBtoYUV();

   float f = a * yuv.y + (1.0f - a) * Lv;

   yuv.y = yuv.y / (yuv.y + f);
   c = yuv.YUVtoRGB();
}
