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
		//virtual void filterfunc(float *r, float *g, float *b);
		filterfunc(data, data + 1, data + 2);
	}
}

void Filter::applyRGB(Image &im)
{
	int num = im.getWidth() * im.getHeight();
	float *data = im.getData();

	for(int i = 0; i < num; i++, data += 3)
	{
		//virtual void filterfunc(Color &c);
      Color c(data[0], data[1], data[2]);
		filterfunc(c);
      data[0] = c.r;
      data[1] = c.g;
      data[2] = c.b;
	}
}

void Filter::filterfunc(float *r, float *g, float *b)
{
}

void Filter::filterfunc(Color &c)
{
}

