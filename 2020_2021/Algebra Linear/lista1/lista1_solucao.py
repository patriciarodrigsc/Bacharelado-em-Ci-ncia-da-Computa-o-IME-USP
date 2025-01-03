import random
import math
def resort(M, n,x):
    A = []
    for i in range(n):
        j = i
        while j < (n * n):
            A.append(M[j])
            j += n
    print(A)
    if x == 1:
        return EscalonamentoS(A, n*n, n)
    if x == 2:
        return EscalonamentoI(A, n*n, n)

def retorna_vetores(M, n,x):
    A = []
    for l in range(n):
        for i in range(n):
            linha = []
            j = 0
            while (j < n):
                for k in range(n * n):
                    if (k - l) % n == 0:
                        linha.append(M[i][j])
                        j += 1
                    else:
                        linha.append(0)
            A.append(linha)
    return resort(A, n,x)

def EscalonamentoS(M, n, nF):
    k = 0
    cont = 0
    for j in range(n):
        #escolhendo um pivô
        for i in range(n):
            if(M[i][j] != 0 and i>=cont):
                pivoI = i
                i = i+1
                cont = cont +1
                while i < n:
                    if(M[i][j] != 0):
                        kLocal = M[i][j]
                        k = j
                        while k < n:
                            M[i][k] = M[pivoI][j]*M[i][k] - (kLocal * M[pivoI][k])
                            k = k+1
                    i = i+1
    print("Escalonando a matriz para a forma triangular superior para posterior resolucao do sistema:")
    print(M)
    return(solucionaMatrizTriangSup(M, n, nF))

def EscalonamentoI(M, n, nF):
    k = 0
    x = -1
    cont2 = 1
    iterac = 0
    while iterac < n*n:
        for i in range(n):
                #escolhendo um pivô
                for j in range(n):
                    if i == j:
                        if(j >= n-cont2 and i >= n-cont2):
                            if(M[i][j] != 0):
                                pivoI = i
                                i = i-1
                                while i > -1:
                                    if M[i][j] != 0:
                                        kLocal = M[i][j]
                                        k = j
                                        while k > -1:
                                            M[i][k] = M[pivoI][j]*M[i][k] - (kLocal * M[pivoI][k])
                                            k = k-1
                                    i = i - 1
                            cont2 = cont2+1
        iterac = iterac + 1

    print("A matriz escalonada para triangular Inferior: ", M)

def matrizIdentidade(nF):
    n = nF
    matriz = [] # lista vazia
    valor = 0
    for i in range(n):
        # cria a linha i
        linha = [] # lista vazia
        for j in range(n):
            linha.append(int(valor))
        # coloque linha na matriz
        matriz.append(linha)
    for i in range(n):
        for j in range(n):
            if i == j:
                matriz[i][j] = 1
    return matriz

def alocaMatriz(n,m):
    matriz = [] # lista vazia
    valor = 0
    for i in range(n):
        # cria a linha i
        linha = [] # lista vazia
        for j in range(m):
            linha.append(int(valor))

        # coloque linha na matriz
        matriz.append(linha) 
    return matriz

def solucionaMatrizTriangSup(M, n, nF):
    print("As ", n, "incógnitas são: ")
    matInc = []
    ap = alocaMatriz(n,1)
    ide = matrizIdentidade(nF)
    conti = 0
    mult = n
    for i in range(nF):
        for j in range(nF):
            ap[conti][0] = ide[i][j]
            conti = conti+1
    resultado = alocaMatriz(1,n)
    cont2 = 1
    iterac = 0
    #procurando o coeficiente angular da incógnita solucionada
    while iterac < n*n:
        foi = 0
        for i in range(n):
                #escolhendo um pivô
                for j in range(n):
                    if i == j and foi == 0:
                        if(j >= n-cont2 and i >= n-cont2 and foi == 0):
                            if(M[i][j] != 0):
                                foi = 1
                                a = i
                                b = j
                                mult = i - 1
                                aux = (int(ap[a][0])/int(M[a][b]))
                                print("x:",aux)
                                while mult > -1:
                                    M[mult][b] = M[mult][b]*aux
                                    mult = mult - 1
                            cont2 = cont2+1
        iterac = iterac + 1
                    
def geraMatrizAleatoria():
    a = random.randint(0,9)
    matriz = [] # lista vazia
    valor = random.randint(0,9)
    for i in range(a):
        # cria a linha i
        linha = [] # lista vazia
        for j in range(a):
            linha.append(int(random.randint(0,9)))

        # coloque linha na matriz
        matriz.append(linha) 
    return a, matriz

def geraHibertMatriz(n,m):
    matriz = [] # lista vazia
    valor = 0
    for i in range(n):
        i = i+1
        # cria a linha i
        linha = [] # lista vazia
        for j in range(m):
            j = j+1
            linha.append(1/i+j-1)
        matriz.append(linha) 
    return matriz

print("EXERCÍCIO 4:  Implemente o algoritmo do item 1 e teste o seu código para a matrizes aleatórias") 
print("--------------------TESTE1--------------------")         
A = [[1,2],[3,4]]
n = 2
retorna_vetores(A, n, 1)
print("--------------------TESTE2--------------------") 
print("Gerando para matrizes aleatórias:")
n, B = geraMatrizAleatoria()
retorna_vetores(B, n, 1)
n, B = geraMatrizAleatoria()
retorna_vetores(B, n, 1)
n, B = geraMatrizAleatoria()
retorna_vetores(B, n, 1)
print("EXERCÍCIO 5:  Implemente o algoritmo do item 2 e teste o seu código para a matrizes aleatórias. Analise o resultado dos seus testes.")
C = [[1,2],[3,4]]
n = 2
retorna_vetores(C,n,2)
n,D = geraMatrizAleatoria()
retorna_vetores(D, n, 1)
n,D = geraMatrizAleatoria()
retorna_vetores(D, n, 1)
n,D = geraMatrizAleatoria()
retorna_vetores(D, n, 1)

E = geraHibertMatriz(5,5)
print("Matriz de Hilbert 5x5: ")
print(E)
retorna_vetores(E,5, 1)
for i in range(50):
    i = i+5
    for j in range(50):
        j = j+5
        E = geraHibertMatriz(i,j)
        print("Matriz de Hilbert 5x5: ")
        print(E)
        retorna_vetores(E,i, 1)