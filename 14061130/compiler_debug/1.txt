const int max_len = 32;
int list[32];


int getn(int x){
  int tmp;
  tmp = 1;
  if(x <= 0){
    return (0);
  }
  if(x >= 1){
    return (getn(x - 1) + tmp);
  }
  return (0);
}

void dag(){
   int i,x,y,z,c ;
   x = 0 ;
   y = 0 ;
   z = 0 ;
   i = 0 ;
   while(i < getn(max_len) - 3){
     x = x + list[i] ;
     y = y + list[i+1] ;
     z = z + list[i+2] ;
     i = i + 3 ;
   }

   c = 3 ;
   i = 0 ;
   while(i < 100) {
     y = x * c + z - (y * 2) ;
     z = x * c - z + (y * 2) ;
     x = x * c + z - (y * 2) ; 
     i = i + 1 ; 
   }


   printf("x= ", x) ;
   printf("y= ", y) ;
   printf("z= ", z) ;

}
void quicksort(int i,int j)
{
        int x,y,z;
        int tmp;
        x = i;
        y = j;
        z = list[(x + y) / 2];
        while(x <= y){
                while(z > list[y]) {
                        y = y - 1;
                }

                while(z < list[x]) {
                        x = x + 1;
                }

                if (x <= y){
                         tmp = list[x];
                         list[x] = list[y];
                         list[y] = tmp;
                         x = x + 1;
                         y = y - 1;
                }
        }

        if ( x < j) quicksort(x , j);
        if ( i < y) quicksort(i , y);
}

void print_list(int n)
{
   int i;
   i = 0;
   while(i < n){
      if( i == 1 ){
         printf(" ", list[i]);
      }
      if( i == 7){
         printf(" ", list[i]);
      }
      if( i == 12 ){
         printf(" ", list[i]);
      }
      i = i + 1;
   }
}

void main()
{
   int i;

        i = 0;
        while(i < getn(max_len)){
                list[i] = i * 99 ;
                i = i + 2;
        }
        i = 1;
        while(i < getn(max_len)){
                list[i] = (max_len - i) * 99 ;
                i = i + 2;
        }

   printf("before: ");
   print_list(max_len);

   quicksort(0,max_len - 1);

   printf(" after: ");
   print_list(max_len);
   
   dag() ;
}
