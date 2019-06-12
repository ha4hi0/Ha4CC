#!/bin/bash

try(){
    expected="$1"
    input="$2"

    ./hcc "$input" > tmp.s
    gcc -o tmp tmp.s
    ./tmp
    actual="$?"

    if [ "$actual" = "$expected" ]; then
        echo "$input => $actual"
    else
        echo "$expected expected, but got $actual"
        exit 1
    fi
}

try 0 0
try 42 42
try 21 '5+20-4'
try 41 " 12 + 34- 5 +0 "
try 57 " 25 *2 + 10 - 6/2"
try 34 " (33 - 4) *2 + 45 -(50 +38/2)"
try 2 " +3 -1"
try 10 " -(-3 +2) * 10 + -0"

echo OK
