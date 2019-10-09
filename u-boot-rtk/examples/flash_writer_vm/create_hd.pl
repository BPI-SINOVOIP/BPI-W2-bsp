#! /usr/bin/perl -w

################################################################################
#
# create bootcode2 header
#
# Usage:
#	./create.pl <input_file>
#
################################################################################

if( $#ARGV != -1 ) {

	open BINARY0, $ARGV[0] or die $!;
	
	my $size = -s BINARY0;

	$strsize = sprintf "%08x", $size;
	
	# ----------------------------
	{
		my $str = "beef1195";
		
		@str = reverse @str;
	
		# 1. Extract pairs of hexadecimal characters from the string.
		my @hex = ($str =~ /(..)/g);
	
		# 2. Convert each pair to a decimal number.
		my @dec = map { hex($_) } @hex;
	
		# 3. Pack the number as a byte.
		my @bytes = map { pack('C', $_) } @dec;
		
		# 4. swap endian
		@bytes = reverse @bytes;
	
		print @bytes;
	}
	# ----------------------------
	{
		my $str = "00000001";
	
		@str = reverse @str;
	
		# 1. Extract pairs of hexadecimal characters from the string.
		my @hex = ($str =~ /(..)/g);
	
		# 2. Convert each pair to a decimal number.
		my @dec = map { hex($_) } @hex;
	
		# 3. Pack the number as a byte.
		my @bytes = map { pack('C', $_) } @dec;
		
		# 4. swap endian
		@bytes = reverse @bytes;
	
		print @bytes;
	}
	# ----------------------------
	{
		my $str = $strsize;
	
		@str = reverse @str;
	
		# 1. Extract pairs of hexadecimal characters from the string.
		my @hex = ($str =~ /(..)/g);
	
		# 2. Convert each pair to a decimal number.
		my @dec = map { hex($_) } @hex;
	
		# 3. Pack the number as a byte.
		my @bytes = map { pack('C', $_) } @dec;
		
		# 4. swap endian
		@bytes = reverse @bytes;
	
		print @bytes;
	}
	# ----------------------------
	{
		my $str = "01400000";
		
		# 1. Extract pairs of hexadecimal characters from the string.
		my @hex = ($str =~ /(..)/g);

		# 2. Convert each pair to a decimal number.
		my @dec = map { hex($_) } @hex;
	
		# 4. swap endian
		# 3. Pack the number as a byte.
		my @bytes = map { pack('C', $_) } @dec;
		
		@bytes = reverse @bytes;

		print @bytes;
	}
	# -------------------------------

	close BINARY0;

}
else {
	die "Usage:\n\create <input_file>\n";
}
