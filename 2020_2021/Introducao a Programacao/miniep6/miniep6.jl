# Parte 2.1 - Escreva abaixo sua função impares_consecutivos(n)

function impares_consecutivos(n)
    soma = 0
    inicio = 1
    while soma < n*n*n
        soma = 0
        count = 0
        while count <= n - 1
            soma += inicio + 2 * count
            count += 1
        end
        inicio += 2
    end
    inicio -= 2
    return inicio
end

# Parte 2.2 - Escreva abaixo suas funções imprime_impares_consecutivos(m) e mostra_n(n)

function imprime_impares_consecutivos(n)
    print(n, " ")
print(n*n*n, " ")
    soma = 0
    inicio = 1
    while soma < n*n*n
        soma = 0
        count = 0
        while count <= n - 1
            soma += inicio + 2 * count
            count += 1
        end
        inicio += 2
    end
    inicio -= 2
    teste(n,inicio)
end

    
function teste(n,inicio)
    contadora = 0
    incremento = 0
    a = 0
    while n > contadora
        a = inicio + (2 * incremento)
        print( a, " ") 
        incremento += 1
        n -= 1
        
    end
end

function mostra_n(n)
    for i in 1:n
    imprime_impares_consecutivos(i)
    print("\n")
    end
end

# Testes automatizados - segue os testes para a parte 2.1. Não há testes para a parte 2.2.

function test()
    if impares_consecutivos(1) != 1
        print("Sua função retornou o valor errado para n = 1")
    end
    if impares_consecutivos(2) != 3
        print("Sua função retornou o valor errado para n = 2")
    end
    if impares_consecutivos(7) != 43
        print("Sua função retornou o valor errado para n = 7")
    end
    if impares_consecutivos(14) != 183
        print("Sua função retornou o valor errado para n = 14")
    end
    if impares_consecutivos(21) != 421
        print("Sua função retornou o valor errado para n = 21")
    end
end



# Para rodar os testes, certifique-se de que suas funções estão com os nomes corretos! Em seguida, descomente a linha abaixo:
# test()
