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

try 0 "main(){return 0;}"
try 42 "main(){return 42;}"
try 21 "main(){return 5+20-4;}"
try 41 "main(){return 12 + 34- 5 +0 ;}"
try 57 "main(){return  25 *2 + 10 - 6/2;}"
try 34 "main(){return  (33 - 4) *2 + 45 -(50 +38/2);}"
try 2 "main(){return  +3 -1;}"
try 10 "main(){return  -(-3 +2) * 10 + -0;}"
try 0 "main(){return (1!=0)*(0<3)-(1==1)+(2*3>14/2);}"
try 3  "main(){return  (1 ==1 )*(2/1<0) + (1!=2)*(1-1>=0)*3;}"
try 51 "main(){return  1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+2-1;}"
try 1 "main(){return a=1;}"
try 6 "main(){b=5;d=1;z=3;a=b*(z-d);return 2*a/3;}"
try 11 "main(){5+3;n=10/2;c=2+1;return n*c-4;}"
try 8  "main(){return 8;return 5;}"
try 10 "main(){pi=31415;count=100*314;return 2*(pi-count)/3;}"
try 1 "main(){if(0)return 0;return 1;}"
try 10 "main(){ab=10; if(ab/5==2)return ab; return -10;}"
try 0 "main(){ alpha=10;beta=0;if(alpha<beta)beta=alpha;else alpha=beta; return alpha;}"
try 24 "main(){fact=1; for(i=1;fact<10;i=i+1)fact=fact*i;return fact;}"
try 64 "main(){pow=1;while(pow<50)pow=pow*2;return pow;}"
try 2 "main(){i=1;{i=i+1;}return i;}"
try 55 "main(){i=0;sum=0;while(i<11){sum=sum+i;i=i+1;}return sum;}"
try 64 "main(){for(i=1;i<100;i=i*2){if(i>32){return i;}}}"
try 3 "main(){return foo1()+foo2();}"
try 10 "main(){return foo(2, 8);}"
try 55 "main(){return foo(1, foo(2, foo(3, foo(4, foo(5, foo(6, foo(7, foo(8, foo(9, 10)))))))));}"
try 233 "fibo(n){
	if(n==0){
		return 0;
	}else if(n==1){
		return 1;
	}else{
		return fibo(n-1)+fibo(n-2);
	}
}
main(){
	return fibo(13);
}"

echo OK
