void setup() {
  //Pantalla
  delay(2000); // Inicialización de la pantalla
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);

  //Encoder
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(swPin, INPUT);
  //digitalWrite(swPin, HIGH);

  //Sensores
  pinMode(LM_1, INPUT);
  pinMode(R_LOAD, OUTPUT);
  pinMode(fan, OUTPUT);
  sensor.begin();

  T_C = sensor.readTemperature() ; // Lectura de datos AM2302
  H = sensor.readHumidity();



  //Characters
  welcomeScreen(0); // Pantalla de bienvenida
  //PID
  PID_R.SetOutputLimits(0, 255);
  //PID_R.SetSampleTime(0); // Por default esta seteada en 200, habría que analizar que frecuencia de sampleo es necesaria o si conviene usar interrupciones
  PID_R.SetMode(AUTOMATIC);//Se 'enciende' el pid
  Serial.begin (9600);
  BT.begin(9600);
  Avg_LM35.begin();
}
void loop() {
  Encoder_Mov();
  if ((digitalRead(swPin) == LOW) && (millis() > (btnTime + debounceTime))) { //Al menos una diferencia de 300 milisegundos
    Pages();
    btnTime = millis(); // Actualizo la variable de debounce
  }
  if ((millis() > (updateTime + sampleTime_US)) && (currentMenu == 12)) {
    T_C = medianFilter_Si7021.AddValue(sensor.readTemperature()); // Mediana de buffer circular -> Recordar que mediana mejor que promedio
    T_R = medianFilter_LM35.AddValue(analogRead(LM_1));
     T_R = (T_R * 149.00) / 1023.00; //33.44 mV/C -> debido a valores reales de resistencias
//    T_R = (T_R * 500.00) / 1023.00;

    screenUpdate(currentMenu);
    updateTime = millis();
  }

  if ((millis() > (updateTime + sampleTime_PID)) && (currentMenu == 13 || currentMenu == 132)) {
    T_C = medianFilter_Si7021.AddValue(sensor.readTemperature()); // Mediana de buffer circular -> Recordar que mediana mejor que promedio
    T_R = medianFilter_LM35.AddValue(analogRead(LM_1));
     T_R = (T_R * 149.00) / 1023.00; //33.44 mV/C -> debido a valores reales de resistencias
//    T_R = (T_R * 500.00) / 1023.00;
    T_Ra = Avg_LM35.reading(T_R);

    //  Serial.println("Leyo");
    if (pidOn == true) {
      if (firstSet == true) {
        if (T_C < 19.00) {
          Kp = 8.5, Ki = 1.8, Kd = 5.25;
          KpS = Kp/3.0, KiS = Ki/3.0, KdS = 7.25;
          // PID_R.SetOutputLimits(50, 245);

          //  Serial.println("Entre 1");
        }
        else if (T_C >= 19.00 && T_C < 20.00) {
          Kp = 7, Ki = 1.5, Kd = 5;
          KpS = Kp/3.0, KiS = Ki/3.0, KdS = 7.25;
          //  PID_R.SetOutputLimits(50, 235);
          //  Serial.println("Entre 2");
        }
        else if (T_C >= 20.00 && T_C < 20.50) {
          Kp = 6.25, Ki = 1.5, Kd = 5;
          KpS = Kp/3.0, KiS = Ki/3.0, KdS = 7.25;
          //Serial.println("Entre 2");
          // PID_R.SetOutputLimits(50, 220);
        }
        else if (T_C >= 20.00 && T_C < 21.00) {
          Kp = 6, Ki = 1.5, Kd = 5;
          KpS = Kp/3.0, KiS = Ki/3.0, KdS = 7.25;
          //Serial.println("Entre 2");
          // PID_R.SetOutputLimits(50, 220);
        }
        else if (T_C >= 21.00 && T_C < 21.5) {
          Kp = 5, Ki = 1.2, Kd = 5;
          KpS = Kp/3.0, KiS = Ki/3.0, KdS = 7.25;
          //Serial.println("Entre 3");
          // PID_R.SetOutputLimits(50, 195);
        }
        else if (T_C >= 21.5 && T_C < 22.0) {
          Kp = 4.5, Ki = 1.2, Kd = 5;
          KpS = Kp/3.0, KiS = Ki/3.0, KdS = 7.25;
          //Serial.println("Entre 3");
          // PID_R.SetOutputLimits(50, 195);
        }
        else if (T_C >= 22.00 && T_C < 22.5) {
          Kp = 3, Ki = 0.75, Kd = 5 ;
          KpS = Kp/3.0, KiS = Ki/3.0, KdS = 7.25;
          //Serial.println("Entre 5");
          // PID_R.SetOutputLimits(50, 185);
        }
        else if (T_C >= 22.5 && T_C < 23.0) {
          Kp = 3, Ki = 1, Kd = 5 ;
          KpS = Kp/3.0, KiS = Ki/3.0, KdS = 7.25;
          //Serial.println("Entre 5");
          // PID_R.SetOutputLimits(50, 185);
        }
        else if (T_C >= 23.00 && T_C < 23.5) {
          Kp = 2, Ki = 0.75, Kd = 5;
          KpS = Kp/3.0, KiS = Ki/3.0, KdS = 7.25;
          // Serial.println("Entre 7");
          // PID_R.SetOutputLimits(50, 180);
        }
        else if (T_C >= 23.50 && T_C < 24.0) {
          Kp = 2, Ki = 0.75, Kd = 5;
          KpS = Kp/3.0, KiS = Ki/3.0, KdS = 7.25;
          // Serial.println("Entre 7");
          // PID_R.SetOutputLimits(50, 180);
        }
        else if (T_C >= 24.0 && T_C < 24.5) {
          Kp = 2, Ki = 0.75, Kd = 5;
          KpS = Kp/3.0, KiS = Ki/3.0, KdS = 7.25;
          //  Serial.println("Entre 8");
          // PID_R.SetOutputLimits(50, 190);
        }
        else if (T_C >= 24.5 && T_C < 25.0) {
          Kp = 1.75, Ki = 0.6, Kd = 5;
          KpS = Kp/3.0, KiS = Ki/3.0, KdS = 7.25;
          //  Serial.println("Entre 8");
          // PID_R.SetOutputLimits(50, 190);
        }
        else if (T_C >= 25.0 && T_C < 25.5) {
          Kp = 1.75, Ki = 0.6, Kd = 4.9;
          KpS = Kp/3.0, KiS = Ki/3.0, KdS = 7.25;
          // Serial.println("Entre 9");
          //PID_R.SetOutputLimits(50, 190);
        }
        else if (T_C >= 25.50 && T_C < 26.0) {
          Kp = 1.5, Ki =0.5, Kd = 4.9;
          KpS = Kp/3.0, KiS = Ki/3.0, KdS = 7.25;
          // Serial.println("Entre 9");
          //PID_R.SetOutputLimits(50, 190);
        }
        else {
          Kp = 1, Ki = 0.5, Kd = 4.9;
          KpS = Kp/3.0, KiS = Ki/3.0, KdS = 7.25;
          //    Serial.println("Entre 10");
          //PID_R.SetOutputLimits(50, 185);
        }

        //        Serial.println(T_C);
        //        Serial.println(PID_R.GetKp());
        //        Serial.println(PID_R.GetKi());
        //        Serial.println(PID_R.GetKd());
        PID_R.SetTunings(Kp, Ki, Kd);
        firstSet = false;
      }
      errGap = (Setpoint - T_C);
      if ((errGap >= 0) && (errGap <= 5) && (PID_R.GetKp() != KpS)) {
        PID_R.SetTunings(KpS, KiS, KdS); //Soft tunnings
      }
      else if (((errGap < 0)||(errGap>5)) && (PID_R.GetKp() != Kp)) {
        PID_R.SetTunings(Kp, Ki, Kd);
      }
      ////
      //      if ((errGap <= (-0.75)) && (PID_R.GetKp() != KpS)) {
      //        PID_R.SetTunings(KpS, KiS, KdS); //Soft tunnings
      //      }
      //      else if ((errGap > (-0.75)) && (PID_R.GetKp() != Kp)) {
      //        PID_R.SetTunings(Kp, Ki, Kd);
      //      }

      PID_R.Compute();
      // Serial.println("Computo");
      analogWrite(R_LOAD, Output);
      // Serial.println("Output");
      // analogWrite(R_LOAD, 255);
      T_Cs = String(T_C);
      T_Rs = String(T_R);
      Hs= String(H);
      HeaterOuts = String(Output * 100 / 255);
      Final = T_Cs + ',' + T_Rs + ',' + HeaterOuts+ ','+Hs;// Concatenacion de variables para GUI
      //      char* F[1] = {Final}
      //BT.println(Final);
      Serial.println(Final);
      // Serial.print(PID_R.GetKp());
    }
    screenUpdate(currentMenu);
    //Serial.println("salio de screen up");

    updateTime = millis();
    //  Serial.println("update time");
  }
  //Serial.println(freeRam());
}
