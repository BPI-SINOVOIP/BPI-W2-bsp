../tools/RtSSL/RtSSL enc -d -aes_128_ecb -i hwsetting_header_enc.bin -o hw_header -k `hexdump -e '8/1 "%02x"' ../image/aes_128bit_key.bin`
../tools/RtSSL/RtSSL enc -d -aes_128_ecb -i hwsetting.bin -o hw -k `hexdump -e '8/1 "%02x"' ../image/aes_128bit_key.bin`
../tools/RtSSL/RtSSL enc -d -aes_128_ecb -i fsbl.bin -o fsbl -k `hexdump -e '8/1 "%02x"' ../image/aes_128bit_key.bin`
../tools/RtSSL/RtSSL enc -d -aes_128_ecb -i fsbl_os.bin -o fsbl_os -k `hexdump -e '8/1 "%02x"' ../image/aes_128bit_key.bin`
../tools/RtSSL/RtSSL enc -d -aes_128_ecb -i uboot.bin -o boot -k `hexdump -e '8/1 "%02x"' ../image/aes_128bit_key.bin`
../tools/RtSSL/RtSSL enc -d -aes_128_ecb -i rescue.bin -o rescue -k `hexdump -e '8/1 "%02x"' ../image/aes_128bit_key.bin`
