function [p, n] = curt1(a, epsilon)
    if a <= 0
        disp('O valor de ''a'' deve ser maior que zero.');
        p = NaN;
        n = NaN;
        return;
    end
    
    if a <= 1
        intervalo = [a, 1];
    else
        intervalo = [1, a];
    end
    
    n = ceil(log2(intervalo(2) - intervalo(1)) - log2(2 * epsilon));
    
    for k = 1:n
        p = (intervalo(1) + intervalo(2)) / 2;
        fp = p^3 - a;
        
        if fp * (intervalo(1)^3 - a) < 0
            intervalo(2) = p;
        else
            intervalo(1) = p;
        end
    end
    
    p = (intervalo(1) + intervalo(2)) / 2;
end

function resultado = g(x, a)
    resultado = x - x^3 + a;
end

function [raiz_cubica, iter] = curt2(x0, a, epsilon, max_iter)
    x = x0;
    for iter = 1:max_iter
        x_next = g(x, a);
        if abs(x_next - x) < epsilon
            raiz_cubica = x_next;
            return;
        end
        x = x_next;
    end
    raiz_cubica = x;
end

function [x, num_iter] = curt3(a, epsilon, M)
    % Aproximação inicial usando a primeira ordem de Taylor
    x = (a + 2) / 3;
    
    % Número de iterações necessárias (aproximado)
    % O número de iterações é aproximadamente dado por log(M * (x - x_star)^2 / epsilon) / log(M)
    % onde x_star é a raiz cúbica de 3 e M é a constante de convergência quadrática
    num_iter = log(M * ((x ^ 3) - a) / epsilon) / log(M);
    
    % Iterações do método de Newton
    for i = 1:ceil(num_iter)
        x = x - (x ^ 3 - a) / (3 * (x ^ 2));
    end
end



a = 3; 
epsilon = 1e-6; 

disp("========================== Método Bisseccao ==============================")
[p, n] = curt1(a, epsilon);

disp(['Raiz cúbica de ', num2str(a), ' aproximada: ', num2str(p)]);
disp(['Número de iterações: ', num2str(n)]);

disp("========================== Método Ponto Fixo ==============================");
x0 = -0.5; % Novo valor inicial
max_iter = 1000; % Limite de iterações
epsilon = 1e-6; % Tolerância
a = 0.2; % Valor de a (de acordo com o contexto do problema)
[p, n] = curt2(x0, a, epsilon, max_iter);
disp(['x0: ', num2str(x0)])
disp(['a: ', num2str(a)])
disp(['Raiz cúbica de ', num2str(a), ' aproximada: ', num2str(p)]);
disp(['Número de iterações: ', num2str(n)]);



% Comentário: Escrevi no papel as contas que explicam para quais valores de x e consequentemente de a o metodo garante convergencia
% Resultado para alguns testes: 
% ========================== Método Ponto Fixo ==============================
% x0: 0.5
% a: 0.2
% Raiz cúbica de 0.2 aproximada: 0.5848
% Número de iterações: 5

% ========================== Método Ponto Fixo ==============================
% x0: -0.5
% a: 0.2
% Raiz cúbica de 0.2 aproximada: 0.5848
% Número de iterações: 10

disp("========================== Método de Newton ==============================");
% Exemplo de uso:
a = 0.2;
epsilon = 1e-6;
M = 2;  % Suponha que M seja 2 para fins de exemplo

[raiz_cubica_de_3, num_iter] = curt3(a, epsilon, M);
disp(["Raiz cúbica de 3: ", num2str(raiz_cubica_de_3)]);
disp(['Número de iterações: ', num2str(num_iter)]);




