// include the library code:
#include <LiquidCrystal.h>
#include <DueTimer.h>
 
// Initialize the library with the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int pushButtonStart =22;
int pushButtonStop = 24;
int clave=0;
int clave1=0;

int buttonState=0; 
int buttonState1=0; 
int sentido=0;

float contador = 0;
int n = contador ;
int a = 26;
int b = 28;
int f=0;
float rev=0;
int sign=1;
float ref=90,kp=0.15,ki=0.1,kd=0;
float pos=0,last=0,acu=0;
float ee,ed,ei;
double pid;
int sensorValue=0;
float outsensor=0;
double outmotor=0;


void setup() {
// set up the LCD's number of columns and rows
Serial.begin(115200);
lcd.begin(16, 2);
// Print a message to the LCD
lcd.print("Press");


  // make the pushbutton's pin an input:||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
pinMode(pushButtonStart, INPUT);
pinMode(pushButtonStop, INPUT);


       pinMode(23, INPUT);
       pinMode(25, INPUT);
       pinMode(27, INPUT);
       pinMode(29, INPUT);
       
       pinMode(a, INPUT);
       attachInterrupt( a, ServicioBoton, FALLING);
       //pinMode(a, INPUT);
       pinMode(b, INPUT);
       Timer3.attachInterrupt(myHandler);
      // Timer3.setFrequency(10);
       Timer3.start(100000); // Calls every 100ms
       
       pinMode(6, OUTPUT);
       pinMode(5, OUTPUT);

       pinMode(3, OUTPUT);
       pinMode(2, OUTPUT);

       digitalWrite(3, LOW);
       digitalWrite(2, HIGH);   
}
 
void loop() {

  lcd.setCursor(0, 1);
  lcd.print(rev);
  
//-------------------------------- intensidad de iluminacion 
//  sensorValue = analogRead(A8);
//
//  outsensor=sensorValue*(255)/(1023);
//  
//  analogWrite(5, outsensor);
  
//------------------------------------
  buttonState = digitalRead(pushButtonStart);
  buttonState1 = digitalRead(pushButtonStop);

   if(f==1){
     if(sentido==0){
    Serial.println('-');
    sign=-1;
    }else{
      Serial.println('+');
      sign=1;
      };
      f=0;
   };



  if(buttonState or clave==1){


  lcd.setCursor(0, 0);
  lcd.print("Start");
  
    
  clave=1;
  clave1=0;  
 // lcd.clear();


  
 outmotor=abs(pid)*(255)/(100); 
   if(pid>0){
    
    analogWrite(6, outmotor);
    digitalWrite(5, LOW);
    };
   if(pid<0){
    
    analogWrite(5, outmotor);
    digitalWrite(6, LOW);
    };


  }

  if(buttonState1 or clave1==1){
    
 
  lcd.setCursor(0, 0);
  lcd.print("Stop");
 
    
    
  clave=0;
  clave1=1; 
  //lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Stop");
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  
  }
  
  // print out the state of the button:
  Serial.print(buttonState);
  Serial.println(buttonState);
//  Serial.println(1);

  delay(1);        // delay in between reads for stability
}

void ServicioBoton() 
   
   {  contador++ ;
      sentido= digitalRead(b);
      f=1;
   }

void myHandler(){
     
     rev=sign*(contador/1600)*10*60;
     
     
     contador=0;

     PID();
}

 void PID()
   {  
 
 ee = ref-rev;  // error actual
 ed = 0;// ee-last;   // error derivativo
 ei=  ee+acu;  // error integral

 pid = (kp*ee) + (ki*ei) + (kd*ed);  // P,I,D terminos
 
 if (pid>100 && pid>0){ pid=100;}
 if (pid<-100 && pid<0){ pid=-100;}
 last=ee;
 acu=acu+ee;
 //velocidad(num);

 //Serial.println(pos); 

   
   }
   



