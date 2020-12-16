void FanSpeed() {
  if (pidOn == true) {
    switch (Fs) {
      case 0:
        analogWrite(fan, 255);
        delay(2000);
        analogWrite(fan,225);
        delay(2000);
        analogWrite(fan,200);
        delay(2000);
        analogWrite(fan, 100);
        delay(2000);
        analogWrite(fan,68);
        break;
      case 1:
        analogWrite(fan, 255);
        delay(4000);
        analogWrite(fan, 113); 
        break;
      case 2:
        analogWrite(fan, 255);
        break;
    }
  }
  else {
   analogWrite(fan, 0);
  }
}

int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}    
  
