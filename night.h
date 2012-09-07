#ifndef NIGHT_H
#define NIGHT_H

#include "main.h"

class NightFilter : public Filter
{
public:
   NightFilter();
	virtual void filter(Image &im);

protected:
	virtual void filterfunc(Color &c);
};

#endif
