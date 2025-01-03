using Test

function verifica()

    @test matrix_pot([1 2; 4 5], 2) == [1 2; 4 5] * [1 2; 4 5]
    @test matrix_pot([4 8 0 4 ; 8 4 9 6 ; 9 6 4 0 ; 9 5 4 7], 7) == [4 8 0 4 ; 8 4 9 6 ; 9 6 4 0 ; 9 5 4 7] * [4 8 0 4 ; 8 4 9 6 ; 9 6 4 0 ; 9 5 4 7] * [4 8 0 4 ; 8 4 9 6 ; 9 6 4 0 ; 9 5 4 7] * [4 8 0 4 ; 8 4 9 6 ; 9 6 4 0 ; 9 5 4 7] * [4 8 0 4 ; 8 4 9 6 ; 9 6 4 0 ; 9 5 4 7] * [4 8 0 4 ; 8 4 9 6 ; 9 6 4 0 ; 9 5 4 7] * [4 8 0 4 ; 8 4 9 6 ; 9 6 4 0 ; 9 5 4 7]
    @test matrix_pot([1 2; 4 5], 3) == [1 2; 4 5] * [1 2; 4 5] * [1 2; 4 5]
     println ("Final dos testes")
end

function multiplica(a, b)
  dima = size(a)
  dimb = size(b)
  if dima[2] != dimb[1]
    return -1
  end
  c = zeros(dima[1], dimb[2])
  for i in 1:dima[1]
    for j in 1:dimb[2]
        for k in 1:dima[2]
            c[i, j] = c[i, j] + a[i, k] * b[k, j]
        end
    end
end
 return c
end

function matrix_pot(a, b)
resultado = a
    for i 1:b - 1
      resultado = multiplica(resultado, a)
    end
end

verifica()
