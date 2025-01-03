import math

def calcula_maneiras(valor):
    moedas = []
    i = 1
    k = 1
    moeda_index = 0

    maneiras_pag = [0] * (valor + 1)
    maneiras_pag[0] = 1

    while k <= valor:
        k = int(math.pow(i, 3))
        i = i + 1
        if k <= valor:
            moedas.append(k)

    while moeda_index < len(moedas):
        moeda = moedas[moeda_index]
        j = moeda
        while j <= valor:
            maneiras_pag[j] = maneiras_pag[j] + maneiras_pag[j - moeda]
            j = j + 1
        moeda_index = moeda_index + 1

    return maneiras_pag[valor]

def main():
    while True:
        try:
            valor = int(input())
            maneiras = calcula_maneiras(valor)
            print(maneiras)
        except EOFError:
            break

if __name__ == "__main__":
    main()
