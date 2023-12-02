#!/bin/bash
export PKG_CONFIG_PATH=/usr/lib/pkgconfig/ && gcc -g *.c source/*.c -o main.exe $(pkg-config --cflags --libs jansson) && ./main.exe $@
