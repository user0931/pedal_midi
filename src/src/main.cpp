#include <Arduino.h>
#include <Pushbutton.h>

#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


U8G2_SSD1309_128X64_NONAME0_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8); 

#define BUTTON_PIN 24
Pushbutton button(BUTTON_PIN);

int led1 = 22;  
int led2 = 23;
String pos_1 = "11";
String pos_2 = "22";

void draw1() {
  
  Serial.println("Estamos en función draw1");
  u8g2.clearBuffer();					// clear the internal memory
  //u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  //u8g2.setFont(u8g2_font_ncenB24_tr);
  u8g2.setFont(u8g2_font_inr42_mf);
  u8g2.setCursor(15,10);
  u8g2.print(pos_1);
  //u8g2.drawStr(5,50,"A1");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
  delay(1000);  
  Serial.println("Fin de función draw1");
}

void draw2() {
  
  Serial.println("Estamos en función draw2");
  u8g2.clearBuffer();					// clear the internal memory
  //u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.setFont(u8g2_font_inr42_mr);	// choose a suitable font
  u8g2.drawStr(5,50,"B2");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
  delay(1000);  
  Serial.println("Fin de función draw2");
}


void setup()  
{  
    Serial.begin(115200);
    pinMode(22, OUTPUT);  
    pinMode(23, OUTPUT);
    u8g2.begin();
}  
void loop()   
{  
  
  // rebuild the picture after some delay
    delay(100);
    digitalWrite(led1, HIGH); // turn the LED on (HIGH is the voltage level)  
    delay(200); // wait for a second  
    digitalWrite(led1, LOW); // turn the LED off by making the voltage LOW  
    delay(10); // wait for a second  
    digitalWrite(led2, HIGH); // turn the LED on (HIGH is the voltage level)  
    delay(200); // wait for a second  
    digitalWrite(led2, LOW); // turn the LED off by making the voltage LOW  
    delay(10); // wait for a second  

  /* Method 2: Use the waitForButton() function, which blocks and
   * doesn't return until a button press and release are
   * detected. This function takes care of button debouncing. */
  Serial.println("Estoy en 0035");
  draw1();
  button.waitForButton();
  Serial.println("Estoy en 0040");

  // blink LED
  digitalWrite(led1, HIGH);
  delay(100);
  digitalWrite(led1, LOW);
  delay(100);
  digitalWrite(led2, HIGH);
  delay(100);
  digitalWrite(led2, LOW);
  delay(100);
  digitalWrite(led1, HIGH);
  delay(100);
  digitalWrite(led1, LOW);
  delay(100);
  digitalWrite(led2, HIGH);
  delay(100);
  digitalWrite(led2, LOW);
  delay(100);
  draw2();

}

