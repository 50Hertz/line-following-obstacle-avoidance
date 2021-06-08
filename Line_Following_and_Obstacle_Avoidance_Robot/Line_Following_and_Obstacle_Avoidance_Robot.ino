#define echopin A4 // Echo pin
#define trigpin A5 // Trigger pin


int motor_r2 = 9;
int motor_r1 = 10;

int motor_l2 = 5;
int motor_l1 = 6;


int speed = 115;

int  frontdist;
long duration;

int setdist = 10;

int L_S = A0; //Left IR Sensor
int R_S = A1; //Right IR Sensor

int leftSensorState;
int rightSensorState;

void setup(){
 
 pinMode(motor_l1, OUTPUT);
 pinMode(motor_l2, OUTPUT);
 
 pinMode(motor_r1, OUTPUT);
 pinMode(motor_r2, OUTPUT);

 pinMode (trigpin, OUTPUT);
 pinMode (echopin, INPUT);
 
 pinMode(L_S, INPUT);
 pinMode(R_S, INPUT);

 Serial.begin(9600);
 delay(1000);
 }

void loop(){
frontdist = data();

leftSensorState = digitalRead(L_S);
rightSensorState = digitalRead(R_S);

//Serial.println("Front Distance: ");
//Serial.println(frontdist);
  
//Serial.println("Left Sensor: ");
//Serial.println(leftSensorState);

//Serial.println("Right Sensor: ");
//Serial.println(rightSensorState); 

//delay(3000);

if(frontdist>setdist){
if ((leftSensorState == 0)&&(rightSensorState == 0)){forward();}
if ((leftSensorState == 0)&&(rightSensorState == 1)){turnRight();}
if ((leftSensorState == 1)&&(rightSensorState == 0)){turnLeft();}
}else{

turnLeft();
delay(350);
forward();
delay(850);
turnRight();  
delay(300);
forward();
delay(500);
//turnRight();  
//delay(350);
//forward();
//delay(500);
}

}

long data(){
 digitalWrite(trigpin,LOW);
 delayMicroseconds(2);
 digitalWrite(trigpin,HIGH);
 delayMicroseconds(10);
 duration=pulseIn (echopin,HIGH);
 return duration / 29 / 2; 
}

void stop(){
 //Serial.println("Stopping...");
 analogWrite(motor_l1, 0);
 analogWrite(motor_l2, 0);
 analogWrite(motor_r1, 0);
 analogWrite(motor_r2, 0);  
}

void forward(){
 //Serial.println("Moving Forward...");
 analogWrite(motor_l1, speed);
 analogWrite(motor_l2, 0);
 analogWrite(motor_r1, 0);
 analogWrite(motor_r2, speed);  
}

void backword(){
 //Serial.println("Moving Backward...");
 analogWrite(motor_l1, 0);
 analogWrite(motor_l2, speed);
 analogWrite(motor_r1, speed);
 analogWrite(motor_r2, 0);   
}


void turnRight(){
//Serial.println("Moving Right...");
analogWrite(motor_l1, 0);
analogWrite(motor_l2, speed);
analogWrite(motor_r1, 0);
analogWrite(motor_r2, speed);  
}

void turnLeft(){
//Serial.println("Moving Left...");
analogWrite(motor_l1, speed);
analogWrite(motor_l2, 0);
analogWrite(motor_r1, speed);
analogWrite(motor_r2, 0);   
}
