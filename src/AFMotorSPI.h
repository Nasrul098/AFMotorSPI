// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#ifndef _AFMotorSPI_h_
#define _AFMotorSPI_h_

#define AF_SPI_COMPATIBLE

#include <inttypes.h>
#include <avr/io.h>

// comment out this line to remove microstepping support
// for smaller library. Be sure to delete the old library objects!
#define MICROSTEPPING 1

#ifdef MICROSTEPPING
#define MICROSTEP 8
#endif

#ifdef AF_SPI_COMPATIBLE
//motor1 on timer1
#define MOTOR1_64KHZ _BV(CS10)  // no prescale
#define MOTOR1_8KHZ _BV(CS11)   // divide by 8
#define MOTOR1_1KHZ (_BV(CS11) | _BV(CS10)) // divide by 64
//motor2 on timer2
#define MOTOR2_64KHZ _BV(CS20)  // no prescale
#define MOTOR2_8KHZ _BV(CS21)   // divide by 8
#define MOTOR2_2KHZ (_BV(CS21) | _BV(CS20)) // divide by 32
#define MOTOR2_1KHZ _BV(CS22)  // divide by 64
#define MOTOR12_64KHZ _BV(CS10)  // no prescale
#define MOTOR12_8KHZ _BV(CS11)   // divide by 8
#else   //ifdef AF_SPI_COMPATIBLE
//motors 1 & 2 on timer2
#define MOTOR1_64KHZ _BV(CS20)  // no prescale
#define MOTOR1_8KHZ _BV(CS21)   // divide by 8
#define MOTOR1_2KHZ (_BV(CS21) | _BV(CS20)) // divide by 32
#define MOTOR1_1KHZ _BV(CS22)  // divide by 64
#define MOTOR2_64KHZ _BV(CS20)  // no prescale
#define MOTOR2_8KHZ _BV(CS21)   // divide by 8
#define MOTOR2_2KHZ (_BV(CS21) | _BV(CS20)) // divide by 32
#define MOTOR2_1KHZ _BV(CS22)  // divide by 64
#define MOTOR12_64KHZ _BV(CS20)  // no prescale
#define MOTOR12_8KHZ _BV(CS21)   // divide by 8
#define MOTOR12_2KHZ (_BV(CS21) | _BV(CS20)) // divide by 32
#define MOTOR12_1KHZ _BV(CS22)  // divide by 64
#endif	//ifdef AF_SPI_COMPATIBLE

//motors 3 & 4 on timer0
#define MOTOR3_64KHZ _BV(CS00)  // no prescale
#define MOTOR3_8KHZ _BV(CS01)   // divide by 8
#define MOTOR3_1KHZ (_BV(CS01) | _BV(CS00))  // divide by 64
#define MOTOR4_64KHZ _BV(CS00)  // no prescale
#define MOTOR4_8KHZ _BV(CS01)   // divide by 8
#define MOTOR4_1KHZ (_BV(CS01) | _BV(CS00))  // divide by 64
#define MOTOR34_64KHZ _BV(CS00)  // no prescale
#define MOTOR34_8KHZ _BV(CS01)   // divide by 8
#define MOTOR34_1KHZ (_BV(CS01) | _BV(CS00))  // divide by 64

#define MOTOR1_A 2
#define MOTOR1_B 3
#define MOTOR2_A 1
#define MOTOR2_B 4
#define MOTOR4_A 0
#define MOTOR4_B 6
#define MOTOR3_A 5
#define MOTOR3_B 7

#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3
#define RELEASE 4

#define SINGLE 1
#define DOUBLE 2
#define INTERLEAVE 3


/*
#define LATCH 4
#define LATCH_DDR DDRB
#define LATCH_PORT PORTB

#define CLK_PORT PORTD
#define CLK_DDR DDRD
#define CLK 4

#define ENABLE_PORT PORTD
#define ENABLE_DDR DDRD
#define ENABLE 7

#define SER 0
#define SER_DDR DDRB
#define SER_PORT PORTB
*/

// Arduino pin names
//You can change MOTORCLK, MOTORENABLE, MOTORDATA, MOTORLATCH values to change pin position
#define MOTORCLK 4
#define MOTORENABLE 7
#define MOTORDATA 8
//<patched_by_nsky>
#ifdef AF_SPI_COMPATIBLE
#define MOTORLATCH 2
#else   //ifdef AF_SPI_COMPATIBLE
#define MOTORLATCH 12
#endif	//ifdef AF_SPI_COMPATIBLE

//Warning! Changing PWM*_PIN value is not enough to switch pin position. Changes in source code are also necessary.
#ifdef AF_SPI_COMPATIBLE
#define PWM1_PIN 9
#else   //ifdef AF_SPI_COMPATIBLE
#define PWM1_PIN 11
#endif	//ifdef AF_SPI_COMPATIBLE
#define PWM2_PIN 3
#define PWM3_PIN 6
#define PWM4_PIN 5

#define PHASE_CORRECT 0x8
//</patched_by_nsky>

class AFMotorController
{
  public:
    AFMotorController(void);
    void enable(void);
    friend class AF_DCMotor;
    void latch_tx(void);
};

class AF_DCMotor
{
 public:
  AF_DCMotor(uint8_t motornum, uint8_t freq =  MOTOR34_8KHZ);
  void run(uint8_t);
  void setSpeed(uint8_t);

 private:
  uint8_t motornum, pwmfreq;
};

class AF_Stepper {
 public:
  AF_Stepper(uint16_t, uint8_t);
  void step(uint16_t steps, uint8_t dir,  uint8_t style = SINGLE);
  void setSpeed(uint16_t);
  uint8_t onestep(uint8_t dir, uint8_t style);
  void release(void);
  uint16_t revsteps; // # steps per revolution
  uint8_t steppernum;
  uint32_t usperstep, steppingcounter;
 private:
};

uint8_t getlatchstate(void);

#endif
