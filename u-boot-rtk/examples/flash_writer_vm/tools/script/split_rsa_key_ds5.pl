#! /usr/bin/perl

#########################################################################
#
#  split_RSA_key.pl
#
#  Split RSA key string to DS-5 define style 
#
#########################################################################
#
#  Usage:
#  	./split_RSA_key.pl <RSA key>
#
#  Example:
#  	./split_RSA_key.pl ABCDABCD135713572467246822222222
#
#  Output:
# 	memory set at 0x0330???? 32 0xABCDABCD
# 	memory set at 0x0330???? 32 0x13571357
# 	memory set at 0x0330???? 32 0x24682468
# 	memory set at 0x0330???? 32 0x22222222
#
#  Note:
#	Input Data length must be 512 hex characters long.
#
#########################################################################

my $input=$ARGV[0];

# check input RSA key length
chomp($input);
die "invalid RSA key length!" if (length($input) != 512); 

#print "RSA DATA =\"$input\"\n";

$len = length($input)/2-4;
# split RSA key into 4 integer defines
for ($i=0, $j=0 ; $j<length($input); $i++, $j+=8, $len-=4) {
	#$result = sprintf("%04x", $j/2);
	$result = sprintf("%04x", $len );
	$d1 = substr($input, $j+0, 2);
	$d2 = substr($input, $j+2, 2);
	$d3 = substr($input, $j+4, 2);
	$d4 = substr($input, $j+6, 2);
	#print "memory set 0x0330$result 32 0x" . substr($input, $j, 8) . "\n";
	print "memory set 0x0330$result 32 0x$d1$d2$d3$d4\n";
}
