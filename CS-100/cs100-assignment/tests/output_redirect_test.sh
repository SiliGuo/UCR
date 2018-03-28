#!/bin/sh
../bin/rshell << 'EOF'
echo Hello World > ../test2.txt
cat ../test2.txt
cat < ../test.txt > ../test2.txt
cat ../test2.txt
exit
EOF
