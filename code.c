#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

/*h2b (*char H , int n){
	for(int h = 0; h<8; h++){
		a
	}
{*/



int main(/* int argc, const char* argv[] */)
{
	int flag = 1;
  	int end ;
	int l;
	int r = 0;
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
  	unsigned char *buffer;
	char cadena [1600] = {0}; 
	int F = 0xA1;
	int h0, position;
	int nro = 0;
	int binario = 0;

	buffer = (unsigned char *) malloc(1600*sizeof(unsigned char));
	file = fopen("prueba","rb");   //-f nombrearchivo -d
	if (file==NULL)
	{
		fputs ("Error de archivo\n", stderr);
		exit(1);
	}

	printf("\n");
	while(!feof(file))
	{	
	
		//cadena = buffer[h] & 0x000000000000000F;
		fgets(buffer, 1600, file);
		printf("%c", buffer[3]);
		printf("\n");
		/*nro = 31;
		position = 1;
		while(nro > 0){
			binario = binario + (nro%2)*position;
			nro /=2;
			position *= 10;
		}
		printf("%d", binario);*/
	}
		
	
	
	printf("\n");

	void free (void* buffer);
	return 0;
}	
