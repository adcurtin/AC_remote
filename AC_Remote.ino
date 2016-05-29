#include "ac_remote.h"


String cmd = "";
char inbyte = 0;
int i = 0;
int IRPin = 13;
char buf[16];


void setup(){
  pinMode(IRPin, OUTPUT);
  Serial.begin(9600); 
  Serial.println("command format: command#");
  Serial.print("Enter command: ");
}

void loop(){
  if(Serial.available() > 0){ //read data into line1 and line 2
    inbyte = Serial.read();
    if(inbyte == '\n'){ //this catches \r\n
      while(Serial.available() == 0);
      inbyte = Serial.read();
    }
    Serial.print(inbyte);
    //if(inbyte == '@'){ //FINDME

      cmd = "";
      cmd.concat(inbyte);
      //delay(100);
      while(/*Serial.available() > 0 &&*/ inbyte != '#' && inbyte !='\r'){ //add @?
        while(Serial.available() == 0);
        inbyte = Serial.read();
        Serial.print(inbyte);
        cmd.concat(inbyte); //empty buffer into line1
      }
      Serial.println("");
      if(inbyte=='#' || inbyte=='\r') cmd = cmd.substring(0,cmd.length()-1);
      if(cmd[cmd.length()-1] == '\n') cmd = cmd.substring(0,cmd.length()-1); //this catches \n\r
      //Serial.println(cmd);
      if(cmd == "power"){
        SendCode(AC_power, 72); 
        Serial.print("Enter command: ");
      }else if(cmd == "sleep"){
        SendCode(AC_sleep, 72);
        Serial.print("Enter command: ");
      }else if(cmd == "swing"){
        SendCode(AC_swing, 72);
        Serial.print("Enter command: ");
      }else if(cmd == "mode"){
        SendCode(AC_mode, 72);
        Serial.print("Enter command: ");
      }else if(cmd == "timer"){
        SendCode(AC_timer, 72);
        Serial.print("Enter command: ");
      }else if(cmd == "fan"){
        SendCode(AC_fan, 72);
        Serial.print("Enter command: ");
      }else if(cmd == "up"){
        SendCode(AC_up, 68);
        Serial.print("Enter command: ");
      }else if(cmd == "down"){
        SendCode(AC_down, 76);
        Serial.print("Enter command: ");
      }else if(cmd == "degrees"){
        SendCode(AC_degrees, 72);
        Serial.print("Enter command: ");
      }else if(cmd == "exit"){
        Serial.write(4);
      }else{
        Serial.println(cmd);
        Serial.println("Available commands: ");
        Serial.println("\tpower");
        Serial.println("\ttimer");
        Serial.println("\tswing");
        Serial.println("\tmode");
        Serial.println("\tup");
        Serial.println("\tdown");
        Serial.println("\tsleep");
        Serial.println("\tdegrees");
        Serial.println("\texit");

        Serial.print("Enter command: ");
      }
    }
  //}
}



// This procedure sends a 38KHz pulse to the IRledPin
// for a certain # of microseconds. We'll use this whenever we need to send codes
void pulseIR(long microsecs) {
  // we'll count down from the number of microseconds we are told to wait

  cli();  // this turns off any background interrupts

  while (microsecs > 0) {
    // 38 kHz is about 13 microseconds high and 13 microseconds low
   digitalWrite(IRPin, HIGH);  // this takes about 3 microseconds to happen
   delayMicroseconds(10);         // hang out for 10 microseconds
   digitalWrite(IRPin, LOW);   // this also takes about 3 microseconds
   delayMicroseconds(10);         // hang out for 10 microseconds

   // so 26 microseconds altogether
   microsecs -= 26;
  }

  sei();  // this turns them back on
}


void SendCode(int code[], int length) {
  for(i=0;i<length;i+=2){
      pulseIR(code[i]*10);
      delayMicroseconds(code[i+1]*10);
  }
}
