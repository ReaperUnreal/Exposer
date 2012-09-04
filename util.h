#ifndef UTIL_H
#define UTIL_H
#include "main.h"

class Color
{
public:
   Color(float _r = 0.0f, float _g = 0.0f, float _b = 0.0f) : r(_r), g(_g), b(_b)
   {
   }

   Color(float *array)
   {
      r = array[0];
      g = array[1];
      b = array[2];
   }

   void ClampNormal()
   {
      if(r > 1.0f)
         r = 1.0f;
      if(r < 0.0f)
         r = 0.0f;
      if(g > 1.0f)
         g = 1.0f;
      if(g < 0.0f)
         g = 0.0f;
      if(b > 1.0f)
         b = 1.0f;
      if(b < 0.0f)
         b = 0.0f;
   }

   RGBApixel ToRGBAPixel()
   {
      int red = lrintf(r * 255.0f);
      int green = lrintf(g * 255.0f);
      int blue = lrintf(b * 255.0f);
      RGBApixel p;
      p.Red = red;
      p.Green = green;
      p.Blue = blue;
      p.Alpha = 255;
      return p;
   }

   Color RGBtoHSL()
   {
      //formula taken from http://en.wikipedia.org/wiki/HSL_and_HSV
      float M = fmax(fmax(r, g), b);
      float m = fmin(fmin(r, g), b);
      float C = M - m;

      float L = (M + m) * 0.5f;

      float hprime, S;
      if(C == 0.0f)
      {
         //achromatic
         hprime = 0.0f;
         S = 0.0f;
      }
      else
      {
         if(M == r)
         {
            hprime = (g - b) / C;
            hprime = fmod(hprime, 6.0f);
         }
         else if(M == g)
         {
            hprime = ((b - r) / C) + 2.0f;
         }
         else //M == b
         {
            hprime = ((r - g) / C) + 4.0f;
         }

         S = C / (1.0f - fabsf((2.0f * L) - 1.0f));
      }
      float H = hprime / 6.0f;

      return Color(H, S, L);
   }

   Color RGBtoHSV()
   {
      //formula taken from http://en.wikipedia.org/wiki/HSL_and_HSV
      float M = fmax(fmax(r, g), b);
      float m = fmin(fmin(r, g), b);
      float C = M - m;

      float V = M;

      float hprime, S;
      if(C == 0.0f)
      {
         //achromatic
         hprime = 0.0f;
         S = 0.0f;
      }
      else
      {
         if(M == r)
         {
            hprime = (g - b) / C;
            hprime = fmod(hprime, 6.0f);
         }
         else if(M == g)
         {
            hprime = ((b - r) / C) + 2.0f;
         }
         else //M == b
         {
            hprime = ((r - g) / C) + 4.0f;
         }

         S = C / V;
      }
      float H = hprime / 6.0f;

      return Color(H, S, V);
   }

   Color HSLtoRGB()
   {
      //formula taken from http://en.wikipedia.org/wiki/HSL_and_HSV
      float C = (1.0f - fabsf((2.0f * l) - 1.0f)) * s;
      float hprime = h * 6.0f;
      float X = C * (1.0f - fabsf(fmod(hprime, 2.0f) - 1.0f));

      float r1 = 0.0f, g1 = 0.0f, b1 = 0.0f;
      if(hprime >= 0.0f)
      {
         if(hprime < 1.0f)
         {
            r1 = C;
            g1 = X;
         }
         else if(hprime < 2.0f)
         {
            r1 = X;
            g1 = C;
         }
         else if(hprime < 3.0f)
         {
            g1 = C;
            b1 = X;
         }
         else if(hprime < 4.0f)
         {
            g1 = X;
            b1 = C;
         }
         else if(hprime < 5.0f)
         {
            r1 = X;
            b1 = C;
         }
         else if(hprime < 6.0f)
         {
            r1 = C;
            b1 = X;
         }
      }

      float m = l - (0.5f * C);

      return Color(r1 + m, g1 + m, b1 + m);
   }

   Color HSVtoRGB()
   {
      //formula taken from http://en.wikipedia.org/wiki/HSL_and_HSV
      float C = v * s;
      float hprime = h * 6.0f;
      float X = C * (1.0f - fabsf(fmod(hprime, 2.0f) - 1.0f));

      float r1 = 0.0f, g1 = 0.0f, b1 = 0.0f;
      if(hprime >= 0.0f)
      {
         if(hprime < 1.0f)
         {
            r1 = C;
            g1 = X;
         }
         else if(hprime < 2.0f)
         {
            r1 = X;
            g1 = C;
         }
         else if(hprime < 3.0f)
         {
            g1 = C;
            b1 = X;
         }
         else if(hprime < 4.0f)
         {
            g1 = X;
            b1 = C;
         }
         else if(hprime < 5.0f)
         {
            r1 = X;
            b1 = C;
         }
         else if(hprime < 6.0f)
         {
            r1 = C;
            b1 = X;
         }
      }

      float m = v - C;

      return Color(r1 + m, g1 + m, b1 + m);
   }

   union
   {
      float r;
      float h;
   };
   union
   {
      float g;
      float s;
   };
   union
   {
      float b;
      float l;
      float v;
   };
};
#endif
