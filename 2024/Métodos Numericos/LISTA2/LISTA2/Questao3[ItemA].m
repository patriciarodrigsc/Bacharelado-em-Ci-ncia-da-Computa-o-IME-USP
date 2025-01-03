num_pontos = 161;
limite_inferior = 1.921;
limite_superior = 2.08;
vetor = linspace(limite_inferior, limite_superior, num_pontos);

% Função de Horner
function y = horner(coefs, x)
    n = length(coefs);
    y = coefs(1);
    for i = 2:n
        y = y * x + coefs(i);
    end
end

% Método de Horner
coefs_horner = [1 -18 144 -672 2016 -4032 5376 -4608 2304 -512]; % Coeficientes do polinômio
resultado_horner = zeros(1, num_pontos);
for i = 1:num_pontos
    x = vetor(i);
    resultado_horner(i) = horner(coefs_horner, x) - horner(coefs_horner, 2);
end

% Método de cálculo direto
resultado_direto = (vetor - 2).^9;

% Plotando os resultados
figure(1);
plot(vetor, resultado_horner, 'r');
title('Método de Horner');
xlabel('x');
ylabel('f(x)');

figure(2);
plot(vetor, resultado_direto, 'b');
title('Cálculo Direto');
xlabel('x');
ylabel('f(x)');

% Salvando as figuras
saveas(figure(1), 'grafico---Metodo_de_Horner.png');
saveas(figure(2), 'grafico---Calculo_Direto.png');

% Comentários adicionados ao código explicando as diferenças entre os métodos.
% O método de Horner é mais preciso que o cálculo direto, especialmente para polinômios de alto grau,
% porque evita o cancelamento numérico, que ocorre quando subtrair números muito próximos causa perda de dígitos significativos.
% O método de Horner divide a avaliação do polinômio em uma série de operações de multiplicação e adição,
% evitando subtrações próximas que levam ao cancelamento numérico, resultando em resultados mais precisos.
