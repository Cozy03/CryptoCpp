#include <classical_ciphers/caeser_cipher.hpp>
#include <classical_ciphers/vigenere_cipher.hpp>
#include <benchmark/benchmark.h>
#include <random>

/**
 * @file classical_cipher_bench.cpp
 * @brief Google Benchmark-based performance test for Classical Ciphers.
 */

using cryptcpp::Plaintext;
using cryptcpp::Ciphertext;
using namespace cryptcpp::classical;

/// Generates a random alphanumeric string of given length
std::string generate_random_text(size_t length) {
    const std::string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::string result;
    result.reserve(length);

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<> dist(0, charset.size() - 1);

    for (size_t i = 0; i < length; ++i) {
        result += charset[dist(rng)];
    }
    return result;
}

///////////////////////
// Caesar Cipher Bench
///////////////////////

static void BM_CaesarEncrypt(benchmark::State& state) {
    size_t text_size = state.range(0);
    uint8_t key = 5;
    Plaintext input = generate_random_text(text_size);

    for (auto _ : state) {
        benchmark::DoNotOptimize(caeser_encrypt(input, key));
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(text_size));
}
BENCHMARK(BM_CaesarEncrypt)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000);

static void BM_CaesarDecrypt(benchmark::State& state) {
    size_t text_size = state.range(0);
    uint8_t key = 5;
    Plaintext input = generate_random_text(text_size);
    Ciphertext encrypted = caeser_encrypt(input, key);

    for (auto _ : state) {
        benchmark::DoNotOptimize(caeser_decrypt(encrypted, key));
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(text_size));
}
BENCHMARK(BM_CaesarDecrypt)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000);

///////////////////////////
// Vigenère Cipher Bench
///////////////////////////

static void BM_VigenereEncrypt(benchmark::State& state) {
    size_t text_size = state.range(0);
    std::string key = "KEY";
    Plaintext input = generate_random_text(text_size);

    for (auto _ : state) {
        benchmark::DoNotOptimize(vigenere_encrypt(input, key));
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(text_size));
}
BENCHMARK(BM_VigenereEncrypt)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000);

static void BM_VigenereDecrypt(benchmark::State& state) {
    size_t text_size = state.range(0);
    std::string key = "KEY";
    Plaintext input = generate_random_text(text_size);
    Ciphertext encrypted = vigenere_encrypt(input, key);

    for (auto _ : state) {
        benchmark::DoNotOptimize(vigenere_decrypt(encrypted, key));
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(text_size));
}
BENCHMARK(BM_VigenereDecrypt)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000);

BENCHMARK_MAIN();
