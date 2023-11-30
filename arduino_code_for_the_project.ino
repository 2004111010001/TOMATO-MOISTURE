#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "**************"      //Paste your credentials here
//#define BLYNK_DEVICE_NAME "TOMATO HUMIDITY"  //Paste your credentials here
#define BLYNK_TEMPLATE_ID "TMPL6mxzIbYo6"
#define BLYNK_TEMPLATE_NAME "TOMATO HUMIDITY"

#include <ESP32_Servo.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "g5VMo9XAGGneLXORCk-0T6zpQCfbKkc0";//Paste auth token you copied

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Internet Positif";///Enter your wifi name
char pass[] = "12345678";// Enter wifi password

int sensor_analog1,sensor_analog2;
float moisture1, moisture2;
const int sm1 = A0; 
const int sm2 = A3;
// Uncomment whatever type you're using!

Servo myservo;
int pos = 0;
int servoPin = 4;
BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  sensor_analog1 = analogRead(sm1);
  sensor_analog2 = analogRead(sm2);
  moisture1 = ( 100 - ( (sensor_analog1/4095.00) * 100 ) );
  moisture2 = ( 100 - ( (sensor_analog2/4095.00) * 100 ) );
  Serial.print("Moisture = ");
  Serial.print(sensor_analog1);
  Serial.print(sensor_analog2);/* Print Temperature on the serial window */
  Serial.println("%"); 

  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V3, moisture1); // select your virtual pins accordingly
  Blynk.virtualWrite(V4, moisture2); // select your virtual pins accordingly
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  delay(1000);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  
  myservo.attach(servoPin, 500, 2400);


  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}

BLYNK_WRITE(V0)
{
bool RelayOne = param.asInt();
  if (RelayOne == 1) {
//    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(120);              // tell servo to go to position in variable 'pos'
      delay(15);
//    }
  } else {
//    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(0);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
//  }
}
