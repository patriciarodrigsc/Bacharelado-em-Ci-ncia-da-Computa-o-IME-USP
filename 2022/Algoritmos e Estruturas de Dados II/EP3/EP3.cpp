
// Grafos - Verifica se um grafo direcionado tem ciclo

#include <iostream>
#include <fstream>
#include <list>
#include <stack> // pilha para usar na DFS
#include <math.h>
#include <string.h>
#include <vector>

using namespace std;

struct no
{
    int valor;
    int dist;
};

class Grafo
{

    public:
        Grafo(int V);
        ~Grafo();
        void deleteGrafo();
        void adicionarAresta(int v1, int v2);
        void printM();
        void printMb();
        void dfsR(int v);
        void bfsR(int v);
        void printVisitados();
        void printCC();
        void printPais();
        void identificaCompCon();
        void estabeleceConexao(string* palavras);
        void probabilidade(int p100);
        void calculaDist(int uI);
        // verifica se o grafo direcionado tem ciclo
        bool temCiclo();
        int V; // número de vertices
        int qntdCom;
        int *pais;
        bool *visitados;
        int *cc;
        int *dist;
        no **matriz; 
        bool contemCiclos;
        void reset();
        int mediaDist();
    private:
        void identificaCompCon(int v);
        void bfsR(int v, int grau);


};

Grafo::Grafo(int V)
{
    //inicializa matriz
    this->V = V;
    this->qntdCom = 0;
    this->contemCiclos = false;

    matriz = (no**)malloc(V * sizeof(no*));

    for(int i = 0; i < V; i++)
    {
        matriz[i] = (no*)malloc(V * sizeof(no));
    }

    for(int i = 0; i < V; i++)
    {
        for(int j = 0; j < V; j++)
        {
            matriz[i][j].valor = 0;
            matriz[i][j].dist = -1;
        }
    }
    //inicializa vetor visitados
    visitados = (bool*)malloc(V * sizeof(bool));

    for(int i = 0; i < V; i++)
    {
        visitados[i] = false;
    }
    
    //inicializa vetor pais
    pais = (int*)malloc(V * sizeof(int));

    for(int i = 0; i < V; i++)
    {
        pais[i] = -1;
    }

    cc = (int*)malloc(V * sizeof(int));

    for(int i = 0; i < V; i++)
    {
        cc[i] = -1;
    }

    dist = (int*)malloc(V * sizeof(int));

    for(int i = 0; i < V; i++)
    {
        dist[i] = -1;
    }
    

}

Grafo::~Grafo()
{
    delete[] visitados;
    delete[] pais;
    delete[] cc;
    delete[] dist;
    delete[] matriz;
}

void Grafo::deleteGrafo()
{
    for(int i = 0; i < V; i++)
    {
        for(int j = 0; j < V; j++)
        {
            matriz[i][j].valor = 0;
            matriz[i][j].dist = -1;
        }
    }
    this->contemCiclos = false;
}

void Grafo::printM()
{

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            cout << matriz[i][j].valor << " ";
        }
            
        // Newline for new row
        cout << endl;
    }
}

void Grafo::printMb()
{

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            cout << matriz[i][j].valor << "(" << matriz[i][j].dist << ")" << " ";

        }
            
        // Newline for new row
        cout << endl;
    }
}

void Grafo::reset()
{
    this->qntdCom = 0;
    for(int i = 0; i < V; i++)
    {
        visitados[i] = false;
        dist[i] = -1;
        cc[i] = -1;
        pais[i] = -1;

        for(int i = 0; i < V; i++)
        {
            for(int j = 0; j < V; j++)
            {
                matriz[i][j].dist = -1;
            }
        }
    }
}

void Grafo::printVisitados()
{
    for (int i = 0; i < V; i++)
    {
        cout << visitados[i]<< " ";
    }
        
    // Newline for new row
    cout << endl;
}

void Grafo::printPais()
{
    for (int i = 0; i < V; i++)
    {
        cout << pais[i] << " ";
    }
        
    // Newline for new row
    cout << endl;
}

void Grafo::printCC()
{
    for (int i = 0; i < V; i++)
    {
        cout << cc[i] << " ";
    }
        
    // Newline for new row
    cout << endl;
}

void Grafo::dfsR(int v)
{
    if(visitados[v] == false)
    {
        visitados[v] = true;
        for(int i = 0; i < V; i++)
        {
            if(matriz[v][i].valor == 1)
            {
                
                if(pais[i] == -1)
                {
                    pais[i] = v;
                }

                if(visitados[i] != -1)
                {
                    contemCiclos = true;
                }
                dfsR(i);
            }
        }
    }
}

void Grafo::bfsR(int v)
{
    bfsR(v, 1);
    matriz[v][v].dist = 0;
    dist[v] = 0;
}

void Grafo::bfsR(int v, int grau)
{

    for(int add = 0; add < V; add++)
    {
        if((matriz[v][add].valor == 1 && matriz[v][add].dist > grau) || (matriz[v][add].valor == 1 && matriz[v][add].dist == -1 && dist[add] == -1))
        {
            matriz[v][add].dist = grau;
            dist[add] = grau;
        }
    }

    if(visitados[v] == false)
    {
        visitados[v] = true;
        for(int i = 0; i < V; i++)
        {
            if(matriz[v][i].valor == 1)
            {
                if(pais[i] == -1)
                {
                    pais[i] = v;
                }
                else
                {
                    contemCiclos = true;
                }
                bfsR(i, grau + 1);
            }
        }
    }
}

void Grafo::adicionarAresta(int v1, int v2)
{
    matriz[v1][v2].valor = 1;
}

int random(int min, int max)
{
    int r = (min + (rand() % max));
    return r;
}

void Grafo::estabeleceConexao(string* palavras)
{
    cout << "ENTREI" << endl;
    int conecta = 0;
    int k;
    int n;

    char aux1[20];
    char aux2[20];
    for(int i = 0; i < 20; i++)
    {
        aux1[i] = 'F';
        aux2[i] = 'F';
    }

    int n1 = 0;
    int tamCo = 0;

    for(int i = 0; i < V; i++)
    {
        tamCo = palavras[i].length();
        strcpy(aux1, palavras[i].c_str());
        
        for(int j = 0; j < V; j++)
        {

            if(i != j)
            {
                conecta = 0;

                cout << "compara:" << palavras[i] << " e " << palavras[j] << endl;
                strcpy(aux2,palavras[j].c_str());
                for(int t = 0; t < strlen(aux1); t++)
                {
                    cout << "1:" << aux1[t] << endl;
                    cout << "2:" << aux2[t] << endl;
                    if(aux1[t] == aux2[t])
                    {
                        cout << aux1[t] << "é igual a " << aux2[t] << endl;
                        conecta++;
                    }
                }
                cout << "conecta é: " << conecta << endl;
                if(conecta == tamCo - 1)
                {
                    adicionarAresta(i,j);   
                }
            }
        } 
    }
}

void Grafo::probabilidade(int p100)
{
    int res;
    reset();
    for(int k = 0; k < V; k++)
    {
        for(int i = 0; i < V; i++)
        {
            res = random(1, 100);

            if(res <= p100)
            {
                adicionarAresta(k, i);
            }
        }
    }

}

void Grafo::identificaCompCon()
{
    for(int k = 0; k < V; k++)
    {
        if(cc[k] == -1)
        {
            dfsR(k);
            for(int i = k; i < V; i++)
            {
                if(visitados[i])
                    cc[i] = k;

            }

            for(int i = k; i < V; i++)
            {
                if(cc[i] == k)
                    dfsR(i);
            }

            for(int i = k; i < V; i++)
            {
                if(visitados[i])
                    cc[i] = k;
            }
        }
    }

    int contComp = 0;
    int contTot = 0;
    int *cap = (int*)malloc(V * sizeof(int));
    for(int i = 0; i < V; i++)
    {
        cap[i] = -1;
    }

        for(int i = 0; i < V; i++)
        {
            for(int j = 0; j < V; j++)
            {
                if(cc[j] == i)  
                {
                    contComp++;
                }
            }

            if(contComp != 0)
            {
                contTot++;
                cap[i] = contComp;
            }
            contComp = 0;
        }

    int contQual = 1;

    for(int j = 0; j < V; j++)
    {
        if(cap[j] != -1)
        {
            cout << "A quantidade de elementos da " << contQual <<"° componente é: " << cap[j] << endl;  
            contQual++;
        }
    }
    cout << "A quantidade de componentes conexas é " << contTot << endl;
    this->qntdCom = contTot;

    
}

void Grafo::calculaDist(int uI)
{
    bfsR(uI);
}

int Grafo::mediaDist()
{
    int media = 0;
    int cont = 0;
    for(int i = 0; i < V; i++)
    {
        if(visitados[i])
        {
            media = media + dist[i];
            cont++;
        }
    }

    media = media /cont;

    return media;
}

int main(int argc, char *argv[])
{
    char op;
    cout << "########## Menu ##########" << endl;
    cout << "1 - Testar funcionalidades dos grafos (ler grafo, calcular distancia, ver componentes conexas, verificar se há ciclos, gerar grafos aleatórios de probabilidade p, ler grafos de palavras) " << endl;
    cout << "2 - testar experimentos com grafos legais" << endl;
    cin >> op;

    if(op == '2')
    {   
        char op1;
        cout << "########## Menu ##########" << endl;
        cout << "1 - Componentes Gigantes " << endl;
        cout << "2 - Seis Graus de separação" << endl;
        cin >> op1;



        if(op1 == '1')
        {
            float e;
            float p1 = 0;
            float p2 = 0;
            int ver = 200;
            int mediaDistGrafos = 0;
            int vMed[100];
            int qntdCom = 0;
            int media;
            int qntdI;
            char tam;
            int tamI;
            string si;
            cout << "***************** Teste ****************" << endl;
            
            tamI = 20;
            e = 0.05;
            cout << "e: " << e << endl;
            p1 = (1 - e)/tamI; 
            p2 = (1 + e)/tamI;

            Grafo grafo(tamI);
            grafo.printM();
            for(int i = 0; i < 100; i++)
            {
                grafo.probabilidade(i);
                grafo.identificaCompCon();
                qntdCom = grafo.qntdCom;
                qntdI = uint8_t(qntdCom);

                vMed[i] = qntdI;

            }

            cout << " Um arquivo de texto arqCompCom.txt foi gerado com dados que mostram que para um grafo n = 20 e = 1/n (e = 1/20 = 0.05) e p <= (1-e)/n (p <=" << p1 << ") a quantidade de componentes conexas aumenta e também que para p >= (1+e)/n (p >= " << p2 << ") a quantidade de componentes conexas diminuem até chegar a 1. No relatório essas informações estão mais organizadas e há um gráico também mostrando isso" << endl;
            char Str[100];
            FILE *arq;
            char result;
            arq = fopen("arqCompCom.txt", "wt");  // Cria um arquivo texto para gravação
            if (arq == NULL) // Se não conseguiu criar
            {
                printf("Problemas na CRIACAO do arquivo\n");

            }

            string c = " ";
            for(int i = 0; i < 100; i++)
            {
                c = c + to_string(vMed[i]);
                fputs(c.c_str(), arq);
                fputs("\n", arq);   
                c = " ";
            }
            
            fclose(arq);
        }

        if(op1 == '2')
        {
            int p = 10; //0.1 * 100 = 10 (p = 0.1)
            int ver = 300;
            int mediaDistGrafos = 0;
            int vMed[ver];
            Grafo grafo(1);

            for (int i = 5; i < ver; i++)
            {
                int media;
                Grafo grafo(i);
                grafo.probabilidade(p);
                grafo.calculaDist(0);
                media = grafo.mediaDist();
                vMed[i-5] = media;
                grafo.reset();
            }

            char Str[ver];
            FILE *arq;
            char result;
            arq = fopen("arq.txt", "wt");  // Cria um arquivo texto para gravação
            if (arq == NULL) // Se não conseguiu criar
            {
                printf("Problemas na CRIACAO do arquivo\n");

            }

            char c;
            for(int i = 0; i < ver-5; i++)
            {
                c = vMed[i] + '0';
                fputc(c, arq);
                fputs("\n", arq);
            }
            
            fclose(arq);
            

            cout << "Um arquivo de texto foi gerado com dados de grafos de G(5,p) até G(300, p) sendo p = 0.1 a probabilidade de conexão. Os dados mostram que a distancia média dos vértices conforme o tamanho do gráfico vai crescendo também vai crescendo e '' estabiliza '' ao redor de seis, fazendo com que a média de distância (grau de separação) seja 6. Mais informações estão no relatório e um gráfico também para ilustrar o que ocorreu." << mediaDistGrafos << endl;
            //grafo.~Grafo();
        }
    }
    if(op == '1')
    {
        string tam[2];
        int tamI;
        cout << "Digite o tamanho do grafo (V E): (ex: 10 5)   :" ;
        for(int i = 0; i < 2; i++)
            cin >> tam[i];

        tamI = stoi(tam[0]);
        Grafo grafo(tamI);
        int aresta = 0;
        aresta = stoi(tam[1]);
        while(true)
        {
            cout << "########## Menu ##########" << endl;
            cout << "1 - Constroir a estrutura para representar o grafo (adicionar vertices e arestas) " << endl;
            cout << "2 - dado um vértice u calcular a distância de u até todos os vértices de G" << endl;
            cout << "3 - dado um grafo G determinar o número de componentes conexas e o tamanho de cada componente"  << endl;   
            cout << "4 - Verificar se há ciclos"  << endl;
            cout << "5 - Fazer experimentos de grafos aleatórios para G(n,p) talque n é o numero de vertices e p a probabilidade, 0 <= p <= 1" << endl;
            cout << "6 - Grafo de palavras" << endl;

            char opcao = 0;
            cin >> opcao;
            //adiciona arestas no grafo
            if(opcao == '1')
            {
                int qntd;
                grafo.reset();
                grafo.deleteGrafo();

                string ver[2];
                char u1 = 0;
                char v1 = 0;
                int u1I = 0;
                int v1I = 0;

                qntd = aresta;
                for(int i = 0; i < qntd; i++)
                {  
                    cout << "Digite u_"<< i <<"v_"<< i << "(ex: 0 1)   :" << endl;
                    for(int i = 0; i < 2; i++)
                        cin >> ver[i];
                    u1I = stoi(ver[0]);
                    v1I = stoi(ver[1]);
                    grafo.adicionarAresta(u1I, v1I);
                }

                cout << "Essa é a matriz de adjacencia" << endl;
                grafo.printM();
            }
            //ve a distancia do vertice u a todos os outros
            if(opcao == '2')
            {
                char u;
                int uI;
                int media = 0;
                cout << "Digite o vértice u" << endl;
                cin >> u;
                uI = u - '0';
                grafo.calculaDist(uI);
                for(int i = 0; i < grafo.V; i++)
                {
                    if(grafo.visitados[i])
                        cout << "A distancia de " << uI << " até " << i << " é " << grafo.dist[i] << endl;
                }
                
                grafo.reset();
            }

            if(opcao == '3')
            {
                grafo.identificaCompCon();
                grafo.reset();
            }

            if(opcao == '4')
            {
                bool testa = false;

                for(int i = 0; i < grafo.V; i++)
                {
                    grafo.dfsR(i);
                    if(grafo.contemCiclos == true)
                    {
                        testa = true;
                    }
                }

                if(testa)
                {
                    cout << "Há ciclos " << endl;
                }else
                {
                    cout << "Não há ciclos" << endl;
                }
                grafo.reset();
            }
            //grafos aleatórios
            if(opcao == '5')
            {
                grafo.deleteGrafo();
                grafo.reset();
                char *pc;
                string aux;
                float pF;
                cout << "Qual é a probabilidade P PARA O GRAFO g(v, p) com que os vértices lidos devem se ligar?" << endl;
                cin >> aux;
                int n = aux.length();
                char p[n+1];
                strcpy(p, aux.c_str());
                pF = atof(p);
                pF = pF * 100;

                int maxI = (int)pF;
                grafo.probabilidade(maxI);

            }
            //grafos de palavras
            if(opcao == '6')
            {
                char opp;
                cout << "Observação: A 1° palavra será 0, a 2° palavra será 1, a 3° 3 e assim por diante. Quando for verificar alguma operação como calcular ver a distância use esses valores" << endl;
                cout << "1 - testar lista de palavras listpal.txt" << endl;
                cout << "2 - Digitar palavras" << endl;
                cin >> opp;

                if(opp == '2')
                {
                    string aux;
                    int tamanho = grafo.V;
                    string palavras[tamanho];
                    for(int i = 0; i < grafo.V; i++)
                    {
                        cout << "Digite a palavra" << endl;
                        cin >> aux;
                        
                        palavras[i] = aux;
                    }
                    grafo.estabeleceConexao(palavras);
                    grafo.printM();
                    grafo.reset();
                }
                
                if(opp == '1')
                {
                    Grafo grafo1(238);
                    string filename("teste.txt");
                    vector<string> words;
                    string word;
                    
                    ifstream input_file(filename);
                    if (!input_file.is_open()) {
                        cerr << "Não pode abrir o arquivo - '"
                            << filename << "'" << endl;
                        return EXIT_FAILURE;
                    }

                    while (input_file >> word) {
                        words.push_back(word);
                    }

                    cout << "aqui" << endl;
                    string palavras[238];
                    int cont = 0;
                    for (const auto &i : words) 
                    {
                        cout << "i: " << i << endl;
                        palavras[cont] = i;
                        cont++;                        
                    }
                    grafo = grafo1;
                    grafo.estabeleceConexao(palavras);
                    grafo1.printM();
                    grafo.identificaCompCon();
                    grafo.reset();
                    break;
                }
            }



            cout << "Deseja fazer mais alguma verificação? s/n" << endl;
            char quer;
            cin >> quer;
            if(quer == 'n')
                break;
        }
    }

	return 0;
}