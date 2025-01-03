//NUSP: 11315590
//Nome: Patricia da Silva Rodrigues
//ESTE EP GERA O fRACTAL DE NEWTON ATRAVES DA BACIA DE CONVERGENCIA
#include<graphics.h>
#include<math.h>
#include<iostream>
#include<stdio.h>
#include <fstream>


using namespace std;

#define TAU 6.283185307

//Para que possamos fazer operacoes com numeros complexos, e importante
//definir as operacoes basicas dos numeros complexos. A classe complexos faz isso.
class complexo {
public:
	float real, imag;
    complexo(float r = 0, float i =0)  
	{
		real = r;
		imag = i;
	}
    complexo operator + (complexo const &obj) 
	{
         complexo res;
         res.real = real + obj.real;
         res.imag = imag + obj.imag;
         return res;
    }
    complexo operator - (complexo const &obj) 
	{
         complexo res;
         res.real = real - obj.real;
         res.imag = imag - obj.imag;
         return res;
    }
    complexo operator * (complexo const &obj) 
	{
         complexo res;
         res.real = real*obj.real - imag*obj.imag;
         res.imag = real*obj.imag + imag*obj.real;
         return res;
    }
    complexo operator / (complexo const &obj) 
	{
         complexo res;
         res.real = (real*obj.real + imag*obj.imag) / (obj.real*obj.real + obj.imag*obj.imag);
         res.imag = (-real*obj.imag + imag*obj.real) / (obj.real*obj.real + obj.imag*obj.imag);
         return res;
    }
};

//algumas funcoes tambem serao usadas

//a funcao abs retorna o a raiz quadrada do numero real z ao quadrado
float abs(complexo z)
{
	return sqrt(z.real*z.real+z.imag*z.imag);
}

//arctangente de z
float arg(complexo z)
{
	return atan2(z.imag,z.real);
}
//retorna o numero complexo z elevado a um n
complexo pow(complexo z, int n)
{
	int i;
	complexo z1=complexo(1,0);
	for(i=0;i<n;i++)
		z1=z1*z;
	return z1;	
}

//Funcao  define a funcao f formada no campo complexo
//O numero escolhido aqui ira selecionar qual função será processada
complexo evalf(complexo z, int v)
{
	if(v == 1)
	{
		return pow(z,3) - 1;
	}
	if(v == 2)
	{
		return pow(z,4) - z*2 - 1;
	}
	if(v == 3)
	{
		return pow(z,3)- 6;
	}
	if(v == 4)
	{
		return pow(z,4)*2 + 1;
	}
	if(v == 5)
	{
		return pow(z, 3) + pow(z,2) + 1;
	}
}
//Funcao  define a derivada da f formada no campo complexo
//O numero escolhido aqui ira selecionar qual derivada será processada
complexo evalDf(complexo z, int v)
{
	if(v == 1)
	{
		return pow(z,2)*2;
	}
	if(v == 2)
	{
		return z*z*z*4 - 2;
	}
	if(v == 3)
	{
		return z*z*3;
	}
	if(v == 4)
	{
		return z*z*z*8;
	}
	if(v == 5)
	{
		return z*z*3 + z*2;
	}
}

//Cria um arquivo com os pontos que geram as bacias de convergência
void newton_basins (float l[],float u[],FILE * arq2, int v)
{
	float iter = 100;
	int shift = 5, gd,gm;
	float tol = 0.000001;

	
	complexo z;
	//O número complexo z recebera um ponto do domínio
	//[l1 , u1 ] × [l2 , u2]
	z = complexo(u[0] + l[0],-u[1]+ l[1]);
	int k = 0;
	for(k=0;k<iter;k++)
	{
		//Agora alguns critérios de convergência terão que ser
		//analisados. Para isso, usaremos o algoritimo de parada

		// |f(z)| < tol.Caso atenda, ela parara de
		//convergir e isso significará que z e uma raiz
		if(abs(evalf(z, v)) < tol)
			break;

		z=z-evalf(z, v)/evalDf(z, v);
	}
	//apos acharmos a raiz ela sera associada a uma cor especifica
	//e em seguida preenchera o pixel da imagem
	if(k!=iter)
	{
		//armazena a coordenada no campo complexo no arquivo de texto 
		//output.txt que contera as coordenadas usadas para a geracao
		//do fractal
		fprintf(arq2, "%f    ", z.real);
	    fprintf(arq2, "%f \n", z.imag);
		
		//no caso do fractal gerado por iteracao, k (somatorio) sera associado ao pixel referido na funcao putpixel
		//putpixel(u[0]/(4.0/600),u[1]/(4.0/600),1+(k+shift)%14);

		//a funcao arc(z) sera associar ao pixel referido na funcao putpixel
		putpixel(u[0]/(4.0/600),u[1]/(4.0/600),1+int(shift+tol+(arg(z)*14/TAU+8))%14);
	}
}


int main()
{
	int v = 0;
	printf("Digite qual função você deseja ver:\n");

	printf("1 : z^2 - 2 \n");
	printf("2:  z^4 - 2*z - 1 \n");
	printf("3:  2*z^3 \n");
	printf("4:  2z^4 + 1 \n");
	printf("5:  z^3 + z^2 + 1 \n");

	std::cin >> v;
	


	float u[2];
	float l[2];
	l[0] = -2;
	l[1] = 2;

	//criando o arquivo que armazenada os pontos da bacia de convergencia
	FILE *arq2;
	arq2 = fopen("output.txt","wt");

	int i,j,gd,gm;
	float tol=0.000001;
	
	complexo z;
	detectgraph(&gd,&gm);
	initgraph(&gd,&gm,NULL);
	delay(2000);
	for(i=0;i<=1000;i++)
	{
		for(j=0;j<=600;j++)
		{
			float tol=0.000001;
			//dado um campo de dimensões 1000 x 600 associaremos cada coordenada a u
			u[0] = i * 4.0/600;
			u[1] = j * 4.0/600;
			newton_basins(l,u, arq2, v);
		}
	}

	fclose(arq2);

	return 0;
}

