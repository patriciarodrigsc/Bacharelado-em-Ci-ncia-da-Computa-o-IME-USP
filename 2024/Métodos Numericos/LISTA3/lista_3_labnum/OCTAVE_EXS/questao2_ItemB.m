x_pontos = [0, 1, 3];
y_pontos = [1, 0.9, 0.5];
z_log = log(y_pontos);

function dif_dividida = calcularDiferencaDividida(x_pontos, z_log, i, j)
    if i == j
        dif_dividida = z_log(i);
    else
        dif_dividida = (calcularDiferencaDividida(x_pontos, z_log, i+1, j) - calcularDiferencaDividida(x_pontos, z_log, i, j-1)) / (x_pontos(j) - x_pontos(i));
    end
end

% Interpolação de Newton
function v = interpolacaoNewton(x_pontos, x_valor, dif_div)
    n = length(x_pontos);
    v = dif_div(1);
    termo_multiplicativo = 1;
    
    for j = 2:n
        termo_multiplicativo = termo_multiplicativo * (x_valor - x_pontos(j-1));
        v = v + dif_div(j) * termo_multiplicativo;
    end
end

% CalculaNDO as diferenças divididas
n = length(x_pontos);
diferencas_divididas = zeros(1, n);
for j = 1:n
    diferencas_divididas(j) = calcularDiferencaDividida(x_pontos, z_log, 1, j);
end

x = linspace(0, 6, 400);
v = arrayfun(@(x_valor) interpolacaoNewton(x_pontos, x_valor, diferencas_divididas), x); %calcula v(x) usando newton
u = exp(v);  %u(x) = e^v(x)
figure;
plot(x, u, 'b-', 'DisplayName', 'Interpolação u(x)');
hold on;
scatter(x_pontos, y_pontos, 'r', 'filled', 'DisplayName', 'Pontos');
xlabel('x');
ylabel('u(x)');
title('Plot para u(x) = e^{v(x)}');
legend('show');
grid on;
hold off;

% Imprimindo coeficientes γ_i
gamma_coeficientes = diferencas_divididas;
disp('Coeficientes γ_i:');
disp(gamma_coeficientes);

% Característica qualitativa diferente 
disp('Característica qualitativa do gráfico:');
disp('A curva mostra um decaimento rápido, o que é típico de uma função exponencial,');
disp('em contraste com uma função quadrática que varia de forma mais gradual.');
