#ifndef IMAGE_H
#define IMAGE_H

class Image
{
public:
   Image();
   virtual ~Image();

   void FromRawFile(const char *filename);
   void ToBMP(const char *filename) const;

   int getWidth();
   int getHeight();
   float *getData();
protected:
   int width;
   int height;
   float *data;
};

#endif
