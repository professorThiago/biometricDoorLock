//DEFINIÇÕES DAS FUNÇÕES

byte gravar(byte id)
{
  int p = -1;
  Serial.print(F("Esperando uma leitura válida para gravar #")); Serial.println(id);
  //Loop de verificação de digital
  while (p != FINGERPRINT_OK)
  {
    p = finger.getImage();
    switch (p)
    {
      case FINGERPRINT_OK:
        Serial.println(F("Leitura concluída"));
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        delay(200);
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println(F("Erro comunicação"));
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println(F("Erro de leitura"));
        break;
      default:
        Serial.println(F("Erro desconhecido"));
        break;
    }
  }

  //Capitura a primeira imagem da digital
  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println(F("Leitura convertida"));
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println(F("Leitura suja"));
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println(F("Erro de comunicação"));
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println(F("Não foi possível encontrar propriedade da digital"));
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println(F("Não foi possível encontrar propriedade da digital"));
      return p;
    default:
      Serial.println(F("Erro desconhecido"));
      return p;
  }

  //Aguardar retirar o dedo
  Serial.println(F("Remova o dedo"));
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) p = finger.getImage();

  //Loop de verificação de digital
  p = -1;
  Serial.println(F("Coloque o Mesmo dedo novamente"));
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println(F("Leitura concluída"));
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        delay(200);
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println(F("Erro de comunicação"));
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println(F("Erro de Leitura"));
        break;
      default:
        Serial.println(F("Erro desconhecido"));
        break;
    }
  }
  //Capitura a segunda imagem da digital
  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println(F("Leitura convertida"));
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println(F("Leitura suja"));
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println(F("Erro de comunicação"));
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println(F("Não foi possível encontrar as propriedades da digital"));
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println(F("Não foi possível encontrar as propriedades da digital"));
      return p;
    default:
      Serial.println(F("Erro desconhecido"));
      return p;
  }

  //Cria modelo com as duas digitais
  Serial.print(F("Criando modelo para #"));  Serial.println(id);
  p = finger.createModel();
  if (p == FINGERPRINT_OK)
  {
    Serial.println(F("As digitais batem!"));
  }
  else if (p == FINGERPRINT_PACKETRECIEVEERR)
  {
    Serial.println(F("Erro de comunicação"));
    return p;
  }
  else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println(F("As digitais não batem"));
    return p;
  }
  else
  {
    Serial.println(F("Erro desconhecido"));
    return p;
  }

  //Salva modelo na posição id
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK)
  {
    Serial.println(F("Armazenado!"));
  }
  else if (p == FINGERPRINT_PACKETRECIEVEERR)
  {
    Serial.println(F("Erro de comunicação"));
    return p;
  }
  else if (p == FINGERPRINT_BADLOCATION)
  {
    Serial.println(F("Não foi possível gravar neste local da memória"));
    return p;
  }
  else if (p == FINGERPRINT_FLASHERR)
  {
    Serial.println(F("Erro durante escrita na memória flash"));
    return p;
  }
  else
  {
    Serial.print(F("Erro desconhecido: 0x")); Serial.println(p, HEX);
    return p;
  }
}


byte leitura(void)
{
  byte p = finger.getImage(); //Verifica se há digital
  if (p != FINGERPRINT_OK)  return 253;

  p = finger.image2Tz(); //Capitura a digital
  if (p != FINGERPRINT_OK)  return 254;

  p = finger.fingerFastSearch(); //procura no banco de dados
  if (p != FINGERPRINT_OK)  return 255;

  //Serial.print("ID encontrado #"); Serial.print(finger.fingerID);
  //Serial.print(" com confiança de "); Serial.println(finger.confidence);
  return finger.fingerID;
}

byte deleta(byte id)
{
  byte p = -1;

  p = finger.deleteModel(id);

  if (p == FINGERPRINT_OK) {
    Serial.println(F("Apagada!"));
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println(F("Erro de comunicação"));
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println(F("Não foi possível gravar neste local da memória"));
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println(F("Erro durante escrita na memória flash"));
    return p;
  } else {
    Serial.print(F("Erro desconhecido: 0x")); Serial.println(p, HEX);
    return p;
  }
}
