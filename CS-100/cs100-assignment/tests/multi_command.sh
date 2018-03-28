#!/bin/sh
../bin/rshell << 'EOF'
ls && ls -a && echo hello
ls - && ls && echo nothing
echo hello || rm -d test && echo rm not work
ls - || echo run && rm -d test;
ls -; ls -a -l && echo run ; 
exit
EOF
