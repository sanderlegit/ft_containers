#!/bin/bash
if [ "$2" == "lldb" ]; then
	make re NO_FT=1 G=1 && lldb test_$1
elif [ "$2" == "fsan" ]; then
	make re NO_FT=1 F=1 G=1 && ./test_$1
else
	make re && ./test_$1
fi
