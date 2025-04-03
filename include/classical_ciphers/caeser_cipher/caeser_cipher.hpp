#pragma once

#include <string>
#include <cstdint>

/**
 * @file caeser_cipher.hpp
 * @brief Caesar Cipher encryption and decryption with optional digit shifting.
 * 
 * This header provides functions to encrypt and decrypt strings using 
 * the classic Caesar Cipher technique. It supports both alphabetic 
 * characters (A-Z, a-z) and numeric digits (0-9) shifting.
 */

/**
 * @typedef Plaintext
 * @brief Alias for plaintext data type.
 */
using Plaintext = std::string;

/**
 * @typedef Ciphertext
 * @brief Alias for ciphertext data type.
 */
using Ciphertext = std::string;

/**
 * @brief Encrypts a plaintext string using Caesar Cipher.
 * 
 * Shifts alphabetic characters by (key % 26) positions 
 * and numeric digits by (key % 10) positions.
 * Non-alphanumeric characters remain unchanged.
 * 
 * @param pln Input plaintext to encrypt.
 * @param key Shift key (0-255).
 * @return Ciphertext Encrypted result.
 */
Ciphertext caeser_encrypt(const Plaintext &pln, uint8_t key);

/**
 * @brief Decrypts a ciphertext string using Caesar Cipher.
 * 
 * Reverses the shift applied during encryption. 
 * Handles both alphabetic characters and numeric digits.
 * 
 * @param cxt Input ciphertext to decrypt.
 * @param key Shift key used during encryption.
 * @return Plaintext Decrypted result.
 */
Plaintext caeser_decrypt(const Ciphertext &cxt, uint8_t key);
