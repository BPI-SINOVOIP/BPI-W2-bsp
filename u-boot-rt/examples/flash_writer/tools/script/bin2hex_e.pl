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
if( !@ARGV )
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
my $idx = 0;

while ($i < 0x20000)
{
        my $h1 = sprintf("%X", $i);
	print HEX "$h1/00;\n";
        $i++;
}

$i = 0;
$idx = 0x20000;

#while ($i < $size)
while (read(BINARY, $buffer, 1))
{
	## save string bit in output file		
	#my @arr = unpack("B*", $buffer);
	#print HEX "@arr\n";
	
	## show hex value on console
	my $h = sprintf('%02X', ord($buffer));
	my $h1 = sprintf("%X", $idx);
	print HEX "$h1/$h;\n";

	$i++;
	$idx++;
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
# stuff bit representation of "0xff" until 42K
#------------------
#while ($i < 0xa800)
#{
#	my $h1 = sprintf("%X", $idx);
#	print HEX "$h1/FF;\n";
#	$i++;
#}

close(HEX);

print "bin2hex Done\n";

