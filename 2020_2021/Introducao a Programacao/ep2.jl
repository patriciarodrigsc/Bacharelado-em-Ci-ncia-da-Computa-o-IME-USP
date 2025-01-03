#Essa função lê os números digitados pelo usuário e os armazena em um vetor chamado cards
function lerVetor()
num = 0
cards = [1,2,3,4]
      println("Qual o tamanho do vetor")
            tam = parse(Int64, readline())
            println("O tamanho informado foi :", tam)
            println("Digite o vetor")
            num = parse(Int64, readline())
            println("O vetor informado foi :", num)
            for i in 1:tam
                  cards[i] = div(num, 10^(tam - i))
                  num = num - cards[i]*10^(tam - i)
            end
            return cards
end


#Essa função recebe um vetor "cards" e ordena seus valores em ordem crescente
function ordenarVetores(cards)
aux = 0
      tam = 0
      tam = length(cards)
      for i in 1:tam

            if cards[i] > cards[i+1]
                  aux = cards[i]
                  cards[i] = cards[i+1]
                  cards[i+1] = aux
                  i = 1
                  aux = 0
           end
      end
      return cards
end





#Essa função recebe um vetor "cards" e concatena todos os seus valores em uma única variável, seguindo sua ordem natural
function concatenarVetor(cards)
num1 = 0
v = []
tam = length(cards)
      for i in 1:tam - 1
            num1 += v[i] * 10^(tam - i)
      end
      return num1
end



#Essa função recebe um vetor "cards" e concatena todos os seus valores em uma única variável, mas invertendo a sua ordem
function concatenarVetorInvertido(cards)
num2 = 0
v = []
tam = length(cards)
      for i in tam:1
      num2 += v[i] * 10^(tam - i)
      end
      return num2
end


#Essa função calcula a diferença entre os dois valores
function diferencaVariaveis(num1, num2)
diferenca = 0

      if num1>num2
            diferenca = num1 - num2
            else
            diferenca = num2 - num1
      end

      return diferenca
end



# Essa função desmembra os  valores de uma variável em um vetor "voltaVetor"
function voltaVetor(num)
tam = lenght(num)
v = []
      for i in 1:tam
            v[i] = div(num, 10^(tam - 1))
            num = v[i] * 10^(tam - 1)
      end

      return voltaVetor
end

#Essa função faz o processo conhecido como "rotina de Kaprekar"
function iterarKaprekar()

cards = lerVetor()

vetorOrdenado = ordenarVetores(cards)

numConcat = concatenarVetor(vetorOrdenado)

end

numConcatInv= concatenarVetorInvertido(vetorOrdenado)

diferenca = diferencaVariaveis(numConcat, numConcatInv)
      return diferenca

end


#essa função fará a comparação entre os valor obtidos pelas iterações com o valor desejado

function checkWill()

      for i in 1:7
            valorObtido = iterarKaprekar

                  if valorObtido == 6174
                  return true
                  end
      end
      return false
end

checkWill()
