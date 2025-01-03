function fat(num)
      if num == 0 || num == 1
          return 1
      else
          return num * fat(num - 1)
      end
end


function sen(x)
sen = 0
n = 1
alt = 1

  for i in 1:10
    sen += alt * (x^(n)/fat(n))
      n  = n + 2
    alt = alt * (-1)
  end
    return sen
end

function cos(x)
cos = 0
n = 0
alt = 1

  for i in 1:10
    cos += alt * (x^(n)/fat(n))
      n  = n + 2
    alt = alt * (-1)
  end

    return cos
end

function bernoulli(n)
 n *= 2
 A = Vector{Rational{BigInt}}(undef, n + 1)
   for m = 0 : n
      A[m + 1] = 1 // (m + 1)
      for j = m : -1 : 1
            A[j] = j * (A[j] - A[j + 1])
      end
   end

   return abs(A[1])
end

function tan(x)
tan = 0
n = 1
B = 0
  for i in 1:10
  B = bernoulli(n)
    tan += (2^(2 * n) * (2^(2 * n) - 1) * B * x^((2 * n) - 1))/fat(2 * n)
    n += 1
  end
    return tan
end

function quaseigual(v1,v2)
erro = 0.0001
  igual = abs(v1 - v2)
    if igual <= erro
      return true
    else
      return false
    end
end


