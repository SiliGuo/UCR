#!/bin/sh
../bin/rshell << 'EOF'
cat < ../test.txt
cat < ../test5.txt || ls -l
exit
EOF
