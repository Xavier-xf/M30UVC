#!/bin/bash
if (( $EUID != 0 )); then
  echo "Root is required!"
  exit 1
fi
LD_LIBRARY_PATH=. ./uvcCamera
