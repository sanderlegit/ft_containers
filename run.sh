#!/bin/bash
if [ "$2" == "lldb" ]; then
	echo "make re CONT=$1 NO_FT=1 G=1 && lldb test_$1"
	make re CONT=$1 NO_FT=1 G=1 && lldb test_$1
elif [ "$2" == "fsan" ]; then
	echo "make re CONT=$1 NO_FT=1 F=1 G=1 && ./test_$1"
	make re CONT=$1 NO_FT=1 F=1 G=1 && ./test_$1
elif [ "$2" == "main" ]; then
	echo "make re CONT=$1 NO_FT=1 MAIN=1 F=1 G=1 && ./test_$1"
	make re CONT=$1 NO_FT=1 MAIN=1 F=1 G=1 && ./test_$1
else
	echo "make re CONT=$1 && ./test_$1"
	make re CONT=$1 && ./test_$1
fi
