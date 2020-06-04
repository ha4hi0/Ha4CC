int try(int no, int expected, int actual){
	if(expected != actual){
		printf("[ERROR] test%d: %d expected, but got %d\n", no, expected, actual);
	}
}

int test0(){
	return 0;
}

int test1(){
	return 42;
}

int test2(){
	return 5+20-4;	
}

int test3(){
	return 12 + 34- 5 +0 ;
}

int test4(){
	return  25 *2 + 10 - 6/2;
}

int test5(){
	return  (33 - 4) *2 + 45 -(50 +38/2);
}

int test6(){
	return  +3 -1;
}

int test7(){
	return  -(-3 +2) * 10 + -0;
}

int test8(){
	return (1!=0)*(0<3)-(1==1)+(2*3>14/2);
}

int test9(){
	return  (1 ==1 )*(2/1<0) + (1!=2)*(1-1>=0)*3;
}

int test10(){
	return  1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+2-1;
}

int test11(){
	int a=1; return a;
}

int test12(){
	int b=5;int d=1;int z=3;int a=b*(z-d);return 2*a/3;
}

int test13(){
	5+3;int n=10/2;int c=2+1;return n*c-4;
}

int test14(){
	return 8;return 5;
}

int test15(){
	int pi=31415;int count=100*314;return 2*(pi-count)/3;
}

int test16(){
	if(0)return 0;return 1;
}

int test17(){
	int ab=10; if(ab/5==2)return ab; return -10;
}

int test18(){
	int alpha=10;int beta=0;if(alpha<beta)beta=alpha;else alpha=beta; return alpha;
}

int test19(){
	int fact=1; for(int i=1;fact<10;i=i+1)fact=fact*i;return fact;
}

int test20(){
	int pow=1;while(pow<50)pow=pow*2;return pow;
}

int test21(){
	int i=1;{i+=1;}return i;
}

int test22(){
	int i=0;int sum=0;while(i<11){sum=sum+i;i=i+1;}return sum;
}

int test23(){
	for(int i=1;i<100;i=i*2){if(i>32){return i;}}
}

int test24(){
	return foo1()+foo2();
}

int test25(){
	return foo(2, 8);
}

int test26(){
	return foo(1, foo(2, foo(3, foo(4, foo(5, foo(6, foo(7, foo(8, foo(9, 10)))))))));
}

int fibo(int n){
	if(n==0){
		return 0;
	}else if(n==1){
		return 1;
	}else{
		return fibo(n-1)+fibo(n-2);
	}
}

int test27(){
	return fibo(13);
}

int test28(){
	int a=2; int b=1; int c=0; return hoge(a, b, c);
}

int hoge(int b, int c, int d){return c*(b+d);}

int test29(){
	int x=3;int *y=&x; return *y;
}

int test30(){
	int x=3;int y=5;int *z=&y+1; return *z;
}

int test31(){
	int x; int *y; y=&x; *y=3; return x;
}

int test32(){
	int *p; alloc4(&p, 1, 2, 4, 8); int *q=p+3; return *q;
}

int test33(){
	int *p; alloc4(&p, 0, 1, 2, 3); for(int i=0; i<4; i=i+1){*p=4+i; p=p+1;}return *(p-2);
}

int test34(){
	;int i;i=0;;;return i;;;
}

int test35(){
	return sizeof(0);
}

int test36(){
	int **x; return sizeof(*(*(x+4)-2));
}

int test37(){
	int x= sizeof(x); return sizeof(&x)*sizeof(x);
}

int test38(){
	int i=0; {i=10; int i; i=100;} return i;
}

int test39(){
	int ary[10]; *(ary + 5) = 4; return *(ary + 5); 
}

int test40(){
	int ary[10]; for (int i = 0; i < 10; i=i+1) *(i + ary) = i; return *(ary + 5); 
}

int test41(){
	int ary[100]; for(int i=0; i<100; i=i+1){if(i==0)ary[i]=i;else ary[i]=ary[i-1]+i;} return 10[ary];
}

int a42;
int test42(){
	return a42;
}

int a43;
int test43(){
	a43=5; return a43;
}

int a44;
int foo44(int *x){
	*x=100; int a=10; return a;
}

int test44(){
	int *x=&a44; foo44(x); return a44;
}

int a45[10];

int init45(){
	for(int i=1; i<10; i=i+1){a45[i]=a45[i-1]+i;} return 0;
}

int test45(){
	init45(); return a45[9];
}

int test46(){
	char x[3]; x[0]=-1; x[1]=2; x[2]=-5; int y=1; return x[1]+y;
}

int test47(){
	char *str="hoge"; return str[0];
}

int test48(){
	int a; if(1>0){a=1;}else{a=0;} return a;
}

int test49(){
	char *a="abc"; char *b="zyx"; char *str; if(a[0]<b[0]){str=a;}else{str=b;} return str[2];
}

int test50(){
	// line comment---
	return 2;
}

int test51(){
	// line comment
	return 
	// line
		0
	// comment
		;
}

int test52(){
	/* BLOCK COMMENT */
	/* 1+2+3+4+5+6+7+8+9+10=55*/
	return 55;
}

int test53(){
	/*
	   This is a test for block comments.
	 */
	return 53;
	/* 
	   // line comment/
	   /*
	*/
}

int test54(){
	return 33%4;
}

int test55(){
	return -111111%23456;
}

int test56(){
	int a=5;
	int b=-10;
	int c=20;
	if(a < b && a < c){
		return a;
	}else if(b < a && b < c){
		return b;
	}else{
		return c;
	}
}

int test57(){
	return 0||1&&1||0&&1&&2;
}

int test58(){
	int a=-10;
	a += 68;
	return a;
}

int test59(){
	int b=30;
	b-=-29;
	return b;
}

int test60(){
	int c=12;
	c*=5;
	return c;
}

int test61(){
	int d=3905;
	d/=63;
	return d;
}

int test62(){
	char a='a';
	return a;
}

int test63(){
	char *str;
	str = "abc";
	return str[0]=='a'&&str[1]=='b'&&str[2]=='c';
}

int test64(){
	int num = 10;
	char a = 'a';
	a += num;
	return a;
}

int test65(){
	char k = test64();
	if(k == 'k'){
		return 'y';
	}else{
		return 'n';
	}
}

int test66(){
	int arr[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	return arr[5];
}

int test67(){
	int test[10] = {test1(), test2(), test3(), test4(), test5(), test6(), test7(), test8(), test9(), test10()};
	return test[9];
}

int test68(){
	int arr[10] = {1};
	for(int i=1; i<10; i=i+1){
		arr[i] = arr[i-1]+arr[i];
	}
	for(int i=1; i<10; i=i+1){
		arr[i] = arr[i-1]+arr[i];
	}
	return arr[9];
}

int test69(){
	int arr[3] = {0, 0, 1, 1, 2, 2};
	return sizeof(arr);
}

int main(){
	try(0, 0, test0());
	try(1, 42, test1());
	try(2, 21, test2());
	try(3, 41, test3());
	try(4, 57, test4());
	try(5, 34, test5());
	try(6, 2, test6());
	try(7, 10, test7());
	try(8, 0, test8());
	try(9, 3, test9());
	try(10, 51, test10());
	try(11, 1, test11());
	try(12, 6, test12());
	try(13, 11, test13());
	try(14, 8, test14());
	try(15, 10, test15());
	try(16, 1, test16());
	try(17, 10, test17());
	try(18, 0, test18());
	try(19, 24, test19());
	try(20, 64, test20());
	try(21, 2, test21());
	try(22, 55, test22());
	try(23, 64, test23());
	try(24, 3, test24());
	try(25, 10, test25());
	try(26, 55, test26());
	try(27, 233, test27());
	try(28, 2, test28());
	try(29, 3, test29());
	try(30, 3, test30());
	try(31, 3, test31());
	try(32, 8, test32());
	try(33, 6, test33());
	try(34, 0, test34());
	try(35, 4, test35());
	try(36, 4, test36());
	try(37, 32, test37());
	try(38, 10, test38());
	try(39, 4, test39());
	try(40, 5, test40());
	try(41, 55, test41());
	try(42, 0, test42());
	try(43, 5, test43());
	try(44, 100, test44());
	try(45, 45, test45());
	try(46, 3, test46());
	try(47, 104, test47());
	try(48, 1, test48());
	try(49, 99, test49());
	try(50, 2, test50());
	try(51, 0, test51());
	try(52, 55, test52());
	try(53, 53, test53());
	try(54, 1, test54());
	try(55, -17287, test55());
	try(56, -10, test56());
	try(57, 1, test57());
	try(58, 58, test58());
	try(59, 59, test59());
	try(60, 60, test60());
	try(61, 61, test61());
	try(62, 97, test62());
	try(63, 1, test63());
	try(64, 107, test64());
	try(65, 121, test65());
	try(66, 5, test66());
	try(67, 51, test67());
	try(68, 10, test68());
	try(69, 12, test69());
}

