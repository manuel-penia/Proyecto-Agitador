#include "SevSeg.h"
SevSeg sevseg; // Instanciamos el controlador de LCD de 7 segmentos.

const int pinPot=A2;
const int pinControlRelay=22;
const int pinJoystickX=A0;
const int pinBotonJoystick=30;
const int pinPWMVent=46;  //salidaPWM

const int umbralMinimo=100; // Umbral mínimo para ajustar la salida del PWM y controlar la conexión/desconexión del voltaje de 12V.

int outPwm=0;  // Salida PWM (0-255) que regula el voltaje de entrada al ventilador y, por lo tanto, la velocidad.
int tiempoRestante =-1; // Tiempo restante en el temporizador.
bool temporizadorIniciado = false; // Estado del temporizador.
float duracionTemporizador = 0;  //Es el valor a setear en el temporizador en segundos.

void setup() {
  pinMode(pinPot, INPUT);
  pinMode(pinControlRelay, OUTPUT);
  pinMode(pinJoystickX, INPUT);
  pinMode(pinBotonJoystick, INPUT_PULLUP);
  pinMode(pinPWMVent, OUTPUT);
  digitalWrite(pinControlRelay, LOW);  // Inicialmente, mantener el relé apagado para no permitir la conexión del voltaje de 12V.

byte numDigits = 4;
byte digitPins[] = {2, 3, 4, 5};
byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
bool resistorsOnSegments = false;
byte hardwareConfig = COMMON_CATHODE;
bool updateWithDelays = false;
bool leadingZeros = false;
bool disableDecPoint = false;

sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
sevseg.setBrightness(10);

  Serial.begin(9600);


}




bool IsPotActivado(int valorPot){
  if (valorPot < umbralMinimo) {  //umbralMínimo es una Constante Global.
    return false;
  } else {
    return true;
  }
}

void ControlarRelay(bool IsPotActivado, int valorPot){
  if (!IsPotActivado) {
    outPwm = 0;  // Establecer la salida del PWM en cero cuando ValorPot está por debajo del umbral.
    digitalWrite(pinControlRelay, LOW);  // Desconectar el voltaje de 12V apagando el relé.
    //Serial.println("rele desactivado");


  } else {
      if(tiempoRestante!=0){
        outPwm = map(valorPot, umbralMinimo, 1023, 0, 255);  // Mapear los valores del potenciómetro al rango del PWM (0 a 255 es el default).
        digitalWrite(pinControlRelay, HIGH);  // Conectar el voltaje de 12V encendiendo el transistor.
        //Serial.println("rele activado");
      }
    }
  if (temporizadorIniciado && (tiempoRestante <= 0)) {
      temporizadorIniciado = false;  // Detener el temporizador cuando se agota el tiempo.
      duracionTemporizador=0;        // Volver el acumulador a 0.
      tiempoRestante = 0;            //
      digitalWrite(pinControlRelay, LOW);  // Desconectar el voltaje de 12V apagando el relé.
      //Serial.println("rele desactivado");
    }
}

void ControlarTemporizador(int valorJoystickX){
  if (valorJoystickX > 600) {
      duracionTemporizador +=0.1;  // Aumentar la duración del temporizador en 30 seg si el joystick se mueve a la derecha.
  } else if (valorJoystickX < 400) {
      duracionTemporizador -= 0.1;  // Disminuir la duración del temporizador en 30 seg si el joystick se mueve a la izquierda.
      if (duracionTemporizador < 0) {
        duracionTemporizador = 0;  // Asegurarse de que la duración del temporizador no sea negativa.
    }
  }
}

void IniciarTemporizador(int valorBotonJoystick){ // Iniciar o detener el temporizador con el botón del joystick
  if (valorBotonJoystick == LOW && !temporizadorIniciado) {
    temporizadorIniciado = true;
    //Serial.println("Temporizador iniciado");
    tiempoRestante = duracionTemporizador;
  } else if (valorBotonJoystick == LOW && temporizadorIniciado) {
      temporizadorIniciado = false;   //Esto es para detener.
      //Serial.println("Temporizador apagado");
  }
}

void ActualizarTiempoRestante(){
  static unsigned long timer = millis(); //Guardamos la hora
  if (temporizadorIniciado) {   //Sólo cuando el Temporizador esté andando.
    if (millis() - timer >= 1000) { //Si superamos los 1000 ms(1s)
      timer += 1000;
      tiempoRestante -= 1;    //Restamos 1 seg del tiempoRestante.
      //Serial.println("se desconto un seg.");
    }
  }
}


int ControlarVisor() {
  int segundos;
  if (temporizadorIniciado) {
    segundos = tiempoRestante;
  } else {
    segundos = duracionTemporizador;
  }
  int minutos = floor(segundos / 60); // Obtener la cantidad de minutos completos
  int segundosRestantes = segundos % 60; // Obtener los segundos restantes

  String numero_display_string;
  int numero_display;

  if (segundos == -1) {
    segundosRestantes = 0;
  }

  if (segundosRestantes < 10) {
    numero_display_string = String(minutos) + "0" + String(segundosRestantes);
  } else {
    numero_display_string = String(minutos) + String(segundosRestantes);
  }

  numero_display = numero_display_string.toInt();

  //Serial.print("el numero display es:");
  //Serial.println(numero_display);
  return numero_display;
}

void loop() {
  int valorPot;
  int valorJoystickX;
  int valorBotonJoystick;
  int numero_display;


  valorPot=analogRead(pinPot);
  valorJoystickX=analogRead(pinJoystickX);
  valorBotonJoystick=digitalRead(pinBotonJoystick);

  IsPotActivado(valorPot);
  ControlarRelay(IsPotActivado(valorPot),valorPot);
  ControlarTemporizador(valorJoystickX);

  //Serial.print("El tiempo del temp es:");
  //Serial.println(duracionTemporizador);

  IniciarTemporizador(valorBotonJoystick);
  numero_display=ControlarVisor();
  ActualizarTiempoRestante();

  //Serial.print("El tiempo Restante es:");
  //Serial.println(tiempoRestante);
 
  sevseg.setNumber(numero_display, 2);
  sevseg.refreshDisplay();
  analogWrite(pinPWMVent, outPwm);
}
