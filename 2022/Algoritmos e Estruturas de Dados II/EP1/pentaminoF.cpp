#include <iostream>
#include "pilha.h"
#include <stdlib.h>



using namespace std;

typedef struct
{
    int code;
    char** valor;
    int n;
    int m;
} tipoLetra;

//essa funçao cria uma letra nova a partir dos parametros de dimensão e do codigo da letra
char** criaLetra(int letra,int n,int m)
{
    //definindo a letra F
    int i = 0;
    int j = 0;

    char **Le;


    Le = (char **)malloc(n * sizeof(char *));

    for(i = 0; i < n; i++)
    {
        Le[i] = (char *)malloc(m * sizeof(char));
    }

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            Le[i][j] = '*';
        }
    }


    if(letra == 1)
    {
        return Le;

    }
    if(letra == 2)
    {
        Le[0][1] = 'F';
        Le[0][2] = 'F';
        Le[1][0] = 'F';
        Le[1][1] = 'F';
        Le[2][1] = 'F';
        return Le;
    }

    if(letra == 3)
    {
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < m; j++)
            {
                Le[i][j] = 'I';
            }
        }
    }


    if(letra == 4)
    {
        
        Le[0][0] = 'L';
        Le[1][0] = 'L';
        Le[2][0] = 'L';
        Le[3][0] = 'L';
        Le[3][1] = 'L';
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < m; j++)
            {
                cout<<Le[i][j];
            }
            printf("\n");
        }

        return Le;
    }

    if(letra == 5)
    {
        Le[0][1] = 'N';
        Le[1][1] = 'N';
        Le[2][1] = 'N';
        Le[2][0] = 'N';
        Le[3][0] = 'N';

        return Le;
    }

    if(letra == 6)
    {


        Le[0][0] = 'P';
        Le[0][1] = 'P';
        Le[1][0] = 'P';
        Le[1][1] = 'P';
        Le[2][0] = 'P';

        return Le;
    }
    if(letra == 7)
    {

        Le[0][0] = 'T';
        Le[0][1] = 'T';
        Le[0][2] = 'T';
        Le[1][1] = 'T';
        Le[2][1] = 'T';
        return Le;
    }

    if(letra == 8)
    {
        Le[0][0] = 'U';
        Le[0][2] = 'U';
        Le[1][0] = 'U';
        Le[1][1] = 'U';
        Le[1][2] = 'U';

        return Le;
    }

    if(letra == 9)
    {
        Le[0][0] = 'V';
        Le[1][0] = 'V';
        Le[2][0] = 'V';
        Le[2][1] = 'V';
        Le[2][2] = 'V';

        return Le;
    }

    if(letra == 10)
    {


    Le[0][2] = 'W';
    Le[1][1] = 'W';
    Le[1][2] = 'W';
    Le[2][0] = 'W';
    Le[2][1] = 'W';

    return Le;
    }

    if(letra == 11)
    {
        Le[0][1] = 'X';
        Le[1][0] = 'X';
        Le[1][1] = 'X';
        Le[1][2] = 'X';
        Le[2][1] = 'X';

        return Le;
    }


    if(letra == 12)
    {


        Le[0][0] = 'Y';
        Le[1][0] = 'Y';
        Le[1][1] = 'Y';
        Le[2][0] = 'Y';
        Le[3][0] = 'Y';

        return Le;
    }

    if(letra == 13)
    {
        Le[0][0] = 'Z';
        Le[0][1] = 'Z';
        Le[1][1] = 'Z';
        Le[2][1] = 'Z';
        Le[2][2] = 'Z';

        return Le;
    }
    return NULL;
}

//essa função gira a letra para a orientação desejada
char** giraPeca(char** peca,int n, int m, int oriente)
{
    int i = 0;
    int j = 0;
    
    char **PecaVirada;
    
    PecaVirada = (char **)malloc(n * sizeof(char *));

    for(i = 0; i < n; i++)
    {
        PecaVirada[i] = (char *)malloc(m * sizeof(char));
    }

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            PecaVirada[i][j] = '*';
        }
    }

    //orientacao 0
    if(oriente == 0)
    {
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < m; j++)
            {
                PecaVirada[i][j] = peca[i][j];
            }
        }
        return PecaVirada;
    }    
    //orientacao 1
    if(oriente == 1)
    {
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < m; j++)
            {
                PecaVirada[j][n-i-1] = peca[i][j];
            }
        }
        return PecaVirada;
    }

    //orientacao 2
    if(oriente == 2)
    {
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < m; j++)
            {
                PecaVirada[n-i-1][m-j-1] = peca[i][j];
            }
        }
        return PecaVirada;
    }

    //orientacao 3
    if(oriente == 3)
    {
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < m; j++)
            {
                PecaVirada[i][m-j-1] = peca[i][j];
            }
        }
        return PecaVirada;
    }
    return NULL;
}

//caso seja a primeira peça, o código fara com que ela gire até se posicionar de modo a não deixar buraco no restante do tabuleiro
bool encaixaPrimeira(char** tabuleiro, int nT, int mT, char** peca, int nP, int mP, Pilha pilha, tipoLetra * vetorLetras)
{
    int aux;
    bool verifica;
    pilha.push(vetorLetras[0]);
    char** pecaGirada;
    if(nP <= mP)
    {
        pecaGirada = giraPeca(peca,nT,mT,1);
        aux = vetorLetras->m;
        vetorLetras->m = vetorLetras->n;
        vetorLetras->n = aux;
       verifica  = encaixou(tabuleiro,nT,mT,pecaGirada,nP,mP,pilha, vetorLetras);
       if(verifica == true)
       {
           return true;
       }
       else
       {
            pecaGirada = giraPeca(peca,nT,mT,3);
            aux = vetorLetras->m;
            vetorLetras->m = vetorLetras->n;
            vetorLetras->n = aux;

            verifica = encaixou(tabuleiro,nT,mT,pecaGirada,nP,mP,pilha, vetorLetras);
            if(verifica == true)
            {
                return true;
            }
            else
            {
                return false;
            }
       }
    }
    else
    {
        pecaGirada = giraPeca(peca,nT,mT,0);

       verifica = encaixou(tabuleiro,nT,mT,pecaGirada,nP,mP,pilha, vetorLetras);
       if(verifica == true)
       {
           return true;
       }
       else
       {
            pecaGirada = giraPeca(peca,nT,mT,2);

            verifica = pecaGirada = encaixou(tabuleiro,nT,mT,pecaGirada,nP,mP,pilha, vetorLetras);
            if(verifica == true)
            {
                return true;
            }
            else
            {
                return false;
            }
       }
    }
}

//essa função vericará se, alpem da primeira coluna da peça não conforntar com o tabueiro, se o restante também não confrontará
bool verificaResto(char** tabuleiro, int nT, int mT, char** peca,int nP, int mP,int lT, int cT)
{
    int i = 0;
    int j = 0;

    for(i = 0, i < nP, i++)
    {
        for(j = 0, j < mP,j++)
        {
            if(tabuleiro[lT+i][cT+j] != '*' && peca[i][j] != '*')
            {
                return false;
            }
        }
    }
    return true;
}

//verifica se a primeira coluna da peça não confronta com a coluna com do tabuleiro onde ela quer ser encaixada
bool verificaPrimeiraCol(char** tabuleiro, int nT, int mT, char** peca,int nP, int mP,int lT, int cT)
{
    int correColuna = 0;
        if(pilha.top < 1)
        {
            for(correColuna = 0, correColuna < nP, correColuna++)
            {   
                if(tabuleiro[correColuna][cT] == '*' && peca[correColuna][0] == '*')
                {
                    return false;
                } 
            }
        }
    return true;
}

//apenas encaixará a peça após ver que ela é possível
void encaixePronto(char** tabuleiro, int nT, int mT, char** peca,int nP, int mP,int lT, int cT, tipoLetra * vetorLetras, int v)
{
    int i = 0;
    int j = 0;
    for(i = 0, i < nP, i++)
    {
        for(j = 0, j < mP, j++)
        {
            tabuleiro[lT+i][j+cT] = peca[i][j];
        }
    }
}


//tentara encaixar a peça veriicando todas as duas possibilidades tendo em vista o lugar onde ela quer entrar. Caso a peça tenha apenas uma peça na pilha 
//o que nesse caso equivale a ela estar vazia, ele ira ver se a primeira coluna encaixa no tabuleiro e não h´a necessidade de verificar o resto da peça, pois é a
//primeira. No entanto, caso não seja a primeira peça, verificar o encaixe do resto da peça é fundamental
bool encaixePeca(char** tabuleiro, int nT, int mT, char** peca,int nP, int mP, Pilha pilha, tipoLetras * vetorLetras, int lT,int cT, int v)
{
    int correColuna = 0;
        if(pilha.top < 1)
        {
            if(verificaPrimeiraCol(tabuleiro, nT, mT, peca,nP, mP, lT,cT))
            {
                encaixePronto(tabuleiro, nT, mT, peca, nP, mP, lT,cT, vetorLetras, v);
                return true;
            }            
        }
        else
        {
            if(verificaPrimeiraCol(tabuleiro, nT, mT, peca,nP, mP, lT,cT))
            {
                if(verificaResto(tabuleiro, nT, mT, nP, mP, lT,cT))
                {
                    encaixePronto(tabuleiro, nT, mT, peca, nP, mP, lT,cT, vetorLetras, v)
                    return true;
                }
            }
        }

}


//essa função é um função que gereciará para que lado irá a peça baseado nas condições existentes (caso sejá a primeira peça receberá tratamentoe especial) 
//antes de ir para a encaixePeca() e aso não seja, irá diretamente para lá). Depois de todo o tramite o valor bool voltará dizendo se é ou não é possível
//encaixar a peça no tabueiro.
//para ela para que ela possa dizer se é ou não é possível o encaixe
//Além disso, ela também chama as funções encaixa primeira e encaixa peça a fim de verica se é o caso de primeiro encaixe ou não.
bool encaixou(char** tabuleiro, int nT, int mT, Pilha pilha, tipoLetras * vetorLetras, int lT, int cT, int v)
{
    if(pilha.Empty())
    {
        return encaixaPrimeira(tabuleiro,nT,mT,vetorLetras.valor,vetorLetras.n,vetorLetras.m, pilha, vetorLetras);
    }
    else
    {
        return encaixePeca(tabuleiro,nT,mT,vetorLetras[v].valor,vetorLetras[v].n,vetorLetras[v].m,pilha, vetorLetras,lT, cT, v);
    }
}

//A função backtracking é aquela função que sempre que chegarmos ao final de todas as letras testadas ela irá  voltar um passo atrás
//A função desempilhará a pilha (tirará a ultima solução)
//A função tirará do tabuleiro essa última peça colocada atráveis de contas que se basearão em sua ultima atualização de dimensão (o que é suicinte para que)
//a o formato da peça seja substituido por * no tabuleiro.
char** backtracking(char** tabuleiro, Pilha pilha, int i, int , int nO, int mO, tipoLetra * vetorLetras)
{
    int i = 0;
    int j = 0;
    tipoLetra letraRetirada;
    letraRetirada = pilha.pop();
    for(i = 0; i < (pilha.top(vetorLetras->n); i++)
    {
        for(j = 0; j < (pilha.top(vetorLetras->m); j++)
        {
            tabuleiro[i-(pilha.top(vetorLetras->n)][j-(pilha.top(vetorLetras->m)] = '*';
        }
    }
    return tabuleiro;
}


//essa função é responsavel dpor percorrer todo o tabuleiro tentando emcaixar todas as peeças e fazendo backtrack quando necessário e por fim retornar o tabuleiro resolvido
//além disso ela chama a função encaixou que verifica esse encaixe a cada nova tentativa
char** tabuleiroResolvido(char** tabuleiro, int nT, int mT, Pilha pilha, tipoLetras * vetorLetras)
{
    int iEntrou = 0;
    int jEntrou = 0;
    int nO = 0;
    int mO = 0;
    int perVetor = 0;
    int linhas = 0;
    int celDisponivel = 0;
    //percorre a linha do tabuleiro
    for(linhas = 0, linhas < nT, linhas++)
    {
        //percorre a coluna do tabuleiro
        for(celDisponivel = 0, celDisponivel < mT, celDisponivel++)
        {
            //percorre o vetor de structs vetorLetras
            for(perVetor = 0, perVetor < 11, perVetor++)
            {
                if(encaixou(tabuleiro, nT, mT, pilha, vetorLetras, linhas, celDisponivel, v))
                {
                    //caso tenha encaixado, o código adiciona a solução na pilha e atudaliza os indices que definem dão as coordenadas dessa ultima peça 
                    //para o caso de um backtracking
                    pilha.push(vetorLetras[perVetor]);
                    iEntrou = linhas;
                    jEntrou = colDisponivel;
                    nO = vetorLetras.n;
                    mO = vetorLetras.m;
                    
                }
            }
            tabuleiro = backtracking(tabuleiro,pilha, iEntrou, jEntrou,nO, mO)
            //depois de chamar a função backtracking ainda é importante que os indices sejam atualizados para os antigos(aqueles para qual o backtraking nos levou)
            vetorLetras = vetorLetras + 1;
            celDisponivel = jEntrou;
            linhas = iEntrou;
        }
    }

    //se o tauleiro não estiver vazio
    if(tabuleiro[nT-1][mT-1] != '*')
    {
        return tabuleiro;
    }
    else
    {
        cout<<"sem solução!!!";
        return NULL;
    }
}



//cria as peças, as colocam dentro de uma struct com suas respectivas informações de identificação
tipoLetra* enfileiraLetras()
{
    tipoLetra *vetorLetras = (tipoLetra *)malloc(12 * sizeof(tipoLetra));

    //cria F
    tipoLetra F;
    tipoLetra I;
    tipoLetra L;
    tipoLetra N;
    tipoLetra P;
    tipoLetra T;
    tipoLetra U;
    tipoLetra V;
    tipoLetra W;
    tipoLetra X;
    tipoLetra Y;
    tipoLetra Z;
    
    F.code = 2;
    F.valor = criaLetra(2, 3, 3);
    F.m = 3;
    F.n = 3;

    vetorLetras[0] = F;

    I.code = 3;
    I.valor = criaLetra(3, 5, 1);
    I.m = 5;
    I.n = 1;

    vetorLetras[1] = I;

    L.code = 4;
    L.valor = criaLetra(4, 4, 2);
    L.m = 4;
    L.n = 2;

    vetorLetras[2] = L;

    N.code = 5;
    N.valor = criaLetra(5, 4, 2);
    N.m = 4;
    N.n = 2;

    vetorLetras[3] = N;

    P.code = 6;
    P.valor = criaLetra(6, 3, 2);
    P.m = 3;
    P.n = 2;

    vetorLetras[4] = P;

    T.code = 7;
    T.valor = criaLetra(7, 3, 3);
    T.m = 3;
    T.n = 3;

    vetorLetras[5] = T;

    U.code = 8;
    U.valor = criaLetra(8, 2, 3);
    U.m = 2;
    U.n = 3;

    vetorLetras[6] = U;

    V.code = 9;
    V.valor = criaLetra(9, 3, 3);
    V.m = 3;
    V.n = 3;

    vetorLetras[7] = V;

    W.code = 10;
    W.valor = criaLetra(10, 3, 3);
    W.m = 3;
    W.n = 3;

    vetorLetras[8] = W;


    Y.code = 11;
    Y.valor = criaLetra(11, 4, 2);
    Y.m = 4;
    Y.n = 2;

    vetorLetras[9] = Y;

    Z.code = 12;
    N.valor = criaLetra(12, 3, 2);
    N.m = 3;
    N.n = 2;

    vetorLetras[10] = Z;


    return vetorLetras;
    
}

//cria Tabuleiro baseado nas dimenções pedidas
char** geraTabuleiro(int n, int m)
{
    int i = 0;
    int j = 0;
    char** tabuleiro;
    
    tabuleiro = (char **)malloc(n * sizeof(char *));

    for(i = 0; i < n; i++)
    {
        tabuleiro[i] = (char *)malloc(m * sizeof(char));
    }

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            tabuleiro[i][j] = '*';
        }
    }
    return tabuleiro;

}

int main()
{   
    tipoLetra* vetorLetras = enfileiraLetras();
    int n = 0;
    int m = 0;
    int i = 0;
    int j = 0;

    printf("\nDigite n do tabuleiro: ");
    cin>>n;

    printf("\nDigite n do tabuleiro: ");
    cin>>m;
    char** tabuleiro;
    tabuleiro = geraTabuleiro(n,m);

    PilhaLetras.Pilha();

    tabuleiro = tabuleiroResolvido(tabuleiro,n,m,PilhaLetras, vetorLetras);

    printf("\nO tabuleiro resolvido é: ")
    //Caso o tabuleiro não esteja vazio
    if(tabuleio != NULL)
    {
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < m; j++)
            {
                printf("%c", tabuleiro);
            } 
            printf("\n");
        }

    }

    //libera memória de tudo
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            free(tabuleiro[i][j]);
        } 

    }

    for(i = 0; i < 12; i++))
    {
        free(tabuleiro[i]->valor);
    }


    PilhaLetras.~Pilha();
    return 0;
}
