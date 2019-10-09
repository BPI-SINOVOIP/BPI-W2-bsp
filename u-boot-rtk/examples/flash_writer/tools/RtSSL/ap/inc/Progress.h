#ifndef __PREGRESS_H__
#define __PREGRESS_H__

class Progress
{
public:    
    Progress(unsigned long min, unsigned long max, unsigned long tick);
    virtual ~Progress();
    
protected:
    unsigned long long m_tick;
    unsigned long long m_min;
    unsigned long long m_max;
    unsigned long long m_cur;        
    
private:
    
    int Update(unsigned long val);    
    
public:    
    virtual void Show(unsigned long val);    
};

#endif  //__PREGRESS_H__
