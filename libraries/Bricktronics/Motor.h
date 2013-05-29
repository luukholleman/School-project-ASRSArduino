/* Bricktronics Library -- Buttons.h
Copyright (C) 2012 Adam Wolf, Matthew Beckler, John Baichtal

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef Motor_h
#define Motor_h

#include "Bricktronics.h"

class Bricktronics;

class Motor {
public:
    Motor(Bricktronics* brick,
          uint8_t dir_pin,
          uint8_t pwm_pin,
          uint8_t en_pin,
          uint8_t tach_a_pin,
          uint8_t tach_b_pin);

    Motor(Bricktronics* brick,
          uint8_t port);

    Motor(Bricktronics* brick);

    uint8_t dir_pin;
    uint8_t pwm_pin;
    uint8_t en_pin;
    uint8_t tach_a_pin;
    uint8_t tach_b_pin;

    Bricktronics* brick;
    Encoder *encoder;

    bool enabled;
    bool direction;
    uint16_t speed;

    void begin(void);
    void stop(void);
    void set_speed(int16_t);
    void set_port(uint8_t);
    int16_t get_speed(void);

    int32_t get_pos(void);
    void set_pos(int32_t);

private:

};

class PIDMotor: public Motor {
public:
    PIDMotor(Bricktronics* brick,
             uint8_t dir_pin,
             uint8_t pwm_pin,
             uint8_t en_pin,
             uint8_t tach_a_pin,
             uint8_t tach_b_pin) : Motor(brick,
                                               dir_pin,
                                               en_pin,
                                               pwm_pin,
                                               tach_a_pin,
                                               tach_b_pin)
    {
        mKP = .8;
        mKD = 1;
        mKI = 0.003;
    };


    PIDMotor(Bricktronics* brick,
             uint8_t port) : Motor(brick, port)
    {
        mKP = .8;
        mKD = 1;
        mKI = 0.003;
    };

    PIDMotor(Bricktronics* brick);

    void go_to_pos(int16_t);
    void update(void);

    int32_t last_error;
    int32_t sum_error;
    int16_t destination_pos;

    float mKP;
    float mKD;
    float mKI;

private:
};

#endif

