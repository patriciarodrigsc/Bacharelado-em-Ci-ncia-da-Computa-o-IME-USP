function confereQuadrada(m)
  a = size(m)
  if length(a) != 2 || a[1] != a[2]
    return false
  else
    return true
  end
end

function somaMatriz(m)
a = size(m)
soma = 0
    for i in 1:a[1]
      for j in 1:a[2]
        soma = soma + m[i, j]
      end
    end
  return soma
end

function imprimeMatriz(m)
a = size(m)
soma = 0
  for i in 1:a[1]
    for j in 1:a[2]
      print(" m[", i, ", ", j, "] = ", m[i,j])
    end
  println()
  end
end



function  max_sum_submatrix(matrix)
a = size(matrix)
box = zeros(a[1],a[2])
somaBox = somaMatriz(box)
soma = 0

    if confereQuadrada(matrix) == true

      for coluna in 1:a[2]
        for i in 1:a[1]
          for j in coluna:a[2]
            soma += matrix[i,j]
          end
        end
        if soma > somaBox
          for coluna in 1:a[2]
            for i in 1:a[1]
              for j in coluna:a[2]
                box[i,j] = matrix[i,j]
              end
            end
          end
        end
      end


      for linha in 1:a[2]
        for i in 1:a[1]
          for j in linha:a[2]
            soma += matrix[i,j]
          end
        end
        if soma > somaBox
          for linha in 1:a[2]
            for i in 1:a[1]
              for j in linha:a[2]
                box[i,j] = matrix[i,j]
              end
            end
          end
        end
      end

      imprimeMatriz(box)
    else
    println("Matriz não é quadrada")
  end
end


max_sum_submatrix([1 2 3; 4 5 6; 7 8 9])
