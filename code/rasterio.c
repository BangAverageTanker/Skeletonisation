/******
 *
 * Load a mono, uncompressed standard   
 * Sun Rasterfile and decode it into
 * an array.
 *
 ******/

#ifndef __rasterio
#define __rasterio

static char AMIGArasterio[] = "$VER: rasterio.c Version 1 ©1995 Simon Westerby" ;
static char UNIXrasterio[] = "@(#)RELEASE rasterio.c Version 1 (c)1995 Simon Westerby" ;

#include <math.h>
#include <stdlib.h>
#include <rasterfile.h>
#include "rasterio.h"

#define RIO_SUCCESS              0
#define RIO_FILE_OPEN_FAILED     7
#define RIO_FILE_IS_EMPTY        6
#define RIO_NOT_RASTERFILE       5
#define RIO_TOO_MANY_BITS        3
#define RIO_NO_COLOUR_MAP        2
#define RIO_HEADER_CORRUPT       1
#define RIO_NO_MEM_4_IMAGE       8
#define RIO_IMAGE_CORRUPT        9

#define RIO_CANT_WRITE_HEADER   10
#define RIO_CANT_OPEN_FILE      11
#define RIO_CANT_WRITE_IMAGE    12
#define RIO_CANT_ALLOCATE_MEM   13

#define RIO_FILE_TOO_BIG        14

#define RIO_ERROR_MSG_SIZE     255

char *Ras_IO_Error(int errval)
/******
 *
 * Get associated i/o error message 
 *
 ******/
{
   char *ErrorMessage ;

   ErrorMessage = malloc(RIO_ERROR_MSG_SIZE) ;

   switch (errval)
   {
      case RIO_FILE_OPEN_FAILED :
         ErrorMessage = "RAS IO ERROR: Couldn't open file.\n" ;
         break ;
      case RIO_FILE_IS_EMPTY :
         ErrorMessage = "RAS IO ERROR: File is too short.\n" ;
         break ;
      case RIO_NOT_RASTERFILE :
         ErrorMessage = "RAS IO ERROR: File is not a Sun Rasterfile.\n" ;
         break ;
      case RIO_TOO_MANY_BITS :
         ErrorMessage = "RAS IO ERROR: File is not monochrome.\n(too many bits per pixel)\n" ;
         break ;
      case RIO_NO_COLOUR_MAP :
         ErrorMessage = "RAS IO ERROR: File has no colour map.\n(Is this a problem?)\n" ;
         break ;
      case RIO_HEADER_CORRUPT :
         ErrorMessage = "RAS IO ERROR: The file is corrupt.\n" ;
         break ;
      case RIO_NO_MEM_4_IMAGE :
         ErrorMessage = "RAS IO ERROR: Couldn't allocate memory for the image data.\n" ;
         break ;
      case RIO_IMAGE_CORRUPT :
         ErrorMessage = "RAS IO ERROR: The file is corrupt.\n" ;
         break ;
      case RIO_SUCCESS :
         ErrorMessage = "Operation successful.\n(No Errors Fool!)\n" ;
         break ;
      case RIO_CANT_WRITE_HEADER :
         ErrorMessage = "RAS IO ERROR: Problems occurred saving file header.\n" ;
         break ;
      case RIO_CANT_OPEN_FILE :
         ErrorMessage = "RAS IO ERROR: Couldn't open file for writing to.\n" ;
         break ;
      case RIO_CANT_WRITE_IMAGE :
         ErrorMessage = "RAS IO ERROR: Problems occurrred saving the image data.\n" ;
         break ;
      case RIO_CANT_ALLOCATE_MEM :
         ErrorMessage = "RAS IO ERROR: Couldn't allocate memory for saving image.\n" ;
         break ;
      case RIO_FILE_TOO_BIG :
         ErrorMessage = "RAS IO ERROR: File is too big for allocated memory.\n" ;
         break ;
      default :
         ErrorMessage = "RAS IO ERROR: Unknown error number - PANIC!\n" ;
         break ;
   }
   return(ErrorMessage) ;
}



int Get_Bit(int bit, signed char data)
/******
 *
 * Get the value of a given bit in a given byte.
 *
 ******/
{
   signed char mask ;
   int value ;

   mask = 1 << (8-bit) ;
   value =  (mask & data) >> (8-bit) ;

   return(abs(value)) ;
}


signed char Set_Bit(int bit, signed char data, int value)
/******
 *
 * Set a given bit to a given value
 *
 *****/
{

   if (bit == 1)
   {
      data = (value << (8-bit)) ;
   }
   else
   {
      data = data | (value << (8-bit))  ;
   }

   return (data) ;
}

#define RASSIZE sizeof(struct rasterfile)
#define IMAGESIZE header.ras_length

int Load_Raster(char *filename)
/******
 *
 * Load a Sun Rasterfile into memory and decode into an array 
 *
 ******/
{
   extern signed char *base_memory ;
   extern int image[MAX_WIDTH][MAX_HEIGHT] ;
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;
   extern struct rasterfile header ;
   extern int width, height ;
   FILE *file_handle ;
   int x,
       y,
          bit = 1,
          error = RIO_SUCCESS ;
   signed char *memory_location ;

   if (file_handle = fopen(filename, "rb"))
   {
      if (fread(&header, RASSIZE, 1, file_handle) == 1)
      {
         if (header.ras_magic == RAS_MAGIC)
         {
            if (header.ras_depth == 1)
            {
               if ((header.ras_width <= (MAX_WIDTH-2)) && (header.ras_height <= (MAX_HEIGHT-2)))
               {
                  if (header.ras_maptype != RMT_NONE)
                  {
                     if (fseek(file_handle, header.ras_maplength, SEEK_CUR) == 0)
                     {
                        width = header.ras_width ;
                        height = header.ras_height ;
                        if (IMAGESIZE == 0)
                        {
                           header.ras_length = (width * height) / 8 ;
                        }
                        if ((base_memory = (signed char *) malloc(IMAGESIZE)) != NULL)
                        {
                           if (fread(base_memory, IMAGESIZE, 1, file_handle) == 1)
                           {
/* 
            Now decode the image from a block of
            memory into the array old_image
            (already defined somewhere else).
*/
                              memory_location = base_memory ;
                              for (y = 1; y <= height; y++)
                              {
                                 for (x = 1; x <= width; x++)
                                 {
                                    old_image[x][y] = Get_Bit(bit, *memory_location) ;
                                    bit = bit + 1 ;
                                    if (bit > 8)
                                    {
                                       bit = 1 ;
                                       memory_location = memory_location + 1 ;
                                    }
                                 }
                              }
                           }
                           else
                           {
                              error = RIO_IMAGE_CORRUPT ;
                           }
                           free(base_memory) ;
                        }
                        else
                        {
                           error = RIO_NO_MEM_4_IMAGE ;
                        }
                     }
                     else
                     {
                        error = RIO_HEADER_CORRUPT ;
                     }
                  }
                  else
                  {
                     width = header.ras_width ;
                     height = header.ras_height ;
                     if (IMAGESIZE == 0)
                     {
                        header.ras_length = (width * height) / 8 ;
                     }
                     if ((base_memory = (signed char *) malloc(IMAGESIZE)) != NULL)
                     {
                        if (fread(base_memory, IMAGESIZE, 1, file_handle) == 1)
                        {
                           memory_location = base_memory ;
                           for (y = 1; y <= height; y++)
                           {
 /* 
            Now decode the image from a block of
            memory into the array image
            (already defined somewhere else).
*/
                              for (x = 1; x <= width; x++)
                              {
                                 old_image[x][y] = Get_Bit(bit, *memory_location) ;
                                 bit = bit + 1 ;
                                 if (bit > 8)
                                 {
                                    bit = 1 ;
                                    memory_location = memory_location + 1 ;
                                 }
                              }
                           }
                           free(base_memory) ;
                        }
                        else
                        {
                           error = RIO_IMAGE_CORRUPT ;
                        }
                     }
                     else
                     {
                        error = RIO_NO_MEM_4_IMAGE ;
                     }
                  }
               }
               else
               {
                  error = RIO_FILE_TOO_BIG ;
               }
            }
            else
            {
               error = RIO_TOO_MANY_BITS ;
            }
         }
         else
         {
            error = RIO_NOT_RASTERFILE ;
         }
      }
      else
      {
         error = RIO_FILE_IS_EMPTY ;
      }
      fclose(file_handle) ;
   }
   else
   {
      error = RIO_FILE_OPEN_FAILED ;
   }
   
   return (error) ;
}


int Save_Raster(char *filename)
/******
 * Encode the image from the array image and save as a rasterfile.
 *
 * NOTE: As this only creates mono rasterfiles, then no colour map is needed,
 *       so header. ras_maptype = RMT_NONE and ras_maplength = 0.
 *
 ******/
{
   signed char *base_memory ;
   extern int image[MAX_WIDTH][MAX_HEIGHT] ;
   extern struct rasterfile header ;
   
   FILE *file_handle ;
   int x,
       y,
          bit = 1,
          error = RIO_SUCCESS ;
   signed char *memory_location ;   

   if (file_handle=fopen(filename, "wb"))
   {
      header.ras_maptype = RMT_NONE;
      header.ras_maplength = 0 ;
      if ((base_memory = (signed char *) malloc(IMAGESIZE)) != NULL)
      {
         if (fwrite(&header, RASSIZE, 1, file_handle) == 1)
         {
            memory_location = base_memory ;
            for (y = 1; y <= header.ras_height; y++)
            {
               for (x = 1; x <= header.ras_width; x++)
               {
                  *memory_location = Set_Bit(bit, *memory_location, old_image[x][y]) ;
                  bit = bit + 1 ;
                  if (bit > 8)
                  {
                     bit = 1 ;
                     memory_location = memory_location + 1 ;
                  }
               }
            }
            if (fwrite(base_memory, IMAGESIZE, 1, file_handle) !=1)
            {
               error = 12 ;
            }
         }
         else
         {
            error = 10 ;
         }
         free(base_memory) ;
      }
      else
      {
         error = 13 ;
      }
      fclose(file_handle) ;
   }
   else
   {
      error = 11 ;
   }   

   return(error) ;
}

#endif /* __rasterio */
