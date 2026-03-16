#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

inline unsigned long _mock_millis = 0;
inline unsigned long millis() { return _mock_millis; }
inline void mock_set_millis(unsigned long v) { _mock_millis = v; }
inline void delay(unsigned long) {}

#define HIGH 1
#define LOW 0
#define INPUT 0
#define OUTPUT 1

inline int _pin_state[40] = {0};
inline void pinMode(uint8_t, uint8_t) {}
inline void digitalWrite(uint8_t pin, int val) { _pin_state[pin] = val; }
inline int digitalRead(uint8_t pin) { return _pin_state[pin]; }
inline void mock_set_pin(uint8_t pin, int val) { _pin_state[pin] = val; }

struct _Serial_t
{
    void begin(int) {}
    void print(const char *s) { printf("%s", s); }
    void println(const char *s) { printf("%s\n", s); }
    void print(unsigned long v) { printf("%lu", v); }
    void println() { printf("\n"); }
};
inline _Serial_t Serial;

#include <string>
using String = std::string;