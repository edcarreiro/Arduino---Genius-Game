#include <Arduino.h>

const int a = 440;
const int f = 349;
const int cH = 523;
int counter = 0;


#define totalRodadas 20
#define btDebug 7
int leds [4] = {2, 3, 4, 5};
int botoes [4] = {8, 9, 10, 11};
int tons [4] = {262, 294, 330, 349};

int delayPisca = 100;
byte buzzer = 6;
bool resposta = false;

int botaoApertado;

int sequencia[totalRodadas]; // cores sorteadas
bool gameOver = false;

byte totalSequencia = 0; // numero  de acertos. Ex. depois de 3 rodadas de acertos = 2 (começa do 0)

byte jogadaAtual = 0;  //numero da jogada que o jogador está jogando agora


void iniciaPortas() {   // Start ports of led's,  button's and buzzer
      for ( byte x = 0; x <= 3; x++ ) {
            pinMode ( leds [x], OUTPUT );
            pinMode ( botoes [x] , INPUT_PULLUP );
            }
      pinMode ( 7, INPUT_PULLUP );
      pinMode ( buzzer, OUTPUT );
      }

void piscaLed ( int portaLed, int delayPisca ) { // Blink a led based in the digital input of portaLed
      digitalWrite ( leds[portaLed], HIGH );
      tone ( buzzer, tons[portaLed] );
      Serial.print ( leds[portaLed] );
      Serial.println ( tons[portaLed] );
      delay ( delayPisca );
      digitalWrite ( leds[portaLed], LOW );
      noTone ( buzzer );
      delay ( delayPisca );
      }



void piscaSequencia() { //Blink all leds in sequence - Red, Green, Yellow and Blue
      for ( byte x = 0; x <= 3; x++ ) {
            piscaLed ( x, 100 );
            }
      }

void piscaTodos() { //Turn on all leds, delays and turn off all leds
      for ( byte x = 0; x <= 3; x++ ) {
            digitalWrite ( leds [x], HIGH );
            }
      delay ( 100 );
      for ( byte x = 0; x <= 3; x++ ) {
            digitalWrite ( leds [x], LOW );
            } delay ( 100 );
      noTone ( buzzer );
      }

void iniciaJogo() { // Initial sequence of the game
      for ( byte x = 1; x <= 2; x++ ) {
            piscaSequencia();
            for ( byte z = 2; z >= 1; z-- ) {
                  piscaLed ( z, 100 );
                  }
            }
      for ( byte x = 0; x <= 4; x++ ) {
            piscaTodos();
            }
      }

void criaSequencia () { // Random led assigned to variable "sequencia"
      randomSeed ( analogRead ( A5 ) * 17 * 11 );
      sequencia [jogadaAtual] = random ( 4 );
      }

void playRodada() {
      for ( int i = 0 ; i <= jogadaAtual; i++ ) {
            piscaLed ( sequencia[i], 400 );
            }
      }

void respostaJogador() {
      for ( int i = 0 ; i <= jogadaAtual ; i++ ) {
            bool resposta = false;
            while ( !resposta ) {
                  for ( int z = 0; z <= 3; z++ ) {
                        if  ( digitalRead ( botoes[z] ) == LOW ) {
                              botaoApertado = z;
                              piscaLed ( z, 300 );
                              resposta = true;
                              }
                        }
                  }
            if ( sequencia[i] !=  botaoApertado ) {
                  gameOver = true;
                  break;
                  }
            }
      jogadaAtual++;
      }


void marchEndGame() {
      beep ( a, 500 );
      beep ( a, 500 );
      beep ( a, 500 );
      beep ( f, 350 );
      beep ( cH, 150 );
      beep ( a, 500 );
      beep ( f, 350 );
      beep ( cH, 150 );
      beep ( a, 650 );
      delay ( 500 );
      }

void beep ( int note, int duration ) {
      //Play tone on buzzerPin
      tone ( buzzer, note, duration );
      //Play different LED depending on value of 'counter'
      if ( counter % 2 == 0 ) {
            digitalWrite ( leds[1], HIGH );
            delay ( duration );
            digitalWrite ( leds[1], LOW );
            }
      else {
            digitalWrite ( leds[2], HIGH );
            delay ( duration );
            digitalWrite ( leds[2], LOW );
            }
      //Stop tone on buzzerPin
      noTone ( buzzer );
      delay ( 50 );
      //Increment counter
      counter++;
      }




void setup() {
      Serial.begin ( 9600 );
      iniciaPortas();
      iniciaJogo();
      delay ( 500 );
      jogadaAtual = 0;
      }

void loop() {
      criaSequencia();
      playRodada();
      respostaJogador();
      if ( gameOver == true ) {
            sequencia[totalRodadas] = {};
            jogadaAtual = 0;
            gameOver = false;
            marchEndGame();
            delay ( 1000 );
            iniciaJogo();
            }
      delay ( 500 );
      }
