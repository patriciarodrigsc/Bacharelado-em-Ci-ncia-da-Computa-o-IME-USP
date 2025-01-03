
/* ==================================================
    cronometro.js

    Nome: Patricia da Silva Rodrigues
    NUSP: 11315590

    Ao preencher esse cabeçalho com o meu nome e o meu número USP,
    declaro que todas as partes originais desse exercício programa (EP)
    foram desenvolvidas e implementadas por mim e que portanto não 
    constituem desonestidade acadêmica ou plágio.
    Declaro também que sou responsável por todas as cópias desse
    programa e que não distribui ou facilitei a sua distribuição.
    Estou ciente que os casos de plágio e desonestidade acadêmica
    serão tratados segundo os critérios divulgados na página da 
    disciplina.
    Entendo que EPs sem assinatura devem receber nota zero e, ainda
    assim, poderão ser punidos por desonestidade acadêmica.

    Abaixo descreva qualquer ajuda que você recebeu para fazer este
    EP.  Inclua qualquer ajuda recebida por pessoas (inclusive
    monitores e colegas). Com exceção de material da disciplina, caso
    você tenha utilizado alguma informação, trecho de código,...
    indique esse fato abaixo para que o seu programa não seja
    considerado plágio ou irregular.

    Exemplo:

        A minha função quicksort() foi baseada na descrição encontrada na 
        página https://www.ime.usp.br/~pf/algoritmos/aulas/quick.html.

    Descrição de ajuda ou indicação de fonte: 

    https://panda.ime.usp.br/introcg/static/introcg/05-interacao.html



================================================== */



function cronometro() {
  atualizarDisplay(0, 0, 0)
  document.getElementById('Display_input').value = "00 : 00";
  // Seleciona o campo de texto do cronômetro
  var cronometro = document.getElementById('Display_input');

  // Seleciona todos os botões
  var botoes = document.querySelectorAll('.styled');
  var b0 = 0;
  var b1 = 0;
  var b2 = 0;
  var b3 = 0;

  var global_min;
  var global_seg;
  var global_mil;

  var min_init;
  var seg_init;
  var mil_init;

  var stop_click;

  // Função para formatar os dígitos do cronômetro
  function formatarDigitosCrono() {
    return b3.toString() + b2.toString() + " : " + b1.toString() + b0.toString();
  }

  function input_to_output_crono() {
    var valorDisplay = document.getElementById('Display_input').value;
    var partes = valorDisplay.split(' : ');
    b3 = parseInt(partes[0][0]);
    b2 = parseInt(partes[0][1]);
    b1 = parseInt(partes[1][0]);
    b0 = parseInt(partes[1][1]);

    console.log(b3, b2, b1, b0);

    var minutos = parseInt(b3.toString() + b2.toString()); // Convertendo os dígitos em uma única representação numérica
    var segundos = parseInt(b1.toString() + b0.toString());
    milesimos = 0;
    console.log(minutos, segundos, milesimos);
    return [minutos, segundos, milesimos];
  }

  // Atualiza o valor do cronômetro
  function atualizarCronometro() {
    cronometro.value = formatarDigitosCrono();
  }

  // Adiciona um ouvinte de evento de clique a cada botão
  botoes.forEach(function (botao) {
    botao.addEventListener('click', function () {
      // Atualiza os dígitos do botão
      b3 = b2;
      b2 = b1;
      b1 = b0;
      b0 = parseInt(this.value); // Converte o valor do botão para um número

      console.log(botao);
      console.log("Botao: "+ botao.value + " "+ b3 + b2 + b1 + b0);
      // Atualiza o valor do cronômetro
      atualizarCronometro();
    });
  });

  // Exibir zeros iniciais
  atualizarCronometro();

  var cronometroInterval;
  var cronometroRodando = false;

  document.getElementById("startButton/stopButton").addEventListener("click", function () {
    if (!cronometroRodando) {
      var [minutos, segundos, milesimos] = input_to_output_crono();

      if (!stop_click) {
        min_init = minutos;
        seg_init = segundos;
        mil_init = milesimos;
        iniciarCronometro(minutos, segundos, milesimos);
      } else {
        iniciarCronometro(global_min, global_seg, global_mil);
      }
      document.getElementById("startButton/stopButton").value = "Stop";
      cronometroRodando = true;
    } else {
      stop_click = true;
      zerarCronometro();
      document.getElementById("startButton/stopButton").value = "Start";
      cronometroRodando = false;
    }
  });

  document.getElementById("pauseButton/runButton").addEventListener("click", function () {
    if (cronometroRodando) {
      pausarCronometro();
      document.getElementById("pauseButton/runButton").value = "Run";
      cronometroRodando = false;
    } else {
      retomarCronometro();
      document.getElementById("pauseButton/runButton").value = "Pause";
      cronometroRodando = true;
    }
  });

  function iniciarCronometro(minutos, segundos, milesimos) {
    cronometroInterval = setInterval(function () {
      milesimos--;

      if (milesimos === -1) {
        milesimos = 59;
        segundos--;
      }
      if (segundos === -1) {
        segundos = 59;
        minutos--;
      }
      if (minutos === -1) {
        clearInterval(cronometroInterval);
        minutos = mil_init;
        segundos = seg_init;
        milesimos = mil_init;
        atualizarDisplay(minutos, segundos, milesimos);
        reiniciarValores();
      }

      global_min = minutos;
      global_seg = segundos;
      global_mil = milesimos;

      atualizarDisplay(minutos, segundos, milesimos);
    }, 1);
  }

  function pausarCronometro() {
    clearInterval(cronometroInterval);
    desativarBotoesPause();
  }

  function zerarCronometro() {
    clearInterval(cronometroInterval);
    stop_click = false;
  }

  function retomarCronometro() {
    iniciarCronometro(global_min, global_seg, global_mil);
    habilitarBotoes();
  }

  function reiniciarValores() {
    var valorDisplay = document.getElementById('Display_input').value;
    var partes = valorDisplay.split(' : ');
    b3 = parseInt(partes[0][0]);
    b2 = parseInt(partes[0][1]);
    b1 = parseInt(partes[1][0]);
    b0 = parseInt(partes[1][1]);

    global_min = parseInt(partes[0]);
    global_seg = parseInt(partes[1]);
    global_mil = 0; // Você pode definir isso como 0 ou como quiser
    document.getElementById("startButton/stopButton").value = "Start";
    cronometroRodando = false;
  }

  function desativarBotoesPause() {
    var botoes = document.querySelectorAll('.styled');
    botoes.forEach(function (botao) {
      botao.disabled = true;
    });

    var botaoTimer = document.getElementById('timerButton/CronoButton');
    if (botaoTimer) {
      botaoTimer.disabled = true;
      printDesabilitada("Timer")
    }


  }

  function printDesabilitada(tecla) {
    console.log("Tecla " + tecla + " desabilidada")
  }

  function habilitarBotoes() {
    var botoes = document.querySelectorAll('.styled');
    botoes.forEach(function (botao) {
      botao.disabled = false;
    });
  }

  function atualizarDisplay(minutos, segundos, milesimos) {
    let tempo = minutos + ':' + (segundos < 10 ? '0' : '') + segundos + ':' + (milesimos < 10 ? (milesimos < 10 ? '00' : '0') : '') + milesimos;
    document.getElementById('Display_output').innerHTML = tempo;
  }

  function cl() {
    clearInterval(cronometroInterval);
    atualizarCronometro();
    document.getElementById('Display_input').value = "00 : 00";
    cronometroRodando = false;
    b0 = 0
    b1 = 0
    b2 = 0
    b3 = 0
    min_init = global_min;
    seg_init = global_seg;
    mil_init = global_seg;
    stop_click = false;
  }

  // Adiciona um ouvinte de evento de clique ao botão "cl"
  document.getElementById("cl").addEventListener("click", cl);
}

//////////////////////////////////////////////////////////
function timer() {

  atualizarDisplay(0, 0, 0)
  document.getElementById('Display_input').value = "00 : 00";

  var timer = document.getElementById('Display_input');
  var botoes = document.querySelectorAll('.styled');
  var b0 = 0;
  var b1 = 0;
  var b2 = 0;
  var b3 = 0;

  var global_min;
  var global_seg;
  var global_mil;

  var min_init;
  var seg_init;
  var mil_init;

  var stop_click;

  function formatarDigitosTimer() {
    return b3.toString() + b2.toString() + " : " + b1.toString() + b0.toString();
  }

  function input_to_output_timer() {
    var valorDisplay = document.getElementById('Display_input').value;
    var partes = valorDisplay.split(' : ');
    b3 = parseInt(partes[0][0]);
    b2 = parseInt(partes[0][1]);
    b1 = parseInt(partes[1][0]);
    b0 = parseInt(partes[1][1]);

    console.log(b3, b2, b1, b0);

    var minutos = parseInt(b3.toString() + b2.toString());
    var segundos = parseInt(b1.toString() + b0.toString());
    var milesimos = 0; // Inicializa os milésimos como zero
    console.log(minutos, segundos, milesimos);
    return [minutos, segundos, milesimos];
  }

  function atualizarTimer() {
    timer.value = formatarDigitosTimer();
  }

  botoes.forEach(function (botao) {
    botao.addEventListener('click', function () {
      b3 = b2;
      b2 = b1;
      b1 = b0;
      b0 = parseInt(this.value);

      console.log(botao);
      console.log("Botao: " + botao.value + " " + b3 + b2 + b1 + b0);
      atualizarTimer();
    });
  });

  atualizarTimer();

  var timerInterval;
  var timerRodando = false;

  document.getElementById("startButton/stopButton").addEventListener("click", function () {
    if (!timerRodando) {
      var [minutos, segundos, milesimos] = input_to_output_timer();

      if (!stop_click) {
        min_fim = minutos;
        seg_fim = segundos;
        mil_fim = milesimos;
        iniciarTimer(0, 0, 0);
      } else {
        iniciarTimer(global_min, global_seg, global_mil);
      }
      document.getElementById("startButton/stopButton").value = "Stop";
      timerRodando = true;
    } else {
      stop_click = true;
      zerarTimer();
      document.getElementById("startButton/stopButton").value = "Start";
      timerRodando = false;
    }
  });

  document.getElementById("pauseButton/runButton").addEventListener("click", function () {
    if (timerRodando) {
      pausarTimer();
      document.getElementById("pauseButton/runButton").value = "Run";
      timerRodando = false;
    } else {
      retomarTimer();
      document.getElementById("pauseButton/runButton").value = "Pause";
      timerRodando = true;
    }
  });

  function iniciarTimer(minutos, segundos, milesimos) {
    timerInterval = setInterval(function () {

      if (minutos == min_fim && segundos == seg_fim && milesimos == mil_fim) {
        clearInterval(timerInterval);
        reiniciarValores();
        atualizarDisplay(minutos, segundos, milesimos);
        return;
      }

      milesimos++;
      if (milesimos === 60) {
        milesimos = 0;
        segundos++;

        if (segundos === 60) {
          segundos = 0;
          minutos++;

          if (minutos === 60) {
            clearInterval(timerInterval);
            minutos = 0;
            segundos = 0;
            milesimos = 0;
            atualizarDisplay(minutos, segundos, milesimos);
            reiniciarValores();
          }
        }
      }



      global_min = minutos;
      global_seg = segundos;
      global_mil = milesimos;

      atualizarDisplay(minutos, segundos, milesimos);
    }, 10); // Intervalo ajustado para 10 para milissegundos
  }


  function pausarTimer() {
    clearInterval(timerInterval);
    desativarBotoesPause();
  }

  function zerarTimer() {
    clearInterval(timerInterval);
    stop_click = false;
  }

  function retomarTimer() {
    iniciarTimer(global_min, global_seg, global_mil);
    habilitarBotoes();
  }

  function reiniciarValores() {
    var valorDisplay = document.getElementById('Display_input').value;
    var partes = valorDisplay.split(' : ');
    b3 = parseInt(partes[0][0]);
    b2 = parseInt(partes[0][1]);
    b1 = parseInt(partes[1][0]);
    b0 = parseInt(partes[1][1]);

    global_min = parseInt(partes[0]);
    global_seg = parseInt(partes[1]);
    global_mil = 0;
    document.getElementById("startButton/stopButton").value = "Start";
    timerRodando = false;
  }

  function desativarBotoesPause() {
    var botoes = document.querySelectorAll('.styled');
    botoes.forEach(function (botao) {
      botao.disabled = true;
    });

    var botaoTimer = document.getElementById('timerButton/CronoButton');
    if (botaoTimer) {
      botaoTimer.disabled = true;
      printDesabilitada("Timer")
    }
  }

  function printDesabilitada(tecla) {
    console.log("Tecla " + tecla + " desabilidada")
  }

  function printDesabilitada(tecla) {
    console.log("Tecla " + tecla + " habilitada")
  }

  function habilitarBotoes() {
    var botoes = document.querySelectorAll('.styled');
    botoes.forEach(function (botao) {
      botao.disabled = false;

      var botaoTimer = document.getElementById('timerButton/CronoButton');
      if (botaoTimer) {
        botaoTimer.disabled = false;
        printDesabilitada("Timer")
      }

    });

    var botaoTimer = document.getElementById('timerButton/CronoButton');
    if (botaoTimer) {
      botaoTimer.disabled = false;
      printHabilitada("Timer")
    }
  }

  function atualizarDisplay(minutos, segundos, milesimos) {
    let tempo = minutos + ':' + (segundos < 10 ? '0' : '') + segundos + ':' + (milesimos < 10 ? '0' : '') + milesimos;
    document.getElementById('Display_output').innerHTML = tempo;
  }

  function cl() {
    document.getElementById('cl').value = "cl";
    console.log("Botao: cl");
    clearInterval(timerInterval);
    atualizarTimer();
    document.getElementById('Display_input').value = "00 : 00";
    timerRodando = false;
    b0 = 0
    b1 = 0
    b2 = 0
    b3 = 0
    min_init = global_min;
    seg_init = global_seg;
    mil_init = global_seg;
    stop_click = false;
    min_fim = 0
    seg_fim = 0
    min_fim = 0
  }

  document.getElementById("cl").addEventListener("click", cl);

}

document.addEventListener("DOMContentLoaded", function () {
  cronometro();
  let alternarFuncao = true;

  function alternarFuncaoTimerCronometro() {
    if (!alternarFuncao) {
      timer();
      console.log("timer rodando");
      document.getElementById("timerButton/CronoButton").value = "Crono";

    } else {
      cronometro();
      console.log("cronometro rodando")
      document.getElementById("timerButton/CronoButton").value = "Timer";
    }
    alternarFuncao = !alternarFuncao; // Alternar o valor da variável de controle
  }

  // Adiciona um event listener para o botão
  const botao = document.getElementById("timerButton/CronoButton");
  botao.addEventListener("click", alternarFuncaoTimerCronometro);
});