#include "main.h"

//class NightFilter : public Filter
NightFilter::NightFilter()
{
}

void NightFilter::filter(Image &im)
{
   //nothing to do here really, it's all in there
   applyColor(im);
}

void NightFilter::filterfunc(Color &c)
{
   Color xyz = c.RGBtoXYZ();

   //calculate scotopic luminance
   float X = xyz.r;
   float Y = xyz.g;
   float Z = xyz.b;

   float V = Y * (1.33f * (1.0f + (Y + Z) / X) - 1.68f);

   //multiply by a nice blue-grey (chosen empirically: 44, 44, 99)
   c.r = 0.1725f * V;
   c.g = 0.1725f * V;
   c.b = 0.3888f * V;
}
