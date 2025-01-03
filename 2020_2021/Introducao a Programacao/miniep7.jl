function fat(num)
      if num == 0 || num == 1
          return 1
      else
          return num * fat(num - 1)
      end
end

fat(2)
fat(4)
fat(6)

#funçãoseno
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

sen(0)
sen(pi/6)
sen(pi/4)
sen(pi/3)
sen(pi/2)

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

cos(0)
cos(pi/6)
cos(pi/4)
cos(pi/3)
cos(pi/2)


quaseigual(sen(0), 0)
quaseigual(sen(pi/6), 1/2)
quaseigual(sen(pi/4), sqrt(2)/2)
quaseigual(sen(pi/3), sqrt(3)/2)
quaseigual(sen(pi/2), 0)

#funçãocosseno
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

cos(0)
cos(pi/6)
cos(pi/4)
cos(pi/3)
cos(pi/2)


quaseigual(cos(0), 0)
quaseigual(cos(pi/6), sqrt(3)/2)
quaseigual(cos(pi/4), sqrt(2)/2)
quaseigual(cos(pi/3), 1/2)
quaseigual(cos(pi/2), 0)

#Funçãotangente
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


#testes
function quaseigual(v1,v2)
erro = 0.0001
  igual = abs(v1 - v2)
    if igual <= erro
      return true
    else
      return false
    end
end

tan(0)
tan(pi/6)
tan(pi/4)
tan(pi/3)
tan(pi/2)

quaseigual(tan(0), 0)
quaseigual(tan(pi/6), sqrt(3)/3)
quaseigual(tan(pi/4), 1)
quaseigual(tan(pi/3), sqrt(3))


