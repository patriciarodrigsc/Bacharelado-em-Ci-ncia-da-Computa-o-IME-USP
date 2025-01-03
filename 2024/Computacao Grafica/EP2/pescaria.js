/*
    pescaria de MAC0420/MAC5744 - Pescaria

    Nome: Patrícia da Silva Rodrigues
    NUSP: 11315590
 */

window.onload = main;

var ctx;
let canvas;

let L;
let H;

const vertices = [4, 8, 16];
let relacoes = [[], [], []];

let posicao_peixes = [];
let posicao_bolhas = [];
let posicao_arpao;

let velocidade_peixes = [];
const velocidade_bolhas = 10;
const velocidade_arpao = 0.5;

let status_peixes = [];
let status_bolhas = [];

let numero_peixes = 10;
let numero_bolhas = 0;

let cor_peixes = [];
let raio_peixes = [];
let tipo_peixes = [];

let tempo = 0;
let isPaused = false;
let animationId;

/*
----
MAIN
----
*/

function main() {

  canvas = document.getElementById('meucanvas')
  ctx = canvas.getContext('2d');
  canvas.style.backgroundColor = "lightblue";

  ctx.canvas.width = window.innerWidth;
  ctx.canvas.height = window.innerHeight;
  L = ctx.canvas.width;
  H = ctx.canvas.height;

  posicao_arpao = [1 / 2 * L, 0.9 * H]

  n = numero_peixes;

  for (i = 0; i < 3; i++) {
    for (j = 0; j < vertices[i]; j++) {
      relacoes[i].push([Math.cos(j * 2 * Math.PI / vertices[i]), Math.sin(j * 2 * Math.PI / vertices[i])]);
    }
  }

  for (i = 0; i < n; i++) {
    gera_peixe(L, H);
    desenha_peixe(i);
  }

  passo()

}

/*
------------------
FUNÇÕES DO PASSO
------------------
*/

function passo() {
  tempo = tempo + 1;
  // a cada passo, redefine o tamanho da janela
  ctx.canvas.width = window.innerWidth;
  ctx.canvas.height = window.innerHeight;
  L = ctx.canvas.width;
  H = ctx.canvas.height;

  // redefine o tamanho da areia
  desenhePoligono([[0, 0.8 * H], [1 * L, 0.8 * H], [1 * L, 1 * H], [0 * L, 1 * H]], 'blue', 0)

  // recalcula a posição do arpão
  if (posicao_arpao[0] < 0) {
    posicao_arpao[0] = -posicao_arpao[0];
  }
  if (posicao_arpao[0] > L) {
    posicao_arpao[0] = 2 * L - posicao_arpao[0];
  }
  posicao_arpao[1] = 0.9 * H;
  desenha_arpao();

  // recalcula a posição dos peixes
  for (i = 0; i < n; i++) {
    if (status_peixes[i] == true) {
      posicao_peixes[i][0] = posicao_peixes[i][0] + velocidade_peixes[i][0];
      posicao_peixes[i][1] = posicao_peixes[i][1] + velocidade_peixes[i][1];
      if (posicao_peixes[i][0] - raio_peixes[i] < 0) {
        velocidade_peixes[i][0] *= -1;
        posicao_peixes[i][0] = 2 * raio_peixes[i] - posicao_peixes[i][0];
      }
      if (posicao_peixes[i][0] + raio_peixes[i] >= L) {
        velocidade_peixes[i][0] *= -1;
        posicao_peixes[i][0] = 2 * L - posicao_peixes[i][0] - 2 * raio_peixes[i];
      }
      if (posicao_peixes[i][1] - raio_peixes[i] < 0) {
        velocidade_peixes[i][1] *= -1;
        posicao_peixes[i][1] = 2 * raio_peixes[i] - posicao_peixes[i][1];
      }
      if (posicao_peixes[i][1] + raio_peixes[i] >= 0.8 * H) {
        velocidade_peixes[i][1] *= -1;
        posicao_peixes[i][1] = 1.6 * H - posicao_peixes[i][1] - 2 * raio_peixes[i];
      }

      desenha_peixe(i);
    }
  };

  // bolhas
  for (i = 0; i < numero_bolhas; i++) {
    if (status_bolhas[i] == true) {
      posicao_bolhas[i][1] = posicao_bolhas[i][1] - velocidade_bolhas;
      checar_colisao(i);
      desenha_bolha(i);
    }
  };



  // input do usuário
  if (tempo > 0 && !isPaused) {
    document.addEventListener("keydown", function (event) {
      console.log("tecla : " + event.key);
      tempo = 0;
      if (event.key === "d") {
        posicao_arpao[0] = posicao_arpao[0] + Math.abs(velocidade_arpao);
      }
      if (event.key === "a") {
        posicao_arpao[0] = posicao_arpao[0] - Math.abs(velocidade_arpao);
      }
      //atira bolha
      if (event.key === "s") {
        gera_bolha();

      }
    });
  }

  // continua infinitamente
  animationId = requestAnimationFrame(passo);
}

/*
------------------
FUNÇÕES DE COLISÃO
------------------
*/

function checar_colisao(i) {
  if (posicao_bolhas[i][1] < 0) {
    status_bolhas[i] = false
    return null
  }
  for (j = 0; j < numero_peixes; j++) {
    if (status_peixes[j] == true) {
      let dx = posicao_bolhas[i][0] - posicao_peixes[j][0];
      if (dx < raio_peixes[j]) {
        let dy = posicao_bolhas[i][1] - posicao_peixes[j][1];
        if (dy < raio_peixes[j]) {
          let d = Math.sqrt(dx * dx + dy * dy);
          if (d < raio_peixes[j]) {
            status_peixes[j] = false;
            status_bolhas[i] = false;
          }
        }
      }
    }
  }
}

/*
------------------
FUNÇÕES GERADORAS
------------------
*/

function gera_peixe(L, H) {
  let raio = Math.min(L, H) * real_aleatorio(0.02, 0.07);
  raio_peixes.push(raio);

  posicao_peixes.push([real_aleatorio(raio, L - raio), real_aleatorio(raio, 0.8 * H - raio)]);
  velocidade_peixes.push([real_aleatorio(-L, L) / 200, real_aleatorio(-H, H) / 200]);
  cor_peixes.push(randomColor());
  status_peixes.push(true);
  tipo_peixes.push(int_aleatorio(0, 2));
  return null
}

function gera_bolha() {
  posicao_bolhas.push([posicao_arpao[0], posicao_arpao[1]])
  status_bolhas.push(true)
  numero_bolhas = numero_bolhas + 1;
}

/*
------------------
FUNÇÕES DE DESENHO
------------------
*/

function int_aleatorio(a, b) {
  return Math.floor(Math.random() * (b - a + 1) + a)
}

function desenhePoligono(pts, cor = 'blue', wid = 10) {
  let tam = pts.length;
  // console.log("Desenhando poligono", cor, pts, tam);

  poli = new Path2D();
  poli.moveTo(Math.floor(pts[0][0]), Math.floor(pts[0][1]));
  for (let i = 1; i < pts.length; i++) {
    poli.lineTo(Math.floor(pts[i][0]), Math.floor(pts[i][1]));
    // console.log(pts[i][0], pts[i][1]);
  }
  poli.closePath(); // cria um contorno fechado.

  if (wid > 0) {
    ctx.strokeStyle = cor;
    ctx.lineWidth = wid;
    ctx.stroke(poli);
  }
  else { // wid <= 0 preenche o polígono
    ctx.fillStyle = cor;
    ctx.fill(poli);
  }
}

function desenha_peixe(i) {
  let pontos = [];
  let xTemp;
  let yTemp;
  for (j = 0; j < vertices[tipo_peixes[i]]; j++) {
    xTemp = posicao_peixes[i][0] + (raio_peixes[i] * relacoes[tipo_peixes[i]][j][0]);
    yTemp = posicao_peixes[i][1] + (raio_peixes[i] * relacoes[tipo_peixes[i]][j][1]);
    pontos.push([xTemp, yTemp]);
  }

  cor = cor_peixes[i]
  desenhePoligono(pontos, cor, 0);
}

function desenha_arpao() {
  const x = posicao_arpao[0];
  const y = posicao_arpao[1];
  pontos = [[x, y - H * 0.1], [x + L * 0.03, y], [x - L * 0.03, y]]
  desenhePoligono(pontos, 'red', 0);
}

function desenha_bolha(i) {
  const x = posicao_bolhas[i][0];
  const y = posicao_bolhas[i][1];
  pontos = [[x, y - 10], [x - 1, y], [x + 1, y]]
  desenhePoligono(pontos, 'black', 0)
}

/*
------------------
FUNÇÕES AUXILIARES
------------------
*/
function real_aleatorio(a, b) {
  return (Math.random() * (b - a) + a)
}

function randomColor() {
  var r = Math.floor(Math.random() * 256);
  var g = Math.floor(Math.random() * 256);
  var b = Math.floor(Math.random() * 256);

  return `rgb(${r}, ${g}, ${b})`;
}

// Exemplo de uso
document.getElementById('playPauseButton').addEventListener('click', function () {
  if (!isPaused) {
    cancelAnimationFrame(animationId);
    isPaused = true;
    document.getElementById('playPauseButton').textContent = 'Jogar';
  } else {
    isPaused = false;
    passo();
    document.getElementById('playPauseButton').textContent = 'Pausar';
  }
});
