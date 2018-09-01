#! /usr/bin/perl

#########################################################################
#
#  binary2ascii.pl
#
#  Convert byte file into ascii style (seperated by ",")
#
#########################################################################
#
#  Usage:
#  	./binary2ascii.pl <binary file>
#
#  Example:
#  	./binary2ascii.pl key_img_seed.bin
#
#  Output:
# 	0x2d, 0xc2, 0xdf, 0x39, 0x42, 0x03, 0x21, 0xd0, 0xce, 0xf1, 0xfe, 
#	0x23, 0x74, 0x02, 0x9d, 0x95,
#
#
#  Note:
#	Input key length must be 32 hex characters long.
#
#########################################################################

open INPUT, $ARGV[0] or die $!;
$size = -s INPUT;
$idx = 0;

while ($idx < $size)
{
	read(INPUT, $bytes, 1);
	@a = map ord, split //, $bytes;
	printf "0x%02x, ", @a;
	$idx++;
}
