
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,&Wire,-1);

const int Trig = 12;
const int Echo = 11;
int LedRouge=3;
int LedVerte=4;
int Buzzer=6;

void setup()
{
  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C))
  {
    Serial.println("Probleme affichage");
    for(;;);
  }
  //configurer les broches trigPin et echoPin en entrée/sortie
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
  pinMode(LedRouge,OUTPUT);
  pinMode(LedVerte,OUTPUT);
  pinMode(Buzzer,OUTPUT);
  Serial.begin(9600); //initialiser le moniteur série
}

void loop()
{
  long duration,distance;
  
  // envoyer une impulsion de 10 microsecondes
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  tone(6,700);                // Buzzer allumé émettant une fréquence de 700 Hz
  
  // mesurer la durée de l'impulsion écho en microsecondes
  duration=pulseIn(Echo,HIGH);
  
  // calculer la distance en utilisant la vitesse du son (34300 cm/s)
  distance=(duration/2)/29.1;
  
  if(distance>=200 || distance <=0)
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10,10);
    display.println("Distance trop loin");
  }
  else 
  {
    display.print(distance);
    display.println("cm");
  }
  if(distance>=1 && distance<5) // Si la distance est plus grande ou égal à 1 et infèrieur à 5
  {
    digitalWrite(LedRouge,HIGH); // Allumage de la Led Rouge
    tone(6,600);                 // Allumage du buzzer d'une fréquence de 600 Hz
  }
  else
  {
    digitalWrite(LedRouge,LOW);
  }
  if(distance>=5 && distance<10) // Si la distance est plus grande ou égal à 5 et infèrieur à 10
  {
    digitalWrite(LedVerte,HIGH);
    tone(6,400);                  // Allumage du buzzer d'une fréquence de 400 Hz
  }
  else
  {
    digitalWrite(LedVerte,LOW);
  }
  display.display();
  delay(500); // On attend avant de recommencer
}
