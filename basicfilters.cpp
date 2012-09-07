#include "main.h"

//class SaturateFilter : public Filter
void SaturateFilter::filter(Image &im)
{
	//calculate the scale and offset
	float *data = im.getData();
	int height = im.getHeight();
	int width = im.getWidth();

	float max = *data;
	float min = *data;
	++data;

	int num = width * height * 3;
	for(int i = 1; i < num; i++, data++)
	{
		if(*data < min) min = *data;
		if(*data > max) max = *data;
	}

	offset = -min;
	scale = 1.0f / (max - min);

	printf("min = %0.3f, max = %0.3f, scale = %0.3f, offset = %0.3f\n", min, max, scale, offset);

	//apply the filterfunc, this would be easier in haskell
	apply(im);
}

void SaturateFilter::filterfunc(float *r, float *g, float *b)
{
	*r = (*r + offset) * scale;
	*g = (*g + offset) * scale;
	*b = (*b + offset) * scale;
}

//class CompressFilter : public SaturateFilter
void CompressFilter::filter(Image &im)
{
	//calculate the scale and offset
	float *data = im.getData();
	int height = im.getHeight();
	int width = im.getWidth();

	float max = *data;
	float min = *data;
	++data;

	int num = width * height * 3;
	for(int i = 1; i < num; i++, data++)
	{
		if(*data < min) min = *data;
		if(*data > max) max = *data;
	}

	offset = -min;
	scale = 1.0f / (max - min);

	printf("min = %0.3f, max = %0.3f, scale = %0.3f, offset = %0.3f\n", min, max, scale, offset);

	//only apply the filterfunc if we have too much data
	if(max > 1.0f)
		apply(im);
}

//class GammaFilter : public Filter
GammaFilter::GammaFilter(float g) : gamma(g)
{
	if(gamma <= 0.0f)
		gamma = 1.0f;
}

void GammaFilter::filter(Image &im)
{
	printf("gamma = %0.3f\n", gamma);
	apply(im);
}

void GammaFilter::filterfunc(float *r, float *g, float *b)
{
	*r = powf(*r, gamma);
	*g = powf(*g, gamma);
	*b = powf(*b, gamma);
}

//class GammaLFilter : public Filter
GammaLFilter::GammaLFilter(float g) : gamma(g)
{
	if(gamma <= 0.0f)
		gamma = 1.0f;
}

void GammaLFilter::filter(Image &im)
{
	printf("gamma = %0.3f\n", gamma);
	applyColor(im);
}

void GammaLFilter::filterfunc(Color &c)
{
   Color yuv = c.RGBtoYUV();
   yuv.y = powf(yuv.y, gamma);
   c = yuv.YUVtoRGB();
}
