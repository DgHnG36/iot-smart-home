#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include <iostream>

#define LOG_RESET "\x1B[0m"

#define LOG_GREEN "\x1B[32m"
#define LOG_BLUE "\x1B[34m"
#define LOG_YELLOW "\x1B[33m"
#define LOG_RED "\x1B[31m"
#define LOG_BG_RED "\x1B[41m"

void log_init();

void log_info(const char *msg);
void log_debug(const char *msg);
void log_warn(const char *msg);
void log_error(const char *msg);
void log_fatal(const char *msg);
void log_panic(const char *msg);

#endif // LOGGER_H