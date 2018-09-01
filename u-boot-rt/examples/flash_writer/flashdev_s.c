//#include <common.h>
//#include <exports.h>
//#include <linux/types.h>

#include <rbus/sb2_reg.h>
#include "flashdev_s.h"
#include "sysdefs.h"
#include "dvrboot_inc/util.h"
#include "uart_reg.h"
#include "dvrboot_inc/io.h"
#include "uart.h"

void _sync(void)
{
	sync();
}


void spi_switch_read_mode(void)
{
	_sync();
    rtd_outl(SB2_SFC_OPCODE, 0x00000003); //switch flash to read mode
    rtd_outl(SB2_SFC_CTL, 0x00000018); //command cycle
	_sync();
}

void spi_hexdump( const char * str, unsigned int start_address, unsigned int length )
{
	unsigned int i, j, rows, count;
	volatile unsigned char tmp;
	rtprintf("======================================================\n");
	rtprintf("%s(base=0x%08x)\n", str, start_address);
	count = 0;
	rows = (length+((1<<4)-1)) >> 4;
	for( i = 0; ( i < rows ) && (count < length); i++ ) {
		rtprintf("%03x :", i<<4 );
		for( j = 0; ( j < 16 ) && (count < length); j++ ) {
			tmp = rtd_inb(start_address);
			rtprintf(" %02x",  tmp );
			count++;
			start_address++;
		}
		rtprintf("\n");
	}
}

#ifdef CONFIG_VERIFY_SPI
void spi_verify_data( const char * str, unsigned int start_address,unsigned int data_address, unsigned int length )
{
	prints("check\n");
	unsigned int i, j, rows, count,count1;
	volatile unsigned char tmp,data;
	rtprintf("======================================================\n");
	rtprintf("%s(base=0x%08x)\n", str, start_address);
	count = 0;
	rows = (length+((1<<4)-1)) >> 4;
	for( i = 0; ( i < rows ) && (count < length); i++ ) {
		rtprintf("%03x :", i<<4 );	
		for( j = 0; ( j < 16 ) && (count < length); j++ ) {
			tmp = rtd_inb(start_address);
			data = rtd_inb(data_address);
			//rtprintf("(%02x,%02x)", tmp,data);
		
			if(tmp!= data){
					//rtprintf("(0x%x:%02x,%02x)",start_address, tmp,data);				
					prints("[err]address=");
					print_hex(start_address);
					prints(", value=");
					print_hex(tmp);
					prints(", origin=");
					print_hex(data);
					prints("\n");
										
				return;
			}
		
			count++;
			start_address++;
			data_address++;
		}
		rtprintf("\n");
					
	}
	prints("done\n");
}
#endif

/************************************************************************
 *
 *                          do_erase_s
 *  Description :
 *  -------------
 *  implement the flash erase
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/

int do_erase_s( void * dev,
                unsigned int * dest_address,
                unsigned int ram_byte_size )
{
    volatile unsigned char tmp;
    unsigned int address;
    unsigned int end_address;
    unsigned int size;
    s_device_type * pDevice;

    address = (unsigned int) dest_address;
    pDevice = (s_device_type *)dev;

    //rtprintf("*** %s %s %d, address=0x%08x\n", __FILE__, __FUNCTION__, __LINE__, address);
    //rtprintf("*** %s %s %d, rem_size=0x%08x\n", __FILE__, __FUNCTION__, __LINE__, ram_byte_size);
    
    // sanity check
    // ram_byte_size must be aligment to 256KB, 64KB, 32KB or 4KB
    if( pDevice->sec_4k_en == 1 ) {
    	ram_byte_size += SPI_ERASE_SIZE_4KB_MINUS_1;
    	ram_byte_size &= SPI_ERASE_SIZE_4KB_ALIGNMENT;
    	address &= SPI_ERASE_SIZE_4KB_ALIGNMENT;
    }
    else if( pDevice->sec_32k_en == 1 ) {
    	ram_byte_size += SPI_ERASE_SIZE_32KB_MINUS_1;
    	ram_byte_size &= SPI_ERASE_SIZE_32KB_ALIGNMENT;
    	address &= SPI_ERASE_SIZE_32KB_ALIGNMENT;
    }
    else if( pDevice->sec_64k_en == 1 ) {
    	ram_byte_size += SPI_ERASE_SIZE_64KB_MINUS_1;
    	ram_byte_size &= SPI_ERASE_SIZE_64KB_ALIGNMENT;
    	address &= SPI_ERASE_SIZE_64KB_ALIGNMENT;
    }
    else if( pDevice->sec_256k_en == 1 ) {
    	ram_byte_size += SPI_ERASE_SIZE_256KB_MINUS_1;
    	ram_byte_size &= SPI_ERASE_SIZE_256KB_ALIGNMENT;
    	address &= SPI_ERASE_SIZE_256KB_ALIGNMENT;
    }
    
    end_address = address-SPI_BASE_ADDR+ram_byte_size;
    
    if( end_address > pDevice->size ) {
	    #ifdef FOR_ICE_LOAD
		prints("spi : erase space over range\n");
		#endif
    	rtprintf("spi : erase space over range\n");
    	rtprintf("      ram_byte_size : 0x%08x\n", ram_byte_size);
    	rtprintf("      dest_addresss : 0x%08x\n", (unsigned int)dest_address);
    	rtprintf("      start address : 0x%08x\n", address-SPI_BASE_ADDR);
    	rtprintf("      erase size    : 0x%08x\n", ram_byte_size);
    	rtprintf("      max capacity  : 0x%08x\n", pDevice->size);
    	return -1;    	
    }

	//disable auto-prog
	rtd_outl(SB2_SFC_EN_WR,    0x00000006);
        rtd_outl(SB2_SFC_WAIT_WR,    0x00000005);

    while( ram_byte_size > 0 )
    {
        // show '/' for progress bar
	    #ifdef FOR_ICE_LOAD
		prints("/");
		#endif
        rtprintf("/");

        // write enable
        rtd_outl(SB2_SFC_OPCODE,0x00000006);
        rtd_outl(SB2_SFC_CTL,0x00000000);
		_sync();
        tmp = rtd_inb(address);

		//rtprintf("\n");
		//rtprintf("*** %s %s %d, address=0x%08x\n", __FILE__, __FUNCTION__, __LINE__, address);
		//rtprintf("*** %s %s %d, rem_size=0x%08x\n", __FILE__, __FUNCTION__, __LINE__, ram_byte_size);

		do {
			if( pDevice->sec_256k_en == 1 )
            {
                if( ram_byte_size >= 0x00040000 ) {
	                rtd_outl(SB2_SFC_OPCODE,0x000000d8);
	                rtd_outl(SB2_SFC_CTL,0x00000008);
					_sync();
	                tmp = rtd_inb(address);
	                size = 0x00040000;
	                break;
	            }
            }
			if( pDevice->sec_64k_en == 1 )
            {
                if( ram_byte_size >= 0x00010000 ) {
	                rtd_outl(SB2_SFC_OPCODE,0x000000d8);
                	rtd_outl(SB2_SFC_CTL,0x00000008);
					_sync();
                	tmp = rtd_inb(address);
                	size = 0x00010000;
	                break;
	            }
            }
			if( pDevice->sec_32k_en == 1 )
            {			
            	if( ram_byte_size >= 0x00008000 ) {
	            	rtd_outl(SB2_SFC_OPCODE,0x00000052);
	                rtd_outl(SB2_SFC_CTL,0x00000008);
					_sync();
	                tmp = rtd_inb(address);
	                size = 0x00008000;
	                break;
	            }
            }
			if( pDevice->sec_4k_en == 1 )
            {			
            	if( ram_byte_size >= 0x00001000 ) {
	            	if (pDevice->id==PMC_4Mbit)
	                    rtd_outl(SB2_SFC_OPCODE,0x000000d7);
	                else
	                    rtd_outl(SB2_SFC_OPCODE,0x00000020);
	                rtd_outl(SB2_SFC_CTL,0x00000008);
					_sync();
	                tmp = rtd_inb(address);
	                size = 0x00001000;
	                break;
	            }
            }            

		    #ifdef FOR_ICE_LOAD
			prints("spi : erase error. curr ram_byte_size = 0x");
			print_hex(ram_byte_size);
            prints("\n");
			prints("      sector 256k en: 0x");
			print_hex(pDevice->sec_256k_en);
            prints("\n");
			prints("      sector  64k en: 0x");
			print_hex(pDevice->sec_64k_en);
            prints("\n");
			prints("      sector  32k en: 0x");
			print_hex(pDevice->sec_32k_en);
            prints("\n");
			prints("      sector   4k en: 0x");
			print_hex(pDevice->sec_4k_en);
            prints("\n");
			prints("      page_program  : 0x");
			print_hex(pDevice->page_program);
            prints("\n");
			prints("      max capacity  : 0x");
			print_hex(pDevice->size);
            prints("\n");
			prints("      spi type name : ");
            prints(pDevice->string);
            prints("\n");
			#endif
            rtprintf("\n");
            rtprintf("spi : erase error. curr ram_byte_size = 0x%08x\n", ram_byte_size);
            rtprintf("      sector 256k en: %d\n", pDevice->sec_256k_en);
            rtprintf("      sector  64k en: %d\n", pDevice->sec_64k_en);
            rtprintf("      sector  32k en: %d\n", pDevice->sec_32k_en);
            rtprintf("      sector   4k en: %d\n", pDevice->sec_4k_en);
            rtprintf("      page_program  : %d\n", pDevice->page_program);
            rtprintf("      max capacity  : 0x%08x\n", pDevice->size);
            rtprintf("      spi type name : %s\n", pDevice->string);
	//enable auto-prog
	rtd_outl(SB2_SFC_EN_WR,    0x00000106);
        rtd_outl(SB2_SFC_WAIT_WR,    0x00000105);
            return -1;
		}
		while(0);

        /* read status registers until write operation completed*/
        do
        {
            rtd_outl(SB2_SFC_OPCODE,0x00000005);
            rtd_outl(SB2_SFC_CTL,0x00000010);
			_sync();
            tmp = rtd_inb(address);
        } while(tmp&0x1);

        //size = (ram_byte_size > size) ?  size : ram_byte_size ;
        ram_byte_size -= size;
        address += size;
    }

	//enable auto-prog
	rtd_outl(SB2_SFC_EN_WR,    0x00000106);
    rtd_outl(SB2_SFC_WAIT_WR,    0x00000105);

    return 0;
}
/************************************************************************
 *
 *                          do_write
 *  Description :
 *  -------------
 *  implement the flash write
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
int do_write_s(void *dev,
               unsigned char* array_ptr,
               unsigned int* dest,
               unsigned int   rem_size,
               unsigned int   signature,
               const unsigned int page_offset)
{
        int i = 0;
        s_device_type *device = (s_device_type *)dev;
        unsigned char *loc;

        loc = (unsigned char *)dest;

#ifdef Board_CPU_RTD1192
	sys_dcache_flush_MVA(array_ptr, rem_size);
#endif
        //add by angus
        rtd_outl(SB2_SFC_EN_WR,    0x00000106);
        rtd_outl(SB2_SFC_WAIT_WR,    0x00000105);
        rtd_outl(SB2_SFC_CE,    0x001A1307);

        //issue write command
        rtd_outl(SB2_SFC_OPCODE,  0x00000002);
        rtd_outl(SB2_SFC_CTL,  0x00000018);
		sync();

#if 0 //wilma add+  0812
        // if dest address is not on 256 byte boundary, use byte program until reach boundary
        while ((((UINT32)loc) & 0xff) && (rem_size > 0))
        {
            rtd_outb(loc++ , *array_ptr++);
            rem_size--;
        }



        //if flash support page program, we can use page program to reduce program time
        if (device->page_program)
        {
            //if writing data greater than one page(256 bytes)
            while(rem_size >= 256)
            {
#ifdef ENABLE_UART_FUNC

                /* show '.' in console */
                if ( !(i++ % 4))
                    rtd_outl(UART0_REG_BASE, 0x2f) ; //cy test
#endif

                copy_memory((UINT8 *)loc, array_ptr, 256);

                /* shift to next page to writing */
                array_ptr+=256;
                loc+=256;
                rem_size-=256;

            }//end of page program

        }//end of page program

#endif  //wilma add+  0812
        /* left data in-sufficient to one page, we write it using byte program
           or flash doesn't support page program mode */
        while(rem_size--)
        {
#ifdef ENABLE_UART_FUNC

            /* show '.' in console */
            if ((rem_size % 1024 )== 1023)
                rtd_outl(UART0_REG_BASE, 0x2e) ; //cy test
#endif

            rtd_outb(loc++ , *array_ptr++);
        }


        return 0;
}

/************************************************************************
 *
 *                          do_identify_s
 *  Description :
 *  -------------
 *  implement the identyfy flash type
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
int do_identify_s(void **dev)
{
    UINT32 id;
    UINT32 idx;
    s_device_type * pDevice;
    UINT8 * temp_ptr = (UINT8 *)SPI_BASE_ADDR;


    rtprintf("*** %s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
    
    // configure spi flash controller register
    rtd_outl(SB2_SFC_POS_LATCH,0x00000001);   //set serial flash controller latch data at rising edge

    //remove this, due to we already set this register at hw-setting
    //rtd_outl(0xb801a808,0x0101000f);   //lowering frequency, setup freq divided no

    rtd_outl(SB2_SFC_CE,0x001A1307);   //setup control edge

    // read Manufacture & device ID
    rtd_outl(SB2_SFC_OPCODE,0x0000009f);
    rtd_outl(SB2_SFC_CTL,0x00000010);
	_sync();
    id = swap_endian(rtd_inl((UINT32 *)temp_ptr));

    id >>= 8;
	#ifdef FOR_ICE_LOAD
	prints("\nnor flash id [0x");
	print_hex(id);
	prints("]\n");
	#endif
    rtprintf("\nflash id [0x%x]\n", id);
    /* find the match flash brand */
    for (idx = 0; idx < DEV_SIZE_S; idx++)
    {
        if ( s_device[idx].id == id )
        {
            //special case: the same id have two mode, check ext-id
            if (id == SPANSION_128Mbit)
            {
                /* read extended device ID */
                    rtd_outl(SB2_SFC_OPCODE,0x0000009f);
                    rtd_outl(SB2_SFC_CTL,0x00000013);
					_sync();
                    id = swap_endian(rtd_inl((UINT32 *)temp_ptr));
                    id >>= 16;
					#ifdef FOR_ICE_LOAD
					prints("\textension id [0x");
					print_hex(id);
					prints("]\n");
					#endif
                    rtprintf("\textension id [0x%x]\n", id);
                continue;
            }

            *dev = (void *)&s_device[idx];
            pDevice = &s_device[idx];

            // show flash info
		    #ifdef FOR_ICE_LOAD
			prints("      sector 256k en: 0x");
			print_hex(pDevice->sec_256k_en);
            prints("\n");
			prints("      sector  64k en: 0x");
			print_hex(pDevice->sec_64k_en);
            prints("\n");
			prints("      sector  32k en: 0x");
			print_hex(pDevice->sec_32k_en);
            prints("\n");
			prints("      sector   4k en: 0x");
			print_hex(pDevice->sec_4k_en);
            prints("\n");
			prints("      page_program  : 0x");
			print_hex(pDevice->page_program);
            prints("\n");
			prints("      max capacity  : 0x");
			print_hex(pDevice->size);
            prints("\n");
			prints("      spi type name : ");
            prints(pDevice->string);
            prints("\n");
			#endif
            rtprintf("sector 256k en: %d\n", pDevice->sec_256k_en);
            rtprintf("sector  64k en: %d\n", pDevice->sec_64k_en);
            rtprintf("sector  32k en: %d\n", pDevice->sec_32k_en);
            rtprintf("sector   4k en: %d\n", pDevice->sec_4k_en);
            rtprintf("page_program  : %d\n", pDevice->page_program);
            rtprintf("max capacity  : 0x%08x\n", pDevice->size);
            rtprintf("spi type name : %s\n", pDevice->string);

            return 0;
        }
    }

	#ifdef FOR_ICE_LOAD
	prints("ID not match try CMD 90h\n");
	#endif
    rtprintf("ID not match try CMD 90h...\n");

    //device not found, down freq and try again
    if (idx == DEV_SIZE_S)
    {
        rtd_outl(SB2_SFC_OPCODE,0x00000090);  //read id
        rtd_outl(SB2_SFC_CTL,0x00000010);  //issue command
		_sync();
        id = rtd_inl((UINT32 *)temp_ptr);
        id >>= 16;

        for (idx = 0; idx < DEV_SIZE_S; idx++)
        {
            if ( s_device[idx].id == id )
            {
                //special case: the same id have two mode, check ext-id
                if (id == SPANSION_128Mbit)
                {
                    /* read extended device ID */
                    rtd_outl(SB2_SFC_OPCODE,0x00000090);
                    rtd_outl(SB2_SFC_CTL,0x0000001b);
					_sync();
                    id = swap_endian(rtd_inl((UINT32 *)temp_ptr));
                    id >>= 16;
                    continue;
                }

                *dev = (void *)&s_device[idx];
                pDevice = &s_device[idx];

                // show flash info
                rtprintf("sector 256k en: %d\n", pDevice->sec_256k_en);
                rtprintf("sector  64k en: %d\n", pDevice->sec_64k_en);
                rtprintf("sector  32k en: %d\n", pDevice->sec_32k_en);
                rtprintf("sector   4k en: %d\n", pDevice->sec_4k_en);
                rtprintf("page_program  : %d\n", pDevice->page_program);
                rtprintf("max capacity  : 0x%08x\n", pDevice->size);
                rtprintf("spi type name : %s\n", pDevice->string);

                return 0;
            }
        }

        if (idx == DEV_SIZE_S)
        {
            *dev = (void *)0x0;
            return -1;
        }
    }

    *dev = (void *)0x0;

    return -1;
}
/************************************************************************
 *
 *                          do_init_s
 *  Description :
 *  -------------
 *  implement the init flash controller
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
int do_init_s(void *dev)
{
    UINT8 tmp;
    UINT8 * temp_ptr = (UINT8 *)SPI_BASE_ADDR;

    rtprintf("*** %s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

    // configure serial flash controller

    rtd_outl(SB2_SFC_CE,0x001A1307);   // setup control edge

    rtd_outl(SB2_SFC_WP,0x00000000);    // disable hardware potection

    // enable write status register
    rtd_outl(SB2_SFC_OPCODE,0x00000050);
    rtd_outl(SB2_SFC_CTL,0x00000000);
	_sync();
    tmp = rtd_inb(temp_ptr);
    rtd_outb(temp_ptr, 0x0);

    // write status register , no memory protection
    rtd_outl(SB2_SFC_OPCODE,0x00000001);
    rtd_outl(SB2_SFC_CTL,0x00000010);
	_sync();
    rtd_outb(temp_ptr, 0x0);

    return 0;
}
/************************************************************************
 *
 *                          do_exit_s
 *  Description :
 *  -------------
 *  implement the exit flash writing operation
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
void do_exit_s(void *dev)
{
    UINT8 tmp;
    UINT8 * temp_ptr = (UINT8 *)SPI_BASE_ADDR;

    rtprintf("*** %s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

    spi_switch_read_mode();

    tmp = rtd_inb(temp_ptr);
}
