/******
 *
 * Functions to  skeletonise an image
 * Using Wu and Tsai's Algorithm
 * modified by Stewart.
 *
 * ©1995 Simon Westerby
 *
 ******

 * Function Prototypes  */
void Stewart(void) ;
void S_Remove_Point(int, int) ;
int S_Edge(int, int) ;
int S_Protected(int, int) ;

#define C  (old_image[i][j] == BLACK)
#define N  (old_image[i][j-1] == BLACK)
#define S  (old_image[i][j+1] == BLACK)
#define E  (old_image[i+1][j] == BLACK)
#define W  (old_image[i-1][j] == BLACK)
#define NE (old_image[i+1][j-1] == BLACK)
#define SE (old_image[i+1][j+1] == BLACK)
#define NW (old_image[i-1][j-1] == BLACK)
#define SW (old_image[i-1][j+1] == BLACK)

#define c   i, j
#define n   i, j-1
#define s   i, j+1
#define e   i+1, j
#define w   i-1, j
#define ne  i+1, j-1
#define nw  i-1, j-1
#define se  i+1, j+1
#define sw  i-1, j+1

int altered ;
int debug ;

#define P1 old_image[i][j]

#define BLACK 1
#define WHITE 0

int S_Edge(int i, int j)
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;
   
   return (C && ((W && !E) && (((NW && SW) && ((N || !NE) && (S || !SE))) || (S && !(N || NE))) ||
                 (N && !S) && (((NW && NE) && ((E || !SE) && (W || !SW))) || (W && !(E || SE))) ||
                 (E && !W) && (((NE && SE) && ((S || !SW) && (N || !NW))) || (N && !(S || SW))) ||
                 (S && !N) && (((SW && SE) && ((W || !NW) && (E || !NE))) || (E && !(W || NW)))  
                )
             ) ;
}

int S_Protected(int i, int j)
{
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;
   
   return (!S_Edge(c)
        || (S_Edge(e) && N && S)
        || (S_Edge(s) && W && E)
        || (!SE && S && E && (S_Edge(s) || S_Edge(e)))
        || (!SW && W && S && (S_Edge(w) || S_Edge(s)))
        || (S_Edge(e) && S_Edge(s) && S_Edge(se))
          );
}

void S_Remove_Point(int i, int j)
{
   extern int altered ;
   extern int old_image[MAX_WIDTH][MAX_HEIGHT] ;
   extern int image[MAX_WIDTH][MAX_HEIGHT] ;
   extern int debug ;
   int value = 0 ;

   if (debug == DEBUG)
   {
      if (P1 == BLACK)
      {
         if (S_Edge(i, j))
         {
            value = value + 1 ;
            if (!S_Protected(i, j))
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
            if (S_Protected(i, j))
            {
               value = value + 2 ;
            }
         }
      }
      printf("%d", value) ;
   }
   else
   {
      if (P1 == BLACK)
      {
         if (S_Edge(i, j) && (!S_Protected(i, j)))
          {
            altered = TRUE ;
            image[i][j]  = WHITE ;
         }
      }
   }
   return ;
}



void Stewart()
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
            S_Remove_Point(i, j) ;
         }
         if (debug == DEBUG)
         {
            printf("\n") ;
         }
      }
      Image_2_Old_Image() ;
   } while (altered == TRUE) ;
   Invert() ;
   return ;
}      
