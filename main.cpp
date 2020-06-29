#include "mbed.h"

Serial pc(SERIAL_TX,SERIAL_RX);

DigitalInOut pingPin(PC_12);
/*
PA_13 (ping BL) works
PA_14 (ping L) works
PA_15 (Ping FL) works
PB_7 (PING B) works
PC_11 ( PING fr) works
PB_15 (Ping R) Works 
PB_7 (Ping BR) doesnt work , ganti ke PC_12 
*/

Timer tmr;
long microsecondsToInches(long microseconds);
float microsecondsToCentimeters(float microseconds);
float getDistance();

int main() {
    pc.printf ("TESTESTEST PROG  " ); 
    while (1) {
    wait(1) ; 
    pc.printf ("distance: %f ", getDistance() ); 
        
    }
}
float getDistance()
{
    
            // establish variables for duration of the ping,
        // and the distance result in inches and centimeters:
               // long duration2,duration, inches;
        float test1,test2;
        float mm; 

        // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
        // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
        pingPin.output();
        pingPin = 0;
        wait_us(2);
        pingPin = 1;
        wait_us(5);
        pingPin = 0;

        // The same pin is used to read the signal from the PING))): a HIGH
        // pulse whose duration is the time (in microseconds) from the sending
        // of the ping to the reception of its echo off of an object.
        pingPin.input();

        tmr.start();
        tmr.stop();
        test1= tmr.read_us();  
        // pulseIn
        while (!pingPin); // wait for high
        tmr.start();
        while (pingPin); // wait for low
        tmr.stop () ;
        test2 =tmr.read_us() - test1 ;
        
                // convert the time into a distance
       //inches = microsecondsToInches(test2);
        mm = microsecondsToCentimeters(test2);
        //pc.printf (" duration : %d " ,test2  ) ;
        //pc.printf("cm= %4d \n", cm);
        wait_ms(100);
        return (mm);//- 0.534550) ;
    }
    
long microsecondsToInches(long microseconds) {
    // According to Parallax's datasheet for the PING))), there are
    // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
    // second).  This gives the distance travelled by the ping, outbound
    // and return, so we divide by 2 to get the distance of the obstacle.
    // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
    return microseconds / 74 / 2;
}

float microsecondsToCentimeters(float microseconds) {
    // The speed of sound is 340 m/s or 29 microseconds per centimeter.
    // The ping travels out and back, so to find the distance of the
    // object we take half of the distance travelled.
    return ((microseconds/ 29 / 2)) ;/// 29 / 2; *0.034029
}
