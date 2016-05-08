#include "F:\Chichielectronica\Proyectos\flexometroPic\fexometroPic.h"
short int
          flagHayDatos,
          flagtrig;
//short int flag_endecho;
short int flagToggleFlanco;
int8 Dh,Dl;
float time,
      D,
      V_error;
char cad = ' ';

#int_ccp2
void handle_ccp2_int(){
  output_toggle(led);
  if(flagToggleFlanco==0){      // He recibido Flanco de Subida
    set_timer1(0);              // Reinicio TMR1
    setup_ccp2(CCP_CAPTURE_FE); // Configuro para capturar siguiente flanco de Bajada
    flagToggleFlanco=1;         // Indico que el siguiente flanco será de Bajada
  } else {                      // He recibido Flanco de Bajada
    time=get_timer1();            // Guardo en time el valor de TMR1 al Flanco de Bajada
    setup_ccp2(CCP_CAPTURE_RE); // Configuro para capturar siguiente flanco de subida
    flagToggleFlanco=0;         // Indico que el siguiente flanco será de Subida
    if(flagHayDatos==0){        // Si los datos anteriores han sido procesados ...
      flagHayDatos=1;           // Indico que ya hay nuevos datos de flancos para calcular
    }
  }
}


void main()
{
   delay_ms(300);
   //flagToggleFlanco = 0;
   setup_ccp2(CCP_CAPTURE_RE);
   flagToggleFlanco = 0;
   setup_TIMER_1 (T1_INTERNAL|T1_DIV_BY_8);//configuracion timer 1
   enable_interrupts(int_ccp2);
   enable_interrupts(global);
    while (true) {
      if(input(boton)==0){
        delay_ms(500);
        printf("prueba comunicacion\r\n");
      }
      if(kbhit()){// si recivimos datos
         cad = getc();// se guardan en cad
         delay_ms(50);//espremos 50ms
         putc(cad);//devolvemos lo recivido
      }
      if(flagHayDatos==0&&flagtrig==0){
        output_bit(trig,1);
        delay_us(9);
        output_bit(trig,0);
        flagtrig=1;
        //printf("flagHayDatos = 0 flagtrig = 1\r\n");
     }
     if(flagHayDatos==1){
      //printf("finalizo captura de eco\r\n");
         D=time/58.82;
         v_error=d*0.33;
         D=D-v_error;
         if(d<=400&&d>=2){
           //formato para enviar variables tipo float %f tipo String %S
           //para protocoder enviar siempre \r\n
           printf("%f%S",d,"\r");
         }
         flagHayDatos=0;
         time=0;
         flagtrig=0;
      }
        delay_ms(250);
    }
}
