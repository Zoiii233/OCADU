const int pinX = A0;
const int pinY = A1;
const int SW = 2;

int posX = 0;
int posY = 0;
int button;
int mapX = 0;
int mapY = 0;

const int speaker = 12;
//Tutorial: https://learn.adafruit.com/adafruit-arduino-lesson-10-making-sounds/playing-a-scale
//note pitch numbers
int tones[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440};
//            mid C  C#   D    D#   E    F    F#   G    G#   A

const int pinTouch = 7;
int touch;

void setup() {
  Serial.begin(115200); 
  
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  pinMode(SW, INPUT); 
  //Tutorial: https://www.brainy-bits.com/post/how-to-connect-and-use-analog-joystick-with-an-arduino
  //with out declaring it, the value would jump between 0 and 1
  digitalWrite(SW, HIGH);

  pinMode(pinTouch, INPUT);
}

void loop() {
  posX = analogRead(pinX);
  posY = analogRead(pinY);
  button = digitalRead(SW);
  //Tutorial: https://create.arduino.cc/projecthub/MisterBotBreak/how-to-use-a-joystick-with-serial-monitor-1f04f0 
  //the max value of joystick is 1023, normalize the value in to xy coordinates
  mapX = map(posX, 0, 1023, -100, 100); 
  mapY = map(posY, 0, 1023, -100, 100);
  
  touch = digitalRead(pinTouch);

  //My Code: when touch sensor is triggered, play the tone based on the position of the joystick
  //use 90 instead of 100, lower percision required
  if(touch == HIGH) {
    Serial.print("Touch: on");

    //Up
    if (mapX < 90 && mapX > -90 && mapY <= -90){
      tone(speaker, tones[0]);
      Serial.print(" | up ");
    }
    //Up right
    else if (mapX >= 90 && mapY <= -90){
      tone(speaker, tones[1]);
      Serial.print(" | up right ");
    }
    //Right
    else if (mapX >= 90 && mapY < 90 && mapY > -90){
      tone(speaker, tones[2]);
      Serial.print(" | right ");
    }
    //Down right
    else if (mapX >= 90 && mapY >= 90){
      tone(speaker, tones[3]);
      Serial.print(" | down right ");
    }
    //Down 
    else if (mapX < 90 && mapX > -90 && mapY >= 90){
      tone(speaker, tones[4]);
      Serial.print(" | down ");
    }
    //Down left
    else if (mapX <= -90 && mapY >= 90){
      tone(speaker, tones[5]);
      Serial.print(" | down left ");
    }
    //Left 
    else if (mapX <= -90 && mapY < 90 && mapY > -90){
      tone(speaker, tones[6]);
      Serial.print(" | left ");
    }    
    //Up left
    else if (mapX <= -90 && mapY <= -90){
      tone(speaker, tones[7]);
      Serial.print(" | up left ");
    }
    //Center
    else{
      //Button
      if(button == LOW){
        tone(speaker, tones[9]);
        Serial.print(" | button ");
      }
      //Center
      else{
        tone(speaker, tones[8]);
        Serial.print(" | center ");
      }
    } 
    

  } 
  else {
    noTone(speaker);
    Serial.print("Touch: off");
  }



  //Tutorial: https://create.arduino.cc/projecthub/MisterBotBreak/how-to-use-a-joystick-with-serial-monitor-1f04f0
  //an organized way to show values in the serial monitor
  Serial.print(" | X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.print(" | Button: ");
  Serial.println(button);

  delay(500);
  
}
