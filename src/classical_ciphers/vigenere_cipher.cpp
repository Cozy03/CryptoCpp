/**
 * @file vigenere_cipher.cpp
 * @brief Implementation of Vigenère Cipher encryption and decryption.
 */

#include <classical_ciphers/vigenere_cipher.hpp>
#include <cctype>

namespace cryptcpp::classical {

Ciphertext vigenere_encrypt(const Plaintext &plt, const std::string &key) {
    Ciphertext result = plt;
    size_t key_len = key.length();
    size_t j = 0; // Key index

    for (size_t i = 0; i < plt.length(); ++i) {
        char c = plt[i];
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            char key_c = std::toupper(key[j % key_len]) - 'A';
            result[i] = (c - base + key_c) % 26 + base;
            j++; // only increment when alphabetic
        }
        else {
            result[i] = c; // Keep non-alphabetic characters as is
        }
    }
    return result;
}

Plaintext vigenere_decrypt(const Ciphertext &cxt, const std::string &key) {
    Plaintext result = cxt;
    size_t key_len = key.length();
    size_t j = 0; // Key index

    for (size_t i = 0; i < cxt.length(); ++i) {
        char c = cxt[i];
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            char key_c = std::toupper(key[j % key_len]) - 'A';
            result[i] = (c - base - key_c + 26) % 26 + base;
            j++; // only increment when alphabetic
        }
        else {
            result[i] = c;
        }
    }
    return result;
}

} // namespace cryptcpp::classical
