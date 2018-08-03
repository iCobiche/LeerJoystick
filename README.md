# LeerJoystick

Código en C, creado en CodeComposer para leer 2 Joysticks de 2 ejes con el micrcontrolador **MSP430G2553**. Pero antes:

Como sabemos, los Joystick de dos ejes en realidad son dos potenciómetros construidos de forma circular, y para poder leerlos basta con poder leer un potenciómetro pero hacerlo más veces. Específicamente el **G2553** necesita de un control de transferencia de datos (DTC) cuando tiene que leer más de un canal, esto es así porque sólo cuenta con una unidad de memoria disponible para almacenar el valor de un solo canal, y el DTC se encarga de guardar en un arreglo de datos todos los datos de todos los canales que nosotros configuremos.

## Diagrama de conexiones del proyecto

<img src="https://raw.githubusercontent.com/iCobiche/LeerJoystick/master/LeerJoystick.png"/>

**Figura 1** : Diagrama de conexiones.

Las conexiones de la figura 1 se colocan así por un motivo: los joystick suelen ser implementados como mandos a distancia de algún dispositivo, por lo que se estan dejando libre las terminales en el MSP430G2553 que cuentan con protocolo de comunicación UART; uno de los protocolos más usados en dispositivos de transmisión por RF.

Además, muchos (sino es que todos) los joystick que existen en el mercado cuentan con un botón centrar que puede ser accionado. Para los botones se ha creado una rutina básica de interupciones que se ejecutan cuando los botones se presionan.