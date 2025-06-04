/******
 *
 * Miscellanious functions
 *
 * 07/01/96 Version 1
 *   void Draw_Image (FILE *)
 * 28/01/96 Version 2
 *    void Clear_Image(void)
 *   void Old_Image_2_Image(void)
 *    void Image_2_Old_Image(void)
 * 12/02/96 Version 3
 *   void All()
 * 28/02/96 Version 4
 *    int IsEven(int)
 *    void Invert(void)
 *    void Usage(char *, char *)
 *
 ******/

#ifndef __misc
#define __misc

static char AMIGAmisc[] = "$VER: Misc.c Version 4 ©1996 Simon Westerby" ;
static char UNIXmisc[] = "@(#)RELEASE Misc.c Version 4 (c)1996 Simon Westerby" ;

#include "misc.h"

void Draw_Image (FILE *stream)
/******
 *
 * output the array old_image to a given file 
 * (This may be stdout-the screen. )
 *
 ******/
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT];
   extern int width, height ;
   int x,
       y ;

   for (y = 1; y <= height; y++)
   {
      for (x = 1; x <= width; x++)
      {
         fputc(48+old_image[x][y], stream) ;
      }
      fprintf(stream,"\n") ;
   }
   return ;
}


void Clear_Image(void)
/******
 *
 * Set all the array elements to 0
 *
 ******/
{
   extern int image[MAX_WIDTH][MAX_HEIGHT] ;
   extern int width, height ;
   int i, j;

   for (j = 0; j < MAX_HEIGHT; j++)
   {
      for (i = 1; i < MAX_WIDTH; i++)
      {
         image[i][j] = 0 ;
      }
   }
   return ;
}


void Image_2_Old_Image(void)
/******
 *
 * Copy the contenets of the array image to the 
 * array old_image.
 *
 ******/
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT];
   extern int image[MAX_WIDTH][MAX_HEIGHT];
   extern int width, height ;
   int i, j ;

   for (j = 1; j <= height; j++)
   {
      for (i = 1; i <= width; i++)
      {
         old_image [i][j] = image [i][j] ;
      }
   }
   return ;
}



void Old_Image_2_Image(void)
/******
 *
 * Copy the contents of the array old_image to the
 * array image
 *
 ******/
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT];
   extern int image[MAX_WIDTH][MAX_HEIGHT];
   extern int width, height ;
   int i, j ;

   for (j = 1; j <= height; j++)
   {
      for (i = 1; i <= width; i++)
      {
         image [i][j] = old_image [i][j] ;
      }
   }
   return ;
}


void All(void)
/******
 *
 * Produces output of each (sub-)iteration
 * and sends it to stdout (the screen).
 * 
 ******/
{
   extern int debug ;

   if(debug == DEBUG)
   {
      Invert();
      Draw_Image(stdout) ;
      Invert() ;
   }
   return ;
}



int IsEven(int value)
/******
 *
 * Function to check if an integer is even
 *
 ******/
{
   return ((value % 2)  == 0) ;
}



void Invert(void)
/******
 *
 * Invert the matrix Old_Image
 *
 ******/
{
   int x, y ;
   extern old_image[MAX_WIDTH][MAX_HEIGHT] ;
   extern int width, height ;

   for (y = 1; y <= height; y++)
   {
      for (x = 1; x<= width; x++)
      {
         old_image[x][y] = 1 - old_image[x][y] ;
      }
   }
   return ;
}



void Usage(char *progname, char *reason)
{
   fprintf (stderr, "Error: %s\n", reason) ;
   fprintf (stderr, "\tUsage: %s <from-file> <save-format> [<to-file>] \n", progname) ;
   fprintf (stderr, "\tCurrently supported save formats :-\n") ;
   fprintf (stderr, "\t\t ASC :- ASCII Text file\n") ;
   fprintf (stderr, "\t\t SUN :- SUN Rasterfile Binary\n") ;
   fprintf (stderr, "\t\t VDU :- The Screen output device\n") ;
   fprintf (stderr, "\t\t ALL :- The Screen & debug info\n") ;
   fprintf (stderr, "\t\t NON :- No Output (For speed Tests)\n") ;
   return  ;
}
#endif /* __misc */
