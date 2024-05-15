
int x=0, y=0;
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

#include <Servo.h>
int sem = 0;
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

int getFingerprintIDez();

// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// On Leonardo/Micro or others with hardware serial, use those! #0 is green wire, #1 is white
//Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial1);

void setup()  
{
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
   lcd.print("Fingerprint:");
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
   myservo.attach(4);  // attaches the servo on pin 9 to the servo object
    myservo.write(0);
  Serial.begin(9600);
  Serial.println("finger detect test");
pinMode(5, OUTPUT);
digitalWrite(5,LOW);
  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
   Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
   while (1);
  }
  Serial.println("Waiting for valid finger...");
  lcd.clear();
  lcd.setCursor(0, 0);
   lcd.print("Customer Id?");
   pinMode(A1, INPUT);
   pinMode(A0, OUTPUT);
   digitalWrite(A1, HIGH);
   digitalWrite(A0, HIGH);
    pinMode(A2, OUTPUT);
   digitalWrite(A2, HIGH);
     pinMode(A3, INPUT);
   pinMode(A5, INPUT);
   digitalWrite(A3, HIGH);
   digitalWrite(A5, HIGH);
}

void loop()                     // run over and over again
{
  //Serial.println(digitalRead(A3));
  if(Serial.available()>0)
  {
    char r = Serial.read();
    
    if(r=='B' )
    {
    
      lcd.setCursor(0, 0);
   lcd.print("Customer Iris Ok    ");
   delay(2000);
   lcd.setCursor(0, 0);
   lcd.print("                   ");
   lcd.setCursor(0, 1);
   lcd.print("Access Granted   ");
    Serial.println("servo");
    sem = 0;
   
    myservo.write(180);              // tell servo to go to position in variable 'pos'
  delay(3000);
  myservo.write(0); 
  lcd.setCursor(0, 1);
   lcd.print("              ");
  lcd.setCursor(0, 0);
   lcd.print("Customer Id?       ");
    }
    
      if(r=='A')
    {
     
      digitalWrite(5,HIGH);
      lcd.setCursor(0, 0);
   lcd.print("Unauthorized     ");
    lcd.setCursor(0, 1);
   lcd.print("Diff. Iris  ");
   digitalWrite(A2, LOW);
   delay(2000);
    digitalWrite(A2, HIGH);
   digitalWrite(5,LOW);
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Press Reset!  ");
    }
  
  }
  getFingerprintID();
  delay(50);            //don't ned to run this at full speed.
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
    //  Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
   //   Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
    //  Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
    //  Serial.println("Imaging error");
      return p;
    default:
     // Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
   //   Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
  //   Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
     // Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
    //  Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
     // Serial.println("Could not find fingerprint features");
      return p;
    default:
    //  Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
    
   // Serial.write('A');
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    //Serial.println("Communication error");
     Serial.write('B');
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    // Serial.write('C');
    return p;
  } else {
  //  Serial.println("Unknown error");
     Serial.write('D');
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
 
  if(finger.fingerID == 6)
  {
   digitalWrite(5,HIGH);
      lcd.setCursor(0, 0);
   lcd.print("Unauthorized ");
   
   digitalWrite(A2, LOW);
   delay(2000);
    digitalWrite(A2, HIGH);
   digitalWrite(5,LOW);
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Press Reset!  ");
  }
   if((finger.fingerID == 2 || finger.fingerID == 3 || finger.fingerID == 8 || finger.fingerID == 4) && sem == 0)
  {
    sem++;
     lcd.setCursor(0, 0);
   lcd.print("sending otp  ");
   digitalWrite(A0, LOW);
   digitalWrite(A2, LOW);
   delay(2000);
   digitalWrite(A0, HIGH);
    digitalWrite(A2, HIGH);
   lcd.setCursor(0, 0);
   lcd.print("enter otp   ");
      delay(2000);
   while(digitalRead(A1)==1 );
  
      lcd.setCursor(0, 0);
   lcd.print("Customer Ok    ");
   delay(2000);
   lcd.setCursor(0, 0);
   lcd.print("            ");
  }
  if(sem == 1)
  {
  
   lcd.setCursor(0, 1);
   lcd.print("Access Granted  ");
    Serial.println("servo");
    sem = 0;
   
    myservo.write(180);              // tell servo to go to position in variable 'pos'
  delay(3000);
  myservo.write(0); 
  lcd.setCursor(0, 1);
   lcd.print("              ");
  lcd.setCursor(0, 0);
   lcd.print("Customer Id?");
  }
}
