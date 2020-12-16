/*
   Esta funcion se encarga de actualizar la pantalla(incluyendo al cusor ( llama a Update
   Esta segmentada segun sea una pantalla de menues/4 opciones [0] o pantalla de menues/ 2 opciones [3]
   o una pantalla de accion(seteo) o informacion con [1] o  sin [2] opcion back explicita.
  Tomará los strings declarados en el main
*/
void Drawing(char* interface[4], int i) {
  lcd.clear();
  delay(50);
  switch (i) {
    case 0: // ploteo de pantalla de menues
      for (int i = 0; i < FilasEnPantalla; i++) {
        lcd.setCursor(0, i);
        if (i == cursorPos) {  // Puntero
          lcd.print(interface[i]);
          lcd.print("<");
        }
        else {
          lcd.print(interface[i]);
        }
      }
      break;
    case 1: // Menu 12 -> informacion de sensores de temperatura/ PID andando y opción Abort -> cursor fijo en Back
      lcd.setCursor(0, 0);
      lcd.print(interface[0]);
      lcd.setCursor(0, 1);
      lcd.print(interface[1]);
      lcd.setCursor(0, 2);
      lcd.print(interface[2]);
      lcd.setCursor(0, 3);
      lcd.print(interface[3]);
      lcd.print("<");
      break;
    case 2: // Menues de seteo-> no necesito cursor
      lcd.setCursor(0, 0);
      lcd.print(interface[0]);
      lcd.setCursor(0, 1);
      lcd.print(interface[1]);
      lcd.setCursor(0, 2);
      lcd.print(interface[2]);
      lcd.setCursor(0, 3);
      lcd.print(interface[3]);
      break;
    case 3: // Pantalla con menu Go o Back.
      cursorPos = constrain(cursorPos, 2, 3);
      for (int i = 0; i < FilasEnPantalla; i++) {
        lcd.setCursor(0, i);
        if (i == cursorPos) {
          lcd.print(interface[i] );
          lcd.print("<");
        }
        else {
          lcd.print(interface[i]);
        }
      }
      break;
  }
}
