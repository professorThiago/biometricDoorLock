void atualizaHora()
{
  byte cadastro = leitura();
  if (RTC.seconds == 0);
  {
    lcd.home();
    lcd.print(DS1302(2));
    lcd.setCursor(15, 0);
    lcd.print(DS1302(5));
  }
}

void atualizaStatusPorta()
{
  if (porta != porta_aux)
  {
    if (porta)
    {
      lcd.setCursor(0, 2);
      lcd.print("Porta Aberta  ");
    }

    else
    {
      lcd.setCursor(0, 2);
      lcd.print("Porta Trancada");
    }
  porta_aux = porta;
  }
  
}
