#ifndef FILTER_H
#define FILTER_H

#include "main.h"

class Filter
{
public:
	Filter();
	virtual ~Filter();

	virtual void filter(Image &im);
protected:
	virtual void apply(Image &im);
	virtual void applyColor(Image &im);
	virtual void filterfunc(float *r, float *g, float *b);
   virtual void filterfunc(Color &c);
};

#endif
