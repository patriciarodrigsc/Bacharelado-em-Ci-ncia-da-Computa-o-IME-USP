import random
import math
import time

def pontos(n):
	x = []
	y = []

	for i in range(n):
		print("Digite X",i+1,":")
		a = int(input())
		x.append(a)
		print("Digite Y",i+1,":")
		b = int(input())
		y.append(b)
	return x,y

def sistemaNormal(x, y, n):
	a = 0
	matrizNormal = []
	m = math.sqrt(n)
	m = int(m)
	for i in range(m):
		linha = []
		for j in range(m):
			a = 0
			for k in range(n):
				a = a + 1 * pow(x[k],j+i)
			linha.append(a)
		matrizNormal.append(linha)
	return matrizNormal

def matrizB(x, y, n):
	a = 0
	matriz = []
	m = math.sqrt(n)
	m = int(m)
	for i in range(m):
		linha = []
		for j in range(1):
			a = 0
			for k in range(n):
				a = a + y[k] * pow(x[k],i)
			linha.append(a)
		matriz.append(linha)
	return matriz

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

def gauss(M, n2):
	#triang. Inferior
	contPivo = 0
	for j in range(n2):
		contPivo = contPivo + 1
		for i in range(n2):
			if i == contPivo - 1:
				den = M[contPivo-1][j]
				for k in range(n2*2):
					M[i][k] = M[i][k] * (1/den)
			if i > contPivo - 1:
				pivoLoc = M[i][j]
				for k in range(n2*2):
					M[i][k] = M[i][k] - (pivoLoc * M[contPivo - 1][k])
	#triangSup
	for j in range(n2):
		for i in range(n2):
			if i == j and i > 0:
				pivo = M[i][j]
				for l in range(i):
					pivoLoc = M[l][j]
					for k in range((n2*2)-j):
						M[l][j+k] = M[l][j+k] - (pivoLoc * M[i][j+k])
	return M

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

def multiplicaAinB(A,B,n2):
	C = alocaMatriz(n2,1)
	for i in range(n2):
		for j in range(n2):
			C[i][0] = C[i][0] + (A[i][j] * B[j][0])
	return C

def testa(x,y,n):
	print("Os pontos são: ")
	for i in range(n):
		print("(",x[i],",",y[i],")")
	print("Passo 1: Dado os pontos, calcular as matrizes A e B que irão compor o Sistema Normal")
	print("Matriz A:")
	matriz = sistemaNormal(x,y,n)
	print("matriznormal",matriz)
	print(matriz)
	matriz2 = matrizB(x,y,n)
	print("matrizB",matriz2)

	n2 = math.sqrt(n)
	n2 = int(n2)
	mIdentidade = matrizIdentidade(n2)
	print("matrizI:",mIdentidade)

	mMatriz = []
	for i in range(n2):
		linha = []
		for j in range(n2):
			linha.append(matriz[i][j])
		for j in range(n2):
			linha.append(mIdentidade[i][j])
		mMatriz.append(linha)

	#Pela lógica AX = B -> X = A^-1*B
	matrizApoio = gauss(mMatriz, n2)

	matrizInversa = []
	for i in range(n2):
		linha = []
		for j in range(n2):
			linha.append(matrizApoio[i][j+n2])
		matrizInversa.append(linha)
	print("Passo 2: Dada as matrizes, calcular as incógnitas pelo Método de eliminação de Gauss. Pela lógica AX = B -> X = A^-1*B ")
	print("Arredondando, matriz inversa de A é:")
	imprime_matriz(matrizInversa)
	print("Por fim, para o polinômio na forma: p(x) = a0 + a1X + a2x^2 + ... + amX^m, temos:")
	C = multiplicaAinB(matrizInversa, matriz2,n2)

	for i in range(n2):
		print("a",i,":",C[i][0],"(aproximadamente",round(arredondar(C[i][0]),1),")")

def testes():
	print("teste 1")
	time.sleep(2)
	x = [-1,0,1,2,7,3,1,4,3]
	y = [1,-1,2,3,4,3,2,5,6]
	n = 9
	time.sleep(2)
	testa(x,y,n)
	x = [1,-2,0,4]
	y = [2,4,0,-2]
	n = 4
	time.sleep(2)
	testa(x,y,n)
	x = [1,4]
	y = [-1,2]
	n = 2
	time.sleep(2)
	testa(x,y,n)
	x = [0,-1,0,-1,0]
	y = [-1,0,-1,0,0]
	n = 5
	time.sleep(2)
	testa(x,y,n)
	x = [0,-1,0,0,0]
	y = [0,0,0,0,-1]
	n = 5
	time.sleep(2)
	testa(x,y,n)
	x = [1]
	y = [1]
	n = 1
	time.sleep(2)
	testa(x,y,n)
	x = [12,-11,18,123,2]
	y = [90,1,2,17,-1]
	n = 5
	time.sleep(2)
	testa(x,y,n)

def arredondar(num):
    return float( '%g' % ( num ) )

def imprime_matriz(matriz):

    linhas = len(matriz)
    colunas = len(matriz[0])

    for i in range(linhas):
        for j in range(colunas):
            if(j == colunas - 1):
                print("%.2f" %matriz[i][j])
            else:
                print("%.2f" %matriz[i][j], end = " ")
    print()



sair = 0
while(sair == 0):
	print("##Menu##")
	print("Digite ""1"" para executar os testes")
	print("Digite ""2"" para introduzir pontos para novos testes")
	print("Digite ""3"" para sair")
	a = input()
	a = int(a)
	if a == 1:
		testes()
	if a == 2:
		print("Digite quantos pontos você quer por:")
		n = input()
		n = int(n)
		x,y = pontos(n)
		testa(x,y,n)
	if a == 3:
		sair = 1









