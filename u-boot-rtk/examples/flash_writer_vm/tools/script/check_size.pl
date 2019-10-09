
use File::stat;


#$flash_size = $ARGV[0];
$flash_size = 2;
$flash_size = $flash_size * 1024 * 1024;

$bootrom_stat = stat("framework.bin");
$logo_stat = stat("logo.bin");
$rescue_linux_stat = stat("vmlinux.rescue.bin.lzma");


$block_size = 64 * 1024; #64Kbytes

print "bootrom image size = " . $bootrom_stat->size . " bytes\n";
print "logo image size = " . $logo_stat->size . "\n";
print "rescue image size = " . $rescue_linux_stat->size . "\n";

$bootrom_space = int( $bootrom_stat->size / $block_size ) + 1;
$logo_space = int( $logo_stat->size / $block_size ) + 1;
$rescue_linux_space = int( $rescue_linux_stat->size / $block_size ) + 1;

$flash_space = $flash_size / $block_size;
$used_space = $bootrom_space + $logo_space + $rescue_linux_space;

print "\none block : 64K\n";
print "flash block count : " . $flash_space . " \n\n";

print "bootrom : " . $bootrom_space . " blocks\n";
print "logo    : " . $logo_space . " blocks\n";
print "rescue  : " . $rescue_linux_space . " blocks\n";

if ($flash_space < $used_space)
{
	open (ERR_FILE, ">size_exceed");
	print "\n!!content size large than flash size\n";
	close (ERR_FILE);
}
