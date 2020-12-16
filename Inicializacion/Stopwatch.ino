void Temporizador() {
  if (watchFlag == 0) {
    startMillis = millis();
    watchFlag = 1;
  }
  currentMillis = millis();
  elapsedMillis = (currentMillis - startMillis);
  durMM = (elapsedMillis / (60000)); //Minutes
  //unsigned long durHH = (elapsedMillis/(3600000))
  minFaltantes = minNecesarios - durMM;
  hrsFaltantes = int(minFaltantes) / 60; // Entero
  // minFaltantes=minFaltantes-hrsFaltantes*60;// Hace falta/

  //
  //if(hrsFaltantes<10){
  //  lcd.setCursor(12, 2);
  //  lcd.print(hrsFaltantes);
  //  }
  //  else{
  //  lcd.setCursor(11, 2);
  //  lcd.print(hrsFaltantes);
  //    }
  //  lcd.setCursor(13, 2);
  //  lcd.print(":");
  lcd.setCursor(14, 2);

  if (minFaltantes < 10) {
    lcd.write('0');
    lcd.setCursor(15, 2);
    lcd.print(minFaltantes);
  }
  else {
    lcd.print(minFaltantes);
  }
  if ( minFaltantes == 0) { //borre hrsFaltantes==0 &&
    temporizadorOn = false;
    pidOn = false;
    FanSpeed();
    analogWrite(R_LOAD, 0);
    lcd.clear();
    currentMenu = 1;
    Drawing(Menu1, 0);
    watchFlag = 0; // Si 'Abort', reseteo el start millis del stopwatch
    elapsedMillis = 0;
    startMillis = 0;
    durMM = 0;
    firstTimeRead = true;
    firstSet = true;

    welcomeScreen(1);
  }
}
