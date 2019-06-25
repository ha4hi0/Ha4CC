#!/bin/bash

try(){
    expected="$1"
    input="$2"

    ./hcc "$input" > tmp.s
    gcc -o tmp tmp.s
    ./tmp
    actual="$?"

    echo "$input"
    if [ "$actual" = "$expected" ]; then
        echo "=> $actual"
    else
        echo "$expected expected, but got $actual"
        exit 1
    fi
}

try 0 "0;"
try 42 "42;"
try 21 '5+20-4;'
try 41 " 12 + 34- 5 +0 ;"
try 57 " 25 *2 + 10 - 6/2;"
try 34 " (33 - 4) *2 + 45 -(50 +38/2);"
try 2 " +3 -1;"
try 10 " -(-3 +2) * 10 + -0;"
try 0 "(1!=0)*(0<3)-(1==1)+(2*3>14/2);"
try 3  " (1 ==1 )*(2/1<0) + (1!=2)*(1-1>=0)*3;"
try 51 " 1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+2-1;"
try 1 "a=1;"
try 6 "b=5;d=1;z=3;a=b*(z-d);2*a/3;"
try 11 "5+3;n=10/2;c=2+1;return n*c-4;"
try 8  "return 8;return 5;"

echo OK
