#! /usr/bin/perl

$file_start = 
"/************************************************************************
 *
 *  project_config.h
 *
 *  external parameters was included in this file
 * 
 *
 ************************************************************************/

#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H
";
#remove this part since we should not include anything to project_config.h
#/************************************************************************
# *  Include files
# ************************************************************************/
#
##include <sysdefs.h>
#
#";

$file_end = "
#endif //#ifndef EXTERN_PARAM_H	
";




#################################################################

#check include file state and name
(-e $ARGV[1]) || die "error!! input file not exists\n";
($ARGV[1] =~ /.*inc\b/) || die "error!! input file is not a config file\n";
($ARGV[0] =~ /.*h\b/) || die "error!! output file is not a header file\n";

#open include config file and output 

print "Config convert to header file \n\n";


open (CONFIG_FILE1, "$ARGV[1]");
print "Input Config File     : "  . substr( $ARGV[1], rindex($ARGV[1], "/") + 1) . "\n";

open (CONFIG_FILE2, "$ARGV[2]");
print "Input Logo1 Info File : "  . substr( $ARGV[2], rindex($ARGV[2], "/") + 1) . "\n";

if(defined $ARGV[3])
{
	open (CONFIG_FILE3, "$ARGV[3]");
	print "Input Logo2 Info File : "  . substr( $ARGV[3], rindex($ARGV[3], "/") + 1) . "\n";
}

if(defined $ARGV[4])
{
	open (CONFIG_FILE4, "$ARGV[4]");
	print "Input Logo3 Info File : "  . substr( $ARGV[4], rindex($ARGV[4], "/") + 1) . "\n";
}

if(defined $ARGV[5])
{
	open (CONFIG_FILE5, "$ARGV[5]");
	print "Input Logo4 Info File : "  . substr( $ARGV[5], rindex($ARGV[5], "/") + 1) . "\n";
}

if(defined $ARGV[6])
{
	open (CONFIG_FILE6, "$ARGV[6]");
	print "Input Logo5 Info File : "  . substr( $ARGV[6], rindex($ARGV[6], "/") + 1) . "\n";
}

if(defined $ARGV[7])
{
	open (CONFIG_FILE7, "$ARGV[7]");
	print "Input Logo6 Info File : "  . substr( $ARGV[7], rindex($ARGV[7], "/") + 1) . "\n";
}

if(defined $ARGV[8])
{
	open (CONFIG_FILE8, "$ARGV[8]");
	print "Input Logo7 Info File : "  . substr( $ARGV[8], rindex($ARGV[8], "/") + 1) . "\n";
}

if(defined $ARGV[9])
{
	open (CONFIG_FILE9, "$ARGV[9]");
	print "Input Logo8 Info File : "  . substr( $ARGV[9], rindex($ARGV[9], "/") + 1) . "\n";
}

if(defined $ARGV[10])
{
	open (CONFIG_FILE10, "$ARGV[10]");
	print "Input RSA Info File : "  . substr( $ARGV[10], rindex($ARGV[10], "/") + 1) . "\n";
}

if(defined $ARGV[11])
{
	open (CONFIG_FILE11, "$ARGV[11]");
	print "Input RSA0 Info File : "  . substr( $ARGV[11], rindex($ARGV[11], "/") + 1) . "\n";
}

#if(defined $ARGV[11])
#{
#	open (CONFIG_FILE11, "$ARGV[11]");
#	print "Input AES Info File : "  . substr( $ARGV[11], rindex($ARGV[11], "/") + 1) . "\n";
#}

open (HEADER_FILE, ">$ARGV[0]");
print "Output Header File    : "  . substr( $ARGV[0], rindex($ARGV[0], "/") + 1) . "\n";

print HEADER_FILE $file_start;

$tmp1 = 0;
$tmp2 = 0;
$dram_block = 0;
$dram_number  = 0;
$dram_size = 0;

while (<CONFIG_FILE1>){
	
	# display segment header
	if (/^# .*/)
	{
		s/^# /\/\//;
		print HEADER_FILE;
	}

	# Board, Config and USB_OTG setup segment
	if ((/^Board/) || (/^Config/)|| (/^USB_OTG/))
	{
		if (/^Board_DRAM_Block/)
		{
			($tmp1, $tmp2, $dram_block) = split(/ +/);
			chomp($dram_block);
		}
		
		if (/^Board_DRAM_Number/)
		{
			($tmp1, $tmp2, $dram_number) = split(/ +/);
			chomp($dram_number);
		}
		
		if (/^Config_HDMI/)
		{
			s/ *= */			/; # replace with three TAB space
		}

		if (/^Config_Secure_Uart/)
		{
			s/ *= */			/; # replace with three TAB space
		}

		if (/\./)
		{
			s/\./___/;	# replace "." with "___"
		}
		
		if ((/Size/) || (/Number/) || (/Block/) || (/Value/) || (/_File/))
		{
			s/ *= */			/; # replace with three TAB space
		}
		else
		{
			s/ *= */_/;
		}

		print HEADER_FILE "#define " . $_;


		if (($dram_number != 0) && ($dram_block != 0))
		{
			$dram_size = $dram_block * $dram_number;			
			print HEADER_FILE "#define Board_DRAM_Size				$dram_size\n";
			
			$dram_number = ($dram_block = 0);
		}
		
		if (/Config_Secure_Key_TRUE/)
		{
			while (<CONFIG_FILE10>){
				s/ *= */			/; # replace with three TAB space
				print HEADER_FILE "#define " . $_;
			}

			while (<CONFIG_FILE11>){
				s/ *= */			/; # replace with three TAB space
				print HEADER_FILE "#define " . $_;
			}
		}

		#if (/Config_Secure_AES_TRUE/)
		#{
		#	while (<CONFIG_FILE11>){
		#		s/ *= */			/; # replace with three TAB space
		#		print HEADER_FILE "#define " . $_;
		#	}
		#}
	}
	
	# GPIO and Param setup segment
	if ((/^GPIO/) || (/^Param/))
	{
		s/ *= */			/; # replace with three TAB space
		print HEADER_FILE "#define " . $_;
	}

	# Logo setup segment
	if (/^Logo/)
	{
		if ((/Source/) || (/Type/))
		{
			s/ *= */_/;
		}
		else
		{
			s/ *= */			/; # replace with three TAB space
		}

		print HEADER_FILE "#define " . $_;
		
		if (/Logo_Source_FLASH/)
		{
			while (<CONFIG_FILE2>){
				s/ *= */			/; # replace with three TAB space
				print HEADER_FILE "#define " . $_;
			}
		}
		
		if (/Logo2_Source_FLASH/)
		{	
			while (<CONFIG_FILE3>)
			{
				s/ *= */			/; # replace with three TAB space
				s/Logo/Logo2/;
				print HEADER_FILE "#define " . $_;
			}
		}
		
		if (/Logo3_Source_FLASH/)
		{	
			while (<CONFIG_FILE4>)
			{
				s/ *= */			/; # replace with three TAB space
				s/Logo/Logo3/;
				print HEADER_FILE "#define " . $_;
			}
		}
		
		if (/Logo4_Source_FLASH/)
		{	
			while (<CONFIG_FILE5>)
			{
				s/ *= */			/; # replace with three TAB space
				s/Logo/Logo4/;
				print HEADER_FILE "#define " . $_;
			}
		}
		
		if (/Logo5_Source_FLASH/)
		{	
			while (<CONFIG_FILE6>)
			{
				s/ *= */			/; # replace with three TAB space
				s/Logo/Logo5/;
				print HEADER_FILE "#define " . $_;
			}
		}
		
		if (/Logo6_Source_FLASH/)
		{	
			while (<CONFIG_FILE7>)
			{
				s/ *= */			/; # replace with three TAB space
				s/Logo/Logo6/;
				print HEADER_FILE "#define " . $_;
			}
		}
		
		if (/Logo7_Source_FLASH/)
		{	
			while (<CONFIG_FILE8>)
			{
				s/ *= */			/; # replace with three TAB space
				s/Logo/Logo7/;
				print HEADER_FILE "#define " . $_;
			}
		}
		
		if (/Logo8_Source_FLASH/)
		{	
			while (<CONFIG_FILE9>)
			{
				s/ *= */			/; # replace with three TAB space
				s/Logo/Logo8/;
				print HEADER_FILE "#define " . $_;
			}
		}
	}

	# Rescue and Linux setup segment
	if ((/^Rescue/) || (/^Linux/))
	{
		if (/Source/)
		{
			s/ *= */_/;
		}
		else
		{
			s/TAB/0x09/;  		#convert strting 'TAB' to 0x09
			s/ESC/0x1B/;  		#convert strting 'ESC' to 0x09
			s/SPACE/0x20/;  	#convert strting 'SPACE' to 0x09
			s/High/0x1/;  		#convert strting 'High' to 0x1
			s/Low/0x0/;  		#convert strting 'Low' to 0x0
			
			s/ *= */			/; # replace with three TAB space
		}
		
		print HEADER_FILE "#define " . $_;
	}

	# Cmd setup segment
	if (/^Cmd/)
	{
		s/ *= */_/;
		print HEADER_FILE "#define " . $_;
	}
	
	#User_Defined setup segment
	if (/^User_Defined/)
	{
		s/User_Defined *= *//;
		print HEADER_FILE "#define " . $_;
		
	}
	
}


print HEADER_FILE $file_end;

close (HEADER_FILE);
close (CONFIG_FILE1);
close (CONFIG_FILE2);
if(defined $ARGV[3])
{
	close (CONFIG_FILE3);
}
if(defined $ARGV[4])
{
	close (CONFIG_FILE4);
}
if(defined $ARGV[5])
{
	close (CONFIG_FILE5);
}

if(defined $ARGV[6])
{
	close (CONFIG_FILE6);
}

if(defined $ARGV[7])
{
	close (CONFIG_FILE7);
}

if(defined $ARGV[8])
{
	close (CONFIG_FILE8);
}

if(defined $ARGV[9])
{
	close (CONFIG_FILE9);
}

if(defined $ARGV[10])
{
	close (CONFIG_FILE10);
}

if(defined $ARGV[11])
{
	close (CONFIG_FILE11);
}

print "convert config file to header file: done \n";



#while (defined($textd = <WORDLIST>)){
#	if($textd[0] ne "#')
#		print "$textd";
#}


#close(INC)


#while (<>) {
#    print $_;
#}
