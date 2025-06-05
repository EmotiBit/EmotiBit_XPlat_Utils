/**************************************************************************/
/*!
    @file     EmotiBitDataTester.cpp
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

int main() {
    String dataMessage;
    uint16_t packetNumber = 0;

    // Define the type tags for the test data, can be used to expand the test data in the future
    const char* typeTags[] = {
        EmotiBitPacket::TypeTag::PPG_INFRARED,
        EmotiBitPacket::TypeTag::PPG_RED,
        EmotiBitPacket::TypeTag::PPG_GREEN,
        EmotiBitPacket::TypeTag::EDA,
        EmotiBitPacket::TypeTag::EDL,
        EmotiBitPacket::TypeTag::EDR,
        EmotiBitPacket::TypeTag::TEMPERATURE_0,
        EmotiBitPacket::TypeTag::HUMIDITY_0,
        EmotiBitPacket::TypeTag::ACCELEROMETER_X,
        EmotiBitPacket::TypeTag::ACCELEROMETER_Y,
        EmotiBitPacket::TypeTag::ACCELEROMETER_Z,
        EmotiBitPacket::TypeTag::GYROSCOPE_X,
        EmotiBitPacket::TypeTag::GYROSCOPE_Y,
        EmotiBitPacket::TypeTag::GYROSCOPE_Z,
        EmotiBitPacket::TypeTag::MAGNETOMETER_X,
        EmotiBitPacket::TypeTag::MAGNETOMETER_Y,
        EmotiBitPacket::TypeTag::MAGNETOMETER_Z
    };
    uint8_t clipping = 0;
    uint32_t x = 0;

    std::ofstream testfile("test.csv", std::ios::binary);
    if (!testfile.is_open()) {
        std::cerr << "Failed to open test.csv for writing." << std::endl;
        return 1;
    }

    while (x <= EmotiBitPacket::maxTestLength + 1) {
        EmotiBitPacket::appendTestDataMessage(dataMessage);
        testfile << dataMessage.str;
        x++;
    }

    testfile.close();
    return 0;
}
#endif