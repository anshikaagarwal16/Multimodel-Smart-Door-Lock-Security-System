 #include <Keypad.h>
#include <Password.h>
//initialize password to 1234
//you can change here for new password
 long otp;
  long otp1;
Password password=Password( "0000" );
int timesTosend=1;

int count2=0;
byte maxPasswordLength = 4;
byte currentPasswordLength = 0;
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
 int s=0;
//Define the keymap
char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
char buf1[16];
String strotp;
//char otp[4];
/*char keys[ROWS][COLS] = {
{'D','#','0','*'},
{'C','9','8','7'},
{'B','6','5','4'},
{'A','3','2','1'}
};*/
 
//// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = {6,7,8,9}; //connect to row pinouts
 
// Connect keypad COL0, COL1, COL2 and COL3 to these Arduino pins.
byte colPins[COLS] = {2,3,4,5}; //connect to column pinouts
 
// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
 
void setup(){
   Serial.begin(9600);
          delay(500);
    Serial.println("AT+CMGF=1"); //set GSM to text mode
            delay(500);
       pinMode(A0,INPUT);
    digitalWrite(A0,HIGH);
     pinMode(A1,OUTPUT);
   digitalWrite(A1,HIGH); //signal
 
}
 
void loop(){
 
 
 //Serial.println(otp1);
   char key = keypad.getKey();
   if (key != NO_KEY){
      delay(60);
      switch (key){
      
  //    case '*':  break;
      
     
      default: processNumberKey(key);
      }
   }
   if(digitalRead(A0)==0 && s==0)
   {
    s=1;
     otp = random(1, 4);
     otp1=otp;
        // Serial.print(" generated opt is: ");
   // Serial.println(otp);
    switch(otp)
    {
      case 1:
    password = Password( "2347" );
     Serial.println("AT+CMGF=1"); //set GSM to text mode
            delay(200);
            count2=0;
            while(count2<timesTosend){
          delay(1500);
           Serial.print("AT+CMGS=\"");
           Serial.print("8938054720");
           Serial.println("\"");
          while ( Serial.read()!='>');
          {
             Serial.println("Otp is: 2347 ");
              
         //SMS body
          delay(500);
           //SMS body
          
           Serial.write(0x1A);  // sends ctrl+z end of message
               Serial.write(0x0D);  // Carriage Return in Hex
           Serial.write(0x0A);  // Line feed in Hex
          
          //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
          delay(5000);
          }
          count2++;
            
          } 
    break;
      case 2:
      password = Password( "9571" );
       count2=0;
            while(count2<timesTosend){
          delay(1500);
           Serial.print("AT+CMGS=\"");
           Serial.print("8938054720");
           Serial.println("\"");
          while ( Serial.read()!='>');
          {
             Serial.println("Otp is: 9571 ");
              
         //SMS body
          delay(500);
           //SMS body
          
           Serial.write(0x1A);  // sends ctrl+z end of message
               Serial.write(0x0D);  // Carriage Return in Hex
           Serial.write(0x0A);  // Line feed in Hex
          
          //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
          delay(5000);
          }
          count2++;
            
          } 
    break;
     case 3:
    password = Password( "6698" );
    count2=0;
            while(count2<timesTosend){
          delay(1500);
           Serial.print("AT+CMGS=\"");
           Serial.print("8938054720");
           Serial.println("\"");
          while ( Serial.read()!='>');
          {
             Serial.println("Otp is: 6698 ");
              
         //SMS body
          delay(500);
           //SMS body
          
           Serial.write(0x1A);  // sends ctrl+z end of message
               Serial.write(0x0D);  // Carriage Return in Hex
           Serial.write(0x0A);  // Line feed in Hex
          
          //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
          delay(5000);
          }
          count2++;
            
          } 
    
    break;
      case 4:
      password = Password( "9989" );
       count2=0;
            while(count2<timesTosend){
          delay(1500);
           Serial.print("AT+CMGS=\"");
           Serial.print("8938054720");
           Serial.println("\"");
          while ( Serial.read()!='>');
          {
             Serial.println("Otp is: 9989 ");
              
         //SMS body
          delay(500);
           //SMS body
          
           Serial.write(0x1A);  // sends ctrl+z end of message
               Serial.write(0x0D);  // Carriage Return in Hex
           Serial.write(0x0A);  // Line feed in Hex
          
          //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
          delay(5000);
          }
          count2++;
            
          } 
    break;
    

    }
   }
   
}
 
void processNumberKey(char key) {
  
   Serial.print(key);

   currentPasswordLength++;
   password.append(key);
  
   if (currentPasswordLength == maxPasswordLength) {
    
      checkPassword();
   }
}

void checkPassword() {
   if (password.evaluate()){
      Serial.println("   OK.");
      s=0;
       digitalWrite(A1,LOW);
       delay(500);
      digitalWrite(A1,HIGH);
       
    
     
      
   } else {
     
      Serial.println(" Wrong password!");
     
    
     
      delay(3000);
    
    
   }
   resetPassword();
}

void resetPassword() {
   password.reset();
   currentPasswordLength = 0;
   
   
}
