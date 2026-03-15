#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

#define LOG_RESET "\033[0m"

#define LOG_GREEN "\033[32m"
#define LOG_BLUE "\033[34m"
#define LOG_YELLOW "\033[33m"
#define LOG_RED "\033[31m"
#define LOG_BG_RED "\033[41m"

void log_init();

void log_info(const char *msg);
void log_debug(const char *msg);
void log_warn(const char *msg);
void log_error(const char *msg);
void log_fatal(const char *msg);
void log_panic(const char *msg);

#endif // LOGGER_H