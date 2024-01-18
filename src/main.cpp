#include <Arduino.h>

/* Libreria para la gestión de los pulsadores */
#include <Pushbutton.h>

/* Includes para la pantalla */
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
#define DEF_BUTTON_1_1 22
Pushbutton button_1_1(DEF_BUTTON_1_1);
#define DEF_BUTTON_1_2 24
Pushbutton button_1_2(DEF_BUTTON_1_2);
#define DEF_BUTTON_1_3 26
Pushbutton button_1_3(DEF_BUTTON_1_3);
#define DEF_BUTTON_1_4 28
Pushbutton button_1_4(DEF_BUTTON_1_4);
#define DEF_BUTTON_1_5 30
Pushbutton button_1_5(DEF_BUTTON_1_5);
#define DEF_BUTTON_2_1 32
Pushbutton button_2_1(DEF_BUTTON_2_1);
#define DEF_BUTTON_2_2 34
Pushbutton button_2_2(DEF_BUTTON_2_2);
#define DEF_BUTTON_2_3 36
Pushbutton button_2_3(DEF_BUTTON_2_3);
#define DEF_BUTTON_2_4 38
Pushbutton button_2_4(DEF_BUTTON_2_4);
#define DEF_BUTTON_2_5 40
Pushbutton button_2_5(DEF_BUTTON_2_5);
#define DEF_BUTTON_3_1 42
Pushbutton button_3_1(DEF_BUTTON_3_1);
#define DEF_BUTTON_3_2 44
Pushbutton button_3_2(DEF_BUTTON_3_2);
#define DEF_BUTTON_3_3 46
Pushbutton button_3_3(DEF_BUTTON_3_3);
#define DEF_BUTTON_3_4 48
Pushbutton button_3_4(DEF_BUTTON_3_4);
#define DEF_BUTTON_3_5 50
Pushbutton button_3_5(DEF_BUTTON_3_5);


/* Definimos los leds y les asignamos el pin donde están conectados- Primer numero fila, segundo columna por ejemplo 1_5 fila 1 quinto led  */ 
int led_1_1 = 23;
int led_1_2 = 25;
int led_1_3 = 27;
int led_1_4 = 29;
int led_1_5 = 31;
int led_2_1 = 33;
int led_2_2 = 35;
int led_2_3 = 37;
int led_2_4 = 39;
int led_2_5 = 41;
int led_3_1 = 43;
int led_3_2 = 45;
int led_3_3 = 47;
int led_3_4 = 49;
int led_3_5 = 51;


const char * pos_1 = "2";
const char * pos_2 = "A";

void draw1(char * pos_x,char * pos_y) {
  
  Serial.println("Estamos en función draw1");
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
  Serial.println("Fin de función draw1");
}
void draw2(char * texto1,char * texto2) {
  Serial.print("Comienza función: ");
  Serial.println(__func__);
  u8g2.clearBuffer();					// clear the internal memory
  //u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  //u8g2.setFont(u8g2_font_inr42_mr);	// choose a suitable font
  u8g2.setFont(u8g2_font_callite24_tr);
  u8g2.drawStr(5,20,texto1);	// write something to the internal memory
  //u8g2.drawStr(5,30,"1_1");	// write something to the internal memory
  u8g2.drawStr(5,40,texto2);	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
  delay(100);
  Serial.print("Texto1 es: ");
  Serial.println(texto1);
  Serial.print("Texto2 es: ");
  Serial.println(texto2);
  Serial.print("Fin de la función: ");
  Serial.println(__func__);
}
void parpadea(int led_x) {
    // blink LED
  Serial.print("Comienza función: ");
  Serial.println(__func__);
  Serial.print("Recibido parámetro:");
  Serial.println(led_x);
  int blink = 0;
  do
  {
    digitalWrite(led_x, HIGH);
    delay(30);
    digitalWrite(led_x, LOW);
    delay(30);
  } while (blink++ < 5);
  Serial.print("Fin de la función: ");
  Serial.println(__func__);
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
  Serial.print("Comienza función: ");
  Serial.println(__func__);
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
  Serial.print("Fin de la función: ");
  Serial.println(__func__);

}
void button_1_1_pressed() {
  Serial.print("Comienza función: ");
  Serial.println(__func__);
  Serial.println("Pulsado boton 1 cambio Stomps");
  parpadea(led_1_1);
  draw2("Stomp","1");
  Serial.print("Fin de la función: ");
  Serial.println(__func__);
  
  //draw1("44", "z");
}
void button_1_2_pressed() { 
  Serial.print("Comienza función: ");
  Serial.println(__func__);
  Serial.println("Pulsado boton 2 cambio Stomps");
  parpadea(led_1_2);
  draw2("Stomp","2");
  Serial.print("Fin de la función: ");
  Serial.println(__func__);
  //draw1("44", "z");
}
void button_1_3_pressed() { 
  Serial.print("Comienza función: ");
  Serial.println(__func__);
  Serial.println("Pulsado boton 3 cambio Stomps");
  parpadea(led_1_3);
  draw2("Stomp","3");
  Serial.print("Fin de la función: ");
  Serial.println(__func__);
}
void button_1_4_pressed() { 
  Serial.print("Comienza función: ");
  Serial.println(__func__);
  Serial.println("Pulsado boton 4 cambio Stomps");
  parpadea(led_1_4);
  draw2("Stomp","4");
  Serial.print("Fin de la función: ");
  Serial.println(__func__);
}
void button_1_5_pressed() { 
  Serial.print("Comienza función: ");
  Serial.println(__func__);
  Serial.println("Pulsado boton incrementa performance");
  parpadea(led_1_5);
  draw2("Perform","+");
  Serial.print("Fin de la función: ");
  Serial.println(__func__);
}
void button_2_1_pressed() { 
  Serial.print("Comienza función: ");
  Serial.println(__func__);
  Serial.println("Pulsado boton 1 cambio Effects");
  parpadea(led_2_1);
  draw2("Efects","1");
  Serial.print("Fin de la función: ");
  Serial.println(__func__);
}
void button_2_2_pressed() { 
  Serial.print("Comienza función: ");
  Serial.println(__func__);
  Serial.println("Pulsado boton 2 cambio Effects");
  parpadea(led_2_2);
  draw2("Efects","2");
  Serial.print("Fin de la función: ");
  Serial.println(__func__);
}
void button_2_3_pressed() { 
  Serial.print("Comienza función: ");
  Serial.println(__func__);
  Serial.println("Pulsado boton 3 cambio Effects");
  parpadea(led_2_3);
  draw2("Efects","3");
  Serial.print("Fin de la función: ");
  Serial.println(__func__);
}
void button_2_4_pressed() { 
  Serial.print("Comienza función: ");
  Serial.println(__func__);
  Serial.println("Pulsado boton 4 cambio Effects");
  parpadea(led_2_4);
  draw2("Efects","4");
  Serial.print("Fin de la función: ");
  Serial.println(__func__);
}
void button_2_5_pressed() { 
  Serial.print("Comienza función: ");
  Serial.println(__func__);
  Serial.println("Pulsado boton decrementa performance");
  parpadea(led_2_5);
  draw2("Perform","-");
  Serial.print("Fin de la función: ");
  Serial.println(__func__);
}
void button_3_1_pressed() { 
  Serial.print("Comienza función: ");
  Serial.println(__func__);
  Serial.println("Pulsado boton 1 cambio Performance");
  parpadea(led_3_1);
  draw2("Perform","1");
  Serial.print("Fin de la función: ");
  Serial.println(__func__);
}
void button_3_2_pressed() { 
  Serial.print("Comienza función: ");
  Serial.println(__func__);
  Serial.println("Pulsado boton 2 cambio Performance");
  parpadea(led_3_2);
  draw2("Perform","2");
  Serial.print("Fin de la función: ");
  Serial.println(__func__);
}
void button_3_3_pressed() { 
  Serial.print("Comienza función: ");
  Serial.println(__func__);
  Serial.println("Pulsado boton 3 cambio Performance");
  parpadea(led_3_3);
  draw2("Perform","3");
  Serial.print("Fin de la función: ");
  Serial.println(__func__);
}
void button_3_4_pressed() { 
  Serial.print("Comienza función: ");
  Serial.println(__func__);
  Serial.println("Pulsado boton 4 cambio Performance");
  parpadea(led_3_4);
  draw2("Perform","4");
  Serial.print("Fin de la función: ");
  Serial.println(__func__);
}
void button_3_5_pressed() { 
  Serial.print("Comienza función: ");
  Serial.println(__func__);
  Serial.println("Pulsado boton 5 cambio Performance");
  parpadea(led_3_5);
  draw2("Perform","5");
  Serial.print("Fin de la función: ");
  Serial.println(__func__);
}


void setup() {  
    Serial.begin(115200);
    u8g2.begin();
    /* Inicializamos como output los pines a los que están conectados los leds*/
    pinMode(23, OUTPUT);
    pinMode(25, OUTPUT);
    pinMode(27, OUTPUT);
    pinMode(29, OUTPUT);
    pinMode(31, OUTPUT);
    pinMode(33, OUTPUT);
    pinMode(35, OUTPUT);
    pinMode(37, OUTPUT);
    pinMode(39, OUTPUT);
    pinMode(41, OUTPUT);
    pinMode(43, OUTPUT);
    pinMode(45, OUTPUT);
    pinMode(47, OUTPUT);
    pinMode(49, OUTPUT);
    pinMode(51, OUTPUT);
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
  /* Method 2: Use the waitForButton() function, which blocks and
   * doesn't return until a button press and release are
   * detected. This function takes care of button debouncing. */
  //Serial.println("Estoy en 0035");
  //draw1();
  //button.waitForButton();
  //Serial.println("Estoy en 0040");
}