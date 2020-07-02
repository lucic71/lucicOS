#!/bin/sh

. ./iso.sh
(./sym.sh "kernel/os.kernel")

BOCHS_CONFIG_FILE=bochs/bochsrc.txt

bochs -f ${BOCHS_CONFIG_FILE} -q
