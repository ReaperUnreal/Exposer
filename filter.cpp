#include "main.h"

Filter::Filter()
{
}

Filter::~Filter()
{
}

void Filter::filter(Image &im)
{
	apply(im);
}

void Filter::apply(Image &im)
{
	int num = im.getWidth() * im.getHeight();
	float *data = im.getData();

	for(int i = 0; i < num; i++, data += 3)
	{
		//virtual void filterfunc(float *r, float *g, float *b) = 0;
		filterfunc(data, data + 1, data + 2);
	}
}
