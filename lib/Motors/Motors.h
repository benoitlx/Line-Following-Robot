#ifndef MOTORS_H
#define MOTORS_H

#define MAXPWM 255 // can be set up to 255

class Motors {
  public:
    Motors(int pinSpeed, int pin1, int pin2);

    int speedPin;
    int dir1Pin;
    int dir2Pin;

    void setMotorSpeed(int speed); // select a motor and set a speed
};



#endif // !MOTORS_H
