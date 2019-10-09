#! /usr/bin/perl

#------------------
#
# Gen Input File Length Header
#
#------------------

#------------------
# check argument
#------------------
if( !@ARGV )
{
	die "\nUsage:\n\tgen_length_header.pl <input_file> <output_length_header>\n";
}

#------------------
# open file
#------------------
my $fin = $ARGV[0];
my $fout = $ARGV[1];

open (INPUT_FILE, $fin) or die "cannot open input file $!\n";
open (LENGTH_HEADER, ">$fout") or die "cannot open output file $!\n";

my $size = sprintf("%08X", -s INPUT_FILE);
print "size: $size\n";

die "input hex string is not in pairs" if (length($size) % 2 != 0);
 
# 1. Extract pairs of hexadecimal characters from the string.
my @hex = ($size =~ /(..)/g);

# 2. Convert each pair to a decimal number.
my @dec = map { hex($_) } @hex;

# 3. Pack the number as a byte.
my @bytes = map { pack('C', $_) } @dec;
 
print LENGTH_HEADER @bytes;

close(INPUT_FILE);
close(LENGTH_HEADER);

print "gen length header Done\n";

