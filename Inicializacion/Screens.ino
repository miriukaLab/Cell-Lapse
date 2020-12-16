void Pages() {
  switch (currentMenu) {

    case 134:
      switch (cursorPos) {
        case 3:
          currentMenu = 132;
          Drawing(Menu132, 1);
          lcd.setCursor(4, 0);
          lcd.print(Setpoint);// Este valor es fijo, no hace falta refresh
          lcd.setCursor(9, 0);
          lcd.write(2);
          lcd.setCursor(10, 0);
          lcd.print("C");         
          break;
        case 2:
          currentMenu = 1;
          Drawing(Menu1, 0);
          watchFlag = 0; // Si 'Abort', reseteo el start millis del stopwatch
          elapsedMillis = 0;
          startMillis = 0;
          durMM = 0;
          temporizadorOn = false;
          firstTimeRead=true;
          pidOn = false;
          firstSet=true;
          
          analogWrite(R_LOAD, 0);
          lcd.setCursor(19, 0);
          lcd.print('C');
          delay(5000);
          analogWrite(fan,0);
          lcd.setCursor(19, 0);
          lcd.print(' ');
          break;
      }
      break;
    case 133:
      currentMenu = 1;
      cursorPos = 0;
      Drawing(Menu1, 0);
      watchFlag = 0; // Si 'Abort', reseteo el start millis del stopwatch
      elapsedMillis = 0;
      startMillis = 0;
      durMM = 0;

      break;
    case 131:
      currentMenu = 132;
      Drawing(Menu132, 1);
      lcd.setCursor(4, 0);
      lcd.print(Setpoint);// Este valor es fijo, no hace falta refresh
      lcd.setCursor(9, 0);
      lcd.write(2);
      lcd.setCursor(10, 0);
      lcd.print("C");

      lcd.setCursor(7, 1);//Grados LM35
      lcd.write(2);
      lcd.setCursor(8, 1);
      lcd.print("C");

      lcd.setCursor(18, 1); //Grados T_C
      lcd.write(2);
      lcd.setCursor(19, 1);
      lcd.print("C");
      temporizadorOn = true; // Comienzo a contar
      //
      break;
    case 132:
      currentMenu = 134;
      cursorPos = 3;
      Drawing(Menu134, 3);

      //Serial.println("Sali");
      break;
    case 111:
      currentMenu = 11;
      cursorPos = 0;
      Drawing(Menu11, 0);
      //Serial.println("Sali");
      break;
    case 113:

      if ( hourOrMinute == 1) {
        hourOrMinute = 0;
      }
      else if (hourOrMinute == 0) {
        currentMenu = 11;
        cursorPos = 2;
        Drawing(Menu11, 0);
      }

      // Serial.println("Sali");
      break;
    case 12:
      currentMenu = 1;
      Drawing(Menu1, 0);
      // Serial.println("Sali");
      break;
    case 13:
      switch (cursorPos) {
        case 2:
          currentMenu = 131;
          Drawing(Menu131, 2);
          break;
        case 3:
          currentMenu = 1;
          cursorPos = 2;
          Drawing(Menu1, 0);
          pidOn = false;
          FanSpeed();
          analogWrite(R_LOAD, 0);
          firstSet=true;         
          break;
      }
      break;

    case 14:
      currentMenu = 1;
      Drawing(Menu1, 0);
      Serial.println("Sali");
      break;
    case 11:
      switch (cursorPos) {
        case 0:
          currentMenu = 111;        
          Drawing(Menu111, 2);
          lcd.setCursor(11, 2);
          lcd.write(2);
          lcd.setCursor(12, 2);
          lcd.print("C");
          //Serial.println("Entre");
          break;
        case 1:
           currentMenu = 113;
          Drawing(Menu113, 2);
          hourOrMinute = 1;
          break;
        case 2:
        analogWrite(fan,255);
        lcd.setCursor(19, 0);
        lcd.print('C');
        delay(30000);
        analogWrite(fan,0);
        

        case 3:
          currentMenu = 1;
          cursorPos = 0;
          Drawing(Menu1, 0);
          break;
          Serial.println("Sali");
      }
      break;
    case 1: // Si estoy en el menu ppal
      switch (cursorPos) {
        case 0:
          cursorPos = 0;
          currentMenu = 11;
          Drawing(Menu11, 0);        
          break;
        case 1:
          currentMenu = 12;
          Drawing(Menu12, 1);
          lcd.setCursor(4, 0);
          lcd.print(Setpoint);// Este valor es fijo, no hace falta refresh
          lcd.setCursor(9, 0);
          lcd.write(2);
          lcd.setCursor(10, 0);
          lcd.print("C");
          break;
        case 2:
          currentMenu = 13;
          Drawing(Menu13, 3);
          cursorPos = 2;
          pidOn = true;
          FanSpeed();
          break;
        case 3:
          currentMenu = 14;
          Drawing(Menu14, 2);
          break;
      }
  }
}
