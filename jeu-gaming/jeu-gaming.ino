#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);
int JoystickX = A0;
int JoystickY = A1;
int valX;
int valY;
int Y = 10;
int X = 10;
int bo = 0;
int c = 2;
int f = 0;
int v = 2;
int p = 50;
int n = 1;
int kl = 0;

void setup() {
  Serial.begin(9600);
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();
  delay(10);
  display.drawRect(2, 2, 124, 56, WHITE); // Dessiner un rectangle de 50x20 pixels à la position (10, 10)
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(25, 20);
  display.println("ARIO");
  display.display();
  delay(1000);
  display.clearDisplay();
  display.display();
  delay(10);
}

void loop() {
 valX = analogRead(JoystickX);
 valY = analogRead(JoystickY);
  control();
  arrive();
  border();
  display.fillRect(Y, X, 20, 20, WHITE); // Dessiner un rectangle de 50x20 pixels à la position (10, 10)
  
  display.display();
  delay(100);
  display.clearDisplay(); // effacer l'écran
  delay(10);

}

void border(){
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("niveau:");
  display.print(n);
  display.fillRect(125, bo, 3, 64, WHITE);
  if(bo >= 50){
    f = 1;
  }
  if(f == 1){
    bo -= v;
    c = 1;
  }else if(f == 0){
    bo += v;
    c = 2;
  }
}
void arrive(){
  if(Y >= 105 && X >= bo && f == 0){
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(20, 20);
    display.println("GAGNER !");
    display.display();
    delay(3000);
    v++;
    p++;
    n++;
    reset();
  }if(Y >= 105 && X <= bo + 64 && f == 1){
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(20, 20);
    display.println("GAGNER !");
    display.display();
    delay(3000);
    v++;
    p++;
    n++;
    reset();
  }
  else if(bo <= -60){
    perdu();
  }else if(Y >= 105 && X <= bo && f == 0){
    perdu();
  }
  else if(Y >= 105 && X >= bo + 64 && f == 1){
    perdu();
  }
}
void perdu(){
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(20, 20);
    display.println("PERDU !");
    display.display();
    delay(3000);
    n--;
    reset();
}
void reset(){
    Y = 10;
    X = 10;
    bo = 0;
    c = 2;
    f = 0;
    loop();
}

void control(){
if(valY >= 1000 && Y >= 0){
    Serial.println("gauche");
    Y -= 8;
  }
  if(valY <= 60 && Y <= 128){
    Serial.println("droite");
    Y += 8;
  }
  if(valX >= 1000 && X <= 60){
    Serial.println("bas");
    X += 8;
  }
  if(valX <= 60 && X >= 0){
    Serial.println("haut");
    X -= 8;
  }
}
