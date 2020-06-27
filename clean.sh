#!/bin/sh
set -e
. ./config.sh

for PROJECT in $PROJECTS; do
  (echo "\nMoving in $PROJECT" && cd $PROJECT && $MAKE clean)
done

rm -rf sysroot
rm -rf isodir
rm -rf os.iso
