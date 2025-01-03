1;
function calculateError(originalImg, decompressedImg) 
  imgoriginal=imread(originalImg);
  imgdescomprimida=imread(decompressedImg);
  
  origR = double(imgoriginal(:, :, 1));  #vermelho da originalImg
  origG = double(imgoriginal(:, :, 2));  #verde da originalImg
  origB = double(imgoriginal(:, :, 3));  #azul da originalImg
  decR = double(imgdescomprimida(:, :, 1)); #vermelho da decompressedImg
  decG = double(imgdescomprimida(:, :, 2)); #verde da decompressedImg
  decB = double(imgdescomprimida(:, :, 3)); #azul da decompressedImg
 
  #calculo dos erros
  errR = (norm(origR-decR))/(norm(origR)); #vermelho
  errG = (norm(origG-decG))/(norm(origG)); #verde
  errB = (norm(origB-decB))/(norm(origB)); #azul
   
  display((errR + errG + errB)/3); 
endfunction


calculateError('dog.jpeg','decompressed.png');
