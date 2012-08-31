#ifndef UTIL_H
#define UTIL_H
#include "main.h"

class Color
{
public:
   Color(float _r = 0.0f, float _g = 0.0f, float _b = 0.0f) : r(_r), g(_g), b(_b)
   {
   }

   float r;
   float g;
   float b;
};
#endif
