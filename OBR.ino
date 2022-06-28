#include <Ultrasonic.h>
#define led1 A0
#define led2 A1
#define led3 A2
#define led4 A3
#define led5 A4
Ultrasonic ultrasonic(12, 13);
const int m1F = 9;
const int m1T = 10;
const int m2F = 11;
const int m2T = 12;
const int enable1 = 7;
const int enable2 = 13;
int sala = 0;
//Variáveis de velocidade do motor
int velocidadeMotor1, velocidadeMotor2 = 0;

int leituraD1,leituraD2,leituraD3,leituraD4,leituraD5,leituraDist = 0;

void setup() {
  //Definição dos pinos de saída e entrada
  pinMode(led1,INPUT);
  pinMode(led2,INPUT);
  pinMode(led3,INPUT);
  pinMode(led4,INPUT);
  pinMode(led5,INPUT);
  pinMode(m1F,OUTPUT);
  pinMode(m1T,OUTPUT);
  pinMode(m2F,OUTPUT);
  pinMode(m2T,OUTPUT);
  pinMode(enable1,OUTPUT);
  pinMode(enable2,OUTPUT);
}
void moverRobo(){
 leituraD1 = analogWrite(led1); 
 leituraD2 = analogWrite(led2); 
 leituraD3 = analogWrite(led3); 
 leituraD4 = analogWrite(led4); 
 leituraD5 = analogWrite(led5); 
 soma = leituraD1 + leituraD2 - (leituraD4 + leituraD5);
 if(soma > -100 && soma < 100){
  digitalWrite(m1F,HIGH);
  digitalWrite(m1T,LOW);
  digitalWrite(m2F,HIGH);
  digitalWrite(m2T,LOW);
  velocidadeMotor1 = 200;
  velocidadeMotor2 = 200;
 }
 else if(soma > 100){
  digitalWrite(m1F,HIGH);
  digitalWrite(m1T,LOW);
  digitalWrite(m2F,LOW);
  digitalWrite(m2T,HIGH);
  velocidadeMotor1 = map(soma,100,1023,0,255);
  velocidadeMotor2 = map(soma,100,1023,150,0);
 }
 else if(soma < - 100){
  digitalWrite(m1F,HIGH);
  digitalWrite(m1T,LOW); 
  digitalWrite(m2F,HIGH);
  digitalWrite(m2T,LOW);
  velocidadeMotor2 = map(soma,100,1023,0,255);
  velocidadeMotor1 = map(soma,100,1023,150,0);
 } 
 analogWrite(enable1,velocidadeMotor1);
 analogWrite(enable2,velocidadeMotor2);
 }
void curva(){
  leituraDist = ultrasonic1.read(CM);
  velocidadeMotor1 = 200;
  velocidadeMotor2 = 10;
  delay(10);
  digitalWrite(m1F,HIGH);
  digitalWrite(m1T,LOW);
  digitalWrite(m2F,HIGH);
  digitalWrite(m2T,LOW);
  for(int c, c<6, c++){
    velocidadeMotor1 = map(c,0,5,180,10);
    velocidadeMotor2 = map(c,0,5,10,180);
    analogWrite(enable1,velocidadeMotor1);
    analogWrite(enable2,velocidadeMotor2);
    delay(1000);
    }
    }
void loop() {
  if(sala == 0){
    moverRobo()
    if(leituraDist < 15){
      sala = 1;
      }
    }
  else if(sala == 1){
    curva();
    sala = 0;
    }
}
