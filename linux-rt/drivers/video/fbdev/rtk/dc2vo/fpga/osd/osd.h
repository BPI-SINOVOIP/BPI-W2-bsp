#ifndef __FPGA_OSD_H__
#define __FPGA_OSD_H__
typedef struct
{
  unsigned int last:1 ;
  unsigned int addr:31 ;

} VO_OSD_WIN_NEXT_ADDR ;

typedef struct
{
  unsigned int y:16 ;
  unsigned int x:16 ;

} VO_OSD_WIN_XY ;

typedef struct
{
  unsigned int height:16 ;
  unsigned int width:16 ;

} VO_OSD_WIN_WH ;


typedef struct
{
  unsigned int extendMode:1 ;
  unsigned int rgbOrder:3 ;
  unsigned int alphaType:1 ;
  unsigned int alphaEn:1 ;
  unsigned int storageMode:1 ;
  unsigned int objType:1 ;
  unsigned int alpha:8 ;
  unsigned int reserved1:6 ;
  unsigned int littleEndian:1 ;
  unsigned int keepPreCLUT:1 ;
  unsigned int reserved2:3 ;
  unsigned int type:5 ;

} VO_OSD_WIN_ATTR ;


typedef struct
{
  unsigned int reserved:7 ;
  unsigned int keyEn:1 ;
  unsigned int key:24 ;

}VO_OSD_WIN_KEY ;


typedef struct
{
  unsigned int objYoffset:16 ;
  unsigned int objXoffset:16 ;

} VO_OSD_WIN_INIT ;


typedef struct
{
  VO_OSD_WIN_NEXT_ADDR nxtAddr ;
  /* Window Region */
  VO_OSD_WIN_XY   winXY ;
  VO_OSD_WIN_WH   winWH ;
  /* Window Attribute */
  VO_OSD_WIN_ATTR attr ;
  unsigned int    CLUT_addr ;
  VO_OSD_WIN_KEY  colorKey ;
  unsigned int    top_addr ;    /* top or progressive OSD start address (sequential) or index (block mode) */
  unsigned int    bot_addr ;    /* bottom OSD start address (sequential) or index (block mode) */
  unsigned int    pitch ;
  VO_OSD_WIN_INIT objOffset ;

  unsigned int    reserved1;
  unsigned int    reserved2;

} VO_OSD_WIN ;

typedef struct {
    unsigned int magic; //11223344 means OK
    unsigned int state;//0:OFF 1:ON
    unsigned int order;//0~2:
    unsigned int phyAddr;
    unsigned int Height;
    unsigned int Width;
    unsigned int attr_rgbOrder;
    unsigned int attr_type;
    unsigned int reserve[6];
} OSD_STATE;

typedef struct {
    unsigned int magic; //11223344 means OK
    unsigned int state;  //0:OFF 1:ON
    unsigned int Y_addr;
    unsigned int U_addr;
    unsigned int YUVFormat; //0:420 1:422
    unsigned int width;
    unsigned int height;
    unsigned int Y_pitch;
    unsigned int C_pitch;
    unsigned int first;  // 0~2 top:2
    unsigned int pts_inc;
    unsigned int PTSH;
    unsigned int PTSL;
//    unsigned int pRefClock;
} YUV_STATE_V0;

typedef struct {
    unsigned int magic; //11223344 means OK
    unsigned int state;  //0:OFF 1:ON
    unsigned int Y_addr;
    unsigned int U_addr;
    unsigned int YUVFormat; //0:420 1:422
    unsigned int width;
    unsigned int height;
    unsigned int Y_pitch;
    unsigned int C_pitch;
    unsigned int first;  // 0~2 top:2
    unsigned int pts_inc;
    unsigned int PTSH;
    unsigned int PTSL;
    unsigned int pRefClock;
    unsigned int dst_x;
    unsigned int dst_y;
    unsigned int dst_width;
    unsigned int dst_height;
} YUV_STATE;

typedef struct {
    unsigned int dst_x;
    unsigned int dst_y;
    unsigned int dst_width;
    unsigned int dst_height;
} WINDOW_INFO;

typedef struct {
    unsigned int phyAddr;
    unsigned int reserve[7];
} VO_RETURN;

typedef struct{
    unsigned int magic;  //0x11223344 means valid data
    unsigned int width;  //vo resolution: width
    unsigned int height; //vo resolution: height
} VO_RESOLUTION_INFO ;

#define OSD_IOC_MAGIC 'e'
#define GET_OSD_STATE   _IO (OSD_IOC_MAGIC, 100)
#define SET_OSD_STATE   _IO (OSD_IOC_MAGIC, 101)
#define OSD_STATE_RESET _IO (OSD_IOC_MAGIC, 102)
#define OSD_STATE_CLOSE _IO (OSD_IOC_MAGIC, 103)
#define OSD_STATE_OPEN  _IO (OSD_IOC_MAGIC, 104)
#define WRITE_YUV_STATE _IO (OSD_IOC_MAGIC, 105)
#define READ_YUV_STATE  _IO (OSD_IOC_MAGIC, 106)
#define READ_YUV_RETURN _IO (OSD_IOC_MAGIC, 107)
#define YUV_WINDOW_GET  _IO (OSD_IOC_MAGIC, 108)
#define YUV_WINDOW_SET  _IO (OSD_IOC_MAGIC, 109)
#define YUV_WINDOW_OPEN  _IO (OSD_IOC_MAGIC, 110)
#define YUV_WINDOW_CLOSE _IO (OSD_IOC_MAGIC, 111)

#define VO_RESOLUTION_GET _IO (OSD_IOC_MAGIC, 200)
#define VO_RESOLUTION_SET _IO (OSD_IOC_MAGIC, 201)

int OSDShowPic(unsigned int srcW,unsigned int srcH,unsigned int pImage);
int OSDShowPic2(unsigned int srcW,unsigned int srcH,unsigned int pImage);
int OSD_Ioctl(unsigned int cmd, unsigned int arg);

#endif
