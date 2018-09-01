
#ifdef __cplusplus
extern "C" {
#endif 

extern int _kbhit();
extern int _str_to_long(char *str, long* p_val, unsigned char base);
extern int _str_to_long_with_range(char *str, long* p_val, unsigned char base, unsigned long min, unsigned long max);
extern int _str_to_bytes(const char* str, unsigned char* pBuff, unsigned int Len);
extern int _get_yes_no();
extern int _get_number(long int* pval);
extern int _get_bytes(unsigned char* pBuff, unsigned char Len);
extern int _get_bytes_with_text(const char* title, unsigned char* pBuff, unsigned char Len);
extern int fgets_ex(char* buf, int len);

extern void dump_mem(unsigned char* p_data, unsigned short len);
extern void dump_mem_with_text(const char* str, unsigned char* pData, unsigned short Len);
extern void dump_hex(unsigned char* pData, unsigned short Len);

extern int get_file_size(const char* fname);

//------------ Menu --------------

typedef struct {
    const char*      item_desc;
    void (*test_func)();    
}menu_item;

#define menu_item_cnt(menu)         (sizeof(menu) / sizeof(menu_item))

extern void show_menu(const char* title, menu_item* p_items, unsigned long n_item);

//------------ List --------------
typedef struct {
    const char*      item_desc;
    unsigned long    val;
}list_item;


#define list_item_cnt(list)         (sizeof(list) / sizeof(list_item))

extern unsigned long show_list(const char* title, list_item* p_items, unsigned long n_item);

#ifdef __cplusplus
}
#endif 
