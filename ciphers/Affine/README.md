# AffineCipher

[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](https://github.com/0x000N3X4N/cybersecurity/issues)|[![Build Status](https://travis-ci.org/0x000N3X4N/cybersecurity.svg?branch=master)](https://travis-ci.org/0x000N3X4N/cybersecurity)|[![Version](https://img.shields.io/badge/version-0.1-orange.svg?style=plastic&logo=appveyor)](https://github.com/0x000N3X4N/cybersecurity/releases)

> https://en.wikipedia.org/wiki/Affine_cipher

# Usage

- ../exmpl/msg.txt contains the message to be encrypted/decrypted

- ../exmpl/encryptedMsg.txt contains a valid encrypted message

- ../exmpl/decryptedMsg.txt contains a valid decrypted message

@template: ./AffineCipher [a] [b] e/d
~~~
./AffineCipher 21 8 e
~~~

# Building from sources

**Requirements:**
- [cmake](https://cmake.org/) **minimum version 3.9**
~~~
./build.sh
~~~
