#! /usr/bin/perl

#########################################################################
#
#  reverse_RSA_data.pl
#
#  reverse RSA data file in word unit
#
#########################################################################
#
#  Usage:
#  	./reverse_RSA_data.pl <RSA file>
#
#  Example:
#  	./reverse_RSA_data.pl rsa.data
#
#  Output:
#	rsa.data.rev
#
#  Note:
#	Input Data length must be 256 bytes.
#
#########################################################################

$file_in = "INFILE";
$file_out = "OUTFILE";
$input = "<" . $ARGV[0];
$output = ">" . $ARGV[0] . ".rev";

open($file_in, $input) or die "could not open the file: $!\n";
open($file_out, $output) or die "could not open the file: $!\n";

binmode($file_in);
binmode($file_out);

print "input file:" . $ARGV[0];
seek($file_in,$f_len,2);
$f_len = tell($file_in);
#die "invalid RSA data length!" if ($f_len != 256); 
print ", length = " . $f_len . "\n";
print "output file:" . $ARGV[0]. ".rev\n";
seek($file_in,$f_len,0);
$len = $f_len;

for ($i=0,$j=0 ; $j<=$f_len; $i++, $j+=4, $len-=4) {
	seek($file_in,$len,0);
	read($file_in, $binData, 4);
	$binData = reverse $binData;
	#asci dump
	#my $id = unpack('H8', $binData);
	#print $id . "\n";
	print $file_out $binData
}
close($file_in);
close($file_out);
