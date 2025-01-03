//##############################
//#                            #
//#   Nome: Patrícia da Silva Rodrigues      #
//#   NUSP: 11315590   #
//#   Descrição de Funções:    #
//#
//#   FUNCAO MAIN():         #
//#   - Na main, gero a cena inicial (mosquitos, inseticidas e bico do inseticida).        
//#   - Adiciono os eventos que podem ocorrer por cliques do usuário.                      
//#   - Bico: Movimenta o ângulo do bico do inseticida usando i e k para cima e para baixo, sem ultrapassar os ângulos permitidos.  #
//#   - Inseticida: Altera a altura do inseticida com j e l, sem ultrapassar as alturas permitidas.  #
//#   - Barra de velocidade: Mapeamento de 1 até 10 para o intervalo de 0.001 e 0.003.        
//#   - Configuração de executar/pausar que habilita e desabilita o botão passo.              
//#   - Passo: Move a cena por 0.1 segundos e imprime informações sobre a cena.               
//#   - Chama a função loopAnimation() responsável por manter a animação em loop.             
//#                            #
//#   FUNÇÃO animarMosquito():                                                         #
//#   - Movimenta todos os retângulos que representam o mosquito seguindo uma           #
//#     movimentação browniana, que é a movimentação que os mosquitos descrevem que     #
//#     leva a pequenas perturbações em suas posições. Isso causa a sensação de que      #
//#     de fato se movem como mosquitos. É uma simulação.                                #
//#   - Gera-se um número aleatório e a partir dele calcula-se um deltaX e deltaY que     #
//#     serão pequenos, pois é uma oscilação apenas.                                      #
//#   - Verifica se algum dos vértices de todos os mosquitos colidiu com as dimensões    #
//#     da borda. Caso tenham colidido, eles sofrem um pequeno recuo em sua posição.     #
//#   FUNÇÃO animarBolha():                                                           #
//#   - Calcula o deltaT que é a variação de tempo desde o início da movimentação da bolha.    #
//#     Esse deltaT aumenta em 0.1 a cada frame.                                        #
//#   - Usando as equações da cinemática do movimento de projétil/movimento oblíquo,       #
//#     calculamos a velocidade em y (vy) que descreverá o movimento retilíneo uniformemente  #
//#     variado em y. Em x, a velocidade vx permanece constante (em x o movimento é MRU).   #
//#   - É possível observar também que o sinal da velocidade muda quando a bolinha está    #
//#     subindo e descendo. Quando ela está subindo, vai perdendo velocidade devido à ação #
//#     da gravidade. Quando atinge sua altura máxima (vy = 0), ela começa a cair e ganha  #
//#     velocidade novamente.                                                            #
//#   - Calcula as posições de todos os vértices que aproximam a bolinha seguindo a       #
//#     equação horária do movimento retilíneo uniformemente variado (em y) e a equação   #
//#     horária do movimento retilíneo uniforme (em x).                                  #
//#   - Verifica se a bolinha colidiu com o chão. Calcula o alcance máximo inicialmente   #
//#     e quando a posição em x da bolha atinge o alcance máximo e a posição em y da      #
//#     bolha ultrapassa a altura do inseticida (nesse caso, ela ficará negativa ao       #
//#     ultrapassar a posição em y inicial), a bolinha é eliminada da cena e o estado dela #
//#     e todas as suas variáveis são reiniciados usando a função reinicializaBolha().     #
//#     Caso isso ainda não tenha ocorrido, é verificado se ela colidiu com algum         #
//#     mosquito usando a função verificaColisaoBolhaMosca().                             #
//#   FUNÇÃO verificaColisaoBolhaMosca():                                               #
//#   - Para cada mosca, verifica se algum de todos os seus vértices está a uma distância  #
//#     muito baixa da mosca. Caso esteja, ocorre uma colisão. Para isso, é guardado o    #
//#     índice i da mosca do vetor de moscas e a bolha é reinicializada. Em seguida, é     #
//#     interrompido o loop com um break e a mosca é removida do vetor de moscas (gaRetangulo).#
//#   FUNÇÃO desenheAnimacao():                                                          #
//#   - Esta função inicialmente chama a função que anima as moscas. Em seguida, caso o    #
//#     tiro esteja sendo dado, chama a função que anima o tiro também.                  #
//#   - Posteriormente, desenha todos os vetores atualizados que descrevem os objetos da  #
//#     cena. Usando o pincel, desenha-os usando o bufferData e o drawArrays.             #
//#   FUNÇÃO loopAnimacao():                                                             #
//#   - Esta função chama a função requestAnimationFrame e, caso o desenho não esteja     #
//#     pausado, ela chama a função desenheAnimacao().                                   #
//#   FUNÇÃO geraRetangulos():                                                           #
//#   - Esta função gera n retângulos em posições aleatórias e guarda seus vértices no   #
//#     vetor gaRetangulos. Esses retângulos representam as moscas.                       #
//#   FUNÇÃO geraInseticida():                                                           #
//#   - Esta função gera o retângulo do inseticida e o triângulo do seu bico também. Para #
//#     gerar o corpo, ela usa as variáveis de largura e altura atuais do inseticida (que #
//#     começam como a altura máxima). O retângulo que gera o bico é feito usando como    #
//#     referência as dimensões do corpo (pois o bico está preso nele), bem como a bolinha#
//#     usa como referência o bico. Assim, quando um atualiza, todos atualizam. O         #
//#     triângulo que descreve o bico é rotacionado usando a função gira, que faz uma     #
//#     rotação em um dado ângulo. Essa rotação é modificada pelo usuário.                #
//#   FUNÇÃO geraCirculo():                                                               #
//#   - Esta função é responsável por gerar a bolinha que sai do bico. Ela aproxima um    #
//#     círculo através de um polígono de 20 lados e salva os vértices que descrevem a    #
//#     bolha.                                                                          #
//##############################




"use strict";

var gl;
var gCanvas;
var gsVertexShaderSrc;
var gsFragmentShaderSrc;

//mosquito constantes
const ALT_DENGUE = 0.1;
const LAR_DENGUE = 0.15;
const MAX_VEL_DENGUE = 0.05;
const COR_DENGUE = [0.5, 0.3, 0.2, 1];
const BORDA = 0.15;

//constantes inseticida
const BICO_INSETICIDA = 0.075;
const LAR_INSETICIDA = 0.05;
const ALT_MIN_INSETICIDA = 0.25;
const ALT_MAX_INSETICIDA = 0.75;
var  ALT_ATUAL_INSETICIDA = 0.75;
const ANG_MIN_INSETICIDA = -35;
const ANG_MAX_INSETICIDA = 75;
const COR_INSETICIDA_BASE = [0, .7, .9, 1];
const COR_INSETICIDA_PARAFUSO = [0, 0.2, 0.5, 1];
const COR_INSETICIDA_BICO = [0, 0.8, 1, 1];
const ALT_PASSO = 0.02;
const ANG_PASSO = 2;


//mosquitos
let gaRetangulos = [];
let gaInseticida = [];
let gaBicoInseticida = [];
let gaBolha = []
var gaCirculo = [];
let gaOlhos = [];
let gaAsinhas = [];

//constantes bolha
var ACIONOU = false;
let nTiros = 0;
let graus = 0;
let theta = graus * Math.PI / 180;
var v0_bolha = 0.2;
let v0x_bolha = v0_bolha * Math.cos(theta);
let v0y_bolha = v0_bolha * Math.sin(theta);
let vy_bolha = v0y_bolha;
let vx_bolha = v0x_bolha;
let pos0X_bolha;
let pos0Y_bolha;
let posX_bolha;
let posY_bolha;
let deltaT = 0.1;
let g = 0.01;
let y_max = Math.pow(v0y_bolha, 2) / (2 * g);
let alcance_maximo = Math.pow(v0y_bolha, 2) / g;
const rangeInput = document.getElementById('bVel');
let raioBolha = 0.02;
let colidiuBolhaMosca = false;

// Obtém uma referência para o botão
const bRunButton = document.getElementById('bRun');
var cliqueEmPasso = false;

let animationPaused = false;
let animationTimer = null;



const bStepButton = document.getElementById('bStep');


window.onload = main;

function main() {
  gCanvas = document.getElementById("glcanvas");
  gl = gCanvas.getContext('webgl2');
  if (!gl) alert("WebGL 2.0 isn't available");
  console.log(`Canvas: ${gCanvas.width} x ${gCanvas.height}`);
  crieShaders();
  geraRetangulos();
  geraInseticida();
  geraCirculo();

  // EVENTOS DE CLIQUES E MANIPULACOES NA CENA PELO USUARIO
  //atira
  document.addEventListener('keydown', function (event) {
    // Verifica se a tecla pressionada é a tecla "T" (código 84)
    if (event.keyCode === 84) {
      // Chama a função animaTiro
      ACIONOU = true;
      console.log("Tiro");
      console.log("Tiro em " + pos0X_bolha + "   " + pos0Y_bolha +  "   0 ");
    }
  });

  //MOVER O BICO 
  document.addEventListener('keydown', function (event) {
    // Verifica se a tecla pressionada é uma das teclas "l" para subir e "k" para descer
    if (event.keyCode === 74 ) {
      if (graus < ANG_MAX_INSETICIDA) {
        graus += 2;
        console.log("Tecla esq - roda anti horario");
        console.log("Novo angulo:" + graus); 
      }

    //verifica se  "l" ou "j"
    } else if (event.keyCode === 76){{
      if (graus > ANG_MIN_INSETICIDA){
          graus -= 2;
        console.log("Tecla dir - roda horario");
          console.log("Novo angulo:" + graus); 
      }
    }}
    //atualiza inseticida e tiro
    theta = graus * Math.PI / 180;
    v0x_bolha = v0_bolha * Math.cos(theta);
    v0y_bolha = v0_bolha * Math.sin(theta);
    gaInseticida = []; //apaga inseticida que ja estava la 
    gaBicoInseticida = [];
    geraInseticida();
  });
  // Defina ALT_ATUAL_INSETICIDA e ALT_MAX_INSETICIDA conforme necessário

  document.addEventListener('keydown', function (event) {
    // Verifica se a tecla pressionada é uma das teclas "i", "k"
    if (event.keyCode === 73) { // Tecla "i"
      if (ALT_ATUAL_INSETICIDA < ALT_MAX_INSETICIDA) {
        ALT_ATUAL_INSETICIDA += 0.1;
        console.log("Nova Altura: " + ALT_ATUAL_INSETICIDA);
      }else{
        console.log("Inceticida já está na altura máxima!!");
      }
    } else if (event.keyCode === 75) { // Tecla "k"
      if (ALT_ATUAL_INSETICIDA > ALT_MIN_INSETICIDA) {
        ALT_ATUAL_INSETICIDA -= 0.1;
        console.log("Nova Altura: " + ALT_ATUAL_INSETICIDA);
      }else{
        console.log("Inceticida já está na altura mínima!!");
      }
    }
    geraInseticida();
    geraCirculo();
  });
  

  rangeInput.addEventListener('input', function () {
    const newSpeed = parseFloat(this.value);

    // Mapeei o valor para o intervalo 0.01 - 0.03
    const mappedSpeed = 0.01 + (newSpeed - 1) * (0.03 - 0.01) / 9;

    // Atualiza a velocidade
    v0_bolha = mappedSpeed; //normalizei a velocidade no range (0.01 até 0.03 porque de 1 a 10 estava muuuito rapiso a bolha só sumia da cena)
    v0x_bolha = v0_bolha * Math.cos(theta);
    v0y_bolha = v0_bolha * Math.sin(theta);
    vy_bolha = v0y_bolha;
    vx_bolha = v0x_bolha;
    console.log("Nova velocidade:", newSpeed);
  });


  // EVENTO PAUSAR E EXECUTAR
  bRunButton.addEventListener('click', function () {
    // Se a animação estiver pausada, despausa e atualiza o texto do botão
    if (animationPaused) {
      animationPaused = false;
      bRunButton.value = "Pausar"; // Altera o texto do botão
      bStepButton.value = ""; // Adiciona "Passo" ao botão de step
      bStepButton.disabled = true;
      console.log("Pausado: " + animationPaused);
    } else { // Se a animação estiver em execução, pausa e remove o texto do botão de step
      animationPaused = true;
      bRunButton.value = "Executar";
      bStepButton.value = "Passo"; // Remove o texto do botão de step
      bStepButton.disabled = false;
      console.log("Pausado: " + animationPaused);
    }
  });

  // EVENTO PASSO 
  bStepButton.addEventListener('click', function () {
    cliqueEmPasso = true;
    // Define a animação como pausada caso esteja em execução
    if (animationPaused) {
      animationPaused = false;
      // Define um temporizador para parar a animação após 0.1 segundos
      setTimeout(function () {
        animationPaused = true;
      }, 100); // 100 milissegundos = 0.1 segundos
    }

    console.log("Clique em passo :"+ cliqueEmPasso);
    console.log("Passou 0.1 segundos");
    console.log("################# CENA ##################33");

    console.log("Inseticida: ");
    console.log("Altura: " + ALT_ATUAL_INSETICIDA + " Ang (graus): "+ graus);
    console.log("Tiro inseticida: ");
    console.log("Ligado: " + ACIONOU + " Numero de tiros: "+ nTiros);

    console.log("Mosquitos da dengue: ");

    for (let j = 0; j < gaRetangulos.length; j++){
        console.log(gaRetangulos[j]);
    }


    cliqueEmPasso = false;
  });


    loopAnimacao();

}

function crieShaders() {
  var program = makeProgram(gl, gsVertexShaderSrc, gsFragmentShaderSrc);
  gl.useProgram(program);
  var bufPosicoes = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, bufPosicoes);
  gl.bufferData(gl.ARRAY_BUFFER, flatten(gaRetangulos[0]), gl.STATIC_DRAW);
  var aPositionLoc = gl.getAttribLocation(program, "aPosition");
  let size = 2;
  let type = gl.FLOAT;
  let normalize = false;
  let stride = 0;
  let offset = 0;
  gl.vertexAttribPointer(aPositionLoc, size, type, normalize, stride, offset);
  gl.enableVertexAttribArray(aPositionLoc);
}



function animarMosquitos() {
  // Para cada retângulo
  for (let i = 0; i < gaRetangulos.length; i++) {
    let retangulo = gaRetangulos[i];

    // Calcular um único deslocamento aleatório para o retângulo
    let deltaX = (Math.random() - 0.5) * MAX_VEL_DENGUE;
    let deltaY = (Math.random() - 0.5) * MAX_VEL_DENGUE;

    let colidiuParede = false;
    let recuoX = 0;
    let recuoY = 0;

    // Para cada vértice do retângulo
    for (let j = 0; j < retangulo.length; j++) {
      // Aplicar o deslocamento ao vértice
      retangulo[j][0] += deltaX;
      retangulo[j][1] += deltaY;

      // Verificar se o vértice colidiu com as dimensões do canvas
      if (retangulo[j][0] < -1 + BORDA) {
        colidiuParede = true;
        recuoX = Math.max(recuoX, -retangulo[j][0] + (-1 + BORDA));
      }
      if (retangulo[j][0] > 1 - BORDA) {
        colidiuParede = true;
        recuoX = Math.min(recuoX, -retangulo[j][0] + (1 - BORDA));
      }
      if (retangulo[j][1] < -1 + BORDA) {
        colidiuParede = true;
        recuoY = Math.max(recuoY, -retangulo[j][1] + (-1 + BORDA));
      }
      if (retangulo[j][1] > 1 - BORDA) {
        colidiuParede = true;
        recuoY = Math.min(recuoY, -retangulo[j][1] + (1 - BORDA));
      }
    }

    // Se houve colisão com a parede, recuar o retângulo
    if (colidiuParede) {
      // Recuar o retângulo na direção oposta à parede em que colidiu
      for (let j = 0; j < retangulo.length; j++) {
        retangulo[j][0] += recuoX;
        retangulo[j][1] += recuoY;
      }
    }

  }
}


function animaBolha() {
  deltaT = deltaT + 0.1;

  if (posY_bolha < y_max) { // se a bolha está subindo
    vy_bolha = v0y_bolha - g * deltaT;

  } else { // se a bolha chegou na altura máxima ou está descendo
    vy_bolha = - v0y_bolha - g * deltaT;
  }

  // Para cada ponto da trajetória da bolha
  for (let i = 0; i < gaCirculo[0].length; i++) {
    // Atualize as coordenadas de acordo com as velocidades
    gaCirculo[0][i][0] += v0x_bolha * deltaT;
    gaCirculo[0][i][1] += v0y_bolha * deltaT - (1 / 2) * g * Math.pow(deltaT, 2);
    posX_bolha = gaCirculo[0][i][0];
    posY_bolha = gaCirculo[0][i][1];

    // Verifica se a bolha atingiu as bordas do canvas (alcnace maximo do projétil + distancia até o chao em y)
    if (posX_bolha > alcance_maximo & posY_bolha <= -ALT_ATUAL_INSETICIDA) { //critério de parada
      reinicializaBolha();
      return;
    }
    verificaColisaoBolhaMosca(); // Verificar colisao mosca 
  }
}


function verificaColisaoBolhaMosca() {
  let obs = 0
  let deletar;
  let atingiu = false;
  for (let i = 0; i < gaRetangulos.length; i++) {
    const retangulo = gaRetangulos[i];
    // Loop através dos vértices do retângulo
    for (let j = 0; j < retangulo.length; j++) {
      // calcula distancia em x e y
      const distanciaX = Math.abs(retangulo[j][0] - posX_bolha);
      const distanciaY = Math.abs(retangulo[j][1] - posY_bolha);

      // verifica colisao
      if (distanciaX < LAR_DENGUE / 2 && distanciaY < ALT_DENGUE / 2) {
        atingiu = true;
        console.log("Acertou!! " + posX_bolha + "   " + posX_bolha);
        // Remover a mosca (retângulo) da cena
        deletar = i;
        reinicializaBolha();
        break;
      }
    }
  }

  if (atingiu) {
    gaRetangulos.splice(deletar, 1);
    atingiu = false;
  }
}

function reinicializaBolha() {
  // Limpa o array que armazena as coordenadas da bolha
  gaCirculo = [];

  // Reinicializa as variáveis da bolha
  ACIONOU = false;
  v0x_bolha = v0_bolha * Math.cos(theta);
  v0y_bolha = v0_bolha * Math.sin(theta);
  vy_bolha = v0y_bolha;
  vx_bolha = v0x_bolha;
  pos0X_bolha = 0;
  pos0Y_bolha = 0;
  posX_bolha = 0;
  posY_bolha = 0;
  deltaT = 0.1;
  y_max = 0; // Calcula a altura máxima alcançada
  alcance_maximo = 0;
  nTiros += 1;

  // coloca a bolha de volta no inseticida 
  geraCirculo();
}

function desenheAnimacao() {
  if (animationPaused == false) {
      // Limpar o buffer de tela
      gl.viewport(0, 0, gCanvas.width, gCanvas.height);
      gl.clearColor(1.0, 1.0, 1.0, 1.0); // Cor branca
      gl.clear(gl.COLOR_BUFFER_BIT);


      // Atualizar a posição dos retângulos (mosquitos)
      animarMosquitos();

      if (ACIONOU == true) {
        
        animaBolha();
      }

      // Desenhar o inseticida
      let offsetInseticida = 0;
      for (let i = 0; i < gaInseticida.length; i++) {
        let countInseticida = gaInseticida[i].length;
        gl.bufferData(gl.ARRAY_BUFFER, flatten(gaInseticida[i]), gl.STATIC_DRAW);
        gl.drawArrays(gl.LINE_LOOP, offsetInseticida, countInseticida);
      }

      //desenha bico inseticida
      for (let i = 0; i < gaBicoInseticida.length; i++) {
        let countBicoInseticida = gaBicoInseticida[i].length;
        gl.bufferData(gl.ARRAY_BUFFER, flatten(gaBicoInseticida[i]), gl.STATIC_DRAW);
        gl.drawArrays(gl.LINE_LOOP, offsetInseticida, countBicoInseticida);
      }

      // Desenhar todos os retângulos gerados (mosquitos)
      let tipoMosquito = gl.LINE_LOOP;
      let offsetMosquito = 0;
      for (let i = 0; i < gaRetangulos.length; i++) {
        let countMosquito = gaRetangulos[i].length;
        gl.bufferData(gl.ARRAY_BUFFER, flatten(gaRetangulos[i]), gl.STATIC_DRAW);
        gl.drawArrays(tipoMosquito, offsetMosquito, countMosquito);
      }

      //desenha disco 
      let tipoCirculo = gl.LINE_LOOP;
      let offsetCirculo = 0;
      for (let i = 0; i < gaCirculo.length; i++) {
        let countCirculo = gaCirculo[i].length;
        gl.bufferData(gl.ARRAY_BUFFER, flatten(gaCirculo[i]), gl.STATIC_DRAW);
        gl.drawArrays(tipoCirculo, offsetCirculo, countCirculo);
      }

    }
}


function loopAnimacao() {
  // Solicita o próximo quadro de animação
  requestAnimationFrame(loopAnimacao);

  // Se a animação não estiver pausada, desenha a animação
  if (!animationPaused) {
    desenheAnimacao();
  }
}



function geraRetangulos() {
  for (let i = 0; i < 20; i++) {
    let retangulo = [];

    // Escolher dois pontos aleatórios como vértices opostos do retângulo
    let x1 = Math.random() * 2 - 1;
    let y1 = Math.random() * 2 - 1;
    let x2 = x1 + LAR_DENGUE;
    let y2 = y1 + ALT_DENGUE;

    // Adicionar os vértices do retângulo ao array
    retangulo.push([x1, y1]);
    retangulo.push([x1, y2]);
    retangulo.push([x2, y2]);
    retangulo.push([x2, y1]);

    // Adicionar o retângulo gerado ao array de retângulos
    gaRetangulos.push(retangulo);
  }
}


function geraInseticida() {
  let inseticida = [];

  // Coordenadas do retângulo do inseticida
  let x1 = -1; // Canto inferior esquerdo em x
  let y1 = -1; // Canto inferior esquerdo em y
  let x2 = x1 + LAR_INSETICIDA; // Canto superior direito em x
  let y2 = y1 + ALT_ATUAL_INSETICIDA; // Canto superior direito em y

  // Adicionar os vértices do retângulo ao array
  inseticida.push([x1, y1]);
  inseticida.push([x1, y2]);
  inseticida.push([x2, y2]);
  inseticida.push([x2, y1]);

  // Adicionar o retângulo gerado ao array de inseticida
  gaInseticida.push(inseticida);

  // Gerando bico do inseticida 
  let bicoInseticida = [];

  // Adicionar vértices do triângulo do bico
  let x3 = x1 + LAR_INSETICIDA / 2; // Centralizado horizontalmente na largura do retângulo
  let y3 = y2 + BICO_INSETICIDA; // Altura do topo do retângulo mais a altura do bico
  bicoInseticida.push([x1, y2]); // Canto inferior esquerdo
  bicoInseticida.push([x2, y2]); // Canto inferior direito
  bicoInseticida.push([x3, y3]); // Ponto médio superior (vértice do triângulo)


  bicoInseticida = gira(bicoInseticida, 90 + graus);
  // Adicionar o triângulo do bico ao array de bicoInseticida
  gaBicoInseticida.push(bicoInseticida);
}

function geraCirculo() {
  // Gerando o círculo
  let bolha = [];

  // Número de pontos para aproximar o círculo usando poligono (quantidade de vertices)
  let numPontos = 20;

  // Definindo o centro do círculo como as coordenadas do terceiro vértice do triângulo gaBicoInseticida
  let centerX = gaBicoInseticida[0][2][0];
  let centerY = gaBicoInseticida[0][2][1];

  pos0X_bolha = centerX;
  pos0Y_bolha = centerY;

  // Calculando as coordenadas do círculo
  for (let i = 0; i < numPontos; i++) {
    let angle = (i / numPontos) * Math.PI * 2;
    let x = centerX + raioBolha * Math.cos(angle);
    let y = centerY + raioBolha * Math.sin(angle);
    bolha.push([x, y]);
  }

  gaCirculo.push(bolha);
}





//######## FUNCOES AUXILIARES #######
function gira(figura, ang) {
  var angRad = ang * Math.PI / 180; // Convertendo o ângulo para radianos
  var cosAng = Math.cos(angRad);
  var sinAng = Math.sin(angRad);
  var pontoReferencia = figura[figura.length - 1]; // Último ponto como ponto de referência
  var figuraGirada = [];

  for (var i = 0; i < figura.length - 1; i++) {
    var x = figura[i][0] - pontoReferencia[0]; // Translada para o ponto de referência
    var y = figura[i][1] - pontoReferencia[1]; // Translada para o ponto de referência
    var novoX = x * cosAng - y * sinAng; // Fórmula de rotação
    var novoY = x * sinAng + y * cosAng; // Fórmula de rotação
    figuraGirada.push([novoX + pontoReferencia[0], novoY + pontoReferencia[1]]); // Translada de volta
  }
  figuraGirada.push(pontoReferencia); // Adiciona o ponto de referência

  return figuraGirada;
}










// ========================================================
// Código fonte dos shaders em GLSL
// a primeira linha deve conter "#version 300 es"
// para WebGL 2.0

gsVertexShaderSrc = `#version 300 es

// aPosition é um buffer de entrada
in vec2 aPosition;

void main()
{
    // gl_Position é uma variável reservada que deve ser especificada
    gl_Position = vec4(aPosition, 0, 1);
}
`;

gsFragmentShaderSrc = `#version 300 es

// Define a precisão do FS.
precision highp float;

// Define a saída de cor
out vec4 fColor;

void main()
{
    // Defina a cor como preto
    fColor = vec4(0.0, 0.0, 0.0, 1.0);
}
`;


// ========================================================
// Rotinas auxiares
// Serão movidas para um arquivo webglUtils.js
// ========================================================
/**
 * cria o programa WebGL
 * @param {Obj} gl - contexto WebGL
 * @param {String} gsVertexShaderSrc - fonte do V Shader
 * @param {String} gsFragmentShaderSrc - fonte do F Shader
 * @returns - programa
 * 
 * Baseado em: https://webgl2fundamentals.org/webgl/lessons/webgl-fundamentals.html
 */
function makeProgram(gl, gsVertexShaderSrc, gsFragmentShaderSrc) {
  // Compilar e linkar os shaders
  var vertexShader = compile(gl, gl.VERTEX_SHADER, gsVertexShaderSrc);
  var fragmentShader = compile(gl, gl.FRAGMENT_SHADER, gsFragmentShaderSrc);
  var program = link(gl, vertexShader, fragmentShader);
  if (program) {
    return program;
  }
  alert("ERRO: na criação do programa.");
};

// ========================================================
/**
 * compila um shader
 * @param {Obj} gl - contexto WebGL
 * @param {*} type - gl.VERTEX_SHADER ou gl.FRAGMENT_SHADER
 * @param {*} source - código fonte
 * @returns - codigo compilado
 */

function compile(gl, type, source) {
  var shader = gl.createShader(type);
  gl.shaderSource(shader, source);
  gl.compileShader(shader);
  var deuCerto = gl.getShaderParameter(shader, gl.COMPILE_STATUS);
  if (deuCerto) {
    return shader;
  }
  // mostra o erro
  console.log(gl.getShaderInfoLog(shader));
  gl.deleteShader(shader); // limpa antes de sair
};

// ========================================================
/**
 * monta (liga ou linka?) o programa
 * @param {Obj} gl - contexto WebGL 
 * @param {*} vertexShader 
 * @param {*} fragmentShader 
 * @returns programa
 */
function link(gl, vertexShader, fragmentShader) {
  var program = gl.createProgram();
  gl.attachShader(program, vertexShader);
  gl.attachShader(program, fragmentShader);
  gl.linkProgram(program);

  var deuCerto = gl.getProgramParameter(program, gl.LINK_STATUS);
  if (deuCerto) {
    return program;
  }

  console.log(gl.ProgramInfoLog(program));
  gl.deleteProgram(program); // limpa
};

// ========================================================
/**
 * recebe array de arrays (triangulo) de diferentes tipos
 * @param {Array} v 
 * @returns retorna um array 1D com float32
 * 
 * Do livro do Angel, "Interactive Computer Graphics".
 */

function flatten(v) {
  // será que v é um array?
  if (!Array.isArray(v)) return v;

  // se for 1D transforma para float32
  if (typeof (v[0]) == 'number') {
    var floats = new Float32Array(v.length);

    for (var i = 0; i < v.length; i++)
      floats[i] = v[i];

    return floats;
  }



  // transforma para 1D de floats32
  var floats = new Float32Array(v.length * v[0].length);

  for (var i = 0; i < v.length; i++) for (var j = 0; j < v[0].length; j++) {
    floats[i * v[0].length + j] = v[i][j];
  }

  return floats;
}
