SYSTEM_THREAD(ENABLED);
#include <blynk.h>
#include "oled-wing-adafruit.h"

int i = 1;

OledWingAdafruit display;

void setup() {
  display.setup();
	display.clearDisplay();
	display.display();
  Blynk.begin("CyJI8nsiIsPGDAjjUxFqc902n-8Vns1N", IPAddress(167, 172, 234, 162), 9090);

}

void loop() {
  display.loop();
  Blynk.run();

  //The formula to get the temperature in celsius and fahrenheit and from the TMP36
  uint64_t reading = analogRead(A5);
  double voltage = (reading * 3.3) / 4095.0;
  double temperature = (voltage - 0.5) * 100;
  double fahrenheit = temperature * 1.8 + 32;
  
  //preparing the message for the oled display and notification
  String strCelsius = String(temperature); 
  String strFahrenheit = String(fahrenheit);
  String textForNotification = " your temperature in celsius is: "+ strCelsius+ "\n and in fahrenheit: "+ strFahrenheit;
  String textForOledDisplay = "Your temerature is:\ncelsius: "+ strCelsius + "\nfahrenheit: " + strFahrenheit;

  //to display the temperature for the first time in the oled display
  if(i == 1){
    display.clearDisplay();
  	display.setTextSize(1);
	  display.setTextColor(WHITE);
	  display.setCursor(0,0);
    display.print(textForOledDisplay);
    display.display();
    i = i +1;
  }

  // to display the temperature on the oled display and send it as a notification
  if (display.pressedA()) {
    display.clearDisplay();
    display.setTextSize(1);
	  display.setTextColor(WHITE);
	  display.setCursor(0,0);
    display.println("push sent");
    display.display();
    delay(5000);
    Blynk.notify(textForNotification);
    display.clearDisplay();
    display.print(textForOledDisplay);
		display.display();
  }

}