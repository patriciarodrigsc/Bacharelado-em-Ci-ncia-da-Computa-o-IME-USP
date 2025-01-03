function xenc = enc(x,N)
  e =  floor(log10(abs(x)))+1-N;
  m = round(x*10^(-e));
  xenc = [m e];
endfunction

function x = dec(xenc)
  x = xenc(1)*10^xenc(2);
endfunction

% Implementação direta
function soma_direta = soma_direta()
    soma_direta = 0;
    for n = 1:100000
        soma_direta +=  1/n;
    end
end

% Usando arredondamento para 5 casas decimais (enc e dec)
function soma_arredondada = soma_arredondada()
    soma_arredondada = 0;
    for n = 1:100000
        soma_arredondada +=  dec(enc(1/n, 5));
    end
end

% Usando arredondamento para 5 casas decimais na ordem inversa dos termos
function soma_inversa_arredondada = soma_inversa_arredondada()
    soma_inversa_arredondada = 0;
    for n = 100000:-1:1
        soma_inversa_arredondada += dec(enc(1/n, 5));
    end
end

% Resultados
resultado_direto = soma_direta();
resultado_arredondado = soma_arredondada();
resultado_inverso_arredondado = soma_inversa_arredondada();

% Mostrar resultados
disp(['Resultado direto: ' num2str(resultado_direto)]);
disp(['Resultado arredondado: ' num2str(resultado_arredondado)]);
disp(['Resultado inverso arredondado: ' num2str(resultado_inverso_arredondado)]);



%Comentário: diferencas observadas entre as diferentes funcoes

#{
% Os resultados mostram que a soma direta é ligeiramente diferente das somas arredondadas, com diferenças na ordem de 0.0001. Isso ocorre devido à perda de precisão introduzida pelo arredondamento. A soma inversa arredondada produz um resultado semelhante à soma arredondada, sugerindo que a ordem dos termos não afeta significativamente a precisão quando se trata de arredondamento.
#}