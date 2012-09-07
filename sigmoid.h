#ifndef SIGMOID_H
#define SIGMOID_H

#include "main.h"

class ConstSigmoidFilter : public Filter
{
public:
   ConstSigmoidFilter(float ssc, float exp = 1.0f);
	virtual void filter(Image &im);

protected:
	virtual void filterfunc(float *r, float *g, float *b);

   float semiSatConst;
   float n;
   float f;
};

class ConstSigmoidLFilter : public Filter
{
public:
   ConstSigmoidLFilter(float ssc, float exp = 1.0f);
	virtual void filter(Image &im);

protected:
	virtual void filterfunc(Color &c);

   float semiSatConst;
   float n;
   float f;
};

class ConstSigmoidAverageFilter : public Filter
{
public:
   ConstSigmoidAverageFilter(float kval = 0.18f, float exp = 1.0f);
   virtual void filter(Image &im);

protected:
   virtual void filterfunc(Color &c);

   float n;
   float Lv;
   float k;
   float f;
};

class ConstSigmoidInterpolatedFilter : public Filter
{
public:
   ConstSigmoidInterpolatedFilter(float contrast = 0.5f);
   virtual void filter(Image &im);

protected:
   virtual void filterfunc(Color &c);

   float a;
   float Lv;
   float n;
};

#endif
