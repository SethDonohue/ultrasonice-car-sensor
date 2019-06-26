// ---------------------------------------------------------------------------
// Sensor sketch that pins every 50ms between each sensor and signals buzzer according to the lowest distance pinged.
// ---------------------------------------------------------------------------
#include <Wire.h>
#include <NewPing.h>

int buzzerPin = 7;//the pin of the active buzzer attach to pin7
int distance = 0;
int distances[4];
int triggerDistanceClose = 10;
int triggerDistanceMed = 25;
int triggerDistanceFar = 40;
int onTime = 100;
int quietTimeClose = 0;
int quietTimeMed = 100;
int quietTimeFar = 200;

// #define TRIGGER_PIN  2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
// #define ECHO_PIN     3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define SONAR_NUM 4 // Numer of Sensors
#define MAX_DISTANCE 250 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar[SONAR_NUM] = {
  NewPing(2, 3, MAX_DISTANCE), // each sensors trigger pin, echo pin, and max distance.
  NewPing(4, 5, MAX_DISTANCE),
  NewPing(6, 7, MAX_DISTANCE),
  NewPing(8, 9, MAX_DISTANCE)
};

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(buzzerPin,OUTPUT);//set the buzzer as as OUTPUT
  digitalWrite(buzzerPin,HIGH);//initialize the buzzerPin as LOW level
}

void loop() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    delay(50); // 29ms should be the shortest delay between pings.
    unsigned int distance = sonar[i].ping_cm();
    distances[i] = distance;
    Serial.print(i);
    Serial.print('=');
    Serial.print(distance);
    Serial.print("cm ");
  }
  Serial.println();

  // IF ANY of the distances are below the thresholds take lowest adn signal the buzzer accordingly.
  for (uint8_t i = 0; i < SONAR_NUM; i++){
    if(distances[i] < distances[0]) distances[0] = distances[i];
  }

  if (distances[0] <= triggerDistanceClose) {
    digitalWrite(buzzerPin, LOW);
    Serial.println("Close");
  } else if (distances[0] <= triggerDistanceMed) {
    digitalWrite(buzzerPin, LOW);
    delay(onTime);
    digitalWrite(buzzerPin, HIGH);
    delay(quietTimeMed);
    Serial.println("Med");
  } else if (distances[0] <= triggerDistanceFar) {
    digitalWrite(buzzerPin, LOW);
    delay(onTime);
    digitalWrite(buzzerPin, HIGH);
    delay(quietTimeFar);
    Serial.println("Far");
  } 
}