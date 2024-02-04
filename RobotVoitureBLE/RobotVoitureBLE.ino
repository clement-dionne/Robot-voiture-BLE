///////////////////   variable ////////////////
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#include <SoftwareSerial.h>
SoftwareSerial HC06(13,12);
String messageRecu;
const byte TRIGGER_PIN = 3; // Broche TRIGGER
const byte ECHO_PIN = 4;    // Broche ECHO
const unsigned long MEASURE_TIMEOUT = 25000UL;
const float SOUND_SPEED = 340.0 / 1000;
int va = 62;
int vb = 125;
int vc = 187;
int vd = 250;
int vitesse = 2;
long measure;
float distance_mm;
float cm;
//////////////////////////////////// setup //////////////////////
void setup() {
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN, INPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  Serial.begin(9600);
  HC06.begin(9600); 
  pinMode(2, OUTPUT); 
  vitesse = 2;
 }
///////////////////////////// loop ///////////
void loop()
{
////////////////////////////// antichoc avant /////////////
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
   measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
   distance_mm = measure / 2.0 * SOUND_SPEED;
   cm = distance_mm / 10.0, 2;
  Serial.print(("Distance: "));
  Serial.print(distance_mm);
  Serial.print("mm (");
  Serial.print(distance_mm / 10.0, 2);
  Serial.print("cm, ");
  Serial.print(distance_mm / 1000.0, 2);
  Serial.println("m)");
  if(cm < 30 && cm > 1){
  analogWrite(ENA,vc);
  analogWrite(ENB,vc);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(350);
  analogWrite(ENA,LOW);
  analogWrite(ENB,LOW);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);    
  }
///////////////////////////// initialisation du bleutooth (HC-06) ///////
    while(HC06.available())
    {
      delay(3);
      char c = HC06.read();
      messageRecu += c;
    }
    if (messageRecu.length() >0)
    {
      Serial.println(messageRecu);
//////////////////////////////////// commande robot ////////////////////
////////////////////////////////////// commande simple robot ///////////
if (vitesse == 2)
{
      if (messageRecu == "avant")     
  {
  analogWrite(ENB,vb);
  analogWrite(ENA,vb);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  }
      if (messageRecu == "arriere")
  {
  analogWrite(ENB,vb);
  analogWrite(ENA,vb);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH); 
  }
        if (messageRecu == "droite")     
  {
  analogWrite(ENA,vb);
  analogWrite(ENB,vb);
  digitalWrite(IN1,LOW); //set IN1 hight level
  digitalWrite(IN2,HIGH);  //set IN2 low level
  digitalWrite(IN3,LOW);  //set IN3 low level
  digitalWrite(IN4,HIGH); //set IN4 hight level 
  }
      if (messageRecu == "gauche")
  {
  analogWrite(ENA,vb);
  analogWrite(ENB,vb);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  }
///////////////////////////////// commande complex robot ///////////////////
if (messageRecu == "avantdroite")
  {
  analogWrite(ENA,vc);
  analogWrite(ENB,va);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  }
  if (messageRecu == "avantgauche")
  {
  analogWrite(ENA,va);
  analogWrite(ENB,vc);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  }
  if (messageRecu == "arrieredroite")
  {
  analogWrite(ENA,vc);
  analogWrite(ENB,va);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  }
  if (messageRecu == "arrieregauche")
  {
  analogWrite(ENA,va);
  analogWrite(ENB,vc);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  }
  if (messageRecu == "stop")
  {
  analogWrite(ENA,LOW);
  analogWrite(ENB,LOW);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW); 
  }
  if (messageRecu == "vitesseplus")
  {
  vitesse = vitesse - 1;
  delay(10);
  }
}
if (vitesse == 1)
{
  if (messageRecu == "avant")     
  {
  analogWrite(ENB,vd);
  analogWrite(ENA,vd);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  }
  if (messageRecu == "arriere")
  {
  analogWrite(ENB,vd);
  analogWrite(ENA,vd);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH); 
  }
  if (messageRecu == "droite")     
  {
  analogWrite(ENA,vb);
  analogWrite(ENB,vb);
  digitalWrite(IN1,LOW); //set IN1 hight level
  digitalWrite(IN2,HIGH);  //set IN2 low level
  digitalWrite(IN3,LOW);  //set IN3 low level
  digitalWrite(IN4,HIGH); //set IN4 hight level 
  }
  if (messageRecu == "gauche")
  {
  analogWrite(ENA,vb);
  analogWrite(ENB,vb);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  }
///////////////////////////////// commande complex robot ///////////////////
  if (messageRecu == "avantdroite")
  {
  analogWrite(ENA,vd);
  analogWrite(ENB,vb);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  }
  if (messageRecu == "avantgauche")
  {
  analogWrite(ENA,vb);
  analogWrite(ENB,vd);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  }
  if (messageRecu == "arrieredroite")
  {
  analogWrite(ENA,vd);
  analogWrite(ENB,vb);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  }
  if (messageRecu == "arrieregauche")
  {
  analogWrite(ENA,vb);
  analogWrite(ENB,vd);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  }
  if (messageRecu == "stop")
  {
  analogWrite(ENA,LOW);
  analogWrite(ENB,LOW);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW); 
  }
  if (messageRecu == "vitessemoins")
  {
  vitesse = vitesse + 1;
  delay(10);
  }
}
///////////////////////////////// commande vitesse robot ////////////////////
///////////////////////////////// stop et fin du programe ///////////////////
      messageRecu="";
    }
    delay(200);
}
