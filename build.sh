#!/bin/sh
set -e
. ./headers.sh

for PROJECT in $PROJECTS; do
  (echo "\nMoving in $PROJECT" && cd $PROJECT && DESTDIR="$SYSROOT" $MAKE install)
done
