#include <Keypad.h> // the library for the 4x4 keypad
#include <LiquidCrystal_I2C.h> // the library for the i2c 1602 lcd
#include <Servo.h> // the library to control the servo motor
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 4); // gets the lcd 
Servo servo;

#define Password_Length 5 // the length of the password, if the password is 4 digits long set this to 5
int Position = 0; // position of the servo
int Last_Position = 0;
char Particular[Password_Length]; // the password length 
char Specific[Password_Length] = "1234"; // the password which is called specific in the code, change this to anything you want with the numbers 0-9 and the letters A-D
byte Particular_Count = 0, Specific_Count = 0; // counts the amount of digits and and checks to see if the password is correct
char Key;
const byte ROWS = 4; // the amount of rows on the keypad
const byte COLS = 4; // the amount of columns on the keypad
char keys[ROWS][COLS] = { // sets the rows and columns
  {'1','2','3','A'}, 
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
bool SmartDoor = true; // the servo 
// the pins to plug the keypad into
byte rowPins[ROWS] = {6, 7, 8, 9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {2, 3, 4, 5}; //connect to the column pinouts of the keypad
Keypad myKeypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); // gets the data from the keypad

// locked character
byte Locked[8] = { 
  B01110,
  B10001,
  B10001,
  B11111,
  B11011,
  B11011,
  B11011,
  B11111
};
// open character
byte Opened[8] = {
  B01110,
  B00001,
  B00001,
  B11111,
  B11011,
  B11011,
  B11011,
  B11111
};

SoftwareSerial mySerial(12, 13); // RX, TX
String readString;

bool locked = false;    // Flag to track the lock state

void setup() {
  servo.attach(11); // attaches the servo to pin 11
  ServoClose(); // closes the servo when you say this function
  lcd.init(); // initializes the lcd 
  lcd.backlight(); // turns on the backlight
  lcd.setCursor(0, 0); // sets the cursor on the lcd
  lcd.print("Greetings !"); // prints the text/character
  lcd.setCursor(0, 1); // sets the cursor on the lcd
  lcd.print("Arduino Lock!!!"); // prints text
  delay(4000); // waits 4 seconds
  lcd.clear(); // clears the lcd display
  mySerial.begin(9600);
}

void loop() {
  func_finger();
  func_LCD();
}

void func_LCD() {
  if (SmartDoor == 0) // opens the smart door
  {
    Key = myKeypad.getKey(); // the word key = myKeypad which gets the value
    if (Key == '#') // when the '#' key is pressed
    {
      lcd.clear(); // clears the lcd display
      ServoClose(); // closes the servo motor
      lcd.setCursor(2, 0); // sets the cursor on the lcd
      lcd.print("Door Closed"); // prints the text to the lcd
      lcd.createChar(0, Locked); // prints the locked character 
      lcd.setCursor(14, 0); // sets the cursor on the lcd
      lcd.write(0); // prints the first character when you are on the door closed page
      delay(3000); // waits 3 seconds
      SmartDoor = 1; // closes the door
    }
  } else {
    Open(); // keeps the door open
  }
}

void clearData() {
  while (Particular_Count != 0) {
    Particular[Particular_Count--] = 0;
  }
  Last_Position = 0; // Reset the position of the last entered digit
}

void ServoOpen() // opens the servo
{
  for (Position = 0; Position <= 180; Position += 5) { // moves from 0 to 180 degrees
    servo.write(Position); // moves to the position
    delay(15); // waits 15 milliseconds
  }
}

void ServoClose() // closes the servo
{
  for (Position = 180; Position >= 0; Position -= 5) { // moves from position 180 to 0 degrees
    servo.write(Position); // moves to the position
    delay(15); // waits 15 milliseconds
  }
}

void Open() // function declarations
{
  lcd.setCursor(1, 0); // sets the cursor on the lcd
  lcd.print("Enter Password:"); // prints the text

  Key = myKeypad.getKey();
  if (Key == 'C') {
    if (Particular_Count > 0) {
      Particular_Count--;
      lcd.setCursor(Particular_Count, 1);
      lcd.print(" ");
    }
    return; // Exit the function after handling 'C' key
  }  
  if (Key) {
    Particular[Particular_Count] = Key; 
    lcd.setCursor(Particular_Count, 1); // sets the cursor on the lcd
    lcd.print("*"); // prints '*' instead of the password
    Particular_Count++; // counts the length of the password
  }

  if (Particular_Count == Password_Length - 1) // gets the length of the password 
  {
    Particular[Particular_Count] = '\0'; // Add null terminator to make it a proper string
    if (!strcmp(Particular, Specific)) // counts the length and checks to see if the password is correct
    {
      lcd.clear();
      ServoOpen(); // moves the servo 180 degrees
      lcd.setCursor(2, 0); // sets the cursor on the lcd
      lcd.print("Door Opened");
      lcd.createChar(1, Opened);
      lcd.setCursor(14, 0); // sets the cursor on the lcd
      lcd.write(1);
      lcd.setCursor(0, 1); // sets the cursor on the lcd
      lcd.print("Press # to Close");
      SmartDoor = 0;
    } else {
      lcd.clear();
      lcd.setCursor(0, 0); // sets the cursor on the lcd
      lcd.print("Wrong Password"); // prints the text/character
      lcd.setCursor(0, 1);
      lcd.print("Try Again In");
      for (int i = 10; i > 0; i--) {
        lcd.setCursor(13, 1);
        lcd.print(i < 10 ? "0" : "");
        lcd.print(i);
        delay(1000);
      }
      lcd.clear();
      SmartDoor = 1; // closes the smart door
    }
    clearData(); // clears the data
  }
}

void func_finger() {
  while (mySerial.available() > 0) {
    delay(10);
    char c = mySerial.read();
    if (c == '#') {
      break;
    }
    readString += c;
  }
  
  if (readString.length() > 0) {
    mySerial.println(readString);  // Print the received string
    
    if (readString == "f success") {
      if (locked) {
        ServoClose();  // Move the servo to close the door if already locked
        locked = false;       // Update the lock state
      } else {
        ServoOpen(); // Move the servo to open the door if unlocked
        locked = true;         // Update the lock state
      }
    }
    
    readString = "";
  }
}
