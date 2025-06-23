/**************************************************************************/
/*!
    @file     main.cpp
    @author   Joseph Jacobson (EmotiBit)

    @mainpage Data tester for EmotiBit to generate test data packets

    @section intro_sec Introduction

    This is a program to generate the test data packets from EmotiBitPacket, and can be used to compare with expected outputs from the EmotiBit, generating an exe that produces a CSV file with the test data packets.

    EmotiBit invests time and resources providing this open source code,
    please support EmotiBit and open-source hardware by purchasing
    products from EmotiBit!

    @section author Author

    Written by Joseph Jacobson for EmotiBit.

    @section  HISTORY

    v1.0  - First release

    @section license License

    BSD license, all text here must be included in any redistribution
*/
/**************************************************************************/

#ifdef ARDUINO
#else

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "EmotiBitPacket.h"

//! @brief Helper operator to compare EmotiBit::String with std::string
//! @param lhs EmotiBit::String to compare
//! @param rhs std::string to compare
//! @return Boolean true if the strings are equal, false if not
bool operator==(const EmotiBit::String& lhs, const std::string& rhs) {
    return lhs.str == rhs;
}

//! @brief Helper operator to compare std::string with EmotiBit::String
//! @param lhs std::string to compare
//! @param rhs EmotiBit::String to compare
//! @return Boolean true if the strings are equal, false if not
bool operator==(const EmotiBit::String& lhs, const EmotiBit::String& rhs) {
    return lhs.str == rhs.str;
}


//! @brief Creates a test data packet to ensure createPacket can intake a std::string and return a std::string
//! @return Boolean true if the test passes, false if it fails
bool testStdStringToStdString()
{
    int tempLength = 1;
    std::string data = "0,1";
    std::string packet;
    EmotiBitPacket::Header header = EmotiBitPacket::createTestHeader(tempLength);
    
    packet = EmotiBitPacket::createPacket(header, data);
    std::cout << packet << std::endl;
    
    if (packet.find(data) == std::string::npos)
    {
        std::cout << "testStdStringToStdString failed" << std::endl;
        return false;
    }
    else
    {
        std::cout << "testStdStringToStdString successful" << std::endl;
        return true;
    }
}

//! @brief Creates a test data packet to ensure createPacket can intake a std::string and return a String
//! @return Boolean true if the test passes, false if it fails
bool testStdStringToString()
{
    int tempLength = 1;
    std::string data = "0,1";
    String packet;
    EmotiBitPacket::Header header = EmotiBitPacket::createTestHeader(tempLength);
    
    packet = EmotiBitPacket::createPacket(header, data);
    std::cout << packet.str << std::endl;
    
    String testData = packet.substring(packet.length() - 4, packet.length()); //manually extract the last 4 characters to keep the comparison as a String
    String expectedData = "0,1\n";
    if (!testData.equals(expectedData))
    {
        std::cout << "testStdToString failed: Got '" << testData.str << "', Expected '" << expectedData.str << "'" << std::endl;
        return false;
    }
    else
    {
        std::cout << "testStdToString successful" << std::endl;
        return true;
    }
}

//! @brief Creates a test data packet to ensure createPacket can intake a String and return a std::string
//! @return Boolean true if the test passes, false if it fails
bool testStringToStdString()
{
    int tempLength = 1;
    String data = "0,1";
    std::string packet;
    EmotiBitPacket::Header header = EmotiBitPacket::createTestHeader(tempLength);
    
    packet = EmotiBitPacket::createPacket(header, data);
    std::cout << packet << std::endl;

    if (packet.find(data) == std::string::npos)
    {
        std::cout << "testStringToStdString failed" << std::endl;
        return false;
    }
    else
    {
        std::cout << "testStringToStdString successful" << std::endl;
        return true;
    }
}

//! @brief Creates a test data packet to ensure createPacket can intake a String and return a String
//! @return Boolean true if the test passes, false if it fails
bool testStringToString()
{
    int tempLength = 1;
    String data = "0,1";
    String packet;
    EmotiBitPacket::Header header = EmotiBitPacket::createTestHeader(tempLength);

    packet = EmotiBitPacket::createPacket(header, data);
    std::cout << packet.str << std::endl;

    String testData = packet.substring(packet.length() - 4, packet.length()); //manually extract the last 4 characters to keep the comparison as a String
    String expectedData = "0,1\n";
    if (!testData.equals(expectedData))
    {
        std::cout << "testStringToString failed" << std::endl;
        return false;
    }
    else
    {
        std::cout << "testStringToString successful" << std::endl;
        return true;
    }
}

int main() {
    bool results[] =
    {
        testStdStringToStdString(),
        testStdStringToString(),
        testStringToStdString(),
        testStringToString()
    };

    bool any_fail = false;
    for (bool result : results)
    {
        if (!result) any_fail = true;
    }

    if (any_fail) 
    {
        std::cout << "One or more tests failed." << std::endl;
        return 1; 
    } else 
    {
        std::cout << "All tests passed" << std::endl;
        return 0; 
    }
}
#endif