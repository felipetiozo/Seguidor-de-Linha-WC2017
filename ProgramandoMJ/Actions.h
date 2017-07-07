#include <Arduino.h>
#include <Servo.h>
#include <QTRSensors.h>

/*
  FUNÇÕES de Ação DO ROBÔ
*/

void pararMotores() {
  analogWrite(MotorEsquerdoFrente, 0);
  analogWrite(MotorEsquerdoTras, 0);

  /*** direita ***/
  analogWrite(MotorDireitoFrente, 0);
  analogWrite(MotorDireitoTras, 0);
}


/*** bloco okk ****/
void mover(int a, int b) {
  if (a > 0) {
    analogWrite(MotorEsquerdoFrente, a);
    analogWrite(MotorEsquerdoTras, 0);
  }
  else if (a == 0) {
    analogWrite(MotorEsquerdoFrente, 0);
    analogWrite(MotorEsquerdoTras, 0);
  }
  else {
    analogWrite(MotorEsquerdoFrente, 0);
    analogWrite(MotorEsquerdoTras, abs(a));
  }
  if (b > 0) {
    analogWrite(MotorDireitoFrente, b);
    analogWrite(MotorDireitoTras, 0);
  }
  else if (b == 0) {
    analogWrite(MotorDireitoFrente, 0);
    analogWrite(MotorDireitoTras, 0);
  }
  else {
    analogWrite(MotorDireitoFrente, 0);
    analogWrite(MotorDireitoTras, abs(b));
  }
};


void AlertaDeInicio() {
  // Acender Todos LEDs
  // Dar Beep no buzzer
  Buzzer.turnOn();
  LED1.turnOn();
  LED2.turnOn();
  LED3.turnOn();
  delay(25);
  Buzzer.turnOff();
  LED1.turnOff();
  LED2.turnOff();
  LED3.turnOff();
  delay(50);
  Buzzer.turnOn();
  LED1.turnOn();
  LED2.turnOn();
  LED3.turnOn();
  delay(25);
  Buzzer.turnOff();
  LED2.turnOff();
  LED3.turnOff();
}
int erro; int P; int I; int D;

int ganho;

double motorB; double motorC;
int pass = 0;

void PID (double kP, double kI, double kD, double tP, int media) {

    
  erro = lerTodosQTR() - media;
  
  P = kP * erro;
  I = I + (erro * kI);
//  I = 0;
  D = kD * (erro - lastError);

  ganho = P + I + D;

  lastError = erro;

  motorB = tP + ganho;
  motorC = tP - ganho;
 /*if(lerQTR(7) < 750) {
    pass++;
    LED1.turnOn();
    while(pass == 10) {
    mover(0,0);
    }
  } else {
   */ 
   
   //LED1.turnOff();
    mover(motorB, motorC);
  //}
};

