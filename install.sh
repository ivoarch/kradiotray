#!/bin/bash

clean() {
    rm kradiotray 2>/dev/null
}

compile() {
    gcc -Wall -g kradiotray.c -o kradiotray `pkg-config --cflags --libs gtk+-2.0`
}

clean
compile

exit 0
