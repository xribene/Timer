// Flash three LEDs at different rates (frequencies) and different duty cycles 
// using Simon Monk's Timer library

#include "Timer.h"   //http://github.com/JChristensen/Timer             
const int LED1 = 8;  //connect one LED to this pin (with appropriate current-limiting resistor of course)   
const int LED2 = 9; //connect another LED to this pin (don't forget the resistor)
const int LED3 = 13;
float dt1 = 0.1; // set the duty_cycle for LED1
float dt2 = 0.8; // set the duty_cycle for LED2
int freq1=1; // set frequency of the first oscillation (LED1) at 1Hz
int freq2=2; // set frequency of the first oscillation (LED1) at 1Hz
const unsigned long timeON_1 = dt1*1000/freq1; // timeON = the amount of time in the period that LED1 will be on
const unsigned long timeOFF_1 = (1-dt1)*1000/freq1; // timeOFF = the amount of time in the period that LED1 will be off
const unsigned long timeON_2 = dt2*1000/freq2;
const unsigned long timeOFF_2 = (1-dt2)*1000/freq2;
const unsigned long PERIOD_3 = 1000;
Timer t; //instantiate the timer object
int repeatCount=-1; // the number of full cycles ,set the value to -1 for infinite repetition
// if repeatCount=-1 then it can be ommited (see event2 below)
int event1,event2,event3;
void setup()
{
    Serial.begin(9600);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    event1=t.oscillate(LED1, timeON_1 ,HIGH,repeatCount,timeOFF_1);
    event2=t.oscillate(LED2, timeON_2, HIGH,timeOFF_2); 
    event3=t.oscillate(LED3, PERIOD_3, HIGH);// in this case timeON=timeOFF=PERIOD3, so duty_cycle=0.5
    t.after(10000, doAfter); // after 10 secs of blinking run doAfter()

}

void loop()
{
    t.update();
}

void doAfter()
{  
    t.stop(event1); // stop event1
    t.stop(event2);// stop event2
    t.stop(event3);// stop event3
}

