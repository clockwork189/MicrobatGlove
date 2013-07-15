#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define MAX_POWER 255 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define buzzer1Pin 9


NewPing sonar(TRIGGER_PIN, ECHO_PIN); // NewPing setup of pins and maximum distance.

int power = 0;

void setup() {
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int distance = sonar.ping_cm(); // Send ping, get ping time in microseconds (uS).
  unsigned int power = MAX_POWER - (2 * distance);
  if(distance < MAX_DISTANCE) {
      if(distance > 5) {
          // fade out from max to min in increments of 5 points:
          for(int fadeValue = 0 ; fadeValue <= MAX_POWER; fadeValue +=3) { 
            // sets the value (range from 0 to 255):
            analogWrite(buzzer1Pin, fadeValue);         
            // wait for 30 milliseconds to see the dimming effect    
            delay(5);                            
          } 
          // fade out from max to min in increments of 5 points:
          for(int fadeValue = MAX_POWER ; fadeValue >= 0; fadeValue -=3) { 
            // sets the value (range from 0 to 255):
            analogWrite(buzzer1Pin, fadeValue);         
            // wait for 30 milliseconds to see the dimming effect    
            delay(5);                            
          }
      } else {
          analogWrite(buzzer1Pin, 0);
      }
  } else {
      analogWrite(buzzer1Pin, 0);
  }
  
  Serial.print("POWER:");
  Serial.println(power); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
}
