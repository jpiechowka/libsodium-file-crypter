# libsodium-file-crypter
A file encryption utility written in C using libsodium

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