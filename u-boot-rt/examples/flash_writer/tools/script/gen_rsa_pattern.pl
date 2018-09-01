#!/usr/bin/perl

use bigint;
use Math::BigInt;
use POSIX;
use Getopt::Long;
use Switch




#   Mapping to openssl component
#
#   modulus INTEGER, n
#   publicExponent INTEGER, e
#   privateExponent INTEGER, d
#   prime1 INTEGER, p
#   prime2 INTEGER, q
#   exponent1 INTEGER, d mod (p-1)
#   exponent2 INTEGER, d mod (q-1)
#   coefficient INTEGER, (inverse of q) mod p





$KEY_BITS = 0;

$mod_hex ='';
$pub_exp_hex = '';
$pri_exp_hex = '';
$prime1_hex = '';
$prime2_hex = '';
$RRModN_hex = '';
$result_hex = '';
$msg_hex = '';

$msg_file = '';
$key_files = '';
@key_files = [];
$no_reverse = '';
$gen_binary;
$word_swap = '';
$mod_hex_total='';
$rrmod_hex_total='';
$pub_hex_total='';
$pri_hex_total='';
$msg_hex_total='';
$result_hex_total='';
$np_inv32_total='';
$np_inv = '';

GetOptions (
    "noreverse" => \$no_reverse,
    "wordswap" => \$word_swap,
    "msg=s"   => \$msg_file,      
    "key=s"  => \$key_files,
    "binary" => \$gen_binary
)    or die("gen_rsa_pattern  --msg [msg_file (binary)] --key \"openssl key text files\"  [--binary] [--noreverse] [--wordswap]\n");


@key_files = split(' ', $key_files);
my $tmp = @key_files;
print("const unsigned int RSA_KEY_COUNT = $tmp;\n");

foreach my $key_file (@key_files)
{
    $mod_hex ='';
    $pub_exp_hex = '';
    $pri_exp_hex = '';
    $prime1_hex = '';
    $prime2_hex = '';
    $RRModN_hex = '';
    $result_hex = '';
    $msg_hex = '';



    open(MSG, "<$msg_file") or die "Fail to open message file $msg_file\n";
    binmode(MSG);
    while (read(MSG, $msg_buf, 1))
    {
        my $n = length($msg_buf);
        my $s = 2*$n;
        $msg_hex .= unpack("H$s", $msg_buf);
    }
    close(MSG);
    open(KEY, "<$key_file") or die "Fail to open key file:$key_file\n";

    $PARSE_MODE = '';
    my $input_state = 'none';


    if($key_file eq 'in_out_data.txt')
    {
        $PARSE_MODE = 'from_hw';

        print ("//from_hw\n");

        while(<KEY>)
        {

            if(/_nn0\s*=\s*([a-f0-9]+)/)
            {
                #remove first '0'
                $mod_hex = substr($1, 1);
            }
            elsif(/CipherText_ee0\s*=\s*([a-f0-9]+)/)
            {
                $pub_exp_hex = substr($1, 1);
                $pri_exp_hex = $pub_exp_hex;
            }
            elsif(/_rr0\s*=\s*([a-f0-9]+)/)
            {
                $RRModN_hex = substr($1, 1);
            }
            elsif(/_mm0\s*=\s*([a-f0-9]+)/)
            {
                $msg_hex = substr($1, 1);
            }
            elsif(/_aa0\s*=\s*([a-f0-9]+)/)
            {
                $result_hex = $1;
                print("//DEBUG: result_hex = $result_hex\n");
            }
        }
    }
    else
    {
        $PARSE_MODE = 'from_openssl';
        while(<KEY>)
        {
            if(/Private-Key:.*\(([0-9]+)/)
            {
                $KEY_BITS = int($1);
            }

            elsif (/modulus/)
            {
                #single lines or multi-lines
                if(/0x([a-f0-9]+)/)
                {
                    $mod_hex = $1;
                    $input_state = 'none';
                }else
                {
                    $input_state = 'modulus';
                }
            }
            elsif(/publicExponent/)
            {
                if(/0x([a-f0-9]+)/)
                {
                    $pub_exp_hex = $1;
                    $input_state = 'none';
                }else
                {
                    $input_state = 'publicExponent';
                }
            }
            elsif(/privateExponent/)
            {
                if(/0x([a-f0-9]+)/)
                {
                    $pri_exp_hex = $1;
                    $input_state = 'none';
                }else
                {
                    $input_state = 'privateExponent';
                }
            }
            elsif(/prime1/)
            {
                if(/0x([a-f0-9]+)/)
                {
                    $prime1_hex = $1;
                    $input_state = 'none';
                }else
                {
                    $input_state = 'prime1';
                }
            }
            elsif($input_state eq 'modulus' and /[a-f0-9][a-f0-9]\:?/)
            {
                $_ =~ s/[\s\:]//g;
                $mod_hex .=  $_;
            }
            elsif($input_state eq 'privateExponent' and /[a-f0-9][a-f0-9]\:?/)
            {
                $_ =~ s/[\s\:]//g;
                $pri_exp_hex .=  $_;
            }
            elsif($input_state eq 'prime1' and /[a-f0-9][a-f0-9]\:?/)
            {
                $_ =~ s/[\s\:]//g;
                $prime1_hex .=  $_;
            }
            elsif($input_state eq 'prime2' and /[a-f0-9][a-f0-9]\:?/)
            {
                $_ =~ s/[\s\:]//g;
                $prime2_hex .=  $_;
            }
            else
            {
                $input_state = 'none';
            }
        }
    }
#padding to  mudulus significant bits
    if($PARSE_MODE eq 'from_openssl')
    {
        #   $mod_hex = '00000000000000' . $mod_hex;
    }

    my $mod = Math::BigInt->new("0x$mod_hex");
    my $pub_exp = Math::BigInt->new('65537');
    my $pri_exp = Math::BigInt->new("0x$pri_exp_hex");
    my $cipher = Math::BigInt->new();
    my $p1 = Math::BigInt->new("0x$prime1_hex");
    my $p2 = Math::BigInt->new("0x$prime2_hex");



    if($PARSE_MODE eq 'from_openssl')
    {
        my $cmd = "openssl rsautl -encrypt -inkey $key_file -raw -in $msg_file > enc.dat";
        #my $cmd = "openssl rsautl -sign -inkey $key_file -raw -in $msg_file > enc.dat";
        qx($cmd);
        print ("//[openssl] $cmd");
        open(ENC, "<enc.dat") or die "Fail to open encrypted file enc.dat\n";
        binmode(ENC);

        while (read(ENC, $msg_buf, $KEY_BITS/8))
        {
            my $n = length($msg_buf);
            my $s = 2*$n;
            $result_hex .= unpack("H$s", $msg_buf);
        }
    }

    if($PARSE_MODE eq 'from_openssl')
    {

        my $RRModN = Math::BigInt->new("0x2");
        my $v = &r_power($KEY_BITS);
        print("//r_pwr=$v\n");
        $RRModN =  $RRModN->bmodpow( $v, $mod);
        my $RRModN_hex_tmp = $RRModN->as_hex();
        print ("// 0x$RRModN_hex_tmp \n");


        $RRModN_hex = $RRModN->as_hex();
    }else{
        #from hardware
        #evaluate the expected RRModN
        my $mod_tmp = $mod->as_hex();
        printf("//[DEBUG] mod=$mod_tmp\n");
        my $RRModN = Math::BigInt->new("0x2");
        my $v = &r_power($KEY_BITS);
        $RRModN =  $RRModN->bmodpow( $v , $mod);
        print("//r_pwr=$v\n");
        my $RRModN_hex_tmp = $RRModN->as_hex();
        print ("// 0x$RRModN_hex_tmp \n");
    }


    $mod_hex = &gen_hex_string($mod_hex);
    $mod_hex_total = join ( '', ($mod_hex_total, $mod_hex));
#remove first '0x' and fill 'zero'
    $RRModN_hex =~  s/0x//g;
    $rrmod_hex_total = join ( '', ($rrmod_hex_total, &gen_hex_string($RRModN_hex)));
    $msg_hex_total = join ( '', ($msg_hex_total, &gen_hex_string($msg_hex)));
    $result_hex_total = join ( '', ($result_hex_total, &gen_hex_string($result_hex)));
    $pri_hex_total = join ( '', ($pri_hex_total, &gen_hex_string($pri_exp_hex)));
    $pub_hex_total = join ( '', ($pub_hex_total, &gen_hex_string($pub_exp_hex)));

    my @np_inv32=[];
    my @mod_array = $mod_hex =~ m/../g ;
    print("//@mod_array\n");
    if (!$no_reverse) {@np_inv32 = reverse @mod_array[0..3];}
    else { my $end = $KEY_BITS/8 -1;
        @np_inv32 = @mod_array[$end-3..$end];}

    if($word_swap)
    {
        my $tmp;
        $tmp = $np_inv32[$i*4];
        $np_inv32[$i*4] = $np_inv32[$i*4+3];
        $np_inv32[$i*4+3] = $tmp;

        $tmp = $np_inv32[$i*4+1];
        $np_inv32[$i*4+1] = $np_inv32[$i*4+2];
        $np_inv32[$i*4+2] = $tmp;
    }

    $np_inv = Math::BigInt->new ("0x" . join('',@np_inv32));
    my $R = Math::BigInt->new("2");
    $R->bpow(32);
    $np_inv = ($R - $np_inv)->bmodinv($R);
    push(@np_inv32_total, "$np_inv" );


}

print ("#ifndef _RSA_AUTOGEN_PATTERN_H__\n");
print ("#define _RSA_AUTOGEN_PATTERN_H__\n");

&print_hex_string('modulus', "$mod_hex_total");
&print_hex_string('privateExponent', "$pri_hex_total");
&print_hex_string('publicExponent', "$pub_hex_total");
&print_hex_string('RRModN', "$rrmod_hex_total");
&print_hex_string('result', "$result_hex_total");
&print_hex_string('msg', "$msg_hex_total");


if($gen_binary)
{
    &print_binary('modulus.bin', "$mod_hex_total");
    &print_binary('privateExponent.bin', "$pri_hex_total");
    &print_binary('publicExponent.bin', "$pub_hex_total");
    &print_binary('RRModN.bin', "$rrmod_hex_total");
    &print_binary('result.bin', "$result_hex_total");
    &print_binary('msg.bin', "$msg_hex_total");

}

#@mod_array = &print_array('modulus', $mod_hex);

#&print_array('privateExponent', $pri_exp_hex);




#&print_array('RRModN', $RRModN_hex);

#&print_array('result', $result_hex);

#&print_array('msg', $msg_hex);


if(@key_files > 1)
{
    my $key_count = @key_files;
    print ("unsigned int np_inv32[$key_count] = {");
    print (join( ', ', @np_inv32_total));
    print ("\n};\n");
}
else
{
    print "unsigned int np_inv32 = $np_inv;\n";

    if($gen_binary)
    {
        my $np_inv32_hex = sprintf("%x", $np_inv);
        &print_binary('np_inv32.bin', $np_inv32_hex);

    }

}
printf "const unsigned int RSA_WORD_LENGTH=%d;\n", $KEY_BITS/32;
#&print_array('publicExponent', $pub_exp_hex);



print ("#endif\n");

sub r_power
{
    return (($KEY_BITS/32)+1+1)*32*2;
}

sub gen_hex_string
{
    my $hex = shift @_ ;
    my $tmp =  sprintf("%%0%ds", $KEY_BITS/8*2);

    $hex = sprintf("$tmp", $hex);
    my @array = $hex =~ m/../g ;

    if( (@array > $KEY_BITS/8) )
    {
        if($array[0] eq '00')
        {
            shift (@array);
            print("//remove significant 00\n");
        }
        else
        {
            print("//[ERROR]>  $KEY_BITS bits\n");
        }
    }
    if (!$no_reverse) { @array = reverse @array ;}

    if($word_swap)
    {
        my $tmp;
        for(my $i=0; $i< ( @array / 4); $i++)
        {
            $tmp = $array[$i*4];
            $array[$i*4] = $array[$i*4+3];
            $array[$i*4+3] = $tmp;

            $tmp = $array[$i*4+1];
            $array[$i*4+1] = $array[$i*4+2];
            $array[$i*4+2] = $tmp;
        }
    }
    return join('', @array);
}
sub print_hex_string
{
    my ($name, $hex) = @_;
    my $tmp =  sprintf("%%0%ds", length($hex));
    $hex = sprintf("$tmp", $hex);
    my @array = $hex =~ m/../g ;

    my $array_len = @array;
    printf ("unsigned char $name [$array_len] = {\n");
    print '0x' . join(" ,0x", @array) . "\n";
    print (" };\n");

    return @array;
}
sub print_array
{
    my ($name, $hex) = @_;
    my $tmp =  sprintf("%%0%ds", $KEY_BITS/8*2);

    $hex = sprintf("$tmp", $hex);
    my @array = $hex =~ m/../g ;

    if( (@array > $KEY_BITS/8) )
    {
        if($array[0] eq '00')
        {
            shift (@array);
            print("//remove significant 00\n");
        }
        else
        {
            print("//[ERROR]>  $KEY_BITS bits\n");
        }
    }
    if (!$no_reverse) { @array = reverse @array ;}

    if($word_swap)
    {
        my $tmp;
        for(my $i=0; $i< ( @array / 4); $i++)
        {
            $tmp = $array[$i*4];
            $array[$i*4] = $array[$i*4+3];
            $array[$i*4+3] = $tmp;

            $tmp = $array[$i*4+1];
            $array[$i*4+1] = $array[$i*4+2];
            $array[$i*4+2] = $tmp;
        }

    }

    my $array_len = @array;
    printf ("unsigned char $name [$array_len] = {\n");
    print '0x' . join(" ,0x", @array) . "\n";
    print (" };\n");

    return @array;
}

sub print_binary
{
    my ($name, $hex) = @_;
    my $tmp =  sprintf("%%0%ds", length($hex));
    $hex = sprintf("$tmp", $hex);
    my @array = $hex =~ m/../g ;

    my $array_len = @array;


    my $BIN;
    binmode(BIN);
    open(BIN, ">$name") or die "Fail to wtite binary file for RSA :$name\n";
    foreach my $v (@array)
    {
        print BIN pack('C', hex($v));
    }

    close(BIN);
    return @array;
}
