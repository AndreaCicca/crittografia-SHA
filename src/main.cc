#include "sha1.hh"
#include <iomanip>
#include <iostream>
#include <openssl/sha.h>
#include <vector> // Aggiunto questo include

void cripto_test_sha1(const std::string &message) {
  uint8_t digest[cripto::SHA1_DIGEST_SIZE];

  cripto::SHA1 sha1;

  sha1.update(reinterpret_cast<const uint8_t *>(message.data()),
              message.length());
  sha1.final(digest);

  std::string result =
      cripto::SHA1::toHexString(digest, cripto::SHA1_DIGEST_SIZE);
  std::cout << "Cripto  SHA1: " << result << std::endl;
}

void openssl_test_sha1(const std::string &message) {
  unsigned char hash[SHA_DIGEST_LENGTH];
  SHA1(reinterpret_cast<const unsigned char *>(message.data()),
       message.length(), hash);

  std::string hash_string = cripto::SHA1::toHexString(hash, SHA_DIGEST_LENGTH);
  std::cout << "OpenSSL SHA1: " << hash_string << std::endl;
}

int main() {
  std::vector<std::string> test_cases = {
      "",
      "a",
      "abc",
      "message digest",
      "abcdefghijklmnopqrstuvwxyz",
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
      "123456789012345678901234567890123456789012345678901234567890123456789012"
      "34567890",
      "Nel mezzo del cammin di nostra vita mi ritrovai per una selva oscura, "
      "ché la diritta via era smarrita."};

  for (const auto &test : test_cases) {
    std::cout << "Testing message: \"" << test << "\"" << std::endl;
    cripto_test_sha1(test);
    openssl_test_sha1(test);
    std::cout << std::endl;
  }

  return 0;
}