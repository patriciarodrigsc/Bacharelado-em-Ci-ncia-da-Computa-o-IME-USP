coefs_horner = [1 -18 144 -672 2016 -4032 5376 -4608 2304 -512];


% Function to evaluate the polynomial using Horner's method
function y = horner(coefs, x)
    n = length(coefs);
    y = coefs(1);
    for i = 2:n
        y = y * x + coefs(i);
    end
end

% Function to evaluate the polynomial directly
function y = f_direto(x)
    y = (x - 2).^9;
end

% Main function to find roots using bisection method for both Horner and direct polynomial evaluation
function [p_horner, n_horner, p_direto, n_direto] = bisseccao_polinomio(coefs, a, b, atol)
    fa = horner(coefs, a) - horner(coefs, 2);
    fb = horner(coefs, b) - horner(coefs, 2);
    n = ceil(log2(b - a) - log2(2 * atol));

    % Method of bisection for Horner's method
    for k = 1:n
        p_horner = (a + b) / 2;
        fp = horner(coefs, p_horner) - horner(coefs, 2);
        if fa * fp < 0
            b = p_horner;
            fb = fp;
        else
            a = p_horner;
            fa = fp;
        end
    end
    p_horner = (a + b) / 2;
    n_horner = k;

    % Method of bisection for direct calculation
    a = 1.921;
    b = 2.08;
    fa = f_direto(a);
    fb = f_direto(b);

    for k = 1:n
        p_direto = (a + b) / 2;
        fp = f_direto(p_direto);
        if fa * fp < 0
            b = p_direto;
            fb = fp;
        else
            a = p_direto;
            fa = fp;
        end
    end
    p_direto = (a + b) / 2;
    n_direto = k;
end

% Call your main function
a = 1.921;
b = 2.08;
atol = 1e-6;


[p_horner, n_horner, p_direto, n_direto] = bisseccao_polinomio(coefs_horner, a, b, atol);

fprintf('Raiz encontrada pelo método de Horner: %.8f após %d iterações.\n', p_horner, n_horner);
fprintf('Raiz encontrada pelo método de cálculo direto: %.8f após %d iterações.\n', p_direto, n_direto);


% Comentário diferencas encontradas: 
% Ambos os métodos convergiram para raízes próximas em apenas 17 iterações, 
% sugerindo sua eficácia para encontrar raízes dentro do intervalo com a precisão 
% especificada (atol = 1e-6). A pequena discrepância entre as raízes pode ser 
% atribuída a erros de arredondamento, pois o metodo do calculo direto calcula a subtracao de numeros muito proximos.
% 1.98 - 2 ... 2.08 - 2. Nesses casos x e x˜ sao muito proximos, algo que pode levar a erros de cancelamento