#include "EmotiBitSerial.h"

#ifdef ARDUINO
bool EmotiBitSerial::parseSerialMessage(String message, String &typetag, String &payload)
{
	if(message.charAt(0) == MSG_START_CHAR)
	{
		int payloadDelimiterIndex = message.indexOf(PAYLOAD_DELIMITER);
		int messageDelimiterIndex = message.indexOf(MSG_TERM_CHAR);
		if (payloadDelimiterIndex > 0 && messageDelimiterIndex > 0)
		{
			typetag = message.substring(1, payloadDelimiterIndex);
			payload = message.substring(payloadDelimiterIndex + 1, messageDelimiterIndex);
			// ToDo: Add a debug pre-processor guard instead of comments
			//Serial.print("typetag: ");Serial.println(typetag);
			//Serial.print("payload: ");Serial.println(payload);
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}

void EmotiBitSerial::sendMessage(String typeTag, String payload)
{
    String msg = MSG_START_CHAR + typeTag + PAYLOAD_DELIMITER + payload + MSG_TERM_CHAR;
    Serial.println(msg);
}
#endif