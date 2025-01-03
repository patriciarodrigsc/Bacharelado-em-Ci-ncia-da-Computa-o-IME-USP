function palindromo(x)
 a = sizeof(x)
 div = 0
 b = 0
 meio = 0
 v = []
 meio = div(a,2)
   for i in 1:a
    b = SubString(x, i, i)
    v[i] = b
   end
    if v[i] == v[a]
      resposta = true
      a = a - 1
    else
      return false
    end
end

palindromo("arara")


function palindromos(x)
a = sizeof(x)
resposta = 0
meio = div(a,2)
v = Array{Union{Nothing, String}}(nothing, a)
  for i in 1:a
    v[i] = SubString(x,i,i)
  end
  for i in 1:meio
    if v[i] == v[a]
      a = a - 1
      resposta = true
    else
      return false
    end
  end
  return resposta
end


using Test
function verifica ()

palindromos("arara") == true
palindromos("ovo") == true
palindromos("MiniEP11") == false
palindromos("socorrammesubinoonibusemmarrocos") == true

println("final dos testes")

end


verifica()
