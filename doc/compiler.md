# Cross-compiler install

Microcontrollers generally use a different CPU architecture than your laptop.
It's straightforward to install the 32-bit ARM C/C++ cross-compiler on popular operating systems.

Please follow the section relevant to your laptop operating system.
Note that about 2..5 gigabytes of hard drive space is required overall.

## macOS

Homebrew is popular and generally useful on macOS to get a wide variety of development and creative software packages.
Obtain Homebrew as per https://brew.sh.

Install Git, CMake build system, and ARM cross-compiler by:

```sh
brew install cmake git
brew tap ArmMbed/homebrew-formulae
brew install arm-none-eabi-gcc
```

The "brew tap" installs from "https://github.com/ARMmbed/homebrew-formulae".
If your Mac has an Apple Silicon CPU, you may need to [enable Rosetta](https://support.apple.com/en-us/HT211861).
Rosetta enables most x86 apps on Apple Silicon at nearly full performance.

## Linux

This install command gives Git, CMake, the cross-compiler, and libraries for:

* laptop/desktop with: WSL Ubuntu, Ubuntu/Debian-like distros
* full Raspberry Pi (e.g. Raspberry Pi 4)

```sh
sudo apt update
sudo apt install git make cmake g++ gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib
```

NOTE: if upon `cmake -B build` you get an immediate error about CMake being too old,
please install a newer CMake via [scripts/install_cmake_linux.sh](../scripts/install_cmake_linux.sh)

## Windows

Windows Subsystem for Linux (WSL) is useful for many projects including the Raspberry Pi Pico SDK.
WSL can be the easiest way to work with non-Windows projects on Windows.

The Ubuntu WSL process takes about 10 minutes depending on download speed.
WSL can be installed via the [Microsoft Store Ubuntu app](https://docs.microsoft.com/en-us/windows/wsl/install).
If the Microsoft Store isn't available on the computer, it is alsopossible to install [Ubuntu WSL manually](https://docs.microsoft.com/en-us/windows/wsl/install), but the Store is the method Microsoft WSL team recommends.

[WSL can access](https://docs.microsoft.com/en-us/windows/wsl/filesystems)
the native Windows filesystem.
WSL sees the native Windows filesystem "C:" in WSL via "/mnt/c".
To make it easier to copy files to the Pico, we suggest for this project to use the native Windows drive under "/mnt/c" from WSL.
Then you can use Windows File Explorer to
[drag and drop .uf2 file to Pico](./upload.md).

The cross-compiler install on WSL Ubuntu is just like plain Linux in the section above.

To make switching between Windows and WSL easier, we optionally use
[Windows Terminal](https://docs.microsoft.com/en-us/windows/terminal/install).

### Alternative: Visual Studio

The Visual Studio cross-compiler setup is described in Section 9.2 of the
[Pico install guide](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf).
I used WSL as above instead.
