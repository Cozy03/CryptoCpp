#include <classical_ciphers/caeser_cipher.hpp>
#include <classical_ciphers/vigenere_cipher.hpp>
#include <gtest/gtest.h>

/**
 * @file classical_cipher_test.cpp
 * @brief Unit tests for Classical Ciphers (Caesar & Vigenère).
 */

using cryptcpp::Plaintext;
using cryptcpp::Ciphertext;
using namespace cryptcpp::classical;

///////////////////////
// Caesar Cipher Tests
///////////////////////

TEST(CaeserCipherTest, BasicAlphabetEncryption) {
    Plaintext input = "HELLOworld";
    uint8_t key = 3;
    Ciphertext expected = "KHOORzruog";

    EXPECT_EQ(caeser_encrypt(input, key), expected);
}

TEST(CaeserCipherTest, BasicAlphabetDecryption) {
    Ciphertext input = "KHOORzruog";
    uint8_t key = 3;
    Plaintext expected = "HELLOworld";

    EXPECT_EQ(caeser_decrypt(input, key), expected);
}

TEST(CaeserCipherTest, AlphabetAndDigitEncryption) {
    Plaintext input = "abcXYZ123";
    uint8_t key = 4;
    Ciphertext expected = "efgBCD567";

    EXPECT_EQ(caeser_encrypt(input, key), expected);
}

TEST(CaeserCipherTest, AlphabetAndDigitDecryption) {
    Ciphertext input = "efgBCD567";
    uint8_t key = 4;
    Plaintext expected = "abcXYZ123";

    EXPECT_EQ(caeser_decrypt(input, key), expected);
}

TEST(CaeserCipherTest, NoChangeWithZeroKey) {
    Plaintext input = "Test123";
    uint8_t key = 0;

    EXPECT_EQ(caeser_encrypt(input, key), input);
    EXPECT_EQ(caeser_decrypt(input, key), input);
}

TEST(CaeserCipherTest, LargeKeyNormalizationChar) {
    Plaintext input = "HELLOBRO";
    uint8_t key = 208;  // 208 % 26 == 0

    EXPECT_EQ(caeser_encrypt(input, key), input);
    EXPECT_EQ(caeser_decrypt(input, key), input);
}

TEST(CaeserCipherTest, LargeKeyNormalizationDigit) {
    Plaintext input = "123467";
    uint8_t key = 20;  // 20 % 10 == 0

    EXPECT_EQ(caeser_encrypt(input, key), input);
    EXPECT_EQ(caeser_decrypt(input, key), input);
}

///////////////////////////
// Vigenère Cipher Tests
///////////////////////////

TEST(VigenereCipherTest, BasicEncryption) {
    Plaintext input = "HELLOWORLD";
    std::string key = "KEY";
    Ciphertext expected = "RIJVSUYVJN";

    EXPECT_EQ(vigenere_encrypt(input, key), expected);
}

TEST(VigenereCipherTest, BasicDecryption) {
    Ciphertext input = "RIJVSUYVJN";
    std::string key = "KEY";
    Plaintext expected = "HELLOWORLD";

    EXPECT_EQ(vigenere_decrypt(input, key), expected);
}

TEST(VigenereCipherTest, MixedCaseAndSymbols) {
    Plaintext input = "Hello World!";
    std::string key = "key";
    Ciphertext encrypted = vigenere_encrypt(input, key);
    Plaintext decrypted = vigenere_decrypt(encrypted, key);

    EXPECT_EQ(decrypted, input);
}

TEST(VigenereCipherTest, LongKeyHandling) {
    Plaintext input = "THISISALONGMESSAGE";
    std::string key = "SHORT";

    Ciphertext encrypted = vigenere_encrypt(input, key);
    Plaintext decrypted = vigenere_decrypt(encrypted, key);

    EXPECT_EQ(decrypted, input);
}
