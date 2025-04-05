#include <Arduino.h>
//#include "avr8-stub.h"

/*                  Libreria para la gestión de los pulsadores */
#include <Pushbutton.h>

/*                  Includes para la pantalla */
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
/* Pantalla de 128*64 SPI */
U8G2_SSD1309_128X64_NONAME0_F_4W_SW_SPI u8g2(U8G2_R2, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8); 

/* Definimos los pulsadores y les asignamos el pin donde están conectados. Primer numero fila, segundo columna por ejemplo 1_5 fila 1 quinto pulsador*/
//#define DEF_BUTTON_1_1 26
//Pushbutton button_1_1(DEF_BUTTON_1_1);
Pushbutton button_1_1(26);
Pushbutton button_1_2(28);
Pushbutton button_1_3(24);
Pushbutton button_1_4(16);
Pushbutton button_1_5(14);
Pushbutton button_2_1(31);
Pushbutton button_2_2(32);
Pushbutton button_2_3(18);
Pushbutton button_2_4(3);
Pushbutton button_2_5(4);
Pushbutton button_3_1(34);
Pushbutton button_3_2(36);
Pushbutton button_3_3(48);
Pushbutton button_3_4(50);
Pushbutton button_3_5(52);

/* Definimos los leds y les asignamos el pin donde están conectados- Primer numero fila, segundo columna por ejemplo 1_5 fila 1 quinto led  */ 
int led_1_1 = 27;
int led_1_2 = 29;
int led_1_3 = 25;
int led_1_4 = 17;
int led_1_5 = 15;
int led_2_1 = 30;
int led_2_2 = 33;
int led_2_3 = 19;
int led_2_4 = 2;
int led_2_5 = 5;
int led_3_1 = 35;
int led_3_2 = 37;
int led_3_3 = 49;
int led_3_4 = 51;
int led_3_5 = 53;

/* Definimos variables para el estado del pulsador */

bool est_1_1 = false;
bool est_1_2 = false;
bool est_1_3 = false;
bool est_1_4 = false;
bool est_1_5 = false;
bool est_2_1 = false;
bool est_2_2 = false;
bool est_2_3 = false;
bool est_2_4 = false;
bool est_2_5 = false;
bool est_3_1 = false;
bool est_3_2 = false;
bool est_3_3 = false;
bool est_3_4 = false;
bool est_3_5 = false;


//   Estructura para los datos de cada pedal

struct PEDAL
   {   byte  CCMidi     ;      // CC midi
       byte  CCValor    ;      // Valor del CC midi
       byte  CCCanal    ;      // Canal midi
       char* Texto1     ;      // Texto en linea1 de la pantalla
       char* Texto2     ;      // Texto en linea2 de la pantalla
       bool  Persis_Led ;      // Indica si el led debe quedarse encendido o no
   } ;

// Cuando hay que enviar un valor para activarlo y otro para desactivarlo.

PEDAL P1_1_ON  = {60,127,1,"Tuner","On",true};           // Activación
PEDAL P1_1_OFF = {60,0,1,"Tuner","Off",false};       // Desactivación
PEDAL P1_2_ON  = {79,0,1,"FS1","",true};             // Activación
PEDAL P1_2_OFF = P1_2_ON;                              // Desactivación
PEDAL P1_3_ON  = {80,0,1,"FS2","",true};             // Activación
PEDAL P1_3_OFF = P1_3_ON;                              // Desactivación
PEDAL P1_4_ON  = {81,0,1,"FS3","",true};             // Activación
PEDAL P1_4_OFF = P1_4_ON;                              // Desactivación
PEDAL P1_5_ON  = {29,0,1,"Mode 1","Footsw",true};      // Activación
PEDAL P1_5_OFF = {29,127,1,"Mode 2","FX Chain",true};  // Desactivación
PEDAL P2_1_ON  = {28,0,1,"  Patch ","  Mode ",true};   // Activación
PEDAL P2_1_OFF = {28,127,1,"  Stomp","  Mode ",false};   // Desactivación
PEDAL P2_2_ON  = {13,0,1,"Pedal 1","On",true};         // Activación
PEDAL P2_2_OFF = {13,127,1,"Pedal 2","On",false};      // Desactivación
PEDAL P2_3_ON  = {22,0,1,"Bank -","",true};          // Activación
PEDAL P2_3_OFF = P1_3_ON;                              // Desactivación
PEDAL P2_4_ON  = {23,0,1,"Bank +","",true};          // Activación
PEDAL P2_4_OFF = P1_4_ON;                              // Desactivación
PEDAL P2_5_ON  = {13,0,1,"EXP 1","",true};  // Activación
PEDAL P2_5_OFF = {13,127,1,"EXP 2","",true};                              // Desactivación
PEDAL P3_1_ON  = {26,0,1,"Patch -","",true};           // Activación
PEDAL P3_1_OFF = P3_1_ON;                              // Desactivación
PEDAL P3_2_ON  = {27,0,1,"Patch +","",true};           // Activación
PEDAL P3_2_OFF = P1_2_ON;                              // Desactivación
PEDAL P3_3_ON  = {25,1,1,"Scene 1","   On",true};      // Activación
PEDAL P3_3_OFF = P1_3_ON;                              // Desactivación
PEDAL P3_4_ON  = {25,2,1,"Scene 2","   On",true};      // Activación
PEDAL P3_4_OFF = P1_4_ON;                              // Desactivación
PEDAL P3_5_ON  = {25,3,1,"Scene 3","   On",true};      // Activación
PEDAL P3_5_OFF = P1_5_ON;                              // Desactivación

/* Variables con el texto del display */
const char * pos_1 = "2";
const char * pos_2 = "A";

/* Variables para almacenar estado de FS y Escena*/
int estado_fs;
int estado_escena;

/* Librería para MIDI */
#include <MIDI.h>
MIDI_CREATE_INSTANCE(HardwareSerial,Serial, midiOut); // create a MIDI object called midiOut

void draw1(char * pos_x,char * pos_y) {
  
  //Serial.println("Estamos en función draw1");
  u8g2.clearBuffer();					// clear the internal memory
  //u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  //u8g2.setFont(u8g2_font_ncenB24_tr);
  // OK u8g2.setFont(u8g2_font_inr42_mf);
  u8g2.setFont(u8g2_font_inr42_mr);
  u8g2.setCursor(15,10);
  //u8g2.print(pos_1);
  // OK u8g2.drawStr(5,50,"A1");	// write something to the internal memory
  u8g2.drawStr(5,50,pos_x);	// write something to the internal memory
  // u8g2.drawStr(70,50,pos_2);	// write something to the internal memory
  u8g2.drawStr(70,50,pos_y);	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
  delay(1000);  
  //Serial.println("Fin de función draw1");
}
void draw2(char * texto1,char * texto2) {
  //Serial.print("Comienza función: ");
  //Serial.println(__func__);
  u8g2.clearBuffer();					// clear the internal memory
  //u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  //u8g2.setFont(u8g2_font_inr42_mr);	// choose a suitable font
  // JGL u8g2.setFont(u8g2_font_callite24_tr);
  /*   Con el font u8g2_font_courB18_tf caben max. 8 caracteres */
  u8g2.setFont(u8g2_font_courB18_tf);
  u8g2.drawStr(5,20,texto1);	// write something to the internal memory
  //u8g2.drawStr(5,30,"1_1");	// write something to the internal memory
  u8g2.drawStr(5,40,texto2);	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
  delay(100);
  //Serial.print("Texto1 es: ");
  //Serial.println(texto1);
  //Serial.print("Texto2 es: ");
  //Serial.println(texto2);
  //Serial.print("Fin de la función: ");
  //Serial.println(__func__);
}
void parpadea(int led_x) {
    // blink LED
  //Serial.print("Comienza función: ");
  //Serial.println(__func__);
  //Serial.print("Recibido parámetro:");
  //Serial.println(led_x);
  int blink = 0;
  do
  {
    digitalWrite(led_x, HIGH);
    delay(30);
    digitalWrite(led_x, LOW);
    delay(30);
  } while (blink++ < 5);
  //Serial.print("Fin de la función: ");
  //Serial.println(__func__);
}
void envia_cc_midi(int CCMidi,int CCMidiValue,int CHMidi){
  midiOut.sendControlChange(CCMidi,CCMidiValue,CHMidi);
}
void test_led(){

  /*for(int x = 1; x<4; x++){
    for(int y = 1; y < 6; y++){
      char sx[2];
      itoa(x,sx,10);
      char sy[2];
      itoa(y,sy,10);
      String led_x_y;
      led_x_y = "led_" + sx + "_" + sy;
      parpadea(led_x_y);
      delay(50);
    }
  }*/
  //Serial.print("Comienza función: ");
  //Serial.println(__func__);
  parpadea(led_1_1);
  parpadea(led_1_2);
  parpadea(led_1_3);
  parpadea(led_1_4);
  parpadea(led_1_5);

  parpadea(led_2_1);
  parpadea(led_2_2);
  parpadea(led_2_3);
  parpadea(led_2_4);
  parpadea(led_2_5);

  parpadea(led_3_1);
  parpadea(led_3_2);
  parpadea(led_3_3);
  parpadea(led_3_4);
  parpadea(led_3_5);
  //Serial.print("Fin de la función: ");
  //Serial.println(__func__);
}
void button_1_1_pressed() {
  envia_cc_midi(P1_1_ON.CCMidi,P1_1_ON.CCValor,P1_1_ON.CCCanal);
  digitalWrite(led_1_1, HIGH);
  draw2(P1_1_ON.Texto1,P1_1_ON.Texto2);
  est_1_1 = true;
  button_1_1.waitForPress();
  envia_cc_midi(P1_1_OFF.CCMidi,P1_1_OFF.CCValor,P1_1_OFF.CCCanal);
  digitalWrite(led_1_1, LOW);
  draw2(P1_1_OFF.Texto1,P1_1_OFF.Texto2);
  est_1_1 = false;
}
void button_1_2_pressed() {
    envia_cc_midi(P1_2_ON.CCMidi,P1_2_ON.CCValor,P1_2_ON.CCCanal);
    estado_fs = 1;
    digitalWrite(led_1_2, HIGH);
    digitalWrite(led_1_3, LOW);
    digitalWrite(led_1_4, LOW);
    draw2(P1_2_ON.Texto1,P1_2_ON.Texto2);
}
void button_1_3_pressed() { 
  envia_cc_midi(P1_3_ON.CCMidi,P1_3_ON.CCValor,P1_3_ON.CCCanal);
  estado_fs = 2;
  digitalWrite(led_1_2, LOW);
  digitalWrite(led_1_3, HIGH);
  digitalWrite(led_1_4, LOW);
  draw2(P1_3_ON.Texto1,P1_3_ON.Texto2);
}
void button_1_4_pressed() { 
  envia_cc_midi(P1_4_ON.CCMidi,P1_4_ON.CCValor,P1_4_ON.CCCanal);
  estado_fs = 3;
  digitalWrite(led_1_2, LOW);
  digitalWrite(led_1_3, LOW);
  digitalWrite(led_1_4, HIGH);
  draw2(P1_4_ON.Texto1,P1_4_ON.Texto2);
}
void button_1_5_pressed() { 
  if (est_1_5 == false) {
    envia_cc_midi(P1_5_ON.CCMidi,P1_5_ON.CCValor,P1_5_ON.CCCanal);
    digitalWrite(led_1_5, HIGH);
    draw2(P1_5_ON.Texto1,P1_5_ON.Texto2);
    delay(1000);
    digitalWrite(led_1_5, LOW);
    est_1_5 = true;
  } else {
    envia_cc_midi(P1_5_OFF.CCMidi,P1_5_OFF.CCValor,P1_5_OFF.CCCanal);
    digitalWrite(led_1_5, HIGH);
    draw2(P1_5_OFF.Texto1,P1_5_OFF.Texto2);
    delay(1000);
    digitalWrite(led_1_5, LOW);
    est_1_5 = false;
  }
}
void button_2_1_pressed() {
  if (est_2_1 == false) {
    envia_cc_midi(P2_1_ON.CCMidi,P2_1_ON.CCValor,P2_1_ON.CCCanal);
    digitalWrite(led_2_1, HIGH);
    draw2(P2_1_ON.Texto1,P2_1_ON.Texto2);
    delay(1000);
    digitalWrite(led_2_1, LOW);
    est_2_1 = true;
  } else {
    envia_cc_midi(P2_1_OFF.CCMidi,P2_1_OFF.CCValor,P2_1_OFF.CCCanal);
    digitalWrite(led_2_1, HIGH);
    draw2(P2_1_OFF.Texto1,P2_1_OFF.Texto2);
    delay(1000);
    digitalWrite(led_2_1, LOW);
    est_2_1 = false;
  }
}
void button_2_2_pressed() { 
  if (est_2_2 == false) {
    envia_cc_midi(P2_2_ON.CCMidi,P2_2_ON.CCValor,P2_2_ON.CCCanal);
    digitalWrite(led_2_2, HIGH);
    draw2(P2_2_ON.Texto1,P2_2_ON.Texto2);
    delay(1000);
    digitalWrite(led_2_2, LOW);
    est_2_2 = true;
  } else {
    envia_cc_midi(P2_2_OFF.CCMidi,P2_2_OFF.CCValor,P2_2_OFF.CCCanal);
    digitalWrite(led_2_2, HIGH);
    draw2(P2_2_OFF.Texto1,P2_2_OFF.Texto2);
    delay(1000);
    digitalWrite(led_2_2, LOW);
    est_2_2 = false;
  }
}
void button_2_3_pressed() { 
  envia_cc_midi(P2_3_ON.CCMidi,P2_3_ON.CCValor,P2_3_ON.CCCanal);
  digitalWrite(led_2_3, HIGH);
  draw2(P2_3_ON.Texto1,P2_3_ON.Texto2);
  delay(500);
  digitalWrite(led_2_3, LOW);
}
void button_2_4_pressed() { 
  envia_cc_midi(P2_4_ON.CCMidi,P2_4_ON.CCValor,P2_4_ON.CCCanal);
  digitalWrite(led_2_4, HIGH);
  draw2(P2_4_ON.Texto1,P2_4_ON.Texto2);
  delay(500);
  digitalWrite(led_2_4, LOW);
}
void button_2_5_pressed() { 
  if (est_2_5 == false) {
    envia_cc_midi(P2_5_ON.CCMidi,P2_5_ON.CCValor,P2_5_ON.CCCanal);
    digitalWrite(led_2_5, HIGH);
    draw2(P2_5_ON.Texto1,P2_5_ON.Texto2);
    delay(1000);
    digitalWrite(led_2_5, LOW);
    est_2_5 = true;
  } else {
    envia_cc_midi(P1_5_OFF.CCMidi,P1_5_OFF.CCValor,P1_5_OFF.CCCanal);
    digitalWrite(led_1_5, HIGH);
    draw2(P1_5_OFF.Texto1,P1_5_OFF.Texto2);
    delay(1000);
    digitalWrite(led_1_5, LOW);
    est_1_5 = false;
  }
}
void button_3_1_pressed() { 
  envia_cc_midi(P3_1_ON.CCMidi,P3_1_ON.CCValor,P3_1_ON.CCCanal);
  digitalWrite(led_3_1, HIGH);
  draw2(P3_1_ON.Texto1,P3_1_ON.Texto2);
  delay(500);
  digitalWrite(led_3_1, LOW);
}
void button_3_2_pressed() { 
  envia_cc_midi(P3_2_ON.CCMidi,P3_2_ON.CCValor,P3_2_ON.CCCanal);
  digitalWrite(led_3_2, HIGH);
  draw2(P3_2_ON.Texto1,P3_2_ON.Texto2);
  delay(500);
  digitalWrite(led_3_2, LOW);
}
void button_3_3_pressed() { 
  envia_cc_midi(P3_3_ON.CCMidi,P3_3_ON.CCValor,P3_3_ON.CCCanal);
  estado_escena = 1;
  digitalWrite(led_3_3, HIGH);
  digitalWrite(led_3_4, LOW);
  digitalWrite(led_3_5, LOW);
  draw2(P3_3_ON.Texto1,P3_3_ON.Texto2);
}
void button_3_4_pressed() { 
  envia_cc_midi(P3_4_ON.CCMidi,P3_4_ON.CCValor,P3_4_ON.CCCanal);
  estado_escena = 2;
  digitalWrite(led_3_3, LOW);
  digitalWrite(led_3_4, HIGH);
  digitalWrite(led_3_5, LOW);
  draw2(P3_4_ON.Texto1,P3_4_ON.Texto2);
}
void button_3_5_pressed() { 
  envia_cc_midi(P3_5_ON.CCMidi,P3_5_ON.CCValor,P3_5_ON.CCCanal);
  estado_escena = 3;
  digitalWrite(led_3_3, LOW);
  digitalWrite(led_3_4, LOW);
  digitalWrite(led_3_5, HIGH);
  draw2(P3_5_ON.Texto1,P3_5_ON.Texto2);
}
void setup() {  
    // Serial.begin(115200);
    //                  Velocidad del puerto MIDI 
    midiOut.begin(31250);
    u8g2.begin();
    /*                  Inicializamos como output los pines a los que están conectados los leds*/
    pinMode(led_1_1, OUTPUT);
    pinMode(led_1_2, OUTPUT);
    pinMode(led_1_3, OUTPUT);
    pinMode(led_1_4, OUTPUT);
    pinMode(led_1_5, OUTPUT);
    pinMode(led_2_1, OUTPUT);
    pinMode(led_2_2, OUTPUT);
    pinMode(led_2_3, OUTPUT);
    pinMode(led_2_4, OUTPUT);
    pinMode(led_2_5, OUTPUT);
    pinMode(led_3_1, OUTPUT);
    pinMode(led_3_2, OUTPUT);
    pinMode(led_3_3, OUTPUT);
    pinMode(led_3_4, OUTPUT);
    pinMode(led_3_5, OUTPUT);
    //                  Lanzamos un test de leds donde se iluminarań todos en secuencia
    test_led();
}  


void loop() {  
   /* Si se pulsa algún pulsador llamamos a su función*/
   if (button_1_1.getSingleDebouncedPress())
   {
     button_1_1_pressed();
   }
   if (button_1_2.getSingleDebouncedPress())
   {
     button_1_2_pressed();
   }
   if (button_1_3.getSingleDebouncedPress())
   {
     button_1_3_pressed();
   }
   if (button_1_4.getSingleDebouncedPress())
   {
     button_1_4_pressed();
   }
   if (button_1_5.getSingleDebouncedPress())
   {
     button_1_5_pressed();
   }
   if (button_2_1.getSingleDebouncedPress())
   {
     button_2_1_pressed();
   }
   if (button_2_2.getSingleDebouncedPress())
   {
     button_2_2_pressed();
   }
   if (button_2_3.getSingleDebouncedPress())
   {
     button_2_3_pressed();
   }
   if (button_2_4.getSingleDebouncedPress())
   {
     button_2_4_pressed();
   }
   if (button_2_5.getSingleDebouncedPress())
   {
     button_2_5_pressed();
   }
   if (button_3_1.getSingleDebouncedPress())
   {
     button_3_1_pressed();
   }
   if (button_3_2.getSingleDebouncedPress())
   {
     button_3_2_pressed();
   }
   if (button_3_3.getSingleDebouncedPress())
   {
     button_3_3_pressed();
   }
   if (button_3_4.getSingleDebouncedPress())
   {
     button_3_4_pressed();
   }
   if (button_3_5.getSingleDebouncedPress())
   {
     button_3_5_pressed();
   }

}
