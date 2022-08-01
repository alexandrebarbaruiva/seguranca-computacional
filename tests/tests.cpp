#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <unordered_map>
#include <cmath>
#include "catch.hpp"
#include "../include/cipher.hpp"
#include "../include/other.hpp"
#include "../include/recover.hpp"

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
    SECTION("No name was provided")
    {
        REQUIRE(readFromFile("") == "");
    }

    SECTION("Filename was provided correctly and file exists")
    {
        REQUIRE(readFromFile("tests/inputs/test.txt") == "THIS IS A TEST FILE");
    }

    SECTION("Filename was provided correctly but file doesn't exists")
    {
        REQUIRE(readFromFile("tests/inputs/~.t.a.s.~") == "");
    }
}

TEST_CASE("Remove all non alpha characters works properly", "[other.removeNonAlphanumeric]")
{
    REQUIRE(removeNonAlpha("A l.l,N!@;on<>,Alp*ha()0+1=2_3") == "AllNonAlpha");
}

TEST_CASE("Get all letters frequency works properly", "[recover.getAllLettersFrequency]")
{
    std::unordered_map<char, int> current = getAllLettersFrequency("EXAMPLE");
    REQUIRE(current.size() == 26);
    REQUIRE(current.find('A')->second == 1);
    REQUIRE(current.find('B')->second == 0);
    REQUIRE(current.find('E')->second == 2);
}

TEST_CASE("Index of Coincidence works properly", "[recover.getIndexCoincidence]")
{
    REQUIRE(getIndexCoincidence("ABACD") == 0.1f);
    REQUIRE(getIndexCoincidence("ABABA") == 0.4f);
    REQUIRE(getIndexCoincidence("ABCDEF") == 0.0f);
    REQUIRE(getIndexCoincidence("AAA") == 1.0f);
    REQUIRE(std::ceil(getIndexCoincidence("ABA") * 100.0) == std::ceil(33.33f));
}

TEST_CASE("Key length analysis works properly", "[recover.findKeyLength]")
{
    std::string ciphered = readFromFile("tests/inputs/find_key_length.txt");

    REQUIRE(findKeyLength(ciphered) == 15);
}

TEST_CASE("Key finder works properly", "[recover.findKey]")
{
    std::string ciphered = readFromFile("tests/inputs/find_key_length.txt");

    REQUIRE(findKey(ciphered, 5) == "ARARA");
}

TEST_CASE("Run all subsets", "[all]")
{
    std::string directory = "tests/inputs/subset_N/";

    SECTION("Subset 1 - Large message, small key")
    {
        directory = directory.substr(0, directory.size() - 2).append("1/");
        std::string expectedMessage = readFromFile(directory + "cipher_message.txt");
        std::string expectedDecipheredMessage = readFromFile(directory + "decipher_message.txt");
        std::string expectedKey = readFromFile(directory + "key.txt");

        REQUIRE(cipher(expectedMessage, expectedKey) == expectedDecipheredMessage);
        REQUIRE(decipher(expectedDecipheredMessage, expectedKey) == expectedMessage);
        REQUIRE(guessKeyByMessage(expectedDecipheredMessage, "en") == expectedKey);
    }

    SECTION("Subset 2 - Medium message, small key")
    {
        directory = directory.substr(0, directory.size() - 2).append("2/");
        std::string expectedMessage = readFromFile(directory + "cipher_message.txt");
        std::string expectedDecipheredMessage = readFromFile(directory + "decipher_message.txt");
        std::string expectedKey = readFromFile(directory + "key.txt");

        REQUIRE(cipher(expectedMessage, expectedKey) == expectedDecipheredMessage);
        REQUIRE(decipher(expectedDecipheredMessage, expectedKey) == expectedMessage);
        REQUIRE(guessKeyByMessage(expectedDecipheredMessage, "en") == expectedKey);
    }

    SECTION("Subset 3 - Small message, small key")
    {
        directory = directory.substr(0, directory.size() - 2).append("3/");
        std::string expectedMessage = readFromFile(directory + "cipher_message.txt");
        std::string expectedDecipheredMessage = readFromFile(directory + "decipher_message.txt");
        std::string expectedKey = readFromFile(directory + "key.txt");

        REQUIRE(cipher(expectedMessage, expectedKey) == expectedDecipheredMessage);
        REQUIRE(decipher(expectedDecipheredMessage, expectedKey) == expectedMessage);
        REQUIRE(guessKeyByMessage(expectedDecipheredMessage, "en") == expectedKey);
    }

    SECTION("Subset 4 - Large message, big key")
    {
        directory = directory.substr(0, directory.size() - 2).append("4/");
        std::string expectedMessage = readFromFile(directory + "cipher_message.txt");
        std::string expectedDecipheredMessage = readFromFile(directory + "decipher_message.txt");
        std::string expectedKey = readFromFile(directory + "key.txt");

        REQUIRE(cipher(expectedMessage, expectedKey) == expectedDecipheredMessage);
        REQUIRE(decipher(expectedDecipheredMessage, expectedKey) == expectedMessage);
        REQUIRE(guessKeyByMessage(expectedDecipheredMessage, "en") == expectedKey);
    }

    SECTION("Subset 5 - Medium message, big key")
    {
        directory = directory.substr(0, directory.size() - 2).append("5/");
        std::string expectedMessage = readFromFile(directory + "cipher_message.txt");
        std::string expectedDecipheredMessage = readFromFile(directory + "decipher_message.txt");
        std::string expectedKey = readFromFile(directory + "key.txt");

        REQUIRE(cipher(expectedMessage, expectedKey) == expectedDecipheredMessage);
        REQUIRE(decipher(expectedDecipheredMessage, expectedKey) == expectedMessage);
        // Algorithm is unable to find correct key due to non ideal message and key
        REQUIRE(guessKeyByMessage(expectedDecipheredMessage, "en") != expectedKey);
    }

    SECTION("Subset 6 - Small message, big key")
    {
        directory = directory.substr(0, directory.size() - 2).append("6/");
        std::string expectedMessage = readFromFile(directory + "cipher_message.txt");
        std::string expectedDecipheredMessage = readFromFile(directory + "decipher_message.txt");
        std::string expectedKey = readFromFile(directory + "key.txt");

        REQUIRE(cipher(expectedMessage, expectedKey) == expectedDecipheredMessage);
        REQUIRE(decipher(expectedDecipheredMessage, expectedKey) == expectedMessage);
        // Algorithm is unable to find correct key due to non ideal message and key
        REQUIRE(guessKeyByMessage(expectedDecipheredMessage, "en") != expectedKey);
    }

    SECTION("Subset 7 - Portuguese message, small key")
    {
        directory = directory.substr(0, directory.size() - 2).append("7/");
        std::string expectedMessage = readFromFile(directory + "cipher_message.txt");
        std::string expectedDecipheredMessage = readFromFile(directory + "decipher_message.txt");
        std::string expectedKey = readFromFile(directory + "key.txt");

        REQUIRE(cipher(expectedMessage, expectedKey) == expectedDecipheredMessage);
        REQUIRE(decipher(expectedDecipheredMessage, expectedKey) == expectedMessage);
        REQUIRE(guessKeyByMessage(expectedDecipheredMessage, "pt") == expectedKey);
    }

    SECTION("Subset 8 - Portuguese message, medium key")
    {
        directory = directory.substr(0, directory.size() - 2).append("8/");
        std::string expectedMessage = readFromFile(directory + "cipher_message.txt");
        std::string expectedDecipheredMessage = readFromFile(directory + "decipher_message.txt");
        std::string expectedKey = readFromFile(directory + "key.txt");

        REQUIRE(cipher(expectedMessage, expectedKey) == expectedDecipheredMessage);
        REQUIRE(decipher(expectedDecipheredMessage, expectedKey) == expectedMessage);
        REQUIRE(guessKeyByMessage(expectedDecipheredMessage, "pt") == expectedKey);
    }
}
