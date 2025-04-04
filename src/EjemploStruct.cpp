struct PEDAL
   {   byte CCMidi     ;      // CC midi
       byte CCValor    ;      // Valor del CC midi
       byte CCCanal    ;   // Canal midi
       char Texto1     ;      // Texto en linea1 de la pantalla
       char Texto2     ;      // Texto en linea2 de la pantalla
       bool Persis_Led ;  // Indica si el led debe quedarse encendido o no
   } ;

void setup()
   { Serial.begin( 115200);

    // Declaración del modo 1
    PEDAL P1_1 ;
     P1_1.CCMidi     = 60 ;
     P1_1.CCValor    = 0 ;
     P1_1.CCCanal    = 1 ;
     P1_1.Texto1     = "Tuner" ;
     P1_1.Texto2     = " On" ;
     P1_1.Persis_Led = True ;
    // Declaración del modo 2
    // Cuando hay que enviar un valor para activarlo y otro para desactivarlo.
    PEDAL P1_1_ON  = {60,0,1,"Tuner","On",True} ;       // Activación
    PEDAL P1_1_OFF = {60,127,1,"Tuner","Off",False} ;   // Desactivación
    // Cuando NO hay que enviar un valor para activarlo y otro para desactivarlo.
    PEDAL P1_2_ON  = {60,0,1,"Tuner","On",True} ;       // Activación
    PEDAL P1_2_OFF = P1_2_ON ;   // Desactivación   
   }

void loop()
   {  
     Serial.println(P1_1.CCMidi) ;
   }
void button_1_1_pressed() {
  funcionMidi(P1_1_ON.CCMidi,P1_1_ON.CCValor,P1_1_ON.CCCanal);
  draw2(P1_1_ON.Texto1,P1_1_ON.Texto1);
