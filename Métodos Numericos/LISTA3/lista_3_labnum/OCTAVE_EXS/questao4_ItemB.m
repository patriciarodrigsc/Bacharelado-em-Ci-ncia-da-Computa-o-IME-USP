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

% Plot
figure;
plot(x, f(x), 'r', 'DisplayName', 'e^x');
hold on;
plot(x, p_x, 'b--', 'DisplayName', 'Polinômio Interpolador p(x)');

legend;
xlabel('x');
ylabel('y');
title('Interpolação de Lagrange para e^x');
hold off;

