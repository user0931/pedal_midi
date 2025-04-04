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
U8G2_SSD1309_128X64_NONAME0_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8); 

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

/* Variable con el texto del display */

// char txt_disp;

const char * pos_1 = "2";
const char * pos_2 = "A";

/* Librería para MIDI */
#include <MIDI.h>
//MIDI_CREATE_DEFAULT_INSTANCE();
MIDI_CREATE_INSTANCE(HardwareSerial,Serial, midiOut); // create a MIDI object called midiOut

/*  Variables para MIDI */
//  int CCMidi = 60;
//  int CCMidiValue;
int CHMidi = 1;

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
  //Serial.print("Comienza función: ");
  //Serial.println(__func__);
  //Serial.println("Pulsado boton 1 cambio Stomps");
  if (est_1_1 == false) {
     envia_cc_midi(60,0,CHMidi);
     digitalWrite(led_1_1, HIGH);
     draw2("Tuner","1");
     est_1_1 = true;
  } else {
    envia_cc_midi(60,127,CHMidi);
    digitalWrite(led_1_1, LOW);
    draw2("      ","2");
    est_1_1 = false;
  }

  // parpadea(led_1_1);

  //Serial.print("Fin de la función: ");
  //Serial.println(__func__);
  
  //draw1("44", "z");
  // Envia comando Midi
  envia_cc_midi(60,0,1);
}
void button_1_2_pressed() { 
  //Serial.print("Comienza función: ");
  //Serial.println(__func__);
  //Serial.println("Pulsado boton 2 cambio Stomps");
  envia_cc_midi(79,0,CHMidi);
  // parpadea(led_1_2);
  // draw2("Stomp","2");
  //Serial.print("Fin de la función: ");
  //Serial.println(__func__);
  //draw1("44", "z");
}
void button_1_3_pressed() { 
  //Serial.print("Comienza función: ");
  //Serial.println(__func__);
  //Serial.println("Pulsado boton 3 cambio Stomps");
  // parpadea(led_1_3);
  envia_cc_midi(80,0,CHMidi);
  // draw2("Stomp","3");
  //Serial.print("Fin de la función: ");
  //Serial.println(__func__);
}
void button_1_4_pressed() { 
  //Serial.print("Comienza función: ");
  //Serial.println(__func__);
  //Serial.println("Pulsado boton 4 cambio Stomps");
  // parpadea(led_1_4);
  envia_cc_midi(81,0,CHMidi);
  //draw2("Stomp","4");
  //Serial.print("Fin de la función: ");
  //Serial.println(__func__);
}
void button_1_5_pressed() { 
  //Serial.print("Comienza función: ");
  //Serial.println(__func__);
  //Serial.println("Pulsado boton incrementa performance");
  //parpadea(led_1_5);
  envia_cc_midi(29,0,CHMidi);
  //draw2("Perform","+");
  //Serial.print("Fin de la función: ");
  //Serial.println(__func__);
}
void button_2_1_pressed() { 
  //Serial.print("Comienza función: ");
  //Serial.println(__func__);
  //Serial.println("Pulsado boton 1 cambio Effects");
  //parpadea(led_2_1);
  envia_cc_midi(28,0,CHMidi);
  //draw2("Efects","1");
  //Serial.print("Fin de la función: ");
  //Serial.println(__func__);
}
void button_2_2_pressed() { 
  //Serial.print("Comienza función: ");
  //Serial.println(__func__);
  //Serial.println("Pulsado boton 2 cambio Effects");
  //parpadea(led_2_2);
  envia_cc_midi(28,127,CHMidi);
  //draw2("Efects","2");
  //Serial.print("Fin de la función: ");
  //Serial.println(__func__);
}
void button_2_3_pressed() { 
  //Serial.print("Comienza función: ");
  //Serial.println(__func__);
  //Serial.println("Pulsado boton 3 cambio Effects");
  //parpadea(led_2_3);
  envia_cc_midi(22,0,CHMidi);
  //draw2("Efects","3");
  //Serial.print("Fin de la función: ");
  //Serial.println(__func__);
}
void button_2_4_pressed() { 
  //Serial.print("Comienza función: ");
  //Serial.println(__func__);
  //Serial.println("Pulsado boton 4 cambio Effects");
  //parpadea(led_2_4);
  envia_cc_midi(23,0,CHMidi);
  //draw2("Efects","4");
  //Serial.print("Fin de la función: ");
  //Serial.println(__func__);
}
void button_2_5_pressed() { 
  //Serial.print("Comienza función: ");
  //Serial.println(__func__);
  //Serial.println("Pulsado boton decrementa performance");
  // parpadea(led_2_5);
  envia_cc_midi(29,127,CHMidi);
  //draw2("Perform","-");
  //Serial.print("Fin de la función: ");
  //Serial.println(__func__);
}
void button_3_1_pressed() { 
  //Serial.print("Comienza función: ");
  //Serial.println(__func__);
  //Serial.println("Pulsado boton 1 cambio Performance");
  // parpadea(led_3_1);
  envia_cc_midi(26,0,CHMidi);
  //draw2("Perform","1");
  //Serial.print("Fin de la función: ");
  //Serial.println(__func__);
}
void button_3_2_pressed() { 
  //Serial.print("Comienza función: ");
  //Serial.println(__func__);
  //Serial.println("Pulsado boton 2 cambio Performance");
  // parpadea(led_3_2);
  envia_cc_midi(27,0,CHMidi);
  //draw2("Perform","2");
  //Serial.print("Fin de la función: ");
  //Serial.println(__func__);
}
void button_3_3_pressed() { 
  //Serial.print("Comienza función: ");
  //Serial.println(__func__);
  //Serial.println("Pulsado boton 3 cambio Performance");
  //parpadea(led_3_3);
  envia_cc_midi(25,1,CHMidi);
  //draw2("Perform","3");
  //Serial.print("Fin de la función: ");
  //Serial.println(__func__);
}
void button_3_4_pressed() { 
  //Serial.print("Comienza función: ");
  //Serial.println(__func__);
  //Serial.println("Pulsado boton 4 cambio Performance");
  //parpadea(led_3_4);
  envia_cc_midi(25,2,CHMidi);
  //draw2("Perform","4");
  //Serial.print("Fin de la función: ");
  //Serial.println(__func__);
}
void button_3_5_pressed() { 
  //Serial.print("Comienza función: ");
  //Serial.println(__func__);
  //Serial.println("Pulsado boton 5 cambio Performance");
  //parpadea(led_3_5);
  envia_cc_midi(25,3,CHMidi);
  //draw2("Perform","5");
  //Serial.print("Fin de la función: ");
  //Serial.println(__func__);
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
    draw2("666666","222222");
    delay(1000);
    draw2("7777777","2222222");
    delay(1000);
    draw2("12345678","12345678");
    delay(1000);
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
