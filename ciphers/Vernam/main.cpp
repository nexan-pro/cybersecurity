#include <iostream>
#include <fstream>
#include <time.h>
#include <sys/stat.h>

#define KEY_SIZE 2000

namespace {
  std::string& readFromFile(std::ifstream& in, std::string& contentOfFile) {
    in.seekg(0, std::ios::end);
    unsigned long long length = in.tellg();
    contentOfFile.resize(length);
    in.seekg(0, std::ios::beg);
    in.read(const_cast<char*>(contentOfFile.c_str()), length);
    return contentOfFile;
  }

  inline bool exist(const std::string name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
  }

  inline void writeToFile(std::string& data, std::string filename) {
    std::ofstream out(filename);
    out << data;
    out.close();
  }
}

class Vernam {
public:
  Vernam() = default;
  inline std::string encrypt(std::string& src_text, std::string& key);
};

int main() {
  srand(time(0));
  std::ifstream in("message.txt");
  if (in && exist("key_for_decrypt.txt") && exist("encrypted_msg.txt")) {
    std::cout << "\"key.txt\" file and \"encrypted_msg.txt\" are exist, starting to decrypt\n";
    std::ifstream fkey("key_for_decrypt.txt");
    std::ifstream fencrypted_MSG("encrypted_msg.txt");
    if (fkey && fencrypted_MSG) {
      std::string encryptedData;
      encryptedData = readFromFile(fencrypted_MSG, encryptedData);
      std::string key;
      key = readFromFile(fkey, key);
      Vernam obj;
      std::string decrypted_MSG = obj.encrypt(encryptedData, key);
      std::cout << "decryptedMSG is: " << decrypted_MSG;
      writeToFile(decrypted_MSG, "decrypted_msg.txt");
    } else std::cerr << "Error to open files: \"key.txt\" or \"encrypted_msg.txt\"\n";
  }
  else {
    std::cout << "starting generating key\n";
    std::ofstream out("key_for_encrypt.txt");
    std::ofstream foutd("key_for_decrypt.txt");;
    std::string contentOfMSG;
    contentOfMSG = readFromFile(in, contentOfMSG);
    std::string key;
    key.resize(KEY_SIZE);
    for (size_t c = 0; c < KEY_SIZE; c++)
      key[c] = rand() % 127 + 32;
    std::string encryptKey = key;
    for (int i = 0; i < contentOfMSG.size(); i++)
      encryptKey.erase(i, 1);
    if (exist("key_for_encrypt.txt")) {
      out << encryptKey;
      foutd << key;
      foutd.close();
      out.close();
      std::cout << "Successfully, written to file \"key_for_encrypt.txt\"\n";
    } else std::cerr << "Error to create output file!\n";

    Vernam obj;
    std::string encryptedMSG = obj.encrypt(contentOfMSG, key);
    writeToFile(encryptedMSG, "encrypted_msg.txt");
  }
  return 0;
}

inline std::string Vernam::encrypt(std::string& src_text, std::string& key) {
  std::string encryptedMSG;
  encryptedMSG.resize(src_text.size());
  for (size_t c = 0; c < src_text.size(); c++)
    encryptedMSG[c] = src_text[c] ^ key[c];
  return encryptedMSG;
}