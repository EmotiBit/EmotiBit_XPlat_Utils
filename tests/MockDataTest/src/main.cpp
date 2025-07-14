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

int main(int argc, char* argv[]) {
    String dataMessage;
    uint16_t packetNumber = 0;
    uint8_t clipping = 0;
    uint32_t x = 0;
	const char* testDataType = EmotiBitPacket::TestType::SAWTOOTH; // Default to SAWTOOTH

    // Check test type
    for (int i = 1; i < argc - 1; ++i) {
        if (std::string(argv[i]) == "--testtype" || std::string(argv[i]) == "-t") {
            std::string type = argv[i + 1];
            if (type == "Splitter" || type == "splitter" || type == "SPLITTER" || type == "SP") {
                testDataType = EmotiBitPacket::TestType::SPLITTER;
            } else if (type == "Sawtooth" || type == "sawtooth" || type == "SAWTOOTH" || type == "ST") {
                testDataType = EmotiBitPacket::TestType::SAWTOOTH;
            } else {
                std::cerr << "Unknown test type: " << type << ". Using default (SAWTOOTH)." << std::endl;
            }
        }
    }

    std::ofstream testfile("test.csv", std::ios::binary);
    if (!testfile.is_open()) {
        std::cerr << "Failed to open test.csv for writing." << std::endl;
        return 1;
    }

    while (x <= EmotiBitPacket::maxTestLength + 2) { // Loop until maxTestLength + 2 to account for the first and last messages
        EmotiBitPacket::createTestDataPacket(dataMessage, testDataType);
        testfile << dataMessage.str;
        x++;
    }

    testfile.close();
    return 0;
}
#endif