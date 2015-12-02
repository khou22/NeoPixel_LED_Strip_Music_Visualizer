//For NeoPixel Strand
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

//For Spectrum analysis
//Declare Spectrum Shield pin connections
#define STROBE 4
#define RESET 5
#define DC_One A0
#define DC_Two A1 

//Define spectrum variables
int freq_amp;
int Frequencies_One[7];
int Frequencies_Two[7]; 
int i;

int average = 0;

float stripColor[] = {0, 0, 0};
int maxIntensity = 0;
int tempMax = 0;
int currentTimer = 0;
int recheckInterval = 4000; //Recheck max interval every 4 seconds
int lastReset = 0;

//Adjustable
float sensitivity = 70; //Sensitivity to color changes (divided by 100)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800); //Define the strand

void setup() {
  Serial.begin(9600);
  
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  //Set spectrum Shield pin configurations
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(DC_One, INPUT);
  pinMode(DC_Two, INPUT);  
  digitalWrite(STROBE, HIGH);
  digitalWrite(RESET, HIGH);
  
  //Initialize Spectrum Analyzers
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, HIGH);
  delay(1);
  digitalWrite(STROBE, HIGH);
  delay(1);
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, LOW);

  //Define first color
  stripColor[0] = random(0, 255); //New random color
  stripColor[1] = random(0, 255);
  stripColor[2] = random(0, 255);
}

void loop() {
  // put your main code here, to run repeatedly:
  Read_Frequencies();
  Print_Frequencies();
  Light_LEDS();
//  Reset_LEDS();
}

void Read_Frequencies(){
  //Read frequencies for each band
  for (freq_amp = 0; freq_amp<7; freq_amp++)
  {
    Frequencies_One[freq_amp] = ((analogRead(DC_One) + analogRead(DC_One)+analogRead(DC_One)) / 3);
    digitalWrite(STROBE, HIGH);
    digitalWrite(STROBE, LOW);
  }
}

void Print_Frequencies(){
   for( i= 0; i<7; i++)
   {
//    Serial.print(Frequencies_One[i]);
//    Serial.print(" ");
   }
//   Serial.println();
}

void Light_LEDS() {
  
  //Find how many to light up
  for (i = 0; i < 7; i++) {
    average += Frequencies_One[i];
    average += -70; //Compensate
  }
  average = average/7;
//  Serial.println(average);

  checkMaxIntensity();

  float percentage = float(average)/maxIntensity;

  //Determine color
  float threshold = float(sensitivity * maxIntensity)/100;
//  Serial.println(threshold);
  if (average > threshold) {
//    Serial.print(average);
//    Serial.print(": Broke threshold, new color");
//    Serial.println();
    for (i = 0; i < 3; i++) {
      stripColor[i] = random(0, 255);
    }
  }

  //Apply brightness
  percentage += .35;
  float brightness = percentage * percentage;
  if (brightness > 1) {
    brightness = 1;
  }
//  Serial.println(brightness);

  //Turn on lights
  for (i = 0; i < 7; i++) {
    strip.setPixelColor(i, brightness * stripColor[0], brightness * stripColor[1], brightness * stripColor[2]);
    strip.show();
    delay(10);
  }
}

void Reset_LEDS() {
  for (i = 0; i < 7; i++) {
    strip.setPixelColor(i, 0, 0, 0);
    strip.show();
    delay(10);
  }
}

void checkMaxIntensity() {
  currentTimer = millis() - lastReset;
  if (average > tempMax) {
//    Serial.print("Broke threshold ");
//    Serial.print(average);
//    Serial.print(" > ");
//    Serial.print(tempMax);
//    Serial.println();
    tempMax = average + 25; //Store max plus a buffer
  }
//  Serial.print(currentTimer);
//  Serial.print(" versus ");
//  Serial.print(recheckInterval);
//  Serial.println();
  if (currentTimer > recheckInterval) {
//    Serial.println("Resetting max");
    lastReset = millis();
    currentTimer = 0; //Reset timer
    maxIntensity = tempMax;
    tempMax = 0; //Reset temporary
  }
}

