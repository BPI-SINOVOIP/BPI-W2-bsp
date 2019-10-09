#include <stdio.h>
#include <assert.h>
#include "Progress.h"



Progress::Progress(
    unsigned long           min, 
    unsigned long           max, 
    unsigned long           tick
    )
{    
    assert(max>min);
    assert(tick>0);
    
    m_max  = max;
    m_min  = min;    
    m_tick = tick;    
    m_cur  = 0;
}



Progress::~Progress()
{        
}



int Progress::Update(
    unsigned long           val
    )
{
    unsigned long long cur;
        
    cur = m_cur;
    m_cur = (val >= m_max) ? m_tick :            
            (val <= m_min) ? 0 : ((val - m_min) * m_tick) / (m_max - m_min);
                  
    return (m_cur == cur) ? 0 : 1;            
}

#if 0

void Progress::Show(unsigned long val)
{    
    char buff[256];
    int len;    
    unsigned long i;
    
    m_tick = 100;
    
    if (Update(val))
    {                                        
        len = sprintf(buff, "\rProgress : 0% [");    
    
        for (i=0; i<m_tick; i+=5)    
            len += sprintf(&buff[len], "%c", (i>m_cur) ? ' ' : '>');
    
        sprintf(&buff[len], "] %lld %c", m_cur ,'%');
    
        printf("%s", buff);        
    
        fflush(stdout);
    }
}


#else


void Progress::Show(unsigned long val)
{                
    m_tick = 100;
    
    if (Update(val))    
    {        
        printf("\r Progress : %lld %c", m_cur, '%');  
        fflush(stdout);          
    }        
}

#endif
