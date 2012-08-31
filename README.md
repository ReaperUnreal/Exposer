Exposer
=======

Various fun algorithms and functions to try and compress a floating point image to an 8-bit per channel BMP.

The file format for the incoming raw image is simply as follows:
int width
int height
(float r g b) * (width * height)
