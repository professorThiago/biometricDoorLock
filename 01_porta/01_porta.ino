#include "02_header.h"

void setup()
{
  Serial.begin(9600);
  finger.begin(57600);
  lcd.init();                      // initialize the lcd
  lcd.init();
  lcd.backlight();
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(RealTimeClock);
  while (!finger.verifyPassword())
    Serial.println(F("Sensor biometrico não encontrado!"));
  Serial.println(F("Sensor biometrico encontrado!"));

  if (!SD.begin(4))
    Serial.println(F("Erro na leitura do Cartao SD!"));
  Serial.println(F("Cartao SD inicializado"));

  //inserirNaPosicao("teste.txt", 101);
  //criar_arquivo_usuario();

  //  inserirTexto("teste.txt", "Teste de inserção de nova linha", 101);
  //  leituraSD("teste.txt");
  //unsigned long usuario = procurarPorNumero("teste.txt",11);
  //Serial.println(usuario);

  //  informacaoSD();
  atualizaStatusPorta();
}



void loop() {
  atualizaHora();

  byte cadastro = leitura();
  
  if (cadastro == 255)
  {
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 1);
    lcd.print("Nao cadastrado");
  }

  else if (cadastro <= 150)
  {
    porta = !porta;
    atualizaStatusPorta();
    unsigned long endereco = procurarPorNumero("usuarios.txt", cadastro);
    Serial.println(endereco);
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 1);
    String nome = lerNaPosicao("usuarios.txt", endereco);
    for (int x = 0; x < (nome.length() - 1); x++) lcd.print(nome[x]); //resolver problema da biblioteca que está enviando '/0'
    Serial.println(nome);
    //Serial.println(String(nome,DEC));
  }

}
