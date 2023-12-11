#include <LiquidCrystal_I2C.h>
#include <Wire.h> 

const int pinPot=A2;
const int pinControlRelay=8;
const int pinBotonTiempo=4;
const int pinBotonIniciar=5;
const int pinPWMVent=3;  //salidaPWM
LiquidCrystal_I2C lcd(0x27,16,2);

const int umbralMinimo=300; // Umbral mínimo para ajustar la salida del PWM y controlar la conexión/desconexión del voltaje de 12V.

int outPwm=0;  // Salida PWM (0-255) que regula el voltaje de entrada al ventilador y, por lo tanto, la velocidad.
int tiempoRestante = 0; // Tiempo restante en el temporizador.
bool temporizadorIniciado = false; // Estado del temporizador.
float duracionTemporizador = 0;  //Es el valor a setear en el temporizador en segundos.
long botonTiempoLastPressed = 0;

void setup() {
  pinMode(pinPot, INPUT);
  pinMode(pinControlRelay, OUTPUT);
  pinMode(pinBotonTiempo, INPUT);
  pinMode(pinBotonIniciar, INPUT);
  pinMode(pinPWMVent, OUTPUT);
  digitalWrite(pinControlRelay, HIGH);  // Inicialmente, mantener el relé apagado para no permitir la conexión del voltaje de 12V.

  // Inicializar el LCD
  lcd.init();
  
  //Encender la luz de fondo.
  lcd.backlight();
  
  Serial.begin(9600);
  Serial.println(outPwm);
}

bool IsPotActivado(int valorPot){
  if (valorPot < umbralMinimo) {  //umbralMínimo es una Constante Global.
    return false;
  } else {
    return true;
  }
}

void ControlarRelay(int valorPot, bool temporizadorIniciado){
  if (IsPotActivado(valorPot) && temporizadorIniciado) {
      digitalWrite(pinControlRelay, HIGH);  // Conectar el voltaje de 12V encendiendo el transistor.
      outPwm = map(valorPot, umbralMinimo, 1023, 0, 255);  // Mapear los valores del potenciómetro al rango del PWM (0 a 255 es el default).
      Serial.println(outPwm);
  } else {
      digitalWrite(pinControlRelay, LOW);  // Desconectar el voltaje de 12V apagando el relé.
  }
}

void ControlarTemporizador(){
  if (tiempoRestante <= 0) {
      temporizadorIniciado = false;  // Detener el temporizador cuando se agota el tiempo.
      tiempoRestante = 0;
    }
}

void aumentarTemporizador() {
  long tiempoActual = millis();
  if (tiempoActual - botonTiempoLastPressed >= 500) {
    botonTiempoLastPressed = tiempoActual;
    if (tiempoRestante == 0) {
      tiempoRestante += 30;
    } else {
      tiempoRestante *= 2;
    }
  }
}


void ActualizarTiempoRestante(){
  static unsigned long timer = millis(); //Guardamos la hora
  if (millis() - timer >= 1000) {
    timer += 1000;
    if (temporizadorIniciado) {
      tiempoRestante -= 1;
      lcd.clear();
    }
  }
}
void segundos_a_hh_mm_ss(int segundos, char* resultado) {
  int horas = segundos / 3600; // 1 hora = 3600 segundos
  int minutos = (segundos % 3600) / 60;
  int segundosRestantes = segundos % 60;

  // Formatear la cadena con el tiempo en formato HH:MM:SS
  sprintf(resultado, "%02d:%02d:%02d", horas, minutos, segundosRestantes);
}

int valorPot;
int valorBotonTiempo;
int valorBotonIniciar;
int numero_display;

void loop() {
  valorPot=analogRead(pinPot);
  valorBotonTiempo=digitalRead(pinBotonTiempo);
  valorBotonIniciar=digitalRead(pinBotonIniciar);

  if (temporizadorIniciado) {
    ControlarTemporizador();
    
    if (valorBotonIniciar == HIGH) {
      temporizadorIniciado = false;
      delay(500);
    }
    
  } else {
    if (valorBotonIniciar == HIGH) {
      temporizadorIniciado = true;
      delay(500);
    }
    if (valorBotonTiempo == HIGH) {
      aumentarTemporizador();
    }
  }
    
  ActualizarTiempoRestante();
  
  ControlarRelay(valorPot, temporizadorIniciado);
  

  lcd.setCursor(0, 0);
  lcd.print("Tiempo: ");
  
  lcd.setCursor(8, 0);
  char tiempo_formateado[9];
  segundos_a_hh_mm_ss(tiempoRestante, tiempo_formateado);
  lcd.print(tiempo_formateado);

  analogWrite(pinPWMVent, outPwm);
}
