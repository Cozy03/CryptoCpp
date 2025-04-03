#include <classical_ciphers/caeser_cipher.hpp>
#include <cctype>

namespace cryptcpp::classical {

Ciphertext caeser_encrypt(const Plaintext &pln, uint8_t key) {
    Plaintext result = pln;
    uint8_t alpha_key = key % 26;
    uint8_t digit_key = key % 10;

    for (char &c : result) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            c = (c - base + alpha_key) % 26 + base;
        }
        else if (std::isdigit(c)) {
            c = (c - '0' + digit_key) % 10 + '0';
        }
    }
    return result;
}

Plaintext caeser_decrypt(const Ciphertext &cxt, uint8_t key) {
    Ciphertext result = cxt;
    uint8_t alpha_key = key % 26;
    uint8_t digit_key = key % 10;

    for (char &c : result) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            c = (c - base - alpha_key + 26) % 26 + base;
        }
        else if (std::isdigit(c)) {
            c = (c - '0' - digit_key + 10) % 10 + '0';
        }
    }
    return result;
}

} // namespace cryptcpp::classical
