#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

int main(int argc, char *argv[]){
 // Bandera para saber si no se puede extraer un byte
	int flag = 1;
 // Buffer tipo int
	int B[64] = {0};
//bandera para llenar ceros
	int a = 1;
//Contadores IOTA
  	int r;int k;int k1;int k2;int h; int i; int j; int l; int to; int b;int p;
//puntero a file
	FILE *file;
  //MATRICES AUXILIARES
	unsigned char **C;
	unsigned char ***A;
	unsigned char ***A1;
	unsigned char ***A2;
	unsigned char ***A3;
	unsigned char ***A4;
  	unsigned char ***A5;
	unsigned char **D;
  //////////////////////
  //Inicializar las matrices 3D
	A = (unsigned char ***) malloc (5*sizeof(unsigned char ***));

	for (r = 0; r< 5; r++)
	{
			 A[r] = (unsigned char **) malloc(5*sizeof(unsigned char *));
			 for (k = 0; k < 5; k++)
			 {
					 A[r][k] = (unsigned char *)malloc(64*sizeof(unsigned char));
			 }
	}
  //Inicializar las matrices 2D
	C = (unsigned char **) malloc(5*sizeof(unsigned char *));

	for (k1 = 0; k1 < 5; k1++)
	{
			C[k1] = (unsigned char *)malloc(64*sizeof(unsigned char));
	}

	D = (unsigned char **) malloc(5*sizeof(unsigned char *));

	for (k2 = 0; k2 < 5; k2++)
	{
			D[k2] = (unsigned char *)malloc(64*sizeof(unsigned char));
	}

	unsigned char *buffer = (unsigned char *) malloc (8*sizeof (unsigned char));

 //////////////////////////


	file = fopen("da","rb");   //-f nombrearchivo -d
	if (file==NULL)
	{
		fputs ("Error de archivo\n", stderr);
		exit(1);
	}
	if(file!=NULL){

        	fseek(file,0,SEEK_END);     
        	to=ftell(file);              
      
        	p= 8*to/64;                 
		b= ((to*8)%64)/8;
        	rewind(file); 
	}

	for(h=0; h<8; h++){

		fread(buffer,8,1,file);
		S[0+8*h] = 0b0001 & buffer[h];
		S[1+8*h] = 0b0010 & buffer[h];
		S[2+8*h] = 0b0011 & buffer[h];
		S[3+8*h] = 0b0100 & buffer[h];
		S[4+8*h] = 0b0101 & buffer[h];
		S[5+8*h] = 0b0110 & buffer[h];
		S[6+8*h] = 0b0111 & buffer[h];
		S[7+8*h] = 0b1000 & buffer[h];
	}

	
	printf("%d" , p); //Numero de elementos o bloques de 64 bits que se tienen
	printf ("\n");
	printf("%d" , b);//Numero de elementos de 8 bits
	printf ("\n");
//LECTURA DEL ARCHIVO
//Padding si es necesario
	for(int e = 0; e < p ; e++){
		while (a != 0){
			for (j = 0; j<5; j++){
				for (i = 0; i<5; i++){
					if (i == 2 & j == 3){
						a = 0;
						break;
					}
					else{
						for (k = 0; k<64; k++){
							A[i][j][k] = S[k];
						}
					}
				}
				if (i == 2 & j == 3){
					a = 0;
					break;
				}
			}
		}
//COLUMNAS Y FILAS FALTANTES
		for(j = 3; j < 4; j++ ){
			for (i = 2; i < 5; i++) {
				for (k = 0; k < 64; k++) {
						A[i][j][k] = 0;
				}
			}
		}
		for(j = 4; j < 5; j++ ){
			for (i = 0; i < 5; i++) {
				for (k = 0; k < 64; k++) {
						A[i][j][k] = 0;

				}
			}
		}
/////////////////////////////
	

	}
	for(int q = 0; q<b ; q++){
		
	
	
	
	
	}
	printf("\n");
	free(buffer);




	return 0;

}

int mod(int x, int y){
  	if(x<0){
		    x = x*-1;
  		  return (y-(x%y))%y;
            }
    else{
    	  return (x%y);
        }
}

unsigned char rc(int t){
	unsigned char ans;
	unsigned char * R= malloc(8*sizeof(unsigned char));
	unsigned char * R9= malloc(9*sizeof(unsigned char));
	int i;int j;int k; int l;
	R[0]='1';for(i=1;i<8;i++){
	R[i]='0';}
	if(mod(t,255)==1){
    	free(R);
    	free(R9);
	return '1';
}
	else{
	for(i =1;i<mod(t,255);i++){
		R9[0]='0';for(j=0;j<8;j++){R9[j+1]=R[j];}

		R9[0] = R9[0] ^ R9[8];
		R9[4] = R9[4] ^ R9[8];
		R9[5] = R9[5] ^ R9[8];
		R9[6] = R9[6] ^ R9[8];

		for(k=0;k<8;k++){
		R[k]=R9[k];}

  ans=R[0];
  free(R);
  free(R9);

  return ans;
}}}

void iota( unsigned char ***A4, int ir){
  int j; int k;int n;int f;
  unsigned char * RC= malloc(64*sizeof(unsigned char));
  for(k=0;k<64;k++){
    RC[k]='0';
  }
  for(j=0;j<6;j++){
    RC[(int)pow(2,j)-1]=rc(j+7*ir);
  }
  for(n=0;n<64;n++){
    A5[0][0][n]=A4[0][0][n] ^ RC[n];
  }
  free(RC);
}
void x(unsigned char ***A4, unsigned char ***A3){
  int x;int y;int z;
  for(x = 0;x<5;x++){
  	for (y = 0; y < 5; y++) {
  		for (z = 0; z < 64; z++) {
  				A4 [x][y][z] = A3 [x][y][z] ^( A3 [mod((x+1),5)][y][z] & A3 [mod((x+2),5)][y][z] ) ;

  		}
  	}
  }
}
void pi(unsigned char ***A3, unsigned char ***A2){
  int x; int y; int z;
  for(x = 0;x<5;x++){
  	for (y = 0; y < 5; y++) {
  		for (z = 0; z < 64; z++) {
  				A3 [x][y][z] = A2[mod((x+3*y),5)][x][z] ;
  		}
  	}
  }
}

void ro(unsigned char ***S2, unsigned char ***S1){
  int z; int i; int t; int y; int x;
  for (z = 0; z < 64; z++) {
  		A2 [0][0][z] = A1[0][0][z] ;
  }
  x= 1;y=0;
  for (int t = 0; t <24; t++) {
  	for (z = 0; z < 64; z++) {
  			A2 [x][y][z] = A1[x][y][mod((z-((t+1)*(t+2))/2),64)];
  	}
  	x = y;
  	y = mod((2*x+3*y),5);
  	}
}

void theta(unsigned char ***A1, unsigned char ***A, unsigned char **C, unsigned char **D){
  int x; int y; int z;
  for(x = 0;x<5;x++){
		for (z = 0; z < 64; z++) {
				C[x][z] = A[x][0][z]^S[x][1][z]^A[x][2][z]^A[x][3][z]^A[x][4][z];
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
					A1 [x][y][z] = A[x][y][z] ^ D[x][z];
			}
		}
	}
}
unsigned char * pad(x,m){
	
	j = modulo((-m-2),x);
	unsigned char * P = malloc ((j+2)*sizeof(unsigned char))
	for (l = 1;l<j-1;l++){
		P [j] = 0; 
	}
	P[0] = 1;
	P[j-1] = 1;
	return *P;
}
unsigned char * keccak-p(unsigned char *S , int nr ){
	int b  = countof(S);
	int j; int i; int a; int k;
	int w = 64; // No estoy seguro de esta
	int l = log10 (w)/log10(2); // Log2 (w)
	for (j = 0; j<5; j++){
				for (i = 0; i<5; i++){
					if (i == 2 & j == 3){
						a = 0;
						break;
					}
					else{
						for (k = 0; k<64; k++){
							A[i][j][k] = S[k];
						}
					}
				}
				if (i == 2 & j == 3){
					a = 0;
					break;
				}
			}
		}
//COLUMNAS Y FILAS FALTANTES
		for(j = 3; j < 4; j++ ){
			for (i = 2; i < 5; i++) {
				for (k = 0; k < 64; k++) {
						A[i][j][k] = 0;
				}
			}
		}
		for(j = 4; j < 5; j++ ){
			for (i = 0; i < 5; i++) {
				for (k = 0; k < 64; k++) {
						A[i][j][k] = 0;

				}
			}
		}
	for (ir = 12 + 2*l- nr; ir <  12+2*l - 1; ir++){
		A = iota(x(pi(theta(A))), ir);
	}
	/*Convertir A a un string S*/
}
//nr = 24 eso es fijo dijo el profesor
