#pragma once
#ifdef ARDUINO
#include <Arduino.h>
#endif

class EmotiBitSerial
{
public:
#ifdef ARDUINO
    static bool parseSerialMessage(String message, String &typetag, String &payload);
    static void sendMessage(String typeTag, String payload = "");
    
#endif
    static const char MSG_START_CHAR = '@';
	static const char MSG_TERM_CHAR = '~';
	static const char PAYLOAD_DELIMITER = ',';
    struct Inputs
    {
        static const char RESET = 'R';
        static const char CONFIG_UPDATE = 'C';
        static const char DEBUG_MODE = 'D';
        static const char FACTORY_TEST_MODE = 'F';
    };
};