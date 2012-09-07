#ifndef LOG_H
#define LOG_H

#include "main.h"

class LogFilter : public Filter
{
public:
   LogFilter(float parm = 0.85f);
	virtual void filter(Image &im);

protected:
	virtual void filterfunc(Color &c);

   float p;
   float mult1;
   float exponent;
   float Lmax;
};

#endif
