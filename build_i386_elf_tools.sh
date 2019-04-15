#!/bin/bash

# see also https://articles.jaredcamins.com/building-a-kernel-for-a-toy-os-on-os-x-6002ea8a69b4
# and https://os.phil-opp.com/cross-compile-binutils/
# https://wiki.osdev.org/GCC_Cross-Compiler

export PREFIX="/usr/local/i386-elf"
export TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"

mkdir /tmp/src
cd /tmp/src
curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.26.tar.gz # If the link 404's, look for a more recent version
tar xf binutils-2.26.tar.gz
mkdir binutils-build
cd binutils-build
../binutils-2.26/configure --target=$TARGET --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=$PREFIX 2>&1 | tee binutils.configure.log
sudo make all install 2>&1 | tee binutils.make.log