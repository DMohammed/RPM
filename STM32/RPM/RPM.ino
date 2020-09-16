#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     2//PE11 for stm32fvgt6 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

HardwareTimer *MyTim;

const int PIR = PB12;
bool PIRstate = 0;
long counter = 0;
long RPM = 0;

void setup() {

display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();


  display.clearDisplay();
  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.println("Start");
  display.display();
  delay(1000);

  
  TIM_TypeDef *Instance = TIM1;
  MyTim = new HardwareTimer(Instance);



  MyTim->setOverflow(1, HERTZ_FORMAT); // 10 Hz
  MyTim->attachInterrupt(updateRPM);
  MyTim->resume();



  // put your setup code here, to run once:
  


  //pinMode(3, INPUT);
  pinMode(13, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(3), timer, RISING);
}

void timer() {
  counter++;
}
void updateRPM() {
  RPM = counter;
  counter = 0;
  printer(String(RPM*60));
}

void loop() {

}


void printer(String value) {

  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.println("Electropeak");
  display.setTextSize(2);
  display.setCursor(10, 20);     // Start at top-left corner
  display.println(value);
  display.display();

}
