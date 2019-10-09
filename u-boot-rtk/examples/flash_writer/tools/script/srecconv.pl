#! /usr/local/bin/perl -w
#########################################################################
#
#   srecconv.pl
#
#   Tool that converts from srecord format to :
#
#   1) File suitable for parallel download (.fl format)
#   2) Binary file suitable for EPROM programming devices (.bin format).
#
#   ######################################################################
#
#   mips_start_of_legal_notice
#   
#   Copyright (c) 2003 MIPS Technologies, Inc. All rights reserved.
#
#
#   Unpublished rights (if any) reserved under the copyright laws of the
#   United States of America and other countries.
#
#   This code is proprietary to MIPS Technologies, Inc. ("MIPS
#   Technologies"). Any copying, reproducing, modifying or use of this code
#   (in whole or in part) that is not expressly permitted in writing by MIPS
#   Technologies or an authorized third party is strictly prohibited. At a
#   minimum, this code is protected under unfair competition and copyright
#   laws. Violations thereof may result in criminal penalties and fines.
#
#   MIPS Technologies reserves the right to change this code to improve
#   function, design or otherwise. MIPS Technologies does not assume any
#   liability arising out of the application or use of this code, or of any
#   error or omission in such code. Any warranties, whether express,
#   statutory, implied or otherwise, including but not limited to the
#   implied warranties of merchantability or fitness for a particular
#   purpose, are excluded. Except as expressly provided in any written
#   license agreement from MIPS Technologies or an authorized third party,
#   the furnishing of this code does not give recipient any license to any
#   intellectual property rights, including any patent rights, that cover
#   this code.
#
#   This code shall not be exported or transferred for the purpose of
#   reexporting in violation of any U.S. or non-U.S. regulation, treaty,
#   Executive Order, law, statute, amendment or supplement thereto.
#
#   This code constitutes one or more of the following: commercial computer
#   software, commercial computer software documentation or other commercial
#   items. If the user of this code, or any related documentation of any
#   kind, including related technical data or manuals, is an agency,
#   department, or other entity of the United States government
#   ("Government"), the use, duplication, reproduction, release,
#   modification, disclosure, or transfer of this code, or any related
#   documentation of any kind, is restricted in accordance with Federal
#   Acquisition Regulation 12.212 for civilian agencies and Defense Federal
#   Acquisition Regulation Supplement 227.7202 for military agencies. The
#   use of this code by the Government is further restricted in accordance
#   with the terms of the license agreement(s) and/or applicable contract
#   terms and conditions covering this code from MIPS Technologies or an
#   authorized third party.
#
#   
#   mips_end_of_legal_notice
#   
#
#########################################################################

use Getopt::Long;

$srec_endian = "B";
$bin_endian  = "B";
$addr_bits   = 32;
$addr_offset = "0";
$verbose     = 0;

$help = "
   Usage: $0 [-ES <endian>] [-EB <endian>] [-A <addr bits>] [-O <offset>] [-v] file

   The script reads the <file>.rec file which must be in SREC format,
   and generates two files:
   <file>.fl    : FLASH file for download to MIPS board.
   <file>.bin   : Binary file for EPROM on SEAD-1 board.

   The following options are available:

   -ES <endian> : Set the endianess of the SREC file. Valid options:
                  -ES L (little endian) or -ES B (big endian)

   -EB <endian> : Set the endianess of the binary file. Valid options:
                  -EB L (little endian) or -EB B (big endian)

   -A <addr bits> : Set number of address bits to include in FLASH file.

   -O <offset>  : An optional offset added to all addresses in S-rec file.
                  Must be specified as a hex value e.g. -O 66aa

   -v           : Print verbose information

   Endianess for the SREC file can be changed on the fly by embedding the lines:
      !L
   or
      !B
   in the file.\n\n
";

GetOptions("ES:s"   => \$srec_endian,
           "EB:s"   => \$bin_endian,
	   "A:i"    => \$addr_bits,
	   "O:s"    => \$addr_offset,
	   "v"      => \$verbose);

if (!defined ($ARGV[0])) {
    print $help;
    exit -1;
}

$input_file      = "$ARGV[0]" . ".rec";
$output_file_fl  = "$ARGV[0]" . ".fl";
$output_file_bin = "$ARGV[0]" . ".bin";

open (IFILE, "<$input_file") ||
    die("Error: can't open file $input_file \n");

$addr_mask = 0xffffffff >> (32 - $addr_bits);
$addr_mask = $addr_mask & 0xfffffffc;
$addr_base = -1;
$block_size         = 0x20000;

while ($line = <IFILE>)
{
    # -----------------------------------
    # Process S2 or S3 lines.
    # -----------------------------------
    $count = 0;

    if ($line =~ /^S3(.{2})(.{8})(.*)/)
    {
	$count = hex($1)-4-1;
	$addr  = hex($2) + hex($addr_offset);
	$data  = $3;
    }
    elsif ($line =~ /^S2(.{2})(.{6})(.*)/)
    {
	$count = hex($1)-3-1;
	$addr  = hex($2) + hex($addr_offset);
	$data  = $3;
    }
   
    if ($count != 0)
    {
	for ($i = 0; $i < $count; $i++)
	{

	    $addr32 = $addr & $addr_mask;
	    $addr01 = $addr & 0x3;

	    if ($addr_base < 0)
	    {
		$addr_base = $addr32;
	    }

	    $addr32 = $addr32 - $addr_base;
	    $data =~ /(.{2})/g;

	    $val = hex($1);

	    if ($srec_endian eq "L")
	    {
		
		$val = $val << (8*$addr01);
	    }
	    else
	    {
      
		$val = $val << (8*(3-$addr01));
	    }

	    if (defined($data_array[$addr32]))
	    {
		$data_array[$addr32] = $data_array[$addr32] | $val;
	    }
	    else
	    {
		$data_array[$addr32] = $val;
	    }

	    $addr = $addr + 1;
	}

    }
    elsif ($line =~ /^!B/)
    {
	vprint ("Changing SREC endianess to big endian\n");
	$srec_endian = "B";
    }
    elsif ($line =~ /^!L/)
    {
	vprint ("Changing SREC endianess to little endian\n");
	$srec_endian = "L";
    }
#cyhuang for lx-start
	elsif ($line =~ /^!X/)
    {
    $srec_endian = "L";
    } 


}
close(IFILE);


#------------------------------------------------------------
# Create the FLASH file
#------------------------------------------------------------
open (OFILE, ">$output_file_fl") ||
    die("Error: can't open file $output_file_fl \n");

# Initialize download
print(OFILE "# Reset the loader state machine.\n!R\n");

if ($addr_base == 0x1fc00000)
{
    printf(OFILE ">1fc00xxx \@1fc00000 !C\n");
}

for($i=0; $i<@data_array; $i+=$block_size)
{
    printf(OFILE ">%.5xxxx ",($addr_base + $i)/0x1000);
    printf(OFILE "@%.8x !E\n",$addr_base + $i);
}


$prev_addr = -256;
$block16   = 0;

for ($addr=0; $addr < @data_array; $addr=$addr+4)
{

    next if (!defined($data_array[$addr]));

    if ($addr !=  $prev_addr+4)
    {
	$hole    = ($addr-$prev_addr)/4 - 1;
	$missing = (16 - $block16) % 16;

	$count = $hole > $missing ? $missing : $hole;

	while ($count)
	{
	    printf(OFILE "%.8x\n",0xf111c0de);
	    $block16 = ($block16+1) % 16;
	    $count--;
	}

	if ($hole > $missing)
	{
	    printf(OFILE "@%.8x\n",$addr+$addr_base);
	    printf(OFILE ">%.8x\n",$addr+$addr_base);
	}

    }

    $prev_addr = $addr;

    printf(OFILE "%.8X\n",$data_array[$addr]);
    $block16 = ($block16+1) % 16;
}

while ($block16 < 16)
{
    printf(OFILE "%.8x\n",0xf111c0de);
    $block16++;
}

if ($addr_base == 0x1fc00000)
{
    printf(OFILE ">LOCKFLSH\n");
    printf(OFILE "\@1fc00000 !S\n");
    printf(OFILE "\@1fc20000 !S\n");
    printf(OFILE "\@1fc40000 !S\n");
    printf(OFILE "\@1fc60000 !S\n");
    printf(OFILE "\@1fc80000 !S\n");
    printf(OFILE "\@1fca0000 !S\n");
    printf(OFILE "\@1fcc0000 !S\n");
    printf(OFILE "\@1fce0000 !S\n");
}
printf(OFILE ">#DL_DONE\n");
printf(OFILE ">FINISHED\n");

close(OFILE);

#------------------------------------------------------------
# Create the binary file
#------------------------------------------------------------
open (OFILE, ">$output_file_bin") ||
    die("Error: can't open file $output_file_bin \n");

$prev_addr = -256;

for ($addr=0; $addr < @data_array; $addr=$addr+4)
{
    next if (!defined($data_array[$addr]));

    if (($addr !=  $prev_addr+4) && $prev_addr > 0)
    {
	$hole    = ($addr-$prev_addr)/4 - 1;
	while ($hole)
	{
	    $ostream = pack("C4", 0,0,0,0);
	    print (OFILE $ostream);
	    $hole--;
	}

    }

    $prev_addr = $addr;

    if ($bin_endian eq "L")
    {
	$istream[0] = ($data_array[$addr]>>0)  & 0xff;
	$istream[1] = ($data_array[$addr]>>8)  & 0xff;
	$istream[2] = ($data_array[$addr]>>16) & 0xff;
	$istream[3] = ($data_array[$addr]>>24) & 0xff;
    }
    else
    {
	$istream[3] = ($data_array[$addr]>>0)  & 0xff;
	$istream[2] = ($data_array[$addr]>>8)  & 0xff;
	$istream[1] = ($data_array[$addr]>>16) & 0xff;
	$istream[0] = ($data_array[$addr]>>24) & 0xff;
    }

    $ostream = pack("C4", @istream);
    print (OFILE $ostream);
}

close (OFILE);

sub vprint {
    my $string = $_[0];
    if($verbose) {
	print($string);
    }
}

exit 0;
