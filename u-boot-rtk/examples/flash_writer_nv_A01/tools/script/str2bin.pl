#! /usr/bin/perl -w

################################################################################
#
# str2bin.pl
#
# Convert hex string into binary representation
# 
################################################################################
#
# Usage:
#	./str2bin.pl [input_string] > [output_binary]
#
#  Example:
#  	./str2bin.pl B9975438AF3F83EB > output.bin
#
#  Reslut:
#	in output.bin:
#
#	B9 97 54 38 AF 3F 83 EB
#
#  Note:
#	length of input hex string must be even number
#
################################################################################
if( $#ARGV == -1 ) {
	print "Usage:\n\t ./str2bin.pl [input_string] > [output_binary]\n";
	exit;
}

my $str=$ARGV[0];

die "input hex string is not in pairs" if (length($str) % 2 != 0);

# 1. Extract pairs of hexadecimal characters from the string.
my @hex = ($str =~ /(..)/g);

# 2. Convert each pair to a decimal number.
my @dec = map { hex($_) } @hex;

# 3. Pack the number as a byte.
my @bytes = map { pack('C', $_) } @dec;

print @bytes;
# Print bytes in reverse order (LSB first)
##print reverse @bytes;
