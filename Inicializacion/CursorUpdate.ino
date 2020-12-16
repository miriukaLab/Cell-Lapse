/*
   Esta funcion se basa en actualizar la actual pantalla cuando existe un cambio en la posicion en el eje y, cambiando la posicion
   del puntero. Solo se aplica a pantalla de menu/opciones en las que el cursor debe moverse
*/
void UpdateCursor() {
  switch (currentMenu) {
    case 1:
      Drawing(Menu1, 0);
      break;
    case 11:
      Drawing(Menu11, 0);
      break; 
    case 13:
      Drawing(Menu13, 3);
      break;
    case 134:
    Drawing(Menu134,3);
    break;
  }
}
