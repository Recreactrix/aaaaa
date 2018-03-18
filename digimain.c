#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

unsigned char *padding(int x, int m){

	int j = modulo((-m-2),x);
	char P[j+2];
	P[0] = 1;
	for(int i = 1; i<j+1; i++)
	{
		P[i] = 0;
	}
	P[j+1] = 1;
	return P;
}
unsigned char *sponge  (uint64_t *N, int d, int r){

	uint64_t P[1080];
	uint64_t Paux2[1600] = {0};
	int a = strlen(N);
	padding(r, a);
	uint64_t *Paux = (uint64_t*) malloc(strlen(padding(r, a))*sizeof(uint64_t));
	Paux = padding (r,a);
	int i;
	for(i = 0; i<a; i++)
	{
		P[i] = N[i];
	}
	int y;
	for(y = a; y<1080; y++)
	{
		P[y] = Paux[y-a];     //Matriz con el mensaje y el padding realizado
	}
	for(y = 0; y < 1080; y++)
	{
		Paux2[y] = P[y];  //Matriz con la informacion de P y 512 ceros
	}
	int n = strlen(P)/r;
	int b = 1600;
	int c = b-r;
	char S[b] = {'0'};
	char Saux[b] = {'0'};
	int u;
	for(u = 0; u<n; u++)
	{
		Saux[i] = S[i] ^ Paux2[i];
	}
	return Saux;
}


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
	if(x<0)
	{
		x = x*-1;
		return (y-(x%y))%y;
	}
	else
	{
		return (x%y);
	}
}


void theta(uint64_t **A,uint64_t **Aaux,uint64_t *C,uint64_t *D)
{

	uint64_t temp;int i,j,k,l;

	for (i=0;i<5;i++)
	{
		C[i] =  A[i][0] ^ A[i][1] ^ A[i][2] ^ A[i][3] ^ A[i][4];
	}
	for (j = 0;j<5;j++)
	{
		temp = (C[modulo(j+1,5)] ) << 63 | (C[modulo(j+1,5)]  >> 1);
		D[j] = C[modulo(j-1,5)] ^ temp;
	}
	for (k = 0;j<5;j++)
	{
		for(l=0;l<5;l++)
		{
			Aaux[k][l]=A[k][l] ^ D[k];
		}
	}
	
}

void rho(uint64_t **A,uint64_t **Aaux){

	A[0][0]=Aaux[0][0];
	int x=1;
	int y=0;
	int t;

	for(t=0;t<24;t++)
	{
		A[x][y] = Aaux[x][y] >> modulo(-(t+1)*(t+2)/2,64) | Aaux[x][y]<< ( 64 - modulo(-(t+1)*(t+2)/2,64) );
		x = y;
		y = modulo((2*x + 3*y),5);
	}
}

void pi(uint64_t **A,uint64_t **Aaux){
	int i,j;
	for (i = 0; i<5; i++) {
		for(j = 0;j<5;j++){
			Aaux[i][j]=A[modulo(i+3*j,5)][i];
		}
	}
}

void xci(uint64_t **A,uint64_t **Aaux){
	uint64_t uno =1;int i;int j;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			A[i][j]= Aaux[i][j] ^ ( (Aaux[modulo(i+1,5)][j] ^ uno) & Aaux[modulo(i+2,5)][j]);
		}
	}
}

uint64_t rc(int t){
	uint64_t ansuint;
	unsigned char ans;
	unsigned char * R= malloc(8*sizeof(unsigned char));
	unsigned char * R9= malloc(9*sizeof(unsigned char));
	int i;int j;int k; int l;
	R[0]='1';
	for(i=1;i<8;i++)
	{
		R[i]='0';
	}
	if(mod(t,255)==1)
	{
		free(R);
		free(R9);
		ansuint = 1;
		return ansuint;
	}
	else
	{
		for(i =1;i<mod(t,255);i++)
		{
			R9[0]='0';for(j=0;j<8;j++){R9[j+1]=R[j];}

			R9[0]= R9[0] ^ R9[8];
			R9[4] = R9[4] ^ R9[8];
			R9[5] = R9[5] ^ R9[8];
			R9[6] = R9[6] ^ R9[8];

			for(k=0;k<8;k++)
			{
				R[k]=R9[k];
			}

			ans=R[0];
			free(R);
			free(R9);
			if(ans=='1')
			{
				ansuint = 1;
				return ansuint;
			}
		 	else
			{
				ansuint = 0;
				return ansuint;
			}
		}
	}
}

void iota(uint64_t **A , int ir){
	int j,x;
	uint64_t *RC; = malloc(sizeof(uint64_t));
	for(j=0;j<7;j++)
	{
		if( (int) ((pow(2,j)-1) ) == 0)
		{
			if ( rc(j)== 0x0000000000000001ULL )
			{
	  			RC =( (RC >> 63) | 0x0000000000000001ULL ) << 63 | RC;
			}
			else
			{
				RC = (RC<<1)>>1;
			}
		}

		else if( (int) ((pow(2,j)-1) ) == 1   )
		{
			if ( rc(j)== 0x0000000000000001ULL )
			{
				RC = RC | ~(0xBFFFFFFFFFFFFFFFULL); //Una or 0x0000000000000001ULL<<(2^j-1)
			}
			else
			{
				RC = RC & (0xBFFFFFFFFFFFFFFFULL);
			}
		}

		else if( (int) ((pow(2,j)-1) ) == 3   )
		{
			if ( rc(j)== 0x0000000000000001ULL )
			{
			  RC = RC | ~(0xEFFFFFFFFFFFFFFFULL);
			}
			else
			{
			  RC = RC & 0xEFFFFFFFFFFFFFFFULL;
			}
		}
		else if( (int) ((pow(2,j)-1) ) == 7   )
		{
			if ( rc(j)== 0x0000000000000001ULL )
			{
				RC = RC | ~(0xFEFFFFFFFFFFFFFFULL);
			}
			else
			{
				 RC = RC & 0xFEFFFFFFFFFFFFFFULL;
			}
		}
		else if( (int) ((pow(2,j)-1) ) == 15)
		{
			if ( rc(j)== 0x0000000000000001ULL )
			{
				RC = RC | ~(0xFFFEFFFFFFFFFFFFULL);
			}
			else
			{
				RC = RC & 0xFFFEFFFFFFFFFFFFULL;
			}
		}
		else if ( (int) ((pow(2,j)-1) ) == 31   )
		{
			if ( rc(j)== 0x0000000000000001ULL ){
				RC = RC | ~(0xFFFFFFFEFFFFFFFFULL);
			}
			else{
				RC = RC & 0xFFFFFFFEFFFFFFFFULL;
			}
		}
		else
		{
			if ( rc(j)== 0x0000000000000001ULL )
			{
				RC = RC | ~(0xFFFFFFFFFFFFFFFEULL);
			}
			else{
				RC = RC & 0xFFFFFFFFFFFFFFFEULL;
			}
		}

	}
	for(x=0;x<5;x++)
	{
		Aaux[0][0]=A[0][0] ^ RC ;
	}
}
void RND(uint64_t **A,uint64_t **Aaux,uint64_t *C,uint64_t *D){
	theta(A,Aux,C,D);
	rho(A, Aux);
	pi(A,Aux);
	xci(A,Aux);
	iota(A);
	
}


int main(/* int argc, const char* argv[] */)
{
	int flag;
  	int end;
	int l;
	int r;
	int b = 1600;
	int w = b/25;
	int i = 0;
	int j = 0;
	int h = 0;
	int hc = 0;
	int y = 0;
 	int by = 0;
  	int p = 0;
  	int to = 0;
	int bloque;



	FILE *file;
	uint64_t **A;
  	uint64_t **C;
  	uint64_t **D;
	uint64_t *N;
  	uint64_t **Aaux;



	A = (uint64_t **) malloc(5* sizeof(uint64_t *));      //Matriz antes de Theta

	for (r = 0; r<5;r++)
	{
	    A[r] = (uint64_t *) malloc(sizeof(uint64_t)*5);
	}

	Aaux = (uint64_t **) malloc(5* sizeof(uint64_t*));      //Matriz auxiliar de A

	for (r = 0; r<5;r++)
	{
		Aaux[r] = (uint64_t *) malloc(sizeof(uint64_t)*5);
	}


	//C = (uint64_t *) malloc(5* sizeof(uint64_t));      //Matriz C antes de Theta
	//D = (uint64_t *) malloc(5* sizeof(uint64_t));      //Matriz  Dantes de Theta

	uint64_t *buffer,Zeros;
	buffer = (uint64_t *) malloc(25*sizeof(uint64_t));
	Zeros = 0;
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
	by= ((to*8)%64)/8;
	rewind(file);
	printf("%d", p);
	printf("%d", by);
	}

	while(!feof(file))
	{	
		hc = 0;
		for(bloque = 0; bloque<p; bloque++){
			h = 0; j = 2; i = 2; flag = 0;
		        fread(buffer,8,17,file);
			printf("\n");
			while(h<17){
				A[i][j] = buffer [hc] ;
				flag = flag+1;
				printf("%lu", A[i][j]);
				if(i >= 4)
				{
					i = 0;
				}
				else {
					i = i+1;
				}
				if((flag+1)%5 == 0 && flag != 0)
				{
					if(j==0)
					{
						j = 4;
					}
					else{
						j = j-1;
					}
				}
				printf("\n");
				h = h+1;
				hc = hc+1;
			}

			while(h< 24){
				A[i][j] = 0;
				flag = flag+1;
				printf("%lu", A[i][j]);
				if(i >= 4)
				{
					i = 0;
				}
				else {
					i = i+1;
				}
				if((flag+1)%5 == 0 && flag != 0 && flag !=24)
				{	
					if(j==0)
					{
						j = 4;
					}
					else{
						j = j-1;
					}
				}
				printf("\n");
				h = h+1;
				hc = hc+1;
			}
			void free (void* A);
			printf("\n");		
		}

	}
  	/*A = (unsigned char ***) malloc (5*sizeof(unsigned char ***));

	for (int i = 0; i< 5; i++)
	{
			 A[i] = (unsigned char **) malloc(5*sizeof(unsigned char *));
			 for (int j = 0; j < 5; j++)
			 {
					 A[i][j] = (unsigned char *)malloc(w*sizeof(unsigned char));
			 }
	}*/
 /* if (p%17 == 0){

    //Bloque completo
    sponge(N,20,1080)
  }
  else{
    //Se necesita padding pero a la funcion que se le realizara padding
    //sera N || 1111, esta se ingresara a la funcion padding

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
