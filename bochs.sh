#!/bin/sh

. ./iso.sh

BOCHS_CONFIG_FILE=bochs/bochsrc.txt

bochs -f ${BOCHS_CONFIG_FILE} -q
