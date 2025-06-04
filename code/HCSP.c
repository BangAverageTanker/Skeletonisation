/******
 *
 * Functions to  skeletonise an image
 * Using the Holt et al. Algorithm
 *
 * ©1995 Simon Westerby 
 *
 ******

 * Function Prototypes  */
void Holt(void) ;
void HSCP_Remove_Point(int, int) ;
int HSCP_Edge(int, int) ;
void HSCP_Check(int, int, int) ;
int HSCP_Protected(int, int) ;
/*
 * Global variables 
 */
int altered ;
int debug ;
int edge [MAX_WIDTH][MAX_HEIGHT] ;
int t00, t01, t01s, t11 ;

#define C  old_image[i][j]
#define N  old_image[i][j-1]
#define NE old_image[i+1][j-1]
#define E  old_image[i+1][j]
#define SE old_image[i+1][j+1]
#define S  old_image[i][j+1]
#define SW old_image[i-1][j+1]
#define W  old_image[i-1][j]
#define NW old_image[i-1][j-1]

#define c   i, j
#define n   i, j-1
#define s   i, j+1
#define e   i+1, j
#define w   i-1, j
#define ne  i+1, j-1
#define nw  i-1, j-1
#define se  i+1, j+1
#define sw  i-1, j+1

#define BLACK 1
#define WHITE 0

int HSCP_Edge(int i, int j)
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;

   int edge = 0 ;
   extern int t00 ;
   extern int t01 ;
   extern int t01s ;
   extern int t11 ;

   t00 = FALSE ;
   t01 = FALSE ;
   t01s = FALSE ;
   t11 = FALSE ;   

   HSCP_Check (NW, N, NE) ;
   HSCP_Check (NE, E, SE) ;
   HSCP_Check (SE, S, SW) ;
   HSCP_Check (SW, W, NW) ;

   edge = ((C == BLACK) && (t00 == TRUE) && (t11 == TRUE) && (t01s == FALSE)) ;
   
   return (edge) ;
}

void HSCP_Check(int v1, int v2, int v3)
{
   extern int t00, t01, t01s, t11 ;

   if ((v2 == WHITE) && ((v1 == WHITE) || (v3 == WHITE)))
   {
      t00 = TRUE ;
   }
   if ((v2 == BLACK) && ((v1 == BLACK) || (v3 == BLACK)))
   {
      t11 = TRUE ;
   }
   if (((v1 == WHITE) && (v2 == BLACK)) || ((v2 == WHITE) && (v3 == BLACK)))
   {
      t01s = t01 ;
      t01 = TRUE ;
   }
   return ;
}

int HSCP_Protected(int i, int j) 
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;
   extern int image[MAX_WIDTH][MAX_HEIGHT] ;

   return ((C == BLACK) && ((!HSCP_Edge(c)) || 
                (HSCP_Edge(e) && (N == BLACK) && (S == BLACK)) ||
                (HSCP_Edge(s) && (W == BLACK) && (E == BLACK)) ||
                (HSCP_Edge(e) && HSCP_Edge(se) && HSCP_Edge(s))  )
          ) ;
}


void HSCP_Remove_Point(int i, int j)
{
   extern int altered ;
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;
   extern int image[MAX_WIDTH][MAX_HEIGHT] ;
   extern int debug ;
   int value = 0 ;

   if (debug == DEBUG)
   {
      if (C == BLACK)
      {
         if (HSCP_Edge(i, j))
         {
            value = value + 1 ;
            if (!HSCP_Protected(i, j))
            {
               altered = TRUE ;
               image[i][j] = WHITE ;
            }
            else
            {
               value = value + 2 ;
            }
         }
         else
         {
            if (HSCP_Protected(i, j))
            {
               value = value + 2 ;
            }
         }
      }
      printf("%d", value) ;
   }
   else
   {
      if (C == BLACK)
      {
         if (HSCP_Edge(i, j))
         {
            if (!HSCP_Protected(i, j))
             {
               altered = TRUE ;
               image[i][j]  = WHITE ;
            }
         }
      }
   }
   return ;
}



void Holt()
{
   int i, j ;
   int count = 0 ;
   extern int width, height; 
   extern int altered ;
   extern int debug ;

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
            HSCP_Remove_Point(i, j) ;
         }
         if (debug == DEBUG)
         {
            printf("\n") ;
         }
      }
      Image_2_Old_Image() ;
   } while (altered == TRUE) ;
   printf("Thinning completed.\n") ;
   Invert() ;
   return ;
}      
