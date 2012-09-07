#include "main.h"

void printUsage()
{
   printf("Usage: exposer <filename> <exposure algorithm number>\n\n");
   printf("Exposure algorithms:\n");
   printf("0:\tSimple Clamp\n");
   printf("1:\tSaturate\n");
   printf("2:\tCompress\n");
   printf("3:\tGamma Correction\n");
   printf("4:\tHSL Gamma Correction\n");
   printf("5:\tConstant Sigmoid Compression\n");
   printf("6:\tConstant Sigmoid Lightness Compression\n");
   printf("7:\tConstant Sigmoid Average Lightness Compression\n");
   printf("8:\tConstant Sigmoid Interpolated Lightness Compression\n");
   printf("\n");
}

void renameForOutput(char *filename)
{
   int len = strlen(filename);
   filename[len - 3] = 'b';
   filename[len - 2] = 'm';
   filename[len - 1] = 'p';
}

void process(const char *infilename, const char *outfilename, int algorithm)
{
   //read, process, output
   Image im;
   im.FromRawFile(infilename);
   switch(algorithm)
   {
	   case 1:
		   {
			   SaturateFilter f;
			   f.filter(im);
			   break;
		   }
	   case 2:
		   {
			   CompressFilter f;
			   f.filter(im);
			   break;
		   }
	   case 3:
		   {
			   GammaFilter f(1.0f / 2.2f);
			   f.filter(im);
			   break;
		   }
	   case 4:
		   {
			   GammaLFilter f(1.0f / 2.2f);
			   f.filter(im);
			   break;
		   }
	   case 5:
		   {
			   ConstSigmoidFilter f(1.0f);
			   f.filter(im);
			   break;
		   }
	   case 6:
		   {
			   ConstSigmoidLFilter f(1.0f);
			   f.filter(im);
			   break;
		   }
	   case 7:
		   {
			   ConstSigmoidAverageFilter f(0.05f);
			   f.filter(im);
			   break;
		   }
	   case 8:
		   {
			   ConstSigmoidInterpolatedFilter f(0.2f);
			   f.filter(im);
			   break;
		   }
	   default: break; //auto clamp at the end, so 0 is do nothing by default
   }
   im.ToBMP(outfilename);
}

int main(int argc, char **argv)
{
   //check for enough arguments
   if(argc != 3)
   {
      if(argc < 3)
         printf("Not enough arguments.\n");
      else
         printf("Too many arguments.\n");
      printf("\n");
      printUsage();
      return -1;
   }

   //get the input file name
   char infilename[256];
   strncpy(infilename, argv[1], 256);
   infilename[255] = '\0';
   //printf("Input File: %s\n", infilename);

   //verify that the input file exists
   //side effect: file is now open and ready to read
   ifstream infile(infilename, ifstream::binary);
   if(!infile.good())
   {
      printf("File %s cannot be read.\n\n", infilename);
      printUsage();
      return -3;
   }
   infile.close();

   //get the algorithm number
   char number[32];
   strncpy(number, argv[2], 32);
   number[31] = '\0';
   int algoNum = atoi(number);
   //printf("Algorithm Number: %d\n", algoNum);

   //verify that the algorithm number exists
   if((algoNum < 0) || (algoNum >= NUM_ALGORITHMS))
   {
      printf("%d is not a valid algorithm number.\n\n", algoNum);
      printUsage();
      return -2;
   }

   //compute the output file name
   char outfilename[256];
   memcpy(outfilename, infilename, 256);
   renameForOutput(outfilename);
   //printf("Output File: %s\n", outfilename);

   //process the file
   process(infilename, outfilename, algoNum);

   return 0;
}
