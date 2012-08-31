#include "main.h"

Image::Image(): width(0), height(0), data(NULL)
{
}

Image::~Image()
{
   if(data)
   {
      delete[] data;
      data = NULL;
   }
}

void Image::FromRawFile(const char *filename)
{
}

void Image::ToBMP(const char *filename) const
{
}
