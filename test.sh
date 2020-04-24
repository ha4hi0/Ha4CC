#!/bin/bash

./Ha4CC _test.c > _test.s
gcc -c testutil.c
gcc -o _test _test.s testutil.o -g
./_test
echo FINISH
