#include <NewPing.h>

// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define TRIGGER_PIN1  6  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN1     7  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN2  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN2     13  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 255 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define buzzer1Pin 8
#define buzzer2Pin 9
#define buzzer3Pin 10

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
//NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {
  delay(100);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int distance1 = sonar1.ping_cm(); // Send ping, get ping time in microseconds (uS).
  if(distance1 < 100) {  
    analogWrite(buzzer1Pin, MAX_DISTANCE - distance1); 
    analogWrite(buzzer2Pin, MAX_DISTANCE - distance1); 
    analogWrite(buzzer3Pin, MAX_DISTANCE - distance1); 
  } else {
    analogWrite(buzzer1Pin, 0); 
    analogWrite(buzzer2Pin, 0); 
    analogWrite(buzzer3Pin, 0); 
  }
//  unsigned int distance2 = sonar2.ping_cm(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping Distance 1: ");
  Serial.print(distance1); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
  Serial.println("cm");
  
//  Serial.print("Ping Distance 2: ");
  //Serial.print(distance2); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
//  Serial.println("cm");
}
