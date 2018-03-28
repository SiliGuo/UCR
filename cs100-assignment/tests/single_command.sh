#!/bin/sh
../bin/rshell << 'EOF'
ls
ls -a
echo hello
mkdir test
exit
EOF
