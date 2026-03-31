#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ============== space for macro or golbal defined variables =============

#define MQ5_1 A0 //defined the pins for MQ5 sensor

#define MQ9_1 A1 //defined the pins for MQ9 sensor

#define MQ135_1 A3 //defined the pins for MQ135 sensor

#define BUZZER_PIN 2 //defined the pins for buzzer alram

#define OLED_SDA A4 //defined the pin for the analog input for SDA
#define OLED_SCL A5 //defined the pins for the analog input for SCL

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 diplay(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// ========== Space for only setup function ==========

void setup() {
    Serial.begin(9600);
    //defining the pin's mode for sensors
    pinMode(MQ5_1, INPUT);
    pinMode(MQ9_1, INPUT);
    pinMode(MQ135_1, INPUT);

    //defining the pin's mode for buzzer using digital pins
    pinMode(BUZZER_PIN, OUTPUT);

    //defining the pin's mode for OLED screen using analog pins
    Wire.begin();

    //Initialize OLED
    if(!display.begin(SSD1306_SWITCHAPVCC, 0x3C)) {
        Serial.println("OLED NOT FOUND!!");
        while(true);
    }
    display.clearDisplay();
}

// ========= Space for only loop function =============
void loop() {
    int danger = 0;
    //taking input from the sensors
    int mq5_value = analogRead(MQ5_1);
    int mq9_value = analogRead(MQ9_1);
    int mq135_value = analogRead(MQ135_1);

    //condition for mq135 smoke sensor
    if(mq135_value > 450) danger = max(danger, 1);
    if(mq135_value > 700) danger = max(danger, 2);

    // condition for mq5 snesor
    if(mq5_value > 350) danger = max(danger, 1);
    if(mq5_value > 600) danger = max(danger, 2);

    //condition for mq9 sensor
    if(mq9_value > 850) danger = max(danger, 1);
    if(mq9_value > 1000) danger = max(danger, 2);

    //setting up code for OLED screen
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    //writing the code for buzzer
    if(danger == 2) {
        digitalWrite(BUZZER_PIN, HIGH);
    }
    else {
        digitalWrite(BUZZER_PIN, LOW);
    }

    delay(500);
}
