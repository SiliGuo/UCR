#!/bin/sh
../bin/rshell << 'EOF'
echo hello | tr a-z A-Z
echo hello # | tr a-z A-Z
cat < ../test.txt | tr A-Z a-z | tee ../test2.txt | tr a-z A-Z > ../test3.txt
cat ../test2.txt
cat ../test3.txt
cat < ../test3.txt | tr A-Z a-z && ls
exit
EOF
