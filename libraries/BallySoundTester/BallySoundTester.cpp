//
//  Bally Sound tester.cpp
//
//  Copyright 2018
//  Orange Cloud Software Ltd
//
//  Class to control various Bally pinball sound boards and play the sounds through the control interface
//

#include "BallySoundTester.h"

int _data_bits[] = {DATA_BIT0_PIN,DATA_BIT1_PIN,DATA_BIT2_PIN,DATA_BIT3_PIN,DATA_BIT4_PIN};


//constructor
SoundTester::SoundTester(byte board_id)
{
    
    _board_id = board_id;
    
    
    if (_board_id==0)
    {
        _max_range = 31;
        _board_name = "AS-2518-51 Computer (6 Digit Display)";
    }
    else if (_board_id ==1)
    {
        _max_range = 255;
        _board_name = "AS-2518-61 Computer (7 Digit Display)";
    }
    else if (_board_id ==2)
    {
        _max_range = 255;
        _board_name = "AS-2518-61 Squawk & Talk";
    }
    else if (_board_id ==3)
    {
        _max_range = 255;
        _board_name = "A080-91603-B000 Cheap Squeak";
    }
    else if (_board_id ==4)
    {
        _max_range = 255;
        _board_name = "A080-91855-E000 Turbo Cheap Squeak";
    }
    else if (_board_id ==5)
    {
        _max_range = 255;
        _board_name = "A080-91864-C000 Sounds Deluxe";
    }
    else
    {
         _max_range = 255;
         _board_name = "Not yet supported";
    }
    
}

void SoundTester::setup()
{
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(DATA_BIT0_PIN, OUTPUT);
    pinMode(DATA_BIT1_PIN, OUTPUT);
    pinMode(DATA_BIT2_PIN, OUTPUT);
    pinMode(DATA_BIT3_PIN, OUTPUT);
    pinMode(DATA_BIT4_PIN, OUTPUT);
    
    
    //set all port bits high - off
    for (int i=0;i<5;i++)
    {
        digitalWrite(_data_bits[i],HIGH);
    }
    
    digitalWrite(LATCH_PIN,HIGH); //set latch/interupt HIGH - off -activation is 40us LOw pulse
    
    while (!Serial) //wait for serial log setup
    {
        
    }
    
    reset();
    
    Serial.println("Bally Sound Board Tester v1.0 - OCS Ltd");
    Serial.println("Board is "+String(_board_name)+". Latch Pin is:"+ String(LATCH_PIN));
    
}

void SoundTester::reset()
{
    //load a value of 0 into the sound card
    for (int i=0;i<5;i++)
    {
        digitalWrite(_data_bits[i],LOW);
    }
    
    digitalWrite(LATCH_PIN,LOW);
    delayMicroseconds(40);
    digitalWrite(LATCH_PIN,HIGH); //latch new data to the sound card on the rising edge
    
    
}


void SoundTester::playNext(int timer)
{
    _id = 1;
    _timer=timer;
    _current_timer_store = millis();

    if((_current_timer_store - _previous_timer_store) > _timer) //is it time to update?
    {
        // save the last time a sound command was sent
        _previous_timer_store = _current_timer_store;
        
        if (_board_id==0)
        {
            setBinaryNumber(_sound_id);
        }
        else if (_board_id==1 || _board_id==2)
        {
            setBinaryNumberMod256(_sound_id);
        }
        else if (_board_id>2)
        {
            setBinaryNumberOrig256(_sound_id);
        }

        Serial.println("Playing Sound ID:"+String(_sound_id));
        _sound_id++;
        if (_sound_id>_max_range)
        {
            _sound_id=0;
        }
        Serial.println("Next Sound ID:"+String(_sound_id));

    }
    
}


void SoundTester::playPrevious(int timer)
{
    _id = 2;
    _timer=timer;
    _current_timer_store = millis();
    
    if((_current_timer_store - _previous_timer_store) > _timer) //is it time to update?
    {
        // save the last time a sound command was sent
        _previous_timer_store = _current_timer_store;
        
        if (_board_id==0)
        {
            setBinaryNumber(_sound_id);
        }
        else if (_board_id==1 || _board_id==2)
        {
            setBinaryNumberMod256(_sound_id);
        }
        else if (_board_id>2)
        {
            setBinaryNumberOrig256(_sound_id);
        }
        
        Serial.println("Playing Sound ID:"+String(_sound_id));
        _sound_id--;
        if (_sound_id<0)
        {
            _sound_id=_max_range;
        }
        Serial.println("Previous Sound ID:"+String(_sound_id));
        
    }
    
}

void SoundTester::play(byte sound_id)
{
    stop();
    _sound_id=sound_id;
    
    if (_board_id==0)
    {
        setBinaryNumber(_sound_id);
    }
    else if (_board_id==1 || _board_id==2)
    {
        setBinaryNumberMod256(_sound_id);
    }
    else if (_board_id>2)
    {
        setBinaryNumberOrig256(_sound_id);
    }
    
    Serial.println("Playing Sound ID:"+String(_sound_id));
    _sound_id++;
    if (_sound_id>_max_range)
    {
        _sound_id=0;
    }
    Serial.println("Next Sound ID:"+String(_sound_id));
}


void SoundTester::stop()
{
    _id = 0;
}


void SoundTester::setBinaryNumber(byte num)
{
    //Serial.print("num:"+String(num)+"= binary:");
    for (int i=0;i<5;i++)
    {
        byte value = bitRead(num,i);
        digitalWrite(_data_bits[i],value);
        //Serial.print(String(value));
    }
    //Serial.println();
    
    digitalWrite(LATCH_PIN,LOW);
    delayMicroseconds(40);
    digitalWrite(LATCH_PIN,HIGH); //latch new data to the sound card on the rising edge
}


void SoundTester::setBinaryNumberMod256(byte num)
{
    //285 us length for update - according to bally tech docs
    //Alternative - 4409us length for update - 37μs + 15μs + 125μs + 4,232μs
    
    digitalWrite(LATCH_PIN,LOW); //latch new data to the sound card on the rising edge
    delayMicroseconds(37); //40
    digitalWrite(LATCH_PIN,HIGH);
    delayMicroseconds(15); //22
    //Serial.print("num:"+String(num)+"= binary:");
    for (int i=0;i<4;i++) //least significant 4 bits
    {
        byte value = bitRead(num,i);
        digitalWrite(_data_bits[i],value);
        //Serial.print(String(value));
    }
    delayMicroseconds(125); //145
    
    for (int i=0;i<4;i++) //most significant 4 bits
    {
        byte value = bitRead(num,i+4);
        digitalWrite(_data_bits[i],value);
        //Serial.print(String(value));
    }
    delayMicroseconds(4232); //78
    
    //Serial.println();
    
    }


void SoundTester::setBinaryNumberOrig256(byte num)
{
    //285 us length for update - according to bally tech docs
    
    digitalWrite(LATCH_PIN,LOW); //latch new data to the sound card on the rising edge
    delayMicroseconds(40);
    digitalWrite(LATCH_PIN,HIGH);
    delayMicroseconds(22);
    //Serial.print("num:"+String(num)+"= binary:");
    for (int i=0;i<4;i++) //least significant 4 bits
    {
        byte value = bitRead(num,i);
        digitalWrite(_data_bits[i],value);
        //Serial.print(String(value));
    }
    delayMicroseconds(145);
    
    for (int i=0;i<4;i++) //most significant 4 bits
    {
        byte value = bitRead(num,i+4);
        digitalWrite(_data_bits[i],value);
        //Serial.print(String(value));
    }
    delayMicroseconds(78);
    
    //Serial.println();
    
}


void SoundTester::loop()
{
    if (_id == 1)
    {
        playNext(_timer);
    }
    else if (_id ==2)
    {
        playPrevious(_timer);
    }
    else
    {
        return;
    }

}
