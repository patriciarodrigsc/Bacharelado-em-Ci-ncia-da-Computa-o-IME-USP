//NUSP: 11315590
//Nome: Patricia da Silva Rodrigues
//Este ep calcula as raizes da função f(X) = e^x - 2x^2 atrazes do metodo de convergencia 
//e funções iterativas


#include <stdio.h>
#include <math.h>
#include <stdbool.h>


//Funcao G1
float G1(float x)
{
    return pow(exp(x)/2, 0.5);
}
//Funcao G2
float G2(float x)
{
   return -1 * pow(exp(x)/2, 0.5);

}
//Funcao G3
float G3(float x)
{
    return log(2 * pow(x,2));
}

//Vefirica se o modulo da diferenca entre xk e xk+1 é < EPSILON
bool criUm(float x,float y, float epsilon)
{
    if(fabs(y-x) < epsilon)
    {
        return true;
    }
        return false;
}
//Vefirica se o módulo de f(x_k+1) < EPSILON
bool criDois(float y, float epsilon)
{
    if(fabs(exp(y) - 2 * pow(y,2)) < epsilon)
    {
        return true;
    }
    return false;
}


int main()
{
    FILE *fArq;
    FILE *gArq;


//cria arquivo txt que armazena os valores da f(x) e da g(x)
//durante a iteração para que eu pudesse gerar o gráfico de convergencia
    fArq = fopen("Fexp.txt", "a"); 
    gArq = fopen("Gexp.txt","a");

    printf("f(X):");
    float f[100];
    float g[100];
    int i = 0;


    float candidata = 0;
    float x = 2;
    bool valorCriUm = false;
    bool valorCriDois= false;
    int iteracoes = 1;
    float raiz = 0;
    float epsilon = 0.001;

    //usando a f(x) = exp(x) - 2x² e a g1(x) = +sqrt((e^x)/2)
    printf("Função de iteração G1(X): ");

    while(valorCriUm == false || valorCriDois == false)
    {
        //aqui a variavel candidata a raiz (xk+1) recebe o valor da f(x) aplicada a xk
        candidata = G1(x);
        //aqui o programa testa o primeiro critério de parada |xk+1 - xk| < EPSILON
        valorCriUm = criUm(x,candidata, epsilon);
        //aqui o programa testa o segundo critério de parada |xk+1 - xk| < EPSILON
        valorCriDois = criDois(candidata, epsilon);
        //aqui o sistema printa o valor de xk e xk+1 para que possamos observar a aproximacao
        //entre eles
        printf("\n xAtual%f", x);
        printf("  candidata: %f", candidata);
        //aqui o sistema armazena os valores deles e forma uma lista txt
        fprintf(fArq, "%f \n", x);
        fprintf(gArq, "%f \n", candidata);

         //aqui o sistema verifica se os criterios foram atendidos
        if(valorCriUm == true && valorCriDois == true)
        {
            //caso tenham sido, o sistema armazena o valor da raiz e printa o resultado
            raiz = candidata;
            printf("\n\n Raiz 1: ");
            printf("%f", raiz);
            printf("\n\n Iterações necessárias:");
            printf("%d", iteracoes);
        }
        else
        {
            //caso nao tenha sido, o sistema alimenta a iteracao e 
            //tambem faz com que a xk = xk+1
            //ou seja, a xk+1 agora será o novo valor xk que será jogado na funcao
            //afim de gerar um novo valor xk+1
            iteracoes++;
            x = candidata;
        }

    }
    //fecha o arquivo.txt que armazenou os valores xk e xk+1 a cada iteracao
    fclose(fArq);
    fclose(gArq);

    //A seguir, a mesma coisa foi feita para as outras funcoes g(x)


    //usando a f(x) = exp(x) - 2x² e a g1(x) = -sqrt((e^x)/2)
    FILE *f2Arq;
    FILE *g2Arq;
    f2Arq = fopen("F2exp.txt", "a"); 
    g2Arq = fopen("G2exp.txt","a");

    candidata = 0;
    valorCriDois= false;
    valorCriUm = false;
    float x3 = 2;
    float raiz4 = 0;
    iteracoes = 1;
    i = 0;
    printf("\n\n Função de iteração G2(X): ");
    while(valorCriUm == false || valorCriDois == false)
    {
        i++;
        candidata = G2(x3);
        valorCriUm = criUm(x3,candidata, epsilon);
        valorCriDois = criDois(candidata, epsilon);
        printf("\n xAtual%f", x3);
        printf("  candidata: %f", candidata);
        fprintf(f2Arq, "%f \n", x3);
        fprintf(g2Arq, "%f \n", candidata);


        if(valorCriUm == true && valorCriDois == true)
        {
            raiz4 = candidata;
            printf("\n\n Raiz 4: ");
            printf("%f", raiz4);
            printf("\n\n Iterações necessárias:");
            printf("%d", iteracoes);
        }
        else
        {
            iteracoes++;
            x3 = candidata;
        }
    }

    fclose(f2Arq);
    fclose(g2Arq);
    //usando a f(x) = exp(x) - 2x², a g2(x) = ln(2x²) com x positivo

    FILE *f3Arq;
    FILE *g3Arq;
    
    candidata = 0;
    float x1 = 1;
    valorCriUm = false;
    valorCriDois= false;
    iteracoes = 1;
    float raiz1 = 0;

    f3Arq = fopen("F3exp.txt", "a"); 
    g3Arq = fopen("G3exp.txt","a");


    printf("\n\n Função de iteração G3(X): ");
    while(valorCriUm == false || valorCriDois == false)
    {
        candidata = G3(x1);
        valorCriUm = criUm(x1,candidata, epsilon);
        //printf(valorCriUm ? "true" : "false");
        valorCriDois = criDois(candidata, epsilon);
        //printf(valorCriDois ? "true" : "false");
        printf("\n xAtual%f", x1);
        printf("  candidata: %f", candidata);
        fprintf(f3Arq, "%f \n", x1);
        fprintf(g3Arq, "%f \n", candidata);


        if(valorCriUm == true && valorCriDois == true)
        {
            raiz1 = candidata;
            printf("\n\n Raiz 2: ");
            printf("%f", raiz1);
            printf("\n\n Iterações necessárias:");
            printf("%d", iteracoes);
        }
        else
        {
            iteracoes++;
            x1 = candidata;
        }
    }

    fclose(f3Arq);
    fclose(g3Arq);

    //usando a f(x) = exp(x) - 2x², a g2(x) = ln(2x²) com x negativo
    FILE *f4Arq;
    FILE *g4Arq;
    f4Arq = fopen("F4exp.txt", "a"); 
    g4Arq = fopen("G4exp.txt","a");

    candidata = 0;
    valorCriDois= false;
    valorCriUm = false;
    float x2 = -1;
    float raiz2 = 0;
    iteracoes = 1;

    printf("\n\n Função de iteração G3(X): ");
    while(valorCriUm == false || valorCriDois == false)
    {
        candidata = G3(x2);
        valorCriUm = criUm(x2,candidata, epsilon);
        valorCriDois = criDois(candidata, epsilon);
        printf("\n xAtual%f", x2);
        printf("  candidata: %f", candidata);
        fprintf(f4Arq, "%f \n", x2);
        fprintf(g4Arq, "%f \n", candidata);


        if(valorCriUm == true && valorCriDois == true)
        {
            raiz2 = candidata;
            printf("\n\n Raiz 3: ");
            printf("%f", raiz2);
            printf("\n\n Iterações necessárias:");
            printf("%d", iteracoes);
        }
        else
        {
            iteracoes++;
            x2 = candidata;
        }
    }

    fclose(f4Arq);
    fclose(g4Arq);



    return 0;
}
