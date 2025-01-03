x = randi([1, 10000], 1, 30);

n = length(x);
x_tilde = sum(x) / n;

DP_squared = 0;
for i = 1:n
    DP_squared = DP_squared + (x(i) - x_tilde)^2;
end
DP_squared = DP_squared / n;

DP_squared_alternative = 0;
for i = 1:n
    DP_squared_alternative = DP_squared_alternative + (x(i)^2 - x_tilde^2);
end
DP_squared_alternative = DP_squared_alternative / n;


fprintf('DP^2 = %.10f\n', DP_squared);
fprintf('DP^2 alternativo = %.10f\n', DP_squared_alternative);

% comentaio: A abordagem alternativa, que calcula a variância como a média dos quadrados dos elementos menos o quadrado da média, pode ser mais suscetível a erros de cancelamento numérico. Isso ocorre porque quando os valores dos dados são grandes, os termos "x(i)^2" e "x_tilde^2" podem ser muito maiores que suas diferenças, resultando em perda significativa de precisão ao subtrair esses valores.