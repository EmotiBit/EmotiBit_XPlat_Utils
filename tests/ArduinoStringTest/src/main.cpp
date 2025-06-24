/**************************************************************************/
/*!
    @file     main.cpp
    @author   Joseph Jacobson (EmotiBit)

    @mainpage Arduino String Tester

    @section intro_sec Introduction

    This is a program to test the string conversion functions in ArduinoString.h.

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
using namespace EmotiBit;

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

//! @brief Test function to verify that an empty String is equal to an empty std::string
//! @return Boolean true if the test passes, false if it fails
bool testEmptyString()
{
    String str;
    if (!(str == ""))
    {
        std::cout << "testEmptyString failed" << std::endl;
        return false;
    }
    std::cout << "testEmptyString successful" << std::endl;
    return true;
}

//! @brief Test function to verify that a String initialized with a std::string is equal to the std::string
//! @return Boolean true if the test passes, false if it fails
bool testString()
{
    String str = "test";

    if (!(str == std::string("test")))
    {
        std::cout << "testString failed" << std::endl;
        return false;
    }
    std::cout << "testString successful" << std::endl;
    return true;
}

//! @brief Test function to verify a uint32_t to String conversion
//! @return Boolean true if the test passes, false if it fails
bool testUint32ToString()
{
    uint32_t num = 1234567890;
    String str = String(num);
    if (!(str == "1234567890"))
    {
        std::cout << "testUint32ToString failed" << std::endl;
        return false;
    }
    std::cout << "testUint32ToString successful" << std::endl;
    return true;
}


//! @brief Test function to verify that assigning a String to another String works
//! @return Boolean true if the test passes, false if it fails
bool testAssignStringToString()
{
    String str1 = "test";
    String str2;
    str2 = str1;
    if(!(str1 == str2))
    {
        std::cout << "testAssignStringToString failed" << std::endl;
        return false;
    }
    std::cout << "testAssignStringToString successful" << std::endl;
    return true;
}

//! @brief Test function to verify that assigning a std::string to a String works
//! @return Boolean true if the test passes, false if it fails
bool testAssignStdStringToString()
{
    String str1;
    std::string str2 = "test";
    str1 = str2;
    if(!(str1 == str2))
    {
        std::cout << "testAssignStdStringToString failed" << std::endl;
        return false;
    }
    std::cout << "testAssignStdStringToString successful" << std::endl;
    return true;
}   

//! @brief Test function to verify that adding and assigning a String to another String works
//! @return Boolean true if the test passes, false if it fails
bool testAddAssignString()
{
    String str1 = "test";
    String str2 = "ing";
    str1 += str2;
    if (!(str1 == "testing"))
    {
        std::cout << "testAddAssignString failed" << std::endl;
        return false;
    }
    std::cout << "testAddAssignString successful" << std::endl;
    return true;
}

//! @brief Test function to verify that adding and assigning a std::string to a String works
//! @return Boolean true if the test passes, false if it fails
bool testAddAssignStdString()
{
    String str1 = "test";
    string str2 = "ing";
    str1 += str2;
    if (!(str1 == "testing"))
    {
        std::cout << "testAddAssignStdString failed" << std::endl;
        return false;
    } 
    std::cout << "testAddAssignStdString successful" << std::endl;
    return true;
}

//! @brief Test function to verify that adding a String to another String works
//! @return Boolean true if the test passes, false if it fails
bool testAddString()
{
    String str1 = "test";
    String str2 = "ing";
    String result = str1 + str2;
    if (!(result == "testing"))
    {
        std::cout << "testAddString failed" << std::endl;
        return false;
    }
    std::cout << "testAddString successful" << std::endl;
    return true;
}

//! @brief Test function to verify that adding a std::string to a String works
//! @return Boolean true if the test passes, false if it fails
bool testAddStdString()
{
    String str1 = "test";
    string str2 = "ing";
    String result = str1 + str2;
    if (!(result == "testing"))
    {
        std::cout << "testAddStdString failed" << std::endl;
        return false;
    }
    std::cout << "testAddStdString successful" << std::endl;
    return true;
}

//! @brief Test function to verify that adding and assigning a char to a String works
//! @return Boolean true if the test passes, false if it fails
bool testAddAssignChar()
{
    String str = "test";
    str += 'i';
    if (!(str == "testi"))
    {
        std::cout << "testAddAssignChar failed" << std::endl;
        return false;
    }
    std::cout << "testAddAssignChar successful" << std::endl;
    return true;
}

//! @brief Test function to verify that adding a char to a String works
//! @return Boolean true if the test passes, false if it fails
bool testAddChar()
{
    String str = "test";
    String result = str + 'i';
    if (!(result == "testi"))
    {
        std::cout << "testAddChar failed" << std::endl;
        return false;
    }
    std::cout << "testAddChar successful" << std::endl;
    return true;
}

//! @brief Test function to verify that adding and assigning an int to a String works
//! @return Boolean true if the test passes, false if it fails
bool testAddAssignInt()
{
    String str = "test";
    str += 123;
    if (!(str == "test123"))
    {
        std::cout << "testAddAssignInt failed" << std::endl;
        return false;
    }
    std::cout << "testAddAssignInt successful" << std::endl;
    return true;
}

//! @brief Test function to verify that finding the index of a character in a String works
//! @return Boolean true if the test passes, false if it fails
bool testIndexOf()
{
    String str = "test";
    size_t index = str.indexOf('e', 0);
    if (index != 1)
    {
        std::cout << "testIndexOf failed" << std::endl;
        return false;
    }
    std::cout << "testIndexOf successful" << std::endl;
    return true;
}

//! @brief Test function to verify that substring extraction works
//! @return Boolean true if the test passes, false if it fails
bool testSubstring()
{
    String str = "test";
    String subStr = str.substring(1, 3);
    if (!(subStr == "es"))
    {
        std::cout << "testSubstring failed" << std::endl;
        return false;
    }
    std::cout << "testSubstring successful" << std::endl;
    return true;
}

//! @brief Test function to verify that String object equality works
//! @return Boolean true if the test passes, false if it fails
bool testEquals()
{
    String str1 = "test";
    String str2 = "test";
    if (!str1.equals(str2))
    {
        std::cout << "testEquals failed" << std::endl;
        return false;
    }
    std::cout << "testEquals successful" << std::endl;
    return true;
}

//! @brief Test function to verify that the length of a String is calculated correctly
//! @return Boolean true if the test passes, false if it fails
bool testLength()
{
    String str = "test";
    if (str.length() != 4)
    {
        std::cout << "testLength failed" << std::endl;
        return false;
    }
    std::cout << "testLength successful" << std::endl;
    return true;
}

//! @brief Test function to verify that converting a String to an int works
//! @return Boolean true if the test passes, false if it fails
bool testToInt()
{
    String str = "12345";
    int value = str.toInt();
    if (value != 12345)
    {
        std::cout << "testToInt failed" << std::endl;
        return false;
    }
    std::cout << "testToInt successful" << std::endl;
    return true;
}

//! @brief Test function to test return operator for converting to std::string
//! @return Boolean true if the test passes, false if it fails
bool testStdStringReturnOperator()
{
    String str = "test";
    std::string stdStr = str;
    if (stdStr != "test")
    {
        std::cout << "testStdStringReturnOperator failed" << std::endl;
        return false;
    }
    std::cout << "testStdStringReturnOperator successful" << std::endl;
    return true;
}

int main() {
    bool results[] =
    {
        testEmptyString(),
        testString(),
        testUint32ToString(),
        testAssignStringToString(),
        testAssignStdStringToString(),
        testAddAssignString(),
        testAddAssignStdString(),
        testAddString(),
        testAddStdString(),
        testAddAssignChar(),
        testAddChar(),
        testAddAssignInt(),
        testIndexOf(),
        testSubstring(),
        testEquals(),
        testLength(),
        testToInt(),
        testStdStringReturnOperator()
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