
void ajustaHora (int d_semL, int d_mesL, int mesL, int anoL, int horL, int minL, int segL)
{
  RTC.setDS1302Time(segL, minL, horL, d_semL, d_mesL, mesL, anoL);
}


String DS1302(int tipo)
{
  RTC.updateTime();         //faz leitura do DS1302 e atualiza as variaveis da função
  String dateTime = "";
  switch (tipo)
  {
    case 1:  
      dateTime =  week(RTC.dayofweek);
      dateTime += (F(" "));
      dateTime += (RTC.dayofmonth);
      dateTime += (F("/"));
      dateTime += (RTC.month);
      dateTime += (F("/"));
      dateTime += (RTC.year);
      dateTime += (F(" | "));
      if (RTC.hours < 10) dateTime += (F("0"));
      dateTime += (RTC.hours);
      dateTime += (F(":"));
      if (RTC.minutes < 10) dateTime += (F("0"));
      dateTime += (RTC.minutes);
      dateTime += (F(":"));
      if (RTC.seconds < 10) dateTime += (F("0"));
      dateTime += (RTC.seconds);
      break;  
    
    case 2:
      dateTime =  week(RTC.dayofweek);
      dateTime += (F(" "));
      dateTime += (RTC.dayofmonth);
      dateTime += (F("/"));
      dateTime += (RTC.month);
      dateTime += (F("/"));
      dateTime += (RTC.year);
      break;  

    case 3:
      dateTime = (RTC.dayofmonth);
      dateTime += (F("/"));
      dateTime += (RTC.month);
      dateTime += (F("/"));
      dateTime += (RTC.year);
      break;  
 
   case 4:  
      if (RTC.hours < 10) dateTime += (F("0"));
      dateTime += (RTC.hours);
      dateTime += (F(":"));
      if (RTC.minutes < 10) dateTime += (F("0"));
      dateTime += (RTC.minutes);
      dateTime += (F(":"));
      if (RTC.seconds < 10) dateTime += (F("0"));
      dateTime += (RTC.seconds);
      break;  

   case 5:  
      if (RTC.hours < 10) dateTime += (F("0"));
      dateTime += (RTC.hours);
      dateTime += (F(":"));
      if (RTC.minutes < 10) dateTime += (F("0"));
      dateTime += (RTC.minutes);
      break;    
  }
  return dateTime;
} //end DS1302


String week(int dayW)
{
  String semana = "";
  switch (dayW)
  {

    case 1: semana = (F("Dom")); break;
    case 2: semana = (F("Seg")); break;
    case 3: semana = (F("Ter")); break;
    case 4: semana = (F("Qua")); break;
    case 5: semana = (F("Qui")); break;
    case 6: semana = (F("Sex")); break;
    case 7: semana = (F("Sab")); break;

  } //end switch
  return semana;
} //end week

void RealTimeClock()
{
  RTC.updateTime();
}
