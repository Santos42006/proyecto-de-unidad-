//Canal de YouTube -> RobotUNO
//BRAZO ROBOTICO 2.0

#include <Servo.h>  //se agrega la libreria llamada servo
#include <Stepper.h>  //se agrega la libreria llamada stepper
#define STEPS 32    //se crea una variable constante con valor 32
#define temp 25  //se crea una variable constante con valor 25

//MOTOR PASO A PASO
volatile boolean TurnDetected; //volatile quiere decir que el valor puede cambiar en cualquier momento
volatile boolean rotationdirection;   //boollean quiere decir que puede almacenar infomacion binaria 
const int PinCLK=2;    //const se utiliza para darle un valor fijo a una variable
const int PinDT=3;   //int es para decir que  la variable es de valor entero 
int RotaryPosition=0;   
int PrevPosition;    
int StepsToTake; 
Stepper small_stepper(STEPS, 4, 6, 5, 7);  //stepper es una funcion de la libreria que agregamos
void isr ()  {
  delay(4);  // delay for Debouncing
  if (digitalRead(PinCLK))  //si la lectura de pinCLK es HIGH 
    rotationdirection= digitalRead(PinDT); // aqui dice que va a girar 
  else 
    rotationdirection= !digitalRead(PinDT); //pero si es LOW va a girar para el lado contrario 
  TurnDetected = true;  //aqui confirma que tiene que haber un movimiento para alguno de los dos lados 
}
//SERVOMOTORES
int i=0,j=0,x=0;
Servo servomotor3; //Servomotor pinza es funcion de la libreria
int boton_sub3=0;
int boton_baj3=0;
Servo servomotor2; //Servomotor en medio es funcion de la libreria
int boton_sub2=0;
int boton_baj2=0;
Servo servomotor1; //Servomotor abajo es funcion de la libreria
int boton_sub1=0;
int boton_baj1=0;

void setup(){
  //MOTOR PASO A PASO
  pinMode(PinCLK,INPUT);
  pinMode(PinDT,INPUT);  
  attachInterrupt (0,isr,FALLING); //FALLING es para que verifique si el pin que indicamos cambia de HIGH o LOW 

  //SERVOMOTORES
  servomotor3.attach(13); 
  servomotor3.write(0);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  
  servomotor2.attach(12);
  servomotor2.write(0);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  
  servomotor1.attach(11);
  servomotor1.write(0);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
}

void loop(){
  //MOTOR PASO A PASO
  small_stepper.setSpeed(700); // velocidad a la que se va a mover el motor
  if (TurnDetected)  {
    PrevPosition = RotaryPosition; 
    if (rotationdirection) {
      RotaryPosition=RotaryPosition-1;}
    else {RotaryPosition=RotaryPosition+1;}
    TurnDetected = false;
    if ((PrevPosition + 1) == RotaryPosition) {
      StepsToTake=50; 
      small_stepper.step(StepsToTake);}
    if ((RotaryPosition + 1) == PrevPosition) {
      StepsToTake=-50;
      small_stepper.step(StepsToTake);}
  }
     digitalWrite(4, LOW);
     digitalWrite(5, LOW);
     digitalWrite(6, LOW);
     digitalWrite(7, LOW);   
  
  //SERVOMOTOR pinza
  boton_sub3=digitalRead(A4);
  boton_baj3=digitalRead(A5);
  if(boton_sub3==HIGH){
     i++;
     servomotor3.write(i);
     delay(temp);
  }
  if(boton_baj3==HIGH){
    i--;
    servomotor3.write(i);
    delay(temp);
  }
  //SERVOMOTOR en medio 
  boton_sub2=digitalRead(A2);
  boton_baj2=digitalRead(A3);
  if(boton_sub2==HIGH){
     j++;
     servomotor2.write(j);
     delay(temp);
  }
  if(boton_baj2==HIGH){
    j--;
    servomotor2.write(j);
    delay(temp);
  }
  //SERVOMOTOR abajo
  boton_sub1=digitalRead(A0);
  boton_baj1=digitalRead(A1);
  if(boton_sub1==HIGH){
     x++;
     servomotor1.write(x);
     delay(temp);
  }
  if(boton_baj1==HIGH){
    x--;
    servomotor1.write(x);
    delay(temp);
  }
}