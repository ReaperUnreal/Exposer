Exposer
=======

Various fun algorithms and functions to try and compress a floating point image to an 8-bit per channel BMP.

The file format for the incoming raw image is simply as follows:

    int width
    int height
    (float r g b) * (width * height)


The available algorithms are as follows:

1.   Simple Clamp
2.   Saturate
3.   Compress
4.   Gamma Correction
5.   HSL Gamma Correction
6.   Constant Sigmoid Compression
7.   Constant Sigmoid Lightness Compression
8.   Constant Sigmoid Average Lightness Compression
9.   Constant Sigmoid Interpolated Lightness Compression
10.  Logarithmic Compression
11.  Night Filter
