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
};