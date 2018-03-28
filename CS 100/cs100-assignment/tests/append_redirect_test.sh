#!/bin/sh
../bin/rshell << 'EOF'
echo This is the second line. >> ../test2.txt
cat ../test2.txt
cat < ../test2.txt >> ../test3.txt
cat ../test3.txt
exit
EOF
