//
//  Bally Sound tester.h
//  
//  Copyright 2015
//  Orange Cloud Software Ltd
//
//  Class to control a bally sound board and play the sounds through the control interface
//

#ifndef ____BallySoundTester__
#define ____BallySoundTester__

#include "Arduino.h"

#define DATA_BIT0_PIN       2
#define DATA_BIT1_PIN       3
#define DATA_BIT2_PIN       4
#define DATA_BIT3_PIN       5
#define DATA_BIT4_PIN       6

#define LATCH_PIN    7


class SoundTester
{
public:
    SoundTester(byte board_id);
    void setup();
    void reset();
    void playNext(int timer);
    void playPrevious(int timer);
    void play(byte sound_id);
    void stop();
    void setBinaryNumber(byte num);
    void setBinaryNumber256(byte num);
    void loop();
    
private:
    byte _id;
    byte _board_id;
    String _board_name;
    byte _max_range;
    byte _sound_id;
    boolean _update_flag;
    long _current_timer_store;
    long _previous_timer_store;
    int _timer;
   
    

    
    
};

#endif /* defined(____BallySoundTester__) */
