          // This sketch will send out a Nikon D50 trigger signal (probably works with most Nikons)
// See the full tutorial at http://www.ladyada.net/learn/sensors/ir.html
// this code is public domain, please enjoy!
 
int IRledPin =  13;    // LED connected to digital pin 13
int boardNum = 1;

 
// The setup() method runs once, when the sketch starts
 
void setup()   {                
  // initialize the IR digital pin as an output:
  pinMode(IRledPin, OUTPUT);      
 
  Serial.begin(9600);
}
 
void loop()                     
{
  Serial.println("Sending IR signal");
 
  SendNikonCode();

  while(1){
    
  }
  
//  delay(4*1000);  // wait one minute (60 seconds * 1000 milliseconds)
}
 
// This procedure sends a 38KHz pulse to the IRledPin 
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait
 
  cli();  // this turns off any background interrupts
 
  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
   digitalWrite(IRledPin, HIGH);  // this takes about 3 microseconds to happen
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
   digitalWrite(IRledPin, LOW);   // this also takes about 3 microseconds
   delayMicroseconds(10);         // hang out for 10 microseconds, you can also change this to 9 if its not working
 
   // so 26 microseconds altogether
   microsecs -= 26;
  }
 
  sei();  // this turns them back on
}
 
void SendNikonCode() {
  int boardPause = boardNum * 1500;
  // each board number is pulseIR(board number*1500) 4 times and delay(6) between each one
  
  pulseIR(boardPause);
  delay(6);
  pulseIR(boardPause);
  delay(6);
  pulseIR(boardPause);
  delay(6);
  pulseIR(boardPause);
  
  // we may need to change this delay so that there's enough time for the receiver to register a hit and stop receiving
  // The delay is so we can have insurance to make sure that the signal is actually sent
  // BUT we want to also add the same or larger delay to the receiver so that if it gets a both signals, it doesn't register two hits
  delay(55);
  
  pulseIR(boardPause);
  delay(6);
  pulseIR(boardPause);
  delay(6);
  pulseIR(boardPause);
  delay(6);
  pulseIR(boardPause);
  
}
