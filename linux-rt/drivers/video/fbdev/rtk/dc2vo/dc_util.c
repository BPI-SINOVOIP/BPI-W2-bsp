#include <linux/kernel.h>
#include <linux/spinlock.h>
#include <asm/io.h> 
#include "dc_rpc.h"


#define IPCREAD(x) IPCRead(&(x))
#define IPCWRITE(x,y) IPCWrite(&(x),y)

extern unsigned int G_LAST_VCTX;

__maybe_unused static unsigned int reverseInteger(unsigned int value)
{
#if 1
    return __cpu_to_be32(value);
#else
	unsigned long b0 = value & 0x000000ff;
	unsigned long b1 = (value & 0x0000ff00) >> 8;
	unsigned long b2 = (value & 0x00ff0000) >> 16;
	unsigned long b3 = (value & 0xff000000) >> 24;

	return (b0 << 24) | (b1 << 16) | (b2 << 8) | b3;
#endif
}

__maybe_unused static unsigned long long reverseLongInteger(unsigned long long value)
{
#if 1
    return __cpu_to_be64(value);
#else
  unsigned long long ret;
  unsigned char *des, *src;
  src = (unsigned char *)&value;
  des = (unsigned char *)&ret;
  des[0] = src[7];
  des[1] = src[6];
  des[2] = src[5];
  des[3] = src[4];
  des[4] = src[3];
  des[5] = src[2];
  des[6] = src[1];
  des[7] = src[0];
  return ret;
#endif
}


unsigned int pli_IPCReadULONG(BYTE* src)
{
#if 1
    return __be32_to_cpu(readl(src));
#else
  volatile unsigned int A;  // prevent gcc -O3 optimization to create non-atomic access
	if (((int)src & 0x3) != 0)
		printk("error in pli_IPCReadULONG()...\n");
	A = *(unsigned int *)src;
	return reverseInteger(A);
#endif
}


unsigned long long  pli_IPCReadULONGLONG(BYTE* src)
{
#if 1

#if defined(CONFIG_ARCH_MULTI_V7)
    return __be32_to_cpu(readl(src));
#else
    return __be64_to_cpu(readq(src));
#endif

#else
    volatile unsigned long long A;  // prevent gcc -O3 optimization to create non-atomic access
	if (((int)src & 0x3) != 0)
		printk("error in pli_IPCReadULONG()...\n");

	A = *(unsigned long long*)src;
	return reverseLongInteger(A);
#endif
}

void    pli_IPCWriteULONG(BYTE* des, unsigned int data)
{
#if 1
    return writel(__cpu_to_be32(data), des);
#else
  volatile unsigned int A;  // prevent gcc -O3 optimization to create non-atomic access
	if (((int)des & 0x3) != 0)
		printk("error in pli_IPCWriteULONG()...\n");

	A = reverseInteger(data);
	*(unsigned int *)des = A;
#endif
}
void    pli_IPCWriteULONGLONG(BYTE* des, unsigned long long data)
{
#if 1

#if defined(CONFIG_ARCH_MULTI_V7)
    return writel(__cpu_to_be32(data), des);
#else
    return writeq(__cpu_to_be64(data), des);
#endif

#else
  volatile unsigned long long A; // prevent gcc -O3 optimization to create non-atomic access
	if (((int)des & 0x3) != 0)
		printk("error in pli_IPCWriteULONG()...\n");
	A = reverseLongInteger(data);
	*(unsigned long long*)des = A;
#endif
}



void pli_ipcCopyMemory(void * p_des, void * p_src, unsigned long len)
{
#if 1
    volatile unsigned char * des = (volatile unsigned char *) p_des;
    volatile unsigned char * src = (volatile unsigned char *) p_src;
    int i;
    //printk("[%s] des:%p src:%p size:%lu\n", __func__, des, src, len);
    for (i = 0; i < len; i+=4)
        writel(__cpu_to_be32(readl(&src[i])), &des[i]);
#else
	unsigned long i;
	unsigned int /*long*/ *psrc, *pdes;

	if ((((int)src & 0x3) != 0) || (((int)des & 0x3) != 0) || ((len & 0x3) != 0)) {
		printk("error in pli_IPCCopyMemory() %x %x %lu\n", (unsigned int)(des),
			(unsigned int)(src), len);

	}

	for (i = 0; i < len; i+=4) {
        writel(__cpu_to_be32(readl(&src[i])), &des[i]);
		psrc = (unsigned int *)&src[i];
		pdes = (unsigned int *)&des[i];
		*pdes = reverseInteger(*psrc);
		printf("%x, %x...\n", src[i], des[i]);
	}
#endif
}

__maybe_unused static DEFINE_SPINLOCK(lock);
__maybe_unused static DEFINE_SPINLOCK(wlock);

int ICQ_WriteCmd (void *cmd, RINGBUFFER_HEADER* rbHeader, void *rbHeaderBase)
{
    //spin_lock_irq(&lock);
    volatile void * base_iomap = rbHeaderBase;
    unsigned int size  = ((INBAND_CMD_PKT_HEADER *)cmd)->size;
    unsigned int read  = pli_IPCReadULONG((BYTE*)&rbHeader->readPtr[0]) /*| 0xa0000000*/;
    unsigned int write = pli_IPCReadULONG((BYTE*)&(rbHeader->writePtr)) /*| 0xa0000000*/;
    unsigned int base  = pli_IPCReadULONG((BYTE*)&(rbHeader->beginAddr))/*| 0xa0000000*/;
    unsigned int b_size = pli_IPCReadULONG((BYTE*)&(rbHeader->size))/*| 0xa0000000*/;
#if 1
    unsigned int limit = base + b_size;
#else
    unsigned int limit = (rbHeader->beginAddr + rbHeader->size);
	limit = pli_IPCReadULONG((BYTE*)&limit) /*| 0xa0000000*/;
#endif
    //printk("[%s] r:%x w:%x size:%u base:%u limit:%u\n", __func__, read, write, size, base, limit);

    if ( read + (read > write ? 0 : limit - base) - write > size )
    {
        //spin_lock_irq(&wlock);
      if ( write + size <= limit ) {
          unsigned long offset = write - base;
          void * write_io = (void*)((unsigned long) base_iomap + offset);
          pli_ipcCopyMemory ((void *)write_io, cmd, size) ;
      }
      else
      {
          unsigned long offset = write - base;
          void * write_io = (void*)((unsigned long) base_iomap + offset);
          pli_ipcCopyMemory ((void *)write_io, cmd, limit - write) ;
          pli_ipcCopyMemory ((void *)base_iomap,  (void *)((unsigned long)cmd + limit - write), size - (limit - write)) ;
      }

		write += size ;
		write = write < limit ? write : write - (limit - base) ;

        #if 0
        { /* writecombine */
            unsigned int offset = write - base;
            volatile int temp_read = * (volatile int *)base_iomap + offset;
        }
        #endif

        //spin_unlock_irq(&wlock);
		rbHeader->writePtr =  pli_IPCReadULONG((BYTE*)&write);

        #if 0
        { /* writecombine */
            volatile int temp_read = rbHeader->writePtr;
        }
        #endif

	  	//printk("new wp:0x%x r:0x%x\n", write, read);

		// sb2 flush
		//*(volatile unsigned int *)0xb801a020;       // sb2 flush
		//__asm__ volatile ("sync");
   	}
	else
	{
		printk("errQ r:%x w:%x size:%u base:%u limit:%u\n", read, write, size, base, limit);

        goto err;
	}

    //spin_unlock_irq(&lock);
 	return 0;
err:
    //spin_unlock_irq(&lock);
    return -1;
}

void clkGetPresentation(REFCLOCK* clk, DC_PRESENTATION_INFO *pos)
{
	//printk("dcA 0x%x %llx\n", (unsigned int)clk, clk->videoSystemPTS);
	if( clk != 0)
	{
    		//pos->videoSystemPTS = pli_IPCReadULONGLONG( (BYTE*)&clk->videoSystemPTS );
	    pos->videoContext   = pli_IPCReadULONG( (BYTE*)&clk->videoContext);
	    //pos->videoEndOfSegment = pli_IPCReadULONG( (BYTE*)&clk->videoEndOfSegment);
	}
	else
		pos->videoContext = -1U;

}
void clkResetPresentation(REFCLOCK* clk)
{
	if( clk != 0)
	{
        pli_IPCWriteULONGLONG( (BYTE*)&clk->videoSystemPTS, -1U);
        pli_IPCWriteULONGLONG( (BYTE*)&clk->audioSystemPTS, -1U);
        pli_IPCWriteULONGLONG( (BYTE*)&clk->videoRPTS,      -1U);
        pli_IPCWriteULONGLONG((BYTE*)&clk->audioRPTS,       -1U);
        pli_IPCWriteULONG((BYTE*)&clk->videoContext,        -1U);
        pli_IPCWriteULONG((BYTE*)&clk->audioContext,        -1U);
        pli_IPCWriteULONG((BYTE*)&clk->videoEndOfSegment,   -1U);
#ifdef DC2VO_SUPPORT_MEMORY_TRASH
        pli_IPCWriteULONG((BYTE*)&clk->memorytrashContext,  -1U);
#endif /* End of DC2VO_SUPPORT_MEMORY_TRASH */
	}

}

