#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/os.kernel isodir/boot/os.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "os" {
	multiboot /boot/os.kernel
}
EOF
grub-mkrescue -o os.iso isodir
