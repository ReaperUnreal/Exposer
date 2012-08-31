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

   float r;
   float g;
   float b;
};
#endif
