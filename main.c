#include <msp430.h> 

/* PINES DESIGNADOS DEL MSP430G2553
 *  1:  VCC     :
 *  2:  P1.0    : Botón Josytick Izquierdo
 *  3:  P1.1    :
 *  4:  P1.2    :
 *  5:  P1.3    : Y Josytick Izquierdo
 *  6:  P1.4    : X Josytick Izquierdo
 *  7:  P1.5    : Botón Josytick Derecho
 *  8:  P2.0    :
 *  9:  P2.1    :
 * 10:  P2.2    :
 * 11:  P2.3    :
 * 12:  P2.4    :
 * 13:  P2.5    :
 * 14:  P1.6    : Y Josytick Derecho
 * 15:  P1.7    : X Josytick Derecho
 * 16:  RST     :
 * 17:  TEST    :
 * 18:  P2.7    :
 * 19:  P2.6    :
 * 20:  GND     :
 */

unsigned int valores[5] = {0};  // Donde se almacenaran los valores de cada eje de cada Joystick

void main(void){
    // Detiene el timer watchdog
    WDTCTL  = WDTPW | WDTHOLD;

    // Calibra CPU a 16MHz
    DCOCTL  = CALDCO_16MHZ;
    BCSCTL1 = CALBC1_16MHZ;

    // Configura Puerto
    P1REN   = BIT0|BIT5;            // Resistencia de pull en P1.0 y P1.5
    P1OUT   = BIT0|BIT5;            // Pull Up para P1.0 y P1.5
    P1IES   = 0;                    // Fanco de bajada
    P1IFG   = 0;                    // Borra posibles banderas por instrucciones previas
    P1IE    = BIT0|BIT5;            // Habilita interrupciones en P1.0 y P1.5

    // Configura ADC
    ADC10CTL1     = INCH_7|         // Desde A7
                    ADC10SSEL_3|    // SMCLK
                    CONSEQ_1;       // Secuencia de canales
    ADC10CTL0     = ADC10SHT_2|     // 16 ciclos par retener
                    MSC|ADC10ON|    // Multiples conversiones; Habilitado
                    ENC;            // Encendido
    ADC10AE0      = BIT3|BIT4|      // A4, A3
                    BIT6|BIT7;      // A7, A6
    ADC10DTC1     = 5;              // 5 transferencias

    __enable_interrupt();

    while(1){
        ADC10SA   = (unsigned int)&valores;     // Ruta de almacenamiento
        ADC10CTL0   |= ADC10SC;                 // Inicia la conversion de canales de ADC10
        while((ADC10CTL1&BUSY) != 0);           // Espera a que termine

        /*

        A partir de aquí ya tenemos capturado los valores de
        cada eje de cada jostick, donde:

        valores[0] = canal 7 o X de joystick derecho
        valores[1] = canal 6 o Y de joystick derecho
        valores[2] = no tiene nada util
        valores[3] = canal 4 o X de joystick izquierdo
        valores[4] = canal 3 o Y de joystick izquierdo

        */
    }
}

#pragma vector = PORT1_VECTOR
__interrupt void intPuerto1(void){
    switch(P1IFG&(BIT0|BIT5)){
    case BIT0:
        // Instrucciones para el botón del Joystick izquierdo
        break;
    case BIT5:
        // Instrucciones para el botón del Joystick derecho
        break;
    }
}




