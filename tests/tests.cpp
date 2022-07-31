#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <unordered_map>
#include "catch.hpp"
#include "../include/cipher.hpp"
#include "../include/other.hpp"
#include "../include/recover.hpp"
#include "../include/functions.hpp"

std::string messageKey = "ARARA";
std::string message = "REGULATING THE CIRCULATION";
std::string cipheredMessage = "RVGLLAKIEG TYE TIRTUCATZOE";

TEST_CASE("Cipher works", "[cipher.cipher]")
{
    // message and messageKey are uppercase
    REQUIRE(cipher(message, messageKey) == cipheredMessage);

    std::string ciphered = "TYIJ IS R SZMPCE VXADPCE TF SVE IW CZPHVRZNG NOIKS";

    // message is upper case but messageKey is lowercase
    REQUIRE(cipher("THIS IS A SIMPLE EXAMPLE TO SEE IF CIPHERING WORKS", "arara") == ciphered);

    // message and messageKey are lowercase
    REQUIRE(cipher("this is a simple example to see if ciphering works", "arara") == ciphered);

    // message is lowercase but messageKey is uppercase
    REQUIRE(cipher("this is a simple example to see if ciphering works", "ARARA") == ciphered);
}

TEST_CASE("Decipher works", "[cipher.decipher]")
{
    // cipheredMessage and messageKey are uppercase
    REQUIRE(decipher(cipheredMessage, messageKey) == message);

    std::string deciphered = "THIS IS A SIMPLE EXAMPLE TO SEE IF DECIPHERING WORKS";

    // cipheredMessage is upper case but messageKey is lowercase
    REQUIRE(decipher("TYIJ IS R SZMPCE VXADPCE TF SVE IW DVCIGHVRIEG NORBS", "arara") == deciphered);

    // cipheredMessage and messageKey are lowercase
    REQUIRE(decipher("tyij is r szmpce vxadpce tf sve iw dvcighvrieg norbs", "arara") == deciphered);

    // cipheredMessage is lowercase but messageKey is uppercase
    REQUIRE(decipher("tyij is r szmpce vxadpce tf sve iw dvcighvrieg norbs", "ARARA") == deciphered);
}

TEST_CASE("String conversion to uppercase works properly", "[other.convertToUpper]")
{
    std::string lower = "dinosaur";
    std::string upper = "DINOSAUR";

    REQUIRE(convertToUpper(lower) == upper);

    REQUIRE(convertToUpper(upper) == upper);
}

TEST_CASE("Read from file works properly", "[other.readFromFile]")
{
    REQUIRE(readFromFile("") == "");

    REQUIRE(readFromFile("tests/test.txt") == "THIS IS A TEST FILE");
}

TEST_CASE("Get all letters frequency works properly", "[recover.getAllLettersFrequency]")
{
    std::unordered_map<char, int> current = getAllLettersFrequency("EXAMPLE");
    REQUIRE(current.size() == 26);
    REQUIRE(current.find('A')->second == 1);
    REQUIRE(current.find('B')->second == 0);
    REQUIRE(current.find('E')->second == 2);

}
