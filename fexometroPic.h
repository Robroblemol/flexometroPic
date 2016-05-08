#include <18F2550.h>
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN,CCP2B3

#use delay(clock=48000000)
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)
#build (reset=0x1000,interrupt=0x1008)//reserva para la bootloader
#org 0x0000,0x0FFF{}

#define led pin_C0//definimos pin_c0 como led
#define boton pin_C2//definimos pin_C2 como boton
#define trig pin_a5//pin de disparo
#define eco pin_b0//no esta en uso
