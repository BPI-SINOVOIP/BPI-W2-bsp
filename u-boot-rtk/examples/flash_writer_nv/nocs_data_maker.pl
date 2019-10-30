#! /usr/bin/perl -w
use POSIX; 
if( $#ARGV != -1 )
{
	foreach $arg (@ARGV) {
		($name, $val) = split(/=/, $arg);
		if ($name eq "size_of_scs_params_area") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val;
			$size_of_scs_params_area = hex($val);
		} elsif ($name eq "address_of_scs_params_area") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val;
			$address_of_scs_params_area = hex($val);
		} elsif ($name eq "segmentid_ext") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val;
			$segmentid_ext = hex($val);
		} elsif ($name eq "mask_msid") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$mask_msid = hex($val);
		} elsif ($name eq "version_ext") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val;
			$version_ext =hex($val);
		} elsif ($name eq "mask_vers") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$mask_vers = hex($val);
		} elsif ($name eq "address_of_scs_auxcode_area") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$address_of_scs_auxcode_area = hex($val);
		}elsif ($name eq "size_of_scs_auxcode_area") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$size_of_scs_auxcode_area = hex($val);
		} elsif ($name eq "address_of_scs_dtebootcode_area") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val;
			$address_of_scs_dtebootcode_area = hex($val);
		} elsif ($name eq "str_default_region_min_size") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$str_default_region_min_size = hex($val);
		} elsif ($name eq "scrambling_activation") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$scrambling_activation = hex($val);
		} elsif ($name eq "flashprotection_activation") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$flashprotection_activation = hex($val);
		} elsif ($name eq "rskps_activation") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$rskps_activation = hex($val);
		}elsif ($name eq "scs_total_area_size_1") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val;
			$scs_total_area_size_1 = hex($val);
		}elsif ($name eq "scs_total_area_size_2") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val;
			$scs_total_area_size_2 = hex($val);
		}elsif ($name eq "scs_total_area_size_3") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val;
			$scs_total_area_size_3 = hex($val);
		}elsif ($name eq "scs_total_area_size_4") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val;
			$scs_total_area_size_4 = hex($val);
		}elsif ($name eq "scs_total_area_size_selection") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$scs_total_area_size_selection = hex($val);
		} elsif ($name eq "address_of_bl31_area") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val;
			$address_of_bl31_area = hex($val);
		} elsif ($name eq "address_of_teeos_area") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$address_of_teeos_area =hex($val);
		} elsif ($name eq "address_of_avfw_area") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$address_of_avfw_area = hex($val);
		} elsif ($name eq "str_min_size_of_teeos_area") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$str_min_size_of_teeos_area = hex($val);
		} elsif ($name eq "str_min_size_of_avfw_area") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$str_min_size_of_avfw_area = hex($val);
		} elsif ($name eq "number_of_scramble_key") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$number_of_scramble_key = hex($val);
		} 
		
		#TEE Protect Region	
		elsif ($name eq "address_of_tee_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$address_of_tee_region = hex($val);
		} elsif ($name eq "size_of_tee_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$size_of_tee_region =hex($val);
		} elsif ($name eq "protected_of_tee_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$protected_of_tee_region = hex($val);
		} elsif ($name eq "key_idx_of_tee_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$key_idx_of_tee_region = hex($val);
		}
		
		#AVFW_TEXT Protect Region	
		elsif ($name eq "address_of_avfw_text_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$address_of_avfw_text_region = hex($val);
		} elsif ($name eq "size_of_avfw_text_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$size_of_avfw_text_region = hex($val);
		} elsif ($name eq "protected_of_avfw_text_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$protected_of_avfw_text_region = hex($val);
		} elsif ($name eq "key_idx_of_avfw_text_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$key_idx_of_avfw_text_region = hex($val);
		} 
		
		#AVFW_DATA Protect Region	
		elsif ($name eq "address_of_avfw_data_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$address_of_avfw_data_region = hex($val);
		} elsif ($name eq "size_of_avfw_data_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$size_of_avfw_data_region = hex($val);
		} elsif ($name eq "protected_of_avfw_data_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$protected_of_avfw_data_region = hex($val);
		} elsif ($name eq "key_idx_of_avfw_data_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$key_idx_of_avfw_data_region = hex($val);
		} 
		
		#AVFW_ISR Protect Region	
		elsif ($name eq "address_of_avfw_isr_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$address_of_avfw_isr_region = hex($val);
		} elsif ($name eq "size_of_avfw_isr_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$size_of_avfw_isr_region = hex($val);
		} elsif ($name eq "protected_of_avfw_isr_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$protected_of_avfw_isr_region = hex($val);
		} elsif ($name eq "key_idx_of_avfw_isr_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$key_idx_of_avfw_isr_region = hex($val);
		} 
		
		#AVFW_ENTRY Protect Region	
		elsif ($name eq "address_of_avfw_entry_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$address_of_avfw_entry_region = hex($val);
		} elsif ($name eq "size_of_avfw_entry_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$size_of_avfw_entry_region = hex($val);
		} elsif ($name eq "protected_of_avfw_entry_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$protected_of_avfw_entry_region = hex($val);
		} elsif ($name eq "key_idx_of_avfw_entry_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$key_idx_of_avfw_entry_region = hex($val);
		} 
		
		#Video_Pool Protect Region	
		elsif ($name eq "address_of_video_pool_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$address_of_video_pool_region = hex($val);
		} elsif ($name eq "size_of_video_pool_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$size_of_video_pool_region = hex($val);
		} elsif ($name eq "protected_of_video_pool_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$protected_of_video_pool_region = hex($val);
		} elsif ($name eq "key_idx_of_video_pool_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$key_idx_of_video_pool_region = hex($val);
		} 
		
		#User Protect Region	
		elsif ($name eq "address_of_user_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$address_of_user_region = hex($val);
		} elsif ($name eq "size_of_user_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$size_of_user_region = hex($val);
		} elsif ($name eq "protected_of_user_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$protected_of_user_region = hex($val);
		} elsif ($name eq "key_idx_of_user_region") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$key_idx_of_user_region = hex($val);
		} 
		
		#REE Region_1	
		elsif ($name eq "address_of_ree_region_1") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$address_of_ree_region_1 = hex($val);
		} elsif ($name eq "size_of_ree_region_1") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$size_of_ree_region_1 = hex($val);
		} elsif ($name eq "key_idx_of_ree_region_1") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$key_idx_of_ree_region_1 = hex($val);
		} 
		
		#REE Region_2	
		elsif ($name eq "address_of_ree_region_2") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$address_of_ree_region_2 = hex($val);
		} elsif ($name eq "size_of_ree_region_2") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$size_of_ree_region_2 = hex($val);
		} elsif ($name eq "key_idx_of_ree_region_2") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$key_idx_of_ree_region_2 = hex($val);
		} 
		
		#REE Region_3	
		elsif ($name eq "address_of_ree_region_3") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$address_of_ree_region_3 = hex($val);
		} elsif ($name eq "size_of_ree_region_3") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$size_of_ree_region_3 = hex($val);
		} elsif ($name eq "key_idx_of_ree_region_3") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$key_idx_of_ree_region_3 = hex($val);
		} 
		
		#REE Region_4	
		elsif ($name eq "address_of_ree_region_4") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$address_of_ree_region_4 = hex($val);
		} elsif ($name eq "size_of_ree_region_4") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$size_of_ree_region_4 = hex($val);
		} elsif ($name eq "key_idx_of_ree_region_4") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$key_idx_of_ree_region_4 = hex($val);
		} 
		
		#REE Region_5	
		elsif ($name eq "address_of_ree_region_5") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$address_of_ree_region_5 = hex($val);
		} elsif ($name eq "size_of_ree_region_5") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$size_of_ree_region_5 = hex($val);
		} elsif ($name eq "key_idx_of_ree_region_5") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$key_idx_of_ree_region_5 = hex($val);
		} 
		
		#REE Region_6	
		elsif ($name eq "address_of_ree_region_6") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$address_of_ree_region_6 = hex($val);
		} elsif ($name eq "size_of_ree_region_6") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$size_of_ree_region_6 = hex($val);
		} elsif ($name eq "key_idx_of_ree_region_6") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$key_idx_of_ree_region_6 = hex($val);
		} 
		
		#REE Region_7	
		elsif ($name eq "address_of_ree_region_7") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$address_of_ree_region_7 = hex($val);
		} elsif ($name eq "size_of_ree_region_7") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$size_of_ree_region_7 = hex($val);
		} elsif ($name eq "key_idx_of_ree_region_7") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$key_idx_of_ree_region_7 = hex($val);
		} 
		
		#REE Region_8	
		elsif ($name eq "address_of_ree_region_8") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$address_of_ree_region_8 = hex($val);
		} elsif ($name eq "size_of_ree_region_8") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$size_of_ree_region_8 = hex($val);
		} elsif ($name eq "key_idx_of_ree_region_8") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$key_idx_of_ree_region_8 = hex($val);
		} 
		
		elsif ($name eq "str_default_region_start_address") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$str_default_region_start_address = hex($val);
		} elsif ($name eq "str_resume_mode") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$str_resume_mode = hex($val);
		} elsif ($name eq "str_address_of_bl31_area") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$str_address_of_bl31_area = hex($val);
		} elsif ($name eq "str_size_of_bl31_area") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$str_size_of_bl31_area = hex($val);
		} elsif ($name eq "teeos_segmentid_ext") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$teeos_segmentid_ext = hex($val);
		} elsif ($name eq "teeos_mask_msid") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$teeos_mask_msid = hex($val);
		} elsif ($name eq "teeos_version_ext") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$teeos_version_ext = hex($val);
		} elsif ($name eq "teeos_mask_vers") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$teeos_mask_vers = hex($val);
		} elsif ($name eq "pcpu_fw_version_ext") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$pcpu_fw_version_ext = hex($val);
		} elsif ($name eq "pcpu_fw_segmentid_ext") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$pcpu_fw_segmentid_ext = hex($val);
		} elsif ($name eq "flash_protection_key") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$flash_protection_key = $val;
		} elsif ($name eq "nagrata_protection_key") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$nagrata_protection_key = $val;
		} elsif ($name eq "atf_protection_key") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$atf_protection_key = $val;
		} elsif ($name eq "dte_protection_key") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$dte_protection_key = $val;
		} elsif ($name eq "scs_external_pub_rsa_key") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$scs_external_pub_rsa_key = $val;
		} elsif ($name eq "atf_external_pub_rsa_key") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$atf_external_pub_rsa_key = $val;
		} elsif ($name eq "pcpu_external_pub_rsa_key") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$pcpu_external_pub_rsa_key = $val;
		} elsif ($name eq "dte_fw_external_pub_rsa_key") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$dte_fw_external_pub_rsa_key = $val;
		} elsif ($name eq "afw_external_pub_rsa_key") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$afw_external_pub_rsa_key = $val;
		} elsif ($name eq "hwsetting_file_path") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$hwsetting_file_path = $val;
		} elsif ($name eq "auxcode_file_path") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$auxcode_file_path = $val;
		} elsif ($name eq "pcpu_code_file_path") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$pcpu_code_file_path = $val;
		} elsif ($name eq "dte_bootcode_file_path") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$dte_bootcode_file_path = $val;
		} elsif ($name eq "secure_os_file_path") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$secure_os_file_path = $val;
		} elsif ($name eq "bl31_file_path") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$bl31_file_path = $val;
		} elsif ($name eq "dte_bootcode_rtk_file_path") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$dte_bootcode_rtk_file_path = $val;
		} else {
			printf STDERR "Unknown NOCS argument %s=%s\n", $name, $val;
		}
	}
	#start writing NOCS_Certificate
	open(my $FD_NOCS_Certificate, '>:raw', 'Bind/NOCS_Certificate.bin.tmp') or die "Unable to open: $!";
	print $FD_NOCS_Certificate pack('L<',0x1) ;
	print $FD_NOCS_Certificate pack('L<',$size_of_scs_params_area) ;
	print $FD_NOCS_Certificate pack('L<',$address_of_scs_params_area) ;
	for (my $i=0; $i < 121; $i++) {
		print $FD_NOCS_Certificate pack('L',0XFFFFFFFF) ;
	}
	print $FD_NOCS_Certificate pack('L<',$segmentid_ext) ;
	print $FD_NOCS_Certificate pack('L<',$mask_msid) ;
	print $FD_NOCS_Certificate pack('L<',$version_ext) ;
	print $FD_NOCS_Certificate pack('L<',$mask_vers) ;
	close($FD_NOCS_Certificate);
	$cmd = "cat " . $scs_external_pub_rsa_key . " Bind/NOCS_Certificate.bin.tmp > Bind/NOCS_Certificate.bin; rm  Bind/NOCS_Certificate.bin.tmp";
	system($cmd);
	
	#start writing ATF Certificate
	open(my $FD_ATF_Certificate, '>:raw', 'Bind/ATF_Certificate.bin.tmp') or die "Unable to open: $!";
	print $FD_ATF_Certificate pack('L<',0x2) ;
	for (my $i=0; $i < 123; $i++) {
		print $FD_ATF_Certificate pack('L',0XFFFFFFFF) ;
	}
	print $FD_ATF_Certificate pack('L<',$teeos_segmentid_ext) ;
	print $FD_ATF_Certificate pack('L<',$teeos_mask_msid) ;
	print $FD_ATF_Certificate pack('L<',$teeos_version_ext) ;
	print $FD_ATF_Certificate pack('L<',$teeos_mask_vers) ;
	close($FD_ATF_Certificate);
	$cmd = "cat " . $atf_external_pub_rsa_key . " Bind/ATF_Certificate.bin.tmp > Bind/ATF_Certificate.bin; rm  Bind/ATF_Certificate.bin.tmp";
	system($cmd);
	
	#start writing PCPU Certificate
	open(my $FD_PCPU_Certificate, '>:raw', 'Bind/PCPU_Certificate.bin.tmp') or die "Unable to open: $!";
	print $FD_PCPU_Certificate pack('L<',0x3) ;
	for (my $i=0; $i < 123; $i++) {
		print $FD_PCPU_Certificate pack('L',0XFFFFFFFF) ;
	}
	print $FD_PCPU_Certificate pack('L<',$pcpu_fw_segmentid_ext) ;
	print $FD_PCPU_Certificate pack('L<',$teeos_mask_msid) ;
	print $FD_PCPU_Certificate pack('L<',$pcpu_fw_version_ext) ;
	print $FD_PCPU_Certificate pack('L<',$teeos_mask_vers) ;
	close($FD_PCPU_Certificate);
	$cmd = "cat " . $pcpu_external_pub_rsa_key . " Bind/PCPU_Certificate.bin.tmp > Bind/PCPU_Certificate.bin; rm  Bind/PCPU_Certificate.bin.tmp";
	system($cmd);
	
	#start writing DTE_FW Certificate
	open(my $FD_DTE_FW_Certificate, '>:raw', 'Bind/DTE_FW_Certificate.bin.tmp') or die "Unable to open: $!";
	print $FD_DTE_FW_Certificate pack('L<',0x4) ;
	for (my $i=0; $i < 123; $i++) {
		print $FD_DTE_FW_Certificate pack('L',0XFFFFFFFF) ;
	}
	print $FD_DTE_FW_Certificate pack('L<',$teeos_segmentid_ext) ;
	print $FD_DTE_FW_Certificate pack('L<',$teeos_mask_msid) ;
	print $FD_DTE_FW_Certificate pack('L<',$teeos_version_ext) ;
	print $FD_DTE_FW_Certificate pack('L<',$teeos_mask_vers) ;
	close($FD_DTE_FW_Certificate);
	$cmd = "cat " . $dte_fw_external_pub_rsa_key . " Bind/DTE_FW_Certificate.bin.tmp > Bind/DTE_FW_Certificate.bin; rm  Bind/DTE_FW_Certificate.bin.tmp";
	system($cmd);
	
	#start writing AFW Certificate
	open(my $FD_AFW_Certificate, '>:raw', 'Bind/AFW_Certificate.bin.tmp') or die "Unable to open: $!";
	print $FD_AFW_Certificate pack('L<',0xA) ;
	for (my $i=0; $i < 123; $i++) {
		print $FD_AFW_Certificate pack('L',0XFFFFFFFF) ;
	}
	print $FD_AFW_Certificate pack('L<',$teeos_segmentid_ext) ;
	print $FD_AFW_Certificate pack('L<',$teeos_mask_msid) ;
	print $FD_AFW_Certificate pack('L<',$teeos_version_ext) ;
	print $FD_AFW_Certificate pack('L<',$teeos_mask_vers) ;
	close($FD_AFW_Certificate);
	$cmd = "cat " . $afw_external_pub_rsa_key . " Bind/AFW_Certificate.bin.tmp > Bind/AFW_Certificate.bin; rm  Bind/AFW_Certificate.bin.tmp";
	system($cmd);
	
	#calculate size_of_scs_dtebootcode_area
	my $size_of_scs_dtebootcode_area = 0;
	my $scs_total_area_size = 0;
	if ($scs_total_area_size_selection == 0x1){
		$scs_total_area_size = $scs_total_area_size_1;
	}
	elsif ($scs_total_area_size_selection == 0x2){
		$scs_total_area_size = $scs_total_area_size_2;
	}
	elsif ($scs_total_area_size_selection == 0x3){
		$scs_total_area_size = $scs_total_area_size_3;
	}
	elsif ($scs_total_area_size_selection == 0x4){
		$scs_total_area_size = $scs_total_area_size_4;
	}
	else{
		printf STDOUT "ERROR: illegal scs_total_area_size_selection value, need to be 1~4 (input=%d)\n",$scs_total_area_size_selection;
		exit(-1);
	}
	#scs_total_area_size  = size_of_scs_dtebootcode_area + size_of_scs_auxcode_area + NOCS Certificate area size (1K)+ SCS Params area size + SCS_uncheck area (4K)
	$size_of_scs_dtebootcode_area = $scs_total_area_size - $size_of_scs_auxcode_area - 1024 - $size_of_scs_params_area - 4096;
	if ($size_of_scs_dtebootcode_area < 0x8000){
		printf STDOUT "ERROR: illegal size_of_scs_dtebootcode_area value, need to be >= 32KB (now size_of_scs_dtebootcode_area=0x%x)\n",$size_of_scs_dtebootcode_area; 
		exit(-1);
	}
	printf STDOUT "size_of_scs_dtebootcode_area=0x%x\n", $size_of_scs_dtebootcode_area; 
	
	#start writing SCS_Parmas_Area
	open(my $FD_SCS_Params_Area, '>:raw', 'Bind/SCS_Params_Area.bin.tmp1') or die "Unable to open: $!";
	print $FD_SCS_Params_Area pack('L<',0x1) ;
	print $FD_SCS_Params_Area pack('L',0XFFFFFFFF) ; #External_Flash_Device_Params
	close($FD_SCS_Params_Area);	
	
	open($FD_SCS_Params_Area, '>:raw', 'Bind/SCS_Params_Area.bin.tmp2') or die "Unable to open: $!";
	print $FD_SCS_Params_Area pack('L',0XFFFFFFFF) ; #SCS_Boot_Specific_Params
	print $FD_SCS_Params_Area pack('L<',$address_of_scs_auxcode_area);
	print $FD_SCS_Params_Area pack('L<',$size_of_scs_auxcode_area) ;
	print $FD_SCS_Params_Area pack('L<',$address_of_scs_dtebootcode_area);
	print $FD_SCS_Params_Area pack('L<',$size_of_scs_dtebootcode_area);
	print $FD_SCS_Params_Area pack('L<',$str_default_region_min_size);
	print $FD_SCS_Params_Area pack('L<',$scrambling_activation);
	print $FD_SCS_Params_Area pack('L<',$flashprotection_activation);
	print $FD_SCS_Params_Area pack('L<',$rskps_activation);
	print $FD_SCS_Params_Area pack('L<',$scs_total_area_size_1);
	print $FD_SCS_Params_Area pack('L<',$scs_total_area_size_2);
	print $FD_SCS_Params_Area pack('L<',$scs_total_area_size_3);
	print $FD_SCS_Params_Area pack('L<',$scs_total_area_size_4);
	print $FD_SCS_Params_Area pack('L<',$scs_total_area_size_selection);
	print $FD_SCS_Params_Area pack('L<',$segmentid_ext);
	print $FD_SCS_Params_Area pack('L<',$mask_msid);
	print $FD_SCS_Params_Area pack('L<',$version_ext);
	print $FD_SCS_Params_Area pack('L<',$mask_vers);
	close($FD_SCS_Params_Area);
	#don't remove SCS_Params_Area.bin, it need to be concatenated the flash_protection_key_enc in Makefile
	$cmd = "cat Bind/SCS_Params_Area.bin.tmp1 " . $hwsetting_file_path . " Bind/SCS_Params_Area.bin.tmp2 "  . $flash_protection_key . " > Bind/SCS_Params_Area.bin";
	system($cmd);
	
	#start writing RTK_Parmas_Area
	open(my $FD_RTK_Params_Area, '>:raw', 'Bind/RTK_Params_Area.bin.tmp') or die "Unable to open: $!";
	print $FD_RTK_Params_Area pack('L<',0x2) ;
	print $FD_RTK_Params_Area pack('L<',$address_of_bl31_area);
	print $FD_RTK_Params_Area pack('L<',$address_of_teeos_area) ;
	print $FD_RTK_Params_Area pack('L<',$address_of_avfw_area);
	print $FD_RTK_Params_Area pack('L<',$str_min_size_of_teeos_area);
	print $FD_RTK_Params_Area pack('L<',$str_min_size_of_avfw_area);
	print $FD_RTK_Params_Area pack('L<',$number_of_scramble_key);
	
	#TEE Region
	print $FD_RTK_Params_Area pack('L<',$address_of_tee_region);
	print $FD_RTK_Params_Area pack('L<',$size_of_tee_region);
	print $FD_RTK_Params_Area pack('L<',$protected_of_tee_region);
	print $FD_RTK_Params_Area pack('L<',$key_idx_of_tee_region);
	print $FD_RTK_Params_Area pack('L<',~$size_of_tee_region);
	
	#AVFW_TEXT Region
	print $FD_RTK_Params_Area pack('L<',$address_of_avfw_text_region);
	print $FD_RTK_Params_Area pack('L<',$size_of_avfw_text_region);
	print $FD_RTK_Params_Area pack('L<',$protected_of_avfw_text_region);
	print $FD_RTK_Params_Area pack('L<',$key_idx_of_avfw_text_region);
	print $FD_RTK_Params_Area pack('L<',~$size_of_avfw_text_region);
	
	#AVFW_DATA Region
	print $FD_RTK_Params_Area pack('L<',$address_of_avfw_data_region);
	print $FD_RTK_Params_Area pack('L<',$size_of_avfw_data_region);
	print $FD_RTK_Params_Area pack('L<',$protected_of_avfw_data_region);
	print $FD_RTK_Params_Area pack('L<',$key_idx_of_avfw_data_region);
	print $FD_RTK_Params_Area pack('L<',~$size_of_avfw_data_region);
	
	#AVFW_ISR Region
	print $FD_RTK_Params_Area pack('L<',$address_of_avfw_isr_region);
	print $FD_RTK_Params_Area pack('L<',$size_of_avfw_isr_region);
	print $FD_RTK_Params_Area pack('L<',$protected_of_avfw_isr_region);
	print $FD_RTK_Params_Area pack('L<',$key_idx_of_avfw_isr_region);
	print $FD_RTK_Params_Area pack('L<',~$size_of_avfw_isr_region);
	
	#AVFW_ENTRY Region
	print $FD_RTK_Params_Area pack('L<',$address_of_avfw_entry_region);
	print $FD_RTK_Params_Area pack('L<',$size_of_avfw_entry_region);
	print $FD_RTK_Params_Area pack('L<',$protected_of_avfw_entry_region);
	print $FD_RTK_Params_Area pack('L<',$key_idx_of_avfw_entry_region);
	print $FD_RTK_Params_Area pack('L<',~$size_of_avfw_entry_region);
	
	#Video_Pool Region
	print $FD_RTK_Params_Area pack('L<',$address_of_video_pool_region);
	print $FD_RTK_Params_Area pack('L<',$size_of_video_pool_region);
	print $FD_RTK_Params_Area pack('L<',$protected_of_video_pool_region);
	print $FD_RTK_Params_Area pack('L<',$key_idx_of_video_pool_region);
	print $FD_RTK_Params_Area pack('L<',~$size_of_video_pool_region);
	
	#User Region
	print $FD_RTK_Params_Area pack('L<',$address_of_user_region);
	print $FD_RTK_Params_Area pack('L<',$size_of_user_region);
	print $FD_RTK_Params_Area pack('L<',$protected_of_user_region);
	print $FD_RTK_Params_Area pack('L<',$key_idx_of_user_region);
	print $FD_RTK_Params_Area pack('L<',~$size_of_user_region);
	
	#REE Region 1
	print $FD_RTK_Params_Area pack('L<',$address_of_ree_region_1);
	print $FD_RTK_Params_Area pack('L<',$size_of_ree_region_1);
	print $FD_RTK_Params_Area pack('L<',$key_idx_of_ree_region_1);
	print $FD_RTK_Params_Area pack('L<',~$size_of_ree_region_1);
	
	#REE Region 2
	print $FD_RTK_Params_Area pack('L<',$address_of_ree_region_2);
	print $FD_RTK_Params_Area pack('L<',$size_of_ree_region_2);
	print $FD_RTK_Params_Area pack('L<',$key_idx_of_ree_region_2);
	print $FD_RTK_Params_Area pack('L<',~$size_of_ree_region_2);
	
	#REE Region 3
	print $FD_RTK_Params_Area pack('L<',$address_of_ree_region_3);
	print $FD_RTK_Params_Area pack('L<',$size_of_ree_region_3);
	print $FD_RTK_Params_Area pack('L<',$key_idx_of_ree_region_3);
	print $FD_RTK_Params_Area pack('L<',~$size_of_ree_region_3);
	
	#REE Region 4
	print $FD_RTK_Params_Area pack('L<',$address_of_ree_region_4);
	print $FD_RTK_Params_Area pack('L<',$size_of_ree_region_4);
	print $FD_RTK_Params_Area pack('L<',$key_idx_of_ree_region_4);
	print $FD_RTK_Params_Area pack('L<',~$size_of_ree_region_4);
	
	#REE Region 5
	print $FD_RTK_Params_Area pack('L<',$address_of_ree_region_5);
	print $FD_RTK_Params_Area pack('L<',$size_of_ree_region_5);
	print $FD_RTK_Params_Area pack('L<',$key_idx_of_ree_region_5);
	print $FD_RTK_Params_Area pack('L<',~$size_of_ree_region_5);
	
	#REE Region 6
	print $FD_RTK_Params_Area pack('L<',$address_of_ree_region_6);
	print $FD_RTK_Params_Area pack('L<',$size_of_ree_region_6);
	print $FD_RTK_Params_Area pack('L<',$key_idx_of_ree_region_6);
	print $FD_RTK_Params_Area pack('L<',~$size_of_ree_region_6);
	
	#REE Region 7
	print $FD_RTK_Params_Area pack('L<',$address_of_ree_region_7);
	print $FD_RTK_Params_Area pack('L<',$size_of_ree_region_7);
	print $FD_RTK_Params_Area pack('L<',$key_idx_of_ree_region_7);
	print $FD_RTK_Params_Area pack('L<',~$size_of_ree_region_7);
	
	#REE Region 8
	print $FD_RTK_Params_Area pack('L<',$address_of_ree_region_8);
	print $FD_RTK_Params_Area pack('L<',$size_of_ree_region_8);
	print $FD_RTK_Params_Area pack('L<',$key_idx_of_ree_region_8);
	print $FD_RTK_Params_Area pack('L<',~$size_of_ree_region_8);
	
	print $FD_RTK_Params_Area pack('L<',$str_default_region_start_address);
	print $FD_RTK_Params_Area pack('L<',$str_resume_mode);
	print $FD_RTK_Params_Area pack('L<',$str_address_of_bl31_area);
	print $FD_RTK_Params_Area pack('L<',$str_size_of_bl31_area);
	print $FD_RTK_Params_Area pack('L<',$teeos_segmentid_ext) ;
	print $FD_RTK_Params_Area pack('L<',$teeos_mask_msid) ;
	print $FD_RTK_Params_Area pack('L<',$teeos_version_ext) ;
	print $FD_RTK_Params_Area pack('L<',$teeos_mask_vers) ;
	close($FD_RTK_Params_Area);
	#don't remove RTK_Params_Area.bin, it need to be concatenated the atf_protection_key_enc/dte_protection_key_enc in Makefile
	$cmd = "cat Bind/RTK_Params_Area.bin.tmp " . $atf_protection_key . " " . $dte_protection_key  . " > Bind/RTK_Params_Area.bin";
	system($cmd);
	
	#start writing SCS_Auxcode_Area
	open(my $FD_SCS_Auxcode_Area, '>:raw', 'Bind/Auxcode_Area.bin.tmp') or die "Unable to open: $!";
	print $FD_SCS_Auxcode_Area pack('L<',0x1) ;
	print $FD_SCS_Auxcode_Area pack('L<',$segmentid_ext);
	print $FD_SCS_Auxcode_Area pack('L<',$mask_msid);
	print $FD_SCS_Auxcode_Area pack('L<',$version_ext);
	print $FD_SCS_Auxcode_Area pack('L<',$mask_vers);
	close($FD_SCS_Auxcode_Area);
	$cmd = "cat " . $auxcode_file_path . " Bind/Auxcode_Area.bin.tmp > Bind/Auxcode_Area.bin";
	system($cmd);
	
	#start writing PCPU_Code_Area
	open(my $FD_PCPU_Code_Area, '>:raw', 'Bind/PCPU_Code_Area.bin.tmp') or die "Unable to open: $!";
	print $FD_PCPU_Code_Area pack('L<',0x3) ;
	print $FD_PCPU_Code_Area pack('L<',$pcpu_fw_segmentid_ext);
	print $FD_PCPU_Code_Area pack('L<',$mask_msid);
	print $FD_PCPU_Code_Area pack('L<',$pcpu_fw_version_ext);
	print $FD_PCPU_Code_Area pack('L<',$mask_vers);
	print $FD_PCPU_Code_Area pack('L<',0x16151615);
	for (my $i=0; $i < 0x28; $i++) {
		print $FD_PCPU_Code_Area pack('C',0) ;
	}
	close($FD_PCPU_Code_Area);
	
	
	my $pcpu_code_file_size = -s $pcpu_code_file_path;
	if ($pcpu_code_file_size > 0x6ec0){
		printf STDOUT "ERROR: illegal pcpu_code_file_size(0x%x), need to <= 0x6EC0\n",$pcpu_code_file_size;
		exit(-1);
	}
	if ($pcpu_code_file_size < 0x6ec0){
		open(my $FD_PCPU_FW_PADDING, '>:raw', 'Bind/PCPU_FW_PADDING.bin') or die "Unable to open: $!";
		my $padding_len = 0x6ec0 - $pcpu_code_file_size;
		for (my $i=0; $i < $padding_len; $i++) {
			print $FD_PCPU_FW_PADDING pack('C',0) ;
		}
		close($FD_PCPU_FW_PADDING);
		$cmd = "cat " . $pcpu_code_file_path . " Bind/PCPU_FW_PADDING.bin Bind/PCPU_Code_Area.bin.tmp > Bind/PCPU_Code_Area.bin";
		system($cmd);
		#save Bind/pcpu_code.bin
		$cmd = "cat " . $pcpu_code_file_path . " Bind/PCPU_FW_PADDING.bin > Bind/pcpu_code.bin";
		system($cmd);
	}	
	else{
		$cmd = "cat " . $pcpu_code_file_path . " Bind/PCPU_Code_Area.bin.tmp > Bind/PCPU_Code_Area.bin";
		system($cmd);
		#save Bind/pcpu_code.bin
		$cmd = "cat " . $pcpu_code_file_path . " > Bind/pcpu_code.bin";
		system($cmd);
	}
	
	#if (($pcpu_code_file_size+24) % 64 != 0){
	#	my $padding_len = (ceil(($pcpu_code_file_size+24) / 64) * 64) - ($pcpu_code_file_size+24);
	#	for (my $i=0; $i < $padding_len; $i++) {
	#		print $FD_PCPU_Code_Area pack('C',0) ;
	#	}
	#}
	
	
	#start writing DTE_Bootcdeo_Area
	if (defined $dte_bootcode_file_path){
		open(my $FD_DTE_Bootcode_Area, '>:raw', 'Bind/DTE_Bootcode_Area.bin.tmp') or die "Unable to open: $!";
		print $FD_DTE_Bootcode_Area pack('L<',0x1) ;
		print $FD_DTE_Bootcode_Area pack('L<',$segmentid_ext);
		print $FD_DTE_Bootcode_Area pack('L<',$mask_msid);
		print $FD_DTE_Bootcode_Area pack('L<',$version_ext);
		print $FD_DTE_Bootcode_Area pack('L<',$mask_vers);
		close($FD_DTE_Bootcode_Area);
		$cmd = "cat " . $dte_bootcode_file_path . " Bind/DTE_Bootcode_Area.bin.tmp > Bind/DTE_Bootcode_Area.bin";
		system($cmd);
	}
	
	#start writing DTE_Bootcdeo_RTK_Area
	if (defined $dte_bootcode_rtk_file_path){
		open(my $FD_DTE_Bootcode_RTK_Area, '>:raw', 'Bind/DTE_Bootcode_RTK_Area.bin.tmp') or die "Unable to open: $!";
		print $FD_DTE_Bootcode_RTK_Area pack('L<',0x4) ;
		print $FD_DTE_Bootcode_RTK_Area pack('L<',$segmentid_ext);
		print $FD_DTE_Bootcode_RTK_Area pack('L<',$mask_msid);
		print $FD_DTE_Bootcode_RTK_Area pack('L<',$version_ext);
		print $FD_DTE_Bootcode_RTK_Area pack('L<',$mask_vers);
		close($FD_DTE_Bootcode_RTK_Area);
		$cmd = "cat " . $dte_bootcode_rtk_file_path . " Bind/DTE_Bootcode_RTK_Area.bin.tmp > Bind/DTE_Bootcode_RTK_Area.bin";
		system($cmd);
	}
	
	#start writing BL31_Area
	if (defined $bl31_file_path){
		open(my $FD_BL31_Area, '>:raw', 'Bind/BL31_Area.bin.tmp') or die "Unable to open: $!";
		print $FD_BL31_Area pack('L<',0x2) ;
		print $FD_BL31_Area pack('L<',$teeos_segmentid_ext);
		print $FD_BL31_Area pack('L<',$teeos_mask_msid);
		print $FD_BL31_Area pack('L<',$teeos_version_ext);
		print $FD_BL31_Area pack('L<',$teeos_mask_vers);
		close($FD_BL31_Area);
		$cmd = "cat " . $bl31_file_path . " Bind/BL31_Area.bin.tmp > Bind/BL31_Area.bin";
		system($cmd);
	}
	
	#start writing Secure_OS_Area
	if (defined $secure_os_file_path){
		open(my $FD_Secure_OS_Area, '>:raw', 'Bind/Secure_OS_Area.bin.tmp') or die "Unable to open: $!";
		print $FD_Secure_OS_Area pack('L<',0x2) ;
		print $FD_Secure_OS_Area pack('L<',$teeos_segmentid_ext);
		print $FD_Secure_OS_Area pack('L<',$teeos_mask_msid);
		print $FD_Secure_OS_Area pack('L<',$teeos_version_ext);
		print $FD_Secure_OS_Area pack('L<',$teeos_mask_vers);
		close($FD_Secure_OS_Area);
		$cmd = "cat " . $secure_os_file_path . " Bind/Secure_OS_Area.bin.tmp > Bind/Secure_OS_Area.bin";
		system($cmd);
	}
}