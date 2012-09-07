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
}
