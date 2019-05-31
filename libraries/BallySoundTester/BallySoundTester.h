//
//  Bally Sound tester.h
//  
//  Copyright 2018
//  Orange Cloud Software Ltd
//
//  Class to control various Bally pinball sound boards and play the sounds through the control interface
//

#ifndef ____BallySoundTester__
#define ____BallySoundTester__

#include "Arduino.h"

//define hardware names :)
#define CSB 0
#define CSB6 0
#define COMPUTER_SOUND_BOARD 0
#define COMPUTER_SOUND_BOARD_6 0
#define CSB7 1
#define COMPUTER_SOUND_BOARD_7 1
#define SANDT 2
#define SQUAWK_AND_TALK 2
#define CS 3
#define CHEAP_SQUEAK 3
#define NASTY 3
#define TURBO_CHEAP_SQUEAK 4
#define TCS 4
#define SOUNDS_DELUXE 5
#define SOUNDS_GOOD 5
#define SD 5
#define BIG_68000_MONSTER 5


//define port bits
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
    void setBinaryNumberMod256(byte num);
    void setBinaryNumberOrig256(byte num);
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
