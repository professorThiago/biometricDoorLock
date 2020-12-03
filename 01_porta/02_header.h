// INCLUSÃO DAS BIBLIOTECAS
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <virtuabotixRTC.h> 
#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <SPI.h>
#include <SD.h>
#include <TimerOne.h>

// PINAGEM DO LEITOR BIOMÉTRICO
const int tx = 10; //BRANCO
const int rx = 9; //VERDE
/* No Arduino MEGA utilizar apenas estes pinos como RX
10, 11, 12, 13, 14, 15, 50, 51, 52, 53,
A8(62), A9(63), A10(64), A11(65), A12(66), A13(67), A14(68), A15(69)
No Arduino UNO não ultilizar o RX no pino 13*/

//PINAGEM DO RTC
const int   clk =  6;
const int   dat =  7;
const int   rst =  8;


// INSTANCIANDO OBJETOS
SoftwareSerial mySerial(rx, tx);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
virtuabotixRTC   RTC(clk, dat, rst);
LiquidCrystal_I2C lcd (0x27, 20,4);
File ARQUIVO;
File ARQUIVO_TEMP;

//PINAGEM DO SD
const int CS_Pin = 4;

// DECLARAÇÃO DAS VARIÁVEIS
bool porta = 0;
bool porta_aux = 1;


//PROTÓTIPOS DAS FUNCOES
byte gravar(byte id); //Função para gravar uma digital na posição id
byte leitura(void);   /*Função que lê uma digital, retorna o numero da digital ou
                      253 para sem digital no leitor
                      254 para falha na leitura da digital
                      255  para digital não está cadastrada*/
byte deleta(byte id); //Função para deletar uma digital da posição id


void RealTimeClock(); //Interrupção que atualiza a hora a cada segundo
String DS1302(int tipo);//1 - Retorna data completa
                        //2 - Retorna semana e data
                        //3 - Retorna data
                        //4 - Retorna hora:minuto:segundo
                        //5 - Retorna hora:minuto

void ajustaHora (int d_semL, int d_mesL, int mesL, int anoL, int horL, int minL, int segL);

bool arquivo_mensal(bool tipo, String texto); //Grada texto no arquivo do mes corrente
                                              //0 para não pular linha
                                              //1 para pular linha

void leituraSD(String nome); //Mostra na serial o conteudo do arquivo "nome"

unsigned long procurarPorNumero(String nomeArquivo, byte pos);
String lerNaPosicao(String nomeArquivo, unsigned long pos, char fim = '\n', byte limite = 20);
void inserirTexto(String nomeArquivo, String texto, unsigned long  pos);

void atualizaHora(); //atualiza as variaveis do RTC a cada segundo
