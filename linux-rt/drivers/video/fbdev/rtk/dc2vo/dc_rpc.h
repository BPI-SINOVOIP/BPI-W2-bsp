
/*
kjw note:**
	need to sync with rpc_common.h
*/


#ifndef __DC_RPC_H__
#define __DC_RPC_H__

typedef unsigned char BYTE;

typedef enum _tagAVSyncMode{
    AVSYNC_FORCED_SLAVE,
    AVSYNC_FORCED_MASTER,
    AVSYNC_AUTO_SLAVE,
    AVSYNC_AUTO_MASTER,
    AVSYNC_AUTO_MASTER_NO_SKIP,
    AVSYNC_AUTO_MASTER_CONSTANT_DELAY   /* after getback mastership, it become force master */
} AVSYNC_MODE;

struct _tagMastership {
  unsigned char systemMode;  /* enum AVSYNC_MODE */
  unsigned char videoMode;   /* enum AVSYNC_MODE */
  unsigned char audioMode;   /* enum AVSYNC_MODE */
  unsigned char masterState; /* enum AUTOMASTER_STATE */
};
typedef struct _tagMastership MASTERSHIP;

/* change this structure, make sure to change the CReferenceClock definition*/
struct _tagRefClock {
  long long      RCD;
  unsigned int  RCD_ext;
  long long      GPTSTimeout;
  long long      videoSystemPTS;
  long long      audioSystemPTS;
  long long      videoRPTS;
  long long      audioRPTS;
  unsigned int  videoContext;
  unsigned int  audioContext;

  MASTERSHIP     mastership;
  unsigned int  videoFreeRunThreshold;
  unsigned int  audioFreeRunThreshold;
  long long      masterGPTS;   // this is the value of GPTS (hardware PTS) when master set the reference clock
  int           audioFullness;   // This flag will be turned on when AE's output buffer is almost full.
                                  // VE which is monitoring this flag will issue auto-pause then.
                                  // (0: still have enough output space for encoding.   1: AE request pause)
  int           audioPauseFlag;  // This flag will be turned on when VE decides to auto-pause.
                                  // AE which is monitoring this flag will auto-pause itself then.
                                  // (0: ignore.  1: AE have to pauseEncode immediately)

  int           VO_Underflow; // (0: VO is working properly; otherwise, VO underflow)
  int           AO_Underflow; // (0: AO is working properly; otherwise, AO underflow)
  int           videoEndOfSegment; // set to the flow EOS.eventID by VO after presenting the EOS sample
  int           audioEndOfSegment; // set to the flow EOS.eventID by AO after presenting the EOS sample
#ifdef DC2VO_SUPPORT_MEMORY_TRASH
  unsigned int  memorytrashAddr;
  unsigned int  memorytrashContext;
  unsigned char reserved[8];
#else /* DC2VO_SUPPORT_MEMORY_TRASH */
  unsigned char  reserved[16];
#endif /* End of DC2VO_SUPPORT_MEMORY_TRASH */
};
typedef struct _tagRefClock  REFCLOCK;

typedef enum _tagRingBufferType{
    RINGBUFFER_STREAM,
    RINGBUFFER_COMMAND,
    RINGBUFFER_MESSAGE,
    RINGBUFFER_VBI,
    RINGBUFFER_PTS,
    RINGBUFFER_DTVCC,
    RINGBUFFER_STREAM1,
    RINGBUFFER_COMMAND1
} RINGBUFFER_TYPE;

// Ring Buffer header is the shared memory structure
typedef struct _tagRingBufferHeader {
  unsigned int magic;   //Magic number
  unsigned int beginAddr;
  unsigned int size;
  unsigned int bufferID;  // RINGBUFFER_TYPE, choose a type from RINGBUFFER_TYPE

  unsigned int  writePtr;
  unsigned int  numOfReadPtr;
  unsigned int  reserve2;  //Reserve for Red Zone
  unsigned int  reserve3;  //Reserve for Red Zone

  unsigned int readPtr[4];

  int          fileOffset ;
  int          requestedFileOffset ;
  int          fileSize ;

  int          bSeekable ;  /* Can't be sought if data is streamed by HTTP */

} RINGBUFFER_HEADER;

//// *** need to sync with InbandApi.h  **//
typedef enum
{
  INBAND_CMD_GRAPHIC_FORMAT_RGB565            = 4,    /* 16-bit RGB    (565)  with constant alpha */
  INBAND_CMD_GRAPHIC_FORMAT_ARGB1555          = 5,    /* 16-bit ARGB   (1555) */
  INBAND_CMD_GRAPHIC_FORMAT_ARGB4444          = 6,    /* 16-bit ARGB   (4444) */
  INBAND_CMD_GRAPHIC_FORMAT_ARGB8888          = 7,    /* 32-bit ARGB   (8888) */
  INBAND_CMD_GRAPHIC_FORMAT_YCBCRA4444        = 11,   /* 16-bit YCBCRA (4444) */
  INBAND_CMD_GRAPHIC_FORMAT_YCBCRA8888        = 12,   /* 32-bit YCBCRA (8888) */
  INBAND_CMD_GRAPHIC_FORMAT_RGBA5551          = 13,   /* 16-bit RGBA   (5551) */
  INBAND_CMD_GRAPHIC_FORMAT_RGBA4444          = 14,   /* 16-bit RGBA   (4444) */
  INBAND_CMD_GRAPHIC_FORMAT_RGBA8888          = 15,   /* 32-bit RGBA   (8888) */
  INBAND_CMD_GRAPHIC_FORMAT_RGB556            = 20,   /* 16-bit RGB    (556)  with constant alpha */
  INBAND_CMD_GRAPHIC_FORMAT_RGB655            = 21,   /* 16-bit RGB    (655)  with constant alpha */
  INBAND_CMD_GRAPHIC_FORMAT_RGB888            = 22,   /* 24-bit RGB    (888)  with constant alpha */
  INBAND_CMD_GRAPHIC_FORMAT_RGB565_LITTLE     = 36,   /* litttle endian below */
  INBAND_CMD_GRAPHIC_FORMAT_ARGB1555_LITTLE   = 37,
  INBAND_CMD_GRAPHIC_FORMAT_ARGB4444_LITTLE   = 38,
  INBAND_CMD_GRAPHIC_FORMAT_ARGB8888_LITTLE   = 39,
  INBAND_CMD_GRAPHIC_FORMAT_YCBCRA4444_LITTLE = 43,
  INBAND_CMD_GRAPHIC_FORMAT_YCBCRA8888_LITTLE = 44,
  INBAND_CMD_GRAPHIC_FORMAT_RGBA5551_LITTLE   = 45,
  INBAND_CMD_GRAPHIC_FORMAT_RGBA4444_LITTLE   = 46,
  INBAND_CMD_GRAPHIC_FORMAT_RGBA8888_LITTLE   = 47,
  INBAND_CMD_GRAPHIC_FORMAT_RGB556_LITTLE     = 52,
  INBAND_CMD_GRAPHIC_FORMAT_RGB655_LITTLE     = 53,
  INBAND_CMD_GRAPHIC_FORMAT_RGB888_LITTLE     = 54

} INBAND_CMD_GRAPHIC_FORMAT ;

/** inband cmd type. I use prefix "VIDEO_DEC_" to label the cmd used in video decoder. */
typedef enum
{
  INBAND_CMD_TYPE_PTS = 0,
  INBAND_CMD_TYPE_PTS_SKIP,
  INBAND_CMD_TYPE_NEW_SEG,
  INBAND_CMD_TYPE_SEQ_END,
  INBAND_CMD_TYPE_EOS,
  INBAND_CMD_TYPE_CONTEXT,
  INBAND_CMD_TYPE_DECODE,

  /* Video Decoder In-band Command */
  VIDEO_DEC_INBAND_CMD_TYPE_VOBU,
  VIDEO_DEC_INBAND_CMD_TYPE_DVDVR_DCI_CCI,
  VIDEO_DEC_INBAND_CMD_TYPE_DVDV_VATR,

  /* MSG Type for parse mode */
  VIDEO_DEC_INBAND_CMD_TYPE_SEG_INFO,
  VIDEO_DEC_INBAND_CMD_TYPE_PIC_INFO,

  /* Sub-picture Decoder In-band Command */
  VIDEO_SUBP_INBAND_CMD_TYPE_SET_PALETTE,
  VIDEO_SUBP_INBAND_CMD_TYPE_SET_HIGHLIGHT,

  /* Video Mixer In-band Command */
  VIDEO_MIXER_INBAND_CMD_TYPE_SET_BG_COLOR,
  VIDEO_MIXER_INBAND_CMD_TYPE_SET_MIXER_RPTS,
  VIDEO_MIXER_INBAND_CMD_TYPE_BLEND,

  /* Video Scaler In-band Command */
  VIDEO_SCALER_INBAND_CMD_TYPE_OUTPUT_FMT,

  /*DivX3 resolution In-band Command*/
  VIDEO_DIVX3_INBAND_CMD_TYPE_RESOLUTION,

  /*MPEG4 DivX4 detected In-band command*/
  VIDEO_MPEG4_INBAND_CMD_TYPE_DIVX4,
  /* Audio In-band Commands Start Here */

  /* DV In-band Commands */
  VIDEO_DV_INBAND_CMD_TYPE_VAUX,
  VIDEO_DV_INBAND_CMD_TYPE_FF,                //fast forward

  /* Transport Demux In-band command */
  VIDEO_TRANSPORT_DEMUX_INBAND_CMD_TYPE_PID,
  VIDEO_TRANSPORT_DEMUX_INBAND_CMD_TYPE_PTS_OFFSET,
  VIDEO_TRANSPORT_DEMUX_INBAND_CMD_TYPE_PACKET_SIZE,

  /* Real Video In-band command */
  VIDEO_RV_INBAND_CMD_TYPE_FRAME_INFO,
  VIDEO_RV_INBAND_CMD_TYPE_FORMAT_INFO,
  VIDEO_RV_INBAND_CMD_TYPE_SEGMENT_INFO,

  /*VC1 video In-band command*/
  VIDEO_VC1_INBAND_CMD_TYPE_SEQ_INFO,

  /* general video properties */
  VIDEO_INBAND_CMD_TYPE_VIDEO_USABILITY_INFO,
  VIDEO_INBAND_CMD_TYPE_VIDEO_MPEG4_USABILITY_INFO,

  /*MJPEG resolution In-band Command*/
  VIDEO_MJPEG_INBAND_CMD_TYPE_RESOLUTION,

  /* picture object for graphic */
  VIDEO_GRAPHIC_INBAND_CMD_TYPE_PICTURE_OBJECT,
  VIDEO_GRAPHIC_INBAND_CMD_TYPE_DISPLAY_INFO,



} INBAND_CMD_TYPE ;
/* kjw note. need to sync with common */

typedef struct
{
  INBAND_CMD_TYPE type ;
  unsigned int size ;
} INBAND_CMD_PKT_HEADER ;


typedef struct
{
  INBAND_CMD_PKT_HEADER header ;
  unsigned int wPtr ;
  unsigned int eventID ;
} EOS ;

typedef struct
{
  INBAND_CMD_PKT_HEADER header ;
  int displayEachPic ;      /* 1: each picture sent by upstream must be displayed, 0: follow av-sync to drop/repeat picture */

} VIDEO_GRAPHIC_DISPLAY_INFO ;


typedef struct{
    long long                    videoSystemPTS;
    unsigned int               videoContext;
    int                        videoEndOfSegment;
} DC_PRESENTATION_INFO;


unsigned int    pli_IPCReadULONG(BYTE* src);
unsigned long long  pli_IPCReadULONGLONG(BYTE* src);
void    pli_IPCWriteULONG(BYTE* des, unsigned int data);
void    pli_IPCWriteULONGLONG(BYTE* des, unsigned long long data);



void pli_ipcCopyMemory(void * des, void * src, unsigned long size);
int ICQ_WriteCmd (void *cmd, RINGBUFFER_HEADER* rbHeader, void *rbHeaderBase);

void clkGetPresentation(REFCLOCK* clk, DC_PRESENTATION_INFO *pos);
void clkResetPresentation(REFCLOCK* clk);
#define ulPhyAddrFilter(x) ((x) & ~0xe0000000)



#endif//__DC_RPC_H__


