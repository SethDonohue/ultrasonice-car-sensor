// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

// include the library code
#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
#include <NewPing.h>

//LiquidCrystal_I2C lcd(0x27,16,2);

int buzzerPin = 7;//the pin of the active buzzer attach to pin7
int distance = 0;
int triggerDistanceClose = 5;
int triggerDistanceMed = 15;
int triggerDistanceFar = 30;
int onTime = 100;
int quietTimeClose = 0;
int quietTimeMed = 100;
int quietTimeFar = 200;

#define TRIGGER_PIN  2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(buzzerPin,OUTPUT);//set the buzzer as as OUTPUT
  digitalWrite(buzzerPin,HIGH);//initialize the buzzerPin as LOW level
//  lcd.init(); 
//  lcd.backlight();
}

void loop() {
  delay(100); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  distance = uS / US_ROUNDTRIP_CM;
  Serial.print("Ping: ");
  Serial.print(distance); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  if (distance <= triggerDistanceClose) {
    digitalWrite(buzzerPin, LOW);
//    delay(onTime);
//    digitalWrite(buzzerPin, HIGH);
//    delay(quietTimeClose);
  } else if (distance <= triggerDistanceMed) {
    digitalWrite(buzzerPin, LOW);
    delay(onTime);
    digitalWrite(buzzerPin, HIGH);
    delay(quietTimeMed);
  } else if (distance <= triggerDistanceFar) {
    digitalWrite(buzzerPin, LOW);
    delay(onTime);
    digitalWrite(buzzerPin, HIGH);
    delay(quietTimeFar);
  } 
//  lcd.setCursor(0, 0);
//  lcd.print("Distance:");
//  lcd.setCursor(0, 1);
//  lcd.print("             ");
//  lcd.setCursor(9, 1);
//  lcd.print(uS / US_ROUNDTRIP_CM);
//  lcd.setCursor(12, 1);
//  lcd.print("cm");
}
