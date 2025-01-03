x_pontos = [0, 0.5, 1];

function y = f(x)
    y = exp(x);
end

%  Lj
function term = calcular_Lj(x, j, xi)
    n = length(xi);
    term = 1.0;
    for k = 1:n
        if k ~= j
            term = term .* (x - xi(k)) / (xi(j) - xi(k));
        end
    end
end

% polinômio interpolador P(x)
function px = calcular_Px(x, x_pontos, vec_y)
    m = length(x); 
    n = length(x_pontos); 
    px = zeros(m, 1); 

    for i = 1:m
        sum_term = 0;
        for j = 1:n
            sum_term = sum_term + vec_y(j) * calcular_Lj(x(i), j, x_pontos);
        end
        px(i) = sum_term;
    end
end


vec_y = f(x_pontos);
x = linspace(0, 1, 100)';
p_x = calcular_Px(x, x_pontos, vec_y);

exact_y = f(x);
erro = abs(exact_y - p_x);

% escala logarítmica
figure;
semilogy(x, erro, 'b', 'DisplayName', '|e_x - p(x)|');
hold on;
grid on;

% erro máximo
erro_maximo = exp(1) * sqrt(3) / 216;
semilogy(x, erro_maximo * ones(size(x)), 'm--', 'DisplayName', 'Erro Máximo (e*sqrt(3)/216)');

xlabel('x');
ylabel('|Erro|');
title('Magnitude do Erro |e_x - p(x)| em Escala Logarítmica - Pontos conhecidos');
legend('show'); 
hold off;

% Comentario
fprintf('Podemos ver que o gráfico do erro em escala logarítmica não ultrapassa o erro máximo (e_max = e*sqrt(3)/216) calculado no item a.\n');
