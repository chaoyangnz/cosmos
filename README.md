# cosmos

## what is it?
Cosmos is my world in bare bone - a kernel running as you like. This is my own attempt to gain back my interest in system programming.

## install tools

```
# install cmake, qemu
brew install qemu cmake

# install cross build toolchain
brew install i386-elf-binutils i386-elf-gcc i386-elf-gdb i386-elf-grub
```

## Build & Run

```
cd kernel
mkdir cmake-build-debug
cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" ./cmake-build-debug
cd cmake-build-debug
make
```

## Debug

Once the kernel is running, you can use GDB to remote debug in port 1234. CLion has a good support of visual debugging.
Create a Remote Debug config, and set break points in code. It rolls!