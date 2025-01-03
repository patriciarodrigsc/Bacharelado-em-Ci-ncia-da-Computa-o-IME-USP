# MAC0110 - EP3
# Nome: <SEU NOME>
# NUSP: <SEU NUSP>

# Parte 1 - Entendendo o código

const LOBO = "🐺"
const PROBABILIDADE_LOBO = 0.05
const ENERGIA_LOBO = 10

const COELHO = "🐰"
const PROBABILIDADE_COELHO = 0.1
const ENERGIA_COELHO = 6

const COMIDA = "🥕"
const PROBABILIDADE_COMIDA = 0.2
const ENERGIA_COMIDA = 6

const TERRENO = "🌿"
const TERRENO_ESPECIAL = "🍀"
const REGENERACAO_TERRENO = 0.01
const PROBABILIDADE_ESPECIAL = 0.01

const FATOR_REPRODUCAO = 2
const TAMANHO_ILHA = 20

function gera_ilha(tamanho)
    ilha = Matrix(undef, tamanho, tamanho)

    for i = 1:tamanho
        for j = 1:tamanho
            dado = rand()
            if dado < PROBABILIDADE_LOBO
                ilha[i, j] = LOBO
            elseif dado < PROBABILIDADE_LOBO + PROBABILIDADE_COELHO
                ilha[i, j] = COELHO
            elseif dado < PROBABILIDADE_LOBO + PROBABILIDADE_COELHO + PROBABILIDADE_COMIDA
                ilha[i, j] = COMIDA
            else
                if rand() < PROBABILIDADE_ESPECIAL
                    ilha[i, j] = TERRENO_ESPECIAL
                else
                    ilha[i, j] = TERRENO
                end
            end
        end
    end

    return ilha
end

function gera_energia(ilha)
    energia = zeros(size(ilha, 1), size(ilha, 2))

    for i = 1:size(energia, 1)
        for j = 1:size(energia, 2)
            if ilha[i, j] == LOBO
                energia[i, j] = ENERGIA_LOBO
            elseif ilha[i, j] == COELHO
                energia[i, j] = ENERGIA_COELHO
            elseif ilha[i, j] == COMIDA
                energia[i, j] = ENERGIA_COMIDA
            end
        end
    end

    return energia
end

function olha_vizinhanca(ilha, energia, animal_x, animal_y, amigo, alvo, perigo)
    alvos = []

    for i in [-1, 0, 1]
        for j in [-1, 0, 1]
            if i == j == 0 || !(0 < animal_x + i <= size(ilha, 1)) || !(0 < animal_y + j <= size(ilha, 2))
                continue
            end

            if ilha[animal_x + i, animal_y + j] == amigo || ilha[animal_x + i, animal_y + j] == perigo
                continue
            elseif ilha[animal_x + i, animal_y + j] == alvo
                return [(animal_x + i, animal_y + j)]
            else
                push!(alvos, (animal_x + i, animal_y + j))
            end
        end
    end

    return alvos
end

function processa_animal!(ilha, energia, animal_energia, i, j, animal, alvo, perigo)
    if energia[i, j] == 0
        morre!(ilha, energia, i, j)
        return
    end

    energia[i, j] -= 1

    vizinhanca = olha_vizinhanca(ilha, energia, i, j, animal, alvo, perigo)

    if vizinhanca == []
        return
    end

    vizinho = rand(vizinhanca)

    if ilha[vizinho[1], vizinho[2]] != alvo && energia[i, j] >= FATOR_REPRODUCAO * animal_energia
        reproduz!(ilha, energia, i, j, vizinho[1], vizinho[2]) # ainda não implementada!
    else
        ocupa_vizinho!(ilha, energia, i, j, vizinho[1], vizinho[2]) # ainda não implementado!
    end

    return
end

function processa_animais!(ilha, energia, animal_energia, animal, alvo, perigo)
    ilha_inicial = copy(ilha)

    for i = 1:size(ilha, 1)
        for j = 1:size(ilha, 2)
            if ilha[i, j] == animal && ilha_inicial[i, j] == animal
                processa_animal!(ilha, energia, animal_energia, i, j, animal, alvo, perigo)
            end
        end
    end

    return
end

function processa_terreno!(ilha, energia)
    for i = 1:size(ilha, 1)
        for j = 1:size(ilha, 2)
            if ilha[i, j] == TERRENO || ilha[i, j] == TERRENO_ESPECIAL
                if rand() < REGENERACAO_TERRENO
                    ilha[i, j] = COMIDA
                    energia[i, j] = ENERGIA_COMIDA
                end
            end
        end
    end

    return
end

function processa_ilha!(ilha, energia)
    processa_animais!(ilha, energia, ENERGIA_COELHO, COELHO, COMIDA, LOBO)
    processa_animais!(ilha, energia, ENERGIA_LOBO, LOBO, COELHO, LOBO)
    processa_terreno!(ilha, energia)
end

# Parte 2 - Complete as funções

function imprime_ilha(ilha)
for i in 1:size(ilha,1)
  function imprimeLinha(ilha)
  colunas = size(ilha,2)
  linhas = size(ilha,1)
  i = 1
    for j in 1:colunas
        print(ilha[i,j])
    end
  end
  println(imprimeLinha(ilha))
  end
end

function conta(ilha, elemento)
linhas = size(ilha, 1)
colunas = size(ilha,2)
cont = 0
    for i in 1:linhas
      for j in 1:colunas
        if a[i,j] == elemento
        cont  = cont + 1
        end
      end
    end
    return cont
end

function energia_total(energia)
linhas = size(energia,1)
colunas = size(energia,2)
cont = 0
  for i in 1:linhas
    for j in 1:colunas
      cont = cont + energia[i,j]
    end
  end
  return cont
end

function ocupa_vizinho!(ilha, energia, animal_x, animal_y, vizinho_x, vizinho_y)
    energia[animal_x,animal_y] += energia[vizinho_x,vizinho_y]
    ilha[vizinho_x,vizinho_y] = ilha[animal_x,animal_y]
    ilha[animal_x,animal_y] = "🌿"

end

function reproduz!(ilha, energia, animal_x, animal_y, novo_x, novo_y)
    ilha[novo_x,novo_y] = ilha[animal_x,animal_y]
    energia[novo_x,novo_y] = energia[animal_x,animal_y] %= 2
    energia[novo_x,novo_y] += div(energia[animal_x,animal_y],2)
    energia[animal_x,animal_y] = div(energia[animal_x,animal_y],2)
end

function morre!(ilha, animal_x, animal_y)
    ilha[animal_x,animal_y] = "🌿"
end

# Parte 3 - Testes e simulação

function analisa_ilha(ilha, energia)
    println("Tamanho da Ilha: $(TAMANHO_ILHA ^ 2)")
    println("Energia Total: $(energia_total(energia))")
    println("Comida: $(conta(ilha, COMIDA))")
    println("Lobos: $(conta(ilha, LOBO))")
    println("Coelhos: $(conta(ilha, COELHO))")
end

function simula(iteracoes)
    ilha = gera_ilha(TAMANHO_ILHA)
    energia = gera_energia(ilha)

    imprime_ilha(ilha)
    println()
    analisa_ilha(ilha, energia)
    println()

    for i = 1:iteracoes
        processa_ilha!(ilha, energia)
        imprime_ilha(ilha)
        println()
        analisa_ilha(ilha, energia)
        println()
    end

    return
end

simula(30)

# Parte 4 - Usando DataFrames e plotando gráficos

using DataFrames, StatsPlots, Plots

function atualiza!(simulacao, passo, ilha, energia)
    append!(simulacao,
        DataFrame(tamanho = TAMANHO_ILHA ^ 2,
            passo = passo,
            energia_total = energia_total(energia),
            comida = conta(ilha, COMIDA),
            lobos = conta(ilha, LOBO),
            coelhos = conta(ilha, COELHO)))
    return
end

function simula2(iteracoes, imprime)
    simulacao = DataFrame(tamanho = Float64[],
        passo = Float64[],
        energia_total = Float64[],
        comida = Float64[],
        lobos = Float64[],
        coelhos = Float64[])

    ilha = gera_ilha(TAMANHO_ILHA)
    energia = gera_energia(ilha)

    if imprime
        imprime_ilha(ilha)
        println()
        analisa_ilha(ilha, energia)
        println()
    end

    for i = 1:iteracoes
        atualiza!(simulacao, i, ilha, energia)
        processa_ilha!(ilha, energia)

        if imprime
            imprime_ilha(ilha)
            println()
            analisa_ilha(ilha, energia)
            println()
        end
    end

    return simulacao
end

function gera_graficos(iteracoes)
    dados = simula2(iteracoes, false)
    layout = @layout [a; b]

    p1 = @df dados plot(:passo,
        [:lobos, :coelhos],
        label = ["Lobos" "Coelhos"],
        legend = :topright)

    p2 = @df dados plot(:passo,
        [:energia_total, :comida],
        label = ["Energia Total" "Comida"],
        legend = :topright)

    plot(p1, p2, layout = layout)
end
