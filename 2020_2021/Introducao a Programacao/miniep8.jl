using Test

function verifica()

    @test compareByValue("2♠", "A♠") == true
    @test compareByValue("K♥", "10♥") == false
    @test compareByValue("10♠", "10♥") == false
     println ("Final dos testes")
end


#Função que comparará o valor entre duas cartas
function compareByValue(x,y)
 x1 = SubString(x, 1, 1)
 y1 = SubString(y, 1, 1)
      if x1 < y1
      return true
      else
      return false
      end
end

function troca(v, i, j)
      aux = v[i]
      v[i] = v[j]
      v[j] = aux
end
function insercao(v)
tam = length(v)
      for i in 2:tam
      j = i
            while j > 1
                  if compareByValue(v[j], v[j - 1]) == true
                  troca(v, j, j - 1)
                  else
                  break
                  end
            j = j - 1
            end
      end
      return v
end


 insercao(["10♥", "10♦", "K♠", "A♠", "J♠", "A♠"])


 using Test

 function verifica()

       @test compareByValueAndSuit("2♠", "A♠") == true
       @test compareByValueAndSuit("K♥", "10♥") == false
       @test compareByValueAndSuit("10♠", "10♥") == true
       @test compareByValueAndSuit("A♠", "2♥") == false

      println ("Final dos testes")
 end


 function compareByValueAndSuit(x,y)
 valor = 0
 x1 = SubString(x, 2, 2)
 y1 = SubString(y, 2, 2)
      if x < y
      return true
      else
      valor = compareByValue(x,y)
            if valor == true
            return true
            else
            return false
            end
      end
 end

 compareByValueAndSuit("2♠", "A♠")
 compareByValueAndSuit("K♥", "10♥")
 compareByValueAndSuit("10♠", "10♥")
 compareByValueAndSuit("A♠", "2♥")
 insercao(["10♥", "10♦", "K♠", "A♠", "J♠", "A♠"])
