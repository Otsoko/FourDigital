#include <SoftwareSerial.h>

int pinD1 = 2;
int pinD2 = 3;
int pinD3 = 4;
int pinD4 = 5;

int pins[4] = {pinD1, pinD2, pinD3, pinD4};

// DP,G,F,E,D,C,B,A
const int segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};

int value = 0;

int first_digit  = 0;
int second_digit = 0;
int third_digit  = 0;
int fourth_digit = 0;

byte numbers[10]{B11111100, B01100000, B11011010, B11110010, B01100110,
                 B10110110, B10111110, B11100000, B11111110, B11110110};

int       digits[4] = {0, 0, 0, 0};
const int nbrDigits = 4; // the number of digits in the LED display
int       mdelay    = 1;

void setup() {
    Serial.begin(9600);

    pinMode(pinD1, OUTPUT);
    pinMode(pinD2, OUTPUT);
    pinMode(pinD3, OUTPUT);
    pinMode(pinD4, OUTPUT);

    digitalWrite(pinD1, HIGH);
    digitalWrite(pinD2, HIGH);
    digitalWrite(pinD3, HIGH);
    digitalWrite(pinD4, HIGH);

    for (byte i = 0; i < 9; i++) {
        pinMode(segmentPins[i], OUTPUT);
        digitalWrite(segmentPins[i], HIGH);
    }
}

void break_number(long num) { // seperate the input number into 4 single digits

    first_digit = num / 1000;
    digits[0]   = first_digit;

    int first_left  = num - (first_digit * 1000);
    second_digit    = first_left / 100;
    digits[1]       = second_digit;
    int second_left = first_left - (second_digit * 100);
    third_digit     = second_left / 10;
    digits[2]       = third_digit;
    fourth_digit    = second_left - (third_digit * 10);
    digits[3]       = fourth_digit;
}

// Displays given number on a 7-segment display at the given digit position
void showDigit(int number, int digit) {

    digitalWrite(pinD1, HIGH);
    digitalWrite(pinD2, HIGH);
    digitalWrite(pinD3, HIGH);
    digitalWrite(pinD4, HIGH);

    digitalWrite(pins[digit], HIGH);
    digitalWrite(segmentPins[0], false);
    for (int segment = 1; segment < 8; segment++) {
        boolean isBitSet = bitRead(numbers[number], segment);
        // isBitSet will be true if given bit is 1
        // isBitSet = ! isBitSet; // Code Option*
        // uncomment the above Code Option line for common anode display
        digitalWrite(segmentPins[segment], isBitSet);
    }
    delay(5);
    digitalWrite(pins[digit], LOW);
}

void loop() {

    int sensorValue  = analogRead(A0);
    int secondsensor = analogRead(A1);
    value            = sensorValue + secondsensor;

    String msg = "";
    msg += (String) sensorValue + " + " + secondsensor + " = " + value;
    Serial.println(msg);

    // LOW se enciende
    // HIGH se apaga
    break_number(value);

    showDigit(digits[0], 0);
    delay(mdelay);
    showDigit(digits[1], 1);
    delay(mdelay);
    showDigit(digits[2], 2);
    delay(mdelay);
    showDigit(digits[3], 3);
    delay(mdelay);
}
