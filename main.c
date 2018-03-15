#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
/*int ind(int a){

    switch ( a ) {
    case 0:
        return 3    ;
         break;
    case 1:
        return 4;
          break;
    case 2:
         return 0;
          break;
    case 3:
        return 1;
          break;
    case 4:
        return 2;
          break;
    default:
          break;
    }
}*/


uint64_t _bswap64(uint64_t a)
{
  a = ((a & 0x00000000000000FFULL) << 56) |
      ((a & 0x000000000000FF00ULL) << 40) |
      ((a & 0x0000000000FF0000ULL) << 24) |
      ((a & 0x00000000FF000000ULL) <<  8) |
      ((a & 0x000000FF00000000ULL) >>  8) |
      ((a & 0x0000FF0000000000ULL) >> 24) |
      ((a & 0x00FF000000000000ULL) >> 40) |
      ((a & 0xFF00000000000000ULL) >> 56);
  return a;
}

int modulo(int x, int y){
  	if(x<0){
		    x = x*-1;
  		  return (y-(x%y))%y;
            }
    else{
    	  return (x%y);
        }
}


void theta(uint64_t **A,uint64_t **Aaux,uint64_t *C,uint64_t *D)
{
  uint64_t temp;
  for (int i=0;i<5;i++)
  {
    C[i] =  A[i][0] ^ A[i][1] ^ A[i][2] ^ A[i][3] ^ A[i][4];

  }
  for (int j = 0;j<5;j++){
    temp = (C[modulo(j+1,5)] & 0x8000000000000000ULL) << 63 | (C[modulo(j+1,5)] & 0x7FFFFFFFFFFFFFFFULL >> 1);
    D[j] = C[modulo(j-1,5)] ^ temp;
  }
  for (int k = 0;j<5;j++){
    Aaux[k][l]=A[k][l] ^ D[k];
  }
}





int main(/* int argc, const char* argv[] */)
{
	int flag = 1;
  int end;
	int l;
	int r;
	int b = 1600;
	int w = b/25;
	int i = 0;
	int j = 0;
	int h = 0;
	int y = 0;

	FILE *file;
	uint64_t **A;
  uint64_t **C;
  uint64_t **D;
	uint64_t *N;
  uint64_t **Aaux;

	A = (unsigned char **) malloc(5* sizeof(unsigned char *));      //Matriz antes de Theta

	for (r = 0; r<5;r++)
	 {
	    A[r] = (unsigned char *) malloc(sizeof(unsigned char)*5);
	   }

  Aaux = (unsigned char **) malloc(5* sizeof(unsigned char *));      //Matriz auxiliar de A

  for (r = 0; r<5;r++)
    {
      A[r] = (unsigned char *) malloc(sizeof(unsigned char)*5);
    }



  //C = (uint64_t *) malloc(5* sizeof(uint64_t));      //Matriz C antes de Theta
  //D = (uint64_t *) malloc(5* sizeof(uint64_t));      //Matriz  Dantes de Theta

unsigned char

	unsigned char *buffer,Zeros;
	buffer = (unsigned char *) malloc(25*sizeof(unsigned char));
	Zeros = 0;
	file = fopen("prueba","rb");   //-f nombrearchivo -d
	if (file==NULL)
	{
		fputs ("Error de archivo\n", stderr);
		exit(1);
	}

  end = fread(buffer,8,1,file);
	while(end != 0)
	{
		printf("\n");
    printf("%lu",*buffer);
    A[i][j] = *buffer;
	/*	for (h = 0;h<8;h++)
		{
			printf("\n");

			printf("\n");
		}*/
		printf("\n");
		printf("%lu", A[i][j]);
    printf("\n");
    printf("%lu", sizeof(A[i][j]));
    end = fread(buffer,8,1,file);
    //printf("%d",end);
    printf("\n");
		if (j==5){
			i += 1;
		}
		else{
			j+=1;
		}
		if (i==3 && j ==2){
			break;
		}
	}



  A = (unsigned char ***) malloc (5*sizeof(unsigned char ***));

	for (int i = 0; i< 5; i++)
	{
			 A[i] = (unsigned char **) malloc(5*sizeof(unsigned char *));
			 for (int j = 0; j < 5; j++)
			 {
					 A[i][j] = (unsigned char *)malloc(w*sizeof(unsigned char));
			 }
	}

  /*for(j = 2;j<5;j++){
    A[3][j]=Zeros;
  }
	printf("%lu", A[i][j]);
  for (i = 4;i<5;i++)
  {
    for (j = 0;j<5;j++){
      A[i][j] = Zeros;
    }

  }*/
//Si no logra leer el bloque se debe leer bloques mas pequenos
/*  while (end == 0) {
      printf("%lu",*buffer);
      A[i][j] = *buffer;
      for (h = 0;h<8;h++)
      {
        printf("\n");

        //printf("\n");
      }
      end = fread(buffer,8,1,file);
      if (j==5){
        i += 1;
      }
      else{
        j+=1;
      }
      if (i==3 && j ==2){
        break;
      }

      if (i<3 || j<1){
        printf("Se necesita padding \n");
      }
  }*/
	printf("\n");
	/*printf(sizeof(buffer));*/
void free (void* buffer);
return 0;

}
