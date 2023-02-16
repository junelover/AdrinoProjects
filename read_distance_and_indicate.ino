/*
__________________________________________________________________________________

  This program is A prototype code.
  Auther: Maynard Da Costa (junelover) 
  Project: Blind Sitck 
  Code Name: BS01
  Developed on: 16/02/2023
  Last Updated on: 17/02/2023

  Objective: The working of this project is Basic, it Uses Less Power resulting in
             longer use time. It is also efficient in practical use aswell as in 
             making keep it in buget margin will also helps us to reach out to a
             large user base.
             
  Working: The blind Stick (BS01) is equiped with a ultrasonic sensor which will
           recieve an echo of any obsticals in the range of 4 meters. The close 
           you get to the obsticale the intence haptic feedback you recieve. 
           if the obstical is in range of: 1 meter it will be maxed out
                                           2 meters it will be high
                                           3 meters it will be midium
                                           4 meters it will be low
                                           beyond 4 it will be null.

 this Project is licenced by GNU GENERAL PUBLIC LICENSE (Version 3, 29 June 2007) on GitHub
 at: https://github.com/junelover/AdrinoProjects/blob/Blind-Stick-0.1/LICENSE
___________________________________________________________________________________
*/

// defining hardware pins to comunicate with the board
#define trigPin 10
#define echoPin 13
#define hapticFeedback 0

// float values to set reading sppped and distance.
float duration, distance;

// constants to use for analogWrite(). This decides the intensity value.
const int null = 0;
const int low = 63;
const int mid = 127;
const int high = 191;
const int max = 255;


void setup() {                      // initial setup before starting the actual program
  
  // Setting Hardware pin Constants and init pin setup
  Serial.begin (9600);              // signal pin to read signal 
  pinMode(trigPin, OUTPUT);         // pin used to send ultrasonic signal
  pinMode(echoPin, INPUT);          // pin used to recieve ultrasonic signal 
  pinMode(hapticFeedback, OUTPUT);  // run haptic feedback

}

// This function takes in required params to create a pulsing effect.
// Params:
//        pin: it is uint8_t type variable representing hardware pin on the adrino board
//        pulseDelay: it is an unsigned interger that cannot hold negetive signed interger
//                    value. It is usedto set delay (in Microseconds) before proceding
//        value: it is an integer ranging from 0-255. It is used to set pulse intensity.
//        pulseActive: it is a boolean variable Activating the pulse 
//
void pulseFeedback(uint8_t pin, unsigned int pulseDelay, int value, bool pulseActive){
  while(pulseActive == true){
    analogWrite(pin,value);
    delayMicroseconds(pulseDelay);
    analogWrite(pin,0);
    delayMicroseconds(pulseDelay);
  };
}

void loop() {                        // Actual program running in loop
  
  // Active Listening In a Loop
  digitalWrite(trigPin, LOW);        // turning the ultrasonic sensor low 
  delayMicroseconds(2);              // waiting for 2 micro seconds
  digitalWrite(trigPin, HIGH);       // turning the ultrasonic sencer high 
  delayMicroseconds(10);             // waiting for 10 micro seconds
  digitalWrite(trigPin, LOW);        // turning the ultrasonic sensor low again
  
  // Measure the response from the HC-SR04 Echo Pin
  duration = pulseIn(echoPin, HIGH);
  
  // Determine distance from duration
  // Use 343 metres per second as speed of sound
  distance = (duration / 2) * 0.0343;
  
  // Processing resaults to determine the coresponding type of feedback to the distance of the obstical. 
  Serial.print("Distance is: ");
  if (distance <= 2) {               // if distance is less then 2cm. This will prevent the stick from functioning. Randering a maxed out constant feedback.
      Serial.println("Too close to opperate");        // printing the actual distance in cm to the console.
      pulseFeedback(hapticFeedback, 1, max, true);    // setting feeedback to max.
      delay(25);                                      // setting delay to 25 milliseconds before proceding.

  } else if (distance <= 100 ){      // if distance is less then 100cm (1m). This will randering a high feedback.
      pulseFeedback(hapticFeedback, 3, high, true);   // setting feeedback to high.
      Serial.print(distance);                         // printing the actual distance in cm to the console.
      Serial.println(" cm");
      delay(50);                                      // setting delay to 50 milliseconds before proceding.

  } else if (distance <= 200 ){      // if distance is less then 200cm (2m). This will randering a mid feedback.
      pulseFeedback(hapticFeedback, 5, mid, true);    // setting feeedback to mid.
      Serial.print(distance);                         // printing the actual distance in cm to the console.
      Serial.println(" cm");
      delay(50);                                      // setting delay to 50 milliseconds before proceding.

  } else if (distance <= 300 ){      // if distance is less then 300cm (3m). This will randering a low feedback.
      pulseFeedback(hapticFeedback, 5, low, true);    // setting feeedback to low.
      Serial.print(distance);                         // printing the actual distance in cm to the console.
      Serial.println(" cm");
      delay(50);                                      // setting delay to 50 milliseconds before proceding.

  } else if (distance <= 400 ){      // if distance is less then 400cm (4m). This will randering a low feedback.
      pulseFeedback(hapticFeedback, 10, low, true);    // setting feeedback to low.
      Serial.print(distance);                          // printing the actual distance in cm to the console.
      Serial.println(" cm");
      delay(50);                                       // setting delay to 50 milliseconds before proceding.

  } else {                           // if distance is more then 400cm (4m). This will randering a no feedback.
      pulseFeedback(hapticFeedback, 0, null, false);   // setting feeedback to none.
      Serial.print(distance);                          // printing the actual distance in cm to the console.
      Serial.println(" cm");
      delay(50);                                       // setting delay to 50 milliseconds before proceding.
    
  }
  delay(50);                         // setting delay to 50 milliseconds before proceding.

}



