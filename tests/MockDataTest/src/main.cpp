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

int main() {
    String dataMessage;
    uint16_t packetNumber = 0;
    uint8_t clipping = 0;
    uint32_t x = 0;

    std::ofstream testfile("test.csv", std::ios::binary);
    if (!testfile.is_open()) {
        std::cerr << "Failed to open test.csv for writing." << std::endl;
        return 1;
    }

    while (x <= EmotiBitPacket::maxTestLength + 2) { // Loop until maxTestLength + 2 to account for the first and last messages
        EmotiBitPacket::createTestDataPacket(dataMessage);
        testfile << dataMessage.str;
        x++;
    }

    testfile.close();
    return 0;
}
#endif