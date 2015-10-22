//includes
#include "SPI.h"
#include "BallySoundTester.h"

SoundTester tester = SoundTester(0);
const byte indata_length = 100;

void setup()
{
  Serial.begin(115200);
  tester.setup();
}

void serialEvent()
{
  //define serial related data vars
  static char inData[indata_length]; // Allocate some space for the string
  static byte j = 0;
  static byte sound_id; //sound to play
  static byte command_id; //command to run

  //read serial data
  while (Serial.available() > 0) // data_loaded==false
  {
    char inChar = (char)Serial.read();
    inData[j] = inChar;
    j++;

    if (inChar == '\n')
    {
      //Serial.println(inData);
      //analyse the packet sent
      if (inData[0] == 'f')
      {
        tester.playNext(4000);
      }
      else if (inData[0] == 'b')
      {
        tester.playPrevious(4000);
      }
      else if (inData[0] == 'p')
      {
        //split the string and assign values
        char *token = NULL;
        token = strtok(inData, " ");

        if (token)
        {
          token = strtok(NULL, " ");
          sound_id = atoi(token);
          tester.play(sound_id);
        }

      }
    j=0;
    }
  }
}



void loop()
{
  tester.loop();
}
