#inicializar os valores dos parametros
originalImg='';
k=0;
function compress(originalImg, k)
  A=imread(originalImg);
  [x,y,z] = size(A);
  n = (x+k)/(k+1);
  m = (y+k)/(k+1);
  if(0==mod(x+k, k+1) & 0==mod(y+k,k+1))
    imgcomprimida = zeros(n,m,z);
    for h=1:z
        for i=1:n
            for j=1:m
                      imgcomprimida(i, j, h) = A(1+(i-1)*(k+1), 1+(j-1)*(k+1), h); 
            endfor
        endfor
    endfor
    imwrite(uint8(imgcomprimida), "compressed.png"); 
  else
    display("Não foi possível comprimir a imagem. Digite outro valor para k.");
  endif
endfunction

compress('dog.jpeg',1);

   