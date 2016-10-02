# armv8l-toolchain-mac
A cross-compiler toolchain for macOS (10.12) host and armv8l-linux-gnueabihf target optimized for cortex-a53 (Raspberry Pi 3).

#### Installation
Checkout to /usr/local/armv8l-unknown-linux-gnueabihf and add /usr/local/armv8l-unknown-linux-gnueabihf/bin to PATH.

#### Components and Versions
* gcc 6.2.0, glibc 2.24, binutils 2.26 (built with crosstool-ng)
* boost 1.62.0
* opencv 3.1.0
* Qt 5
* system libraries (X11, OpenGL) are taken from FedBerry 24
