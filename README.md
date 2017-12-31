# libsodium-file-crypter
Linux file encryption utility written in C using libsodium

* Current version ```libsodium-file-crypter version 1.0.0```

## Requirements
#### 1. Libsodium
[Libsodium installation instructions from the official docs](https://download.libsodium.org/doc/installation/)

1. Download source (latest stable preferred) tarball from [HERE](https://download.libsodium.org/libsodium/releases/)
2. Unpack ```tar -xvf LATEST.tar.gz```
3. ```cd libsodium-stable/```
4. ```./configure```
5. ```make && make check```
6. ```sudo make install``` or execute ```make install``` after switching with ```su``` to root
7. You may want to run ```ldconfig``` that creates the necessary links and cache to the most recent shared libraries

Libraries will be installed in ```/usr/local/lib```

#### 2. CMake

Refer to official docs for installation [HERE](https://cmake.org/install/)

* Download binary from [HERE](https://cmake.org/download/)
* Compile from source. Sources available on download page [HERE](https://cmake.org/download/)
    1. ```./bootstrap```
    2. ```make```
    3. ```sudo make install``` or execute ```make install``` after switching with ```su``` to root
* Install from repository
    1. For Fedora and similar distributions run ```dnf install cmake``` after switching with ```su``` to root

## Compiling from source

1. Make sure all requirements like libsodium and cmake are satisfied
2. Clone git repository with ```git clone https://github.com/jpiechowka/libsodium-file-crypter.git```
3. Switch to the downloaded repository directory ```cd libsodium-file-crypter```
4. Run ```cmake .```
5. Run ```make```

[![asciicast](https://asciinema.org/a/154905.png)](https://asciinema.org/a/154905)

## How to use

To see help message run with ```-?``` or ```--help``` options

```
Usage: libsodium-file-crypter [OPTION...] FILE PASSWORD
A file encryption utility written in C using libsodium

  -d, --decrypt              Decrypt the specified file. Specifying operation
                             mode is mandatory for program to run
  -e, --encrypt              Encrypt the specified file. Specifying operation
                             mode is mandatory for program to run
  -f, --force                Force overwrite of output file if it already
                             exists
  -o, --output=FILE          Specify output file instead of default:
                             output.crypt
  -v, --verbose, --debug     Increase verbosity - show debug messages
  -?, --help                 Give this help list
      --usage                Give a short usage message
  -V, --version              Print program version

Mandatory or optional arguments to long options are also mandatory or optional
for any corresponding short options.

Report bugs to https://github.com/jpiechowka/libsodium-file-crypter/issues.

```

1. **FILE** - mandatory argument specifying file to operate on
2. **PASSWORD** - mandatory argument specifying password used to perform encryption/decryption
3. **\[-e/--encrypt] or \[-d/--decrypt]** - specify mode of operation. One of this options in mandatory for program to work.
4. If no output file is provided with **\[-o/--output]** default output file will be used

#### Usage

Run with ```--usage``` option

```
Usage: libsodium-file-crypter [-defv?V] [-o FILE] [--decrypt] [--encrypt]
            [--force] [--output=FILE] [--verbose] [--debug] [--help] [--usage]
            [--version] FILE PASSWORD
```

#### Example usage

1. Encrypting example *plaintext.txt* file using ```super-secret-pass-123``` as password
    * ```./libsodium-file-crypter -v -e -o encrypted.txt plaintext.txt super-secret-pass-123```
        * **-v** for verbose mode
        * **-e** to encrypt the specified file
        * **-o encrypted.txt** to provide output file path
        * **plaintext.txt** is the file to encrypt
        * **super-secret-pass-123** is the password provided

    [![asciicast](https://asciinema.org/a/154917.png)](https://asciinema.org/a/154917)

2. Decrypting previously encrypted file
    * ```./libsodium-file-crypter -v -d -f -o plaintext.txt encrypted.txt super-secret-pass-123```
        * **-v** for verbose mode
        * **-d** to decrypt the specified file
        * **-f** option is used to force overwrite of the previously existing output file
        * **-o plaintext.txt** to provide output file path. Note that this file path is the same as the old plaintext.txt file we encrypted before
        * **encrypted.txt** is the file to decrypt
        * **super-secret-pass-123** is the password provided

    [![asciicast](https://asciinema.org/a/154918.png)](https://asciinema.org/a/154918)

## TODO

1. Investigate how to generate and store salt when using Argon2 for file encryption/decryption
2. Implement generating salt and storing it somehow for file encryption/decryption purposes