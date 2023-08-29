#! /usr/bin/bash

i=0
if [ ! -d "Result" ]; then
	mkdir "Result"
else
	if [ -f "Result/output.txt" ]; then
		rm "Result/output.txt"
	fi
fi

if [ -f "input.txt" ]; then
	while true; do
		read -r line
		if [ "$line" == "" ]; then
			break
		fi
		i+=1
		IFS=' ' read -ra words <<<"$line"
		a=$((words[0]))
		b=$((words[1]))
		if [ "${words[2]}" == "product" ]; then
			ans=$((a * b))
			op="Result of product ${a} ${b}: "
		elif [ "${words[2]}" == "compare" ]; then
			op="Result of compare ${a} ${b}: "
			if [ $a -gt $b ]; then
				ans=$a
			else
				ans=$b
			fi
		elif [ "${words[2]}" == "xor" ]; then
			op="Result of xor ${a} ${b}: "
			ans=$((a ^ b))
		fi
		echo "$op$ans" >>"Result/output.txt"
	done <"input.txt"
else
	echo "input.txt does not exists"
fi
