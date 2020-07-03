#!/bin/sh
set -e
. ./iso.sh

if [ "$1" = "debug" ]; then
    qemu-system-$(./target-triplet-to-arch.sh $HOST) -s -S -cdrom os.iso
else
    qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom os.iso
fi
