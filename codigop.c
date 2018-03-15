#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

int main(/* int argc, const char* argv[] */)
{
	int flag = 1;
  int end = 1;
	int l;
	int r;
	int b = 1600;
	int w = b/25;
	int i = 0;
	int j = 0;
	int h = 0;
	int y = 0;

	FILE *file;
	unsigned char  ***A;
  uint64_t **C;
  uint64_t **D;
	uint64_t *N;
  uint64_t **Aaux;
	unsigned char *buffer;
	A = (unsigned char ***) malloc (5*sizeof(unsigned char ***));

	for (int r = 0; r< 5; r++)
	{
			 A[r] = (unsigned char **) malloc(5*sizeof(unsigned char *));
			 for (int k = 0; k < 5; k++)
			 {
					 A[r][k] = (unsigned char *)malloc(64*sizeof(unsigned char));
			 }
	}
  buffer = (unsigned char *) malloc(200*sizeof(unsigned char));

  file = fopen("prueba","rb");   //-f nombrearchivo -d
  if (file==NULL)
  {
    fputs ("Error de archivo\n", stderr);
    exit(1);
  }

  printf("\n");
  while(end != 0)
  {
		end = fread(buffer,8,1,file);
		for (int h = 0; h<8; h++){
    	/*printf("%c",buffer[h]);*/
    	A[i][j][h] = buffer[h];

    	printf("\n");
	  }
    /*printf(sizeof(buffer));*/
		printf("%c",A[i][j][0]);
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
	 printf("\n");



   void free (void* buffer);
	 void free (void* A);
   return 0;
}
