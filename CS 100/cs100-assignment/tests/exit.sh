#!/bin/sh
../bin/rshell << 'EOF'
ls && echo hello || ls -a
exit
EOF
