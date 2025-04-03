#include <classical_ciphers/caeser_cipher/caeser_cipher.hpp>
#include <gtest/gtest.h>

/**
 * @file caeser_cipher_test.cpp
 * @brief Unit tests for Caesar Cipher encryption and decryption.
 */

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

TEST(CaeserCipherTest, LargeKeyNormalizationCHAR) {
    Plaintext input = "HELLOBRO";
    uint8_t key = 208; 

    EXPECT_EQ(caeser_encrypt(input, key), input);
    EXPECT_EQ(caeser_decrypt(input, key), input);
}

TEST(CaeserCipherTest, LargeKeyNormalizationNUM) {
    Plaintext input = "123467";
    uint8_t key = 20; 

    EXPECT_EQ(caeser_encrypt(input, key), input);
    EXPECT_EQ(caeser_decrypt(input, key), input);
}