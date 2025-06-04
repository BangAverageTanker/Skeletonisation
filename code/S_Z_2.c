/******
 *
 * Functions to  skeletonise an image
 * Using Suen and Zhangs Algorithm
 * Modifications by H E Lu and P S P Wang
 *
 *
 * ©1995 Simon Westerby
 *
 ******

 * Function Prototypes  */

void Suen_Zhang_2(void) ;
void SZ2_ImageSubtract(void) ;
void SZ2_Sub_Iteration_1(void) ;
void SZ2_Sub_Iteration_2(void) ;
int SZ2_Condition_A(int, int) ;
int SZ2_Condition_B(int, int) ;
int SZ2_Condition_C(int, int) ;
int SZ2_Condition_D(int, int) ;
int SZ2_Condition_C_Dash(int, int) ;
int SZ2_Condition_D_Dash(int, int) ;
int SZ2_No_Of_0_1_Combis(int, int) ;
int SZ2_Edge(int, int) ;

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

int SZ2_Edge(int i, int j) 
{
	int contour ;

	if ((P1 != P2) && (P1 == 1))
	{
		contour = TRUE ;
	}
	if ((P1 != P3) && (P1 == 1))
	{
		contour = TRUE ;
	}
	if ((P1 != P4) && (P1 == 1))
	{
		contour = TRUE ;
	}
	if ((P1 != P5) && (P1 == 1))
	{
		contour = TRUE ;
	}
	if ((P1 != P6) && (P1 == 1))
	{
		contour = TRUE ;
	}
	if ((P1 != P7) && (P1 == 1))
	{
		contour = TRUE ;
	}
	if ((P1 != P8) && (P1 == 1))
	{
		contour = TRUE ;
	}
	if ((P1 != P9) && (P1 == 1))
	{
		contour = TRUE ;
	}

	return (contour == TRUE) ;
}        

         

int SZ2_No_Of_0_1_Combis(int i, int j)
/* count the number of  0 1 pairs in the ordered set p2 .. p9 */
{
   int count = 0;
   extern int old_image[MAX_WIDTH][MAX_HEIGHT];

   if ((P2 == 0) && (P3 == 1))
   {
      count = count + 1 ;
   }
   if ((P3 == 0) && (P4 == 1))
   {
      count = count + 1 ;
   }
   if ((P4 == 0) && (P5 == 1))
   {
      count = count + 1 ;
   }
   if ((P5 == 0) && (P6 == 1))
   {
      count = count + 1 ;
   }
   if ((P6 == 0) && (P7 == 1))
   {
      count = count + 1 ;
   }
   if ((P7 == 0) && (P8 == 1))
   {
      count = count + 1 ;
   }
   if ((P8 == 0) && (P9 == 1))
   {
      count = count + 1 ;
   }
   if ((P9 == 0) && (P2 == 1))
   {
      count = count + 1 ;
   }
   return(count) ;
}

int SZ2_Condition_A(int i, int j)
{
   int No_Ones = 0 ;
   extern int old_image[MAX_WIDTH][MAX_HEIGHT];

   No_Ones = P2 + P3 + P4 + P5 + P6 + P7 + P8 + P9 ;

   return ((No_Ones <= 6) && (No_Ones >= 3)) ;
}

int SZ2_Condition_B(int i, int j)
{
   return (SZ2_No_Of_0_1_Combis(i, j) == 1) ;
}

int SZ2_Condition_C(int i, int j)
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT];

   return (P2*P4*P6 == 0) ;
}

int SZ2_Condition_D(int i, int j)
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT];

   return (P4*P6*P8 == 0) ;
}

int SZ2_Condition_C_Dash(int i, int j)
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT];

   return (P2*P4*P8 == 0) ;
}

int SZ2_Condition_D_Dash(int i, int j)
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT];

   return (P2*P6*P8 == 0) ;
}

void SZ2_Sub_Iteration_1()
{
   int i, j ;
   extern altered ;
   extern int image[MAX_WIDTH][MAX_HEIGHT] ;
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;
   extern int width, height ;

   altered = FALSE ;
   printf("Sub-iteration 1 \n") ;
   for(j=1; j<= height; j++)
   {
      for(i=1; i<= width; i++)
      {
         if(SZ2_Edge(i, j) &&
            SZ2_Condition_A(i, j) &&
            SZ2_Condition_B(i, j) &&
            SZ2_Condition_C(i, j) &&
            SZ2_Condition_D(i, j)   )
         {
            image[i][j] = 1 ;
            altered = TRUE ;
         }
      }
   }
   return ;
}

void SZ2_Sub_Iteration_2()
{
   int i, j ;
   extern altered ;
   extern int image[MAX_WIDTH][MAX_HEIGHT] ;
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;
   extern int width, height ;
   
   altered = FALSE ;
   printf("Sub-iteration 2\n") ;
   for(j=1; j<= height; j++)
   {
      for(i=1; i<= width; i++)
      {
         if(SZ2_Edge(i, j) &&
            SZ2_Condition_A(i, j) &&
		SZ2_Condition_B(i, j) &&
            SZ2_Condition_C_Dash(i, j) &&
            SZ2_Condition_D_Dash(i, j)   )
         {
            image[i][j] = 1 ;
            altered = TRUE ;
         }
      }
   }
   return ;
}


void SZ2_ImageSubtract()
{
   int i, j;
   extern int image[MAX_WIDTH][MAX_HEIGHT] ;
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;
   extern int width, height ;

   for (j = 1; j <= height; j++)
   {
      for (i = 1; i <= width; i++)
      {
         old_image[i][j] = old_image[i][j] - image[i][j] ;
         image[i][j] = 0 ;
      }
   }
   return ;
}
      
void Suen_Zhang_2()
{
   int count = 0 ;
   extern altered ;

   Invert() ;
   do
   {
      SZ2_Sub_Iteration_1() ;
      if (altered == TRUE)
      {
         SZ2_ImageSubtract() ;
         All() ;
         SZ2_Sub_Iteration_2() ;
         if(altered == TRUE)
         {
            SZ2_ImageSubtract() ;
            All() ;
         }
      }
      count = count + 1 ;
      printf("Iteration %d completed\n", count) ;
   } while (altered == TRUE) ;
   printf("\nThinning Completed\n") ;
   Invert() ;
   return ;
}
