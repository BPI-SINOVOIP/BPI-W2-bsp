#! /usr/bin/perl -w
use POSIX; 
if( $#ARGV != -1 )
{
	foreach $arg (@ARGV) {
		($name, $val) = split(/=/, $arg);
		if ($name eq "address_of_scs_params_area") {
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
		} elsif ($name eq "dte_bootcode_rtk_area_size") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$dte_bootcode_rtk_area_size = hex($val);
		} elsif ($name eq "address_of_scs_auxcode_area") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$address_of_scs_auxcode_area = hex($val);
		} elsif ($name eq "size_of_scs_auxcode_area") {
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
		} elsif ($name eq "pcpu_fw_segmentid_ext") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$pcpu_fw_segmentid_ext = hex($val);
		} elsif ($name eq "pcpu_fw_mask_msid") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$pcpu_fw_mask_msid = hex($val);
		} elsif ($name eq "pcpu_fw_version_ext") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$pcpu_fw_version_ext = hex($val);
		} elsif ($name eq "pcpu_fw_mask_vers") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$pcpu_fw_mask_vers = hex($val);
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
		} elsif ($name eq "dte_bootcode_file_path") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$dte_bootcode_file_path = $val;
		} elsif ($name eq "dte_bootcode_rtk_file_path") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$dte_bootcode_rtk_file_path = $val;
		} elsif ($name eq "release_flag") {
			printf STDOUT "NOCS argument %s=%s\n", $name, $val; 
			$release_flag = hex($val);
		} else {
			printf STDERR "Unknown NOCS argument %s=%s\n", $name, $val;
		}
	}
	#Release mode will only generate DTE_Bootcode_RTK again
	if ($release_flag == 0x0){
		#start writing NOCS_Certificate
		open(my $FD_NOCS_Certificate, '>:raw', 'Bind/NOCS_Certificate.bin.tmp') or die "Unable to open: $!";
		print $FD_NOCS_Certificate pack('L<',0x1) ;
		print $FD_NOCS_Certificate pack('L<',0x2200) ;
		print $FD_NOCS_Certificate pack('L<',$address_of_scs_params_area) ;
		print $FD_NOCS_Certificate pack('L<',0x400) ; #NOCS Cert is 1K, so Flash_Addr_Of_SCS_Param_Area  will be 1K
		for (my $i=0; $i < 120; $i++) {
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
		print $FD_PCPU_Certificate pack('L<',$pcpu_fw_mask_msid) ;
		print $FD_PCPU_Certificate pack('L<',$pcpu_fw_version_ext) ;
		print $FD_PCPU_Certificate pack('L<',$pcpu_fw_mask_vers) ;
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
		
		#decide scs_total_area_size
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
		
		#calculate size_of_scs_dtebootcode_area
		#scs_total_area_size  = size_of_scs_dtebootcode_area + size_of_scs_auxcode_area(fixed to be 64K) + NOCS Certificate area size (1K)+ SCS Params area size(8704) + SCS_uncheck area (4K)
		my $size_of_scs_dtebootcode_area = $scs_total_area_size - $size_of_scs_auxcode_area - 1024 - 8704 - 4096;
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
		print $FD_SCS_Params_Area pack('L<',$size_of_scs_auxcode_area) ; #size_of_scs_auxcode_area will be fixed to 64KB
		print $FD_SCS_Params_Area pack('L<',$address_of_scs_dtebootcode_area);
		print $FD_SCS_Params_Area pack('L<',$size_of_scs_dtebootcode_area);
		print $FD_SCS_Params_Area pack('L<',0x2600); #Flash_Address_of_SCS_Auxcode_Area is fixed to 0x2600, NOCS_Certificate size (0x400) + SCS_Params size (8552 aligned to 8704=0x2200)
		print $FD_SCS_Params_Area pack('L<',0x12600); #Flash_Address_of_SCS_DTE_Boot_Code_Area is fixed to 0x12600: Auxcode Area Flash address + 64KB(0x10000)
		print $FD_SCS_Params_Area pack('L<',$str_default_region_min_size);
		print $FD_SCS_Params_Area pack('L<',$scrambling_activation);
		print $FD_SCS_Params_Area pack('L<',$flashprotection_activation);
		print $FD_SCS_Params_Area pack('L<',$rskps_activation);
		print $FD_SCS_Params_Area pack('L<',$scs_total_area_size_1);
		print $FD_SCS_Params_Area pack('L<',$scs_total_area_size_2);
		print $FD_SCS_Params_Area pack('L<',$scs_total_area_size_3);
		print $FD_SCS_Params_Area pack('L<',$scs_total_area_size_4);
		print $FD_SCS_Params_Area pack('L<',$scs_total_area_size_selection);
		#padding to be 512B aligned(size: 8552->8704)
		for (my $i=0; $i < 152; $i++) {
			print $FD_SCS_Params_Area pack('C',0xFF) ;
		}
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

		#start writing DTE_Bootcdeo_Area	
		#calculate dte_bootcode_real_size
		if (defined $dte_bootcode_file_path){
			my $dte_bootcode_file_size = -s $dte_bootcode_file_path;
			if ($size_of_scs_dtebootcode_area < $dte_bootcode_file_size + 276){
				printf STDOUT "ERROR: illegal size_of_scs_dtebootcode_area value, need to be >= (dte_bootcode_file_size + 276) (now size_of_scs_dtebootcode_area=0x%x)\n",$size_of_scs_dtebootcode_area; 
				exit(-1);
			}
			my $dte_bootcode_padding_size = $size_of_scs_dtebootcode_area - $dte_bootcode_file_size - 276;
			printf STDOUT "dte_bootcode_padding_size = 0x%x\n", $dte_bootcode_padding_size;
			
			open(my $FD_DTEBOOTCODE_PADDING, '>:raw', 'Bind/DTE_BOOTCODE_PADDING.bin') or die "Unable to open: $!";
			#At least, one byte [KeyRightCheckID] need be padded
			for (my $i=0; $i < $dte_bootcode_padding_size; $i++) {
				print $FD_DTEBOOTCODE_PADDING pack('C',0xFF) ;
			}
			print $FD_DTEBOOTCODE_PADDING pack('L<',0x1) ; #[KeyRightCheckID] need be encrypted together
			close($FD_DTEBOOTCODE_PADDING);
			#control data excludes keyright
			open(my $FD_DTE_Bootcode_Area, '>:raw', 'Bind/DTE_Bootcode_Area.bin.tmp') or die "Unable to open: $!";
			print $FD_DTE_Bootcode_Area pack('L<',$segmentid_ext);
			print $FD_DTE_Bootcode_Area pack('L<',$mask_msid);
			print $FD_DTE_Bootcode_Area pack('L<',$version_ext);
			print $FD_DTE_Bootcode_Area pack('L<',$mask_vers);
			close($FD_DTE_Bootcode_Area);
			
			$cmd = "cat " . $dte_bootcode_file_path . " Bind/DTE_BOOTCODE_PADDING.bin Bind/DTE_Bootcode_Area.bin.tmp > Bind/DTE_Bootcode_Area.bin";
			system($cmd);
			#save Bind/dte_bootcode.bin for encryption
			$cmd = "cat " . $dte_bootcode_file_path . " Bind/DTE_BOOTCODE_PADDING.bin > Bind/dte_bootcode.bin";
			system($cmd);
		}
	}
	#start writing DTE_Bootcdeo_RTK_Area
	if (defined $dte_bootcode_rtk_file_path){
		my $dte_bootcode_rtk_file_size = -s $dte_bootcode_rtk_file_path;
		if ($dte_bootcode_rtk_area_size < $dte_bootcode_rtk_file_size + 276){
			printf STDOUT "ERROR: (dte_bootcode_rtk_file_size + 276) need to be <= 1.5M (now dte_bootcode_rtk_file_size=0x%x)\n",$dte_bootcode_rtk_file_size; 
			exit(-1);
		}
		my $dte_bootcode_rtk_padding_size = $dte_bootcode_rtk_area_size - $dte_bootcode_rtk_file_size - 276;
		printf STDOUT "dte_bootcode_rtk_padding_size = 0x%x\n", $dte_bootcode_rtk_padding_size;
		
		open(my $FD_DTEBOOTCODE_RTK_PADDING, '>:raw', 'Bind/DTE_BOOTCODE_RTK_PADDING.bin') or die "Unable to open: $!";
		#At least, one byte [KeyRightCheckID] need be padded
		for (my $i=0; $i < $dte_bootcode_rtk_padding_size; $i++) {
			print $FD_DTEBOOTCODE_RTK_PADDING pack('C',0xFF) ;
		}
		print $FD_DTEBOOTCODE_RTK_PADDING pack('L<',0x4) ; #[KeyRightCheckID] need be encrypted together
		close($FD_DTEBOOTCODE_RTK_PADDING);
		#control data excludes keyright
		open(my $FD_DTE_Bootcode_RTK_Area, '>:raw', 'Bind/DTE_Bootcode_RTK_Area.bin.tmp') or die "Unable to open: $!";
		print $FD_DTE_Bootcode_RTK_Area pack('L<',$teeos_segmentid_ext);
		print $FD_DTE_Bootcode_RTK_Area pack('L<',$teeos_mask_msid);
		print $FD_DTE_Bootcode_RTK_Area pack('L<',$teeos_version_ext);
		print $FD_DTE_Bootcode_RTK_Area pack('L<',$teeos_mask_vers);
		close($FD_DTE_Bootcode_RTK_Area);
		
		$cmd = "cat " . $dte_bootcode_rtk_file_path . " Bind/DTE_BOOTCODE_RTK_PADDING.bin Bind/DTE_Bootcode_RTK_Area.bin.tmp > Bind/DTE_Bootcode_RTK_Area.bin";
		system($cmd);
		#save Bind/dte_bootcode_rtk.bin for encryption
		$cmd = "cat " . $dte_bootcode_rtk_file_path . " Bind/DTE_BOOTCODE_RTK_PADDING.bin > Bind/dte_bootcode_rtk.bin";
		system($cmd);
	}
}
