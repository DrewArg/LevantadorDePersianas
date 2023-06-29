#include <Stepper.h>;

const int stepsPerRevolution = 300;  // PASOS POR REVOLUCIONES DEL MOTOR

Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);


Luego, se definen varias variables y pines relacionados con luces LED y botones:


int LedAmarillo = 4;
int ApretarAmarillo = 5;  // ACCION DEL LED VERDE
int botonAmarillo;

int LedVerde = 3;
int ApretarVerde = 6;  // ACCION DEL LED ROJO
int botonVerde;

int LedRojo = 2;
int ApretarRojo = 7;  // ACCION DEL LED AMARILLO
int botonRojo;

bool flagStop = false;
bool flagRed = false;
bool flagGreen = false;

int estadoFinalArriba = 1;
int estadoFinalAbajo = 1;
int finalCarreraArriba = 13;
int finalCarreraAbajo = 12;


void setup() {

  myStepper.setSpeed(50);

  pinMode(ApretarAmarillo, INPUT);
  pinMode(LedAmarillo, OUTPUT);

  pinMode(ApretarVerde, INPUT);
  pinMode(LedVerde, OUTPUT);

  pinMode(ApretarRojo, INPUT);
  pinMode(LedRojo, OUTPUT);

  pinMode(finalCarreraArriba, INPUT);
  pinMode(finalCarreraAbajo, INPUT);

  Serial.begin(9600);
}


void loop() {

  estadoFinalArriba = digitalRead(finalCarreraArriba);
  estadoFinalAbajo = digitalRead(finalCarreraArriba);

  botonAmarillo = digitalRead(ApretarAmarillo);
  digitalWrite(LedAmarillo, botonAmarillo);

  botonVerde = digitalRead(ApretarVerde);
  digitalWrite(LedVerde, botonVerde);

  botonRojo = digitalRead(ApretarRojo);
  digitalWrite(LedRojo, botonRojo);


  if (flagStop) {
    digitalWrite(LedRojo, LOW);
    digitalWrite(LedVerde, LOW);
    myStepper.step(0);
  }

  if (estadoFinalArriba == 0 || estadoFinalAbajo == 0) {
    flagStop = true;
  }

  if (flagRed) {
    digitalWrite(LedRojo, HIGH);
    myStepper.step(1);
  }

  if (flagGreen) {
    digitalWrite(LedVerde, HIGH);
    myStepper.step(-1);
  }

  if (botonAmarillo == LOW) {

    flagStop = false;
  }

  if (botonAmarillo == HIGH) {
    flagGreen = false;
    flagRed = false;
    flagStop = true;
  } else if (botonVerde == HIGH) {
    flagRed = false;
    flagGreen = true;

  } else if (botonRojo == HIGH) {
    flagGreen = false;
    flagRed = true;
  }
}

