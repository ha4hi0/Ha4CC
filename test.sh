#!/bin/bash

try(){
    expected="$1"
    input="$2"

    ./hcc "$input" > tmp.s
	cc -c testutil.c
    gcc -o tmp tmp.s testutil.o
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

try 0 "int main(){return 0;}"
try 42 "int main(){return 42;}"
try 21 "int main(){return 5+20-4;}"
try 41 "int main(){return 12 + 34- 5 +0 ;}"
try 57 "int main(){return  25 *2 + 10 - 6/2;}"
try 34 "int main(){return  (33 - 4) *2 + 45 -(50 +38/2);}"
try 2 "int main(){return  +3 -1;}"
try 10 "int main(){return  -(-3 +2) * 10 + -0;}"
try 0 "int main(){return (1!=0)*(0<3)-(1==1)+(2*3>14/2);}"
try 3  "int main(){return  (1 ==1 )*(2/1<0) + (1!=2)*(1-1>=0)*3;}"
try 51 "int main(){return  1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+2-1;}"
try 1 "int main(){int a; a=1; return a;}"
try 6 "int main(){int b; b=5;int d; d=1;int z; z=3;int a; a=b*(z-d);return 2*a/3;}"
try 11 "int main(){5+3;int n; n=10/2;int c; c=2+1;return n*c-4;}"
try 8  "int main(){return 8;return 5;}"
try 10 "int main(){int pi; pi=31415;int count; count=100*314;return 2*(pi-count)/3;}"
try 1 "int main(){if(0)return 0;return 1;}"
try 10 "int main(){int ab; ab=10; if(ab/5==2)return ab; return -10;}"
try 0 "int main(){int alpha;alpha=10;int beta; beta=0;if(alpha<beta)beta=alpha;else alpha=beta; return alpha;}"
try 24 "int main(){int fact;fact=1; int i;for(i=1;fact<10;i=i+1)fact=fact*i;return fact;}"
try 64 "int main(){int pow;pow=1;while(pow<50)pow=pow*2;return pow;}"
try 2 "int main(){int i;i=1;{i=i+1;}return i;}"
try 55 "int main(){int i;i=0;int sum;sum=0;while(i<11){sum=sum+i;i=i+1;}return sum;}"
try 64 "int main(){int i;for(i=1;i<100;i=i*2){if(i>32){return i;}}}"
try 3 "int main(){return foo1()+foo2();}"
try 10 "int main(){return foo(2, 8);}"
try 55 "int main(){return foo(1, foo(2, foo(3, foo(4, foo(5, foo(6, foo(7, foo(8, foo(9, 10)))))))));}"
try 233 "int fibo(int n){if(n==0){return 0;}else if(n==1){return 1;}else{return fibo(n-1)+fibo(n-2);}}int main(){return fibo(13);}"
try 2 "int main(){int a; int b; int c; a=2;b=1;c=0;return hoge(a, b, c);}int hoge(int b, int c, int d){return c*(b+d);}"
try 3 "int main(){int x; x=3;int y; y=&x; return *y;}"
try 3 "int main(){int x; x=3;int y; y=5;int z; z=&y+8; return *z;}"

echo OK
