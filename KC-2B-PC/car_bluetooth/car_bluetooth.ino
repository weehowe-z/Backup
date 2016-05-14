#define LEFT_AHEAD 9
#define LEFT_BACK 10
#define RIGHT_AHEAD 12
#define RIGHT_BACK 13
#define STEER 14
int duty=1082;//diffrent car differnt duty 1082
String inString="";
float RunInit=3.0;
float RUN_LEFT=3.0;
float RUN_RIGHT=3.0;

int TURN=60;
int RUN1=255;
int CYC=5;
float calibrateNum=0;
void stopBack();
void turnLeft();
void turnRight();
void goAhead();
void park();
void goBack();

void setup(){
Serial.begin(9600);
pinMode(LEFT_AHEAD,OUTPUT);
pinMode(LEFT_BACK,OUTPUT);
pinMode(RIGHT_AHEAD,OUTPUT);
pinMode(RIGHT_BACK,OUTPUT);
digitalWrite(LEFT_AHEAD,LOW);
digitalWrite(LEFT_BACK,LOW);
digitalWrite(RIGHT_AHEAD,LOW);
digitalWrite(RIGHT_BACK,LOW);

pinMode(STEER,OUTPUT);
digitalWrite(STEER,LOW);

for (int i=0;i<100;i++) {
digitalWrite(STEER,HIGH);
delayMicroseconds(duty);
digitalWrite(STEER,LOW);
delayMicroseconds(13000-duty);
delayMicroseconds(6550);
}
}
char incomingByte = ' ';//acess data

void loop(){
if (Serial.available() > 0) {
// read the incoming byte:
incomingByte=Serial.read();
Serial.println(incomingByte);
if (incomingByte=='L') {
Serial.println("TURN LEFT");
turnLeft();
Serial.read();
} else if (incomingByte=='R'){
Serial.println("TURN RIGHT");
turnRight();
Serial.read();
} else if (incomingByte=='A'){
Serial.println("GO AHEAD");
goAhead();
Serial.read();
} else if (incomingByte == 'B'){
  Serial.println("GO BACK");
goBack();
Serial.read();
} else if (incomingByte=='P'){
Serial.println("PARK");
park();
Serial.read();
} else if (incomingByte=='C'){
calib();
} else if (incomingByte=='K'){
changeP();
} else if (incomingByte=='S'){
changeS();
} else if (incomingByte=='D'){
changeD();
}
}
}

void park(){
digitalWrite(LEFT_BACK, LOW);
digitalWrite(RIGHT_BACK, LOW);
digitalWrite(LEFT_AHEAD, LOW);
digitalWrite(RIGHT_AHEAD, LOW);
steer(1);
}

void goAhead(){
digitalWrite(LEFT_BACK, LOW);
digitalWrite(RIGHT_BACK, LOW);
analogWrite(LEFT_AHEAD,RUN1);
analogWrite(RIGHT_AHEAD,RUN1);
steer(1.0);
}


void goBack(){
digitalWrite(LEFT_AHEAD,LOW);
digitalWrite(RIGHT_AHEAD,LOW);
analogWrite(LEFT_BACK,RUN1);
analogWrite(RIGHT_BACK,RUN1);
steer(1);
}


void turnLeft(){
digitalWrite(LEFT_BACK, LOW);
digitalWrite(RIGHT_BACK, LOW);
analogWrite(RIGHT_AHEAD,RUN1);
analogWrite(LEFT_AHEAD,TURN);
steer(1.1);
}

void turnRight(){
digitalWrite(LEFT_BACK, LOW);
digitalWrite(RIGHT_BACK, LOW);
analogWrite(LEFT_AHEAD,RUN1);
analogWrite(RIGHT_AHEAD,TURN);
steer(0.88);
}

void steer(float x){
int tmp=x*duty;

for (int i=0;i<CYC;i++) {
digitalWrite(STEER,HIGH);
delayMicroseconds(tmp);
digitalWrite(STEER,LOW);
delayMicroseconds(13000-tmp);
delayMicroseconds(6550);
}
digitalWrite(STEER,LOW);
}

//void stopBack(){
//digitalWrite(LEFT_BACK, LOW);
//digitalWrite(RIGHT_BACK, LOW);
//}

int readInt(){
int x;
int flag=1;
while(flag){
while (Serial.available() > 0) {
int inChar = Serial.read();
if (isDigit(inChar)) {
inString += (char)inChar;
//Serial.println(inString);
}
// if you get a newline, print the string,
// then the string's value:
else {
x=inString.toInt();
Serial.println("now calibrate:");
Serial.println(x);
flag=0;
// clear the string for new input:
inString = "";
  }
 }
}
return x;
}

void calib(){
Serial.println("calibrate:");
TURN=readInt();
Serial.println(TURN,DEC);
}
void changeP(){
CYC = readInt();
Serial.println("DELAY(ms):");
Serial.println(CYC*2,DEC);
}

void changeS(){
RUN1 = readInt();
Serial.println("new spead:");
Serial.println(RUN1,DEC);
}

void changeD(){
duty = readInt();
Serial.print("new duty:");
Serial.println(duty,DEC);
}


