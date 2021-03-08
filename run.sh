#!/bin/bash
if [ "$1" == "lldb" ]; then
	make re VERBOSE=1 G=1 && lldb test_list
elif [ "$1" == "fsan" ]; then
	make re VERBOSE=1 F=1 G=1 && ./test_list
elif [ "$1" == "main" ]; then
	make re F=1 G=1 MAIN=1 && ./test_list
else
	make re && ./test_list
fi
