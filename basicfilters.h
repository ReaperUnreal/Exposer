#ifndef BASICFILTERS_H
#define BASICFILTERS_H

#include "main.h"

class SaturateFilter : public Filter
{
public:
	virtual void filter(Image &im);

protected:
	virtual void filterfunc(float *r, float *g, float *b);

	float scale;
	float offset;
};

class CompressFilter : public SaturateFilter
{
public:
	virtual void filter(Image &im);
};

class GammaFilter : public Filter
{
public:
	GammaFilter(float g);

	virtual void filter(Image &im);

protected:
	virtual void filterfunc(float *r, float *g, float *b);

	float gamma;
};

#endif
