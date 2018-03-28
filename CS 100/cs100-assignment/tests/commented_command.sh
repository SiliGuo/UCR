#!/bin/sh
../bin/rshell << 'EOF'
ls -a;
ls #-a
echo hello # world && ls -a -l
test -d ../src/rshell.cpp
test -d ../src#/rshell.cpp
(ls || ls -l) && echo hello
(ls || ls #-l) && echo hello
exit
EOF
