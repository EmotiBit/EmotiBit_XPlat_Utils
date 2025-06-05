/**************************************************************************/
/*!
    @file     EmotiBitDataTester.cpp
    @author   Joseph Jacobson (EmotiBit)

    @mainpage Arduino String Tester

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
#include "ArduinoString.h"

//helper operators for conducting tests
bool operator==(const EmotiBit::String& lhs, const std::string& rhs) {
    return lhs.str == rhs;
}
bool operator==(const EmotiBit::String& lhs, const EmotiBit::String& rhs) {
    return lhs.str == rhs.str;
}

using namespace EmotiBit;
bool test_Empty_String()
{
    String str;
    if (!(str == ""))
    {
        std::cout << "Test failed" << std::endl;
        return false;
    }
    std::cout << "Test successful" << std::endl;
    return true;
}

bool test_String()
{
    String str = "test";

    if (!(str == std::string("test")))
    {
        std::cout << "Test failed" << std::endl;
        return false;
    }
    std::cout << "Test successful" << std::endl;
    return true;
}

bool test_Assign_String_To_String()
{
    String str1 = "test";
    String str2;
    str2 = str1;
    if(!(str1 == str2))
    {
        std::cout << "Test failed" << std::endl;
        return false;
    }
    std::cout << "Test successful" << std::endl;
    return true;
}


bool test_Assign_string_To_String()
{
    String str1;
    std::string str2 = "test";
    str1 = str2;
    if(!(str1 == str2))
    {
        std::cout << "Test failed" << std::endl;
        return false;
    }
    std::cout << "Test successful" << std::endl;
    return true;
}   


bool test_Add_Assign_String()
{
    String str1 = "test";
    String str2 = "ing";
    str1 += str2;
    if (!(str1 == "testing"))
    {
        std::cout << "Test failed" << std::endl;
        return false;
    }
    std::cout << "Test successful" << std::endl;
    return true;
}

bool test_Add_Assign_string()
{
    String str1 = "test";
    string str2 = "ing";
    str1 += str2;
    if (!(str1 == "testing"))
    {
        std::cout << "Test failed" << std::endl;
        return false;
    } 
    std::cout << "Test successful" << std::endl;
    return true;
}

bool test_Add_String()
{
    String str1 = "test";
    String str2 = "ing";
    String result = str1 + str2;
    if (!(result == "testing"))
    {
        std::cout << "Test failed" << std::endl;
        return false;
    }
    std::cout << "Test successful" << std::endl;
    return true;
}

bool test_Add_string()
{
    String str1 = "test";
    string str2 = "ing";
    String result = str1 + str2;
    if (!(result == "testing"))
    {
        std::cout << "Test failed" << std::endl;
        return false;
    }
    std::cout << "Test successful" << std::endl;
    return true;
}

bool test_Add_Assign_Char()
{
    String str = "test";
    str += 'i';
    if (!(str == "testi"))
    {
        std::cout << "Test failed" << std::endl;
        return false;
    }
    std::cout << "Test successful" << std::endl;
    return true;
}

bool test_Add_Char()
{
    String str = "test";
    String result = str + 'i';
    if (!(result == "testi"))
    {
        std::cout << "Test failed" << std::endl;
        return false;
    }
    std::cout << "Test successful" << std::endl;
    return true;
}

bool test_Add_Assign_Int()
{
    String str = "test";
    str += 123;
    if (!(str == "test123"))
    {
        std::cout << "Test failed" << std::endl;
        return false;
    }
    std::cout << "Test successful" << std::endl;
    return true;
}

bool test_indexOf()
{
    String str = "test";
    size_t index = str.indexOf('e', 0);
    if (index != 1)
    {
        std::cout << "Test failed" << std::endl;
        return false;
    }
    std::cout << "Test successful" << std::endl;
    return true;
}

bool test_substring()
{
    String str = "test";
    String subStr = str.substring(1, 3);
    if (!(subStr == "es"))
    {
        std::cout << "Test failed" << std::endl;
        return false;
    }
    std::cout << "Test successful" << std::endl;
    return true;
}

bool test_equals()
{
    String str1 = "test";
    String str2 = "test";
    if (!str1.equals(str2))
    {
        std::cout << "Test failed" << std::endl;
        return false;
    }
    std::cout << "Test successful" << std::endl;
    return true;
}

bool test_length()
{
    String str = "test";
    if (str.length() != 4)
    {
        std::cout << "Test failed" << std::endl;
        return false;
    }
    std::cout << "Test successful" << std::endl;
    return true;
}

bool test_toInt()
{
    String str = "12345";
    int value = str.toInt();
    if (value != 12345)
    {
        std::cout << "Test failed" << std::endl;
        return false;
    }
    std::cout << "Test successful" << std::endl;
    return true;
}


int main() {
    bool results[] = {
        test_Empty_String(),
        test_String(),
        test_Assign_String_To_String(),
        test_Assign_string_To_String(),
        test_Add_Assign_String(),
        test_Add_Assign_string(),
        test_Add_String(),
        test_Add_string(),
        test_Add_Assign_Char(),
        test_Add_Char(),
        test_Add_Assign_Int(),
        test_indexOf(),
        test_substring(),
        test_equals(),
        test_length(),
        test_toInt()
    };

    bool any_fail = false;
    std::ofstream csv("test.csv");
    for (bool r : results) {
        std::cout << (r ? '0' : '1');
        csv << (r ? '0' : '1');
        if (!r) any_fail = true;
    }
    std::cout << std::endl;
    csv << std::endl;
    csv.close();
    return any_fail ? 1 : 0;
}

#endif