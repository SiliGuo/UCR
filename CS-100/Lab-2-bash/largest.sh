#!/bin/sh
#If user's entries less than 2, error message
if [ $# -le 2 ]; then
    echo "Error: Need enter three numbers!"
fi
#If user's entries greater than 4, error message
if [ $# -ge 4 ]; then
    echo "Error: Only allow  enter three numbers!"
fi
#If user's entries equals to 3
if [ $# -eq 3 ]; then
	#If $1 is largest, output $1
    if [ $1 -ge $2 ] && [ $1 -ge $3 ]; then
        echo $1
    else
		#If $2 is largest, output $2
		if [ $2 -ge $1 ] && [ $2 -ge $3 ]; then
			echo $2
		#If $3 is largest, output $3
		else
			echo $3
		fi
	fi
fi
