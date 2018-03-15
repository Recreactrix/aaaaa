#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
int mod(int x, int y){
  	if(x<0){
		    x = x*-1;
  		  return (y-(x%y))%y;
            }
    else{
    	  return (x%y);
        }
}
int main(){
	int flag = 1;
	int A[63];
	int a = 1;
	int i;
	int j;
	int x;
	int y;
	int z;

	FILE *file;

	unsigned char **C;
	unsigned char ***S;
	unsigned char ***S1;
	unsigned char ***S2;
	unsigned char ***S3;
	unsigned char ***S4;
	unsigned char **D;
	uint64_t *N;
	uint64_t **Aaux;
	S = (unsigned char ***) malloc (5*sizeof(unsigned char ***));

	for (int r = 0; r< 5; r++)
	{
			 S[r] = (unsigned char **) malloc(5*sizeof(unsigned char *));
			 for (int k = 0; k < 5; k++)
			 {
					 S[r][k] = (unsigned char *)malloc(64*sizeof(unsigned char));
			 }
	}
	C = (unsigned char **) malloc(5*sizeof(unsigned char *));
	for (int k1 = 0; k1 < 5; k1++)
	{
			C[k1] = (unsigned char *)malloc(64*sizeof(unsigned char));
	}
	D = (unsigned char **) malloc(5*sizeof(unsigned char *));
	for (int k1 = 0; k1 < 5; k1++)
	{
			D[k1] = (unsigned char *)malloc(64*sizeof(unsigned char));
	}
	unsigned char *buffer = (unsigned char *) malloc (8*sizeof (unsigned char));


	S1 = S;
	S2 = S;
	S3 = S;
	S4 = S;

	file = fopen("prueba","rb");   //-f nombrearchivo -d
	if (file==NULL)
	{
		fputs ("Error de archivo\n", stderr);
		exit(1);
	}


	for(int h=0; h<8; h++){
		fread(buffer,8,1,file);
		A[0+8*h] = 0b0001 & buffer[h];
		A[1+8*h] = 0b0010 & buffer[h];
		A[2+8*h] = 0b0011 & buffer[h];
		A[3+8*h] = 0b0100 & buffer[h];
		A[4+8*h] = 0b0101 & buffer[h];
		A[5+8*h] = 0b0110 & buffer[h];
		A[6+8*h] = 0b0111 & buffer[h];
		A[7+8*h] = 0b1000 & buffer[h];
		}
		while (a != 0){
			for (int j = 0; j<5; j++){
				for (int i = 0; i<5; i++){
					if (i == 2 & j == 3){
						a = 0;
						break;
					}
					else{
						for (int k = 0; k<64; k++){
							S[i][j][k] = A[k];
						}
					}
				}
				if (i == 2 & j == 3){
					a = 0;
					break;
				}
			}
		}
		for(int j = 3; j < 4; j++ ){
			for (int i = 2; i < 5; i++) {
				for (int k = 0; k < 64; k++) {
						S[i][j][k] = 0;
				}
			}
		}
		for(int j = 4; j < 5; j++ ){
			for (int i = 0; i < 5; i++) {
				for (int k = 0; k < 64; k++) {
						S[i][j][k] = 0;

				}
			}
		}

	for (int k = 0; k < 64; k++) {
		printf("%d",S[0][0][k]);
	}


//Especificacion Theta

	for(x = 0;x<5;x++){
		for (z = 0; z < 64; z++) {
				C[x][z] = S[x][0][z]^S[x][1][z]^S[x][2][z]^S[x][3][z]^S[x][4][z];
		}
	}
	for(x = 0;x<5;x++){
		for (z = 0; z < 64; z++) {
				D[x][z] = C[mod((x-1),5)][z]^C[mod((x+1),5)][mod((z-1),64)];
		}
	}
	for(x = 0;x<5;x++){
		for (y = 0; y < 5; y++) {
			for (z = 0; z < 64; z++) {
					S1 [x][y][z] = S[x][y][z] ^ D[x][z];
			}
		}
	}
//Especificacion Rho
for (z = 0; z < 64; z++) {
		S2 [0][0][z] = S1[0][0][z] ;
}
x= 1;y=0;
for (int t = 0; t <24; t++) {
	for (z = 0; z < 64; z++) {
			S2 [x][y][z] = S1[x][y][mod((z-((t+1)*(t+2))/2),64)];
	}
	x = y;
	y = mod((2*x+3*y),5);
	}
//Especificacion Pi
for(x = 0;x<5;x++){
	for (y = 0; y < 5; y++) {
		for (z = 0; z < 64; z++) {
				S3 [x][y][z] = S2[mod((x+3*y),5)][x][z] ;
		}
	}
}
//Especificacion L
for(x = 0;x<5;x++){
	for (y = 0; y < 5; y++) {
		for (z = 0; z < 64; z++) {
				S4 [x][y][z] = S3 [x][y][z] ^( S3 [mod((x+1),5)][y][z] & S3 [mod((x+2),5)][y][z] ) ;
				printf("%x", S4[x][y][z]);
		}
	}
}
//Falta la ultima







	printf("\n");
	void free (void* y);
	void free (void* S);
	return 0;

}
