#include <Wire.h>

// ============== space for macro or golbal defined variables =============

#define MQ5_1 A0 //defined the pins for MQ5 sensor

#define MQ9_1 A1 //defined the pins for MQ9 sensor

#define MQ135_1 A3 //defined the pins for MQ135 sensor

#define BUZZER_PIN 2 //defined the pins for buzzer alram

#define OLED_SDA A4 //defined the pin for the analog input for SDA
#define OLED_SCL A5 //defined the pins for the analog input for SCL

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
}

// ========= Space for only loop function =============
void loop() {
    //taking input from the sensors
    int mq5_value = analogRead(MQ5_1);
    int mq9_value = analogRead(MQ9_1);
    int mq135_value = analogRead(MQ135_1);

    //condition for mq135 smoke sensor
    if(mq135_value > 450) {
        Serial.print("The smoke is detected!! Value of sensor is: ");
        Serial.println(mq135_value);
    }
    else {
        Serial.print("The somke is not detected!! Value of sensor is: ");
        Serial.println(mq135_value);
    }

    //condition for mq5 sensor
    if(mq5_value >= 1350) {
        Serial.print("The value of LPG or natural gases are highly dangerous. The value of the sensor is: ");
        Serial.println(mq5_value);
    }
    else {
        Serial.print("The value of LPG and natural gases are not highly angerous. The value of the sensor is: ");
        Serial.println(mq5_value);
    }
}
