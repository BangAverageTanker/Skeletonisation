/******
 *
 * Basic Module Executable
 *
 * 27/01/96 Version Beta 1
 *
 * Must have three Arguments :
 *
 * <from-file> : Sun Rasterfile image too be thinned
 * <save-format> : Format to save the processe image as (ascii or Sun raster...)
 * <to-file> : File to save the processed image data to.
 *
 ******/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char AMIGA_HCSP_Module[] = "$VER: Holt et al Module Version 1.0" ;
static char UNIX_HCSP_Module[] = "@(#)RELEASE Holt et al Module Version 1.0" ;

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define MAX_WIDTH  200
#define MAX_HEIGHT 200

#define ASCII 1
#define SUNR  2
#define SCRN  3
int debug = 0 ;
#define DEBUG 4
#define NONE  5

#define ClearScreen() system("clear") 

#include "misc.c"
#include "rasterio.c"
#include "HCSP_2.c"

int image[MAX_WIDTH][MAX_HEIGHT];
int old_image[MAX_WIDTH][MAX_HEIGHT];
int width, height ;
signed char *base_memory ;

struct rasterfile header ;
FILE *output_fp ;

main (int argc, char **argv)
{
   char *input_fn ;
   char *output_fn ;
   int savetype ;
   int error ;

   if ((argc < 3) || (argc > 4))
   {
      Usage(argv[0], "Wrong number of arguments!") ;
      exit (1) ;
   }

   if (strncmp (argv[2], "ASC", 3) == 0)
   {
      savetype = ASCII ;
   }
   else
   {
      if (strncmp (argv[2], "SUN", 3) == 0)
      {
         savetype = SUNR ;
      }
      else
      {
         if (strncmp (argv[2], "VDU", 3) == 0)
         {
            savetype = SCRN ;
         }
         else
         {
            if (strncmp (argv[2], "ALL", 3) == 0)
            {
               savetype = SCRN ;
               debug = DEBUG ;
            }
            else
            {
               if (strncmp (argv[2], "NON", 3) == 0)
               {
                  savetype = NONE ;
               }
               else
               {
                  Usage(argv[0], "Unrecognised save type!") ;
                  exit (1) ;
               }
            }
         }
      }
   }

   input_fn = malloc (strlen (argv[1])) ;
   
   if (input_fn != NULL)
   {
      input_fn = strcpy (input_fn, argv[1]) ;
   }
   else
   {
      fprintf (stderr, "Error: Out of memory!!\n") ;
      exit (1) ;
   }
   
   if (!((savetype == SCRN) || (savetype == NONE)))
   {
      output_fn = malloc (strlen (argv[3])) ;
   
      if (output_fn != NULL)
      {
         output_fn = strcpy(output_fn, argv[3]) ;
      }
      else
      {
         fprintf (stderr, "Error: Out of memory!!\n") ;
         free (input_fn) ;
         exit(1) ;
      }
   }
   
   if ((error=Load_Raster (input_fn)) != RIO_SUCCESS)
   {
      fprintf(stderr, "File:%s - Load Failed\n\t%s", input_fn, Ras_IO_Error(error));
      free (input_fn) ;
      free (output_fn) ;
      
      exit (1) ;
   }
   
   Holt () ;
   
   switch (savetype)
   {
      case ASCII :
         if ((output_fp = fopen (output_fn, "w")) != NULL)
         {
            Draw_Image (output_fp) ;
            fclose (output_fp) ;
         }
         break ;
      case SUNR :
         Invert() ;
         if ((error = Save_Raster(output_fn)) != RIO_SUCCESS)
         {
            Ras_IO_Error (error) ;
            free (input_fn) ;
            free (output_fn) ;
            exit (1) ;
         }
         break ;
      case SCRN :
         Draw_Image (stdout) ;
         break ;
      case NONE :
         break ;
   }
   
   free (input_fn) ;
   if (!((savetype == SCRN) || (savetype == NONE)))
   {
      free (output_fn) ;
   }
   
   return (0) ;
}
