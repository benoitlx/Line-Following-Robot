#ifndef MOTORS_H_
#define MOTORS_H_

#define MAXPWM 255 // can be set up to 255

class Motors {
  public:
    Motors(int pinSpeed, int pin1, int pin2);

    int speedPin;
    int dir1Pin;
    int dir2Pin;

    void setMotorSpeed(int speed); // select a motor and set a speed
};



#endif // !MOTORS_H_
