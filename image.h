#ifndef IMAGE_H
#define IMAGE_H

class Image
{
public:
   Image();
   virtual ~Image();

   void FromRawFile(const char *filename);
   void ToBMP(const char *filename) const;
protected:
   int width;
   int height;
   float *data;
};

#endif
