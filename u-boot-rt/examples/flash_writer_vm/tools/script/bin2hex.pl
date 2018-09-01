#! /usr/bin/perl

#------------------
#
# Convert binary to hex format
#
# e.g.
#	[input]
#	f0 ab 78 00....
#------------------
#	[output]
#	f0
#	ab
#	78
#	..
#	00
#
#------------------

#------------------
# check argument
#------------------
if( $#ARGV == -1 )
{
	die "\nUsage:\n\tbin2hex.pl <input_binary> <output_hex>\n";
}

#------------------
# open file
#------------------
my $fin = $ARGV[0];
my $fout = $ARGV[1];

open (BINARY, $fin) or die "cannot open input file $!\n";
open (HEX, ">$fout") or die "cannot open output file $!\n";
binmode (BINARY);

#------------------
# process each byte
#------------------
my $size = -s BINARY;
my $i = 0;
my $buffer = 0;

#while ($i < $size)
while (read(BINARY, $buffer, 1))
{
	## save string bit in output file		
	#my @arr = unpack("B*", $buffer);
	#print HEX "@arr\n";
	
	## show hex value on console
	my $h = sprintf('%02X', ord($buffer));
	print HEX "$h\n";
	$i++;
}

if ($i != $size)
{
	close(BINARY);
	close(HEX);
	die "Error! byte processed:$i, total bytes:$size \n";
}

print "$fin size $size\n";
close(BINARY);

#------------------
# stuff bit representation of "0xff" until 8K
#------------------
while ($i < 0x8000)
{
	#print HEX "11111111\n";
	print HEX "FF\n";
	$i++;
}

close(HEX);

print "bin2hex Done\n";

