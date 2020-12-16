/* Esta funcion lee la posicion en el eje Y y actualiza el lugar del puntero en el caso de estar en una pantalla de menues/opciones
  de ser una pantalla de setting, lo que hará es modificar el valor en cuestión.
  Para hacer el código más eficiente, la pantalla solo se refresca si existió un cambio.
  Además,se plantean dos posibilidades: Pantalla de menu/ opciones, que requiere movimiento del cursor entre 0 y 3
  o para pantallas de tipo seteo en las cuales el valor del cursor se utiliza para setear la variable en cuestion

*/

void Encoder_Mov() {
  if(currentMenu==132){
    return ;
    }
  
  static int oldA = HIGH; //set the oldA as HIGH
  static int oldB = HIGH; //set the oldB as HIGH
  int result = 0;

  int newA = digitalRead(clkPin);//read the value of clkPin to newA
  int newB = digitalRead(dtPin);//read the value of dtPin to newB
  if (newA != oldA || newB != oldB) //if the value of clkPin or the dtPin has changed
  {
    // something has changed
    if ((oldA == HIGH) && (newA == LOW))
    {
      result = (oldB * 2 - 1);
    }
  }
  oldA = newA;
  oldB = newB;
  //Si se encuentra enuna pantalla de menu/opcion

  if (currentMenu != 111 && currentMenu != 112 && currentMenu != 113 && currentMenu != 14 && currentMenu != 12 && currentMenu != 13 && currentMenu != 131 && currentMenu != 134) {
    result = (-1) * result;
    cursorPos = cursorPos + result;
    cursorPos = constrain(cursorPos, 0, 3);// Posiciones en el eje Y
    if (cursorPos != OldcursorPos) {
      UpdateCursor(); // Actualizo la pantalla si hubo un cambio
      OldcursorPos = cursorPos;
    }
  }
  else if (currentMenu == 111 || currentMenu == 112 || currentMenu == 113 || currentMenu == 13 || currentMenu == 134) {

    // si se encuentra en una pantalla de setting
    switch (currentMenu) {

      case 13: //Ya que esta pagina tiene solo 2 opciones de cursor necesito hacer un constrain especial
        result = (-1) * result;
        cursorPos = cursorPos + result;
        cursorPos = constrain(cursorPos, 2, 3);// Posiciones en el eje Y
        if (cursorPos != OldcursorPos) {
          UpdateCursor(); // Actualizo la pantalla si hubo un cambio
          OldcursorPos = cursorPos;
        }
        break;

      case 134: //Ya que esta pagina tiene solo 2 opciones de cursor necesito hacer un constrain especial
        result = (-1) * result;
        cursorPos = cursorPos + result;
        cursorPos = constrain(cursorPos, 2, 3);// Posiciones en el eje Y
        if (cursorPos != OldcursorPos) {
          UpdateCursor(); // Actualizo la pantalla si hubo un cambio
          OldcursorPos = cursorPos;
        }
        break;
      case 111:
        cursorPos = Setpoint; // Default, guarda la última selección.
        cursorPos = cursorPos + result; //Movimiento del cursor
        cursorPos = constrain(cursorPos, 30, 37.5); // Restringo a los valores posibles de temperatura de setpoint
        if (cursorPos != OldcursorPos) {
          lcd.setCursor(9, 2);
          lcd.print(cursorPos);// Escribo
          Setpoint = cursorPos;// Renuevo la opción elegida.
          // SetPoint=cursorPos;
          OldcursorPos = cursorPos;
        }
        break;

      case 113:
        // Dibujo tiempo por default/guardado en horas:minutos
              if (horas < 10) {
                lcd.setCursor(8,2);
                lcd.write('0');
                lcd.setCursor(9, 2);
                lcd.print(horas);// Escribo nuevo valor
              }
              else{
                lcd.setCursor(8, 2);
                lcd.print(horas);// Escribo nuevo valor
                }
        lcd.setCursor(10, 2);
        lcd.print(":");
        lcd.setCursor(11, 2);

        if (minutos < 10) {
          lcd.write('0');
          lcd.setCursor(12, 2);
          lcd.print(minutos);
        }

        else {
          lcd.print(minutos);
        }
        switch (hourOrMinute) {
          //Primero se setean las horas -> click-> seteo de minutos -> click (almaceno y back)
          case 1:
            cursorPos = horas;
            cursorPos = cursorPos + result; // Actualizo el valor
            cursorPos = constrain(cursorPos, 0, 23); // En principio máximo 8 horas de funcionamiento.
            horas = cursorPos;// Almaceno
            if (cursorPos != OldcursorPos) {
              lcd.setCursor(8, 2);
              if (cursorPos < 10) {
                lcd.write('0');
                lcd.setCursor(9, 2);
                lcd.print(cursorPos);// Escribo nuevo valor
              }
              else {
                lcd.print(cursorPos);
              }
                lcd.setCursor(10, 2);
                lcd.print(":");
              OldcursorPos = cursorPos;
            }
            break;
          // Si ya cliquee -> la variable hourOrMinuto cambió entonces el encoder pasa a setear minutos.
          case 0:
            cursorPos = minutos;
            cursorPos = cursorPos + result ; // Actualizo el valor
            cursorPos = constrain(cursorPos, 0, 59);
            minutos = cursorPos;
//            if (cursorPos > 59) {
//              cursorPos = 0;
//            }
//            else if (cursorPos < 0) {
//              cursorPos = 59;
//            }
            if (cursorPos != OldcursorPos) {
              lcd.setCursor(11, 2);
              if (minutos < 10) {
                lcd.write('0');
                lcd.setCursor(12, 2);
                lcd.print(minutos);
              }
              else {
                lcd.print(minutos);
              }
              OldcursorPos = cursorPos;
            }
            break;
        }
        break;
    }
  }
}
