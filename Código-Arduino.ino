const int pinPot = A2;      // Pin donde se conecta el potenciómetro.
const int pinPWMVent = 3;   // Pin de salida PWM para controlar el ventilador.
const int pinControlRele = 2;  // Pin del relé para conectar/desconectar el voltaje de 12V del ventilador.


int OutPWM;                 // Salida PWM (0-255) que regula el voltaje de entrada al ventilador y, por lo tanto, la velocidad.
int ValorPot;               // Valor leído por el potenciómetro (0-1023).
int umbralMinimo = 100;     // Umbral mínimo para ajustar la salida del PWM y controlar la conexión/desconexión del voltaje de 12V.


void setup() {
  pinMode(pinPot, INPUT);
  pinMode(pinPWMVent, OUTPUT);
  pinMode(pinControlRele, OUTPUT);
  digitalWrite(pinControlRele, LOW);  // Inicialmente, mantener el relé apagado para no permitir la conexión del voltaje de 12V.
  Serial.begin(9600);
}


void loop() {
  ValorPot = analogRead(pinPot);


  if (ValorPot < umbralMinimo) {
    OutPWM = 0;  // Establecer la salida del PWM en cero cuando ValorPot está por debajo del umbral.
    digitalWrite(pinControlRele, LOW);  // Desconectar el voltaje de 12V apagando el relé.
    Serial.println("Relay no accionado");


  } else {
    OutPWM = map(ValorPot, umbralMinimo, 1023, 0, 255);  // Mapear los valores del potenciómetro al rango del PWM.
    digitalWrite(pinControlRele, HIGH);  // Conectar el voltaje de 12V encendiendo el transistor.
    Serial.println("Relay accionado");


  }
 
  // Imprimir los valores en el monitor serial
  Serial.print("Lectura Potenciometro: ");
  Serial.print(ValorPot);
  Serial.print(" - Salida por pin PWM: ");
  Serial.println(OutPWM);
 
  analogWrite(pinPWMVent, OutPWM);      // Establecer el valor PWM de salida para controlar la velocidad del ventilador.
  delay(100);
}
