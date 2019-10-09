#! /usr/bin/perl

#########################################################################
#
#  split_AES_key.pl
#
#  Split AES key string to C define style 
#
#########################################################################
#
#  Usage:
#  	./split_AES_key.pl <AES key>
#
#  Example:
#  	./split_AES_key.pl ABCDABCD135713572467246822222222
#
#  Output:
# 	Config_Secure_AES_IMG_KEY0=0xABCDABCD
#	Config_Secure_AES_IMG_KEY1=0x13571357
#	Config_Secure_AES_IMG_KEY2=0x24672468
#	Config_Secure_AES_IMG_KEY3=0x22222222
#
#  Note:
#	Input key length must be 32 hex characters long.
#
#########################################################################

my $input=$ARGV[0];

# check input AES key length
chomp($input);
die "invalid AES key length!" if (length($input) != 32); 

print "Config_Secure_AES_IMG_KEY_STR=\"$input\"\n";

# split AES key into 4 integer defines
for ($i=0, $j=0; $j<length($input); $i++, $j+=8) {
	print "Config_Secure_AES_IMG_KEY$i=0x" . substr($input, $j, 8) . "\n";
}

# split AES key in reverse order (from tail to head)
#for ($i=0, $j=8; $j<=length($input); $i++, $j+=8) {
#	print "Config_Secure_AES_IMG_KEY$i=0x" . substr($input, -$j, 8) . "\n";
#}

