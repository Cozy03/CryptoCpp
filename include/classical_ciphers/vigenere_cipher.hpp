#pragma once

#include <common/types.hpp>
#include <cstdint>
#include <string>

/**
 * @file vigenere_cipher.hpp
 * @brief Vigenère Cipher encryption and decryption.
 */

namespace cryptcpp::classical {

/**
 * @brief Encrypts plaintext using Vigenère Cipher.
 * 
 * Each alphabetic character in the plaintext is shifted by a corresponding character 
 * from the key. Non-alphabetic characters remain unchanged.
 * 
 * @param plt The input plaintext string.
 * @param key The key string used for encryption (only alphabetic characters).
 * @return Ciphertext The encrypted ciphertext.
 */
Ciphertext vigenere_encrypt(const Plaintext &plt, const std::string &key);

/**
 * @brief Decrypts ciphertext using Vigenère Cipher.
 * 
 * Reverses the shift applied during encryption using the key.
 * 
 * @param cxt The input ciphertext string.
 * @param key The key string used for decryption (same as encryption key).
 * @return Plaintext The decrypted plaintext.
 */
Plaintext vigenere_decrypt(const Ciphertext &cxt, const std::string &key);

} // namespace cryptcpp::classical
