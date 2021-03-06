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
   ifstream file(filename, ifstream::binary);

   //pre checked this but who knows how the workflow will change in the future
   if(!file.good())
   {
      fprintf(stderr, "Problem reading %s\n", filename);
      return;
   }

   //load width and height first
   file.read(reinterpret_cast<char *>(&width), 4);
   file.read(reinterpret_cast<char *>(&height), 4);
   printf("Width: %d, Height: %d\n", width, height);

   //create the data
   int num = width * height * 3;
   data = new float[num];

   //load up RGB
   file.read(reinterpret_cast<char *>(data), 4 * num);

   file.close();
}

void Image::ToBMP(const char *filename) const
{
   //thank you EasyBMP
   BMP out;
   out.SetSize(width, height);
   out.SetBitDepth(24);

   float *iter = data;
   for(int j = 0; j < height; j++)
   {
      for(int i = 0; i < width; i++, iter += 3)
      {
         Color c(iter);
         c.ClampNormal();
         out.SetPixel(i, j, c.ToRGBAPixel());
      }
   }

   out.WriteToFile(filename);
}

int Image::getWidth()
{
	return width;
}

int Image::getHeight()
{
	return height;
}

float *Image::getData()
{
	return data;
}
