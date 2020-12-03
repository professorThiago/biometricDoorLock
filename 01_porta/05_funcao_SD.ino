bool arquivo_mensal(bool tipo, String texto)
{
  bool confirmacao = 0;
  RTC.updateTime();
  String nomeArquivo = String(RTC.year) + "_" + String(RTC.month);
  nomeArquivo += ".txt";

  ARQUIVO = SD.open(nomeArquivo, FILE_WRITE);
  if (ARQUIVO)
  {
    switch (tipo)
    {
      case 0:
        ARQUIVO.print(texto);
        break;
      case 1:
        ARQUIVO.println(texto);
        break;
    }
    Serial.println(F("Arquivo implementado"));
    confirmacao = 1;
  }
  else Serial.println(F("Erro ao implementar dado"));
  ARQUIVO.close();
  return confirmacao;
}

void leituraSD(String nome)
{
  ARQUIVO = SD.open(nome, FILE_READ);
  if (ARQUIVO)
  {
    Serial.println(F("O arquivo contem:"));
    while (ARQUIVO.available())
      Serial.write(ARQUIVO.read());
    ARQUIVO.close();
  }
  else Serial.println(F("Erro ao ler o arquivo"));
}


void inserirTexto(String nomeArquivo, String texto, unsigned long  pos)
{
  ARQUIVO = SD.open(nomeArquivo, O_RDWR);
  ARQUIVO_TEMP = SD.open("temp.txt", FILE_WRITE);
  if (ARQUIVO && ARQUIVO_TEMP)
  {
    
    unsigned long tamanho = ARQUIVO.size();

    char novaLinha = "";
    unsigned long novaPos = pos;
    while (novaLinha != '\n' && novaPos < tamanho) //procura a proximo carecter de linha nova
    {
      ARQUIVO.seek(novaPos);
      novaLinha = ARQUIVO.peek();
      novaPos++;
    }

    for (int x = novaPos; x <= tamanho; x++) //Copia todo conteudo para um arquivo temporario
    {
      ARQUIVO.seek(x);
      ARQUIVO_TEMP.print(char(ARQUIVO.peek()));
    }

    ARQUIVO.seek(pos); //volta para posição desejada e insere o texto novo
    ARQUIVO.println(texto);

    unsigned long tamanho_aux = ARQUIVO_TEMP.size();

    for (int x = 0; x < tamanho_aux; x++) //Devolve todo o conteudo copiado ao texto original
    {
      ARQUIVO_TEMP.seek(x);
      ARQUIVO.print(char(ARQUIVO_TEMP.peek()));
    }
    
  }
  else Serial.println(F("Erro ao implementar dado"));
  ARQUIVO.close();
  ARQUIVO_TEMP.close();
  SD.remove("temp.txt");
  
}

String lerNaPosicao(String nomeArquivo, unsigned long pos, char fim = '\n', byte limite = 20)
{
  String retorno = "";
  ARQUIVO = SD.open(nomeArquivo, O_READ);
  if (ARQUIVO)
  {
    for (int x = pos; x < (pos + limite); x++)
    {
      ARQUIVO.seek(x);
      if (char(ARQUIVO.peek()) != fim) retorno += char(ARQUIVO.peek());
      else 
      {
        x = pos + limite;
      }
    }
  }
  else Serial.println(F("Erro ao implementar dado"));
  ARQUIVO.close();
  return retorno;
}


unsigned long procurarPorNumero(String nomeArquivo, byte pos)
{
  ARQUIVO = SD.open(nomeArquivo, O_READ);

  //Ordenação da String que o programa vai comparar tipo '&xxx'
  String posicao = "&";
  if (pos < 10) posicao += String("00" + String(pos));
  else if (pos < 100) posicao += String("0" + String(pos));
  else posicao += String(pos);
  posicao += ";";

  char aux = ""; //caractere capiturado para comparar
  unsigned long retorno = 0; //valor de retorno de endereço
  byte validacao = 0; //variavel da validação das comparações

  if (ARQUIVO)
  {
    unsigned long tamanho = ARQUIVO.size();
    for (int x = 0; x <= tamanho; x++) //varre o arquivo até o tamanho maximo
    {

      ARQUIVO.seek(x);
      aux = char(ARQUIVO.peek());

      if (aux == posicao[0] && validacao == 0) validacao = 1;
      else if (validacao == 1)
      {
        if (aux == posicao[1]) validacao = 2;
        else validacao = 0;
      }
      else if (validacao == 2)
      {
        if (aux == posicao[2]) validacao = 3;
        else validacao = 0;
      }
      else if (validacao == 3)
      {
        if (aux == posicao[3]) validacao = 4;
        else validacao = 0;
      }
      else if (validacao == 4)
      {
        if (aux != posicao[4]) validacao = 0;
        else
        {
          x = tamanho;
          retorno = ARQUIVO.position() + 1;
        }
      }
    }
  }
  else Serial.println(F("Erro ao implementar dado"));
  ARQUIVO.close();
  return retorno;
}


void criar_arquivo_usuario()
{
  SD.remove("usuarios.txt");
  ARQUIVO = SD.open("usuarios.txt", FILE_WRITE);
  if (ARQUIVO)
  {
    for (int x = 0; x <= 150; x++)
    {
      if (x < 10)
      {
        ARQUIVO.print("&00");
        ARQUIVO.print(x, DEC);
        ARQUIVO.println(";");
      }
      else if (x < 100)
      {
        ARQUIVO.print("&0");
        ARQUIVO.print(x, DEC);
        ARQUIVO.println(";");
      }
      else
      {
        ARQUIVO.print("&");
        ARQUIVO.print(x, DEC);
        ARQUIVO.println(";");
      }
    }
  }
  else Serial.println(F("Erro ao implementar dado"));
  ARQUIVO.close();

}


/*
  void informacaoSD()
  {
  Serial.println();
  Serial.print(F("Tipo de cartao:         "));
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println(F("SD1"));
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println(F("SD2"));
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println(F("SDHC"));
      break;
    default:
      Serial.println(F("Unknown"));
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println(F("Nao foi possivel encontrar a particao"));
    while (1);
  }

  Serial.print(F("Clusters:          "));
  Serial.println(volume.clusterCount());
  Serial.print(F("Blocks x Cluster:  "));
  Serial.println(volume.blocksPerCluster());

  Serial.print(F("Total Blocks:      "));
  Serial.println(volume.blocksPerCluster() * volume.clusterCount());
  Serial.println();

  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print(F("O volute é do tipo:    FAT"));
  Serial.println(volume.fatType(), DEC);

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
  Serial.print(F("Volume size (Kb):  "));
  Serial.println(volumesize);
  Serial.print(F("Volume size (Mb):  "));
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print(F("Volume size (Gb):  "));
  Serial.println((float)volumesize / 1024.0);

  Serial.println(F("\nArquivos encontrados no cartao (nome, data e tamanho em bytes): "));
  root.openRoot(volume);

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
  }
*/
