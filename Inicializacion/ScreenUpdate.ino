/* De estar en una pantalla de estado, esta deberá actualizarse con el correr del tiempo y en función de cada variable, por lo que se realiza
  un refreshing en el loop
*/
void screenUpdate(int currentMenu) {
  switch (currentMenu) {
    case 132:
      if (temporizadorOn == true) {
        lcd.setCursor(4, 1);
        lcd.print(T_Ra); //LM1 de seguridad en calefactor
        //        lcd.setCursor(6, 1);
        //        lcd.write(2);
        //        lcd.setCursor(7, 1);
        //        lcd.print("C");

        // Sensado de humedad en la cámara
        H = constrain(sensor.readHumidity(), 0, 99);
        lcd.setCursor(14, 0);
        lcd.print(H);

        if (H < 10) {
          lcd.print(' ');
          lcd.setCursor(15, 0);
          lcd.print(H);
        }

        //Temperatura de camara-> sensor Si7021
        lcd.setCursor(13, 1);
        lcd.print(T_C);// Temperatura en cámara
        //        lcd.setCursor(17, 1);
        //        lcd.write(2);
        //        lcd.setCursor(18, 1);
        //        lcd.print("C");
        // Serial.println("imprimió pantallas");

        lcd.setCursor(7,3);
       // lcd.print(PID_R.GetKp());
        //Alarma
        if ((T_R >= 95) && (T_R < 500)) { // Alerta, si se superan los 95 grados en el calefactor , abortar ensayo
          lcd.clear();
          PID_R.SetMode(MANUAL);
          analogWrite(R_LOAD, 0); // Asegurarse de apagar corriente en R de carga
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Error 1:");
          lcd.setCursor(0, 1);
          lcd.print("Assay Aborted: Reset");
          pidOn = false;
          temporizadorOn = false;
          analogWrite(fan, 255);
          delay(30000);  //Enfrio durante 30 segundos y apago también el cooler
          analogWrite(fan, 0);
          currentMenu = 0;
          break;
          // Serial.println("salto alarma 1");
        }

        //Alarma 2
        if (T_C >= (Setpoint + 4)) { // Alerta, si se superan el setpoint por 3 grados, abortar ensayo
          lcd.clear();
          PID_R.SetMode(MANUAL);
          analogWrite(R_LOAD, 0);
          lcd.setCursor(0, 0);
          lcd.print("Error 2:");
          lcd.setCursor(0, 1);
          lcd.print("Assay Aborted");
          pidOn = false;
          temporizadorOn = false;
          analogWrite(fan, 255);
          delay(30000);  //Enfrio durante 15 segundos y apago también el cooler
          analogWrite(fan, 0);
          currentMenu = 0;
          break;
          //  Serial.println("salto alarma 2");

        }

        // Timer o Elapsed time
        while (firstTimeRead) {
          minNecesarios = minutos + horas * 60; // Calculo de minutos y horas restantes
          firstTimeRead = false;
          //Serial.println("seteo timer");
        }

        Temporizador();
        // Serial.println("salio timer");
      }

      lcd.setCursor(18, 3);
      lcd.write(loading);
      loading++;
      if (loading == 8) {
        loading = 4;
      }
      // Serial.println("terminó");
      break;

    case 12:
      lcd.setCursor(4, 1);
      lcd.print(int(T_R));//LM1 de seguridad
      lcd.setCursor(6, 1);
      lcd.write(2);
      lcd.setCursor(7, 1);
      lcd.print("C");

      // Sensado de humedad en la cámara
      lcd.setCursor(2, 2);
      H = constrain(sensor.readHumidity(), 0, 99);
      lcd.print(H); // Humedad en cámara

      //Temperatura de camara-> sensor / DHT22
      lcd.setCursor(13, 1);
      lcd.print(T_C);// Temperatura en cámara

      lcd.setCursor(18, 1);
      lcd.write(2);
      lcd.setCursor(19, 1);
      lcd.print("C");
      break;

    case 13:


      lcd.setCursor(4, 1);
      lcd.print(T_C); // Mediana de buffer circular -> Recordar que mediana mejor que promedio);
      lcd.setCursor(9, 1);
      lcd.write(2);
      lcd.setCursor(10, 1);
      lcd.print("C");

      lcd.setCursor(13, 1);
      lcd.print(Setpoint);// Temperatura de Setpoint
      lcd.setCursor(18, 1);
      lcd.write(2);
      lcd.setCursor(19, 1);
      lcd.print("C");

      if (T_C > (Setpoint - 2)) {
        lcd.setCursor(0, 0);
        lcd.print("Preparing: Ready!");
      }

      //Alarma
      if ((T_R >= 95) && (T_R < 500)) { // Alerta, si se superan los 149 grados en el calefactor , abortar ensayo
        lcd.clear();
        PID_R.SetMode(MANUAL);
        analogWrite(R_LOAD, 0); // Asegurarse de apagar corriente en R de carga
        lcd.clear();
          lcd.setCursor(0, 0);
        lcd.print("Error 1:");
        lcd.setCursor(0, 1);
        lcd.print("Assay Aborted");
        pidOn = false;
      }

      //Alarma 2
      if (T_C >= (Setpoint + 4)) { // Alerta, si se superan el setpoint por 10 grados, abortar ensayo
        lcd.clear();
        PID_R.SetMode(MANUAL);
        analogWrite(R_LOAD, 0);
        lcd.setCursor(0, 0);
        lcd.print("Error 2:");
        lcd.setCursor(0, 1);
        lcd.print("Assay Aborted");
        pidOn = false;
      }
      break;
  }

}
