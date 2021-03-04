#!/bin/bash
if [ $1 -eq '0' ]; then
	make re G=1 && lldb test_list
elif [ $1 -eq '1' ]; then
	make re F=1 G=1 && ./test_list
elif [ $1 -eq '2' ]; then
	make re F=1 G=1 MAIN=1 && ./test_list
fi
