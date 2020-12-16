void welcomeScreen(int option) {
  lcd.clear();
  byte tope[] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B00000,
    B00000,
    B00000,
    B00000
  };
  lcd.createChar(0, tope);

  byte piso[] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B11111,
    B11111,
    B11111,
    B11111
  };
  lcd.createChar(1, piso);
  //  byte der[] = {
  //    B00011,
  //    B00011,
  //    B00011,
  //    B00011,
  //    B00011,
  //    B00011,
  //    B00011,
  //    B00011
  //  };
  //
  //  lcd.createChar(2, der);
  //  byte izq[] = {
  //    B11000,
  //    B11000,
  //    B11000,
  //    B11000,
  //    B11000,
  //    B11000,
  //    B11000,
  //    B11000
  //  };
  //  lcd.createChar(3, izq);

byte back[] = {
  B00111,
  B00001,
  B00101,
  B01101,
  B11111,
  B01100,
  B00100,
  B00000
};
  lcd.createChar(3, back);

  byte esqSupIzq[] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11000,
    B11000,
    B11000,
    B11000
  };
  lcd.createChar(4, esqSupIzq);

  byte esqInfIzq[] = {
    B11000,
    B11000,
    B11000,
    B11000,
    B11111,
    B11111,
    B11111,
    B11111
  };

  lcd.createChar(5, esqInfIzq);

  byte esqInfDer[] = {
    B00111,
    B00111,
    B00111,
    B00111,
    B11111,
    B11111,
    B11111,
    B11111
  };
  lcd.createChar(6, esqInfDer);

  byte esqSupDer[] = {
    B11111,
    B11111,
    B11111,
    B00111,
    B00111,
    B00111,
    B00111,
    B00111
  };
  lcd.createChar(7, esqSupDer);
  byte grados[] = {
    B00000,
    B01110,
    B01010,
    B01110,
    B00000,
    B00000,
    B00000,
    B00000
  };
  lcd.createChar(2, grados);



  switch (option) {
    case 0:
      for (int i = 1; i <= 18; i++) {
        lcd.setCursor(i, 0);
        lcd.write(0);
      }
      for (int i = 1; i <= 18; i++) {
        lcd.setCursor(i, 3);
        lcd.write(1);
      }
//      lcd.setCursor(0, 1);
//      lcd.write(3);
//      lcd.setCursor(0, 2);
//      lcd.write(3);

//      lcd.setCursor(19, 1);
//      lcd.write(3);
//      lcd.setCursor(19, 2);
//      lcd.write(3);

      lcd.setCursor(0, 0);
      lcd.write(4);
      lcd.setCursor(19, 0);
      lcd.write(7);
      lcd.setCursor(0, 3);
      lcd.write(5);
      lcd.setCursor(19, 3);
      lcd.write(6);

      lcd.setCursor(5, 1);
      lcd.print(F("Welcome to"));
      lcd.setCursor(5, 2);
      lcd.print(F("Cell Lapse"));
      break;
    case 1:
        for (int i = 0; i <= 19; i++) {
        lcd.setCursor(i, 0);
        lcd.write(0);
      }
      for (int i = 0; i <= 19; i++) {
        lcd.setCursor(i, 3);
        lcd.write(1);
      }
    
      lcd.setCursor(2, 1);
      lcd.print(F("Assay Finished"));
      lcd.setCursor(0, 2);
      lcd.print(F("Remove Cell Culture"));

      break;
  }

}
