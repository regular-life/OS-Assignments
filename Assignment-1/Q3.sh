#! /usr/bin/bash

echo "Enter the input file name"
read -r fileName
i=0
if [ ! -d "Result" ]; then
	mkdir "Result"
else
	if [ -f "Result/output.txt" ]; then
		rm "Result/output.txt"
	fi
fi

if [ -f "$fileName" ]; then
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
		elif [ "${words[2]}" == "compare" ]; then
			if [ $a -gt $b ]; then
				ans=$a
			else
				ans=$b
			fi
		else
			ans=$((a ^ b))
		fi
		echo "$ans" >>"Result/output.txt"
	done <"$fileName"
else
	echo "$fileName does not exists"
fi
