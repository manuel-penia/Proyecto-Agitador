# Agitador Magnético

En este proyecto se documenta la realización de un agitador magnético sencillo de bajo costo y con **componentes reutilizados** de computadoras viejas. Incluimos los componentes y circuitos asi como del software usado para controlar, mediante una placa Arduino, la velocidad de giro de un ventilador y la actuación sobre una pantalla de 7 segmentos que muestra un temporizador.

<!--<img src="medidoresIB/doc/20210531_194427.jpg" alt="drawing" width="400" class="center">-->
<img src="medidoresIB/doc/20210602_173510.jpg" alt="drawing" width="500" class="center">

___

# Contenidos
1. Motivación
   1. ¿Agitadores magnéticos?
   
2. Nuestro Agitador
   1. [Funcionalidad](#funcionalidad)
   2. [Uso](#uso) 
   3. [Lista de Componentes](#lista-de-componentes)
   4. [Circuito](#circuito)
   5. [Software](#software)
3. Medidores Parecidos
6. [Contacto](#contacto)

___
 
# Motivación

Realizamos este proyecto para la aprobación de una materia optativa, como así también para crear una sistema de fácil implementación para construir un agitador magnético que actualmente tienen precios caros.

## ¿Agitadores magnéticos?
Los agitadores magnéticos se utilizan para la mezclar de soluciones químicas. Los agitadores comerciales consisten de una pequeña barra magnética recubierta por una capa de plástico y una placa debajo donde se encuentra un imán rotatorio a fin de crear un campo magnético rotatorio. Es muy frecuente que tenga un montaje de resistencias eléctricas a fin de generar calor necesario para calentar algunas soluciones químicas.

___

# Nuestro Agitador
 
## Funcionalidad 

<img src="medidoresIB/doc/pantallaCO2.gif" alt="drawing" width="400" class="center">

## Uso
Girando el *potenciómetro* se controla la velocidad de giro del ventilador.

## Lista de Componentes 
1. [Placa Arduino MEGA]((https://proyectoarduino.com/arduino-mega-2560/)) .
2. Entradas: 
   1. [Potenciómetro](https://programarfacil.com/blog/arduino-blog/el-potenciometro-y-arduino/) 
   2. [Joystick](https://www.luisllamas.es/arduino-joystick/) .
3. Salidas:
   1. Ventilador con PWM [AMD AFB 3300 rpm](https://ar.mouser.com/datasheet/2/632/AFB70x70x15mm-515820.pdf) 
   2. [Pantalla 7 Segmentos](https://www.circuitbasics.com/arduino-7-segment-display-tutorial/).

6. Alimentación: 
   1. Fuente de aliemntacion 12 V [Megalite SF120050](https://megalite.com.ar/data/Catalogo_Nielsen.pdf).

9. Otros accesorios: 
   2. Cables Dupont Macho Hembra y Macho Macho de 20cm x **30**. 

## Circuito
![final](medidoresIB/doc/esquema_bb.png)
Como se puede ver, se usa un resistor "pull down" con el pulsador de recalibración y el pin 12 para registrar el evento, los pines A4/A5 van respectivamente al SDA/SCL de ambos, el LCD I2C y el SCD30, la chicharra o buzzer pasivo es controlada con el pin digital 8, y la batería se conecta al USB del Arduino. Notar que el SCD30 está alimentado con la salida de 3.3V. Los "Peines" o tira de pines se soldaron a los conectores (VCC,SDA,SCL,GND) del sensor SCD30, para poder luego conectarlo a la miniboard. 


## Software

+ Todos los códigos están en [esta carpeta](https://github.com/droyktton/medidorCO2/tree/main/medidoresIB/src).

+ [El código fuente que controla la placa Arduino](./medidoresIB/src/medidoresIB.ino) fue escrito usando el [open-source Arduino Software (IDE)](https://www.arduino.cc/en/software) en Ubuntu 20.04 linux. Para interactuar con el sensor NDIR usamos la biblioteca [SparkFun_SCD30_Arduino_Library](https://github.com/sparkfun/SparkFun_SCD30_Arduino_Library). Para interactuar con la pantalla LCD I2C usamos la biblioteca [liquid-crystal-i2-c](https://www.arduinolibraries.info/libraries/liquid-crystal-i2-c). 

![final](medidoresIB/doc/gaugeserial.gif)


# Medidores Parecidos

Hay proyectos de medidores que usan por ejemplo sensores electroquímicos de CO2 o similares. Son más económicos, pero son menos específicos al CO2 y en general más difíciles de calibrar que los NDIR. Por ello no son recomendados para el fin planteado. 

Esta es un pequeña selección de proyectos de medidores que **si** usan sensores NDIR de distintos tipos, algunos con distintas e interesantes funcionalidades adicionales. 

+ https://github.com/jlaliaga/Medidor-de-CO2
+ https://www.instructables.com/CO2-Sensor-for-Schools/ 
+ https://emariete.com/medidor-casero-co2/
+ https://github.com/danielbernalb/LibreCO2/blob/main/INSTRUCCIONES%20en%20Espa%C3%B1ol.md
+ https://github.com/Sensirion/arduino-ble-gadget/blob/master/documents/SCD30_Monitor_Tutorial.md
+ https://github.com/anaireorg/anaire-devices
+ https://fablab.ruc.dk/co2/
+ https://github.com/Alitux/solarco2
+ [Medidores Comerciales en Argentina](https://www.argentina.gob.ar/ciencia/unidad-coronavirus/ventilar/produccion-local-medidores).
  
# Contacto 
[Alejandro B. Kolton](https://sites.google.com/site/abkoltontalks), @droyktton en twitter o gmail. 
Sugerencias, correcciones y preguntas son muy bien bienvenidas.
