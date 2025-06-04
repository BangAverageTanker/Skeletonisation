/******
 *
 * Functions to skeletonise an image
 * Using Wu and Tsai's Algorithm
 *
 *
 * ©1995 Simon Westerby
 *
 ******

 * Function Prototypes  */
void Wu_Tsai(void) ;
void WT_Remove_Point(int, int) ;
int WT_Template_A(int, int) ;
int WT_Template_B(int, int) ;
int WT_Template_C(int, int) ;
int WT_Template_D(int, int) ;
int WT_Template_E(int, int) ;
int WT_Template_F(int, int) ;
int WT_Template_G(int, int) ;
int WT_Template_H(int, int) ;
int WT_Template_I(int, int) ;
int WT_Template_J(int, int) ;
int WT_Template_K(int, int) ;
int WT_Template_L(int, int) ;
int WT_Template_M(int, int) ;
int WT_Template_N(int, int) ;

int altered ;

#define P1 old_image[i][j]
#define P2 old_image[i][j-1]
#define P3 old_image[i+1][j-1]
#define P4 old_image[i+1][j]
#define P5 old_image[i+1][j+1]
#define P6 old_image[i][j+1]
#define P7 old_image[i-1][j+1]
#define P8 old_image[i-1][j]
#define P9 old_image[i-1][j-1]
/*
 1 extra for Template d
*/
#define P10 old_image[i][j+2]
/*
 1 extra for template c 
*/
#define P11 old_image[i+2][j]

#define BLACK 1
#define WHITE 0

int WT_Template_A(int i, int j)
{
   extern int altered ;
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;

   return (((P3 == WHITE) || (P5 == WHITE)) && (P4 == WHITE) &&
            (P2 == BLACK) && (P6 == BLACK) && (P7 == BLACK) &&
            (P8 == BLACK) && (P9 == BLACK)) ;
}   
   

                  
int WT_Template_B(int i, int j)
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;

   return (((P5 == WHITE) || (P7 == WHITE)) && (P6 == WHITE) &&
            (P2 == BLACK) && (P3 == BLACK) && (P4 == BLACK) &&
            (P8 == BLACK) && (P9 == BLACK)) ;
}   



int WT_Template_C(int i, int j)
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;
   extern int width ;
   int p11 ;

   if (i > width)
   {
      p11 = WHITE ;
   }
   else
   {
      p11 = P11 ;
   }

   return (((P7 == WHITE) || (P9 == WHITE)) && (P8 == WHITE) && 
            (P2 == BLACK) && (P3 == BLACK) && (P4 == BLACK) &&
            (P5 == BLACK) && (P6 == BLACK) && (p11 = BLACK)) ;
}



int WT_Template_D(int i, int j)
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;
   extern int height ;
   int p10 ;

   if (j > height )
   {
      p10 = WHITE ;
   }
   else
   {
      p10 = P10 ;
   }

   return (((P9 == WHITE) || (P3 == WHITE)) && (P2 == WHITE) &&
            (P4 == BLACK) && (P5 == BLACK) && (P6 == BLACK) &&
            (P7 == BLACK) && (P8 == BLACK) && (p10 == BLACK)) ;
}



int WT_Template_E(int i, int j)
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;

   return (((P6 == BLACK) && (P8 == BLACK)) &&
           ((P2 == WHITE) && (P3 == WHITE) && (P4 == WHITE))) ;
}



int WT_Template_F(int i, int j)
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;

   return (((P2 == BLACK) && (P3 == BLACK) && (P4 == BLACK)) &&
           ((P6 == WHITE) && (P7 == WHITE) && (P8 == WHITE))) ;
}



int WT_Template_G(int i, int j)
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;

   return (((P2 == BLACK) && (P4 == BLACK)) &&
           ((P3 == WHITE) && (P5 == WHITE) && (P6 == WHITE)) &&
           ((P7 == WHITE) && (P8 == WHITE) && (P9 == WHITE))) ;
}



int WT_Template_H(int i, int j)
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;

   return (((P2 == BLACK) && (P8 == BLACK)) &&
           ((P4 == WHITE) && (P5 == WHITE) && (P6 == WHITE))) ;
}



int WT_Template_I(int i, int j)
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;

   return (((P4 == BLACK) && (P5 == BLACK) && (P6 == BLACK)) &&
           ((P8 == WHITE) && (P9 == WHITE) && (P2 == WHITE))) ;
}



int WT_Template_J(int i, int j)
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;

   return (((P4 == BLACK) && (P6 == BLACK)) &&
           ((P2 == WHITE) && (P3 == WHITE) && (P5 == WHITE)) &&
           ((P7 == WHITE) && (P8 == WHITE) && (P9 == WHITE))) ;
}



int WT_Template_K(int i, int j)
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;

   return (((P5 == BLACK) && (P6 == BLACK) && (P7 == BLACK)) &&
           ((P2 == WHITE) && (P3 == WHITE) && (P4 == WHITE)) &&
           ((P8 == WHITE) && (P9 == WHITE))) ;
}



int WT_Template_L(int i, int j)
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;

   return (((P7 == BLACK) && (P8 == BLACK) && (P9 == BLACK)) &&
           ((P2 == WHITE) && (P3 == WHITE) && (P4 == WHITE)) &&
           ((P5 == WHITE) && (P6 == WHITE))) ;
}



int WT_Template_M(int i, int j)
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;

   return (((P2 == BLACK) && (P3 == BLACK) && (P9 == BLACK)) &&
           ((P4 == WHITE) && (P5 == WHITE) && (P6 == WHITE)) &&
           ((P7 == WHITE) && (P8 == WHITE))) ;
}



int WT_Template_N(int i, int j)
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;

   return (((P3 == BLACK) && (P4 == BLACK) && (P5 == BLACK)) &&
           ((P6 == WHITE) && (P7 == WHITE) && (P8 == WHITE)) &&
           ((P9 == WHITE) && (P2 == WHITE))) ;
}



void WT_Remove_Point(int i, int    j)
{
   extern int altered ;
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;
   extern int image[MAX_WIDTH][MAX_HEIGHT] ;

   if (P1 == BLACK)
   {
      if (WT_Template_A(i, j) ||
          WT_Template_B(i, j) ||
          WT_Template_C(i, j) ||
          WT_Template_D(i, j) ||
          WT_Template_E(i, j) ||
          WT_Template_F(i, j) ||
          WT_Template_G(i, j) ||
          WT_Template_H(i, j) ||
          WT_Template_I(i, j) ||
          WT_Template_J(i, j) ||
          WT_Template_K(i, j) ||
          WT_Template_L(i, j) ||
          WT_Template_M(i, j) ||
          WT_Template_N(i, j)   )
      {
	   altered = TRUE ;
         image[i][j]  = WHITE ;
      }
   }
   return ;
}



void Wu_Tsai()
{
   int i, j ;
   int count = 0 ;
   extern int width, height; 
   extern int altered ;

   Invert() ;
   Old_Image_2_Image() ;
   do
   {
      altered = FALSE ;
      count = count + 1 ;
      printf("Iteration %d \n", count) ;
      for (j = 1; j <= height; j++)
      {
         for (i = 1; i <= width; i++)
         {
            WT_Remove_Point(i, j) ;
         }
      }
      Image_2_Old_Image() ;
      All() ;
   } while (altered == TRUE) ;
   printf("\nThinning completed\n") ;
   Invert() ;
   return ;
}
