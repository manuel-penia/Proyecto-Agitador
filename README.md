# Agitador Magnético

En este proyecto se documenta la realización de un agitador magnético sencillo de bajo costo y con **componentes reutilizados** de computadoras viejas. Incluimos los componentes y circuitos asi como del software usado para controlar, mediante una placa Arduino, la velocidad de giro de un ventilador y la actuación sobre una pantalla de 7 segmentos que muestra un temporizador.
___

# Contenidos
1. [Motivación](#Motivación)
   1. [¿Agitadores magnéticos?](##¿Agitadoresmagnéticos?)
   
2. [Nuestro Agitador](#NuestroAgitador)
   1. [Uso](#uso) 
   2. [Lista de Componentes](#lista-de-componentes)
   3. [Circuito](#circuito)
   4. [Software](#software)
   5. [Impresión 3D](#Impresión3D)
3. [Inspiración](#Inpiración)

___
 
# Motivación
<p align="justify"> Realizamos este proyecto con el fin de crear una sistema de fácil implementación para construir un agitador magnético que actualmente tienen precios altos y que sea funcional para el trabajo en el laboratorio.
 </p>

## ¿Agitadores magnéticos?
<p align="justify"> Los agitadores magnéticos se utilizan para la mezclar de soluciones químicas. Los agitadores comerciales consisten de una pequeña barra magnética recubierta por una capa de plástico y una placa debajo donde se encuentra un imán rotatorio a fin de crear un campo magnético que gire. Es muy frecuente que tenga un montaje de resistencias eléctricas a fin de generar calor necesario para calentar algunas soluciones químicas.</p>
___

# Nuestro Agitador
<p align="justify"> Para el diseño de nuestro agitador tuvimos en cuenta que debía tener la funcionalidad principal de hacer girar el buzo (para realizar el mezclado) y a su vez que tuviera un temporizador, con el cual pasado el tiempo seleccionado se apague el agitador. </p>

## Uso
<p align="justify"> Presionando el botón amarillo se elige la cantidad de tiempo deseada en el temporizador, con el botón rojo se da inicio al descuento de dicho tiempo. Se puede frenar el giro del ventilador presionando nuevamente el botón rojo. Una vez que arrancó el temporizador, mediante el giro del potenciómetro se controla la velocidad de giro del ventilador y por ende del buzo en la solución. Recomendamos aumentar gradualmente la velocidad de giro hasta la velocidad deseada. 
 </p>

## Lista de Componentes 
1. [Placa Arduino UNO](https://proyectoarduino.com/arduino-uno-r3/)
2. Entradas: 
   1. [Potenciómetro](https://programarfacil.com/blog/arduino-blog/el-potenciometro-y-arduino/) 
   2. [Botones](https://openwebinars.net/blog/tutorial-arduino-entradas-2-botones/) .
3. Salidas:
   1. Ventilador con PWM [AMD AFB 3300 rpm](https://ar.mouser.com/datasheet/2/632/AFB70x70x15mm-515820.pdf) 
   2. [Display LCD](https://www.circuitbasics.com/arduino-7-segment-display-tutorial/).

4. Alimentación: 
   1. Fuente de aliemntacion 12 V [Megalite SF120050](https://megalite.com.ar/data/Catalogo_Nielsen.pdf).

5. Otros accesorios: 
   1. Cables Dupont Macho Hembra y Macho Macho de 20cm x **30**. 

## Circuito
<p align="justify"> En cuanto al circuito, la fuente de alimentación se conecta a la placa Arduino mediante la entrada de 12V. El pin Vin redirecciona el voltaje de alimentación al ventilador. A traves del relay se conecta el cable Vin que conecta el ventilador. El controlador PWM del ventilador sale del pin 3 que tiene dicha funcionalidad. Por otro lado, la salida analógica del potenciómetro se conecta al Arduino por la entrada A2 y la alimentación es de 5V que proporciona el Arduino. El modulo Relay tiene su sistema de de alimentación de 5V con los pines de la placa y el cable sensor por la salida digital 8. Ademas cuenta con 2 botones en una configuración pull-down. Para esto se conecta una resistencia de 10 ohms en la salida GND de los botones. Todos estos componentes se conectan a los pines GND del Arduino. Finalmente el display LCD 16 x 2  .....  </p>

<img src="CircuitoNuevo.jpg" alt="drawing" width="500" class="center">

## Software

El código utilizado se encuentra en el archivo [Codigo-Arduino.ino](https://github.com/manuel-penia/Proyecto-Agitador/blob/main/C%C3%B3digo-Arduino.ino)
Para simplificar la lectura y funcionamiento del codigo se realizo el siguiente diagrama explicativo. En donde, las variables azules son globales y las negras son locales. 

<img src="diagramaCodigo.jpeg" alt="drawing" width="500" class="right">

## Impresión 3D

Se construyó un soporte en la plataforma online TinkerCad dispuesto en tres partes. También se contruyó el buzo que se introduce en lka solución. Dentro del buzo se encuentran los imanes de neodimio. Todos los archivos stl se encuentran en esta [carpeta.](https://github.com/manuel-penia/Proyecto-Agitador/tree/main/IMPRESI%C3%93N)


<img src="desglose_impresion.png" alt="drawing" width="500" class="right">


# Inspiración

Hay proyectos de agitadores de los cuales nos inspiramos para realizar el proyecto, algunos no utilizan una placa Arduino y ninguno posee un temporizador. 

+https://www.thingiverse.com/thing:1175415

+https://www.youtube.com/watch?v=muBcyEvqCYk&ab_channel=CambatronicsOnline

+https://forum.arduino.cc/t/controlar-ventilador-con-arduino/427074

+https://fdossena.com/?p=ArduinoFanControl/i.md

+https://www.youtube.com/watch?v=YBNEXWp-gf0
