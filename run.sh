#!/bin/bash
if [ $1 -eq '0' ]; then
	make re G=1 && lldb test_list
else
	make re F=1 G=1 && ./test_list
fi
