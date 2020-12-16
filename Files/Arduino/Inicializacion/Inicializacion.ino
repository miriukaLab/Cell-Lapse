#include <LiquidCrystal_I2C.h>
#include <PID_v1.h>
#include "MedianFilterLib.h"
#include "Adafruit_Si7021.h"
#include <SoftwareSerial.h> //-> Libreria
#include <movingAvg.h>  

Adafruit_Si7021 sensor = Adafruit_Si7021();

//Crear el objeto lcd  dirección  0x3F y 20 columnas x 4 filas
LiquidCrystal_I2C lcd(0x3f, 20, 4); // si no te sale con esta direccion  puedes usar (0x3f,16,2) || (0x27,16,2)  ||(0x20,16,2)
//Bluetooth
const int RX=10; //TX del módulo
const int TX=11; //RX del módulo
SoftwareSerial BT(RX, TX);// -> "Declaras" el objeto

//Encoder
const int clkPin = 10; 
const int dtPin = 9; 
const int swPin =8;  
int cursorPos = 0;// Inicializo Cursor
int OldcursorPos = 0;
long btnTime = 0;//Tiempo entre acciones de click
int debounceTime = 500; // Tiempo mínimo entre click y click

//Variables Setting control default
int hourOrMinute; // Utilizada en Menu 113 para el seteo de horas y minutos
int horas = 16; // Valor Default
int minutos = 30;// Valor Default
double Setpoint = 37;// Valor Default
int Fs = 2;// Valor Default -> equivale a velocidad de 100%
//char speeds[3][5] = {"25% ", "50% ", "100%"};
bool pidOn = false;



//Pantallas
char* Menu1[4] = {"Set Up", "General Status", "Start!", "About"};
char* Menu11[4] = {"Set Temperature", "Set Time", "Cooldown", "Back"};
char* Menu111[4] = {"Setpoint Temperature:", " ", "       T=", " "};
char* Menu112[4] = {"     Fan Speed:", " ", "       Fs=", " "};
char* Menu113[4] = {"    Assay Time:", " ", "      t=", " "};

char* Menu12[4] = { "Set:         ", "Tr:      Tc:    ", "H:  %", "Back"};

char* Menu13[4] = {"Preparing:Wait...", "Tc:       ->", "Go", "Cancel"};
char* Menu131[4] = {"Insert Cell Culture", "Into The Cell Lapse", " ", " "};
char* Menu132[4] = {"Set:        H:  %", "Tr:       Tc:   ", "Assay time:", "Abort"};
char* Menu134[4]={"Are you sure?"," ","Yes","No"};

char* Menu14[4] = {"Version 1.0", "FLENI-ITBA", "Joaquin Smucler", "jsmucler@itba.edu.ar"};


//Screen Functions; //Cantidad de pantallas existentes
int FilasEnPantalla = 4; //n-1
int currentMenu = 1;
int sampleTime_US = 3000; // Tiempo de actualización de pantalla de estado
int sampleTime_PID=1000; //estaba en 1000
long updateTime;
int loading=4;


//Stopwatch
unsigned long startMillis;
unsigned long currentMillis;
unsigned long elapsedMillis;
int durMM;
int watchFlag = 0;
int minNecesarios; // Cantidad de minutos que debe durar el experimento
int minFaltantes; // Cantidad de minutos hasta que el experimento termine
int hrsFaltantes; // Cantidad de horas hasta que el experimento termine

bool temporizadorOn = false; //Estado del temporizador
bool firstTimeRead=true; //Lectura de temperatura ambiente y elección del perfil PID

//PID
bool firstSet=true;
double T_R, T_C; // Temperatura resistencias, temperatura gabinete
int T_Ra; //Temperatura resistencias promedio
int H;
double Output;
double Kp,Ki,Kd;
double KpS,KiS,KdS;
double errGap;
//DATA
String T_Cs;
String T_Rs;
String HeaterOuts;
String Hs;
String Final;

PID PID_R(&T_C, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

//Sensores
#define LM_1 A0
#define R_LOAD 6 // Resistencia de carga// AL REVES
#define fan 3 //cooler 12V
MedianFilter<volatile double> medianFilter_Si7021(20);// buffer circular de 20 para Lectura de Si7021
MedianFilter<volatile double> medianFilter_LM35(5);// buffer circular de 20 para Lectura de LM35
movingAvg Avg_LM35(20);   
