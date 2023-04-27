#include <Servo.h> // Including the servo library
#include <LiquidCrystal.h> // Including the LCD library

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Initializing the LCD pins
Servo myservo; // Creatinging a servo object

int gasPin = A0; // Defining the gas sensor pin
int ledPin = 13; // Defining the LED pin
int buzzerPin = 10; // Defining the buzzer pin
int gasValue; // Defining the gas value variable
int threshold = 900; // Defining the gas threshold level

void setup() {
  pinMode(ledPin, OUTPUT); // Setting the LED pin as output
  pinMode(buzzerPin, OUTPUT); // Setting the buzzer pin as output
  myservo.attach(9); // Attaching the servo to pin 9
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
  lcd.print("Gas Leakage"); // Printing the text on the first row of the LCD
  lcd.setCursor(0, 1); // Moves the cursor to the second row of the LCD
  lcd.print("Detection System"); // Printing the text on the second row of the LCD
  delay(2000); // Waiting for 2 seconds
  lcd.clear(); // Clearing the LCD screen
  Serial.begin(9600);
}

void loop() {
  gasValue = analogRead(gasPin); // Reading the gas sensor value
  if (gasValue > 800) { // If the gas value is higher than the threshold level
    digitalWrite(ledPin, HIGH); // Turn ON the LED
    digitalWrite(buzzerPin, HIGH); // Turn ON the buzzer
    myservo.write(90); // Rotates the servo to 90 degrees
    lcd.setCursor(0, 0); // Moves the cursor to the first row of the LCD
    lcd.print("Gas Leakage High!"); // Printing the text on the first row of the LCD
    lcd.setCursor(0, 1); // Moves the cursor to the second row of the LCD
    lcd.print("Turn off gas!"); // Printing the text on the second row of the LCD
    tone(buzzerPin, 1000); // Setting up the buzzer
    delay(5000); // Waiting for 5 seconds
    lcd.clear();
  } 
  
  else if (gasValue > 664 && gasValue < 801 ) { // If the gas value is lower than the threshold level
    digitalWrite(ledPin, LOW); // Turning OFF the LED
    digitalWrite(buzzerPin, LOW); // Turning OFF the buzzer
    myservo.write(0); // Rotating the servo to 0 degrees
    lcd.setCursor(0, 0); // Moving the cursor to the firstrow of the LCD
	lcd.print("Minimal Gas Leak"); // Printing the text on the first row of the LCD
	lcd.setCursor(0, 1); // Moving the cursor to the second row of the LCD
	lcd.print("System OK!"); // Printing the text on the second row of the LCD
    delay(5000); // Waiting 5 seconds
    tone(buzzerPin, 600); // Toning down the buzzer
    lcd.clear();
}
  
  else if (gasValue < 665) { // If the gas value is lower than the threshold level
    digitalWrite(ledPin, LOW); // Turning OFF the LED
    digitalWrite(buzzerPin, LOW); // Turning OFF the buzzer
    myservo.write(0); // Rotating the servo to 0 degrees
    lcd.setCursor(0, 0); // Moving the cursor to the firstrow of the LCD
	lcd.print("No Gas Leak"); // Printing the text on the first row of the LCD
	lcd.setCursor(0, 1); // Moving the cursor to the second row of the LCD
	lcd.print("System OK!"); // Printing the text on the second row of the LCD
    delay(5000); // Waiting 5 seconds
    noTone(buzzerPin); // Toning down the buzzer
    lcd.clear();
}
  Serial.println();
  Serial.println("Current Gas Reading: ");
  Serial.println(gasValue);
  Serial.println();
  Serial.println("*** *** *** *** ***");
}


