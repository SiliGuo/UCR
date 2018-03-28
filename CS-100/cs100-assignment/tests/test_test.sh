#!/bin/sh
../bin/rshell << 'EOF'
test ../src
[ -d ../src ]
test -d ../src/leaf.h
[ -f ../src/leaf.h ]
exit
EOF
