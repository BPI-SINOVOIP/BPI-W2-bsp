#ifndef __SC_BUFF_H__
#define __SC_BUFF_H__

#include <linux/list.h>
#include <linux/spinlock.h>
#include <linux/completion.h>

#define RX_BUFFER_SIZE      64

typedef struct {    
    struct list_head    list;    
    unsigned char       status;   
    
#define WAIT_XMIT       0xff
#define XMIT_OK         0x00
#define XMIT_FAIL       0x01    
#define XMIT_TIMEOUT    0x02
#define XMIT_ABORT      0x03
  
    unsigned char       flags;    
#define NONBLOCK        0x80    
    struct completion   complete;        
    unsigned char*      head;          
    unsigned char*      data;          
    unsigned char*      tail;          
    unsigned char*      end;    
    unsigned char       len;        
}sc_buff;


typedef struct {
    spinlock_t          lock;
    struct list_head    list;     
    unsigned int        qlen;                   
}sc_buff_head;

void            scb_queue_head_init(sc_buff_head *head);

void            scb_queue_head  (sc_buff_head *head, sc_buff* scb);

void            scb_queue_tail  (sc_buff_head *head, sc_buff* scb);

sc_buff*        scb_dequeue     (sc_buff_head *head);

sc_buff*        scb_dequeue_tail(sc_buff_head *head);

void            scb_queue_purge (sc_buff_head *head);

unsigned int    scb_queue_len   (const sc_buff_head *head);

sc_buff*        alloc_scb(size_t size);

void            kfree_scb(sc_buff* scb);

void            init_scb(sc_buff* buff, unsigned char* p_buff, size_t size);

void            scb_reserve (sc_buff* scb, unsigned int len);

unsigned char*  scb_put     (sc_buff* scb, unsigned int len);

unsigned char*  scb_push    (sc_buff* scb, unsigned int len);

unsigned char*  scb_pull    (sc_buff* scb, unsigned int len);

void            scb_trim    (sc_buff *scb, unsigned int len);

void            scb_purge   (sc_buff* scb);

int             scb_tailroom(const sc_buff* scb);






#endif  //__SC_BUFF_H__


