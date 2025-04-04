struct PEDAL
   {   byte CCMidi ;      // CC midi
       byte CCValor;      // Valor del CC midi
       byte CCChannel ;   // Canal midi
       char Texto1 ;      // Texto en linea1 de la pantalla
       char Texto2 ;      // Texto en linea2 de la pantalla
       bool Persis_Led ;  // Indica si el led debe quedarse encendido o no
   } ;

void setup()
   { Serial.begin( 115200);
    PEDAL P1_1 ;
     PEDAL.CCMidi     = 60 ;
     PEDAL.CCValor    = 0 ;
     PEDAL.CCCHanel   = 1 ;
     PEDAL.Texto1     = "Tuner" ;
     PEDAL.Texto2     = " On" ;
     PEDAL.Persis_Led = True ;
   }

void loop()
   {  
     Serial.println(P1_1.CCMidi) ;
     
   }
