#!/bin/bash

if [ "$#" -lt 3 ]; then
    echo -e "$0 \033[47;31mUsage: ./gen_signature.sh <control_info> <input_partial_hash> <sign_key> \033[0m"
fi

./do_sha256 $1 $2 hash.bin
#openssl rsa -text -in $(3) -out $(3).text;
openssl rsautl -sign -inkey $3 -in hash.bin -out signature.bin

