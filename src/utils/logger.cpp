#include "utils/logger.h"

static void log_print(const char *color, const char *level, const char *msg)
{
    Serial.print(color);

    Serial.print("[");
    Serial.print(millis());
    Serial.print("] ");

    Serial.print("[");
    Serial.print(level);
    Serial.print("] ");

    Serial.println(msg);

    Serial.println(LOG_RESET);
}

void log_init()
{
    Serial.begin(115200);
}

void log_info(const char *msg)
{
    log_print(LOG_GREEN, "INFO", msg);
}

void log_debug(const char *msg)
{
    log_print(LOG_BLUE, "DEBUG", msg);
}

void log_warn(const char *msg)
{
    log_print(LOG_YELLOW, "WARN", msg);
}

void log_error(const char *msg)
{
    log_print(LOG_RED, "ERROR", msg);
}

void log_fatal(const char *msg)
{
    log_print(LOG_BG_RED, "FATAL", msg);
}

void log_panic(const char *msg)
{
    log_print(LOG_BG_RED, "PANIC", msg);
}
