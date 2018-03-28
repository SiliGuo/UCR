#!/bin/sh
../bin/rshell << 'EOF'
echo A && echo B || echo C && echo D
(echo A && echo B) || (echo C && echo D)
ls && (( echo A || echo B); ls -l) || echo D
ls -a && ( echo hello || echo hi;
())
exit
EOF
