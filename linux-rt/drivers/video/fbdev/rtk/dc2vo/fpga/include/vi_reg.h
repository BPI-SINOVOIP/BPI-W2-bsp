/**************************************************************
// Spec Version                  : 0.8.0
// Parser Version                : MAR_Parser_1.0
// CModelGen Version             : 1.0 2006.04.18
// Naming Rule                   : Module_Register_Name_reg
// Firmware Header Generate Date : 2008/4/1
***************************************************************/


#ifndef _VI_REG_H_INCLUDED_
#define _VI_REG_H_INCLUDED_
#ifdef  _VI_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     video16_en:1;
unsigned int     video16_type:2;
unsigned int     posen:1;
unsigned int     negen:1;
unsigned int     ycsel:2;
}VI_EDGE1;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     posen:1;
unsigned int     negen:1;
unsigned int     ycsel:2;
}VI_EDGE2;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     ignore1:1;
unsigned int     enable1:1;
unsigned int     ignore:1;
unsigned int     enable:1;
unsigned int     write_data:1;
}VI_PBIT;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     error1:1;
unsigned int     error:1;
}VI_PBIT_ERR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     write_enable1:1;
unsigned int     ext_en:1;
unsigned int     write_enable2:1;
unsigned int     hsync_sel:1;
}VI_EXT_SYNC;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     field:1;
unsigned int     vcnt:11;
unsigned int     hcnt:12;
}VI_FVH1;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     field:1;
unsigned int     vcnt:11;
unsigned int     hcnt:12;
}VI_FVH2;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     write_enable3:1;
unsigned int     reinten:1;
unsigned int     write_enable4:1;
unsigned int     top:1;
unsigned int     write_enable1:1;
unsigned int     vstart:11;
unsigned int     write_enable2:1;
unsigned int     vend:11;
}VI_CWV1;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     write_enable3:1;
unsigned int     reinten:1;
unsigned int     write_enable4:1;
unsigned int     top:1;
unsigned int     write_enable1:1;
unsigned int     vstart:11;
unsigned int     write_enable2:1;
unsigned int     vend:11;
}VI_CWV2;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_enable1:1;
unsigned int     hstart:12;
unsigned int     write_enable2:1;
unsigned int     hend:12;
}VI_CWH1;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_enable1:1;
unsigned int     hstart:12;
unsigned int     write_enable2:1;
unsigned int     hend:12;
}VI_CWH2;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     write_enable1:1;
unsigned int     v2_fend:11;
unsigned int     write_enable2:1;
unsigned int     v1_fend:11;
}VI_CWFEND;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     threshold:23;
}VI_VSTHRESHOLD1;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     threshold:23;
}VI_VSTHRESHOLD2;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     flvcnt1:11;
unsigned int     flvcnt2:11;
}VI_FLVCNT;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     slcnt1:11;
unsigned int     slcnt2:11;
}VI_SLCNT;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     llcnt1:11;
unsigned int     llcnt2:11;
}VI_LLCNT;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     write_enable1:1;
unsigned int     slthd1:11;
unsigned int     write_enable2:1;
unsigned int     slthd2:11;
}VI_SLTHRESHOLD;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     write_enable1:1;
unsigned int     llthd1:11;
unsigned int     write_enable2:1;
unsigned int     llthd2:11;
}VI_LLTHRESHOLD;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     write_enable5:1;
unsigned int     reserved_1:1;
unsigned int     write_enable4:1;
unsigned int     yonly:1;
unsigned int     write_enable1:1;
unsigned int     enable:1;
unsigned int     write_enable2:1;
unsigned int     vstart:11;
unsigned int     write_enable3:1;
unsigned int     vend:11;
}VI_VBIWV1F0;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     write_enable5:1;
unsigned int     reserved_1:1;
unsigned int     write_enable4:1;
unsigned int     yonly:1;
unsigned int     write_enable1:1;
unsigned int     enable:1;
unsigned int     write_enable2:1;
unsigned int     vstart:11;
unsigned int     write_enable3:1;
unsigned int     vend:11;
}VI_VBIWV1F1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     write_enable5:1;
unsigned int     reserved_1:1;
unsigned int     write_enable1:1;
unsigned int     yonly:1;
unsigned int     write_enable2:1;
unsigned int     enable:1;
unsigned int     write_enable3:1;
unsigned int     vstart:11;
unsigned int     write_enable4:1;
unsigned int     vend:11;
}VI_VBIWV2F0;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     write_enable5:1;
unsigned int     reserved_1:1;
unsigned int     write_enable1:1;
unsigned int     yonly:1;
unsigned int     write_enable2:1;
unsigned int     enable:1;
unsigned int     write_enable3:1;
unsigned int     vstart:11;
unsigned int     write_enable4:1;
unsigned int     vend:11;
}VI_VBIWV2F1;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_enable1:1;
unsigned int     hstart:12;
unsigned int     write_enable2:1;
unsigned int     hend:12;
}VI_VBIWH1F0;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_enable1:1;
unsigned int     hstart:12;
unsigned int     write_enable2:1;
unsigned int     hend:12;
}VI_VBIWH1F1;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_enable1:1;
unsigned int     hstart:12;
unsigned int     write_enable2:1;
unsigned int     hend:12;
}VI_VBIWH2F0;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_enable1:1;
unsigned int     hstart:12;
unsigned int     write_enable2:1;
unsigned int     hend:12;
}VI_VBIWH2F1;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_enable1:1;
unsigned int     en:1;
unsigned int     write_enable2:1;
unsigned int     vstart:11;
unsigned int     write_enable3:1;
unsigned int     vend:11;
}VI_VBIWV1F0_SC;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_enable1:1;
unsigned int     en:1;
unsigned int     write_enable2:1;
unsigned int     vstart:11;
unsigned int     write_enable3:1;
unsigned int     vend:11;
}VI_VBIWV1F1_SC;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_enable1:1;
unsigned int     en:1;
unsigned int     write_enable2:1;
unsigned int     vstart:11;
unsigned int     write_enable3:1;
unsigned int     vend:11;
}VI_VBIWV2F0_SC;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_enable1:1;
unsigned int     en:1;
unsigned int     write_enable2:1;
unsigned int     vstart:11;
unsigned int     write_enable3:1;
unsigned int     vend:11;
}VI_VBIWV2F1_SC;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_enable1:1;
unsigned int     hstart:12;
unsigned int     write_enable2:1;
unsigned int     hend:12;
}VI_VBIWH1F0_SC;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_enable1:1;
unsigned int     hstart:12;
unsigned int     write_enable2:1;
unsigned int     hend:12;
}VI_VBIWH1F1_SC;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_enable1:1;
unsigned int     hstart:12;
unsigned int     write_enable2:1;
unsigned int     hend:12;
}VI_VBIWH2F0_SC;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_enable1:1;
unsigned int     hstart:12;
unsigned int     write_enable2:1;
unsigned int     hend:12;
}VI_VBIWH2F1_SC;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     write_enable1:1;
unsigned int     scaling_en1:1;
unsigned int     write_enable2:1;
unsigned int     gain:8;
unsigned int     write_enable3:1;
unsigned int     offset:8;
}VI_VBIF0_SCALING1;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     write_enable1:1;
unsigned int     scaling_en1:1;
unsigned int     write_enable2:1;
unsigned int     gain:8;
unsigned int     write_enable3:1;
unsigned int     offset:8;
}VI_VBIF1_SCALING1;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     write_enable1:1;
unsigned int     scaling_en2:1;
unsigned int     write_enable2:1;
unsigned int     gain:8;
unsigned int     write_enable3:1;
unsigned int     offset:8;
}VI_VBIF0_SCALING2;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     write_enable1:1;
unsigned int     scaling_en2:1;
unsigned int     write_enable2:1;
unsigned int     gain:8;
unsigned int     write_enable3:1;
unsigned int     offset:8;
}VI_VBIF1_SCALING2;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     dc:29;
}VI_YDC1;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     dc:29;
}VI_YDC2;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     yen:1;
unsigned int     cen:1;
unsigned int     write_data:1;
}VI_COCTL1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     yen:1;
unsigned int     cen:1;
unsigned int     write_data:1;
}VI_COCTL2;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     write_enable1:1;
unsigned int     range:8;
unsigned int     write_enable2:1;
unsigned int     conti:1;
unsigned int     write_enable3:1;
unsigned int     clamp:1;
}VI_YCO1;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     write_enable1:1;
unsigned int     range:8;
unsigned int     write_enable2:1;
unsigned int     conti:1;
unsigned int     write_enable3:1;
unsigned int     clamp:1;
}VI_CCO1;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     write_enable1:1;
unsigned int     range:8;
unsigned int     write_enable2:1;
unsigned int     conti:1;
unsigned int     write_enable3:1;
unsigned int     clamp:1;
}VI_YCO2;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     write_enable1:1;
unsigned int     range:8;
unsigned int     write_enable2:1;
unsigned int     conti:1;
unsigned int     write_enable3:1;
unsigned int     clamp:1;
}VI_CCO2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     up_en:1;
unsigned int     tap_mode:2;
unsigned int     yen:1;
unsigned int     yoddtype:1;
unsigned int     cen:1;
unsigned int     coddtype:1;
unsigned int     reserved_1:1;
}VI_VSCCTL1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     up_en:1;
unsigned int     tap_mode:2;
unsigned int     yen:1;
unsigned int     yoddtype:1;
unsigned int     cen:1;
unsigned int     coddtype:1;
unsigned int     reserved_1:1;
}VI_VSCCTL2;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     write_enable1:1;
unsigned int     yonl:11;
unsigned int     write_enable2:1;
unsigned int     ydphs:18;
}VI_VYSC1;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     write_enable1:1;
unsigned int     conl:11;
unsigned int     write_enable2:1;
unsigned int     cdphs:18;
}VI_VCSC1;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     write_enable1:1;
unsigned int     yonl:11;
unsigned int     write_enable2:1;
unsigned int     ydphs:18;
}VI_VYSC2;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     write_enable1:1;
unsigned int     conl:11;
unsigned int     write_enable2:1;
unsigned int     cdphs:18;
}VI_VCSC2;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     init_offset:11;
unsigned int     init_phase:14;
}VI_VYIPOS1;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     init_offset:11;
unsigned int     init_phase:14;
}VI_VYIPOS2;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     init_offset:11;
unsigned int     init_phase:14;
}VI_VCIPOS1;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     init_offset:11;
unsigned int     init_phase:14;
}VI_VCIPOS2;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     ysccoef:14;
}VI_VYSCCOEF1;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     ysccoef:14;
}VI_VYSCCOEF2;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     csccoef:14;
}VI_VCSCCOEF1;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     csccoef:14;
}VI_VCSCCOEF2;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     y1_clamp:1;
unsigned int     c1_clamp:1;
unsigned int     y2_clamp:1;
unsigned int     c2_clamp:1;
unsigned int     y1:1;
unsigned int     c1:1;
unsigned int     y2:1;
unsigned int     c2:1;
unsigned int     write_data:1;
}VI_VOFFSETEN;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     write_enable1:1;
unsigned int     heighy:11;
unsigned int     write_enable2:1;
unsigned int     heighc:11;
}VI_VINFO1;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     write_enable1:1;
unsigned int     heighy:11;
unsigned int     write_enable2:1;
unsigned int     heighc:11;
}VI_VINFO2;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     yen:1;
unsigned int     yoddtype:1;
unsigned int     cen:1;
unsigned int     coddtype:1;
unsigned int     write_data:1;
}VI_SCCTL1;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     yen:1;
unsigned int     yoddtype:1;
unsigned int     cen:1;
unsigned int     coddtype:1;
unsigned int     write_data:1;
}VI_SCCTL2;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     write_enable1:1;
unsigned int     yonp:11;
unsigned int     write_enable2:1;
unsigned int     ydphs:17;
}VI_YSC1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     write_enable1:1;
unsigned int     conp:11;
unsigned int     write_enable2:1;
unsigned int     cdphs:17;
}VI_CSC1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     write_enable1:1;
unsigned int     yonp:11;
unsigned int     write_enable2:1;
unsigned int     ydphs:17;
}VI_YSC2;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     write_enable1:1;
unsigned int     conp:11;
unsigned int     write_enable2:1;
unsigned int     cdphs:17;
}VI_CSC2;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     init_offset:11;
unsigned int     init_phase:14;
}VI_YIPOS1;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     init_offset:11;
unsigned int     init_phase:14;
}VI_YIPOS2;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     init_offset:11;
unsigned int     init_phase:14;
}VI_CIPOS1;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     init_offset:11;
unsigned int     init_phase:14;
}VI_CIPOS2;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     ysccoef:14;
}VI_YSCCOEF1;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     ysccoef:14;
}VI_YSCCOEF2;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     csccoef:14;
}VI_CSCCOEF1;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     csccoef:14;
}VI_CSCCOEF2;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     y1_clamp:1;
unsigned int     c1_clamp:1;
unsigned int     y2_clamp:1;
unsigned int     c2_clamp:1;
unsigned int     y1:1;
unsigned int     c1:1;
unsigned int     y2:1;
unsigned int     c2:1;
unsigned int     write_data:1;
}VI_OFFSETEN;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hpd_enable:1;
unsigned int     hpd_acc:29;
}VI_HPD1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hpd_enable:1;
unsigned int     hpd_acc:29;
}VI_HPD2;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     vpd_enable:1;
unsigned int     vpd_acc:29;
}VI_VPD1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     vpd_enable:1;
unsigned int     vpd_acc:29;
}VI_VPD2;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     write_enable7:1;
unsigned int     cvd1_on:1;
unsigned int     write_enable8:1;
unsigned int     cvd2_on:1;
unsigned int     write_enable5:1;
unsigned int     hdcvden1:1;
unsigned int     write_enable6:1;
unsigned int     hdcvden2:1;
unsigned int     write_enable1:1;
unsigned int     cvden1:1;
unsigned int     write_enable2:1;
unsigned int     cvdtp1:2;
unsigned int     write_enable3:1;
unsigned int     cvden2:1;
unsigned int     write_enable4:1;
unsigned int     cvdtp2:2;
}VI_CVDEN;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     write_enable4:1;
unsigned int     src_sel:1;
unsigned int     write_enable5:1;
unsigned int     luma_2x_en:1;
unsigned int     write_enable1:1;
unsigned int     yden:1;
unsigned int     write_enable2:1;
unsigned int     reserved_1:1;
unsigned int     write_enable3:1;
unsigned int     ydrtio:2;
}VI_YDCTL1;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     write_enable4:1;
unsigned int     src_sel:1;
unsigned int     write_enable5:1;
unsigned int     luma_2x_en:1;
unsigned int     write_enable1:1;
unsigned int     yden:1;
unsigned int     write_enable2:1;
unsigned int     reserved_1:1;
unsigned int     write_enable3:1;
unsigned int     ydrtio:2;
}VI_YDCTL2;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     write_enable1:1;
unsigned int     dmaen1:1;
unsigned int     write_enable2:1;
unsigned int     dmaen2:1;
unsigned int     write_enable4:1;
unsigned int     hddmaen1:1;
unsigned int     write_enable5:1;
unsigned int     hddmaen2:1;
unsigned int     write_enable3:1;
unsigned int     bstlen:3;
}VI_DMACTL;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     write_enable1:1;
unsigned int     thd:6;
}VI_VBI1BUF;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     write_enable1:1;
unsigned int     thd:6;
}VI_VBI2BUF;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     write_enable1:1;
unsigned int     thd:6;
unsigned int     reserved_1:10;
}VI_HDY1BUF;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     write_enable1:1;
unsigned int     thd:6;
unsigned int     reserved_1:20;
}VI_HDY2BUF;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     write_enable1:1;
unsigned int     thd:6;
unsigned int     reserved_1:20;
}VI_HDC1BUF;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     write_enable1:1;
unsigned int     thd:6;
unsigned int     reserved_1:20;
}VI_HDC2BUF;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     write_enable1:1;
unsigned int     thd:6;
unsigned int     reserved_1:10;
}VI_Y1BUF;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     write_enable1:1;
unsigned int     thd:6;
unsigned int     reserved_1:20;
}VI_Y2BUF;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     write_enable1:1;
unsigned int     thd:6;
unsigned int     reserved_1:20;
}VI_C1BUF;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     write_enable1:1;
unsigned int     thd:6;
unsigned int     reserved_1:20;
}VI_C2BUF;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     write_enable1:1;
unsigned int     thd1:6;
unsigned int     write_enable2:1;
unsigned int     thd2:6;
unsigned int     reserved_1:13;
}VI_YDBUF;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     addr:28;
}VI_VBISCADR1F0;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     addr:28;
}VI_VBISCADR1F1;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     addr:28;
}VI_VBISCADR2F0;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     addr:28;
}VI_VBISCADR2F1;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     length:18;
}VI_VBISCLEN1F0;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     length:18;
}VI_VBISCLEN1F1;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     length:18;
}VI_VBISCLEN2F0;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     length:18;
}VI_VBISCLEN2F1;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     addr:28;
}VI_VBIADR1F0;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     addr:28;
}VI_VBIADR1F1;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     length:18;
}VI_VBILEN1F0;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     length:18;
}VI_VBILEN1F1;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     addr:28;
}VI_VBIADR2F0;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     addr:28;
}VI_VBIADR2F1;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     length:18;
}VI_VBILEN2F0;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     length:18;
}VI_VBILEN2F1;

typedef struct 
{
unsigned int     write_enable2:1;
unsigned int     yads:7;
unsigned int     write_enable3:1;
unsigned int     cads:7;
unsigned int     write_enable4:1;
unsigned int     hdyads:7;
unsigned int     write_enable5:1;
unsigned int     hdcads:7;
}VI_DMACTL1;

typedef struct 
{
unsigned int     write_enable2:1;
unsigned int     yads:7;
unsigned int     write_enable3:1;
unsigned int     cads:7;
unsigned int     write_enable4:1;
unsigned int     hdyads:7;
unsigned int     write_enable5:1;
unsigned int     hdcads:7;
}VI_DMACTL2;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     dyads2:7;
unsigned int     dyads:7;
}VI_DYDMACTL;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     v1hd_odd:1;
unsigned int     v1hd_interleave:1;
unsigned int     v2hd_odd:1;
unsigned int     v2hd_interleave:1;
unsigned int     v1_odd:1;
unsigned int     v1_interleave:1;
unsigned int     v2_odd:1;
unsigned int     v2_interleave:1;
unsigned int     dy_odd:1;
unsigned int     dy_interleave:1;
unsigned int     dy2_odd:1;
unsigned int     dy2_interleave:1;
unsigned int     write_data:1;
}VI_IMMODE;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     write_enable1:1;
unsigned int     y1c1:4;
unsigned int     write_enable2:1;
unsigned int     y2c2:4;
unsigned int     write_enable3:1;
unsigned int     vbi1:4;
unsigned int     write_enable4:1;
unsigned int     vbi2:4;
unsigned int     write_enable5:1;
unsigned int     dy:4;
unsigned int     write_enable6:1;
unsigned int     dy2:4;
}VI_DMA_MIN_TIME;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     write_enable1:1;
unsigned int     y1c1:4;
unsigned int     write_enable2:1;
unsigned int     y2c2:4;
}VI_HDDMA_MIN_TIME;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     v2_err:1;
unsigned int     v1_err:1;
}VI_DMAERR;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     feinte1:1;
unsigned int     feinte2:1;
unsigned int     hdolinte1:1;
unsigned int     hdolinte2:1;
unsigned int     dmaerrinte:1;
unsigned int     reserved_1:1;
unsigned int     sfinte1:1;
unsigned int     sfinte2:1;
unsigned int     vsinte1:1;
unsigned int     vsinte2:1;
unsigned int     tointe1:1;
unsigned int     tointe2:1;
unsigned int     olinte1:1;
unsigned int     olinte2:1;
unsigned int     write_data:1;
}VI_INTEN;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     feints1:1;
unsigned int     feints2:1;
unsigned int     hdolints1:1;
unsigned int     hdolints2:1;
unsigned int     dmaerrints:1;
unsigned int     reserved_1:1;
unsigned int     sfints1:1;
unsigned int     sfints2:1;
unsigned int     vsints1:1;
unsigned int     vsints2:1;
unsigned int     toints1:1;
unsigned int     toints2:1;
unsigned int     olints1:1;
unsigned int     olints2:1;
unsigned int     write_data:1;
}VI_INTST;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     write_enable1:1;
unsigned int     y:11;
unsigned int     write_enable2:1;
unsigned int     c:11;
}VI_OLN1;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     write_enable1:1;
unsigned int     y:11;
unsigned int     write_enable2:1;
unsigned int     c:11;
}VI_OLN2;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     write_enable1:1;
unsigned int     y:11;
unsigned int     write_enable2:1;
unsigned int     c:11;
}VI_HDOLN1;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     write_enable1:1;
unsigned int     y:11;
unsigned int     write_enable2:1;
unsigned int     c:11;
}VI_HDOLN2;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     y:11;
unsigned int     c:11;
}VI_OLNCNT1;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     y:11;
unsigned int     c:11;
}VI_OLNCNT2;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     y:11;
unsigned int     c:11;
}VI_HDOLNCNT1;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     y:11;
unsigned int     c:11;
}VI_HDOLNCNT2;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     write_enable3:1;
unsigned int     vsce1:1;
unsigned int     write_enable4:1;
unsigned int     vsce2:1;
unsigned int     write_enable7:1;
unsigned int     hdvsce1:1;
unsigned int     write_enable8:1;
unsigned int     hdvsce2:1;
}VI_GCTL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     write_enable1:1;
unsigned int     enable:1;
}VI_DYNAMIC_P;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     write_enable1:1;
unsigned int     start:8;
unsigned int     write_enable2:1;
unsigned int     end:8;
}VI_Y1OBUFF;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     write_enable1:1;
unsigned int     start:8;
unsigned int     write_enable2:1;
unsigned int     end:8;
}VI_Y2OBUFF;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     write_enable1:1;
unsigned int     start:8;
unsigned int     write_enable2:1;
unsigned int     end:8;
}VI_C1OBUFF;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     write_enable1:1;
unsigned int     start:8;
unsigned int     write_enable2:1;
unsigned int     end:8;
}VI_C2OBUFF;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     write_enable1:1;
unsigned int     start:8;
unsigned int     write_enable2:1;
unsigned int     end:8;
}VI_VBI1OBUFF;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     write_enable1:1;
unsigned int     start:8;
unsigned int     write_enable2:1;
unsigned int     end:8;
}VI_VBI2OBUFF;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     write_enable1:1;
unsigned int     start:8;
unsigned int     write_enable2:1;
unsigned int     end:8;
}VI_DYOBUFF;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     write_enable1:1;
unsigned int     start:8;
unsigned int     write_enable2:1;
unsigned int     end:8;
}VI_DYEXTOBUFF;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     write_enable1:1;
unsigned int     start:8;
unsigned int     write_enable2:1;
unsigned int     end:8;
}VI_HDY1OBUFF;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     write_enable1:1;
unsigned int     start:8;
unsigned int     write_enable2:1;
unsigned int     end:8;
}VI_HDY2OBUFF;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     write_enable1:1;
unsigned int     start:8;
unsigned int     write_enable2:1;
unsigned int     end:8;
}VI_HDC1OBUFF;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     write_enable1:1;
unsigned int     start:8;
unsigned int     write_enable2:1;
unsigned int     end:8;
}VI_HDC2OBUFF;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     write_enable1:1;
unsigned int     start:8;
unsigned int     write_enable2:1;
unsigned int     end:8;
}VI_Y1EXTOBUFF;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     write_enable1:1;
unsigned int     start:8;
unsigned int     write_enable2:1;
unsigned int     end:8;
}VI_Y2EXTOBUFF;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     write_enable1:1;
unsigned int     fa_enable:1;
unsigned int     write_enable2:1;
unsigned int     fa_buffer_sel:1;
unsigned int     write_enable3:1;
unsigned int     fa_addr_2:9;
}VI_FA_ADDR;

typedef struct 
{
unsigned int     data:32;
}VI_FA_DATA_MSB;

typedef struct 
{
unsigned int     data:32;
}VI_FA_DATA_LSB;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     write_enable1:1;
unsigned int     sel0:7;
unsigned int     write_enable2:1;
unsigned int     sel1:7;
unsigned int     write_enable3:1;
unsigned int     enable:1;
}VI_DBG;

typedef struct 
{
unsigned int     dummy:32;
}VI_DUMMY;

#endif

#define VI_EDGE1                                                                     0x18004290
#define VI_EDGE1_reg_addr                                                            "0xB8004290"
#define VI_EDGE1_reg                                                                 0xB8004290
#define VI_EDGE1_inst_adr                                                            "0x00A4"
#define VI_EDGE1_inst                                                                0x00A4
#define VI_EDGE1_video16_en_shift                                                    (6)
#define VI_EDGE1_video16_en_mask                                                     (0x00000040)
#define VI_EDGE1_video16_en(data)                                                    (0x00000040&((data)<<6))
#define VI_EDGE1_video16_en_src(data)                                                ((0x00000040&(data))>>6)
#define VI_EDGE1_get_video16_en(data)                                                ((0x00000040&(data))>>6)
#define VI_EDGE1_video16_type_shift                                                  (4)
#define VI_EDGE1_video16_type_mask                                                   (0x00000030)
#define VI_EDGE1_video16_type(data)                                                  (0x00000030&((data)<<4))
#define VI_EDGE1_video16_type_src(data)                                              ((0x00000030&(data))>>4)
#define VI_EDGE1_get_video16_type(data)                                              ((0x00000030&(data))>>4)
#define VI_EDGE1_posen_shift                                                         (3)
#define VI_EDGE1_posen_mask                                                          (0x00000008)
#define VI_EDGE1_posen(data)                                                         (0x00000008&((data)<<3))
#define VI_EDGE1_posen_src(data)                                                     ((0x00000008&(data))>>3)
#define VI_EDGE1_get_posen(data)                                                     ((0x00000008&(data))>>3)
#define VI_EDGE1_negen_shift                                                         (2)
#define VI_EDGE1_negen_mask                                                          (0x00000004)
#define VI_EDGE1_negen(data)                                                         (0x00000004&((data)<<2))
#define VI_EDGE1_negen_src(data)                                                     ((0x00000004&(data))>>2)
#define VI_EDGE1_get_negen(data)                                                     ((0x00000004&(data))>>2)
#define VI_EDGE1_ycsel_shift                                                         (0)
#define VI_EDGE1_ycsel_mask                                                          (0x00000003)
#define VI_EDGE1_ycsel(data)                                                         (0x00000003&((data)<<0))
#define VI_EDGE1_ycsel_src(data)                                                     ((0x00000003&(data))>>0)
#define VI_EDGE1_get_ycsel(data)                                                     ((0x00000003&(data))>>0)


#define VI_EDGE2                                                                     0x18004294
#define VI_EDGE2_reg_addr                                                            "0xB8004294"
#define VI_EDGE2_reg                                                                 0xB8004294
#define VI_EDGE2_inst_adr                                                            "0x00A5"
#define VI_EDGE2_inst                                                                0x00A5
#define VI_EDGE2_posen_shift                                                         (3)
#define VI_EDGE2_posen_mask                                                          (0x00000008)
#define VI_EDGE2_posen(data)                                                         (0x00000008&((data)<<3))
#define VI_EDGE2_posen_src(data)                                                     ((0x00000008&(data))>>3)
#define VI_EDGE2_get_posen(data)                                                     ((0x00000008&(data))>>3)
#define VI_EDGE2_negen_shift                                                         (2)
#define VI_EDGE2_negen_mask                                                          (0x00000004)
#define VI_EDGE2_negen(data)                                                         (0x00000004&((data)<<2))
#define VI_EDGE2_negen_src(data)                                                     ((0x00000004&(data))>>2)
#define VI_EDGE2_get_negen(data)                                                     ((0x00000004&(data))>>2)
#define VI_EDGE2_ycsel_shift                                                         (0)
#define VI_EDGE2_ycsel_mask                                                          (0x00000003)
#define VI_EDGE2_ycsel(data)                                                         (0x00000003&((data)<<0))
#define VI_EDGE2_ycsel_src(data)                                                     ((0x00000003&(data))>>0)
#define VI_EDGE2_get_ycsel(data)                                                     ((0x00000003&(data))>>0)


#define VI_PBIT                                                                      0x18004004
#define VI_PBIT_reg_addr                                                             "0xB8004004"
#define VI_PBIT_reg                                                                  0xB8004004
#define VI_PBIT_inst_adr                                                             "0x0001"
#define VI_PBIT_inst                                                                 0x0001
#define VI_PBIT_ignore1_shift                                                        (4)
#define VI_PBIT_ignore1_mask                                                         (0x00000010)
#define VI_PBIT_ignore1(data)                                                        (0x00000010&((data)<<4))
#define VI_PBIT_ignore1_src(data)                                                    ((0x00000010&(data))>>4)
#define VI_PBIT_get_ignore1(data)                                                    ((0x00000010&(data))>>4)
#define VI_PBIT_enable1_shift                                                        (3)
#define VI_PBIT_enable1_mask                                                         (0x00000008)
#define VI_PBIT_enable1(data)                                                        (0x00000008&((data)<<3))
#define VI_PBIT_enable1_src(data)                                                    ((0x00000008&(data))>>3)
#define VI_PBIT_get_enable1(data)                                                    ((0x00000008&(data))>>3)
#define VI_PBIT_ignore_shift                                                         (2)
#define VI_PBIT_ignore_mask                                                          (0x00000004)
#define VI_PBIT_ignore(data)                                                         (0x00000004&((data)<<2))
#define VI_PBIT_ignore_src(data)                                                     ((0x00000004&(data))>>2)
#define VI_PBIT_get_ignore(data)                                                     ((0x00000004&(data))>>2)
#define VI_PBIT_enable_shift                                                         (1)
#define VI_PBIT_enable_mask                                                          (0x00000002)
#define VI_PBIT_enable(data)                                                         (0x00000002&((data)<<1))
#define VI_PBIT_enable_src(data)                                                     ((0x00000002&(data))>>1)
#define VI_PBIT_get_enable(data)                                                     ((0x00000002&(data))>>1)
#define VI_PBIT_write_data_shift                                                     (0)
#define VI_PBIT_write_data_mask                                                      (0x00000001)
#define VI_PBIT_write_data(data)                                                     (0x00000001&((data)<<0))
#define VI_PBIT_write_data_src(data)                                                 ((0x00000001&(data))>>0)
#define VI_PBIT_get_write_data(data)                                                 ((0x00000001&(data))>>0)


#define VI_PBIT_ERR                                                                  0x18004008
#define VI_PBIT_ERR_reg_addr                                                         "0xB8004008"
#define VI_PBIT_ERR_reg                                                              0xB8004008
#define VI_PBIT_ERR_inst_adr                                                         "0x0002"
#define VI_PBIT_ERR_inst                                                             0x0002
#define VI_PBIT_ERR_error1_shift                                                     (1)
#define VI_PBIT_ERR_error1_mask                                                      (0x00000002)
#define VI_PBIT_ERR_error1(data)                                                     (0x00000002&((data)<<1))
#define VI_PBIT_ERR_error1_src(data)                                                 ((0x00000002&(data))>>1)
#define VI_PBIT_ERR_get_error1(data)                                                 ((0x00000002&(data))>>1)
#define VI_PBIT_ERR_error_shift                                                      (0)
#define VI_PBIT_ERR_error_mask                                                       (0x00000001)
#define VI_PBIT_ERR_error(data)                                                      (0x00000001&((data)<<0))
#define VI_PBIT_ERR_error_src(data)                                                  ((0x00000001&(data))>>0)
#define VI_PBIT_ERR_get_error(data)                                                  ((0x00000001&(data))>>0)


#define VI_EXT_SYNC                                                                  0x180044b0
#define VI_EXT_SYNC_reg_addr                                                         "0xB80044B0"
#define VI_EXT_SYNC_reg                                                              0xB80044B0
#define VI_EXT_SYNC_inst_adr                                                         "0x002C"
#define VI_EXT_SYNC_inst                                                             0x002C
#define VI_EXT_SYNC_write_enable1_shift                                              (3)
#define VI_EXT_SYNC_write_enable1_mask                                               (0x00000008)
#define VI_EXT_SYNC_write_enable1(data)                                              (0x00000008&((data)<<3))
#define VI_EXT_SYNC_write_enable1_src(data)                                          ((0x00000008&(data))>>3)
#define VI_EXT_SYNC_get_write_enable1(data)                                          ((0x00000008&(data))>>3)
#define VI_EXT_SYNC_ext_en_shift                                                     (2)
#define VI_EXT_SYNC_ext_en_mask                                                      (0x00000004)
#define VI_EXT_SYNC_ext_en(data)                                                     (0x00000004&((data)<<2))
#define VI_EXT_SYNC_ext_en_src(data)                                                 ((0x00000004&(data))>>2)
#define VI_EXT_SYNC_get_ext_en(data)                                                 ((0x00000004&(data))>>2)
#define VI_EXT_SYNC_write_enable2_shift                                              (1)
#define VI_EXT_SYNC_write_enable2_mask                                               (0x00000002)
#define VI_EXT_SYNC_write_enable2(data)                                              (0x00000002&((data)<<1))
#define VI_EXT_SYNC_write_enable2_src(data)                                          ((0x00000002&(data))>>1)
#define VI_EXT_SYNC_get_write_enable2(data)                                          ((0x00000002&(data))>>1)
#define VI_EXT_SYNC_hsync_sel_shift                                                  (0)
#define VI_EXT_SYNC_hsync_sel_mask                                                   (0x00000001)
#define VI_EXT_SYNC_hsync_sel(data)                                                  (0x00000001&((data)<<0))
#define VI_EXT_SYNC_hsync_sel_src(data)                                              ((0x00000001&(data))>>0)
#define VI_EXT_SYNC_get_hsync_sel(data)                                              ((0x00000001&(data))>>0)


#define VI_FVH1                                                                      0x1800400c
#define VI_FVH1_reg_addr                                                             "0xB800400C"
#define VI_FVH1_reg                                                                  0xB800400C
#define VI_FVH1_inst_adr                                                             "0x0003"
#define VI_FVH1_inst                                                                 0x0003
#define VI_FVH1_field_shift                                                          (23)
#define VI_FVH1_field_mask                                                           (0x00800000)
#define VI_FVH1_field(data)                                                          (0x00800000&((data)<<23))
#define VI_FVH1_field_src(data)                                                      ((0x00800000&(data))>>23)
#define VI_FVH1_get_field(data)                                                      ((0x00800000&(data))>>23)
#define VI_FVH1_vcnt_shift                                                           (12)
#define VI_FVH1_vcnt_mask                                                            (0x007FF000)
#define VI_FVH1_vcnt(data)                                                           (0x007FF000&((data)<<12))
#define VI_FVH1_vcnt_src(data)                                                       ((0x007FF000&(data))>>12)
#define VI_FVH1_get_vcnt(data)                                                       ((0x007FF000&(data))>>12)
#define VI_FVH1_hcnt_shift                                                           (0)
#define VI_FVH1_hcnt_mask                                                            (0x00000FFF)
#define VI_FVH1_hcnt(data)                                                           (0x00000FFF&((data)<<0))
#define VI_FVH1_hcnt_src(data)                                                       ((0x00000FFF&(data))>>0)
#define VI_FVH1_get_hcnt(data)                                                       ((0x00000FFF&(data))>>0)


#define VI_FVH2                                                                      0x18004010
#define VI_FVH2_reg_addr                                                             "0xB8004010"
#define VI_FVH2_reg                                                                  0xB8004010
#define VI_FVH2_inst_adr                                                             "0x0004"
#define VI_FVH2_inst                                                                 0x0004
#define VI_FVH2_field_shift                                                          (23)
#define VI_FVH2_field_mask                                                           (0x00800000)
#define VI_FVH2_field(data)                                                          (0x00800000&((data)<<23))
#define VI_FVH2_field_src(data)                                                      ((0x00800000&(data))>>23)
#define VI_FVH2_get_field(data)                                                      ((0x00800000&(data))>>23)
#define VI_FVH2_vcnt_shift                                                           (12)
#define VI_FVH2_vcnt_mask                                                            (0x007FF000)
#define VI_FVH2_vcnt(data)                                                           (0x007FF000&((data)<<12))
#define VI_FVH2_vcnt_src(data)                                                       ((0x007FF000&(data))>>12)
#define VI_FVH2_get_vcnt(data)                                                       ((0x007FF000&(data))>>12)
#define VI_FVH2_hcnt_shift                                                           (0)
#define VI_FVH2_hcnt_mask                                                            (0x00000FFF)
#define VI_FVH2_hcnt(data)                                                           (0x00000FFF&((data)<<0))
#define VI_FVH2_hcnt_src(data)                                                       ((0x00000FFF&(data))>>0)
#define VI_FVH2_get_hcnt(data)                                                       ((0x00000FFF&(data))>>0)


#define VI_CWV1                                                                      0x18004014
#define VI_CWV1_reg_addr                                                             "0xB8004014"
#define VI_CWV1_reg                                                                  0xB8004014
#define VI_CWV1_inst_adr                                                             "0x0005"
#define VI_CWV1_inst                                                                 0x0005
#define VI_CWV1_write_enable3_shift                                                  (27)
#define VI_CWV1_write_enable3_mask                                                   (0x08000000)
#define VI_CWV1_write_enable3(data)                                                  (0x08000000&((data)<<27))
#define VI_CWV1_write_enable3_src(data)                                              ((0x08000000&(data))>>27)
#define VI_CWV1_get_write_enable3(data)                                              ((0x08000000&(data))>>27)
#define VI_CWV1_reinten_shift                                                        (26)
#define VI_CWV1_reinten_mask                                                         (0x04000000)
#define VI_CWV1_reinten(data)                                                        (0x04000000&((data)<<26))
#define VI_CWV1_reinten_src(data)                                                    ((0x04000000&(data))>>26)
#define VI_CWV1_get_reinten(data)                                                    ((0x04000000&(data))>>26)
#define VI_CWV1_write_enable4_shift                                                  (25)
#define VI_CWV1_write_enable4_mask                                                   (0x02000000)
#define VI_CWV1_write_enable4(data)                                                  (0x02000000&((data)<<25))
#define VI_CWV1_write_enable4_src(data)                                              ((0x02000000&(data))>>25)
#define VI_CWV1_get_write_enable4(data)                                              ((0x02000000&(data))>>25)
#define VI_CWV1_top_shift                                                            (24)
#define VI_CWV1_top_mask                                                             (0x01000000)
#define VI_CWV1_top(data)                                                            (0x01000000&((data)<<24))
#define VI_CWV1_top_src(data)                                                        ((0x01000000&(data))>>24)
#define VI_CWV1_get_top(data)                                                        ((0x01000000&(data))>>24)
#define VI_CWV1_write_enable1_shift                                                  (23)
#define VI_CWV1_write_enable1_mask                                                   (0x00800000)
#define VI_CWV1_write_enable1(data)                                                  (0x00800000&((data)<<23))
#define VI_CWV1_write_enable1_src(data)                                              ((0x00800000&(data))>>23)
#define VI_CWV1_get_write_enable1(data)                                              ((0x00800000&(data))>>23)
#define VI_CWV1_vstart_shift                                                         (12)
#define VI_CWV1_vstart_mask                                                          (0x007FF000)
#define VI_CWV1_vstart(data)                                                         (0x007FF000&((data)<<12))
#define VI_CWV1_vstart_src(data)                                                     ((0x007FF000&(data))>>12)
#define VI_CWV1_get_vstart(data)                                                     ((0x007FF000&(data))>>12)
#define VI_CWV1_write_enable2_shift                                                  (11)
#define VI_CWV1_write_enable2_mask                                                   (0x00000800)
#define VI_CWV1_write_enable2(data)                                                  (0x00000800&((data)<<11))
#define VI_CWV1_write_enable2_src(data)                                              ((0x00000800&(data))>>11)
#define VI_CWV1_get_write_enable2(data)                                              ((0x00000800&(data))>>11)
#define VI_CWV1_vend_shift                                                           (0)
#define VI_CWV1_vend_mask                                                            (0x000007FF)
#define VI_CWV1_vend(data)                                                           (0x000007FF&((data)<<0))
#define VI_CWV1_vend_src(data)                                                       ((0x000007FF&(data))>>0)
#define VI_CWV1_get_vend(data)                                                       ((0x000007FF&(data))>>0)


#define VI_CWV2                                                                      0x18004018
#define VI_CWV2_reg_addr                                                             "0xB8004018"
#define VI_CWV2_reg                                                                  0xB8004018
#define VI_CWV2_inst_adr                                                             "0x0006"
#define VI_CWV2_inst                                                                 0x0006
#define VI_CWV2_write_enable3_shift                                                  (27)
#define VI_CWV2_write_enable3_mask                                                   (0x08000000)
#define VI_CWV2_write_enable3(data)                                                  (0x08000000&((data)<<27))
#define VI_CWV2_write_enable3_src(data)                                              ((0x08000000&(data))>>27)
#define VI_CWV2_get_write_enable3(data)                                              ((0x08000000&(data))>>27)
#define VI_CWV2_reinten_shift                                                        (26)
#define VI_CWV2_reinten_mask                                                         (0x04000000)
#define VI_CWV2_reinten(data)                                                        (0x04000000&((data)<<26))
#define VI_CWV2_reinten_src(data)                                                    ((0x04000000&(data))>>26)
#define VI_CWV2_get_reinten(data)                                                    ((0x04000000&(data))>>26)
#define VI_CWV2_write_enable4_shift                                                  (25)
#define VI_CWV2_write_enable4_mask                                                   (0x02000000)
#define VI_CWV2_write_enable4(data)                                                  (0x02000000&((data)<<25))
#define VI_CWV2_write_enable4_src(data)                                              ((0x02000000&(data))>>25)
#define VI_CWV2_get_write_enable4(data)                                              ((0x02000000&(data))>>25)
#define VI_CWV2_top_shift                                                            (24)
#define VI_CWV2_top_mask                                                             (0x01000000)
#define VI_CWV2_top(data)                                                            (0x01000000&((data)<<24))
#define VI_CWV2_top_src(data)                                                        ((0x01000000&(data))>>24)
#define VI_CWV2_get_top(data)                                                        ((0x01000000&(data))>>24)
#define VI_CWV2_write_enable1_shift                                                  (23)
#define VI_CWV2_write_enable1_mask                                                   (0x00800000)
#define VI_CWV2_write_enable1(data)                                                  (0x00800000&((data)<<23))
#define VI_CWV2_write_enable1_src(data)                                              ((0x00800000&(data))>>23)
#define VI_CWV2_get_write_enable1(data)                                              ((0x00800000&(data))>>23)
#define VI_CWV2_vstart_shift                                                         (12)
#define VI_CWV2_vstart_mask                                                          (0x007FF000)
#define VI_CWV2_vstart(data)                                                         (0x007FF000&((data)<<12))
#define VI_CWV2_vstart_src(data)                                                     ((0x007FF000&(data))>>12)
#define VI_CWV2_get_vstart(data)                                                     ((0x007FF000&(data))>>12)
#define VI_CWV2_write_enable2_shift                                                  (11)
#define VI_CWV2_write_enable2_mask                                                   (0x00000800)
#define VI_CWV2_write_enable2(data)                                                  (0x00000800&((data)<<11))
#define VI_CWV2_write_enable2_src(data)                                              ((0x00000800&(data))>>11)
#define VI_CWV2_get_write_enable2(data)                                              ((0x00000800&(data))>>11)
#define VI_CWV2_vend_shift                                                           (0)
#define VI_CWV2_vend_mask                                                            (0x000007FF)
#define VI_CWV2_vend(data)                                                           (0x000007FF&((data)<<0))
#define VI_CWV2_vend_src(data)                                                       ((0x000007FF&(data))>>0)
#define VI_CWV2_get_vend(data)                                                       ((0x000007FF&(data))>>0)


#define VI_CWH1                                                                      0x1800401c
#define VI_CWH1_reg_addr                                                             "0xB800401C"
#define VI_CWH1_reg                                                                  0xB800401C
#define VI_CWH1_inst_adr                                                             "0x0007"
#define VI_CWH1_inst                                                                 0x0007
#define VI_CWH1_write_enable1_shift                                                  (25)
#define VI_CWH1_write_enable1_mask                                                   (0x02000000)
#define VI_CWH1_write_enable1(data)                                                  (0x02000000&((data)<<25))
#define VI_CWH1_write_enable1_src(data)                                              ((0x02000000&(data))>>25)
#define VI_CWH1_get_write_enable1(data)                                              ((0x02000000&(data))>>25)
#define VI_CWH1_hstart_shift                                                         (13)
#define VI_CWH1_hstart_mask                                                          (0x01FFE000)
#define VI_CWH1_hstart(data)                                                         (0x01FFE000&((data)<<13))
#define VI_CWH1_hstart_src(data)                                                     ((0x01FFE000&(data))>>13)
#define VI_CWH1_get_hstart(data)                                                     ((0x01FFE000&(data))>>13)
#define VI_CWH1_write_enable2_shift                                                  (12)
#define VI_CWH1_write_enable2_mask                                                   (0x00001000)
#define VI_CWH1_write_enable2(data)                                                  (0x00001000&((data)<<12))
#define VI_CWH1_write_enable2_src(data)                                              ((0x00001000&(data))>>12)
#define VI_CWH1_get_write_enable2(data)                                              ((0x00001000&(data))>>12)
#define VI_CWH1_hend_shift                                                           (0)
#define VI_CWH1_hend_mask                                                            (0x00000FFF)
#define VI_CWH1_hend(data)                                                           (0x00000FFF&((data)<<0))
#define VI_CWH1_hend_src(data)                                                       ((0x00000FFF&(data))>>0)
#define VI_CWH1_get_hend(data)                                                       ((0x00000FFF&(data))>>0)


#define VI_CWH2                                                                      0x18004020
#define VI_CWH2_reg_addr                                                             "0xB8004020"
#define VI_CWH2_reg                                                                  0xB8004020
#define VI_CWH2_inst_adr                                                             "0x0008"
#define VI_CWH2_inst                                                                 0x0008
#define VI_CWH2_write_enable1_shift                                                  (25)
#define VI_CWH2_write_enable1_mask                                                   (0x02000000)
#define VI_CWH2_write_enable1(data)                                                  (0x02000000&((data)<<25))
#define VI_CWH2_write_enable1_src(data)                                              ((0x02000000&(data))>>25)
#define VI_CWH2_get_write_enable1(data)                                              ((0x02000000&(data))>>25)
#define VI_CWH2_hstart_shift                                                         (13)
#define VI_CWH2_hstart_mask                                                          (0x01FFE000)
#define VI_CWH2_hstart(data)                                                         (0x01FFE000&((data)<<13))
#define VI_CWH2_hstart_src(data)                                                     ((0x01FFE000&(data))>>13)
#define VI_CWH2_get_hstart(data)                                                     ((0x01FFE000&(data))>>13)
#define VI_CWH2_write_enable2_shift                                                  (12)
#define VI_CWH2_write_enable2_mask                                                   (0x00001000)
#define VI_CWH2_write_enable2(data)                                                  (0x00001000&((data)<<12))
#define VI_CWH2_write_enable2_src(data)                                              ((0x00001000&(data))>>12)
#define VI_CWH2_get_write_enable2(data)                                              ((0x00001000&(data))>>12)
#define VI_CWH2_hend_shift                                                           (0)
#define VI_CWH2_hend_mask                                                            (0x00000FFF)
#define VI_CWH2_hend(data)                                                           (0x00000FFF&((data)<<0))
#define VI_CWH2_hend_src(data)                                                       ((0x00000FFF&(data))>>0)
#define VI_CWH2_get_hend(data)                                                       ((0x00000FFF&(data))>>0)


#define VI_CWFEND                                                                    0x18004580
#define VI_CWFEND_reg_addr                                                           "0xB8004580"
#define VI_CWFEND_reg                                                                0xB8004580
#define VI_CWFEND_inst_adr                                                           "0x0060"
#define VI_CWFEND_inst                                                               0x0060
#define VI_CWFEND_write_enable1_shift                                                (23)
#define VI_CWFEND_write_enable1_mask                                                 (0x00800000)
#define VI_CWFEND_write_enable1(data)                                                (0x00800000&((data)<<23))
#define VI_CWFEND_write_enable1_src(data)                                            ((0x00800000&(data))>>23)
#define VI_CWFEND_get_write_enable1(data)                                            ((0x00800000&(data))>>23)
#define VI_CWFEND_v2_fend_shift                                                      (12)
#define VI_CWFEND_v2_fend_mask                                                       (0x007FF000)
#define VI_CWFEND_v2_fend(data)                                                      (0x007FF000&((data)<<12))
#define VI_CWFEND_v2_fend_src(data)                                                  ((0x007FF000&(data))>>12)
#define VI_CWFEND_get_v2_fend(data)                                                  ((0x007FF000&(data))>>12)
#define VI_CWFEND_write_enable2_shift                                                (11)
#define VI_CWFEND_write_enable2_mask                                                 (0x00000800)
#define VI_CWFEND_write_enable2(data)                                                (0x00000800&((data)<<11))
#define VI_CWFEND_write_enable2_src(data)                                            ((0x00000800&(data))>>11)
#define VI_CWFEND_get_write_enable2(data)                                            ((0x00000800&(data))>>11)
#define VI_CWFEND_v1_fend_shift                                                      (0)
#define VI_CWFEND_v1_fend_mask                                                       (0x000007FF)
#define VI_CWFEND_v1_fend(data)                                                      (0x000007FF&((data)<<0))
#define VI_CWFEND_v1_fend_src(data)                                                  ((0x000007FF&(data))>>0)
#define VI_CWFEND_get_v1_fend(data)                                                  ((0x000007FF&(data))>>0)


#define VI_VSTHRESHOLD1                                                              0x18004024
#define VI_VSTHRESHOLD1_reg_addr                                                     "0xB8004024"
#define VI_VSTHRESHOLD1_reg                                                          0xB8004024
#define VI_VSTHRESHOLD1_inst_adr                                                     "0x0009"
#define VI_VSTHRESHOLD1_inst                                                         0x0009
#define VI_VSTHRESHOLD1_threshold_shift                                              (0)
#define VI_VSTHRESHOLD1_threshold_mask                                               (0x007FFFFF)
#define VI_VSTHRESHOLD1_threshold(data)                                              (0x007FFFFF&((data)<<0))
#define VI_VSTHRESHOLD1_threshold_src(data)                                          ((0x007FFFFF&(data))>>0)
#define VI_VSTHRESHOLD1_get_threshold(data)                                          ((0x007FFFFF&(data))>>0)


#define VI_VSTHRESHOLD2                                                              0x18004028
#define VI_VSTHRESHOLD2_reg_addr                                                     "0xB8004028"
#define VI_VSTHRESHOLD2_reg                                                          0xB8004028
#define VI_VSTHRESHOLD2_inst_adr                                                     "0x000A"
#define VI_VSTHRESHOLD2_inst                                                         0x000A
#define VI_VSTHRESHOLD2_threshold_shift                                              (0)
#define VI_VSTHRESHOLD2_threshold_mask                                               (0x007FFFFF)
#define VI_VSTHRESHOLD2_threshold(data)                                              (0x007FFFFF&((data)<<0))
#define VI_VSTHRESHOLD2_threshold_src(data)                                          ((0x007FFFFF&(data))>>0)
#define VI_VSTHRESHOLD2_get_threshold(data)                                          ((0x007FFFFF&(data))>>0)


#define VI_FLVCNT                                                                    0x1800402c
#define VI_FLVCNT_reg_addr                                                           "0xB800402C"
#define VI_FLVCNT_reg                                                                0xB800402C
#define VI_FLVCNT_inst_adr                                                           "0x000B"
#define VI_FLVCNT_inst                                                               0x000B
#define VI_FLVCNT_flvcnt1_shift                                                      (11)
#define VI_FLVCNT_flvcnt1_mask                                                       (0x003FF800)
#define VI_FLVCNT_flvcnt1(data)                                                      (0x003FF800&((data)<<11))
#define VI_FLVCNT_flvcnt1_src(data)                                                  ((0x003FF800&(data))>>11)
#define VI_FLVCNT_get_flvcnt1(data)                                                  ((0x003FF800&(data))>>11)
#define VI_FLVCNT_flvcnt2_shift                                                      (0)
#define VI_FLVCNT_flvcnt2_mask                                                       (0x000007FF)
#define VI_FLVCNT_flvcnt2(data)                                                      (0x000007FF&((data)<<0))
#define VI_FLVCNT_flvcnt2_src(data)                                                  ((0x000007FF&(data))>>0)
#define VI_FLVCNT_get_flvcnt2(data)                                                  ((0x000007FF&(data))>>0)


#define VI_SLCNT                                                                     0x18004030
#define VI_SLCNT_reg_addr                                                            "0xB8004030"
#define VI_SLCNT_reg                                                                 0xB8004030
#define VI_SLCNT_inst_adr                                                            "0x000C"
#define VI_SLCNT_inst                                                                0x000C
#define VI_SLCNT_slcnt1_shift                                                        (11)
#define VI_SLCNT_slcnt1_mask                                                         (0x003FF800)
#define VI_SLCNT_slcnt1(data)                                                        (0x003FF800&((data)<<11))
#define VI_SLCNT_slcnt1_src(data)                                                    ((0x003FF800&(data))>>11)
#define VI_SLCNT_get_slcnt1(data)                                                    ((0x003FF800&(data))>>11)
#define VI_SLCNT_slcnt2_shift                                                        (0)
#define VI_SLCNT_slcnt2_mask                                                         (0x000007FF)
#define VI_SLCNT_slcnt2(data)                                                        (0x000007FF&((data)<<0))
#define VI_SLCNT_slcnt2_src(data)                                                    ((0x000007FF&(data))>>0)
#define VI_SLCNT_get_slcnt2(data)                                                    ((0x000007FF&(data))>>0)


#define VI_LLCNT                                                                     0x18004034
#define VI_LLCNT_reg_addr                                                            "0xB8004034"
#define VI_LLCNT_reg                                                                 0xB8004034
#define VI_LLCNT_inst_adr                                                            "0x000D"
#define VI_LLCNT_inst                                                                0x000D
#define VI_LLCNT_llcnt1_shift                                                        (11)
#define VI_LLCNT_llcnt1_mask                                                         (0x003FF800)
#define VI_LLCNT_llcnt1(data)                                                        (0x003FF800&((data)<<11))
#define VI_LLCNT_llcnt1_src(data)                                                    ((0x003FF800&(data))>>11)
#define VI_LLCNT_get_llcnt1(data)                                                    ((0x003FF800&(data))>>11)
#define VI_LLCNT_llcnt2_shift                                                        (0)
#define VI_LLCNT_llcnt2_mask                                                         (0x000007FF)
#define VI_LLCNT_llcnt2(data)                                                        (0x000007FF&((data)<<0))
#define VI_LLCNT_llcnt2_src(data)                                                    ((0x000007FF&(data))>>0)
#define VI_LLCNT_get_llcnt2(data)                                                    ((0x000007FF&(data))>>0)


#define VI_SLTHRESHOLD                                                               0x18004038
#define VI_SLTHRESHOLD_reg_addr                                                      "0xB8004038"
#define VI_SLTHRESHOLD_reg                                                           0xB8004038
#define VI_SLTHRESHOLD_inst_adr                                                      "0x000E"
#define VI_SLTHRESHOLD_inst                                                          0x000E
#define VI_SLTHRESHOLD_write_enable1_shift                                           (23)
#define VI_SLTHRESHOLD_write_enable1_mask                                            (0x00800000)
#define VI_SLTHRESHOLD_write_enable1(data)                                           (0x00800000&((data)<<23))
#define VI_SLTHRESHOLD_write_enable1_src(data)                                       ((0x00800000&(data))>>23)
#define VI_SLTHRESHOLD_get_write_enable1(data)                                       ((0x00800000&(data))>>23)
#define VI_SLTHRESHOLD_slthd1_shift                                                  (12)
#define VI_SLTHRESHOLD_slthd1_mask                                                   (0x007FF000)
#define VI_SLTHRESHOLD_slthd1(data)                                                  (0x007FF000&((data)<<12))
#define VI_SLTHRESHOLD_slthd1_src(data)                                              ((0x007FF000&(data))>>12)
#define VI_SLTHRESHOLD_get_slthd1(data)                                              ((0x007FF000&(data))>>12)
#define VI_SLTHRESHOLD_write_enable2_shift                                           (11)
#define VI_SLTHRESHOLD_write_enable2_mask                                            (0x00000800)
#define VI_SLTHRESHOLD_write_enable2(data)                                           (0x00000800&((data)<<11))
#define VI_SLTHRESHOLD_write_enable2_src(data)                                       ((0x00000800&(data))>>11)
#define VI_SLTHRESHOLD_get_write_enable2(data)                                       ((0x00000800&(data))>>11)
#define VI_SLTHRESHOLD_slthd2_shift                                                  (0)
#define VI_SLTHRESHOLD_slthd2_mask                                                   (0x000007FF)
#define VI_SLTHRESHOLD_slthd2(data)                                                  (0x000007FF&((data)<<0))
#define VI_SLTHRESHOLD_slthd2_src(data)                                              ((0x000007FF&(data))>>0)
#define VI_SLTHRESHOLD_get_slthd2(data)                                              ((0x000007FF&(data))>>0)


#define VI_LLTHRESHOLD                                                               0x1800403c
#define VI_LLTHRESHOLD_reg_addr                                                      "0xB800403C"
#define VI_LLTHRESHOLD_reg                                                           0xB800403C
#define VI_LLTHRESHOLD_inst_adr                                                      "0x000F"
#define VI_LLTHRESHOLD_inst                                                          0x000F
#define VI_LLTHRESHOLD_write_enable1_shift                                           (23)
#define VI_LLTHRESHOLD_write_enable1_mask                                            (0x00800000)
#define VI_LLTHRESHOLD_write_enable1(data)                                           (0x00800000&((data)<<23))
#define VI_LLTHRESHOLD_write_enable1_src(data)                                       ((0x00800000&(data))>>23)
#define VI_LLTHRESHOLD_get_write_enable1(data)                                       ((0x00800000&(data))>>23)
#define VI_LLTHRESHOLD_llthd1_shift                                                  (12)
#define VI_LLTHRESHOLD_llthd1_mask                                                   (0x007FF000)
#define VI_LLTHRESHOLD_llthd1(data)                                                  (0x007FF000&((data)<<12))
#define VI_LLTHRESHOLD_llthd1_src(data)                                              ((0x007FF000&(data))>>12)
#define VI_LLTHRESHOLD_get_llthd1(data)                                              ((0x007FF000&(data))>>12)
#define VI_LLTHRESHOLD_write_enable2_shift                                           (11)
#define VI_LLTHRESHOLD_write_enable2_mask                                            (0x00000800)
#define VI_LLTHRESHOLD_write_enable2(data)                                           (0x00000800&((data)<<11))
#define VI_LLTHRESHOLD_write_enable2_src(data)                                       ((0x00000800&(data))>>11)
#define VI_LLTHRESHOLD_get_write_enable2(data)                                       ((0x00000800&(data))>>11)
#define VI_LLTHRESHOLD_llthd2_shift                                                  (0)
#define VI_LLTHRESHOLD_llthd2_mask                                                   (0x000007FF)
#define VI_LLTHRESHOLD_llthd2(data)                                                  (0x000007FF&((data)<<0))
#define VI_LLTHRESHOLD_llthd2_src(data)                                              ((0x000007FF&(data))>>0)
#define VI_LLTHRESHOLD_get_llthd2(data)                                              ((0x000007FF&(data))>>0)


#define VI_VBIWV1F0                                                                  0x18004040
#define VI_VBIWV1F0_reg_addr                                                         "0xB8004040"
#define VI_VBIWV1F0_reg                                                              0xB8004040
#define VI_VBIWV1F0_inst_adr                                                         "0x0010"
#define VI_VBIWV1F0_inst                                                             0x0010
#define VI_VBIWV1F0_write_enable5_shift                                              (29)
#define VI_VBIWV1F0_write_enable5_mask                                               (0x20000000)
#define VI_VBIWV1F0_write_enable5(data)                                              (0x20000000&((data)<<29))
#define VI_VBIWV1F0_write_enable5_src(data)                                          ((0x20000000&(data))>>29)
#define VI_VBIWV1F0_get_write_enable5(data)                                          ((0x20000000&(data))>>29)
#define VI_VBIWV1F0_write_enable4_shift                                              (27)
#define VI_VBIWV1F0_write_enable4_mask                                               (0x08000000)
#define VI_VBIWV1F0_write_enable4(data)                                              (0x08000000&((data)<<27))
#define VI_VBIWV1F0_write_enable4_src(data)                                          ((0x08000000&(data))>>27)
#define VI_VBIWV1F0_get_write_enable4(data)                                          ((0x08000000&(data))>>27)
#define VI_VBIWV1F0_yonly_shift                                                      (26)
#define VI_VBIWV1F0_yonly_mask                                                       (0x04000000)
#define VI_VBIWV1F0_yonly(data)                                                      (0x04000000&((data)<<26))
#define VI_VBIWV1F0_yonly_src(data)                                                  ((0x04000000&(data))>>26)
#define VI_VBIWV1F0_get_yonly(data)                                                  ((0x04000000&(data))>>26)
#define VI_VBIWV1F0_write_enable1_shift                                              (25)
#define VI_VBIWV1F0_write_enable1_mask                                               (0x02000000)
#define VI_VBIWV1F0_write_enable1(data)                                              (0x02000000&((data)<<25))
#define VI_VBIWV1F0_write_enable1_src(data)                                          ((0x02000000&(data))>>25)
#define VI_VBIWV1F0_get_write_enable1(data)                                          ((0x02000000&(data))>>25)
#define VI_VBIWV1F0_enable_shift                                                     (24)
#define VI_VBIWV1F0_enable_mask                                                      (0x01000000)
#define VI_VBIWV1F0_enable(data)                                                     (0x01000000&((data)<<24))
#define VI_VBIWV1F0_enable_src(data)                                                 ((0x01000000&(data))>>24)
#define VI_VBIWV1F0_get_enable(data)                                                 ((0x01000000&(data))>>24)
#define VI_VBIWV1F0_write_enable2_shift                                              (23)
#define VI_VBIWV1F0_write_enable2_mask                                               (0x00800000)
#define VI_VBIWV1F0_write_enable2(data)                                              (0x00800000&((data)<<23))
#define VI_VBIWV1F0_write_enable2_src(data)                                          ((0x00800000&(data))>>23)
#define VI_VBIWV1F0_get_write_enable2(data)                                          ((0x00800000&(data))>>23)
#define VI_VBIWV1F0_vstart_shift                                                     (12)
#define VI_VBIWV1F0_vstart_mask                                                      (0x007FF000)
#define VI_VBIWV1F0_vstart(data)                                                     (0x007FF000&((data)<<12))
#define VI_VBIWV1F0_vstart_src(data)                                                 ((0x007FF000&(data))>>12)
#define VI_VBIWV1F0_get_vstart(data)                                                 ((0x007FF000&(data))>>12)
#define VI_VBIWV1F0_write_enable3_shift                                              (11)
#define VI_VBIWV1F0_write_enable3_mask                                               (0x00000800)
#define VI_VBIWV1F0_write_enable3(data)                                              (0x00000800&((data)<<11))
#define VI_VBIWV1F0_write_enable3_src(data)                                          ((0x00000800&(data))>>11)
#define VI_VBIWV1F0_get_write_enable3(data)                                          ((0x00000800&(data))>>11)
#define VI_VBIWV1F0_vend_shift                                                       (0)
#define VI_VBIWV1F0_vend_mask                                                        (0x000007FF)
#define VI_VBIWV1F0_vend(data)                                                       (0x000007FF&((data)<<0))
#define VI_VBIWV1F0_vend_src(data)                                                   ((0x000007FF&(data))>>0)
#define VI_VBIWV1F0_get_vend(data)                                                   ((0x000007FF&(data))>>0)


#define VI_VBIWV1F1                                                                  0x180044c8
#define VI_VBIWV1F1_reg_addr                                                         "0xB80044C8"
#define VI_VBIWV1F1_reg                                                              0xB80044C8
#define VI_VBIWV1F1_inst_adr                                                         "0x0032"
#define VI_VBIWV1F1_inst                                                             0x0032
#define VI_VBIWV1F1_write_enable5_shift                                              (29)
#define VI_VBIWV1F1_write_enable5_mask                                               (0x20000000)
#define VI_VBIWV1F1_write_enable5(data)                                              (0x20000000&((data)<<29))
#define VI_VBIWV1F1_write_enable5_src(data)                                          ((0x20000000&(data))>>29)
#define VI_VBIWV1F1_get_write_enable5(data)                                          ((0x20000000&(data))>>29)
#define VI_VBIWV1F1_write_enable4_shift                                              (27)
#define VI_VBIWV1F1_write_enable4_mask                                               (0x08000000)
#define VI_VBIWV1F1_write_enable4(data)                                              (0x08000000&((data)<<27))
#define VI_VBIWV1F1_write_enable4_src(data)                                          ((0x08000000&(data))>>27)
#define VI_VBIWV1F1_get_write_enable4(data)                                          ((0x08000000&(data))>>27)
#define VI_VBIWV1F1_yonly_shift                                                      (26)
#define VI_VBIWV1F1_yonly_mask                                                       (0x04000000)
#define VI_VBIWV1F1_yonly(data)                                                      (0x04000000&((data)<<26))
#define VI_VBIWV1F1_yonly_src(data)                                                  ((0x04000000&(data))>>26)
#define VI_VBIWV1F1_get_yonly(data)                                                  ((0x04000000&(data))>>26)
#define VI_VBIWV1F1_write_enable1_shift                                              (25)
#define VI_VBIWV1F1_write_enable1_mask                                               (0x02000000)
#define VI_VBIWV1F1_write_enable1(data)                                              (0x02000000&((data)<<25))
#define VI_VBIWV1F1_write_enable1_src(data)                                          ((0x02000000&(data))>>25)
#define VI_VBIWV1F1_get_write_enable1(data)                                          ((0x02000000&(data))>>25)
#define VI_VBIWV1F1_enable_shift                                                     (24)
#define VI_VBIWV1F1_enable_mask                                                      (0x01000000)
#define VI_VBIWV1F1_enable(data)                                                     (0x01000000&((data)<<24))
#define VI_VBIWV1F1_enable_src(data)                                                 ((0x01000000&(data))>>24)
#define VI_VBIWV1F1_get_enable(data)                                                 ((0x01000000&(data))>>24)
#define VI_VBIWV1F1_write_enable2_shift                                              (23)
#define VI_VBIWV1F1_write_enable2_mask                                               (0x00800000)
#define VI_VBIWV1F1_write_enable2(data)                                              (0x00800000&((data)<<23))
#define VI_VBIWV1F1_write_enable2_src(data)                                          ((0x00800000&(data))>>23)
#define VI_VBIWV1F1_get_write_enable2(data)                                          ((0x00800000&(data))>>23)
#define VI_VBIWV1F1_vstart_shift                                                     (12)
#define VI_VBIWV1F1_vstart_mask                                                      (0x007FF000)
#define VI_VBIWV1F1_vstart(data)                                                     (0x007FF000&((data)<<12))
#define VI_VBIWV1F1_vstart_src(data)                                                 ((0x007FF000&(data))>>12)
#define VI_VBIWV1F1_get_vstart(data)                                                 ((0x007FF000&(data))>>12)
#define VI_VBIWV1F1_write_enable3_shift                                              (11)
#define VI_VBIWV1F1_write_enable3_mask                                               (0x00000800)
#define VI_VBIWV1F1_write_enable3(data)                                              (0x00000800&((data)<<11))
#define VI_VBIWV1F1_write_enable3_src(data)                                          ((0x00000800&(data))>>11)
#define VI_VBIWV1F1_get_write_enable3(data)                                          ((0x00000800&(data))>>11)
#define VI_VBIWV1F1_vend_shift                                                       (0)
#define VI_VBIWV1F1_vend_mask                                                        (0x000007FF)
#define VI_VBIWV1F1_vend(data)                                                       (0x000007FF&((data)<<0))
#define VI_VBIWV1F1_vend_src(data)                                                   ((0x000007FF&(data))>>0)
#define VI_VBIWV1F1_get_vend(data)                                                   ((0x000007FF&(data))>>0)


#define VI_VBIWV2F0                                                                  0x18004044
#define VI_VBIWV2F0_reg_addr                                                         "0xB8004044"
#define VI_VBIWV2F0_reg                                                              0xB8004044
#define VI_VBIWV2F0_inst_adr                                                         "0x0011"
#define VI_VBIWV2F0_inst                                                             0x0011
#define VI_VBIWV2F0_write_enable5_shift                                              (29)
#define VI_VBIWV2F0_write_enable5_mask                                               (0x20000000)
#define VI_VBIWV2F0_write_enable5(data)                                              (0x20000000&((data)<<29))
#define VI_VBIWV2F0_write_enable5_src(data)                                          ((0x20000000&(data))>>29)
#define VI_VBIWV2F0_get_write_enable5(data)                                          ((0x20000000&(data))>>29)
#define VI_VBIWV2F0_write_enable1_shift                                              (27)
#define VI_VBIWV2F0_write_enable1_mask                                               (0x08000000)
#define VI_VBIWV2F0_write_enable1(data)                                              (0x08000000&((data)<<27))
#define VI_VBIWV2F0_write_enable1_src(data)                                          ((0x08000000&(data))>>27)
#define VI_VBIWV2F0_get_write_enable1(data)                                          ((0x08000000&(data))>>27)
#define VI_VBIWV2F0_yonly_shift                                                      (26)
#define VI_VBIWV2F0_yonly_mask                                                       (0x04000000)
#define VI_VBIWV2F0_yonly(data)                                                      (0x04000000&((data)<<26))
#define VI_VBIWV2F0_yonly_src(data)                                                  ((0x04000000&(data))>>26)
#define VI_VBIWV2F0_get_yonly(data)                                                  ((0x04000000&(data))>>26)
#define VI_VBIWV2F0_write_enable2_shift                                              (25)
#define VI_VBIWV2F0_write_enable2_mask                                               (0x02000000)
#define VI_VBIWV2F0_write_enable2(data)                                              (0x02000000&((data)<<25))
#define VI_VBIWV2F0_write_enable2_src(data)                                          ((0x02000000&(data))>>25)
#define VI_VBIWV2F0_get_write_enable2(data)                                          ((0x02000000&(data))>>25)
#define VI_VBIWV2F0_enable_shift                                                     (24)
#define VI_VBIWV2F0_enable_mask                                                      (0x01000000)
#define VI_VBIWV2F0_enable(data)                                                     (0x01000000&((data)<<24))
#define VI_VBIWV2F0_enable_src(data)                                                 ((0x01000000&(data))>>24)
#define VI_VBIWV2F0_get_enable(data)                                                 ((0x01000000&(data))>>24)
#define VI_VBIWV2F0_write_enable3_shift                                              (23)
#define VI_VBIWV2F0_write_enable3_mask                                               (0x00800000)
#define VI_VBIWV2F0_write_enable3(data)                                              (0x00800000&((data)<<23))
#define VI_VBIWV2F0_write_enable3_src(data)                                          ((0x00800000&(data))>>23)
#define VI_VBIWV2F0_get_write_enable3(data)                                          ((0x00800000&(data))>>23)
#define VI_VBIWV2F0_vstart_shift                                                     (12)
#define VI_VBIWV2F0_vstart_mask                                                      (0x007FF000)
#define VI_VBIWV2F0_vstart(data)                                                     (0x007FF000&((data)<<12))
#define VI_VBIWV2F0_vstart_src(data)                                                 ((0x007FF000&(data))>>12)
#define VI_VBIWV2F0_get_vstart(data)                                                 ((0x007FF000&(data))>>12)
#define VI_VBIWV2F0_write_enable4_shift                                              (11)
#define VI_VBIWV2F0_write_enable4_mask                                               (0x00000800)
#define VI_VBIWV2F0_write_enable4(data)                                              (0x00000800&((data)<<11))
#define VI_VBIWV2F0_write_enable4_src(data)                                          ((0x00000800&(data))>>11)
#define VI_VBIWV2F0_get_write_enable4(data)                                          ((0x00000800&(data))>>11)
#define VI_VBIWV2F0_vend_shift                                                       (0)
#define VI_VBIWV2F0_vend_mask                                                        (0x000007FF)
#define VI_VBIWV2F0_vend(data)                                                       (0x000007FF&((data)<<0))
#define VI_VBIWV2F0_vend_src(data)                                                   ((0x000007FF&(data))>>0)
#define VI_VBIWV2F0_get_vend(data)                                                   ((0x000007FF&(data))>>0)


#define VI_VBIWV2F1                                                                  0x180044cc
#define VI_VBIWV2F1_reg_addr                                                         "0xB80044CC"
#define VI_VBIWV2F1_reg                                                              0xB80044CC
#define VI_VBIWV2F1_inst_adr                                                         "0x0033"
#define VI_VBIWV2F1_inst                                                             0x0033
#define VI_VBIWV2F1_write_enable5_shift                                              (29)
#define VI_VBIWV2F1_write_enable5_mask                                               (0x20000000)
#define VI_VBIWV2F1_write_enable5(data)                                              (0x20000000&((data)<<29))
#define VI_VBIWV2F1_write_enable5_src(data)                                          ((0x20000000&(data))>>29)
#define VI_VBIWV2F1_get_write_enable5(data)                                          ((0x20000000&(data))>>29)
#define VI_VBIWV2F1_write_enable1_shift                                              (27)
#define VI_VBIWV2F1_write_enable1_mask                                               (0x08000000)
#define VI_VBIWV2F1_write_enable1(data)                                              (0x08000000&((data)<<27))
#define VI_VBIWV2F1_write_enable1_src(data)                                          ((0x08000000&(data))>>27)
#define VI_VBIWV2F1_get_write_enable1(data)                                          ((0x08000000&(data))>>27)
#define VI_VBIWV2F1_yonly_shift                                                      (26)
#define VI_VBIWV2F1_yonly_mask                                                       (0x04000000)
#define VI_VBIWV2F1_yonly(data)                                                      (0x04000000&((data)<<26))
#define VI_VBIWV2F1_yonly_src(data)                                                  ((0x04000000&(data))>>26)
#define VI_VBIWV2F1_get_yonly(data)                                                  ((0x04000000&(data))>>26)
#define VI_VBIWV2F1_write_enable2_shift                                              (25)
#define VI_VBIWV2F1_write_enable2_mask                                               (0x02000000)
#define VI_VBIWV2F1_write_enable2(data)                                              (0x02000000&((data)<<25))
#define VI_VBIWV2F1_write_enable2_src(data)                                          ((0x02000000&(data))>>25)
#define VI_VBIWV2F1_get_write_enable2(data)                                          ((0x02000000&(data))>>25)
#define VI_VBIWV2F1_enable_shift                                                     (24)
#define VI_VBIWV2F1_enable_mask                                                      (0x01000000)
#define VI_VBIWV2F1_enable(data)                                                     (0x01000000&((data)<<24))
#define VI_VBIWV2F1_enable_src(data)                                                 ((0x01000000&(data))>>24)
#define VI_VBIWV2F1_get_enable(data)                                                 ((0x01000000&(data))>>24)
#define VI_VBIWV2F1_write_enable3_shift                                              (23)
#define VI_VBIWV2F1_write_enable3_mask                                               (0x00800000)
#define VI_VBIWV2F1_write_enable3(data)                                              (0x00800000&((data)<<23))
#define VI_VBIWV2F1_write_enable3_src(data)                                          ((0x00800000&(data))>>23)
#define VI_VBIWV2F1_get_write_enable3(data)                                          ((0x00800000&(data))>>23)
#define VI_VBIWV2F1_vstart_shift                                                     (12)
#define VI_VBIWV2F1_vstart_mask                                                      (0x007FF000)
#define VI_VBIWV2F1_vstart(data)                                                     (0x007FF000&((data)<<12))
#define VI_VBIWV2F1_vstart_src(data)                                                 ((0x007FF000&(data))>>12)
#define VI_VBIWV2F1_get_vstart(data)                                                 ((0x007FF000&(data))>>12)
#define VI_VBIWV2F1_write_enable4_shift                                              (11)
#define VI_VBIWV2F1_write_enable4_mask                                               (0x00000800)
#define VI_VBIWV2F1_write_enable4(data)                                              (0x00000800&((data)<<11))
#define VI_VBIWV2F1_write_enable4_src(data)                                          ((0x00000800&(data))>>11)
#define VI_VBIWV2F1_get_write_enable4(data)                                          ((0x00000800&(data))>>11)
#define VI_VBIWV2F1_vend_shift                                                       (0)
#define VI_VBIWV2F1_vend_mask                                                        (0x000007FF)
#define VI_VBIWV2F1_vend(data)                                                       (0x000007FF&((data)<<0))
#define VI_VBIWV2F1_vend_src(data)                                                   ((0x000007FF&(data))>>0)
#define VI_VBIWV2F1_get_vend(data)                                                   ((0x000007FF&(data))>>0)


#define VI_VBIWH1F0                                                                  0x18004048
#define VI_VBIWH1F0_reg_addr                                                         "0xB8004048"
#define VI_VBIWH1F0_reg                                                              0xB8004048
#define VI_VBIWH1F0_inst_adr                                                         "0x0012"
#define VI_VBIWH1F0_inst                                                             0x0012
#define VI_VBIWH1F0_write_enable1_shift                                              (25)
#define VI_VBIWH1F0_write_enable1_mask                                               (0x02000000)
#define VI_VBIWH1F0_write_enable1(data)                                              (0x02000000&((data)<<25))
#define VI_VBIWH1F0_write_enable1_src(data)                                          ((0x02000000&(data))>>25)
#define VI_VBIWH1F0_get_write_enable1(data)                                          ((0x02000000&(data))>>25)
#define VI_VBIWH1F0_hstart_shift                                                     (13)
#define VI_VBIWH1F0_hstart_mask                                                      (0x01FFE000)
#define VI_VBIWH1F0_hstart(data)                                                     (0x01FFE000&((data)<<13))
#define VI_VBIWH1F0_hstart_src(data)                                                 ((0x01FFE000&(data))>>13)
#define VI_VBIWH1F0_get_hstart(data)                                                 ((0x01FFE000&(data))>>13)
#define VI_VBIWH1F0_write_enable2_shift                                              (12)
#define VI_VBIWH1F0_write_enable2_mask                                               (0x00001000)
#define VI_VBIWH1F0_write_enable2(data)                                              (0x00001000&((data)<<12))
#define VI_VBIWH1F0_write_enable2_src(data)                                          ((0x00001000&(data))>>12)
#define VI_VBIWH1F0_get_write_enable2(data)                                          ((0x00001000&(data))>>12)
#define VI_VBIWH1F0_hend_shift                                                       (0)
#define VI_VBIWH1F0_hend_mask                                                        (0x00000FFF)
#define VI_VBIWH1F0_hend(data)                                                       (0x00000FFF&((data)<<0))
#define VI_VBIWH1F0_hend_src(data)                                                   ((0x00000FFF&(data))>>0)
#define VI_VBIWH1F0_get_hend(data)                                                   ((0x00000FFF&(data))>>0)


#define VI_VBIWH1F1                                                                  0x180044d0
#define VI_VBIWH1F1_reg_addr                                                         "0xB80044D0"
#define VI_VBIWH1F1_reg                                                              0xB80044D0
#define VI_VBIWH1F1_inst_adr                                                         "0x0034"
#define VI_VBIWH1F1_inst                                                             0x0034
#define VI_VBIWH1F1_write_enable1_shift                                              (25)
#define VI_VBIWH1F1_write_enable1_mask                                               (0x02000000)
#define VI_VBIWH1F1_write_enable1(data)                                              (0x02000000&((data)<<25))
#define VI_VBIWH1F1_write_enable1_src(data)                                          ((0x02000000&(data))>>25)
#define VI_VBIWH1F1_get_write_enable1(data)                                          ((0x02000000&(data))>>25)
#define VI_VBIWH1F1_hstart_shift                                                     (13)
#define VI_VBIWH1F1_hstart_mask                                                      (0x01FFE000)
#define VI_VBIWH1F1_hstart(data)                                                     (0x01FFE000&((data)<<13))
#define VI_VBIWH1F1_hstart_src(data)                                                 ((0x01FFE000&(data))>>13)
#define VI_VBIWH1F1_get_hstart(data)                                                 ((0x01FFE000&(data))>>13)
#define VI_VBIWH1F1_write_enable2_shift                                              (12)
#define VI_VBIWH1F1_write_enable2_mask                                               (0x00001000)
#define VI_VBIWH1F1_write_enable2(data)                                              (0x00001000&((data)<<12))
#define VI_VBIWH1F1_write_enable2_src(data)                                          ((0x00001000&(data))>>12)
#define VI_VBIWH1F1_get_write_enable2(data)                                          ((0x00001000&(data))>>12)
#define VI_VBIWH1F1_hend_shift                                                       (0)
#define VI_VBIWH1F1_hend_mask                                                        (0x00000FFF)
#define VI_VBIWH1F1_hend(data)                                                       (0x00000FFF&((data)<<0))
#define VI_VBIWH1F1_hend_src(data)                                                   ((0x00000FFF&(data))>>0)
#define VI_VBIWH1F1_get_hend(data)                                                   ((0x00000FFF&(data))>>0)


#define VI_VBIWH2F0                                                                  0x1800404c
#define VI_VBIWH2F0_reg_addr                                                         "0xB800404C"
#define VI_VBIWH2F0_reg                                                              0xB800404C
#define VI_VBIWH2F0_inst_adr                                                         "0x0013"
#define VI_VBIWH2F0_inst                                                             0x0013
#define VI_VBIWH2F0_write_enable1_shift                                              (25)
#define VI_VBIWH2F0_write_enable1_mask                                               (0x02000000)
#define VI_VBIWH2F0_write_enable1(data)                                              (0x02000000&((data)<<25))
#define VI_VBIWH2F0_write_enable1_src(data)                                          ((0x02000000&(data))>>25)
#define VI_VBIWH2F0_get_write_enable1(data)                                          ((0x02000000&(data))>>25)
#define VI_VBIWH2F0_hstart_shift                                                     (13)
#define VI_VBIWH2F0_hstart_mask                                                      (0x01FFE000)
#define VI_VBIWH2F0_hstart(data)                                                     (0x01FFE000&((data)<<13))
#define VI_VBIWH2F0_hstart_src(data)                                                 ((0x01FFE000&(data))>>13)
#define VI_VBIWH2F0_get_hstart(data)                                                 ((0x01FFE000&(data))>>13)
#define VI_VBIWH2F0_write_enable2_shift                                              (12)
#define VI_VBIWH2F0_write_enable2_mask                                               (0x00001000)
#define VI_VBIWH2F0_write_enable2(data)                                              (0x00001000&((data)<<12))
#define VI_VBIWH2F0_write_enable2_src(data)                                          ((0x00001000&(data))>>12)
#define VI_VBIWH2F0_get_write_enable2(data)                                          ((0x00001000&(data))>>12)
#define VI_VBIWH2F0_hend_shift                                                       (0)
#define VI_VBIWH2F0_hend_mask                                                        (0x00000FFF)
#define VI_VBIWH2F0_hend(data)                                                       (0x00000FFF&((data)<<0))
#define VI_VBIWH2F0_hend_src(data)                                                   ((0x00000FFF&(data))>>0)
#define VI_VBIWH2F0_get_hend(data)                                                   ((0x00000FFF&(data))>>0)


#define VI_VBIWH2F1                                                                  0x180044d4
#define VI_VBIWH2F1_reg_addr                                                         "0xB80044D4"
#define VI_VBIWH2F1_reg                                                              0xB80044D4
#define VI_VBIWH2F1_inst_adr                                                         "0x0035"
#define VI_VBIWH2F1_inst                                                             0x0035
#define VI_VBIWH2F1_write_enable1_shift                                              (25)
#define VI_VBIWH2F1_write_enable1_mask                                               (0x02000000)
#define VI_VBIWH2F1_write_enable1(data)                                              (0x02000000&((data)<<25))
#define VI_VBIWH2F1_write_enable1_src(data)                                          ((0x02000000&(data))>>25)
#define VI_VBIWH2F1_get_write_enable1(data)                                          ((0x02000000&(data))>>25)
#define VI_VBIWH2F1_hstart_shift                                                     (13)
#define VI_VBIWH2F1_hstart_mask                                                      (0x01FFE000)
#define VI_VBIWH2F1_hstart(data)                                                     (0x01FFE000&((data)<<13))
#define VI_VBIWH2F1_hstart_src(data)                                                 ((0x01FFE000&(data))>>13)
#define VI_VBIWH2F1_get_hstart(data)                                                 ((0x01FFE000&(data))>>13)
#define VI_VBIWH2F1_write_enable2_shift                                              (12)
#define VI_VBIWH2F1_write_enable2_mask                                               (0x00001000)
#define VI_VBIWH2F1_write_enable2(data)                                              (0x00001000&((data)<<12))
#define VI_VBIWH2F1_write_enable2_src(data)                                          ((0x00001000&(data))>>12)
#define VI_VBIWH2F1_get_write_enable2(data)                                          ((0x00001000&(data))>>12)
#define VI_VBIWH2F1_hend_shift                                                       (0)
#define VI_VBIWH2F1_hend_mask                                                        (0x00000FFF)
#define VI_VBIWH2F1_hend(data)                                                       (0x00000FFF&((data)<<0))
#define VI_VBIWH2F1_hend_src(data)                                                   ((0x00000FFF&(data))>>0)
#define VI_VBIWH2F1_get_hend(data)                                                   ((0x00000FFF&(data))>>0)


#define VI_VBIWV1F0_SC                                                               0x180044f0
#define VI_VBIWV1F0_SC_reg_addr                                                      "0xB80044F0"
#define VI_VBIWV1F0_SC_reg                                                           0xB80044F0
#define VI_VBIWV1F0_SC_inst_adr                                                      "0x003C"
#define VI_VBIWV1F0_SC_inst                                                          0x003C
#define VI_VBIWV1F0_SC_write_enable1_shift                                           (25)
#define VI_VBIWV1F0_SC_write_enable1_mask                                            (0x02000000)
#define VI_VBIWV1F0_SC_write_enable1(data)                                           (0x02000000&((data)<<25))
#define VI_VBIWV1F0_SC_write_enable1_src(data)                                       ((0x02000000&(data))>>25)
#define VI_VBIWV1F0_SC_get_write_enable1(data)                                       ((0x02000000&(data))>>25)
#define VI_VBIWV1F0_SC_en_shift                                                      (24)
#define VI_VBIWV1F0_SC_en_mask                                                       (0x01000000)
#define VI_VBIWV1F0_SC_en(data)                                                      (0x01000000&((data)<<24))
#define VI_VBIWV1F0_SC_en_src(data)                                                  ((0x01000000&(data))>>24)
#define VI_VBIWV1F0_SC_get_en(data)                                                  ((0x01000000&(data))>>24)
#define VI_VBIWV1F0_SC_write_enable2_shift                                           (23)
#define VI_VBIWV1F0_SC_write_enable2_mask                                            (0x00800000)
#define VI_VBIWV1F0_SC_write_enable2(data)                                           (0x00800000&((data)<<23))
#define VI_VBIWV1F0_SC_write_enable2_src(data)                                       ((0x00800000&(data))>>23)
#define VI_VBIWV1F0_SC_get_write_enable2(data)                                       ((0x00800000&(data))>>23)
#define VI_VBIWV1F0_SC_vstart_shift                                                  (12)
#define VI_VBIWV1F0_SC_vstart_mask                                                   (0x007FF000)
#define VI_VBIWV1F0_SC_vstart(data)                                                  (0x007FF000&((data)<<12))
#define VI_VBIWV1F0_SC_vstart_src(data)                                              ((0x007FF000&(data))>>12)
#define VI_VBIWV1F0_SC_get_vstart(data)                                              ((0x007FF000&(data))>>12)
#define VI_VBIWV1F0_SC_write_enable3_shift                                           (11)
#define VI_VBIWV1F0_SC_write_enable3_mask                                            (0x00000800)
#define VI_VBIWV1F0_SC_write_enable3(data)                                           (0x00000800&((data)<<11))
#define VI_VBIWV1F0_SC_write_enable3_src(data)                                       ((0x00000800&(data))>>11)
#define VI_VBIWV1F0_SC_get_write_enable3(data)                                       ((0x00000800&(data))>>11)
#define VI_VBIWV1F0_SC_vend_shift                                                    (0)
#define VI_VBIWV1F0_SC_vend_mask                                                     (0x000007FF)
#define VI_VBIWV1F0_SC_vend(data)                                                    (0x000007FF&((data)<<0))
#define VI_VBIWV1F0_SC_vend_src(data)                                                ((0x000007FF&(data))>>0)
#define VI_VBIWV1F0_SC_get_vend(data)                                                ((0x000007FF&(data))>>0)


#define VI_VBIWV1F1_SC                                                               0x180044f4
#define VI_VBIWV1F1_SC_reg_addr                                                      "0xB80044F4"
#define VI_VBIWV1F1_SC_reg                                                           0xB80044F4
#define VI_VBIWV1F1_SC_inst_adr                                                      "0x003D"
#define VI_VBIWV1F1_SC_inst                                                          0x003D
#define VI_VBIWV1F1_SC_write_enable1_shift                                           (25)
#define VI_VBIWV1F1_SC_write_enable1_mask                                            (0x02000000)
#define VI_VBIWV1F1_SC_write_enable1(data)                                           (0x02000000&((data)<<25))
#define VI_VBIWV1F1_SC_write_enable1_src(data)                                       ((0x02000000&(data))>>25)
#define VI_VBIWV1F1_SC_get_write_enable1(data)                                       ((0x02000000&(data))>>25)
#define VI_VBIWV1F1_SC_en_shift                                                      (24)
#define VI_VBIWV1F1_SC_en_mask                                                       (0x01000000)
#define VI_VBIWV1F1_SC_en(data)                                                      (0x01000000&((data)<<24))
#define VI_VBIWV1F1_SC_en_src(data)                                                  ((0x01000000&(data))>>24)
#define VI_VBIWV1F1_SC_get_en(data)                                                  ((0x01000000&(data))>>24)
#define VI_VBIWV1F1_SC_write_enable2_shift                                           (23)
#define VI_VBIWV1F1_SC_write_enable2_mask                                            (0x00800000)
#define VI_VBIWV1F1_SC_write_enable2(data)                                           (0x00800000&((data)<<23))
#define VI_VBIWV1F1_SC_write_enable2_src(data)                                       ((0x00800000&(data))>>23)
#define VI_VBIWV1F1_SC_get_write_enable2(data)                                       ((0x00800000&(data))>>23)
#define VI_VBIWV1F1_SC_vstart_shift                                                  (12)
#define VI_VBIWV1F1_SC_vstart_mask                                                   (0x007FF000)
#define VI_VBIWV1F1_SC_vstart(data)                                                  (0x007FF000&((data)<<12))
#define VI_VBIWV1F1_SC_vstart_src(data)                                              ((0x007FF000&(data))>>12)
#define VI_VBIWV1F1_SC_get_vstart(data)                                              ((0x007FF000&(data))>>12)
#define VI_VBIWV1F1_SC_write_enable3_shift                                           (11)
#define VI_VBIWV1F1_SC_write_enable3_mask                                            (0x00000800)
#define VI_VBIWV1F1_SC_write_enable3(data)                                           (0x00000800&((data)<<11))
#define VI_VBIWV1F1_SC_write_enable3_src(data)                                       ((0x00000800&(data))>>11)
#define VI_VBIWV1F1_SC_get_write_enable3(data)                                       ((0x00000800&(data))>>11)
#define VI_VBIWV1F1_SC_vend_shift                                                    (0)
#define VI_VBIWV1F1_SC_vend_mask                                                     (0x000007FF)
#define VI_VBIWV1F1_SC_vend(data)                                                    (0x000007FF&((data)<<0))
#define VI_VBIWV1F1_SC_vend_src(data)                                                ((0x000007FF&(data))>>0)
#define VI_VBIWV1F1_SC_get_vend(data)                                                ((0x000007FF&(data))>>0)


#define VI_VBIWV2F0_SC                                                               0x180044f8
#define VI_VBIWV2F0_SC_reg_addr                                                      "0xB80044F8"
#define VI_VBIWV2F0_SC_reg                                                           0xB80044F8
#define VI_VBIWV2F0_SC_inst_adr                                                      "0x003E"
#define VI_VBIWV2F0_SC_inst                                                          0x003E
#define VI_VBIWV2F0_SC_write_enable1_shift                                           (25)
#define VI_VBIWV2F0_SC_write_enable1_mask                                            (0x02000000)
#define VI_VBIWV2F0_SC_write_enable1(data)                                           (0x02000000&((data)<<25))
#define VI_VBIWV2F0_SC_write_enable1_src(data)                                       ((0x02000000&(data))>>25)
#define VI_VBIWV2F0_SC_get_write_enable1(data)                                       ((0x02000000&(data))>>25)
#define VI_VBIWV2F0_SC_en_shift                                                      (24)
#define VI_VBIWV2F0_SC_en_mask                                                       (0x01000000)
#define VI_VBIWV2F0_SC_en(data)                                                      (0x01000000&((data)<<24))
#define VI_VBIWV2F0_SC_en_src(data)                                                  ((0x01000000&(data))>>24)
#define VI_VBIWV2F0_SC_get_en(data)                                                  ((0x01000000&(data))>>24)
#define VI_VBIWV2F0_SC_write_enable2_shift                                           (23)
#define VI_VBIWV2F0_SC_write_enable2_mask                                            (0x00800000)
#define VI_VBIWV2F0_SC_write_enable2(data)                                           (0x00800000&((data)<<23))
#define VI_VBIWV2F0_SC_write_enable2_src(data)                                       ((0x00800000&(data))>>23)
#define VI_VBIWV2F0_SC_get_write_enable2(data)                                       ((0x00800000&(data))>>23)
#define VI_VBIWV2F0_SC_vstart_shift                                                  (12)
#define VI_VBIWV2F0_SC_vstart_mask                                                   (0x007FF000)
#define VI_VBIWV2F0_SC_vstart(data)                                                  (0x007FF000&((data)<<12))
#define VI_VBIWV2F0_SC_vstart_src(data)                                              ((0x007FF000&(data))>>12)
#define VI_VBIWV2F0_SC_get_vstart(data)                                              ((0x007FF000&(data))>>12)
#define VI_VBIWV2F0_SC_write_enable3_shift                                           (11)
#define VI_VBIWV2F0_SC_write_enable3_mask                                            (0x00000800)
#define VI_VBIWV2F0_SC_write_enable3(data)                                           (0x00000800&((data)<<11))
#define VI_VBIWV2F0_SC_write_enable3_src(data)                                       ((0x00000800&(data))>>11)
#define VI_VBIWV2F0_SC_get_write_enable3(data)                                       ((0x00000800&(data))>>11)
#define VI_VBIWV2F0_SC_vend_shift                                                    (0)
#define VI_VBIWV2F0_SC_vend_mask                                                     (0x000007FF)
#define VI_VBIWV2F0_SC_vend(data)                                                    (0x000007FF&((data)<<0))
#define VI_VBIWV2F0_SC_vend_src(data)                                                ((0x000007FF&(data))>>0)
#define VI_VBIWV2F0_SC_get_vend(data)                                                ((0x000007FF&(data))>>0)


#define VI_VBIWV2F1_SC                                                               0x180044fc
#define VI_VBIWV2F1_SC_reg_addr                                                      "0xB80044FC"
#define VI_VBIWV2F1_SC_reg                                                           0xB80044FC
#define VI_VBIWV2F1_SC_inst_adr                                                      "0x003F"
#define VI_VBIWV2F1_SC_inst                                                          0x003F
#define VI_VBIWV2F1_SC_write_enable1_shift                                           (25)
#define VI_VBIWV2F1_SC_write_enable1_mask                                            (0x02000000)
#define VI_VBIWV2F1_SC_write_enable1(data)                                           (0x02000000&((data)<<25))
#define VI_VBIWV2F1_SC_write_enable1_src(data)                                       ((0x02000000&(data))>>25)
#define VI_VBIWV2F1_SC_get_write_enable1(data)                                       ((0x02000000&(data))>>25)
#define VI_VBIWV2F1_SC_en_shift                                                      (24)
#define VI_VBIWV2F1_SC_en_mask                                                       (0x01000000)
#define VI_VBIWV2F1_SC_en(data)                                                      (0x01000000&((data)<<24))
#define VI_VBIWV2F1_SC_en_src(data)                                                  ((0x01000000&(data))>>24)
#define VI_VBIWV2F1_SC_get_en(data)                                                  ((0x01000000&(data))>>24)
#define VI_VBIWV2F1_SC_write_enable2_shift                                           (23)
#define VI_VBIWV2F1_SC_write_enable2_mask                                            (0x00800000)
#define VI_VBIWV2F1_SC_write_enable2(data)                                           (0x00800000&((data)<<23))
#define VI_VBIWV2F1_SC_write_enable2_src(data)                                       ((0x00800000&(data))>>23)
#define VI_VBIWV2F1_SC_get_write_enable2(data)                                       ((0x00800000&(data))>>23)
#define VI_VBIWV2F1_SC_vstart_shift                                                  (12)
#define VI_VBIWV2F1_SC_vstart_mask                                                   (0x007FF000)
#define VI_VBIWV2F1_SC_vstart(data)                                                  (0x007FF000&((data)<<12))
#define VI_VBIWV2F1_SC_vstart_src(data)                                              ((0x007FF000&(data))>>12)
#define VI_VBIWV2F1_SC_get_vstart(data)                                              ((0x007FF000&(data))>>12)
#define VI_VBIWV2F1_SC_write_enable3_shift                                           (11)
#define VI_VBIWV2F1_SC_write_enable3_mask                                            (0x00000800)
#define VI_VBIWV2F1_SC_write_enable3(data)                                           (0x00000800&((data)<<11))
#define VI_VBIWV2F1_SC_write_enable3_src(data)                                       ((0x00000800&(data))>>11)
#define VI_VBIWV2F1_SC_get_write_enable3(data)                                       ((0x00000800&(data))>>11)
#define VI_VBIWV2F1_SC_vend_shift                                                    (0)
#define VI_VBIWV2F1_SC_vend_mask                                                     (0x000007FF)
#define VI_VBIWV2F1_SC_vend(data)                                                    (0x000007FF&((data)<<0))
#define VI_VBIWV2F1_SC_vend_src(data)                                                ((0x000007FF&(data))>>0)
#define VI_VBIWV2F1_SC_get_vend(data)                                                ((0x000007FF&(data))>>0)


#define VI_VBIWH1F0_SC                                                               0x18004500
#define VI_VBIWH1F0_SC_reg_addr                                                      "0xB8004500"
#define VI_VBIWH1F0_SC_reg                                                           0xB8004500
#define VI_VBIWH1F0_SC_inst_adr                                                      "0x0040"
#define VI_VBIWH1F0_SC_inst                                                          0x0040
#define VI_VBIWH1F0_SC_write_enable1_shift                                           (25)
#define VI_VBIWH1F0_SC_write_enable1_mask                                            (0x02000000)
#define VI_VBIWH1F0_SC_write_enable1(data)                                           (0x02000000&((data)<<25))
#define VI_VBIWH1F0_SC_write_enable1_src(data)                                       ((0x02000000&(data))>>25)
#define VI_VBIWH1F0_SC_get_write_enable1(data)                                       ((0x02000000&(data))>>25)
#define VI_VBIWH1F0_SC_hstart_shift                                                  (13)
#define VI_VBIWH1F0_SC_hstart_mask                                                   (0x01FFE000)
#define VI_VBIWH1F0_SC_hstart(data)                                                  (0x01FFE000&((data)<<13))
#define VI_VBIWH1F0_SC_hstart_src(data)                                              ((0x01FFE000&(data))>>13)
#define VI_VBIWH1F0_SC_get_hstart(data)                                              ((0x01FFE000&(data))>>13)
#define VI_VBIWH1F0_SC_write_enable2_shift                                           (12)
#define VI_VBIWH1F0_SC_write_enable2_mask                                            (0x00001000)
#define VI_VBIWH1F0_SC_write_enable2(data)                                           (0x00001000&((data)<<12))
#define VI_VBIWH1F0_SC_write_enable2_src(data)                                       ((0x00001000&(data))>>12)
#define VI_VBIWH1F0_SC_get_write_enable2(data)                                       ((0x00001000&(data))>>12)
#define VI_VBIWH1F0_SC_hend_shift                                                    (0)
#define VI_VBIWH1F0_SC_hend_mask                                                     (0x00000FFF)
#define VI_VBIWH1F0_SC_hend(data)                                                    (0x00000FFF&((data)<<0))
#define VI_VBIWH1F0_SC_hend_src(data)                                                ((0x00000FFF&(data))>>0)
#define VI_VBIWH1F0_SC_get_hend(data)                                                ((0x00000FFF&(data))>>0)


#define VI_VBIWH1F1_SC                                                               0x18004504
#define VI_VBIWH1F1_SC_reg_addr                                                      "0xB8004504"
#define VI_VBIWH1F1_SC_reg                                                           0xB8004504
#define VI_VBIWH1F1_SC_inst_adr                                                      "0x0041"
#define VI_VBIWH1F1_SC_inst                                                          0x0041
#define VI_VBIWH1F1_SC_write_enable1_shift                                           (25)
#define VI_VBIWH1F1_SC_write_enable1_mask                                            (0x02000000)
#define VI_VBIWH1F1_SC_write_enable1(data)                                           (0x02000000&((data)<<25))
#define VI_VBIWH1F1_SC_write_enable1_src(data)                                       ((0x02000000&(data))>>25)
#define VI_VBIWH1F1_SC_get_write_enable1(data)                                       ((0x02000000&(data))>>25)
#define VI_VBIWH1F1_SC_hstart_shift                                                  (13)
#define VI_VBIWH1F1_SC_hstart_mask                                                   (0x01FFE000)
#define VI_VBIWH1F1_SC_hstart(data)                                                  (0x01FFE000&((data)<<13))
#define VI_VBIWH1F1_SC_hstart_src(data)                                              ((0x01FFE000&(data))>>13)
#define VI_VBIWH1F1_SC_get_hstart(data)                                              ((0x01FFE000&(data))>>13)
#define VI_VBIWH1F1_SC_write_enable2_shift                                           (12)
#define VI_VBIWH1F1_SC_write_enable2_mask                                            (0x00001000)
#define VI_VBIWH1F1_SC_write_enable2(data)                                           (0x00001000&((data)<<12))
#define VI_VBIWH1F1_SC_write_enable2_src(data)                                       ((0x00001000&(data))>>12)
#define VI_VBIWH1F1_SC_get_write_enable2(data)                                       ((0x00001000&(data))>>12)
#define VI_VBIWH1F1_SC_hend_shift                                                    (0)
#define VI_VBIWH1F1_SC_hend_mask                                                     (0x00000FFF)
#define VI_VBIWH1F1_SC_hend(data)                                                    (0x00000FFF&((data)<<0))
#define VI_VBIWH1F1_SC_hend_src(data)                                                ((0x00000FFF&(data))>>0)
#define VI_VBIWH1F1_SC_get_hend(data)                                                ((0x00000FFF&(data))>>0)


#define VI_VBIWH2F0_SC                                                               0x18004508
#define VI_VBIWH2F0_SC_reg_addr                                                      "0xB8004508"
#define VI_VBIWH2F0_SC_reg                                                           0xB8004508
#define VI_VBIWH2F0_SC_inst_adr                                                      "0x0042"
#define VI_VBIWH2F0_SC_inst                                                          0x0042
#define VI_VBIWH2F0_SC_write_enable1_shift                                           (25)
#define VI_VBIWH2F0_SC_write_enable1_mask                                            (0x02000000)
#define VI_VBIWH2F0_SC_write_enable1(data)                                           (0x02000000&((data)<<25))
#define VI_VBIWH2F0_SC_write_enable1_src(data)                                       ((0x02000000&(data))>>25)
#define VI_VBIWH2F0_SC_get_write_enable1(data)                                       ((0x02000000&(data))>>25)
#define VI_VBIWH2F0_SC_hstart_shift                                                  (13)
#define VI_VBIWH2F0_SC_hstart_mask                                                   (0x01FFE000)
#define VI_VBIWH2F0_SC_hstart(data)                                                  (0x01FFE000&((data)<<13))
#define VI_VBIWH2F0_SC_hstart_src(data)                                              ((0x01FFE000&(data))>>13)
#define VI_VBIWH2F0_SC_get_hstart(data)                                              ((0x01FFE000&(data))>>13)
#define VI_VBIWH2F0_SC_write_enable2_shift                                           (12)
#define VI_VBIWH2F0_SC_write_enable2_mask                                            (0x00001000)
#define VI_VBIWH2F0_SC_write_enable2(data)                                           (0x00001000&((data)<<12))
#define VI_VBIWH2F0_SC_write_enable2_src(data)                                       ((0x00001000&(data))>>12)
#define VI_VBIWH2F0_SC_get_write_enable2(data)                                       ((0x00001000&(data))>>12)
#define VI_VBIWH2F0_SC_hend_shift                                                    (0)
#define VI_VBIWH2F0_SC_hend_mask                                                     (0x00000FFF)
#define VI_VBIWH2F0_SC_hend(data)                                                    (0x00000FFF&((data)<<0))
#define VI_VBIWH2F0_SC_hend_src(data)                                                ((0x00000FFF&(data))>>0)
#define VI_VBIWH2F0_SC_get_hend(data)                                                ((0x00000FFF&(data))>>0)


#define VI_VBIWH2F1_SC                                                               0x1800450c
#define VI_VBIWH2F1_SC_reg_addr                                                      "0xB800450C"
#define VI_VBIWH2F1_SC_reg                                                           0xB800450C
#define VI_VBIWH2F1_SC_inst_adr                                                      "0x0043"
#define VI_VBIWH2F1_SC_inst                                                          0x0043
#define VI_VBIWH2F1_SC_write_enable1_shift                                           (25)
#define VI_VBIWH2F1_SC_write_enable1_mask                                            (0x02000000)
#define VI_VBIWH2F1_SC_write_enable1(data)                                           (0x02000000&((data)<<25))
#define VI_VBIWH2F1_SC_write_enable1_src(data)                                       ((0x02000000&(data))>>25)
#define VI_VBIWH2F1_SC_get_write_enable1(data)                                       ((0x02000000&(data))>>25)
#define VI_VBIWH2F1_SC_hstart_shift                                                  (13)
#define VI_VBIWH2F1_SC_hstart_mask                                                   (0x01FFE000)
#define VI_VBIWH2F1_SC_hstart(data)                                                  (0x01FFE000&((data)<<13))
#define VI_VBIWH2F1_SC_hstart_src(data)                                              ((0x01FFE000&(data))>>13)
#define VI_VBIWH2F1_SC_get_hstart(data)                                              ((0x01FFE000&(data))>>13)
#define VI_VBIWH2F1_SC_write_enable2_shift                                           (12)
#define VI_VBIWH2F1_SC_write_enable2_mask                                            (0x00001000)
#define VI_VBIWH2F1_SC_write_enable2(data)                                           (0x00001000&((data)<<12))
#define VI_VBIWH2F1_SC_write_enable2_src(data)                                       ((0x00001000&(data))>>12)
#define VI_VBIWH2F1_SC_get_write_enable2(data)                                       ((0x00001000&(data))>>12)
#define VI_VBIWH2F1_SC_hend_shift                                                    (0)
#define VI_VBIWH2F1_SC_hend_mask                                                     (0x00000FFF)
#define VI_VBIWH2F1_SC_hend(data)                                                    (0x00000FFF&((data)<<0))
#define VI_VBIWH2F1_SC_hend_src(data)                                                ((0x00000FFF&(data))>>0)
#define VI_VBIWH2F1_SC_get_hend(data)                                                ((0x00000FFF&(data))>>0)


#define VI_VBIF0_SCALING1                                                            0x18004050
#define VI_VBIF0_SCALING1_reg_addr                                                   "0xB8004050"
#define VI_VBIF0_SCALING1_reg                                                        0xB8004050
#define VI_VBIF0_SCALING1_inst_adr                                                   "0x0014"
#define VI_VBIF0_SCALING1_inst                                                       0x0014
#define VI_VBIF0_SCALING1_write_enable1_shift                                        (19)
#define VI_VBIF0_SCALING1_write_enable1_mask                                         (0x00080000)
#define VI_VBIF0_SCALING1_write_enable1(data)                                        (0x00080000&((data)<<19))
#define VI_VBIF0_SCALING1_write_enable1_src(data)                                    ((0x00080000&(data))>>19)
#define VI_VBIF0_SCALING1_get_write_enable1(data)                                    ((0x00080000&(data))>>19)
#define VI_VBIF0_SCALING1_scaling_en1_shift                                          (18)
#define VI_VBIF0_SCALING1_scaling_en1_mask                                           (0x00040000)
#define VI_VBIF0_SCALING1_scaling_en1(data)                                          (0x00040000&((data)<<18))
#define VI_VBIF0_SCALING1_scaling_en1_src(data)                                      ((0x00040000&(data))>>18)
#define VI_VBIF0_SCALING1_get_scaling_en1(data)                                      ((0x00040000&(data))>>18)
#define VI_VBIF0_SCALING1_write_enable2_shift                                        (17)
#define VI_VBIF0_SCALING1_write_enable2_mask                                         (0x00020000)
#define VI_VBIF0_SCALING1_write_enable2(data)                                        (0x00020000&((data)<<17))
#define VI_VBIF0_SCALING1_write_enable2_src(data)                                    ((0x00020000&(data))>>17)
#define VI_VBIF0_SCALING1_get_write_enable2(data)                                    ((0x00020000&(data))>>17)
#define VI_VBIF0_SCALING1_gain_shift                                                 (9)
#define VI_VBIF0_SCALING1_gain_mask                                                  (0x0001FE00)
#define VI_VBIF0_SCALING1_gain(data)                                                 (0x0001FE00&((data)<<9))
#define VI_VBIF0_SCALING1_gain_src(data)                                             ((0x0001FE00&(data))>>9)
#define VI_VBIF0_SCALING1_get_gain(data)                                             ((0x0001FE00&(data))>>9)
#define VI_VBIF0_SCALING1_write_enable3_shift                                        (8)
#define VI_VBIF0_SCALING1_write_enable3_mask                                         (0x00000100)
#define VI_VBIF0_SCALING1_write_enable3(data)                                        (0x00000100&((data)<<8))
#define VI_VBIF0_SCALING1_write_enable3_src(data)                                    ((0x00000100&(data))>>8)
#define VI_VBIF0_SCALING1_get_write_enable3(data)                                    ((0x00000100&(data))>>8)
#define VI_VBIF0_SCALING1_offset_shift                                               (0)
#define VI_VBIF0_SCALING1_offset_mask                                                (0x000000FF)
#define VI_VBIF0_SCALING1_offset(data)                                               (0x000000FF&((data)<<0))
#define VI_VBIF0_SCALING1_offset_src(data)                                           ((0x000000FF&(data))>>0)
#define VI_VBIF0_SCALING1_get_offset(data)                                           ((0x000000FF&(data))>>0)


#define VI_VBIF1_SCALING1                                                            0x180044d8
#define VI_VBIF1_SCALING1_reg_addr                                                   "0xB80044D8"
#define VI_VBIF1_SCALING1_reg                                                        0xB80044D8
#define VI_VBIF1_SCALING1_inst_adr                                                   "0x0036"
#define VI_VBIF1_SCALING1_inst                                                       0x0036
#define VI_VBIF1_SCALING1_write_enable1_shift                                        (19)
#define VI_VBIF1_SCALING1_write_enable1_mask                                         (0x00080000)
#define VI_VBIF1_SCALING1_write_enable1(data)                                        (0x00080000&((data)<<19))
#define VI_VBIF1_SCALING1_write_enable1_src(data)                                    ((0x00080000&(data))>>19)
#define VI_VBIF1_SCALING1_get_write_enable1(data)                                    ((0x00080000&(data))>>19)
#define VI_VBIF1_SCALING1_scaling_en1_shift                                          (18)
#define VI_VBIF1_SCALING1_scaling_en1_mask                                           (0x00040000)
#define VI_VBIF1_SCALING1_scaling_en1(data)                                          (0x00040000&((data)<<18))
#define VI_VBIF1_SCALING1_scaling_en1_src(data)                                      ((0x00040000&(data))>>18)
#define VI_VBIF1_SCALING1_get_scaling_en1(data)                                      ((0x00040000&(data))>>18)
#define VI_VBIF1_SCALING1_write_enable2_shift                                        (17)
#define VI_VBIF1_SCALING1_write_enable2_mask                                         (0x00020000)
#define VI_VBIF1_SCALING1_write_enable2(data)                                        (0x00020000&((data)<<17))
#define VI_VBIF1_SCALING1_write_enable2_src(data)                                    ((0x00020000&(data))>>17)
#define VI_VBIF1_SCALING1_get_write_enable2(data)                                    ((0x00020000&(data))>>17)
#define VI_VBIF1_SCALING1_gain_shift                                                 (9)
#define VI_VBIF1_SCALING1_gain_mask                                                  (0x0001FE00)
#define VI_VBIF1_SCALING1_gain(data)                                                 (0x0001FE00&((data)<<9))
#define VI_VBIF1_SCALING1_gain_src(data)                                             ((0x0001FE00&(data))>>9)
#define VI_VBIF1_SCALING1_get_gain(data)                                             ((0x0001FE00&(data))>>9)
#define VI_VBIF1_SCALING1_write_enable3_shift                                        (8)
#define VI_VBIF1_SCALING1_write_enable3_mask                                         (0x00000100)
#define VI_VBIF1_SCALING1_write_enable3(data)                                        (0x00000100&((data)<<8))
#define VI_VBIF1_SCALING1_write_enable3_src(data)                                    ((0x00000100&(data))>>8)
#define VI_VBIF1_SCALING1_get_write_enable3(data)                                    ((0x00000100&(data))>>8)
#define VI_VBIF1_SCALING1_offset_shift                                               (0)
#define VI_VBIF1_SCALING1_offset_mask                                                (0x000000FF)
#define VI_VBIF1_SCALING1_offset(data)                                               (0x000000FF&((data)<<0))
#define VI_VBIF1_SCALING1_offset_src(data)                                           ((0x000000FF&(data))>>0)
#define VI_VBIF1_SCALING1_get_offset(data)                                           ((0x000000FF&(data))>>0)


#define VI_VBIF0_SCALING2                                                            0x18004054
#define VI_VBIF0_SCALING2_reg_addr                                                   "0xB8004054"
#define VI_VBIF0_SCALING2_reg                                                        0xB8004054
#define VI_VBIF0_SCALING2_inst_adr                                                   "0x0015"
#define VI_VBIF0_SCALING2_inst                                                       0x0015
#define VI_VBIF0_SCALING2_write_enable1_shift                                        (19)
#define VI_VBIF0_SCALING2_write_enable1_mask                                         (0x00080000)
#define VI_VBIF0_SCALING2_write_enable1(data)                                        (0x00080000&((data)<<19))
#define VI_VBIF0_SCALING2_write_enable1_src(data)                                    ((0x00080000&(data))>>19)
#define VI_VBIF0_SCALING2_get_write_enable1(data)                                    ((0x00080000&(data))>>19)
#define VI_VBIF0_SCALING2_scaling_en2_shift                                          (18)
#define VI_VBIF0_SCALING2_scaling_en2_mask                                           (0x00040000)
#define VI_VBIF0_SCALING2_scaling_en2(data)                                          (0x00040000&((data)<<18))
#define VI_VBIF0_SCALING2_scaling_en2_src(data)                                      ((0x00040000&(data))>>18)
#define VI_VBIF0_SCALING2_get_scaling_en2(data)                                      ((0x00040000&(data))>>18)
#define VI_VBIF0_SCALING2_write_enable2_shift                                        (17)
#define VI_VBIF0_SCALING2_write_enable2_mask                                         (0x00020000)
#define VI_VBIF0_SCALING2_write_enable2(data)                                        (0x00020000&((data)<<17))
#define VI_VBIF0_SCALING2_write_enable2_src(data)                                    ((0x00020000&(data))>>17)
#define VI_VBIF0_SCALING2_get_write_enable2(data)                                    ((0x00020000&(data))>>17)
#define VI_VBIF0_SCALING2_gain_shift                                                 (9)
#define VI_VBIF0_SCALING2_gain_mask                                                  (0x0001FE00)
#define VI_VBIF0_SCALING2_gain(data)                                                 (0x0001FE00&((data)<<9))
#define VI_VBIF0_SCALING2_gain_src(data)                                             ((0x0001FE00&(data))>>9)
#define VI_VBIF0_SCALING2_get_gain(data)                                             ((0x0001FE00&(data))>>9)
#define VI_VBIF0_SCALING2_write_enable3_shift                                        (8)
#define VI_VBIF0_SCALING2_write_enable3_mask                                         (0x00000100)
#define VI_VBIF0_SCALING2_write_enable3(data)                                        (0x00000100&((data)<<8))
#define VI_VBIF0_SCALING2_write_enable3_src(data)                                    ((0x00000100&(data))>>8)
#define VI_VBIF0_SCALING2_get_write_enable3(data)                                    ((0x00000100&(data))>>8)
#define VI_VBIF0_SCALING2_offset_shift                                               (0)
#define VI_VBIF0_SCALING2_offset_mask                                                (0x000000FF)
#define VI_VBIF0_SCALING2_offset(data)                                               (0x000000FF&((data)<<0))
#define VI_VBIF0_SCALING2_offset_src(data)                                           ((0x000000FF&(data))>>0)
#define VI_VBIF0_SCALING2_get_offset(data)                                           ((0x000000FF&(data))>>0)


#define VI_VBIF1_SCALING2                                                            0x180044dc
#define VI_VBIF1_SCALING2_reg_addr                                                   "0xB80044DC"
#define VI_VBIF1_SCALING2_reg                                                        0xB80044DC
#define VI_VBIF1_SCALING2_inst_adr                                                   "0x0037"
#define VI_VBIF1_SCALING2_inst                                                       0x0037
#define VI_VBIF1_SCALING2_write_enable1_shift                                        (19)
#define VI_VBIF1_SCALING2_write_enable1_mask                                         (0x00080000)
#define VI_VBIF1_SCALING2_write_enable1(data)                                        (0x00080000&((data)<<19))
#define VI_VBIF1_SCALING2_write_enable1_src(data)                                    ((0x00080000&(data))>>19)
#define VI_VBIF1_SCALING2_get_write_enable1(data)                                    ((0x00080000&(data))>>19)
#define VI_VBIF1_SCALING2_scaling_en2_shift                                          (18)
#define VI_VBIF1_SCALING2_scaling_en2_mask                                           (0x00040000)
#define VI_VBIF1_SCALING2_scaling_en2(data)                                          (0x00040000&((data)<<18))
#define VI_VBIF1_SCALING2_scaling_en2_src(data)                                      ((0x00040000&(data))>>18)
#define VI_VBIF1_SCALING2_get_scaling_en2(data)                                      ((0x00040000&(data))>>18)
#define VI_VBIF1_SCALING2_write_enable2_shift                                        (17)
#define VI_VBIF1_SCALING2_write_enable2_mask                                         (0x00020000)
#define VI_VBIF1_SCALING2_write_enable2(data)                                        (0x00020000&((data)<<17))
#define VI_VBIF1_SCALING2_write_enable2_src(data)                                    ((0x00020000&(data))>>17)
#define VI_VBIF1_SCALING2_get_write_enable2(data)                                    ((0x00020000&(data))>>17)
#define VI_VBIF1_SCALING2_gain_shift                                                 (9)
#define VI_VBIF1_SCALING2_gain_mask                                                  (0x0001FE00)
#define VI_VBIF1_SCALING2_gain(data)                                                 (0x0001FE00&((data)<<9))
#define VI_VBIF1_SCALING2_gain_src(data)                                             ((0x0001FE00&(data))>>9)
#define VI_VBIF1_SCALING2_get_gain(data)                                             ((0x0001FE00&(data))>>9)
#define VI_VBIF1_SCALING2_write_enable3_shift                                        (8)
#define VI_VBIF1_SCALING2_write_enable3_mask                                         (0x00000100)
#define VI_VBIF1_SCALING2_write_enable3(data)                                        (0x00000100&((data)<<8))
#define VI_VBIF1_SCALING2_write_enable3_src(data)                                    ((0x00000100&(data))>>8)
#define VI_VBIF1_SCALING2_get_write_enable3(data)                                    ((0x00000100&(data))>>8)
#define VI_VBIF1_SCALING2_offset_shift                                               (0)
#define VI_VBIF1_SCALING2_offset_mask                                                (0x000000FF)
#define VI_VBIF1_SCALING2_offset(data)                                               (0x000000FF&((data)<<0))
#define VI_VBIF1_SCALING2_offset_src(data)                                           ((0x000000FF&(data))>>0)
#define VI_VBIF1_SCALING2_get_offset(data)                                           ((0x000000FF&(data))>>0)


#define VI_YDC1                                                                      0x18004060
#define VI_YDC1_reg_addr                                                             "0xB8004060"
#define VI_YDC1_reg                                                                  0xB8004060
#define VI_YDC1_inst_adr                                                             "0x0018"
#define VI_YDC1_inst                                                                 0x0018
#define VI_YDC1_dc_shift                                                             (0)
#define VI_YDC1_dc_mask                                                              (0x1FFFFFFF)
#define VI_YDC1_dc(data)                                                             (0x1FFFFFFF&((data)<<0))
#define VI_YDC1_dc_src(data)                                                         ((0x1FFFFFFF&(data))>>0)
#define VI_YDC1_get_dc(data)                                                         ((0x1FFFFFFF&(data))>>0)


#define VI_YDC2                                                                      0x18004064
#define VI_YDC2_reg_addr                                                             "0xB8004064"
#define VI_YDC2_reg                                                                  0xB8004064
#define VI_YDC2_inst_adr                                                             "0x0019"
#define VI_YDC2_inst                                                                 0x0019
#define VI_YDC2_dc_shift                                                             (0)
#define VI_YDC2_dc_mask                                                              (0x1FFFFFFF)
#define VI_YDC2_dc(data)                                                             (0x1FFFFFFF&((data)<<0))
#define VI_YDC2_dc_src(data)                                                         ((0x1FFFFFFF&(data))>>0)
#define VI_YDC2_get_dc(data)                                                         ((0x1FFFFFFF&(data))>>0)


#define VI_COCTL1                                                                    0x180042b4
#define VI_COCTL1_reg_addr                                                           "0xB80042B4"
#define VI_COCTL1_reg                                                                0xB80042B4
#define VI_COCTL1_inst_adr                                                           "0x00AD"
#define VI_COCTL1_inst                                                               0x00AD
#define VI_COCTL1_yen_shift                                                          (2)
#define VI_COCTL1_yen_mask                                                           (0x00000004)
#define VI_COCTL1_yen(data)                                                          (0x00000004&((data)<<2))
#define VI_COCTL1_yen_src(data)                                                      ((0x00000004&(data))>>2)
#define VI_COCTL1_get_yen(data)                                                      ((0x00000004&(data))>>2)
#define VI_COCTL1_cen_shift                                                          (1)
#define VI_COCTL1_cen_mask                                                           (0x00000002)
#define VI_COCTL1_cen(data)                                                          (0x00000002&((data)<<1))
#define VI_COCTL1_cen_src(data)                                                      ((0x00000002&(data))>>1)
#define VI_COCTL1_get_cen(data)                                                      ((0x00000002&(data))>>1)
#define VI_COCTL1_write_data_shift                                                   (0)
#define VI_COCTL1_write_data_mask                                                    (0x00000001)
#define VI_COCTL1_write_data(data)                                                   (0x00000001&((data)<<0))
#define VI_COCTL1_write_data_src(data)                                               ((0x00000001&(data))>>0)
#define VI_COCTL1_get_write_data(data)                                               ((0x00000001&(data))>>0)


#define VI_COCTL2                                                                    0x180042b8
#define VI_COCTL2_reg_addr                                                           "0xB80042B8"
#define VI_COCTL2_reg                                                                0xB80042B8
#define VI_COCTL2_inst_adr                                                           "0x00AE"
#define VI_COCTL2_inst                                                               0x00AE
#define VI_COCTL2_yen_shift                                                          (2)
#define VI_COCTL2_yen_mask                                                           (0x00000004)
#define VI_COCTL2_yen(data)                                                          (0x00000004&((data)<<2))
#define VI_COCTL2_yen_src(data)                                                      ((0x00000004&(data))>>2)
#define VI_COCTL2_get_yen(data)                                                      ((0x00000004&(data))>>2)
#define VI_COCTL2_cen_shift                                                          (1)
#define VI_COCTL2_cen_mask                                                           (0x00000002)
#define VI_COCTL2_cen(data)                                                          (0x00000002&((data)<<1))
#define VI_COCTL2_cen_src(data)                                                      ((0x00000002&(data))>>1)
#define VI_COCTL2_get_cen(data)                                                      ((0x00000002&(data))>>1)
#define VI_COCTL2_write_data_shift                                                   (0)
#define VI_COCTL2_write_data_mask                                                    (0x00000001)
#define VI_COCTL2_write_data(data)                                                   (0x00000001&((data)<<0))
#define VI_COCTL2_write_data_src(data)                                               ((0x00000001&(data))>>0)
#define VI_COCTL2_get_write_data(data)                                               ((0x00000001&(data))>>0)


#define VI_YCO1                                                                      0x180042bc
#define VI_YCO1_reg_addr                                                             "0xB80042BC"
#define VI_YCO1_reg                                                                  0xB80042BC
#define VI_YCO1_inst_adr                                                             "0x00AF"
#define VI_YCO1_inst                                                                 0x00AF
#define VI_YCO1_write_enable1_shift                                                  (12)
#define VI_YCO1_write_enable1_mask                                                   (0x00001000)
#define VI_YCO1_write_enable1(data)                                                  (0x00001000&((data)<<12))
#define VI_YCO1_write_enable1_src(data)                                              ((0x00001000&(data))>>12)
#define VI_YCO1_get_write_enable1(data)                                              ((0x00001000&(data))>>12)
#define VI_YCO1_range_shift                                                          (4)
#define VI_YCO1_range_mask                                                           (0x00000FF0)
#define VI_YCO1_range(data)                                                          (0x00000FF0&((data)<<4))
#define VI_YCO1_range_src(data)                                                      ((0x00000FF0&(data))>>4)
#define VI_YCO1_get_range(data)                                                      ((0x00000FF0&(data))>>4)
#define VI_YCO1_write_enable2_shift                                                  (3)
#define VI_YCO1_write_enable2_mask                                                   (0x00000008)
#define VI_YCO1_write_enable2(data)                                                  (0x00000008&((data)<<3))
#define VI_YCO1_write_enable2_src(data)                                              ((0x00000008&(data))>>3)
#define VI_YCO1_get_write_enable2(data)                                              ((0x00000008&(data))>>3)
#define VI_YCO1_conti_shift                                                          (2)
#define VI_YCO1_conti_mask                                                           (0x00000004)
#define VI_YCO1_conti(data)                                                          (0x00000004&((data)<<2))
#define VI_YCO1_conti_src(data)                                                      ((0x00000004&(data))>>2)
#define VI_YCO1_get_conti(data)                                                      ((0x00000004&(data))>>2)
#define VI_YCO1_write_enable3_shift                                                  (1)
#define VI_YCO1_write_enable3_mask                                                   (0x00000002)
#define VI_YCO1_write_enable3(data)                                                  (0x00000002&((data)<<1))
#define VI_YCO1_write_enable3_src(data)                                              ((0x00000002&(data))>>1)
#define VI_YCO1_get_write_enable3(data)                                              ((0x00000002&(data))>>1)
#define VI_YCO1_clamp_shift                                                          (0)
#define VI_YCO1_clamp_mask                                                           (0x00000001)
#define VI_YCO1_clamp(data)                                                          (0x00000001&((data)<<0))
#define VI_YCO1_clamp_src(data)                                                      ((0x00000001&(data))>>0)
#define VI_YCO1_get_clamp(data)                                                      ((0x00000001&(data))>>0)


#define VI_CCO1                                                                      0x180042c0
#define VI_CCO1_reg_addr                                                             "0xB80042C0"
#define VI_CCO1_reg                                                                  0xB80042C0
#define VI_CCO1_inst_adr                                                             "0x00B0"
#define VI_CCO1_inst                                                                 0x00B0
#define VI_CCO1_write_enable1_shift                                                  (12)
#define VI_CCO1_write_enable1_mask                                                   (0x00001000)
#define VI_CCO1_write_enable1(data)                                                  (0x00001000&((data)<<12))
#define VI_CCO1_write_enable1_src(data)                                              ((0x00001000&(data))>>12)
#define VI_CCO1_get_write_enable1(data)                                              ((0x00001000&(data))>>12)
#define VI_CCO1_range_shift                                                          (4)
#define VI_CCO1_range_mask                                                           (0x00000FF0)
#define VI_CCO1_range(data)                                                          (0x00000FF0&((data)<<4))
#define VI_CCO1_range_src(data)                                                      ((0x00000FF0&(data))>>4)
#define VI_CCO1_get_range(data)                                                      ((0x00000FF0&(data))>>4)
#define VI_CCO1_write_enable2_shift                                                  (3)
#define VI_CCO1_write_enable2_mask                                                   (0x00000008)
#define VI_CCO1_write_enable2(data)                                                  (0x00000008&((data)<<3))
#define VI_CCO1_write_enable2_src(data)                                              ((0x00000008&(data))>>3)
#define VI_CCO1_get_write_enable2(data)                                              ((0x00000008&(data))>>3)
#define VI_CCO1_conti_shift                                                          (2)
#define VI_CCO1_conti_mask                                                           (0x00000004)
#define VI_CCO1_conti(data)                                                          (0x00000004&((data)<<2))
#define VI_CCO1_conti_src(data)                                                      ((0x00000004&(data))>>2)
#define VI_CCO1_get_conti(data)                                                      ((0x00000004&(data))>>2)
#define VI_CCO1_write_enable3_shift                                                  (1)
#define VI_CCO1_write_enable3_mask                                                   (0x00000002)
#define VI_CCO1_write_enable3(data)                                                  (0x00000002&((data)<<1))
#define VI_CCO1_write_enable3_src(data)                                              ((0x00000002&(data))>>1)
#define VI_CCO1_get_write_enable3(data)                                              ((0x00000002&(data))>>1)
#define VI_CCO1_clamp_shift                                                          (0)
#define VI_CCO1_clamp_mask                                                           (0x00000001)
#define VI_CCO1_clamp(data)                                                          (0x00000001&((data)<<0))
#define VI_CCO1_clamp_src(data)                                                      ((0x00000001&(data))>>0)
#define VI_CCO1_get_clamp(data)                                                      ((0x00000001&(data))>>0)


#define VI_YCO2                                                                      0x180042c4
#define VI_YCO2_reg_addr                                                             "0xB80042C4"
#define VI_YCO2_reg                                                                  0xB80042C4
#define VI_YCO2_inst_adr                                                             "0x00B1"
#define VI_YCO2_inst                                                                 0x00B1
#define VI_YCO2_write_enable1_shift                                                  (12)
#define VI_YCO2_write_enable1_mask                                                   (0x00001000)
#define VI_YCO2_write_enable1(data)                                                  (0x00001000&((data)<<12))
#define VI_YCO2_write_enable1_src(data)                                              ((0x00001000&(data))>>12)
#define VI_YCO2_get_write_enable1(data)                                              ((0x00001000&(data))>>12)
#define VI_YCO2_range_shift                                                          (4)
#define VI_YCO2_range_mask                                                           (0x00000FF0)
#define VI_YCO2_range(data)                                                          (0x00000FF0&((data)<<4))
#define VI_YCO2_range_src(data)                                                      ((0x00000FF0&(data))>>4)
#define VI_YCO2_get_range(data)                                                      ((0x00000FF0&(data))>>4)
#define VI_YCO2_write_enable2_shift                                                  (3)
#define VI_YCO2_write_enable2_mask                                                   (0x00000008)
#define VI_YCO2_write_enable2(data)                                                  (0x00000008&((data)<<3))
#define VI_YCO2_write_enable2_src(data)                                              ((0x00000008&(data))>>3)
#define VI_YCO2_get_write_enable2(data)                                              ((0x00000008&(data))>>3)
#define VI_YCO2_conti_shift                                                          (2)
#define VI_YCO2_conti_mask                                                           (0x00000004)
#define VI_YCO2_conti(data)                                                          (0x00000004&((data)<<2))
#define VI_YCO2_conti_src(data)                                                      ((0x00000004&(data))>>2)
#define VI_YCO2_get_conti(data)                                                      ((0x00000004&(data))>>2)
#define VI_YCO2_write_enable3_shift                                                  (1)
#define VI_YCO2_write_enable3_mask                                                   (0x00000002)
#define VI_YCO2_write_enable3(data)                                                  (0x00000002&((data)<<1))
#define VI_YCO2_write_enable3_src(data)                                              ((0x00000002&(data))>>1)
#define VI_YCO2_get_write_enable3(data)                                              ((0x00000002&(data))>>1)
#define VI_YCO2_clamp_shift                                                          (0)
#define VI_YCO2_clamp_mask                                                           (0x00000001)
#define VI_YCO2_clamp(data)                                                          (0x00000001&((data)<<0))
#define VI_YCO2_clamp_src(data)                                                      ((0x00000001&(data))>>0)
#define VI_YCO2_get_clamp(data)                                                      ((0x00000001&(data))>>0)


#define VI_CCO2                                                                      0x180042c8
#define VI_CCO2_reg_addr                                                             "0xB80042C8"
#define VI_CCO2_reg                                                                  0xB80042C8
#define VI_CCO2_inst_adr                                                             "0x00B2"
#define VI_CCO2_inst                                                                 0x00B2
#define VI_CCO2_write_enable1_shift                                                  (12)
#define VI_CCO2_write_enable1_mask                                                   (0x00001000)
#define VI_CCO2_write_enable1(data)                                                  (0x00001000&((data)<<12))
#define VI_CCO2_write_enable1_src(data)                                              ((0x00001000&(data))>>12)
#define VI_CCO2_get_write_enable1(data)                                              ((0x00001000&(data))>>12)
#define VI_CCO2_range_shift                                                          (4)
#define VI_CCO2_range_mask                                                           (0x00000FF0)
#define VI_CCO2_range(data)                                                          (0x00000FF0&((data)<<4))
#define VI_CCO2_range_src(data)                                                      ((0x00000FF0&(data))>>4)
#define VI_CCO2_get_range(data)                                                      ((0x00000FF0&(data))>>4)
#define VI_CCO2_write_enable2_shift                                                  (3)
#define VI_CCO2_write_enable2_mask                                                   (0x00000008)
#define VI_CCO2_write_enable2(data)                                                  (0x00000008&((data)<<3))
#define VI_CCO2_write_enable2_src(data)                                              ((0x00000008&(data))>>3)
#define VI_CCO2_get_write_enable2(data)                                              ((0x00000008&(data))>>3)
#define VI_CCO2_conti_shift                                                          (2)
#define VI_CCO2_conti_mask                                                           (0x00000004)
#define VI_CCO2_conti(data)                                                          (0x00000004&((data)<<2))
#define VI_CCO2_conti_src(data)                                                      ((0x00000004&(data))>>2)
#define VI_CCO2_get_conti(data)                                                      ((0x00000004&(data))>>2)
#define VI_CCO2_write_enable3_shift                                                  (1)
#define VI_CCO2_write_enable3_mask                                                   (0x00000002)
#define VI_CCO2_write_enable3(data)                                                  (0x00000002&((data)<<1))
#define VI_CCO2_write_enable3_src(data)                                              ((0x00000002&(data))>>1)
#define VI_CCO2_get_write_enable3(data)                                              ((0x00000002&(data))>>1)
#define VI_CCO2_clamp_shift                                                          (0)
#define VI_CCO2_clamp_mask                                                           (0x00000001)
#define VI_CCO2_clamp(data)                                                          (0x00000001&((data)<<0))
#define VI_CCO2_clamp_src(data)                                                      ((0x00000001&(data))>>0)
#define VI_CCO2_get_clamp(data)                                                      ((0x00000001&(data))>>0)


#define VI_VSCCTL1                                                                   0x180042d4
#define VI_VSCCTL1_reg_addr                                                          "0xB80042D4"
#define VI_VSCCTL1_reg                                                               0xB80042D4
#define VI_VSCCTL1_inst_adr                                                          "0x00B5"
#define VI_VSCCTL1_inst                                                              0x00B5
#define VI_VSCCTL1_up_en_shift                                                       (7)
#define VI_VSCCTL1_up_en_mask                                                        (0x00000080)
#define VI_VSCCTL1_up_en(data)                                                       (0x00000080&((data)<<7))
#define VI_VSCCTL1_up_en_src(data)                                                   ((0x00000080&(data))>>7)
#define VI_VSCCTL1_get_up_en(data)                                                   ((0x00000080&(data))>>7)
#define VI_VSCCTL1_tap_mode_shift                                                    (5)
#define VI_VSCCTL1_tap_mode_mask                                                     (0x00000060)
#define VI_VSCCTL1_tap_mode(data)                                                    (0x00000060&((data)<<5))
#define VI_VSCCTL1_tap_mode_src(data)                                                ((0x00000060&(data))>>5)
#define VI_VSCCTL1_get_tap_mode(data)                                                ((0x00000060&(data))>>5)
#define VI_VSCCTL1_yen_shift                                                         (4)
#define VI_VSCCTL1_yen_mask                                                          (0x00000010)
#define VI_VSCCTL1_yen(data)                                                         (0x00000010&((data)<<4))
#define VI_VSCCTL1_yen_src(data)                                                     ((0x00000010&(data))>>4)
#define VI_VSCCTL1_get_yen(data)                                                     ((0x00000010&(data))>>4)
#define VI_VSCCTL1_yoddtype_shift                                                    (3)
#define VI_VSCCTL1_yoddtype_mask                                                     (0x00000008)
#define VI_VSCCTL1_yoddtype(data)                                                    (0x00000008&((data)<<3))
#define VI_VSCCTL1_yoddtype_src(data)                                                ((0x00000008&(data))>>3)
#define VI_VSCCTL1_get_yoddtype(data)                                                ((0x00000008&(data))>>3)
#define VI_VSCCTL1_cen_shift                                                         (2)
#define VI_VSCCTL1_cen_mask                                                          (0x00000004)
#define VI_VSCCTL1_cen(data)                                                         (0x00000004&((data)<<2))
#define VI_VSCCTL1_cen_src(data)                                                     ((0x00000004&(data))>>2)
#define VI_VSCCTL1_get_cen(data)                                                     ((0x00000004&(data))>>2)
#define VI_VSCCTL1_coddtype_shift                                                    (1)
#define VI_VSCCTL1_coddtype_mask                                                     (0x00000002)
#define VI_VSCCTL1_coddtype(data)                                                    (0x00000002&((data)<<1))
#define VI_VSCCTL1_coddtype_src(data)                                                ((0x00000002&(data))>>1)
#define VI_VSCCTL1_get_coddtype(data)                                                ((0x00000002&(data))>>1)


#define VI_VSCCTL2                                                                   0x180042d8
#define VI_VSCCTL2_reg_addr                                                          "0xB80042D8"
#define VI_VSCCTL2_reg                                                               0xB80042D8
#define VI_VSCCTL2_inst_adr                                                          "0x00B6"
#define VI_VSCCTL2_inst                                                              0x00B6
#define VI_VSCCTL2_up_en_shift                                                       (7)
#define VI_VSCCTL2_up_en_mask                                                        (0x00000080)
#define VI_VSCCTL2_up_en(data)                                                       (0x00000080&((data)<<7))
#define VI_VSCCTL2_up_en_src(data)                                                   ((0x00000080&(data))>>7)
#define VI_VSCCTL2_get_up_en(data)                                                   ((0x00000080&(data))>>7)
#define VI_VSCCTL2_tap_mode_shift                                                    (5)
#define VI_VSCCTL2_tap_mode_mask                                                     (0x00000060)
#define VI_VSCCTL2_tap_mode(data)                                                    (0x00000060&((data)<<5))
#define VI_VSCCTL2_tap_mode_src(data)                                                ((0x00000060&(data))>>5)
#define VI_VSCCTL2_get_tap_mode(data)                                                ((0x00000060&(data))>>5)
#define VI_VSCCTL2_yen_shift                                                         (4)
#define VI_VSCCTL2_yen_mask                                                          (0x00000010)
#define VI_VSCCTL2_yen(data)                                                         (0x00000010&((data)<<4))
#define VI_VSCCTL2_yen_src(data)                                                     ((0x00000010&(data))>>4)
#define VI_VSCCTL2_get_yen(data)                                                     ((0x00000010&(data))>>4)
#define VI_VSCCTL2_yoddtype_shift                                                    (3)
#define VI_VSCCTL2_yoddtype_mask                                                     (0x00000008)
#define VI_VSCCTL2_yoddtype(data)                                                    (0x00000008&((data)<<3))
#define VI_VSCCTL2_yoddtype_src(data)                                                ((0x00000008&(data))>>3)
#define VI_VSCCTL2_get_yoddtype(data)                                                ((0x00000008&(data))>>3)
#define VI_VSCCTL2_cen_shift                                                         (2)
#define VI_VSCCTL2_cen_mask                                                          (0x00000004)
#define VI_VSCCTL2_cen(data)                                                         (0x00000004&((data)<<2))
#define VI_VSCCTL2_cen_src(data)                                                     ((0x00000004&(data))>>2)
#define VI_VSCCTL2_get_cen(data)                                                     ((0x00000004&(data))>>2)
#define VI_VSCCTL2_coddtype_shift                                                    (1)
#define VI_VSCCTL2_coddtype_mask                                                     (0x00000002)
#define VI_VSCCTL2_coddtype(data)                                                    (0x00000002&((data)<<1))
#define VI_VSCCTL2_coddtype_src(data)                                                ((0x00000002&(data))>>1)
#define VI_VSCCTL2_get_coddtype(data)                                                ((0x00000002&(data))>>1)


#define VI_VYSC1                                                                     0x180042dc
#define VI_VYSC1_reg_addr                                                            "0xB80042DC"
#define VI_VYSC1_reg                                                                 0xB80042DC
#define VI_VYSC1_inst_adr                                                            "0x00B7"
#define VI_VYSC1_inst                                                                0x00B7
#define VI_VYSC1_write_enable1_shift                                                 (30)
#define VI_VYSC1_write_enable1_mask                                                  (0x40000000)
#define VI_VYSC1_write_enable1(data)                                                 (0x40000000&((data)<<30))
#define VI_VYSC1_write_enable1_src(data)                                             ((0x40000000&(data))>>30)
#define VI_VYSC1_get_write_enable1(data)                                             ((0x40000000&(data))>>30)
#define VI_VYSC1_yonl_shift                                                          (19)
#define VI_VYSC1_yonl_mask                                                           (0x3FF80000)
#define VI_VYSC1_yonl(data)                                                          (0x3FF80000&((data)<<19))
#define VI_VYSC1_yonl_src(data)                                                      ((0x3FF80000&(data))>>19)
#define VI_VYSC1_get_yonl(data)                                                      ((0x3FF80000&(data))>>19)
#define VI_VYSC1_write_enable2_shift                                                 (18)
#define VI_VYSC1_write_enable2_mask                                                  (0x00040000)
#define VI_VYSC1_write_enable2(data)                                                 (0x00040000&((data)<<18))
#define VI_VYSC1_write_enable2_src(data)                                             ((0x00040000&(data))>>18)
#define VI_VYSC1_get_write_enable2(data)                                             ((0x00040000&(data))>>18)
#define VI_VYSC1_ydphs_shift                                                         (0)
#define VI_VYSC1_ydphs_mask                                                          (0x0003FFFF)
#define VI_VYSC1_ydphs(data)                                                         (0x0003FFFF&((data)<<0))
#define VI_VYSC1_ydphs_src(data)                                                     ((0x0003FFFF&(data))>>0)
#define VI_VYSC1_get_ydphs(data)                                                     ((0x0003FFFF&(data))>>0)


#define VI_VCSC1                                                                     0x180042e0
#define VI_VCSC1_reg_addr                                                            "0xB80042E0"
#define VI_VCSC1_reg                                                                 0xB80042E0
#define VI_VCSC1_inst_adr                                                            "0x00B8"
#define VI_VCSC1_inst                                                                0x00B8
#define VI_VCSC1_write_enable1_shift                                                 (30)
#define VI_VCSC1_write_enable1_mask                                                  (0x40000000)
#define VI_VCSC1_write_enable1(data)                                                 (0x40000000&((data)<<30))
#define VI_VCSC1_write_enable1_src(data)                                             ((0x40000000&(data))>>30)
#define VI_VCSC1_get_write_enable1(data)                                             ((0x40000000&(data))>>30)
#define VI_VCSC1_conl_shift                                                          (19)
#define VI_VCSC1_conl_mask                                                           (0x3FF80000)
#define VI_VCSC1_conl(data)                                                          (0x3FF80000&((data)<<19))
#define VI_VCSC1_conl_src(data)                                                      ((0x3FF80000&(data))>>19)
#define VI_VCSC1_get_conl(data)                                                      ((0x3FF80000&(data))>>19)
#define VI_VCSC1_write_enable2_shift                                                 (18)
#define VI_VCSC1_write_enable2_mask                                                  (0x00040000)
#define VI_VCSC1_write_enable2(data)                                                 (0x00040000&((data)<<18))
#define VI_VCSC1_write_enable2_src(data)                                             ((0x00040000&(data))>>18)
#define VI_VCSC1_get_write_enable2(data)                                             ((0x00040000&(data))>>18)
#define VI_VCSC1_cdphs_shift                                                         (0)
#define VI_VCSC1_cdphs_mask                                                          (0x0003FFFF)
#define VI_VCSC1_cdphs(data)                                                         (0x0003FFFF&((data)<<0))
#define VI_VCSC1_cdphs_src(data)                                                     ((0x0003FFFF&(data))>>0)
#define VI_VCSC1_get_cdphs(data)                                                     ((0x0003FFFF&(data))>>0)


#define VI_VYSC2                                                                     0x180042e4
#define VI_VYSC2_reg_addr                                                            "0xB80042E4"
#define VI_VYSC2_reg                                                                 0xB80042E4
#define VI_VYSC2_inst_adr                                                            "0x00B9"
#define VI_VYSC2_inst                                                                0x00B9
#define VI_VYSC2_write_enable1_shift                                                 (30)
#define VI_VYSC2_write_enable1_mask                                                  (0x40000000)
#define VI_VYSC2_write_enable1(data)                                                 (0x40000000&((data)<<30))
#define VI_VYSC2_write_enable1_src(data)                                             ((0x40000000&(data))>>30)
#define VI_VYSC2_get_write_enable1(data)                                             ((0x40000000&(data))>>30)
#define VI_VYSC2_yonl_shift                                                          (19)
#define VI_VYSC2_yonl_mask                                                           (0x3FF80000)
#define VI_VYSC2_yonl(data)                                                          (0x3FF80000&((data)<<19))
#define VI_VYSC2_yonl_src(data)                                                      ((0x3FF80000&(data))>>19)
#define VI_VYSC2_get_yonl(data)                                                      ((0x3FF80000&(data))>>19)
#define VI_VYSC2_write_enable2_shift                                                 (18)
#define VI_VYSC2_write_enable2_mask                                                  (0x00040000)
#define VI_VYSC2_write_enable2(data)                                                 (0x00040000&((data)<<18))
#define VI_VYSC2_write_enable2_src(data)                                             ((0x00040000&(data))>>18)
#define VI_VYSC2_get_write_enable2(data)                                             ((0x00040000&(data))>>18)
#define VI_VYSC2_ydphs_shift                                                         (0)
#define VI_VYSC2_ydphs_mask                                                          (0x0003FFFF)
#define VI_VYSC2_ydphs(data)                                                         (0x0003FFFF&((data)<<0))
#define VI_VYSC2_ydphs_src(data)                                                     ((0x0003FFFF&(data))>>0)
#define VI_VYSC2_get_ydphs(data)                                                     ((0x0003FFFF&(data))>>0)


#define VI_VCSC2                                                                     0x180042e8
#define VI_VCSC2_reg_addr                                                            "0xB80042E8"
#define VI_VCSC2_reg                                                                 0xB80042E8
#define VI_VCSC2_inst_adr                                                            "0x00BA"
#define VI_VCSC2_inst                                                                0x00BA
#define VI_VCSC2_write_enable1_shift                                                 (30)
#define VI_VCSC2_write_enable1_mask                                                  (0x40000000)
#define VI_VCSC2_write_enable1(data)                                                 (0x40000000&((data)<<30))
#define VI_VCSC2_write_enable1_src(data)                                             ((0x40000000&(data))>>30)
#define VI_VCSC2_get_write_enable1(data)                                             ((0x40000000&(data))>>30)
#define VI_VCSC2_conl_shift                                                          (19)
#define VI_VCSC2_conl_mask                                                           (0x3FF80000)
#define VI_VCSC2_conl(data)                                                          (0x3FF80000&((data)<<19))
#define VI_VCSC2_conl_src(data)                                                      ((0x3FF80000&(data))>>19)
#define VI_VCSC2_get_conl(data)                                                      ((0x3FF80000&(data))>>19)
#define VI_VCSC2_write_enable2_shift                                                 (18)
#define VI_VCSC2_write_enable2_mask                                                  (0x00040000)
#define VI_VCSC2_write_enable2(data)                                                 (0x00040000&((data)<<18))
#define VI_VCSC2_write_enable2_src(data)                                             ((0x00040000&(data))>>18)
#define VI_VCSC2_get_write_enable2(data)                                             ((0x00040000&(data))>>18)
#define VI_VCSC2_cdphs_shift                                                         (0)
#define VI_VCSC2_cdphs_mask                                                          (0x0003FFFF)
#define VI_VCSC2_cdphs(data)                                                         (0x0003FFFF&((data)<<0))
#define VI_VCSC2_cdphs_src(data)                                                     ((0x0003FFFF&(data))>>0)
#define VI_VCSC2_get_cdphs(data)                                                     ((0x0003FFFF&(data))>>0)


#define VI_VYIPOS1                                                                   0x180042ec
#define VI_VYIPOS1_reg_addr                                                          "0xB80042EC"
#define VI_VYIPOS1_reg                                                               0xB80042EC
#define VI_VYIPOS1_inst_adr                                                          "0x00BB"
#define VI_VYIPOS1_inst                                                              0x00BB
#define VI_VYIPOS1_init_offset_shift                                                 (14)
#define VI_VYIPOS1_init_offset_mask                                                  (0x01FFC000)
#define VI_VYIPOS1_init_offset(data)                                                 (0x01FFC000&((data)<<14))
#define VI_VYIPOS1_init_offset_src(data)                                             ((0x01FFC000&(data))>>14)
#define VI_VYIPOS1_get_init_offset(data)                                             ((0x01FFC000&(data))>>14)
#define VI_VYIPOS1_init_phase_shift                                                  (0)
#define VI_VYIPOS1_init_phase_mask                                                   (0x00003FFF)
#define VI_VYIPOS1_init_phase(data)                                                  (0x00003FFF&((data)<<0))
#define VI_VYIPOS1_init_phase_src(data)                                              ((0x00003FFF&(data))>>0)
#define VI_VYIPOS1_get_init_phase(data)                                              ((0x00003FFF&(data))>>0)


#define VI_VYIPOS2                                                                   0x180042f0
#define VI_VYIPOS2_reg_addr                                                          "0xB80042F0"
#define VI_VYIPOS2_reg                                                               0xB80042F0
#define VI_VYIPOS2_inst_adr                                                          "0x00BC"
#define VI_VYIPOS2_inst                                                              0x00BC
#define VI_VYIPOS2_init_offset_shift                                                 (14)
#define VI_VYIPOS2_init_offset_mask                                                  (0x01FFC000)
#define VI_VYIPOS2_init_offset(data)                                                 (0x01FFC000&((data)<<14))
#define VI_VYIPOS2_init_offset_src(data)                                             ((0x01FFC000&(data))>>14)
#define VI_VYIPOS2_get_init_offset(data)                                             ((0x01FFC000&(data))>>14)
#define VI_VYIPOS2_init_phase_shift                                                  (0)
#define VI_VYIPOS2_init_phase_mask                                                   (0x00003FFF)
#define VI_VYIPOS2_init_phase(data)                                                  (0x00003FFF&((data)<<0))
#define VI_VYIPOS2_init_phase_src(data)                                              ((0x00003FFF&(data))>>0)
#define VI_VYIPOS2_get_init_phase(data)                                              ((0x00003FFF&(data))>>0)


#define VI_VCIPOS1                                                                   0x180042f4
#define VI_VCIPOS1_reg_addr                                                          "0xB80042F4"
#define VI_VCIPOS1_reg                                                               0xB80042F4
#define VI_VCIPOS1_inst_adr                                                          "0x00BD"
#define VI_VCIPOS1_inst                                                              0x00BD
#define VI_VCIPOS1_init_offset_shift                                                 (14)
#define VI_VCIPOS1_init_offset_mask                                                  (0x01FFC000)
#define VI_VCIPOS1_init_offset(data)                                                 (0x01FFC000&((data)<<14))
#define VI_VCIPOS1_init_offset_src(data)                                             ((0x01FFC000&(data))>>14)
#define VI_VCIPOS1_get_init_offset(data)                                             ((0x01FFC000&(data))>>14)
#define VI_VCIPOS1_init_phase_shift                                                  (0)
#define VI_VCIPOS1_init_phase_mask                                                   (0x00003FFF)
#define VI_VCIPOS1_init_phase(data)                                                  (0x00003FFF&((data)<<0))
#define VI_VCIPOS1_init_phase_src(data)                                              ((0x00003FFF&(data))>>0)
#define VI_VCIPOS1_get_init_phase(data)                                              ((0x00003FFF&(data))>>0)


#define VI_VCIPOS2                                                                   0x180042f8
#define VI_VCIPOS2_reg_addr                                                          "0xB80042F8"
#define VI_VCIPOS2_reg                                                               0xB80042F8
#define VI_VCIPOS2_inst_adr                                                          "0x00BE"
#define VI_VCIPOS2_inst                                                              0x00BE
#define VI_VCIPOS2_init_offset_shift                                                 (14)
#define VI_VCIPOS2_init_offset_mask                                                  (0x01FFC000)
#define VI_VCIPOS2_init_offset(data)                                                 (0x01FFC000&((data)<<14))
#define VI_VCIPOS2_init_offset_src(data)                                             ((0x01FFC000&(data))>>14)
#define VI_VCIPOS2_get_init_offset(data)                                             ((0x01FFC000&(data))>>14)
#define VI_VCIPOS2_init_phase_shift                                                  (0)
#define VI_VCIPOS2_init_phase_mask                                                   (0x00003FFF)
#define VI_VCIPOS2_init_phase(data)                                                  (0x00003FFF&((data)<<0))
#define VI_VCIPOS2_init_phase_src(data)                                              ((0x00003FFF&(data))>>0)
#define VI_VCIPOS2_get_init_phase(data)                                              ((0x00003FFF&(data))>>0)


#define VI_VYSCCOEF1_0                                                               0x180042FC
#define VI_VYSCCOEF1_1                                                               0x18004300
#define VI_VYSCCOEF1_2                                                               0x18004304
#define VI_VYSCCOEF1_3                                                               0x18004308
#define VI_VYSCCOEF1_4                                                               0x1800430C
#define VI_VYSCCOEF1_5                                                               0x18004310
#define VI_VYSCCOEF1_6                                                               0x18004314
#define VI_VYSCCOEF1_7                                                               0x18004318
#define VI_VYSCCOEF1_8                                                               0x1800431C
#define VI_VYSCCOEF1_9                                                               0x18004320
#define VI_VYSCCOEF1_10                                                               0x18004324
#define VI_VYSCCOEF1_11                                                               0x18004328
#define VI_VYSCCOEF1_12                                                               0x1800432C
#define VI_VYSCCOEF1_13                                                               0x18004330
#define VI_VYSCCOEF1_14                                                               0x18004334
#define VI_VYSCCOEF1_15                                                               0x18004338
#define VI_VYSCCOEF1_16                                                               0x1800433C
#define VI_VYSCCOEF1_17                                                               0x18004340
#define VI_VYSCCOEF1_18                                                               0x18004344
#define VI_VYSCCOEF1_19                                                               0x18004348
#define VI_VYSCCOEF1_0_reg_addr                                                      "0xB80042FC"
#define VI_VYSCCOEF1_1_reg_addr                                                      "0xB8004300"
#define VI_VYSCCOEF1_2_reg_addr                                                      "0xB8004304"
#define VI_VYSCCOEF1_3_reg_addr                                                      "0xB8004308"
#define VI_VYSCCOEF1_4_reg_addr                                                      "0xB800430C"
#define VI_VYSCCOEF1_5_reg_addr                                                      "0xB8004310"
#define VI_VYSCCOEF1_6_reg_addr                                                      "0xB8004314"
#define VI_VYSCCOEF1_7_reg_addr                                                      "0xB8004318"
#define VI_VYSCCOEF1_8_reg_addr                                                      "0xB800431C"
#define VI_VYSCCOEF1_9_reg_addr                                                      "0xB8004320"
#define VI_VYSCCOEF1_10_reg_addr                                                      "0xB8004324"
#define VI_VYSCCOEF1_11_reg_addr                                                      "0xB8004328"
#define VI_VYSCCOEF1_12_reg_addr                                                      "0xB800432C"
#define VI_VYSCCOEF1_13_reg_addr                                                      "0xB8004330"
#define VI_VYSCCOEF1_14_reg_addr                                                      "0xB8004334"
#define VI_VYSCCOEF1_15_reg_addr                                                      "0xB8004338"
#define VI_VYSCCOEF1_16_reg_addr                                                      "0xB800433C"
#define VI_VYSCCOEF1_17_reg_addr                                                      "0xB8004340"
#define VI_VYSCCOEF1_18_reg_addr                                                      "0xB8004344"
#define VI_VYSCCOEF1_19_reg_addr                                                      "0xB8004348"
#define VI_VYSCCOEF1_0_reg                                                           0xB80042FC
#define VI_VYSCCOEF1_1_reg                                                           0xB8004300
#define VI_VYSCCOEF1_2_reg                                                           0xB8004304
#define VI_VYSCCOEF1_3_reg                                                           0xB8004308
#define VI_VYSCCOEF1_4_reg                                                           0xB800430C
#define VI_VYSCCOEF1_5_reg                                                           0xB8004310
#define VI_VYSCCOEF1_6_reg                                                           0xB8004314
#define VI_VYSCCOEF1_7_reg                                                           0xB8004318
#define VI_VYSCCOEF1_8_reg                                                           0xB800431C
#define VI_VYSCCOEF1_9_reg                                                           0xB8004320
#define VI_VYSCCOEF1_10_reg                                                           0xB8004324
#define VI_VYSCCOEF1_11_reg                                                           0xB8004328
#define VI_VYSCCOEF1_12_reg                                                           0xB800432C
#define VI_VYSCCOEF1_13_reg                                                           0xB8004330
#define VI_VYSCCOEF1_14_reg                                                           0xB8004334
#define VI_VYSCCOEF1_15_reg                                                           0xB8004338
#define VI_VYSCCOEF1_16_reg                                                           0xB800433C
#define VI_VYSCCOEF1_17_reg                                                           0xB8004340
#define VI_VYSCCOEF1_18_reg                                                           0xB8004344
#define VI_VYSCCOEF1_19_reg                                                           0xB8004348
#define VI_VYSCCOEF1_0_inst_adr                                                      "0x00BF"
#define VI_VYSCCOEF1_1_inst_adr                                                      "0x00C0"
#define VI_VYSCCOEF1_2_inst_adr                                                      "0x00C1"
#define VI_VYSCCOEF1_3_inst_adr                                                      "0x00C2"
#define VI_VYSCCOEF1_4_inst_adr                                                      "0x00C3"
#define VI_VYSCCOEF1_5_inst_adr                                                      "0x00C4"
#define VI_VYSCCOEF1_6_inst_adr                                                      "0x00C5"
#define VI_VYSCCOEF1_7_inst_adr                                                      "0x00C6"
#define VI_VYSCCOEF1_8_inst_adr                                                      "0x00C7"
#define VI_VYSCCOEF1_9_inst_adr                                                      "0x00C8"
#define VI_VYSCCOEF1_10_inst_adr                                                      "0x00C9"
#define VI_VYSCCOEF1_11_inst_adr                                                      "0x00CA"
#define VI_VYSCCOEF1_12_inst_adr                                                      "0x00CB"
#define VI_VYSCCOEF1_13_inst_adr                                                      "0x00CC"
#define VI_VYSCCOEF1_14_inst_adr                                                      "0x00CD"
#define VI_VYSCCOEF1_15_inst_adr                                                      "0x00CE"
#define VI_VYSCCOEF1_16_inst_adr                                                      "0x00CF"
#define VI_VYSCCOEF1_17_inst_adr                                                      "0x00D0"
#define VI_VYSCCOEF1_18_inst_adr                                                      "0x00D1"
#define VI_VYSCCOEF1_19_inst_adr                                                      "0x00D2"
#define VI_VYSCCOEF1_0_inst                                                          0x00BF
#define VI_VYSCCOEF1_1_inst                                                          0x00C0
#define VI_VYSCCOEF1_2_inst                                                          0x00C1
#define VI_VYSCCOEF1_3_inst                                                          0x00C2
#define VI_VYSCCOEF1_4_inst                                                          0x00C3
#define VI_VYSCCOEF1_5_inst                                                          0x00C4
#define VI_VYSCCOEF1_6_inst                                                          0x00C5
#define VI_VYSCCOEF1_7_inst                                                          0x00C6
#define VI_VYSCCOEF1_8_inst                                                          0x00C7
#define VI_VYSCCOEF1_9_inst                                                          0x00C8
#define VI_VYSCCOEF1_10_inst                                                          0x00C9
#define VI_VYSCCOEF1_11_inst                                                          0x00CA
#define VI_VYSCCOEF1_12_inst                                                          0x00CB
#define VI_VYSCCOEF1_13_inst                                                          0x00CC
#define VI_VYSCCOEF1_14_inst                                                          0x00CD
#define VI_VYSCCOEF1_15_inst                                                          0x00CE
#define VI_VYSCCOEF1_16_inst                                                          0x00CF
#define VI_VYSCCOEF1_17_inst                                                          0x00D0
#define VI_VYSCCOEF1_18_inst                                                          0x00D1
#define VI_VYSCCOEF1_19_inst                                                          0x00D2
#define VI_VYSCCOEF1_ysccoef_shift                                                   (0)
#define VI_VYSCCOEF1_ysccoef_mask                                                    (0x00003FFF)
#define VI_VYSCCOEF1_ysccoef(data)                                                   (0x00003FFF&((data)<<0))
#define VI_VYSCCOEF1_ysccoef_src(data)                                               ((0x00003FFF&(data))>>0)
#define VI_VYSCCOEF1_get_ysccoef(data)                                               ((0x00003FFF&(data))>>0)


#define VI_VYSCCOEF2_0                                                               0x1800434C
#define VI_VYSCCOEF2_1                                                               0x18004350
#define VI_VYSCCOEF2_2                                                               0x18004354
#define VI_VYSCCOEF2_3                                                               0x18004358
#define VI_VYSCCOEF2_4                                                               0x1800435C
#define VI_VYSCCOEF2_5                                                               0x18004360
#define VI_VYSCCOEF2_6                                                               0x18004364
#define VI_VYSCCOEF2_7                                                               0x18004368
#define VI_VYSCCOEF2_8                                                               0x1800436C
#define VI_VYSCCOEF2_9                                                               0x18004370
#define VI_VYSCCOEF2_10                                                               0x18004374
#define VI_VYSCCOEF2_11                                                               0x18004378
#define VI_VYSCCOEF2_12                                                               0x1800437C
#define VI_VYSCCOEF2_13                                                               0x18004380
#define VI_VYSCCOEF2_14                                                               0x18004384
#define VI_VYSCCOEF2_15                                                               0x18004388
#define VI_VYSCCOEF2_16                                                               0x1800438C
#define VI_VYSCCOEF2_17                                                               0x18004390
#define VI_VYSCCOEF2_18                                                               0x18004394
#define VI_VYSCCOEF2_19                                                               0x18004398
#define VI_VYSCCOEF2_0_reg_addr                                                      "0xB800434C"
#define VI_VYSCCOEF2_1_reg_addr                                                      "0xB8004350"
#define VI_VYSCCOEF2_2_reg_addr                                                      "0xB8004354"
#define VI_VYSCCOEF2_3_reg_addr                                                      "0xB8004358"
#define VI_VYSCCOEF2_4_reg_addr                                                      "0xB800435C"
#define VI_VYSCCOEF2_5_reg_addr                                                      "0xB8004360"
#define VI_VYSCCOEF2_6_reg_addr                                                      "0xB8004364"
#define VI_VYSCCOEF2_7_reg_addr                                                      "0xB8004368"
#define VI_VYSCCOEF2_8_reg_addr                                                      "0xB800436C"
#define VI_VYSCCOEF2_9_reg_addr                                                      "0xB8004370"
#define VI_VYSCCOEF2_10_reg_addr                                                      "0xB8004374"
#define VI_VYSCCOEF2_11_reg_addr                                                      "0xB8004378"
#define VI_VYSCCOEF2_12_reg_addr                                                      "0xB800437C"
#define VI_VYSCCOEF2_13_reg_addr                                                      "0xB8004380"
#define VI_VYSCCOEF2_14_reg_addr                                                      "0xB8004384"
#define VI_VYSCCOEF2_15_reg_addr                                                      "0xB8004388"
#define VI_VYSCCOEF2_16_reg_addr                                                      "0xB800438C"
#define VI_VYSCCOEF2_17_reg_addr                                                      "0xB8004390"
#define VI_VYSCCOEF2_18_reg_addr                                                      "0xB8004394"
#define VI_VYSCCOEF2_19_reg_addr                                                      "0xB8004398"
#define VI_VYSCCOEF2_0_reg                                                           0xB800434C
#define VI_VYSCCOEF2_1_reg                                                           0xB8004350
#define VI_VYSCCOEF2_2_reg                                                           0xB8004354
#define VI_VYSCCOEF2_3_reg                                                           0xB8004358
#define VI_VYSCCOEF2_4_reg                                                           0xB800435C
#define VI_VYSCCOEF2_5_reg                                                           0xB8004360
#define VI_VYSCCOEF2_6_reg                                                           0xB8004364
#define VI_VYSCCOEF2_7_reg                                                           0xB8004368
#define VI_VYSCCOEF2_8_reg                                                           0xB800436C
#define VI_VYSCCOEF2_9_reg                                                           0xB8004370
#define VI_VYSCCOEF2_10_reg                                                           0xB8004374
#define VI_VYSCCOEF2_11_reg                                                           0xB8004378
#define VI_VYSCCOEF2_12_reg                                                           0xB800437C
#define VI_VYSCCOEF2_13_reg                                                           0xB8004380
#define VI_VYSCCOEF2_14_reg                                                           0xB8004384
#define VI_VYSCCOEF2_15_reg                                                           0xB8004388
#define VI_VYSCCOEF2_16_reg                                                           0xB800438C
#define VI_VYSCCOEF2_17_reg                                                           0xB8004390
#define VI_VYSCCOEF2_18_reg                                                           0xB8004394
#define VI_VYSCCOEF2_19_reg                                                           0xB8004398
#define VI_VYSCCOEF2_0_inst_adr                                                      "0x00D3"
#define VI_VYSCCOEF2_1_inst_adr                                                      "0x00D4"
#define VI_VYSCCOEF2_2_inst_adr                                                      "0x00D5"
#define VI_VYSCCOEF2_3_inst_adr                                                      "0x00D6"
#define VI_VYSCCOEF2_4_inst_adr                                                      "0x00D7"
#define VI_VYSCCOEF2_5_inst_adr                                                      "0x00D8"
#define VI_VYSCCOEF2_6_inst_adr                                                      "0x00D9"
#define VI_VYSCCOEF2_7_inst_adr                                                      "0x00DA"
#define VI_VYSCCOEF2_8_inst_adr                                                      "0x00DB"
#define VI_VYSCCOEF2_9_inst_adr                                                      "0x00DC"
#define VI_VYSCCOEF2_10_inst_adr                                                      "0x00DD"
#define VI_VYSCCOEF2_11_inst_adr                                                      "0x00DE"
#define VI_VYSCCOEF2_12_inst_adr                                                      "0x00DF"
#define VI_VYSCCOEF2_13_inst_adr                                                      "0x00E0"
#define VI_VYSCCOEF2_14_inst_adr                                                      "0x00E1"
#define VI_VYSCCOEF2_15_inst_adr                                                      "0x00E2"
#define VI_VYSCCOEF2_16_inst_adr                                                      "0x00E3"
#define VI_VYSCCOEF2_17_inst_adr                                                      "0x00E4"
#define VI_VYSCCOEF2_18_inst_adr                                                      "0x00E5"
#define VI_VYSCCOEF2_19_inst_adr                                                      "0x00E6"
#define VI_VYSCCOEF2_0_inst                                                          0x00D3
#define VI_VYSCCOEF2_1_inst                                                          0x00D4
#define VI_VYSCCOEF2_2_inst                                                          0x00D5
#define VI_VYSCCOEF2_3_inst                                                          0x00D6
#define VI_VYSCCOEF2_4_inst                                                          0x00D7
#define VI_VYSCCOEF2_5_inst                                                          0x00D8
#define VI_VYSCCOEF2_6_inst                                                          0x00D9
#define VI_VYSCCOEF2_7_inst                                                          0x00DA
#define VI_VYSCCOEF2_8_inst                                                          0x00DB
#define VI_VYSCCOEF2_9_inst                                                          0x00DC
#define VI_VYSCCOEF2_10_inst                                                          0x00DD
#define VI_VYSCCOEF2_11_inst                                                          0x00DE
#define VI_VYSCCOEF2_12_inst                                                          0x00DF
#define VI_VYSCCOEF2_13_inst                                                          0x00E0
#define VI_VYSCCOEF2_14_inst                                                          0x00E1
#define VI_VYSCCOEF2_15_inst                                                          0x00E2
#define VI_VYSCCOEF2_16_inst                                                          0x00E3
#define VI_VYSCCOEF2_17_inst                                                          0x00E4
#define VI_VYSCCOEF2_18_inst                                                          0x00E5
#define VI_VYSCCOEF2_19_inst                                                          0x00E6
#define VI_VYSCCOEF2_ysccoef_shift                                                   (0)
#define VI_VYSCCOEF2_ysccoef_mask                                                    (0x00003FFF)
#define VI_VYSCCOEF2_ysccoef(data)                                                   (0x00003FFF&((data)<<0))
#define VI_VYSCCOEF2_ysccoef_src(data)                                               ((0x00003FFF&(data))>>0)
#define VI_VYSCCOEF2_get_ysccoef(data)                                               ((0x00003FFF&(data))>>0)


#define VI_VCSCCOEF1_0                                                               0x1800439C
#define VI_VCSCCOEF1_1                                                               0x180043A0
#define VI_VCSCCOEF1_2                                                               0x180043A4
#define VI_VCSCCOEF1_3                                                               0x180043A8
#define VI_VCSCCOEF1_4                                                               0x180043AC
#define VI_VCSCCOEF1_5                                                               0x180043B0
#define VI_VCSCCOEF1_6                                                               0x180043B4
#define VI_VCSCCOEF1_7                                                               0x180043B8
#define VI_VCSCCOEF1_8                                                               0x180043BC
#define VI_VCSCCOEF1_9                                                               0x180043C0
#define VI_VCSCCOEF1_10                                                               0x180043C4
#define VI_VCSCCOEF1_11                                                               0x180043C8
#define VI_VCSCCOEF1_12                                                               0x180043CC
#define VI_VCSCCOEF1_13                                                               0x180043D0
#define VI_VCSCCOEF1_14                                                               0x180043D4
#define VI_VCSCCOEF1_15                                                               0x180043D8
#define VI_VCSCCOEF1_16                                                               0x180043DC
#define VI_VCSCCOEF1_17                                                               0x180043E0
#define VI_VCSCCOEF1_18                                                               0x180043E4
#define VI_VCSCCOEF1_19                                                               0x180043E8
#define VI_VCSCCOEF1_0_reg_addr                                                      "0xB800439C"
#define VI_VCSCCOEF1_1_reg_addr                                                      "0xB80043A0"
#define VI_VCSCCOEF1_2_reg_addr                                                      "0xB80043A4"
#define VI_VCSCCOEF1_3_reg_addr                                                      "0xB80043A8"
#define VI_VCSCCOEF1_4_reg_addr                                                      "0xB80043AC"
#define VI_VCSCCOEF1_5_reg_addr                                                      "0xB80043B0"
#define VI_VCSCCOEF1_6_reg_addr                                                      "0xB80043B4"
#define VI_VCSCCOEF1_7_reg_addr                                                      "0xB80043B8"
#define VI_VCSCCOEF1_8_reg_addr                                                      "0xB80043BC"
#define VI_VCSCCOEF1_9_reg_addr                                                      "0xB80043C0"
#define VI_VCSCCOEF1_10_reg_addr                                                      "0xB80043C4"
#define VI_VCSCCOEF1_11_reg_addr                                                      "0xB80043C8"
#define VI_VCSCCOEF1_12_reg_addr                                                      "0xB80043CC"
#define VI_VCSCCOEF1_13_reg_addr                                                      "0xB80043D0"
#define VI_VCSCCOEF1_14_reg_addr                                                      "0xB80043D4"
#define VI_VCSCCOEF1_15_reg_addr                                                      "0xB80043D8"
#define VI_VCSCCOEF1_16_reg_addr                                                      "0xB80043DC"
#define VI_VCSCCOEF1_17_reg_addr                                                      "0xB80043E0"
#define VI_VCSCCOEF1_18_reg_addr                                                      "0xB80043E4"
#define VI_VCSCCOEF1_19_reg_addr                                                      "0xB80043E8"
#define VI_VCSCCOEF1_0_reg                                                           0xB800439C
#define VI_VCSCCOEF1_1_reg                                                           0xB80043A0
#define VI_VCSCCOEF1_2_reg                                                           0xB80043A4
#define VI_VCSCCOEF1_3_reg                                                           0xB80043A8
#define VI_VCSCCOEF1_4_reg                                                           0xB80043AC
#define VI_VCSCCOEF1_5_reg                                                           0xB80043B0
#define VI_VCSCCOEF1_6_reg                                                           0xB80043B4
#define VI_VCSCCOEF1_7_reg                                                           0xB80043B8
#define VI_VCSCCOEF1_8_reg                                                           0xB80043BC
#define VI_VCSCCOEF1_9_reg                                                           0xB80043C0
#define VI_VCSCCOEF1_10_reg                                                           0xB80043C4
#define VI_VCSCCOEF1_11_reg                                                           0xB80043C8
#define VI_VCSCCOEF1_12_reg                                                           0xB80043CC
#define VI_VCSCCOEF1_13_reg                                                           0xB80043D0
#define VI_VCSCCOEF1_14_reg                                                           0xB80043D4
#define VI_VCSCCOEF1_15_reg                                                           0xB80043D8
#define VI_VCSCCOEF1_16_reg                                                           0xB80043DC
#define VI_VCSCCOEF1_17_reg                                                           0xB80043E0
#define VI_VCSCCOEF1_18_reg                                                           0xB80043E4
#define VI_VCSCCOEF1_19_reg                                                           0xB80043E8
#define VI_VCSCCOEF1_0_inst_adr                                                      "0x00E7"
#define VI_VCSCCOEF1_1_inst_adr                                                      "0x00E8"
#define VI_VCSCCOEF1_2_inst_adr                                                      "0x00E9"
#define VI_VCSCCOEF1_3_inst_adr                                                      "0x00EA"
#define VI_VCSCCOEF1_4_inst_adr                                                      "0x00EB"
#define VI_VCSCCOEF1_5_inst_adr                                                      "0x00EC"
#define VI_VCSCCOEF1_6_inst_adr                                                      "0x00ED"
#define VI_VCSCCOEF1_7_inst_adr                                                      "0x00EE"
#define VI_VCSCCOEF1_8_inst_adr                                                      "0x00EF"
#define VI_VCSCCOEF1_9_inst_adr                                                      "0x00F0"
#define VI_VCSCCOEF1_10_inst_adr                                                      "0x00F1"
#define VI_VCSCCOEF1_11_inst_adr                                                      "0x00F2"
#define VI_VCSCCOEF1_12_inst_adr                                                      "0x00F3"
#define VI_VCSCCOEF1_13_inst_adr                                                      "0x00F4"
#define VI_VCSCCOEF1_14_inst_adr                                                      "0x00F5"
#define VI_VCSCCOEF1_15_inst_adr                                                      "0x00F6"
#define VI_VCSCCOEF1_16_inst_adr                                                      "0x00F7"
#define VI_VCSCCOEF1_17_inst_adr                                                      "0x00F8"
#define VI_VCSCCOEF1_18_inst_adr                                                      "0x00F9"
#define VI_VCSCCOEF1_19_inst_adr                                                      "0x00FA"
#define VI_VCSCCOEF1_0_inst                                                          0x00E7
#define VI_VCSCCOEF1_1_inst                                                          0x00E8
#define VI_VCSCCOEF1_2_inst                                                          0x00E9
#define VI_VCSCCOEF1_3_inst                                                          0x00EA
#define VI_VCSCCOEF1_4_inst                                                          0x00EB
#define VI_VCSCCOEF1_5_inst                                                          0x00EC
#define VI_VCSCCOEF1_6_inst                                                          0x00ED
#define VI_VCSCCOEF1_7_inst                                                          0x00EE
#define VI_VCSCCOEF1_8_inst                                                          0x00EF
#define VI_VCSCCOEF1_9_inst                                                          0x00F0
#define VI_VCSCCOEF1_10_inst                                                          0x00F1
#define VI_VCSCCOEF1_11_inst                                                          0x00F2
#define VI_VCSCCOEF1_12_inst                                                          0x00F3
#define VI_VCSCCOEF1_13_inst                                                          0x00F4
#define VI_VCSCCOEF1_14_inst                                                          0x00F5
#define VI_VCSCCOEF1_15_inst                                                          0x00F6
#define VI_VCSCCOEF1_16_inst                                                          0x00F7
#define VI_VCSCCOEF1_17_inst                                                          0x00F8
#define VI_VCSCCOEF1_18_inst                                                          0x00F9
#define VI_VCSCCOEF1_19_inst                                                          0x00FA
#define VI_VCSCCOEF1_csccoef_shift                                                   (0)
#define VI_VCSCCOEF1_csccoef_mask                                                    (0x00003FFF)
#define VI_VCSCCOEF1_csccoef(data)                                                   (0x00003FFF&((data)<<0))
#define VI_VCSCCOEF1_csccoef_src(data)                                               ((0x00003FFF&(data))>>0)
#define VI_VCSCCOEF1_get_csccoef(data)                                               ((0x00003FFF&(data))>>0)


#define VI_VCSCCOEF2_0                                                               0x180043EC
#define VI_VCSCCOEF2_1                                                               0x180043F0
#define VI_VCSCCOEF2_2                                                               0x180043F4
#define VI_VCSCCOEF2_3                                                               0x180043F8
#define VI_VCSCCOEF2_4                                                               0x180043FC
#define VI_VCSCCOEF2_5                                                               0x18004400
#define VI_VCSCCOEF2_6                                                               0x18004404
#define VI_VCSCCOEF2_7                                                               0x18004408
#define VI_VCSCCOEF2_8                                                               0x1800440C
#define VI_VCSCCOEF2_9                                                               0x18004410
#define VI_VCSCCOEF2_10                                                               0x18004414
#define VI_VCSCCOEF2_11                                                               0x18004418
#define VI_VCSCCOEF2_12                                                               0x1800441C
#define VI_VCSCCOEF2_13                                                               0x18004420
#define VI_VCSCCOEF2_14                                                               0x18004424
#define VI_VCSCCOEF2_15                                                               0x18004428
#define VI_VCSCCOEF2_16                                                               0x1800442C
#define VI_VCSCCOEF2_17                                                               0x18004430
#define VI_VCSCCOEF2_18                                                               0x18004434
#define VI_VCSCCOEF2_19                                                               0x18004438
#define VI_VCSCCOEF2_0_reg_addr                                                      "0xB80043EC"
#define VI_VCSCCOEF2_1_reg_addr                                                      "0xB80043F0"
#define VI_VCSCCOEF2_2_reg_addr                                                      "0xB80043F4"
#define VI_VCSCCOEF2_3_reg_addr                                                      "0xB80043F8"
#define VI_VCSCCOEF2_4_reg_addr                                                      "0xB80043FC"
#define VI_VCSCCOEF2_5_reg_addr                                                      "0xB8004400"
#define VI_VCSCCOEF2_6_reg_addr                                                      "0xB8004404"
#define VI_VCSCCOEF2_7_reg_addr                                                      "0xB8004408"
#define VI_VCSCCOEF2_8_reg_addr                                                      "0xB800440C"
#define VI_VCSCCOEF2_9_reg_addr                                                      "0xB8004410"
#define VI_VCSCCOEF2_10_reg_addr                                                      "0xB8004414"
#define VI_VCSCCOEF2_11_reg_addr                                                      "0xB8004418"
#define VI_VCSCCOEF2_12_reg_addr                                                      "0xB800441C"
#define VI_VCSCCOEF2_13_reg_addr                                                      "0xB8004420"
#define VI_VCSCCOEF2_14_reg_addr                                                      "0xB8004424"
#define VI_VCSCCOEF2_15_reg_addr                                                      "0xB8004428"
#define VI_VCSCCOEF2_16_reg_addr                                                      "0xB800442C"
#define VI_VCSCCOEF2_17_reg_addr                                                      "0xB8004430"
#define VI_VCSCCOEF2_18_reg_addr                                                      "0xB8004434"
#define VI_VCSCCOEF2_19_reg_addr                                                      "0xB8004438"
#define VI_VCSCCOEF2_0_reg                                                           0xB80043EC
#define VI_VCSCCOEF2_1_reg                                                           0xB80043F0
#define VI_VCSCCOEF2_2_reg                                                           0xB80043F4
#define VI_VCSCCOEF2_3_reg                                                           0xB80043F8
#define VI_VCSCCOEF2_4_reg                                                           0xB80043FC
#define VI_VCSCCOEF2_5_reg                                                           0xB8004400
#define VI_VCSCCOEF2_6_reg                                                           0xB8004404
#define VI_VCSCCOEF2_7_reg                                                           0xB8004408
#define VI_VCSCCOEF2_8_reg                                                           0xB800440C
#define VI_VCSCCOEF2_9_reg                                                           0xB8004410
#define VI_VCSCCOEF2_10_reg                                                           0xB8004414
#define VI_VCSCCOEF2_11_reg                                                           0xB8004418
#define VI_VCSCCOEF2_12_reg                                                           0xB800441C
#define VI_VCSCCOEF2_13_reg                                                           0xB8004420
#define VI_VCSCCOEF2_14_reg                                                           0xB8004424
#define VI_VCSCCOEF2_15_reg                                                           0xB8004428
#define VI_VCSCCOEF2_16_reg                                                           0xB800442C
#define VI_VCSCCOEF2_17_reg                                                           0xB8004430
#define VI_VCSCCOEF2_18_reg                                                           0xB8004434
#define VI_VCSCCOEF2_19_reg                                                           0xB8004438
#define VI_VCSCCOEF2_0_inst_adr                                                      "0x00FB"
#define VI_VCSCCOEF2_1_inst_adr                                                      "0x00FC"
#define VI_VCSCCOEF2_2_inst_adr                                                      "0x00FD"
#define VI_VCSCCOEF2_3_inst_adr                                                      "0x00FE"
#define VI_VCSCCOEF2_4_inst_adr                                                      "0x00FF"
#define VI_VCSCCOEF2_5_inst_adr                                                      "0x0100"
#define VI_VCSCCOEF2_6_inst_adr                                                      "0x0101"
#define VI_VCSCCOEF2_7_inst_adr                                                      "0x0102"
#define VI_VCSCCOEF2_8_inst_adr                                                      "0x0103"
#define VI_VCSCCOEF2_9_inst_adr                                                      "0x0104"
#define VI_VCSCCOEF2_10_inst_adr                                                      "0x0105"
#define VI_VCSCCOEF2_11_inst_adr                                                      "0x0106"
#define VI_VCSCCOEF2_12_inst_adr                                                      "0x0107"
#define VI_VCSCCOEF2_13_inst_adr                                                      "0x0108"
#define VI_VCSCCOEF2_14_inst_adr                                                      "0x0109"
#define VI_VCSCCOEF2_15_inst_adr                                                      "0x010A"
#define VI_VCSCCOEF2_16_inst_adr                                                      "0x010B"
#define VI_VCSCCOEF2_17_inst_adr                                                      "0x010C"
#define VI_VCSCCOEF2_18_inst_adr                                                      "0x010D"
#define VI_VCSCCOEF2_19_inst_adr                                                      "0x010E"
#define VI_VCSCCOEF2_0_inst                                                          0x00FB
#define VI_VCSCCOEF2_1_inst                                                          0x00FC
#define VI_VCSCCOEF2_2_inst                                                          0x00FD
#define VI_VCSCCOEF2_3_inst                                                          0x00FE
#define VI_VCSCCOEF2_4_inst                                                          0x00FF
#define VI_VCSCCOEF2_5_inst                                                          0x0100
#define VI_VCSCCOEF2_6_inst                                                          0x0101
#define VI_VCSCCOEF2_7_inst                                                          0x0102
#define VI_VCSCCOEF2_8_inst                                                          0x0103
#define VI_VCSCCOEF2_9_inst                                                          0x0104
#define VI_VCSCCOEF2_10_inst                                                          0x0105
#define VI_VCSCCOEF2_11_inst                                                          0x0106
#define VI_VCSCCOEF2_12_inst                                                          0x0107
#define VI_VCSCCOEF2_13_inst                                                          0x0108
#define VI_VCSCCOEF2_14_inst                                                          0x0109
#define VI_VCSCCOEF2_15_inst                                                          0x010A
#define VI_VCSCCOEF2_16_inst                                                          0x010B
#define VI_VCSCCOEF2_17_inst                                                          0x010C
#define VI_VCSCCOEF2_18_inst                                                          0x010D
#define VI_VCSCCOEF2_19_inst                                                          0x010E
#define VI_VCSCCOEF2_csccoef_shift                                                   (0)
#define VI_VCSCCOEF2_csccoef_mask                                                    (0x00003FFF)
#define VI_VCSCCOEF2_csccoef(data)                                                   (0x00003FFF&((data)<<0))
#define VI_VCSCCOEF2_csccoef_src(data)                                               ((0x00003FFF&(data))>>0)
#define VI_VCSCCOEF2_get_csccoef(data)                                               ((0x00003FFF&(data))>>0)


#define VI_VOFFSETEN                                                                 0x1800447c
#define VI_VOFFSETEN_reg_addr                                                        "0xB800447C"
#define VI_VOFFSETEN_reg                                                             0xB800447C
#define VI_VOFFSETEN_inst_adr                                                        "0x001F"
#define VI_VOFFSETEN_inst                                                            0x001F
#define VI_VOFFSETEN_y1_clamp_shift                                                  (8)
#define VI_VOFFSETEN_y1_clamp_mask                                                   (0x00000100)
#define VI_VOFFSETEN_y1_clamp(data)                                                  (0x00000100&((data)<<8))
#define VI_VOFFSETEN_y1_clamp_src(data)                                              ((0x00000100&(data))>>8)
#define VI_VOFFSETEN_get_y1_clamp(data)                                              ((0x00000100&(data))>>8)
#define VI_VOFFSETEN_c1_clamp_shift                                                  (7)
#define VI_VOFFSETEN_c1_clamp_mask                                                   (0x00000080)
#define VI_VOFFSETEN_c1_clamp(data)                                                  (0x00000080&((data)<<7))
#define VI_VOFFSETEN_c1_clamp_src(data)                                              ((0x00000080&(data))>>7)
#define VI_VOFFSETEN_get_c1_clamp(data)                                              ((0x00000080&(data))>>7)
#define VI_VOFFSETEN_y2_clamp_shift                                                  (6)
#define VI_VOFFSETEN_y2_clamp_mask                                                   (0x00000040)
#define VI_VOFFSETEN_y2_clamp(data)                                                  (0x00000040&((data)<<6))
#define VI_VOFFSETEN_y2_clamp_src(data)                                              ((0x00000040&(data))>>6)
#define VI_VOFFSETEN_get_y2_clamp(data)                                              ((0x00000040&(data))>>6)
#define VI_VOFFSETEN_c2_clamp_shift                                                  (5)
#define VI_VOFFSETEN_c2_clamp_mask                                                   (0x00000020)
#define VI_VOFFSETEN_c2_clamp(data)                                                  (0x00000020&((data)<<5))
#define VI_VOFFSETEN_c2_clamp_src(data)                                              ((0x00000020&(data))>>5)
#define VI_VOFFSETEN_get_c2_clamp(data)                                              ((0x00000020&(data))>>5)
#define VI_VOFFSETEN_y1_shift                                                        (4)
#define VI_VOFFSETEN_y1_mask                                                         (0x00000010)
#define VI_VOFFSETEN_y1(data)                                                        (0x00000010&((data)<<4))
#define VI_VOFFSETEN_y1_src(data)                                                    ((0x00000010&(data))>>4)
#define VI_VOFFSETEN_get_y1(data)                                                    ((0x00000010&(data))>>4)
#define VI_VOFFSETEN_c1_shift                                                        (3)
#define VI_VOFFSETEN_c1_mask                                                         (0x00000008)
#define VI_VOFFSETEN_c1(data)                                                        (0x00000008&((data)<<3))
#define VI_VOFFSETEN_c1_src(data)                                                    ((0x00000008&(data))>>3)
#define VI_VOFFSETEN_get_c1(data)                                                    ((0x00000008&(data))>>3)
#define VI_VOFFSETEN_y2_shift                                                        (2)
#define VI_VOFFSETEN_y2_mask                                                         (0x00000004)
#define VI_VOFFSETEN_y2(data)                                                        (0x00000004&((data)<<2))
#define VI_VOFFSETEN_y2_src(data)                                                    ((0x00000004&(data))>>2)
#define VI_VOFFSETEN_get_y2(data)                                                    ((0x00000004&(data))>>2)
#define VI_VOFFSETEN_c2_shift                                                        (1)
#define VI_VOFFSETEN_c2_mask                                                         (0x00000002)
#define VI_VOFFSETEN_c2(data)                                                        (0x00000002&((data)<<1))
#define VI_VOFFSETEN_c2_src(data)                                                    ((0x00000002&(data))>>1)
#define VI_VOFFSETEN_get_c2(data)                                                    ((0x00000002&(data))>>1)
#define VI_VOFFSETEN_write_data_shift                                                (0)
#define VI_VOFFSETEN_write_data_mask                                                 (0x00000001)
#define VI_VOFFSETEN_write_data(data)                                                (0x00000001&((data)<<0))
#define VI_VOFFSETEN_write_data_src(data)                                            ((0x00000001&(data))>>0)
#define VI_VOFFSETEN_get_write_data(data)                                            ((0x00000001&(data))>>0)


#define VI_VINFO1                                                                    0x1800456c
#define VI_VINFO1_reg_addr                                                           "0xB800456C"
#define VI_VINFO1_reg                                                                0xB800456C
#define VI_VINFO1_inst_adr                                                           "0x005B"
#define VI_VINFO1_inst                                                               0x005B
#define VI_VINFO1_write_enable1_shift                                                (23)
#define VI_VINFO1_write_enable1_mask                                                 (0x00800000)
#define VI_VINFO1_write_enable1(data)                                                (0x00800000&((data)<<23))
#define VI_VINFO1_write_enable1_src(data)                                            ((0x00800000&(data))>>23)
#define VI_VINFO1_get_write_enable1(data)                                            ((0x00800000&(data))>>23)
#define VI_VINFO1_heighy_shift                                                       (12)
#define VI_VINFO1_heighy_mask                                                        (0x007FF000)
#define VI_VINFO1_heighy(data)                                                       (0x007FF000&((data)<<12))
#define VI_VINFO1_heighy_src(data)                                                   ((0x007FF000&(data))>>12)
#define VI_VINFO1_get_heighy(data)                                                   ((0x007FF000&(data))>>12)
#define VI_VINFO1_write_enable2_shift                                                (11)
#define VI_VINFO1_write_enable2_mask                                                 (0x00000800)
#define VI_VINFO1_write_enable2(data)                                                (0x00000800&((data)<<11))
#define VI_VINFO1_write_enable2_src(data)                                            ((0x00000800&(data))>>11)
#define VI_VINFO1_get_write_enable2(data)                                            ((0x00000800&(data))>>11)
#define VI_VINFO1_heighc_shift                                                       (0)
#define VI_VINFO1_heighc_mask                                                        (0x000007FF)
#define VI_VINFO1_heighc(data)                                                       (0x000007FF&((data)<<0))
#define VI_VINFO1_heighc_src(data)                                                   ((0x000007FF&(data))>>0)
#define VI_VINFO1_get_heighc(data)                                                   ((0x000007FF&(data))>>0)


#define VI_VINFO2                                                                    0x18004574
#define VI_VINFO2_reg_addr                                                           "0xB8004574"
#define VI_VINFO2_reg                                                                0xB8004574
#define VI_VINFO2_inst_adr                                                           "0x005D"
#define VI_VINFO2_inst                                                               0x005D
#define VI_VINFO2_write_enable1_shift                                                (23)
#define VI_VINFO2_write_enable1_mask                                                 (0x00800000)
#define VI_VINFO2_write_enable1(data)                                                (0x00800000&((data)<<23))
#define VI_VINFO2_write_enable1_src(data)                                            ((0x00800000&(data))>>23)
#define VI_VINFO2_get_write_enable1(data)                                            ((0x00800000&(data))>>23)
#define VI_VINFO2_heighy_shift                                                       (12)
#define VI_VINFO2_heighy_mask                                                        (0x007FF000)
#define VI_VINFO2_heighy(data)                                                       (0x007FF000&((data)<<12))
#define VI_VINFO2_heighy_src(data)                                                   ((0x007FF000&(data))>>12)
#define VI_VINFO2_get_heighy(data)                                                   ((0x007FF000&(data))>>12)
#define VI_VINFO2_write_enable2_shift                                                (11)
#define VI_VINFO2_write_enable2_mask                                                 (0x00000800)
#define VI_VINFO2_write_enable2(data)                                                (0x00000800&((data)<<11))
#define VI_VINFO2_write_enable2_src(data)                                            ((0x00000800&(data))>>11)
#define VI_VINFO2_get_write_enable2(data)                                            ((0x00000800&(data))>>11)
#define VI_VINFO2_heighc_shift                                                       (0)
#define VI_VINFO2_heighc_mask                                                        (0x000007FF)
#define VI_VINFO2_heighc(data)                                                       (0x000007FF&((data)<<0))
#define VI_VINFO2_heighc_src(data)                                                   ((0x000007FF&(data))>>0)
#define VI_VINFO2_get_heighc(data)                                                   ((0x000007FF&(data))>>0)


#define VI_SCCTL1                                                                    0x18004070
#define VI_SCCTL1_reg_addr                                                           "0xB8004070"
#define VI_SCCTL1_reg                                                                0xB8004070
#define VI_SCCTL1_inst_adr                                                           "0x001C"
#define VI_SCCTL1_inst                                                               0x001C
#define VI_SCCTL1_yen_shift                                                          (4)
#define VI_SCCTL1_yen_mask                                                           (0x00000010)
#define VI_SCCTL1_yen(data)                                                          (0x00000010&((data)<<4))
#define VI_SCCTL1_yen_src(data)                                                      ((0x00000010&(data))>>4)
#define VI_SCCTL1_get_yen(data)                                                      ((0x00000010&(data))>>4)
#define VI_SCCTL1_yoddtype_shift                                                     (3)
#define VI_SCCTL1_yoddtype_mask                                                      (0x00000008)
#define VI_SCCTL1_yoddtype(data)                                                     (0x00000008&((data)<<3))
#define VI_SCCTL1_yoddtype_src(data)                                                 ((0x00000008&(data))>>3)
#define VI_SCCTL1_get_yoddtype(data)                                                 ((0x00000008&(data))>>3)
#define VI_SCCTL1_cen_shift                                                          (2)
#define VI_SCCTL1_cen_mask                                                           (0x00000004)
#define VI_SCCTL1_cen(data)                                                          (0x00000004&((data)<<2))
#define VI_SCCTL1_cen_src(data)                                                      ((0x00000004&(data))>>2)
#define VI_SCCTL1_get_cen(data)                                                      ((0x00000004&(data))>>2)
#define VI_SCCTL1_coddtype_shift                                                     (1)
#define VI_SCCTL1_coddtype_mask                                                      (0x00000002)
#define VI_SCCTL1_coddtype(data)                                                     (0x00000002&((data)<<1))
#define VI_SCCTL1_coddtype_src(data)                                                 ((0x00000002&(data))>>1)
#define VI_SCCTL1_get_coddtype(data)                                                 ((0x00000002&(data))>>1)
#define VI_SCCTL1_write_data_shift                                                   (0)
#define VI_SCCTL1_write_data_mask                                                    (0x00000001)
#define VI_SCCTL1_write_data(data)                                                   (0x00000001&((data)<<0))
#define VI_SCCTL1_write_data_src(data)                                               ((0x00000001&(data))>>0)
#define VI_SCCTL1_get_write_data(data)                                               ((0x00000001&(data))>>0)


#define VI_SCCTL2                                                                    0x18004074
#define VI_SCCTL2_reg_addr                                                           "0xB8004074"
#define VI_SCCTL2_reg                                                                0xB8004074
#define VI_SCCTL2_inst_adr                                                           "0x001D"
#define VI_SCCTL2_inst                                                               0x001D
#define VI_SCCTL2_yen_shift                                                          (4)
#define VI_SCCTL2_yen_mask                                                           (0x00000010)
#define VI_SCCTL2_yen(data)                                                          (0x00000010&((data)<<4))
#define VI_SCCTL2_yen_src(data)                                                      ((0x00000010&(data))>>4)
#define VI_SCCTL2_get_yen(data)                                                      ((0x00000010&(data))>>4)
#define VI_SCCTL2_yoddtype_shift                                                     (3)
#define VI_SCCTL2_yoddtype_mask                                                      (0x00000008)
#define VI_SCCTL2_yoddtype(data)                                                     (0x00000008&((data)<<3))
#define VI_SCCTL2_yoddtype_src(data)                                                 ((0x00000008&(data))>>3)
#define VI_SCCTL2_get_yoddtype(data)                                                 ((0x00000008&(data))>>3)
#define VI_SCCTL2_cen_shift                                                          (2)
#define VI_SCCTL2_cen_mask                                                           (0x00000004)
#define VI_SCCTL2_cen(data)                                                          (0x00000004&((data)<<2))
#define VI_SCCTL2_cen_src(data)                                                      ((0x00000004&(data))>>2)
#define VI_SCCTL2_get_cen(data)                                                      ((0x00000004&(data))>>2)
#define VI_SCCTL2_coddtype_shift                                                     (1)
#define VI_SCCTL2_coddtype_mask                                                      (0x00000002)
#define VI_SCCTL2_coddtype(data)                                                     (0x00000002&((data)<<1))
#define VI_SCCTL2_coddtype_src(data)                                                 ((0x00000002&(data))>>1)
#define VI_SCCTL2_get_coddtype(data)                                                 ((0x00000002&(data))>>1)
#define VI_SCCTL2_write_data_shift                                                   (0)
#define VI_SCCTL2_write_data_mask                                                    (0x00000001)
#define VI_SCCTL2_write_data(data)                                                   (0x00000001&((data)<<0))
#define VI_SCCTL2_write_data_src(data)                                               ((0x00000001&(data))>>0)
#define VI_SCCTL2_get_write_data(data)                                               ((0x00000001&(data))>>0)


#define VI_YSC1                                                                      0x18004078
#define VI_YSC1_reg_addr                                                             "0xB8004078"
#define VI_YSC1_reg                                                                  0xB8004078
#define VI_YSC1_inst_adr                                                             "0x001E"
#define VI_YSC1_inst                                                                 0x001E
#define VI_YSC1_write_enable1_shift                                                  (29)
#define VI_YSC1_write_enable1_mask                                                   (0x20000000)
#define VI_YSC1_write_enable1(data)                                                  (0x20000000&((data)<<29))
#define VI_YSC1_write_enable1_src(data)                                              ((0x20000000&(data))>>29)
#define VI_YSC1_get_write_enable1(data)                                              ((0x20000000&(data))>>29)
#define VI_YSC1_yonp_shift                                                           (18)
#define VI_YSC1_yonp_mask                                                            (0x1FFC0000)
#define VI_YSC1_yonp(data)                                                           (0x1FFC0000&((data)<<18))
#define VI_YSC1_yonp_src(data)                                                       ((0x1FFC0000&(data))>>18)
#define VI_YSC1_get_yonp(data)                                                       ((0x1FFC0000&(data))>>18)
#define VI_YSC1_write_enable2_shift                                                  (17)
#define VI_YSC1_write_enable2_mask                                                   (0x00020000)
#define VI_YSC1_write_enable2(data)                                                  (0x00020000&((data)<<17))
#define VI_YSC1_write_enable2_src(data)                                              ((0x00020000&(data))>>17)
#define VI_YSC1_get_write_enable2(data)                                              ((0x00020000&(data))>>17)
#define VI_YSC1_ydphs_shift                                                          (0)
#define VI_YSC1_ydphs_mask                                                           (0x0001FFFF)
#define VI_YSC1_ydphs(data)                                                          (0x0001FFFF&((data)<<0))
#define VI_YSC1_ydphs_src(data)                                                      ((0x0001FFFF&(data))>>0)
#define VI_YSC1_get_ydphs(data)                                                      ((0x0001FFFF&(data))>>0)


#define VI_CSC1                                                                      0x1800407c
#define VI_CSC1_reg_addr                                                             "0xB800407C"
#define VI_CSC1_reg                                                                  0xB800407C
#define VI_CSC1_inst_adr                                                             "0x001F"
#define VI_CSC1_inst                                                                 0x001F
#define VI_CSC1_write_enable1_shift                                                  (29)
#define VI_CSC1_write_enable1_mask                                                   (0x20000000)
#define VI_CSC1_write_enable1(data)                                                  (0x20000000&((data)<<29))
#define VI_CSC1_write_enable1_src(data)                                              ((0x20000000&(data))>>29)
#define VI_CSC1_get_write_enable1(data)                                              ((0x20000000&(data))>>29)
#define VI_CSC1_conp_shift                                                           (18)
#define VI_CSC1_conp_mask                                                            (0x1FFC0000)
#define VI_CSC1_conp(data)                                                           (0x1FFC0000&((data)<<18))
#define VI_CSC1_conp_src(data)                                                       ((0x1FFC0000&(data))>>18)
#define VI_CSC1_get_conp(data)                                                       ((0x1FFC0000&(data))>>18)
#define VI_CSC1_write_enable2_shift                                                  (17)
#define VI_CSC1_write_enable2_mask                                                   (0x00020000)
#define VI_CSC1_write_enable2(data)                                                  (0x00020000&((data)<<17))
#define VI_CSC1_write_enable2_src(data)                                              ((0x00020000&(data))>>17)
#define VI_CSC1_get_write_enable2(data)                                              ((0x00020000&(data))>>17)
#define VI_CSC1_cdphs_shift                                                          (0)
#define VI_CSC1_cdphs_mask                                                           (0x0001FFFF)
#define VI_CSC1_cdphs(data)                                                          (0x0001FFFF&((data)<<0))
#define VI_CSC1_cdphs_src(data)                                                      ((0x0001FFFF&(data))>>0)
#define VI_CSC1_get_cdphs(data)                                                      ((0x0001FFFF&(data))>>0)


#define VI_YSC2                                                                      0x18004080
#define VI_YSC2_reg_addr                                                             "0xB8004080"
#define VI_YSC2_reg                                                                  0xB8004080
#define VI_YSC2_inst_adr                                                             "0x0020"
#define VI_YSC2_inst                                                                 0x0020
#define VI_YSC2_write_enable1_shift                                                  (29)
#define VI_YSC2_write_enable1_mask                                                   (0x20000000)
#define VI_YSC2_write_enable1(data)                                                  (0x20000000&((data)<<29))
#define VI_YSC2_write_enable1_src(data)                                              ((0x20000000&(data))>>29)
#define VI_YSC2_get_write_enable1(data)                                              ((0x20000000&(data))>>29)
#define VI_YSC2_yonp_shift                                                           (18)
#define VI_YSC2_yonp_mask                                                            (0x1FFC0000)
#define VI_YSC2_yonp(data)                                                           (0x1FFC0000&((data)<<18))
#define VI_YSC2_yonp_src(data)                                                       ((0x1FFC0000&(data))>>18)
#define VI_YSC2_get_yonp(data)                                                       ((0x1FFC0000&(data))>>18)
#define VI_YSC2_write_enable2_shift                                                  (17)
#define VI_YSC2_write_enable2_mask                                                   (0x00020000)
#define VI_YSC2_write_enable2(data)                                                  (0x00020000&((data)<<17))
#define VI_YSC2_write_enable2_src(data)                                              ((0x00020000&(data))>>17)
#define VI_YSC2_get_write_enable2(data)                                              ((0x00020000&(data))>>17)
#define VI_YSC2_ydphs_shift                                                          (0)
#define VI_YSC2_ydphs_mask                                                           (0x0001FFFF)
#define VI_YSC2_ydphs(data)                                                          (0x0001FFFF&((data)<<0))
#define VI_YSC2_ydphs_src(data)                                                      ((0x0001FFFF&(data))>>0)
#define VI_YSC2_get_ydphs(data)                                                      ((0x0001FFFF&(data))>>0)


#define VI_CSC2                                                                      0x18004084
#define VI_CSC2_reg_addr                                                             "0xB8004084"
#define VI_CSC2_reg                                                                  0xB8004084
#define VI_CSC2_inst_adr                                                             "0x0021"
#define VI_CSC2_inst                                                                 0x0021
#define VI_CSC2_write_enable1_shift                                                  (29)
#define VI_CSC2_write_enable1_mask                                                   (0x20000000)
#define VI_CSC2_write_enable1(data)                                                  (0x20000000&((data)<<29))
#define VI_CSC2_write_enable1_src(data)                                              ((0x20000000&(data))>>29)
#define VI_CSC2_get_write_enable1(data)                                              ((0x20000000&(data))>>29)
#define VI_CSC2_conp_shift                                                           (18)
#define VI_CSC2_conp_mask                                                            (0x1FFC0000)
#define VI_CSC2_conp(data)                                                           (0x1FFC0000&((data)<<18))
#define VI_CSC2_conp_src(data)                                                       ((0x1FFC0000&(data))>>18)
#define VI_CSC2_get_conp(data)                                                       ((0x1FFC0000&(data))>>18)
#define VI_CSC2_write_enable2_shift                                                  (17)
#define VI_CSC2_write_enable2_mask                                                   (0x00020000)
#define VI_CSC2_write_enable2(data)                                                  (0x00020000&((data)<<17))
#define VI_CSC2_write_enable2_src(data)                                              ((0x00020000&(data))>>17)
#define VI_CSC2_get_write_enable2(data)                                              ((0x00020000&(data))>>17)
#define VI_CSC2_cdphs_shift                                                          (0)
#define VI_CSC2_cdphs_mask                                                           (0x0001FFFF)
#define VI_CSC2_cdphs(data)                                                          (0x0001FFFF&((data)<<0))
#define VI_CSC2_cdphs_src(data)                                                      ((0x0001FFFF&(data))>>0)
#define VI_CSC2_get_cdphs(data)                                                      ((0x0001FFFF&(data))>>0)


#define VI_YIPOS1                                                                    0x18004088
#define VI_YIPOS1_reg_addr                                                           "0xB8004088"
#define VI_YIPOS1_reg                                                                0xB8004088
#define VI_YIPOS1_inst_adr                                                           "0x0022"
#define VI_YIPOS1_inst                                                               0x0022
#define VI_YIPOS1_init_offset_shift                                                  (14)
#define VI_YIPOS1_init_offset_mask                                                   (0x01FFC000)
#define VI_YIPOS1_init_offset(data)                                                  (0x01FFC000&((data)<<14))
#define VI_YIPOS1_init_offset_src(data)                                              ((0x01FFC000&(data))>>14)
#define VI_YIPOS1_get_init_offset(data)                                              ((0x01FFC000&(data))>>14)
#define VI_YIPOS1_init_phase_shift                                                   (0)
#define VI_YIPOS1_init_phase_mask                                                    (0x00003FFF)
#define VI_YIPOS1_init_phase(data)                                                   (0x00003FFF&((data)<<0))
#define VI_YIPOS1_init_phase_src(data)                                               ((0x00003FFF&(data))>>0)
#define VI_YIPOS1_get_init_phase(data)                                               ((0x00003FFF&(data))>>0)


#define VI_YIPOS2                                                                    0x1800408c
#define VI_YIPOS2_reg_addr                                                           "0xB800408C"
#define VI_YIPOS2_reg                                                                0xB800408C
#define VI_YIPOS2_inst_adr                                                           "0x0023"
#define VI_YIPOS2_inst                                                               0x0023
#define VI_YIPOS2_init_offset_shift                                                  (14)
#define VI_YIPOS2_init_offset_mask                                                   (0x01FFC000)
#define VI_YIPOS2_init_offset(data)                                                  (0x01FFC000&((data)<<14))
#define VI_YIPOS2_init_offset_src(data)                                              ((0x01FFC000&(data))>>14)
#define VI_YIPOS2_get_init_offset(data)                                              ((0x01FFC000&(data))>>14)
#define VI_YIPOS2_init_phase_shift                                                   (0)
#define VI_YIPOS2_init_phase_mask                                                    (0x00003FFF)
#define VI_YIPOS2_init_phase(data)                                                   (0x00003FFF&((data)<<0))
#define VI_YIPOS2_init_phase_src(data)                                               ((0x00003FFF&(data))>>0)
#define VI_YIPOS2_get_init_phase(data)                                               ((0x00003FFF&(data))>>0)


#define VI_CIPOS1                                                                    0x18004090
#define VI_CIPOS1_reg_addr                                                           "0xB8004090"
#define VI_CIPOS1_reg                                                                0xB8004090
#define VI_CIPOS1_inst_adr                                                           "0x0024"
#define VI_CIPOS1_inst                                                               0x0024
#define VI_CIPOS1_init_offset_shift                                                  (14)
#define VI_CIPOS1_init_offset_mask                                                   (0x01FFC000)
#define VI_CIPOS1_init_offset(data)                                                  (0x01FFC000&((data)<<14))
#define VI_CIPOS1_init_offset_src(data)                                              ((0x01FFC000&(data))>>14)
#define VI_CIPOS1_get_init_offset(data)                                              ((0x01FFC000&(data))>>14)
#define VI_CIPOS1_init_phase_shift                                                   (0)
#define VI_CIPOS1_init_phase_mask                                                    (0x00003FFF)
#define VI_CIPOS1_init_phase(data)                                                   (0x00003FFF&((data)<<0))
#define VI_CIPOS1_init_phase_src(data)                                               ((0x00003FFF&(data))>>0)
#define VI_CIPOS1_get_init_phase(data)                                               ((0x00003FFF&(data))>>0)


#define VI_CIPOS2                                                                    0x18004094
#define VI_CIPOS2_reg_addr                                                           "0xB8004094"
#define VI_CIPOS2_reg                                                                0xB8004094
#define VI_CIPOS2_inst_adr                                                           "0x0025"
#define VI_CIPOS2_inst                                                               0x0025
#define VI_CIPOS2_init_offset_shift                                                  (14)
#define VI_CIPOS2_init_offset_mask                                                   (0x01FFC000)
#define VI_CIPOS2_init_offset(data)                                                  (0x01FFC000&((data)<<14))
#define VI_CIPOS2_init_offset_src(data)                                              ((0x01FFC000&(data))>>14)
#define VI_CIPOS2_get_init_offset(data)                                              ((0x01FFC000&(data))>>14)
#define VI_CIPOS2_init_phase_shift                                                   (0)
#define VI_CIPOS2_init_phase_mask                                                    (0x00003FFF)
#define VI_CIPOS2_init_phase(data)                                                   (0x00003FFF&((data)<<0))
#define VI_CIPOS2_init_phase_src(data)                                               ((0x00003FFF&(data))>>0)
#define VI_CIPOS2_get_init_phase(data)                                               ((0x00003FFF&(data))>>0)


#define VI_YSCCOEF1_0                                                                0x18004098
#define VI_YSCCOEF1_1                                                                0x1800409C
#define VI_YSCCOEF1_2                                                                0x180040A0
#define VI_YSCCOEF1_3                                                                0x180040A4
#define VI_YSCCOEF1_4                                                                0x180040A8
#define VI_YSCCOEF1_5                                                                0x180040AC
#define VI_YSCCOEF1_6                                                                0x180040B0
#define VI_YSCCOEF1_7                                                                0x180040B4
#define VI_YSCCOEF1_8                                                                0x180040B8
#define VI_YSCCOEF1_9                                                                0x180040BC
#define VI_YSCCOEF1_10                                                                0x180040C0
#define VI_YSCCOEF1_11                                                                0x180040C4
#define VI_YSCCOEF1_12                                                                0x180040C8
#define VI_YSCCOEF1_13                                                                0x180040CC
#define VI_YSCCOEF1_14                                                                0x180040D0
#define VI_YSCCOEF1_15                                                                0x180040D4
#define VI_YSCCOEF1_16                                                                0x180040D8
#define VI_YSCCOEF1_17                                                                0x180040DC
#define VI_YSCCOEF1_18                                                                0x180040E0
#define VI_YSCCOEF1_19                                                                0x180040E4
#define VI_YSCCOEF1_20                                                                0x180040E8
#define VI_YSCCOEF1_21                                                                0x180040EC
#define VI_YSCCOEF1_22                                                                0x180040F0
#define VI_YSCCOEF1_23                                                                0x180040F4
#define VI_YSCCOEF1_24                                                                0x180040F8
#define VI_YSCCOEF1_25                                                                0x180040FC
#define VI_YSCCOEF1_26                                                                0x18004100
#define VI_YSCCOEF1_27                                                                0x18004104
#define VI_YSCCOEF1_28                                                                0x18004108
#define VI_YSCCOEF1_29                                                                0x1800410C
#define VI_YSCCOEF1_30                                                                0x18004110
#define VI_YSCCOEF1_31                                                                0x18004114
#define VI_YSCCOEF1_0_reg_addr                                                       "0xB8004098"
#define VI_YSCCOEF1_1_reg_addr                                                       "0xB800409C"
#define VI_YSCCOEF1_2_reg_addr                                                       "0xB80040A0"
#define VI_YSCCOEF1_3_reg_addr                                                       "0xB80040A4"
#define VI_YSCCOEF1_4_reg_addr                                                       "0xB80040A8"
#define VI_YSCCOEF1_5_reg_addr                                                       "0xB80040AC"
#define VI_YSCCOEF1_6_reg_addr                                                       "0xB80040B0"
#define VI_YSCCOEF1_7_reg_addr                                                       "0xB80040B4"
#define VI_YSCCOEF1_8_reg_addr                                                       "0xB80040B8"
#define VI_YSCCOEF1_9_reg_addr                                                       "0xB80040BC"
#define VI_YSCCOEF1_10_reg_addr                                                       "0xB80040C0"
#define VI_YSCCOEF1_11_reg_addr                                                       "0xB80040C4"
#define VI_YSCCOEF1_12_reg_addr                                                       "0xB80040C8"
#define VI_YSCCOEF1_13_reg_addr                                                       "0xB80040CC"
#define VI_YSCCOEF1_14_reg_addr                                                       "0xB80040D0"
#define VI_YSCCOEF1_15_reg_addr                                                       "0xB80040D4"
#define VI_YSCCOEF1_16_reg_addr                                                       "0xB80040D8"
#define VI_YSCCOEF1_17_reg_addr                                                       "0xB80040DC"
#define VI_YSCCOEF1_18_reg_addr                                                       "0xB80040E0"
#define VI_YSCCOEF1_19_reg_addr                                                       "0xB80040E4"
#define VI_YSCCOEF1_20_reg_addr                                                       "0xB80040E8"
#define VI_YSCCOEF1_21_reg_addr                                                       "0xB80040EC"
#define VI_YSCCOEF1_22_reg_addr                                                       "0xB80040F0"
#define VI_YSCCOEF1_23_reg_addr                                                       "0xB80040F4"
#define VI_YSCCOEF1_24_reg_addr                                                       "0xB80040F8"
#define VI_YSCCOEF1_25_reg_addr                                                       "0xB80040FC"
#define VI_YSCCOEF1_26_reg_addr                                                       "0xB8004100"
#define VI_YSCCOEF1_27_reg_addr                                                       "0xB8004104"
#define VI_YSCCOEF1_28_reg_addr                                                       "0xB8004108"
#define VI_YSCCOEF1_29_reg_addr                                                       "0xB800410C"
#define VI_YSCCOEF1_30_reg_addr                                                       "0xB8004110"
#define VI_YSCCOEF1_31_reg_addr                                                       "0xB8004114"
#define VI_YSCCOEF1_0_reg                                                            0xB8004098
#define VI_YSCCOEF1_1_reg                                                            0xB800409C
#define VI_YSCCOEF1_2_reg                                                            0xB80040A0
#define VI_YSCCOEF1_3_reg                                                            0xB80040A4
#define VI_YSCCOEF1_4_reg                                                            0xB80040A8
#define VI_YSCCOEF1_5_reg                                                            0xB80040AC
#define VI_YSCCOEF1_6_reg                                                            0xB80040B0
#define VI_YSCCOEF1_7_reg                                                            0xB80040B4
#define VI_YSCCOEF1_8_reg                                                            0xB80040B8
#define VI_YSCCOEF1_9_reg                                                            0xB80040BC
#define VI_YSCCOEF1_10_reg                                                            0xB80040C0
#define VI_YSCCOEF1_11_reg                                                            0xB80040C4
#define VI_YSCCOEF1_12_reg                                                            0xB80040C8
#define VI_YSCCOEF1_13_reg                                                            0xB80040CC
#define VI_YSCCOEF1_14_reg                                                            0xB80040D0
#define VI_YSCCOEF1_15_reg                                                            0xB80040D4
#define VI_YSCCOEF1_16_reg                                                            0xB80040D8
#define VI_YSCCOEF1_17_reg                                                            0xB80040DC
#define VI_YSCCOEF1_18_reg                                                            0xB80040E0
#define VI_YSCCOEF1_19_reg                                                            0xB80040E4
#define VI_YSCCOEF1_20_reg                                                            0xB80040E8
#define VI_YSCCOEF1_21_reg                                                            0xB80040EC
#define VI_YSCCOEF1_22_reg                                                            0xB80040F0
#define VI_YSCCOEF1_23_reg                                                            0xB80040F4
#define VI_YSCCOEF1_24_reg                                                            0xB80040F8
#define VI_YSCCOEF1_25_reg                                                            0xB80040FC
#define VI_YSCCOEF1_26_reg                                                            0xB8004100
#define VI_YSCCOEF1_27_reg                                                            0xB8004104
#define VI_YSCCOEF1_28_reg                                                            0xB8004108
#define VI_YSCCOEF1_29_reg                                                            0xB800410C
#define VI_YSCCOEF1_30_reg                                                            0xB8004110
#define VI_YSCCOEF1_31_reg                                                            0xB8004114
#define VI_YSCCOEF1_0_inst_adr                                                       "0x0026"
#define VI_YSCCOEF1_1_inst_adr                                                       "0x0027"
#define VI_YSCCOEF1_2_inst_adr                                                       "0x0028"
#define VI_YSCCOEF1_3_inst_adr                                                       "0x0029"
#define VI_YSCCOEF1_4_inst_adr                                                       "0x002A"
#define VI_YSCCOEF1_5_inst_adr                                                       "0x002B"
#define VI_YSCCOEF1_6_inst_adr                                                       "0x002C"
#define VI_YSCCOEF1_7_inst_adr                                                       "0x002D"
#define VI_YSCCOEF1_8_inst_adr                                                       "0x002E"
#define VI_YSCCOEF1_9_inst_adr                                                       "0x002F"
#define VI_YSCCOEF1_10_inst_adr                                                       "0x0030"
#define VI_YSCCOEF1_11_inst_adr                                                       "0x0031"
#define VI_YSCCOEF1_12_inst_adr                                                       "0x0032"
#define VI_YSCCOEF1_13_inst_adr                                                       "0x0033"
#define VI_YSCCOEF1_14_inst_adr                                                       "0x0034"
#define VI_YSCCOEF1_15_inst_adr                                                       "0x0035"
#define VI_YSCCOEF1_16_inst_adr                                                       "0x0036"
#define VI_YSCCOEF1_17_inst_adr                                                       "0x0037"
#define VI_YSCCOEF1_18_inst_adr                                                       "0x0038"
#define VI_YSCCOEF1_19_inst_adr                                                       "0x0039"
#define VI_YSCCOEF1_20_inst_adr                                                       "0x003A"
#define VI_YSCCOEF1_21_inst_adr                                                       "0x003B"
#define VI_YSCCOEF1_22_inst_adr                                                       "0x003C"
#define VI_YSCCOEF1_23_inst_adr                                                       "0x003D"
#define VI_YSCCOEF1_24_inst_adr                                                       "0x003E"
#define VI_YSCCOEF1_25_inst_adr                                                       "0x003F"
#define VI_YSCCOEF1_26_inst_adr                                                       "0x0040"
#define VI_YSCCOEF1_27_inst_adr                                                       "0x0041"
#define VI_YSCCOEF1_28_inst_adr                                                       "0x0042"
#define VI_YSCCOEF1_29_inst_adr                                                       "0x0043"
#define VI_YSCCOEF1_30_inst_adr                                                       "0x0044"
#define VI_YSCCOEF1_31_inst_adr                                                       "0x0045"
#define VI_YSCCOEF1_0_inst                                                           0x0026
#define VI_YSCCOEF1_1_inst                                                           0x0027
#define VI_YSCCOEF1_2_inst                                                           0x0028
#define VI_YSCCOEF1_3_inst                                                           0x0029
#define VI_YSCCOEF1_4_inst                                                           0x002A
#define VI_YSCCOEF1_5_inst                                                           0x002B
#define VI_YSCCOEF1_6_inst                                                           0x002C
#define VI_YSCCOEF1_7_inst                                                           0x002D
#define VI_YSCCOEF1_8_inst                                                           0x002E
#define VI_YSCCOEF1_9_inst                                                           0x002F
#define VI_YSCCOEF1_10_inst                                                           0x0030
#define VI_YSCCOEF1_11_inst                                                           0x0031
#define VI_YSCCOEF1_12_inst                                                           0x0032
#define VI_YSCCOEF1_13_inst                                                           0x0033
#define VI_YSCCOEF1_14_inst                                                           0x0034
#define VI_YSCCOEF1_15_inst                                                           0x0035
#define VI_YSCCOEF1_16_inst                                                           0x0036
#define VI_YSCCOEF1_17_inst                                                           0x0037
#define VI_YSCCOEF1_18_inst                                                           0x0038
#define VI_YSCCOEF1_19_inst                                                           0x0039
#define VI_YSCCOEF1_20_inst                                                           0x003A
#define VI_YSCCOEF1_21_inst                                                           0x003B
#define VI_YSCCOEF1_22_inst                                                           0x003C
#define VI_YSCCOEF1_23_inst                                                           0x003D
#define VI_YSCCOEF1_24_inst                                                           0x003E
#define VI_YSCCOEF1_25_inst                                                           0x003F
#define VI_YSCCOEF1_26_inst                                                           0x0040
#define VI_YSCCOEF1_27_inst                                                           0x0041
#define VI_YSCCOEF1_28_inst                                                           0x0042
#define VI_YSCCOEF1_29_inst                                                           0x0043
#define VI_YSCCOEF1_30_inst                                                           0x0044
#define VI_YSCCOEF1_31_inst                                                           0x0045
#define VI_YSCCOEF1_ysccoef_shift                                                    (0)
#define VI_YSCCOEF1_ysccoef_mask                                                     (0x00003FFF)
#define VI_YSCCOEF1_ysccoef(data)                                                    (0x00003FFF&((data)<<0))
#define VI_YSCCOEF1_ysccoef_src(data)                                                ((0x00003FFF&(data))>>0)
#define VI_YSCCOEF1_get_ysccoef(data)                                                ((0x00003FFF&(data))>>0)


#define VI_YSCCOEF2_0                                                                0x18004118
#define VI_YSCCOEF2_1                                                                0x1800411C
#define VI_YSCCOEF2_2                                                                0x18004120
#define VI_YSCCOEF2_3                                                                0x18004124
#define VI_YSCCOEF2_4                                                                0x18004128
#define VI_YSCCOEF2_5                                                                0x1800412C
#define VI_YSCCOEF2_6                                                                0x18004130
#define VI_YSCCOEF2_7                                                                0x18004134
#define VI_YSCCOEF2_8                                                                0x18004138
#define VI_YSCCOEF2_9                                                                0x1800413C
#define VI_YSCCOEF2_10                                                                0x18004140
#define VI_YSCCOEF2_11                                                                0x18004144
#define VI_YSCCOEF2_12                                                                0x18004148
#define VI_YSCCOEF2_13                                                                0x1800414C
#define VI_YSCCOEF2_14                                                                0x18004150
#define VI_YSCCOEF2_15                                                                0x18004154
#define VI_YSCCOEF2_16                                                                0x18004158
#define VI_YSCCOEF2_17                                                                0x1800415C
#define VI_YSCCOEF2_18                                                                0x18004160
#define VI_YSCCOEF2_19                                                                0x18004164
#define VI_YSCCOEF2_20                                                                0x18004168
#define VI_YSCCOEF2_21                                                                0x1800416C
#define VI_YSCCOEF2_22                                                                0x18004170
#define VI_YSCCOEF2_23                                                                0x18004174
#define VI_YSCCOEF2_24                                                                0x18004178
#define VI_YSCCOEF2_25                                                                0x1800417C
#define VI_YSCCOEF2_26                                                                0x18004180
#define VI_YSCCOEF2_27                                                                0x18004184
#define VI_YSCCOEF2_28                                                                0x18004188
#define VI_YSCCOEF2_29                                                                0x1800418C
#define VI_YSCCOEF2_30                                                                0x18004190
#define VI_YSCCOEF2_31                                                                0x18004194
#define VI_YSCCOEF2_0_reg_addr                                                       "0xB8004118"
#define VI_YSCCOEF2_1_reg_addr                                                       "0xB800411C"
#define VI_YSCCOEF2_2_reg_addr                                                       "0xB8004120"
#define VI_YSCCOEF2_3_reg_addr                                                       "0xB8004124"
#define VI_YSCCOEF2_4_reg_addr                                                       "0xB8004128"
#define VI_YSCCOEF2_5_reg_addr                                                       "0xB800412C"
#define VI_YSCCOEF2_6_reg_addr                                                       "0xB8004130"
#define VI_YSCCOEF2_7_reg_addr                                                       "0xB8004134"
#define VI_YSCCOEF2_8_reg_addr                                                       "0xB8004138"
#define VI_YSCCOEF2_9_reg_addr                                                       "0xB800413C"
#define VI_YSCCOEF2_10_reg_addr                                                       "0xB8004140"
#define VI_YSCCOEF2_11_reg_addr                                                       "0xB8004144"
#define VI_YSCCOEF2_12_reg_addr                                                       "0xB8004148"
#define VI_YSCCOEF2_13_reg_addr                                                       "0xB800414C"
#define VI_YSCCOEF2_14_reg_addr                                                       "0xB8004150"
#define VI_YSCCOEF2_15_reg_addr                                                       "0xB8004154"
#define VI_YSCCOEF2_16_reg_addr                                                       "0xB8004158"
#define VI_YSCCOEF2_17_reg_addr                                                       "0xB800415C"
#define VI_YSCCOEF2_18_reg_addr                                                       "0xB8004160"
#define VI_YSCCOEF2_19_reg_addr                                                       "0xB8004164"
#define VI_YSCCOEF2_20_reg_addr                                                       "0xB8004168"
#define VI_YSCCOEF2_21_reg_addr                                                       "0xB800416C"
#define VI_YSCCOEF2_22_reg_addr                                                       "0xB8004170"
#define VI_YSCCOEF2_23_reg_addr                                                       "0xB8004174"
#define VI_YSCCOEF2_24_reg_addr                                                       "0xB8004178"
#define VI_YSCCOEF2_25_reg_addr                                                       "0xB800417C"
#define VI_YSCCOEF2_26_reg_addr                                                       "0xB8004180"
#define VI_YSCCOEF2_27_reg_addr                                                       "0xB8004184"
#define VI_YSCCOEF2_28_reg_addr                                                       "0xB8004188"
#define VI_YSCCOEF2_29_reg_addr                                                       "0xB800418C"
#define VI_YSCCOEF2_30_reg_addr                                                       "0xB8004190"
#define VI_YSCCOEF2_31_reg_addr                                                       "0xB8004194"
#define VI_YSCCOEF2_0_reg                                                            0xB8004118
#define VI_YSCCOEF2_1_reg                                                            0xB800411C
#define VI_YSCCOEF2_2_reg                                                            0xB8004120
#define VI_YSCCOEF2_3_reg                                                            0xB8004124
#define VI_YSCCOEF2_4_reg                                                            0xB8004128
#define VI_YSCCOEF2_5_reg                                                            0xB800412C
#define VI_YSCCOEF2_6_reg                                                            0xB8004130
#define VI_YSCCOEF2_7_reg                                                            0xB8004134
#define VI_YSCCOEF2_8_reg                                                            0xB8004138
#define VI_YSCCOEF2_9_reg                                                            0xB800413C
#define VI_YSCCOEF2_10_reg                                                            0xB8004140
#define VI_YSCCOEF2_11_reg                                                            0xB8004144
#define VI_YSCCOEF2_12_reg                                                            0xB8004148
#define VI_YSCCOEF2_13_reg                                                            0xB800414C
#define VI_YSCCOEF2_14_reg                                                            0xB8004150
#define VI_YSCCOEF2_15_reg                                                            0xB8004154
#define VI_YSCCOEF2_16_reg                                                            0xB8004158
#define VI_YSCCOEF2_17_reg                                                            0xB800415C
#define VI_YSCCOEF2_18_reg                                                            0xB8004160
#define VI_YSCCOEF2_19_reg                                                            0xB8004164
#define VI_YSCCOEF2_20_reg                                                            0xB8004168
#define VI_YSCCOEF2_21_reg                                                            0xB800416C
#define VI_YSCCOEF2_22_reg                                                            0xB8004170
#define VI_YSCCOEF2_23_reg                                                            0xB8004174
#define VI_YSCCOEF2_24_reg                                                            0xB8004178
#define VI_YSCCOEF2_25_reg                                                            0xB800417C
#define VI_YSCCOEF2_26_reg                                                            0xB8004180
#define VI_YSCCOEF2_27_reg                                                            0xB8004184
#define VI_YSCCOEF2_28_reg                                                            0xB8004188
#define VI_YSCCOEF2_29_reg                                                            0xB800418C
#define VI_YSCCOEF2_30_reg                                                            0xB8004190
#define VI_YSCCOEF2_31_reg                                                            0xB8004194
#define VI_YSCCOEF2_0_inst_adr                                                       "0x0046"
#define VI_YSCCOEF2_1_inst_adr                                                       "0x0047"
#define VI_YSCCOEF2_2_inst_adr                                                       "0x0048"
#define VI_YSCCOEF2_3_inst_adr                                                       "0x0049"
#define VI_YSCCOEF2_4_inst_adr                                                       "0x004A"
#define VI_YSCCOEF2_5_inst_adr                                                       "0x004B"
#define VI_YSCCOEF2_6_inst_adr                                                       "0x004C"
#define VI_YSCCOEF2_7_inst_adr                                                       "0x004D"
#define VI_YSCCOEF2_8_inst_adr                                                       "0x004E"
#define VI_YSCCOEF2_9_inst_adr                                                       "0x004F"
#define VI_YSCCOEF2_10_inst_adr                                                       "0x0050"
#define VI_YSCCOEF2_11_inst_adr                                                       "0x0051"
#define VI_YSCCOEF2_12_inst_adr                                                       "0x0052"
#define VI_YSCCOEF2_13_inst_adr                                                       "0x0053"
#define VI_YSCCOEF2_14_inst_adr                                                       "0x0054"
#define VI_YSCCOEF2_15_inst_adr                                                       "0x0055"
#define VI_YSCCOEF2_16_inst_adr                                                       "0x0056"
#define VI_YSCCOEF2_17_inst_adr                                                       "0x0057"
#define VI_YSCCOEF2_18_inst_adr                                                       "0x0058"
#define VI_YSCCOEF2_19_inst_adr                                                       "0x0059"
#define VI_YSCCOEF2_20_inst_adr                                                       "0x005A"
#define VI_YSCCOEF2_21_inst_adr                                                       "0x005B"
#define VI_YSCCOEF2_22_inst_adr                                                       "0x005C"
#define VI_YSCCOEF2_23_inst_adr                                                       "0x005D"
#define VI_YSCCOEF2_24_inst_adr                                                       "0x005E"
#define VI_YSCCOEF2_25_inst_adr                                                       "0x005F"
#define VI_YSCCOEF2_26_inst_adr                                                       "0x0060"
#define VI_YSCCOEF2_27_inst_adr                                                       "0x0061"
#define VI_YSCCOEF2_28_inst_adr                                                       "0x0062"
#define VI_YSCCOEF2_29_inst_adr                                                       "0x0063"
#define VI_YSCCOEF2_30_inst_adr                                                       "0x0064"
#define VI_YSCCOEF2_31_inst_adr                                                       "0x0065"
#define VI_YSCCOEF2_0_inst                                                           0x0046
#define VI_YSCCOEF2_1_inst                                                           0x0047
#define VI_YSCCOEF2_2_inst                                                           0x0048
#define VI_YSCCOEF2_3_inst                                                           0x0049
#define VI_YSCCOEF2_4_inst                                                           0x004A
#define VI_YSCCOEF2_5_inst                                                           0x004B
#define VI_YSCCOEF2_6_inst                                                           0x004C
#define VI_YSCCOEF2_7_inst                                                           0x004D
#define VI_YSCCOEF2_8_inst                                                           0x004E
#define VI_YSCCOEF2_9_inst                                                           0x004F
#define VI_YSCCOEF2_10_inst                                                           0x0050
#define VI_YSCCOEF2_11_inst                                                           0x0051
#define VI_YSCCOEF2_12_inst                                                           0x0052
#define VI_YSCCOEF2_13_inst                                                           0x0053
#define VI_YSCCOEF2_14_inst                                                           0x0054
#define VI_YSCCOEF2_15_inst                                                           0x0055
#define VI_YSCCOEF2_16_inst                                                           0x0056
#define VI_YSCCOEF2_17_inst                                                           0x0057
#define VI_YSCCOEF2_18_inst                                                           0x0058
#define VI_YSCCOEF2_19_inst                                                           0x0059
#define VI_YSCCOEF2_20_inst                                                           0x005A
#define VI_YSCCOEF2_21_inst                                                           0x005B
#define VI_YSCCOEF2_22_inst                                                           0x005C
#define VI_YSCCOEF2_23_inst                                                           0x005D
#define VI_YSCCOEF2_24_inst                                                           0x005E
#define VI_YSCCOEF2_25_inst                                                           0x005F
#define VI_YSCCOEF2_26_inst                                                           0x0060
#define VI_YSCCOEF2_27_inst                                                           0x0061
#define VI_YSCCOEF2_28_inst                                                           0x0062
#define VI_YSCCOEF2_29_inst                                                           0x0063
#define VI_YSCCOEF2_30_inst                                                           0x0064
#define VI_YSCCOEF2_31_inst                                                           0x0065
#define VI_YSCCOEF2_ysccoef_shift                                                    (0)
#define VI_YSCCOEF2_ysccoef_mask                                                     (0x00003FFF)
#define VI_YSCCOEF2_ysccoef(data)                                                    (0x00003FFF&((data)<<0))
#define VI_YSCCOEF2_ysccoef_src(data)                                                ((0x00003FFF&(data))>>0)
#define VI_YSCCOEF2_get_ysccoef(data)                                                ((0x00003FFF&(data))>>0)


#define VI_CSCCOEF1_0                                                                0x18004198
#define VI_CSCCOEF1_1                                                                0x1800419C
#define VI_CSCCOEF1_2                                                                0x180041A0
#define VI_CSCCOEF1_3                                                                0x180041A4
#define VI_CSCCOEF1_4                                                                0x180041A8
#define VI_CSCCOEF1_5                                                                0x180041AC
#define VI_CSCCOEF1_6                                                                0x180041B0
#define VI_CSCCOEF1_7                                                                0x180041B4
#define VI_CSCCOEF1_8                                                                0x180041B8
#define VI_CSCCOEF1_9                                                                0x180041BC
#define VI_CSCCOEF1_10                                                                0x180041C0
#define VI_CSCCOEF1_11                                                                0x180041C4
#define VI_CSCCOEF1_12                                                                0x180041C8
#define VI_CSCCOEF1_13                                                                0x180041CC
#define VI_CSCCOEF1_14                                                                0x180041D0
#define VI_CSCCOEF1_15                                                                0x180041D4
#define VI_CSCCOEF1_0_reg_addr                                                       "0xB8004198"
#define VI_CSCCOEF1_1_reg_addr                                                       "0xB800419C"
#define VI_CSCCOEF1_2_reg_addr                                                       "0xB80041A0"
#define VI_CSCCOEF1_3_reg_addr                                                       "0xB80041A4"
#define VI_CSCCOEF1_4_reg_addr                                                       "0xB80041A8"
#define VI_CSCCOEF1_5_reg_addr                                                       "0xB80041AC"
#define VI_CSCCOEF1_6_reg_addr                                                       "0xB80041B0"
#define VI_CSCCOEF1_7_reg_addr                                                       "0xB80041B4"
#define VI_CSCCOEF1_8_reg_addr                                                       "0xB80041B8"
#define VI_CSCCOEF1_9_reg_addr                                                       "0xB80041BC"
#define VI_CSCCOEF1_10_reg_addr                                                       "0xB80041C0"
#define VI_CSCCOEF1_11_reg_addr                                                       "0xB80041C4"
#define VI_CSCCOEF1_12_reg_addr                                                       "0xB80041C8"
#define VI_CSCCOEF1_13_reg_addr                                                       "0xB80041CC"
#define VI_CSCCOEF1_14_reg_addr                                                       "0xB80041D0"
#define VI_CSCCOEF1_15_reg_addr                                                       "0xB80041D4"
#define VI_CSCCOEF1_0_reg                                                            0xB8004198
#define VI_CSCCOEF1_1_reg                                                            0xB800419C
#define VI_CSCCOEF1_2_reg                                                            0xB80041A0
#define VI_CSCCOEF1_3_reg                                                            0xB80041A4
#define VI_CSCCOEF1_4_reg                                                            0xB80041A8
#define VI_CSCCOEF1_5_reg                                                            0xB80041AC
#define VI_CSCCOEF1_6_reg                                                            0xB80041B0
#define VI_CSCCOEF1_7_reg                                                            0xB80041B4
#define VI_CSCCOEF1_8_reg                                                            0xB80041B8
#define VI_CSCCOEF1_9_reg                                                            0xB80041BC
#define VI_CSCCOEF1_10_reg                                                            0xB80041C0
#define VI_CSCCOEF1_11_reg                                                            0xB80041C4
#define VI_CSCCOEF1_12_reg                                                            0xB80041C8
#define VI_CSCCOEF1_13_reg                                                            0xB80041CC
#define VI_CSCCOEF1_14_reg                                                            0xB80041D0
#define VI_CSCCOEF1_15_reg                                                            0xB80041D4
#define VI_CSCCOEF1_0_inst_adr                                                       "0x0066"
#define VI_CSCCOEF1_1_inst_adr                                                       "0x0067"
#define VI_CSCCOEF1_2_inst_adr                                                       "0x0068"
#define VI_CSCCOEF1_3_inst_adr                                                       "0x0069"
#define VI_CSCCOEF1_4_inst_adr                                                       "0x006A"
#define VI_CSCCOEF1_5_inst_adr                                                       "0x006B"
#define VI_CSCCOEF1_6_inst_adr                                                       "0x006C"
#define VI_CSCCOEF1_7_inst_adr                                                       "0x006D"
#define VI_CSCCOEF1_8_inst_adr                                                       "0x006E"
#define VI_CSCCOEF1_9_inst_adr                                                       "0x006F"
#define VI_CSCCOEF1_10_inst_adr                                                       "0x0070"
#define VI_CSCCOEF1_11_inst_adr                                                       "0x0071"
#define VI_CSCCOEF1_12_inst_adr                                                       "0x0072"
#define VI_CSCCOEF1_13_inst_adr                                                       "0x0073"
#define VI_CSCCOEF1_14_inst_adr                                                       "0x0074"
#define VI_CSCCOEF1_15_inst_adr                                                       "0x0075"
#define VI_CSCCOEF1_0_inst                                                           0x0066
#define VI_CSCCOEF1_1_inst                                                           0x0067
#define VI_CSCCOEF1_2_inst                                                           0x0068
#define VI_CSCCOEF1_3_inst                                                           0x0069
#define VI_CSCCOEF1_4_inst                                                           0x006A
#define VI_CSCCOEF1_5_inst                                                           0x006B
#define VI_CSCCOEF1_6_inst                                                           0x006C
#define VI_CSCCOEF1_7_inst                                                           0x006D
#define VI_CSCCOEF1_8_inst                                                           0x006E
#define VI_CSCCOEF1_9_inst                                                           0x006F
#define VI_CSCCOEF1_10_inst                                                           0x0070
#define VI_CSCCOEF1_11_inst                                                           0x0071
#define VI_CSCCOEF1_12_inst                                                           0x0072
#define VI_CSCCOEF1_13_inst                                                           0x0073
#define VI_CSCCOEF1_14_inst                                                           0x0074
#define VI_CSCCOEF1_15_inst                                                           0x0075
#define VI_CSCCOEF1_csccoef_shift                                                    (0)
#define VI_CSCCOEF1_csccoef_mask                                                     (0x00003FFF)
#define VI_CSCCOEF1_csccoef(data)                                                    (0x00003FFF&((data)<<0))
#define VI_CSCCOEF1_csccoef_src(data)                                                ((0x00003FFF&(data))>>0)
#define VI_CSCCOEF1_get_csccoef(data)                                                ((0x00003FFF&(data))>>0)


#define VI_CSCCOEF2_0                                                                0x180041D8
#define VI_CSCCOEF2_1                                                                0x180041DC
#define VI_CSCCOEF2_2                                                                0x180041E0
#define VI_CSCCOEF2_3                                                                0x180041E4
#define VI_CSCCOEF2_4                                                                0x180041E8
#define VI_CSCCOEF2_5                                                                0x180041EC
#define VI_CSCCOEF2_6                                                                0x180041F0
#define VI_CSCCOEF2_7                                                                0x180041F4
#define VI_CSCCOEF2_8                                                                0x180041F8
#define VI_CSCCOEF2_9                                                                0x180041FC
#define VI_CSCCOEF2_10                                                                0x18004200
#define VI_CSCCOEF2_11                                                                0x18004204
#define VI_CSCCOEF2_12                                                                0x18004208
#define VI_CSCCOEF2_13                                                                0x1800420C
#define VI_CSCCOEF2_14                                                                0x18004210
#define VI_CSCCOEF2_15                                                                0x18004214
#define VI_CSCCOEF2_0_reg_addr                                                       "0xB80041D8"
#define VI_CSCCOEF2_1_reg_addr                                                       "0xB80041DC"
#define VI_CSCCOEF2_2_reg_addr                                                       "0xB80041E0"
#define VI_CSCCOEF2_3_reg_addr                                                       "0xB80041E4"
#define VI_CSCCOEF2_4_reg_addr                                                       "0xB80041E8"
#define VI_CSCCOEF2_5_reg_addr                                                       "0xB80041EC"
#define VI_CSCCOEF2_6_reg_addr                                                       "0xB80041F0"
#define VI_CSCCOEF2_7_reg_addr                                                       "0xB80041F4"
#define VI_CSCCOEF2_8_reg_addr                                                       "0xB80041F8"
#define VI_CSCCOEF2_9_reg_addr                                                       "0xB80041FC"
#define VI_CSCCOEF2_10_reg_addr                                                       "0xB8004200"
#define VI_CSCCOEF2_11_reg_addr                                                       "0xB8004204"
#define VI_CSCCOEF2_12_reg_addr                                                       "0xB8004208"
#define VI_CSCCOEF2_13_reg_addr                                                       "0xB800420C"
#define VI_CSCCOEF2_14_reg_addr                                                       "0xB8004210"
#define VI_CSCCOEF2_15_reg_addr                                                       "0xB8004214"
#define VI_CSCCOEF2_0_reg                                                            0xB80041D8
#define VI_CSCCOEF2_1_reg                                                            0xB80041DC
#define VI_CSCCOEF2_2_reg                                                            0xB80041E0
#define VI_CSCCOEF2_3_reg                                                            0xB80041E4
#define VI_CSCCOEF2_4_reg                                                            0xB80041E8
#define VI_CSCCOEF2_5_reg                                                            0xB80041EC
#define VI_CSCCOEF2_6_reg                                                            0xB80041F0
#define VI_CSCCOEF2_7_reg                                                            0xB80041F4
#define VI_CSCCOEF2_8_reg                                                            0xB80041F8
#define VI_CSCCOEF2_9_reg                                                            0xB80041FC
#define VI_CSCCOEF2_10_reg                                                            0xB8004200
#define VI_CSCCOEF2_11_reg                                                            0xB8004204
#define VI_CSCCOEF2_12_reg                                                            0xB8004208
#define VI_CSCCOEF2_13_reg                                                            0xB800420C
#define VI_CSCCOEF2_14_reg                                                            0xB8004210
#define VI_CSCCOEF2_15_reg                                                            0xB8004214
#define VI_CSCCOEF2_0_inst_adr                                                       "0x0076"
#define VI_CSCCOEF2_1_inst_adr                                                       "0x0077"
#define VI_CSCCOEF2_2_inst_adr                                                       "0x0078"
#define VI_CSCCOEF2_3_inst_adr                                                       "0x0079"
#define VI_CSCCOEF2_4_inst_adr                                                       "0x007A"
#define VI_CSCCOEF2_5_inst_adr                                                       "0x007B"
#define VI_CSCCOEF2_6_inst_adr                                                       "0x007C"
#define VI_CSCCOEF2_7_inst_adr                                                       "0x007D"
#define VI_CSCCOEF2_8_inst_adr                                                       "0x007E"
#define VI_CSCCOEF2_9_inst_adr                                                       "0x007F"
#define VI_CSCCOEF2_10_inst_adr                                                       "0x0080"
#define VI_CSCCOEF2_11_inst_adr                                                       "0x0081"
#define VI_CSCCOEF2_12_inst_adr                                                       "0x0082"
#define VI_CSCCOEF2_13_inst_adr                                                       "0x0083"
#define VI_CSCCOEF2_14_inst_adr                                                       "0x0084"
#define VI_CSCCOEF2_15_inst_adr                                                       "0x0085"
#define VI_CSCCOEF2_0_inst                                                           0x0076
#define VI_CSCCOEF2_1_inst                                                           0x0077
#define VI_CSCCOEF2_2_inst                                                           0x0078
#define VI_CSCCOEF2_3_inst                                                           0x0079
#define VI_CSCCOEF2_4_inst                                                           0x007A
#define VI_CSCCOEF2_5_inst                                                           0x007B
#define VI_CSCCOEF2_6_inst                                                           0x007C
#define VI_CSCCOEF2_7_inst                                                           0x007D
#define VI_CSCCOEF2_8_inst                                                           0x007E
#define VI_CSCCOEF2_9_inst                                                           0x007F
#define VI_CSCCOEF2_10_inst                                                           0x0080
#define VI_CSCCOEF2_11_inst                                                           0x0081
#define VI_CSCCOEF2_12_inst                                                           0x0082
#define VI_CSCCOEF2_13_inst                                                           0x0083
#define VI_CSCCOEF2_14_inst                                                           0x0084
#define VI_CSCCOEF2_15_inst                                                           0x0085
#define VI_CSCCOEF2_csccoef_shift                                                    (0)
#define VI_CSCCOEF2_csccoef_mask                                                     (0x00003FFF)
#define VI_CSCCOEF2_csccoef(data)                                                    (0x00003FFF&((data)<<0))
#define VI_CSCCOEF2_csccoef_src(data)                                                ((0x00003FFF&(data))>>0)
#define VI_CSCCOEF2_get_csccoef(data)                                                ((0x00003FFF&(data))>>0)


#define VI_OFFSETEN                                                                  0x18004218
#define VI_OFFSETEN_reg_addr                                                         "0xB8004218"
#define VI_OFFSETEN_reg                                                              0xB8004218
#define VI_OFFSETEN_inst_adr                                                         "0x0086"
#define VI_OFFSETEN_inst                                                             0x0086
#define VI_OFFSETEN_y1_clamp_shift                                                   (8)
#define VI_OFFSETEN_y1_clamp_mask                                                    (0x00000100)
#define VI_OFFSETEN_y1_clamp(data)                                                   (0x00000100&((data)<<8))
#define VI_OFFSETEN_y1_clamp_src(data)                                               ((0x00000100&(data))>>8)
#define VI_OFFSETEN_get_y1_clamp(data)                                               ((0x00000100&(data))>>8)
#define VI_OFFSETEN_c1_clamp_shift                                                   (7)
#define VI_OFFSETEN_c1_clamp_mask                                                    (0x00000080)
#define VI_OFFSETEN_c1_clamp(data)                                                   (0x00000080&((data)<<7))
#define VI_OFFSETEN_c1_clamp_src(data)                                               ((0x00000080&(data))>>7)
#define VI_OFFSETEN_get_c1_clamp(data)                                               ((0x00000080&(data))>>7)
#define VI_OFFSETEN_y2_clamp_shift                                                   (6)
#define VI_OFFSETEN_y2_clamp_mask                                                    (0x00000040)
#define VI_OFFSETEN_y2_clamp(data)                                                   (0x00000040&((data)<<6))
#define VI_OFFSETEN_y2_clamp_src(data)                                               ((0x00000040&(data))>>6)
#define VI_OFFSETEN_get_y2_clamp(data)                                               ((0x00000040&(data))>>6)
#define VI_OFFSETEN_c2_clamp_shift                                                   (5)
#define VI_OFFSETEN_c2_clamp_mask                                                    (0x00000020)
#define VI_OFFSETEN_c2_clamp(data)                                                   (0x00000020&((data)<<5))
#define VI_OFFSETEN_c2_clamp_src(data)                                               ((0x00000020&(data))>>5)
#define VI_OFFSETEN_get_c2_clamp(data)                                               ((0x00000020&(data))>>5)
#define VI_OFFSETEN_y1_shift                                                         (4)
#define VI_OFFSETEN_y1_mask                                                          (0x00000010)
#define VI_OFFSETEN_y1(data)                                                         (0x00000010&((data)<<4))
#define VI_OFFSETEN_y1_src(data)                                                     ((0x00000010&(data))>>4)
#define VI_OFFSETEN_get_y1(data)                                                     ((0x00000010&(data))>>4)
#define VI_OFFSETEN_c1_shift                                                         (3)
#define VI_OFFSETEN_c1_mask                                                          (0x00000008)
#define VI_OFFSETEN_c1(data)                                                         (0x00000008&((data)<<3))
#define VI_OFFSETEN_c1_src(data)                                                     ((0x00000008&(data))>>3)
#define VI_OFFSETEN_get_c1(data)                                                     ((0x00000008&(data))>>3)
#define VI_OFFSETEN_y2_shift                                                         (2)
#define VI_OFFSETEN_y2_mask                                                          (0x00000004)
#define VI_OFFSETEN_y2(data)                                                         (0x00000004&((data)<<2))
#define VI_OFFSETEN_y2_src(data)                                                     ((0x00000004&(data))>>2)
#define VI_OFFSETEN_get_y2(data)                                                     ((0x00000004&(data))>>2)
#define VI_OFFSETEN_c2_shift                                                         (1)
#define VI_OFFSETEN_c2_mask                                                          (0x00000002)
#define VI_OFFSETEN_c2(data)                                                         (0x00000002&((data)<<1))
#define VI_OFFSETEN_c2_src(data)                                                     ((0x00000002&(data))>>1)
#define VI_OFFSETEN_get_c2(data)                                                     ((0x00000002&(data))>>1)
#define VI_OFFSETEN_write_data_shift                                                 (0)
#define VI_OFFSETEN_write_data_mask                                                  (0x00000001)
#define VI_OFFSETEN_write_data(data)                                                 (0x00000001&((data)<<0))
#define VI_OFFSETEN_write_data_src(data)                                             ((0x00000001&(data))>>0)
#define VI_OFFSETEN_get_write_data(data)                                             ((0x00000001&(data))>>0)


#define VI_HPD1                                                                      0x1800421c
#define VI_HPD1_reg_addr                                                             "0xB800421C"
#define VI_HPD1_reg                                                                  0xB800421C
#define VI_HPD1_inst_adr                                                             "0x0087"
#define VI_HPD1_inst                                                                 0x0087
#define VI_HPD1_hpd_enable_shift                                                     (29)
#define VI_HPD1_hpd_enable_mask                                                      (0x20000000)
#define VI_HPD1_hpd_enable(data)                                                     (0x20000000&((data)<<29))
#define VI_HPD1_hpd_enable_src(data)                                                 ((0x20000000&(data))>>29)
#define VI_HPD1_get_hpd_enable(data)                                                 ((0x20000000&(data))>>29)
#define VI_HPD1_hpd_acc_shift                                                        (0)
#define VI_HPD1_hpd_acc_mask                                                         (0x1FFFFFFF)
#define VI_HPD1_hpd_acc(data)                                                        (0x1FFFFFFF&((data)<<0))
#define VI_HPD1_hpd_acc_src(data)                                                    ((0x1FFFFFFF&(data))>>0)
#define VI_HPD1_get_hpd_acc(data)                                                    ((0x1FFFFFFF&(data))>>0)


#define VI_HPD2                                                                      0x18004220
#define VI_HPD2_reg_addr                                                             "0xB8004220"
#define VI_HPD2_reg                                                                  0xB8004220
#define VI_HPD2_inst_adr                                                             "0x0088"
#define VI_HPD2_inst                                                                 0x0088
#define VI_HPD2_hpd_enable_shift                                                     (29)
#define VI_HPD2_hpd_enable_mask                                                      (0x20000000)
#define VI_HPD2_hpd_enable(data)                                                     (0x20000000&((data)<<29))
#define VI_HPD2_hpd_enable_src(data)                                                 ((0x20000000&(data))>>29)
#define VI_HPD2_get_hpd_enable(data)                                                 ((0x20000000&(data))>>29)
#define VI_HPD2_hpd_acc_shift                                                        (0)
#define VI_HPD2_hpd_acc_mask                                                         (0x1FFFFFFF)
#define VI_HPD2_hpd_acc(data)                                                        (0x1FFFFFFF&((data)<<0))
#define VI_HPD2_hpd_acc_src(data)                                                    ((0x1FFFFFFF&(data))>>0)
#define VI_HPD2_get_hpd_acc(data)                                                    ((0x1FFFFFFF&(data))>>0)


#define VI_VPD1                                                                      0x180044b4
#define VI_VPD1_reg_addr                                                             "0xB80044B4"
#define VI_VPD1_reg                                                                  0xB80044B4
#define VI_VPD1_inst_adr                                                             "0x002D"
#define VI_VPD1_inst                                                                 0x002D
#define VI_VPD1_vpd_enable_shift                                                     (29)
#define VI_VPD1_vpd_enable_mask                                                      (0x20000000)
#define VI_VPD1_vpd_enable(data)                                                     (0x20000000&((data)<<29))
#define VI_VPD1_vpd_enable_src(data)                                                 ((0x20000000&(data))>>29)
#define VI_VPD1_get_vpd_enable(data)                                                 ((0x20000000&(data))>>29)
#define VI_VPD1_vpd_acc_shift                                                        (0)
#define VI_VPD1_vpd_acc_mask                                                         (0x1FFFFFFF)
#define VI_VPD1_vpd_acc(data)                                                        (0x1FFFFFFF&((data)<<0))
#define VI_VPD1_vpd_acc_src(data)                                                    ((0x1FFFFFFF&(data))>>0)
#define VI_VPD1_get_vpd_acc(data)                                                    ((0x1FFFFFFF&(data))>>0)


#define VI_VPD2                                                                      0x180044b8
#define VI_VPD2_reg_addr                                                             "0xB80044B8"
#define VI_VPD2_reg                                                                  0xB80044B8
#define VI_VPD2_inst_adr                                                             "0x002E"
#define VI_VPD2_inst                                                                 0x002E
#define VI_VPD2_vpd_enable_shift                                                     (29)
#define VI_VPD2_vpd_enable_mask                                                      (0x20000000)
#define VI_VPD2_vpd_enable(data)                                                     (0x20000000&((data)<<29))
#define VI_VPD2_vpd_enable_src(data)                                                 ((0x20000000&(data))>>29)
#define VI_VPD2_get_vpd_enable(data)                                                 ((0x20000000&(data))>>29)
#define VI_VPD2_vpd_acc_shift                                                        (0)
#define VI_VPD2_vpd_acc_mask                                                         (0x1FFFFFFF)
#define VI_VPD2_vpd_acc(data)                                                        (0x1FFFFFFF&((data)<<0))
#define VI_VPD2_vpd_acc_src(data)                                                    ((0x1FFFFFFF&(data))>>0)
#define VI_VPD2_get_vpd_acc(data)                                                    ((0x1FFFFFFF&(data))>>0)


#define VI_CVDEN                                                                     0x180044bc
#define VI_CVDEN_reg_addr                                                            "0xB80044BC"
#define VI_CVDEN_reg                                                                 0xB80044BC
#define VI_CVDEN_inst_adr                                                            "0x002F"
#define VI_CVDEN_inst                                                                0x002F
#define VI_CVDEN_write_enable7_shift                                                 (17)
#define VI_CVDEN_write_enable7_mask                                                  (0x00020000)
#define VI_CVDEN_write_enable7(data)                                                 (0x00020000&((data)<<17))
#define VI_CVDEN_write_enable7_src(data)                                             ((0x00020000&(data))>>17)
#define VI_CVDEN_get_write_enable7(data)                                             ((0x00020000&(data))>>17)
#define VI_CVDEN_cvd1_on_shift                                                       (16)
#define VI_CVDEN_cvd1_on_mask                                                        (0x00010000)
#define VI_CVDEN_cvd1_on(data)                                                       (0x00010000&((data)<<16))
#define VI_CVDEN_cvd1_on_src(data)                                                   ((0x00010000&(data))>>16)
#define VI_CVDEN_get_cvd1_on(data)                                                   ((0x00010000&(data))>>16)
#define VI_CVDEN_write_enable8_shift                                                 (15)
#define VI_CVDEN_write_enable8_mask                                                  (0x00008000)
#define VI_CVDEN_write_enable8(data)                                                 (0x00008000&((data)<<15))
#define VI_CVDEN_write_enable8_src(data)                                             ((0x00008000&(data))>>15)
#define VI_CVDEN_get_write_enable8(data)                                             ((0x00008000&(data))>>15)
#define VI_CVDEN_cvd2_on_shift                                                       (14)
#define VI_CVDEN_cvd2_on_mask                                                        (0x00004000)
#define VI_CVDEN_cvd2_on(data)                                                       (0x00004000&((data)<<14))
#define VI_CVDEN_cvd2_on_src(data)                                                   ((0x00004000&(data))>>14)
#define VI_CVDEN_get_cvd2_on(data)                                                   ((0x00004000&(data))>>14)
#define VI_CVDEN_write_enable5_shift                                                 (13)
#define VI_CVDEN_write_enable5_mask                                                  (0x00002000)
#define VI_CVDEN_write_enable5(data)                                                 (0x00002000&((data)<<13))
#define VI_CVDEN_write_enable5_src(data)                                             ((0x00002000&(data))>>13)
#define VI_CVDEN_get_write_enable5(data)                                             ((0x00002000&(data))>>13)
#define VI_CVDEN_hdcvden1_shift                                                      (12)
#define VI_CVDEN_hdcvden1_mask                                                       (0x00001000)
#define VI_CVDEN_hdcvden1(data)                                                      (0x00001000&((data)<<12))
#define VI_CVDEN_hdcvden1_src(data)                                                  ((0x00001000&(data))>>12)
#define VI_CVDEN_get_hdcvden1(data)                                                  ((0x00001000&(data))>>12)
#define VI_CVDEN_write_enable6_shift                                                 (11)
#define VI_CVDEN_write_enable6_mask                                                  (0x00000800)
#define VI_CVDEN_write_enable6(data)                                                 (0x00000800&((data)<<11))
#define VI_CVDEN_write_enable6_src(data)                                             ((0x00000800&(data))>>11)
#define VI_CVDEN_get_write_enable6(data)                                             ((0x00000800&(data))>>11)
#define VI_CVDEN_hdcvden2_shift                                                      (10)
#define VI_CVDEN_hdcvden2_mask                                                       (0x00000400)
#define VI_CVDEN_hdcvden2(data)                                                      (0x00000400&((data)<<10))
#define VI_CVDEN_hdcvden2_src(data)                                                  ((0x00000400&(data))>>10)
#define VI_CVDEN_get_hdcvden2(data)                                                  ((0x00000400&(data))>>10)
#define VI_CVDEN_write_enable1_shift                                                 (9)
#define VI_CVDEN_write_enable1_mask                                                  (0x00000200)
#define VI_CVDEN_write_enable1(data)                                                 (0x00000200&((data)<<9))
#define VI_CVDEN_write_enable1_src(data)                                             ((0x00000200&(data))>>9)
#define VI_CVDEN_get_write_enable1(data)                                             ((0x00000200&(data))>>9)
#define VI_CVDEN_cvden1_shift                                                        (8)
#define VI_CVDEN_cvden1_mask                                                         (0x00000100)
#define VI_CVDEN_cvden1(data)                                                        (0x00000100&((data)<<8))
#define VI_CVDEN_cvden1_src(data)                                                    ((0x00000100&(data))>>8)
#define VI_CVDEN_get_cvden1(data)                                                    ((0x00000100&(data))>>8)
#define VI_CVDEN_write_enable2_shift                                                 (7)
#define VI_CVDEN_write_enable2_mask                                                  (0x00000080)
#define VI_CVDEN_write_enable2(data)                                                 (0x00000080&((data)<<7))
#define VI_CVDEN_write_enable2_src(data)                                             ((0x00000080&(data))>>7)
#define VI_CVDEN_get_write_enable2(data)                                             ((0x00000080&(data))>>7)
#define VI_CVDEN_cvdtp1_shift                                                        (5)
#define VI_CVDEN_cvdtp1_mask                                                         (0x00000060)
#define VI_CVDEN_cvdtp1(data)                                                        (0x00000060&((data)<<5))
#define VI_CVDEN_cvdtp1_src(data)                                                    ((0x00000060&(data))>>5)
#define VI_CVDEN_get_cvdtp1(data)                                                    ((0x00000060&(data))>>5)
#define VI_CVDEN_write_enable3_shift                                                 (4)
#define VI_CVDEN_write_enable3_mask                                                  (0x00000010)
#define VI_CVDEN_write_enable3(data)                                                 (0x00000010&((data)<<4))
#define VI_CVDEN_write_enable3_src(data)                                             ((0x00000010&(data))>>4)
#define VI_CVDEN_get_write_enable3(data)                                             ((0x00000010&(data))>>4)
#define VI_CVDEN_cvden2_shift                                                        (3)
#define VI_CVDEN_cvden2_mask                                                         (0x00000008)
#define VI_CVDEN_cvden2(data)                                                        (0x00000008&((data)<<3))
#define VI_CVDEN_cvden2_src(data)                                                    ((0x00000008&(data))>>3)
#define VI_CVDEN_get_cvden2(data)                                                    ((0x00000008&(data))>>3)
#define VI_CVDEN_write_enable4_shift                                                 (2)
#define VI_CVDEN_write_enable4_mask                                                  (0x00000004)
#define VI_CVDEN_write_enable4(data)                                                 (0x00000004&((data)<<2))
#define VI_CVDEN_write_enable4_src(data)                                             ((0x00000004&(data))>>2)
#define VI_CVDEN_get_write_enable4(data)                                             ((0x00000004&(data))>>2)
#define VI_CVDEN_cvdtp2_shift                                                        (0)
#define VI_CVDEN_cvdtp2_mask                                                         (0x00000003)
#define VI_CVDEN_cvdtp2(data)                                                        (0x00000003&((data)<<0))
#define VI_CVDEN_cvdtp2_src(data)                                                    ((0x00000003&(data))>>0)
#define VI_CVDEN_get_cvdtp2(data)                                                    ((0x00000003&(data))>>0)


#define VI_YDCTL1                                                                    0x18004228
#define VI_YDCTL1_reg_addr                                                           "0xB8004228"
#define VI_YDCTL1_reg                                                                0xB8004228
#define VI_YDCTL1_inst_adr                                                           "0x008A"
#define VI_YDCTL1_inst                                                               0x008A
#define VI_YDCTL1_write_enable4_shift                                                (10)
#define VI_YDCTL1_write_enable4_mask                                                 (0x00000400)
#define VI_YDCTL1_write_enable4(data)                                                (0x00000400&((data)<<10))
#define VI_YDCTL1_write_enable4_src(data)                                            ((0x00000400&(data))>>10)
#define VI_YDCTL1_get_write_enable4(data)                                            ((0x00000400&(data))>>10)
#define VI_YDCTL1_src_sel_shift                                                      (9)
#define VI_YDCTL1_src_sel_mask                                                       (0x00000200)
#define VI_YDCTL1_src_sel(data)                                                      (0x00000200&((data)<<9))
#define VI_YDCTL1_src_sel_src(data)                                                  ((0x00000200&(data))>>9)
#define VI_YDCTL1_get_src_sel(data)                                                  ((0x00000200&(data))>>9)
#define VI_YDCTL1_write_enable5_shift                                                (8)
#define VI_YDCTL1_write_enable5_mask                                                 (0x00000100)
#define VI_YDCTL1_write_enable5(data)                                                (0x00000100&((data)<<8))
#define VI_YDCTL1_write_enable5_src(data)                                            ((0x00000100&(data))>>8)
#define VI_YDCTL1_get_write_enable5(data)                                            ((0x00000100&(data))>>8)
#define VI_YDCTL1_luma_2x_en_shift                                                   (7)
#define VI_YDCTL1_luma_2x_en_mask                                                    (0x00000080)
#define VI_YDCTL1_luma_2x_en(data)                                                   (0x00000080&((data)<<7))
#define VI_YDCTL1_luma_2x_en_src(data)                                               ((0x00000080&(data))>>7)
#define VI_YDCTL1_get_luma_2x_en(data)                                               ((0x00000080&(data))>>7)
#define VI_YDCTL1_write_enable1_shift                                                (6)
#define VI_YDCTL1_write_enable1_mask                                                 (0x00000040)
#define VI_YDCTL1_write_enable1(data)                                                (0x00000040&((data)<<6))
#define VI_YDCTL1_write_enable1_src(data)                                            ((0x00000040&(data))>>6)
#define VI_YDCTL1_get_write_enable1(data)                                            ((0x00000040&(data))>>6)
#define VI_YDCTL1_yden_shift                                                         (5)
#define VI_YDCTL1_yden_mask                                                          (0x00000020)
#define VI_YDCTL1_yden(data)                                                         (0x00000020&((data)<<5))
#define VI_YDCTL1_yden_src(data)                                                     ((0x00000020&(data))>>5)
#define VI_YDCTL1_get_yden(data)                                                     ((0x00000020&(data))>>5)
#define VI_YDCTL1_write_enable2_shift                                                (4)
#define VI_YDCTL1_write_enable2_mask                                                 (0x00000010)
#define VI_YDCTL1_write_enable2(data)                                                (0x00000010&((data)<<4))
#define VI_YDCTL1_write_enable2_src(data)                                            ((0x00000010&(data))>>4)
#define VI_YDCTL1_get_write_enable2(data)                                            ((0x00000010&(data))>>4)
#define VI_YDCTL1_write_enable3_shift                                                (2)
#define VI_YDCTL1_write_enable3_mask                                                 (0x00000004)
#define VI_YDCTL1_write_enable3(data)                                                (0x00000004&((data)<<2))
#define VI_YDCTL1_write_enable3_src(data)                                            ((0x00000004&(data))>>2)
#define VI_YDCTL1_get_write_enable3(data)                                            ((0x00000004&(data))>>2)
#define VI_YDCTL1_ydrtio_shift                                                       (0)
#define VI_YDCTL1_ydrtio_mask                                                        (0x00000003)
#define VI_YDCTL1_ydrtio(data)                                                       (0x00000003&((data)<<0))
#define VI_YDCTL1_ydrtio_src(data)                                                   ((0x00000003&(data))>>0)
#define VI_YDCTL1_get_ydrtio(data)                                                   ((0x00000003&(data))>>0)


#define VI_YDCTL2                                                                    0x180044c0
#define VI_YDCTL2_reg_addr                                                           "0xB80044C0"
#define VI_YDCTL2_reg                                                                0xB80044C0
#define VI_YDCTL2_inst_adr                                                           "0x0030"
#define VI_YDCTL2_inst                                                               0x0030
#define VI_YDCTL2_write_enable4_shift                                                (10)
#define VI_YDCTL2_write_enable4_mask                                                 (0x00000400)
#define VI_YDCTL2_write_enable4(data)                                                (0x00000400&((data)<<10))
#define VI_YDCTL2_write_enable4_src(data)                                            ((0x00000400&(data))>>10)
#define VI_YDCTL2_get_write_enable4(data)                                            ((0x00000400&(data))>>10)
#define VI_YDCTL2_src_sel_shift                                                      (9)
#define VI_YDCTL2_src_sel_mask                                                       (0x00000200)
#define VI_YDCTL2_src_sel(data)                                                      (0x00000200&((data)<<9))
#define VI_YDCTL2_src_sel_src(data)                                                  ((0x00000200&(data))>>9)
#define VI_YDCTL2_get_src_sel(data)                                                  ((0x00000200&(data))>>9)
#define VI_YDCTL2_write_enable5_shift                                                (8)
#define VI_YDCTL2_write_enable5_mask                                                 (0x00000100)
#define VI_YDCTL2_write_enable5(data)                                                (0x00000100&((data)<<8))
#define VI_YDCTL2_write_enable5_src(data)                                            ((0x00000100&(data))>>8)
#define VI_YDCTL2_get_write_enable5(data)                                            ((0x00000100&(data))>>8)
#define VI_YDCTL2_luma_2x_en_shift                                                   (7)
#define VI_YDCTL2_luma_2x_en_mask                                                    (0x00000080)
#define VI_YDCTL2_luma_2x_en(data)                                                   (0x00000080&((data)<<7))
#define VI_YDCTL2_luma_2x_en_src(data)                                               ((0x00000080&(data))>>7)
#define VI_YDCTL2_get_luma_2x_en(data)                                               ((0x00000080&(data))>>7)
#define VI_YDCTL2_write_enable1_shift                                                (6)
#define VI_YDCTL2_write_enable1_mask                                                 (0x00000040)
#define VI_YDCTL2_write_enable1(data)                                                (0x00000040&((data)<<6))
#define VI_YDCTL2_write_enable1_src(data)                                            ((0x00000040&(data))>>6)
#define VI_YDCTL2_get_write_enable1(data)                                            ((0x00000040&(data))>>6)
#define VI_YDCTL2_yden_shift                                                         (5)
#define VI_YDCTL2_yden_mask                                                          (0x00000020)
#define VI_YDCTL2_yden(data)                                                         (0x00000020&((data)<<5))
#define VI_YDCTL2_yden_src(data)                                                     ((0x00000020&(data))>>5)
#define VI_YDCTL2_get_yden(data)                                                     ((0x00000020&(data))>>5)
#define VI_YDCTL2_write_enable2_shift                                                (4)
#define VI_YDCTL2_write_enable2_mask                                                 (0x00000010)
#define VI_YDCTL2_write_enable2(data)                                                (0x00000010&((data)<<4))
#define VI_YDCTL2_write_enable2_src(data)                                            ((0x00000010&(data))>>4)
#define VI_YDCTL2_get_write_enable2(data)                                            ((0x00000010&(data))>>4)
#define VI_YDCTL2_write_enable3_shift                                                (2)
#define VI_YDCTL2_write_enable3_mask                                                 (0x00000004)
#define VI_YDCTL2_write_enable3(data)                                                (0x00000004&((data)<<2))
#define VI_YDCTL2_write_enable3_src(data)                                            ((0x00000004&(data))>>2)
#define VI_YDCTL2_get_write_enable3(data)                                            ((0x00000004&(data))>>2)
#define VI_YDCTL2_ydrtio_shift                                                       (0)
#define VI_YDCTL2_ydrtio_mask                                                        (0x00000003)
#define VI_YDCTL2_ydrtio(data)                                                       (0x00000003&((data)<<0))
#define VI_YDCTL2_ydrtio_src(data)                                                   ((0x00000003&(data))>>0)
#define VI_YDCTL2_get_ydrtio(data)                                                   ((0x00000003&(data))>>0)


#define VI_DMACTL                                                                    0x1800422c
#define VI_DMACTL_reg_addr                                                           "0xB800422C"
#define VI_DMACTL_reg                                                                0xB800422C
#define VI_DMACTL_inst_adr                                                           "0x008B"
#define VI_DMACTL_inst                                                               0x008B
#define VI_DMACTL_write_enable1_shift                                                (11)
#define VI_DMACTL_write_enable1_mask                                                 (0x00000800)
#define VI_DMACTL_write_enable1(data)                                                (0x00000800&((data)<<11))
#define VI_DMACTL_write_enable1_src(data)                                            ((0x00000800&(data))>>11)
#define VI_DMACTL_get_write_enable1(data)                                            ((0x00000800&(data))>>11)
#define VI_DMACTL_dmaen1_shift                                                       (10)
#define VI_DMACTL_dmaen1_mask                                                        (0x00000400)
#define VI_DMACTL_dmaen1(data)                                                       (0x00000400&((data)<<10))
#define VI_DMACTL_dmaen1_src(data)                                                   ((0x00000400&(data))>>10)
#define VI_DMACTL_get_dmaen1(data)                                                   ((0x00000400&(data))>>10)
#define VI_DMACTL_write_enable2_shift                                                (9)
#define VI_DMACTL_write_enable2_mask                                                 (0x00000200)
#define VI_DMACTL_write_enable2(data)                                                (0x00000200&((data)<<9))
#define VI_DMACTL_write_enable2_src(data)                                            ((0x00000200&(data))>>9)
#define VI_DMACTL_get_write_enable2(data)                                            ((0x00000200&(data))>>9)
#define VI_DMACTL_dmaen2_shift                                                       (8)
#define VI_DMACTL_dmaen2_mask                                                        (0x00000100)
#define VI_DMACTL_dmaen2(data)                                                       (0x00000100&((data)<<8))
#define VI_DMACTL_dmaen2_src(data)                                                   ((0x00000100&(data))>>8)
#define VI_DMACTL_get_dmaen2(data)                                                   ((0x00000100&(data))>>8)
#define VI_DMACTL_write_enable4_shift                                                (7)
#define VI_DMACTL_write_enable4_mask                                                 (0x00000080)
#define VI_DMACTL_write_enable4(data)                                                (0x00000080&((data)<<7))
#define VI_DMACTL_write_enable4_src(data)                                            ((0x00000080&(data))>>7)
#define VI_DMACTL_get_write_enable4(data)                                            ((0x00000080&(data))>>7)
#define VI_DMACTL_hddmaen1_shift                                                     (6)
#define VI_DMACTL_hddmaen1_mask                                                      (0x00000040)
#define VI_DMACTL_hddmaen1(data)                                                     (0x00000040&((data)<<6))
#define VI_DMACTL_hddmaen1_src(data)                                                 ((0x00000040&(data))>>6)
#define VI_DMACTL_get_hddmaen1(data)                                                 ((0x00000040&(data))>>6)
#define VI_DMACTL_write_enable5_shift                                                (5)
#define VI_DMACTL_write_enable5_mask                                                 (0x00000020)
#define VI_DMACTL_write_enable5(data)                                                (0x00000020&((data)<<5))
#define VI_DMACTL_write_enable5_src(data)                                            ((0x00000020&(data))>>5)
#define VI_DMACTL_get_write_enable5(data)                                            ((0x00000020&(data))>>5)
#define VI_DMACTL_hddmaen2_shift                                                     (4)
#define VI_DMACTL_hddmaen2_mask                                                      (0x00000010)
#define VI_DMACTL_hddmaen2(data)                                                     (0x00000010&((data)<<4))
#define VI_DMACTL_hddmaen2_src(data)                                                 ((0x00000010&(data))>>4)
#define VI_DMACTL_get_hddmaen2(data)                                                 ((0x00000010&(data))>>4)
#define VI_DMACTL_write_enable3_shift                                                (3)
#define VI_DMACTL_write_enable3_mask                                                 (0x00000008)
#define VI_DMACTL_write_enable3(data)                                                (0x00000008&((data)<<3))
#define VI_DMACTL_write_enable3_src(data)                                            ((0x00000008&(data))>>3)
#define VI_DMACTL_get_write_enable3(data)                                            ((0x00000008&(data))>>3)
#define VI_DMACTL_bstlen_shift                                                       (0)
#define VI_DMACTL_bstlen_mask                                                        (0x00000007)
#define VI_DMACTL_bstlen(data)                                                       (0x00000007&((data)<<0))
#define VI_DMACTL_bstlen_src(data)                                                   ((0x00000007&(data))>>0)
#define VI_DMACTL_get_bstlen(data)                                                   ((0x00000007&(data))>>0)


#define VI_VBI1BUF                                                                   0x1800429c
#define VI_VBI1BUF_reg_addr                                                          "0xB800429C"
#define VI_VBI1BUF_reg                                                               0xB800429C
#define VI_VBI1BUF_inst_adr                                                          "0x00A7"
#define VI_VBI1BUF_inst                                                              0x00A7
#define VI_VBI1BUF_write_enable1_shift                                               (6)
#define VI_VBI1BUF_write_enable1_mask                                                (0x00000040)
#define VI_VBI1BUF_write_enable1(data)                                               (0x00000040&((data)<<6))
#define VI_VBI1BUF_write_enable1_src(data)                                           ((0x00000040&(data))>>6)
#define VI_VBI1BUF_get_write_enable1(data)                                           ((0x00000040&(data))>>6)
#define VI_VBI1BUF_thd_shift                                                         (0)
#define VI_VBI1BUF_thd_mask                                                          (0x0000003F)
#define VI_VBI1BUF_thd(data)                                                         (0x0000003F&((data)<<0))
#define VI_VBI1BUF_thd_src(data)                                                     ((0x0000003F&(data))>>0)
#define VI_VBI1BUF_get_thd(data)                                                     ((0x0000003F&(data))>>0)


#define VI_VBI2BUF                                                                   0x180042a0
#define VI_VBI2BUF_reg_addr                                                          "0xB80042A0"
#define VI_VBI2BUF_reg                                                               0xB80042A0
#define VI_VBI2BUF_inst_adr                                                          "0x00A8"
#define VI_VBI2BUF_inst                                                              0x00A8
#define VI_VBI2BUF_write_enable1_shift                                               (6)
#define VI_VBI2BUF_write_enable1_mask                                                (0x00000040)
#define VI_VBI2BUF_write_enable1(data)                                               (0x00000040&((data)<<6))
#define VI_VBI2BUF_write_enable1_src(data)                                           ((0x00000040&(data))>>6)
#define VI_VBI2BUF_get_write_enable1(data)                                           ((0x00000040&(data))>>6)
#define VI_VBI2BUF_thd_shift                                                         (0)
#define VI_VBI2BUF_thd_mask                                                          (0x0000003F)
#define VI_VBI2BUF_thd(data)                                                         (0x0000003F&((data)<<0))
#define VI_VBI2BUF_thd_src(data)                                                     ((0x0000003F&(data))>>0)
#define VI_VBI2BUF_get_thd(data)                                                     ((0x0000003F&(data))>>0)


#define VI_HDY1BUF                                                                   0x18004480
#define VI_HDY1BUF_reg_addr                                                          "0xB8004480"
#define VI_HDY1BUF_reg                                                               0xB8004480
#define VI_HDY1BUF_inst_adr                                                          "0x0020"
#define VI_HDY1BUF_inst                                                              0x0020
#define VI_HDY1BUF_write_enable1_shift                                               (16)
#define VI_HDY1BUF_write_enable1_mask                                                (0x00010000)
#define VI_HDY1BUF_write_enable1(data)                                               (0x00010000&((data)<<16))
#define VI_HDY1BUF_write_enable1_src(data)                                           ((0x00010000&(data))>>16)
#define VI_HDY1BUF_get_write_enable1(data)                                           ((0x00010000&(data))>>16)
#define VI_HDY1BUF_thd_shift                                                         (10)
#define VI_HDY1BUF_thd_mask                                                          (0x0000FC00)
#define VI_HDY1BUF_thd(data)                                                         (0x0000FC00&((data)<<10))
#define VI_HDY1BUF_thd_src(data)                                                     ((0x0000FC00&(data))>>10)
#define VI_HDY1BUF_get_thd(data)                                                     ((0x0000FC00&(data))>>10)


#define VI_HDY2BUF                                                                   0x18004484
#define VI_HDY2BUF_reg_addr                                                          "0xB8004484"
#define VI_HDY2BUF_reg                                                               0xB8004484
#define VI_HDY2BUF_inst_adr                                                          "0x0021"
#define VI_HDY2BUF_inst                                                              0x0021
#define VI_HDY2BUF_write_enable1_shift                                               (26)
#define VI_HDY2BUF_write_enable1_mask                                                (0x04000000)
#define VI_HDY2BUF_write_enable1(data)                                               (0x04000000&((data)<<26))
#define VI_HDY2BUF_write_enable1_src(data)                                           ((0x04000000&(data))>>26)
#define VI_HDY2BUF_get_write_enable1(data)                                           ((0x04000000&(data))>>26)
#define VI_HDY2BUF_thd_shift                                                         (20)
#define VI_HDY2BUF_thd_mask                                                          (0x03F00000)
#define VI_HDY2BUF_thd(data)                                                         (0x03F00000&((data)<<20))
#define VI_HDY2BUF_thd_src(data)                                                     ((0x03F00000&(data))>>20)
#define VI_HDY2BUF_get_thd(data)                                                     ((0x03F00000&(data))>>20)


#define VI_HDC1BUF                                                                   0x18004488
#define VI_HDC1BUF_reg_addr                                                          "0xB8004488"
#define VI_HDC1BUF_reg                                                               0xB8004488
#define VI_HDC1BUF_inst_adr                                                          "0x0022"
#define VI_HDC1BUF_inst                                                              0x0022
#define VI_HDC1BUF_write_enable1_shift                                               (26)
#define VI_HDC1BUF_write_enable1_mask                                                (0x04000000)
#define VI_HDC1BUF_write_enable1(data)                                               (0x04000000&((data)<<26))
#define VI_HDC1BUF_write_enable1_src(data)                                           ((0x04000000&(data))>>26)
#define VI_HDC1BUF_get_write_enable1(data)                                           ((0x04000000&(data))>>26)
#define VI_HDC1BUF_thd_shift                                                         (20)
#define VI_HDC1BUF_thd_mask                                                          (0x03F00000)
#define VI_HDC1BUF_thd(data)                                                         (0x03F00000&((data)<<20))
#define VI_HDC1BUF_thd_src(data)                                                     ((0x03F00000&(data))>>20)
#define VI_HDC1BUF_get_thd(data)                                                     ((0x03F00000&(data))>>20)


#define VI_HDC2BUF                                                                   0x1800448c
#define VI_HDC2BUF_reg_addr                                                          "0xB800448C"
#define VI_HDC2BUF_reg                                                               0xB800448C
#define VI_HDC2BUF_inst_adr                                                          "0x0023"
#define VI_HDC2BUF_inst                                                              0x0023
#define VI_HDC2BUF_write_enable1_shift                                               (26)
#define VI_HDC2BUF_write_enable1_mask                                                (0x04000000)
#define VI_HDC2BUF_write_enable1(data)                                               (0x04000000&((data)<<26))
#define VI_HDC2BUF_write_enable1_src(data)                                           ((0x04000000&(data))>>26)
#define VI_HDC2BUF_get_write_enable1(data)                                           ((0x04000000&(data))>>26)
#define VI_HDC2BUF_thd_shift                                                         (20)
#define VI_HDC2BUF_thd_mask                                                          (0x03F00000)
#define VI_HDC2BUF_thd(data)                                                         (0x03F00000&((data)<<20))
#define VI_HDC2BUF_thd_src(data)                                                     ((0x03F00000&(data))>>20)
#define VI_HDC2BUF_get_thd(data)                                                     ((0x03F00000&(data))>>20)


#define VI_Y1BUF                                                                     0x18004230
#define VI_Y1BUF_reg_addr                                                            "0xB8004230"
#define VI_Y1BUF_reg                                                                 0xB8004230
#define VI_Y1BUF_inst_adr                                                            "0x008C"
#define VI_Y1BUF_inst                                                                0x008C
#define VI_Y1BUF_write_enable1_shift                                                 (16)
#define VI_Y1BUF_write_enable1_mask                                                  (0x00010000)
#define VI_Y1BUF_write_enable1(data)                                                 (0x00010000&((data)<<16))
#define VI_Y1BUF_write_enable1_src(data)                                             ((0x00010000&(data))>>16)
#define VI_Y1BUF_get_write_enable1(data)                                             ((0x00010000&(data))>>16)
#define VI_Y1BUF_thd_shift                                                           (10)
#define VI_Y1BUF_thd_mask                                                            (0x0000FC00)
#define VI_Y1BUF_thd(data)                                                           (0x0000FC00&((data)<<10))
#define VI_Y1BUF_thd_src(data)                                                       ((0x0000FC00&(data))>>10)
#define VI_Y1BUF_get_thd(data)                                                       ((0x0000FC00&(data))>>10)


#define VI_Y2BUF                                                                     0x18004234
#define VI_Y2BUF_reg_addr                                                            "0xB8004234"
#define VI_Y2BUF_reg                                                                 0xB8004234
#define VI_Y2BUF_inst_adr                                                            "0x008D"
#define VI_Y2BUF_inst                                                                0x008D
#define VI_Y2BUF_write_enable1_shift                                                 (26)
#define VI_Y2BUF_write_enable1_mask                                                  (0x04000000)
#define VI_Y2BUF_write_enable1(data)                                                 (0x04000000&((data)<<26))
#define VI_Y2BUF_write_enable1_src(data)                                             ((0x04000000&(data))>>26)
#define VI_Y2BUF_get_write_enable1(data)                                             ((0x04000000&(data))>>26)
#define VI_Y2BUF_thd_shift                                                           (20)
#define VI_Y2BUF_thd_mask                                                            (0x03F00000)
#define VI_Y2BUF_thd(data)                                                           (0x03F00000&((data)<<20))
#define VI_Y2BUF_thd_src(data)                                                       ((0x03F00000&(data))>>20)
#define VI_Y2BUF_get_thd(data)                                                       ((0x03F00000&(data))>>20)


#define VI_C1BUF                                                                     0x18004238
#define VI_C1BUF_reg_addr                                                            "0xB8004238"
#define VI_C1BUF_reg                                                                 0xB8004238
#define VI_C1BUF_inst_adr                                                            "0x008E"
#define VI_C1BUF_inst                                                                0x008E
#define VI_C1BUF_write_enable1_shift                                                 (26)
#define VI_C1BUF_write_enable1_mask                                                  (0x04000000)
#define VI_C1BUF_write_enable1(data)                                                 (0x04000000&((data)<<26))
#define VI_C1BUF_write_enable1_src(data)                                             ((0x04000000&(data))>>26)
#define VI_C1BUF_get_write_enable1(data)                                             ((0x04000000&(data))>>26)
#define VI_C1BUF_thd_shift                                                           (20)
#define VI_C1BUF_thd_mask                                                            (0x03F00000)
#define VI_C1BUF_thd(data)                                                           (0x03F00000&((data)<<20))
#define VI_C1BUF_thd_src(data)                                                       ((0x03F00000&(data))>>20)
#define VI_C1BUF_get_thd(data)                                                       ((0x03F00000&(data))>>20)


#define VI_C2BUF                                                                     0x1800423c
#define VI_C2BUF_reg_addr                                                            "0xB800423C"
#define VI_C2BUF_reg                                                                 0xB800423C
#define VI_C2BUF_inst_adr                                                            "0x008F"
#define VI_C2BUF_inst                                                                0x008F
#define VI_C2BUF_write_enable1_shift                                                 (26)
#define VI_C2BUF_write_enable1_mask                                                  (0x04000000)
#define VI_C2BUF_write_enable1(data)                                                 (0x04000000&((data)<<26))
#define VI_C2BUF_write_enable1_src(data)                                             ((0x04000000&(data))>>26)
#define VI_C2BUF_get_write_enable1(data)                                             ((0x04000000&(data))>>26)
#define VI_C2BUF_thd_shift                                                           (20)
#define VI_C2BUF_thd_mask                                                            (0x03F00000)
#define VI_C2BUF_thd(data)                                                           (0x03F00000&((data)<<20))
#define VI_C2BUF_thd_src(data)                                                       ((0x03F00000&(data))>>20)
#define VI_C2BUF_get_thd(data)                                                       ((0x03F00000&(data))>>20)


#define VI_YDBUF                                                                     0x18004240
#define VI_YDBUF_reg_addr                                                            "0xB8004240"
#define VI_YDBUF_reg                                                                 0xB8004240
#define VI_YDBUF_inst_adr                                                            "0x0090"
#define VI_YDBUF_inst                                                                0x0090
#define VI_YDBUF_write_enable1_shift                                                 (26)
#define VI_YDBUF_write_enable1_mask                                                  (0x04000000)
#define VI_YDBUF_write_enable1(data)                                                 (0x04000000&((data)<<26))
#define VI_YDBUF_write_enable1_src(data)                                             ((0x04000000&(data))>>26)
#define VI_YDBUF_get_write_enable1(data)                                             ((0x04000000&(data))>>26)
#define VI_YDBUF_thd1_shift                                                          (20)
#define VI_YDBUF_thd1_mask                                                           (0x03F00000)
#define VI_YDBUF_thd1(data)                                                          (0x03F00000&((data)<<20))
#define VI_YDBUF_thd1_src(data)                                                      ((0x03F00000&(data))>>20)
#define VI_YDBUF_get_thd1(data)                                                      ((0x03F00000&(data))>>20)
#define VI_YDBUF_write_enable2_shift                                                 (19)
#define VI_YDBUF_write_enable2_mask                                                  (0x00080000)
#define VI_YDBUF_write_enable2(data)                                                 (0x00080000&((data)<<19))
#define VI_YDBUF_write_enable2_src(data)                                             ((0x00080000&(data))>>19)
#define VI_YDBUF_get_write_enable2(data)                                             ((0x00080000&(data))>>19)
#define VI_YDBUF_thd2_shift                                                          (13)
#define VI_YDBUF_thd2_mask                                                           (0x0007E000)
#define VI_YDBUF_thd2(data)                                                          (0x0007E000&((data)<<13))
#define VI_YDBUF_thd2_src(data)                                                      ((0x0007E000&(data))>>13)
#define VI_YDBUF_get_thd2(data)                                                      ((0x0007E000&(data))>>13)


#define VI_VBISCADR1F0                                                               0x18004510
#define VI_VBISCADR1F0_reg_addr                                                      "0xB8004510"
#define VI_VBISCADR1F0_reg                                                           0xB8004510
#define VI_VBISCADR1F0_inst_adr                                                      "0x0044"
#define VI_VBISCADR1F0_inst                                                          0x0044
#define VI_VBISCADR1F0_addr_shift                                                    (0)
#define VI_VBISCADR1F0_addr_mask                                                     (0x0FFFFFFF)
#define VI_VBISCADR1F0_addr(data)                                                    (0x0FFFFFFF&((data)<<0))
#define VI_VBISCADR1F0_addr_src(data)                                                ((0x0FFFFFFF&(data))>>0)
#define VI_VBISCADR1F0_get_addr(data)                                                ((0x0FFFFFFF&(data))>>0)


#define VI_VBISCADR1F1                                                               0x18004514
#define VI_VBISCADR1F1_reg_addr                                                      "0xB8004514"
#define VI_VBISCADR1F1_reg                                                           0xB8004514
#define VI_VBISCADR1F1_inst_adr                                                      "0x0045"
#define VI_VBISCADR1F1_inst                                                          0x0045
#define VI_VBISCADR1F1_addr_shift                                                    (0)
#define VI_VBISCADR1F1_addr_mask                                                     (0x0FFFFFFF)
#define VI_VBISCADR1F1_addr(data)                                                    (0x0FFFFFFF&((data)<<0))
#define VI_VBISCADR1F1_addr_src(data)                                                ((0x0FFFFFFF&(data))>>0)
#define VI_VBISCADR1F1_get_addr(data)                                                ((0x0FFFFFFF&(data))>>0)


#define VI_VBISCADR2F0                                                               0x18004518
#define VI_VBISCADR2F0_reg_addr                                                      "0xB8004518"
#define VI_VBISCADR2F0_reg                                                           0xB8004518
#define VI_VBISCADR2F0_inst_adr                                                      "0x0046"
#define VI_VBISCADR2F0_inst                                                          0x0046
#define VI_VBISCADR2F0_addr_shift                                                    (0)
#define VI_VBISCADR2F0_addr_mask                                                     (0x0FFFFFFF)
#define VI_VBISCADR2F0_addr(data)                                                    (0x0FFFFFFF&((data)<<0))
#define VI_VBISCADR2F0_addr_src(data)                                                ((0x0FFFFFFF&(data))>>0)
#define VI_VBISCADR2F0_get_addr(data)                                                ((0x0FFFFFFF&(data))>>0)


#define VI_VBISCADR2F1                                                               0x1800451c
#define VI_VBISCADR2F1_reg_addr                                                      "0xB800451C"
#define VI_VBISCADR2F1_reg                                                           0xB800451C
#define VI_VBISCADR2F1_inst_adr                                                      "0x0047"
#define VI_VBISCADR2F1_inst                                                          0x0047
#define VI_VBISCADR2F1_addr_shift                                                    (0)
#define VI_VBISCADR2F1_addr_mask                                                     (0x0FFFFFFF)
#define VI_VBISCADR2F1_addr(data)                                                    (0x0FFFFFFF&((data)<<0))
#define VI_VBISCADR2F1_addr_src(data)                                                ((0x0FFFFFFF&(data))>>0)
#define VI_VBISCADR2F1_get_addr(data)                                                ((0x0FFFFFFF&(data))>>0)


#define VI_VBISCLEN1F0                                                               0x18004520
#define VI_VBISCLEN1F0_reg_addr                                                      "0xB8004520"
#define VI_VBISCLEN1F0_reg                                                           0xB8004520
#define VI_VBISCLEN1F0_inst_adr                                                      "0x0048"
#define VI_VBISCLEN1F0_inst                                                          0x0048
#define VI_VBISCLEN1F0_length_shift                                                  (0)
#define VI_VBISCLEN1F0_length_mask                                                   (0x0003FFFF)
#define VI_VBISCLEN1F0_length(data)                                                  (0x0003FFFF&((data)<<0))
#define VI_VBISCLEN1F0_length_src(data)                                              ((0x0003FFFF&(data))>>0)
#define VI_VBISCLEN1F0_get_length(data)                                              ((0x0003FFFF&(data))>>0)


#define VI_VBISCLEN1F1                                                               0x18004524
#define VI_VBISCLEN1F1_reg_addr                                                      "0xB8004524"
#define VI_VBISCLEN1F1_reg                                                           0xB8004524
#define VI_VBISCLEN1F1_inst_adr                                                      "0x0049"
#define VI_VBISCLEN1F1_inst                                                          0x0049
#define VI_VBISCLEN1F1_length_shift                                                  (0)
#define VI_VBISCLEN1F1_length_mask                                                   (0x0003FFFF)
#define VI_VBISCLEN1F1_length(data)                                                  (0x0003FFFF&((data)<<0))
#define VI_VBISCLEN1F1_length_src(data)                                              ((0x0003FFFF&(data))>>0)
#define VI_VBISCLEN1F1_get_length(data)                                              ((0x0003FFFF&(data))>>0)


#define VI_VBISCLEN2F0                                                               0x18004528
#define VI_VBISCLEN2F0_reg_addr                                                      "0xB8004528"
#define VI_VBISCLEN2F0_reg                                                           0xB8004528
#define VI_VBISCLEN2F0_inst_adr                                                      "0x004A"
#define VI_VBISCLEN2F0_inst                                                          0x004A
#define VI_VBISCLEN2F0_length_shift                                                  (0)
#define VI_VBISCLEN2F0_length_mask                                                   (0x0003FFFF)
#define VI_VBISCLEN2F0_length(data)                                                  (0x0003FFFF&((data)<<0))
#define VI_VBISCLEN2F0_length_src(data)                                              ((0x0003FFFF&(data))>>0)
#define VI_VBISCLEN2F0_get_length(data)                                              ((0x0003FFFF&(data))>>0)


#define VI_VBISCLEN2F1                                                               0x1800452c
#define VI_VBISCLEN2F1_reg_addr                                                      "0xB800452C"
#define VI_VBISCLEN2F1_reg                                                           0xB800452C
#define VI_VBISCLEN2F1_inst_adr                                                      "0x004B"
#define VI_VBISCLEN2F1_inst                                                          0x004B
#define VI_VBISCLEN2F1_length_shift                                                  (0)
#define VI_VBISCLEN2F1_length_mask                                                   (0x0003FFFF)
#define VI_VBISCLEN2F1_length(data)                                                  (0x0003FFFF&((data)<<0))
#define VI_VBISCLEN2F1_length_src(data)                                              ((0x0003FFFF&(data))>>0)
#define VI_VBISCLEN2F1_get_length(data)                                              ((0x0003FFFF&(data))>>0)


#define VI_VBIADR1F0                                                                 0x180042a4
#define VI_VBIADR1F0_reg_addr                                                        "0xB80042A4"
#define VI_VBIADR1F0_reg                                                             0xB80042A4
#define VI_VBIADR1F0_inst_adr                                                        "0x00A9"
#define VI_VBIADR1F0_inst                                                            0x00A9
#define VI_VBIADR1F0_addr_shift                                                      (0)
#define VI_VBIADR1F0_addr_mask                                                       (0x0FFFFFFF)
#define VI_VBIADR1F0_addr(data)                                                      (0x0FFFFFFF&((data)<<0))
#define VI_VBIADR1F0_addr_src(data)                                                  ((0x0FFFFFFF&(data))>>0)
#define VI_VBIADR1F0_get_addr(data)                                                  ((0x0FFFFFFF&(data))>>0)


#define VI_VBIADR1F1                                                                 0x180044e0
#define VI_VBIADR1F1_reg_addr                                                        "0xB80044E0"
#define VI_VBIADR1F1_reg                                                             0xB80044E0
#define VI_VBIADR1F1_inst_adr                                                        "0x0038"
#define VI_VBIADR1F1_inst                                                            0x0038
#define VI_VBIADR1F1_addr_shift                                                      (0)
#define VI_VBIADR1F1_addr_mask                                                       (0x0FFFFFFF)
#define VI_VBIADR1F1_addr(data)                                                      (0x0FFFFFFF&((data)<<0))
#define VI_VBIADR1F1_addr_src(data)                                                  ((0x0FFFFFFF&(data))>>0)
#define VI_VBIADR1F1_get_addr(data)                                                  ((0x0FFFFFFF&(data))>>0)


#define VI_VBILEN1F0                                                                 0x180042a8
#define VI_VBILEN1F0_reg_addr                                                        "0xB80042A8"
#define VI_VBILEN1F0_reg                                                             0xB80042A8
#define VI_VBILEN1F0_inst_adr                                                        "0x00AA"
#define VI_VBILEN1F0_inst                                                            0x00AA
#define VI_VBILEN1F0_length_shift                                                    (0)
#define VI_VBILEN1F0_length_mask                                                     (0x0003FFFF)
#define VI_VBILEN1F0_length(data)                                                    (0x0003FFFF&((data)<<0))
#define VI_VBILEN1F0_length_src(data)                                                ((0x0003FFFF&(data))>>0)
#define VI_VBILEN1F0_get_length(data)                                                ((0x0003FFFF&(data))>>0)


#define VI_VBILEN1F1                                                                 0x180044e4
#define VI_VBILEN1F1_reg_addr                                                        "0xB80044E4"
#define VI_VBILEN1F1_reg                                                             0xB80044E4
#define VI_VBILEN1F1_inst_adr                                                        "0x0039"
#define VI_VBILEN1F1_inst                                                            0x0039
#define VI_VBILEN1F1_length_shift                                                    (0)
#define VI_VBILEN1F1_length_mask                                                     (0x0003FFFF)
#define VI_VBILEN1F1_length(data)                                                    (0x0003FFFF&((data)<<0))
#define VI_VBILEN1F1_length_src(data)                                                ((0x0003FFFF&(data))>>0)
#define VI_VBILEN1F1_get_length(data)                                                ((0x0003FFFF&(data))>>0)


#define VI_VBIADR2F0                                                                 0x180042ac
#define VI_VBIADR2F0_reg_addr                                                        "0xB80042AC"
#define VI_VBIADR2F0_reg                                                             0xB80042AC
#define VI_VBIADR2F0_inst_adr                                                        "0x00AB"
#define VI_VBIADR2F0_inst                                                            0x00AB
#define VI_VBIADR2F0_addr_shift                                                      (0)
#define VI_VBIADR2F0_addr_mask                                                       (0x0FFFFFFF)
#define VI_VBIADR2F0_addr(data)                                                      (0x0FFFFFFF&((data)<<0))
#define VI_VBIADR2F0_addr_src(data)                                                  ((0x0FFFFFFF&(data))>>0)
#define VI_VBIADR2F0_get_addr(data)                                                  ((0x0FFFFFFF&(data))>>0)


#define VI_VBIADR2F1                                                                 0x180044e8
#define VI_VBIADR2F1_reg_addr                                                        "0xB80044E8"
#define VI_VBIADR2F1_reg                                                             0xB80044E8
#define VI_VBIADR2F1_inst_adr                                                        "0x003A"
#define VI_VBIADR2F1_inst                                                            0x003A
#define VI_VBIADR2F1_addr_shift                                                      (0)
#define VI_VBIADR2F1_addr_mask                                                       (0x0FFFFFFF)
#define VI_VBIADR2F1_addr(data)                                                      (0x0FFFFFFF&((data)<<0))
#define VI_VBIADR2F1_addr_src(data)                                                  ((0x0FFFFFFF&(data))>>0)
#define VI_VBIADR2F1_get_addr(data)                                                  ((0x0FFFFFFF&(data))>>0)


#define VI_VBILEN2F0                                                                 0x180042b0
#define VI_VBILEN2F0_reg_addr                                                        "0xB80042B0"
#define VI_VBILEN2F0_reg                                                             0xB80042B0
#define VI_VBILEN2F0_inst_adr                                                        "0x00AC"
#define VI_VBILEN2F0_inst                                                            0x00AC
#define VI_VBILEN2F0_length_shift                                                    (0)
#define VI_VBILEN2F0_length_mask                                                     (0x0003FFFF)
#define VI_VBILEN2F0_length(data)                                                    (0x0003FFFF&((data)<<0))
#define VI_VBILEN2F0_length_src(data)                                                ((0x0003FFFF&(data))>>0)
#define VI_VBILEN2F0_get_length(data)                                                ((0x0003FFFF&(data))>>0)


#define VI_VBILEN2F1                                                                 0x180044ec
#define VI_VBILEN2F1_reg_addr                                                        "0xB80044EC"
#define VI_VBILEN2F1_reg                                                             0xB80044EC
#define VI_VBILEN2F1_inst_adr                                                        "0x003B"
#define VI_VBILEN2F1_inst                                                            0x003B
#define VI_VBILEN2F1_length_shift                                                    (0)
#define VI_VBILEN2F1_length_mask                                                     (0x0003FFFF)
#define VI_VBILEN2F1_length(data)                                                    (0x0003FFFF&((data)<<0))
#define VI_VBILEN2F1_length_src(data)                                                ((0x0003FFFF&(data))>>0)
#define VI_VBILEN2F1_get_length(data)                                                ((0x0003FFFF&(data))>>0)


#define VI_DMACTL1                                                                   0x1800424c
#define VI_DMACTL1_reg_addr                                                          "0xB800424C"
#define VI_DMACTL1_reg                                                               0xB800424C
#define VI_DMACTL1_inst_adr                                                          "0x0093"
#define VI_DMACTL1_inst                                                              0x0093
#define VI_DMACTL1_write_enable2_shift                                               (31)
#define VI_DMACTL1_write_enable2_mask                                                (0x80000000)
#define VI_DMACTL1_write_enable2(data)                                               (0x80000000&((data)<<31))
#define VI_DMACTL1_write_enable2_src(data)                                           ((0x80000000&(data))>>31)
#define VI_DMACTL1_get_write_enable2(data)                                           ((0x80000000&(data))>>31)
#define VI_DMACTL1_yads_shift                                                        (24)
#define VI_DMACTL1_yads_mask                                                         (0x7F000000)
#define VI_DMACTL1_yads(data)                                                        (0x7F000000&((data)<<24))
#define VI_DMACTL1_yads_src(data)                                                    ((0x7F000000&(data))>>24)
#define VI_DMACTL1_get_yads(data)                                                    ((0x7F000000&(data))>>24)
#define VI_DMACTL1_write_enable3_shift                                               (23)
#define VI_DMACTL1_write_enable3_mask                                                (0x00800000)
#define VI_DMACTL1_write_enable3(data)                                               (0x00800000&((data)<<23))
#define VI_DMACTL1_write_enable3_src(data)                                           ((0x00800000&(data))>>23)
#define VI_DMACTL1_get_write_enable3(data)                                           ((0x00800000&(data))>>23)
#define VI_DMACTL1_cads_shift                                                        (16)
#define VI_DMACTL1_cads_mask                                                         (0x007F0000)
#define VI_DMACTL1_cads(data)                                                        (0x007F0000&((data)<<16))
#define VI_DMACTL1_cads_src(data)                                                    ((0x007F0000&(data))>>16)
#define VI_DMACTL1_get_cads(data)                                                    ((0x007F0000&(data))>>16)
#define VI_DMACTL1_write_enable4_shift                                               (15)
#define VI_DMACTL1_write_enable4_mask                                                (0x00008000)
#define VI_DMACTL1_write_enable4(data)                                               (0x00008000&((data)<<15))
#define VI_DMACTL1_write_enable4_src(data)                                           ((0x00008000&(data))>>15)
#define VI_DMACTL1_get_write_enable4(data)                                           ((0x00008000&(data))>>15)
#define VI_DMACTL1_hdyads_shift                                                      (8)
#define VI_DMACTL1_hdyads_mask                                                       (0x00007F00)
#define VI_DMACTL1_hdyads(data)                                                      (0x00007F00&((data)<<8))
#define VI_DMACTL1_hdyads_src(data)                                                  ((0x00007F00&(data))>>8)
#define VI_DMACTL1_get_hdyads(data)                                                  ((0x00007F00&(data))>>8)
#define VI_DMACTL1_write_enable5_shift                                               (7)
#define VI_DMACTL1_write_enable5_mask                                                (0x00000080)
#define VI_DMACTL1_write_enable5(data)                                               (0x00000080&((data)<<7))
#define VI_DMACTL1_write_enable5_src(data)                                           ((0x00000080&(data))>>7)
#define VI_DMACTL1_get_write_enable5(data)                                           ((0x00000080&(data))>>7)
#define VI_DMACTL1_hdcads_shift                                                      (0)
#define VI_DMACTL1_hdcads_mask                                                       (0x0000007F)
#define VI_DMACTL1_hdcads(data)                                                      (0x0000007F&((data)<<0))
#define VI_DMACTL1_hdcads_src(data)                                                  ((0x0000007F&(data))>>0)
#define VI_DMACTL1_get_hdcads(data)                                                  ((0x0000007F&(data))>>0)


#define VI_DMACTL2                                                                   0x18004250
#define VI_DMACTL2_reg_addr                                                          "0xB8004250"
#define VI_DMACTL2_reg                                                               0xB8004250
#define VI_DMACTL2_inst_adr                                                          "0x0094"
#define VI_DMACTL2_inst                                                              0x0094
#define VI_DMACTL2_write_enable2_shift                                               (31)
#define VI_DMACTL2_write_enable2_mask                                                (0x80000000)
#define VI_DMACTL2_write_enable2(data)                                               (0x80000000&((data)<<31))
#define VI_DMACTL2_write_enable2_src(data)                                           ((0x80000000&(data))>>31)
#define VI_DMACTL2_get_write_enable2(data)                                           ((0x80000000&(data))>>31)
#define VI_DMACTL2_yads_shift                                                        (24)
#define VI_DMACTL2_yads_mask                                                         (0x7F000000)
#define VI_DMACTL2_yads(data)                                                        (0x7F000000&((data)<<24))
#define VI_DMACTL2_yads_src(data)                                                    ((0x7F000000&(data))>>24)
#define VI_DMACTL2_get_yads(data)                                                    ((0x7F000000&(data))>>24)
#define VI_DMACTL2_write_enable3_shift                                               (23)
#define VI_DMACTL2_write_enable3_mask                                                (0x00800000)
#define VI_DMACTL2_write_enable3(data)                                               (0x00800000&((data)<<23))
#define VI_DMACTL2_write_enable3_src(data)                                           ((0x00800000&(data))>>23)
#define VI_DMACTL2_get_write_enable3(data)                                           ((0x00800000&(data))>>23)
#define VI_DMACTL2_cads_shift                                                        (16)
#define VI_DMACTL2_cads_mask                                                         (0x007F0000)
#define VI_DMACTL2_cads(data)                                                        (0x007F0000&((data)<<16))
#define VI_DMACTL2_cads_src(data)                                                    ((0x007F0000&(data))>>16)
#define VI_DMACTL2_get_cads(data)                                                    ((0x007F0000&(data))>>16)
#define VI_DMACTL2_write_enable4_shift                                               (15)
#define VI_DMACTL2_write_enable4_mask                                                (0x00008000)
#define VI_DMACTL2_write_enable4(data)                                               (0x00008000&((data)<<15))
#define VI_DMACTL2_write_enable4_src(data)                                           ((0x00008000&(data))>>15)
#define VI_DMACTL2_get_write_enable4(data)                                           ((0x00008000&(data))>>15)
#define VI_DMACTL2_hdyads_shift                                                      (8)
#define VI_DMACTL2_hdyads_mask                                                       (0x00007F00)
#define VI_DMACTL2_hdyads(data)                                                      (0x00007F00&((data)<<8))
#define VI_DMACTL2_hdyads_src(data)                                                  ((0x00007F00&(data))>>8)
#define VI_DMACTL2_get_hdyads(data)                                                  ((0x00007F00&(data))>>8)
#define VI_DMACTL2_write_enable5_shift                                               (7)
#define VI_DMACTL2_write_enable5_mask                                                (0x00000080)
#define VI_DMACTL2_write_enable5(data)                                               (0x00000080&((data)<<7))
#define VI_DMACTL2_write_enable5_src(data)                                           ((0x00000080&(data))>>7)
#define VI_DMACTL2_get_write_enable5(data)                                           ((0x00000080&(data))>>7)
#define VI_DMACTL2_hdcads_shift                                                      (0)
#define VI_DMACTL2_hdcads_mask                                                       (0x0000007F)
#define VI_DMACTL2_hdcads(data)                                                      (0x0000007F&((data)<<0))
#define VI_DMACTL2_hdcads_src(data)                                                  ((0x0000007F&(data))>>0)
#define VI_DMACTL2_get_hdcads(data)                                                  ((0x0000007F&(data))>>0)


#define VI_DYDMACTL                                                                  0x18004254
#define VI_DYDMACTL_reg_addr                                                         "0xB8004254"
#define VI_DYDMACTL_reg                                                              0xB8004254
#define VI_DYDMACTL_inst_adr                                                         "0x0095"
#define VI_DYDMACTL_inst                                                             0x0095
#define VI_DYDMACTL_dyads2_shift                                                     (7)
#define VI_DYDMACTL_dyads2_mask                                                      (0x00003F80)
#define VI_DYDMACTL_dyads2(data)                                                     (0x00003F80&((data)<<7))
#define VI_DYDMACTL_dyads2_src(data)                                                 ((0x00003F80&(data))>>7)
#define VI_DYDMACTL_get_dyads2(data)                                                 ((0x00003F80&(data))>>7)
#define VI_DYDMACTL_dyads_shift                                                      (0)
#define VI_DYDMACTL_dyads_mask                                                       (0x0000007F)
#define VI_DYDMACTL_dyads(data)                                                      (0x0000007F&((data)<<0))
#define VI_DYDMACTL_dyads_src(data)                                                  ((0x0000007F&(data))>>0)
#define VI_DYDMACTL_get_dyads(data)                                                  ((0x0000007F&(data))>>0)


#define VI_IMMODE                                                                    0x1800425c
#define VI_IMMODE_reg_addr                                                           "0xB800425C"
#define VI_IMMODE_reg                                                                0xB800425C
#define VI_IMMODE_inst_adr                                                           "0x0097"
#define VI_IMMODE_inst                                                               0x0097
#define VI_IMMODE_v1hd_odd_shift                                                     (12)
#define VI_IMMODE_v1hd_odd_mask                                                      (0x00001000)
#define VI_IMMODE_v1hd_odd(data)                                                     (0x00001000&((data)<<12))
#define VI_IMMODE_v1hd_odd_src(data)                                                 ((0x00001000&(data))>>12)
#define VI_IMMODE_get_v1hd_odd(data)                                                 ((0x00001000&(data))>>12)
#define VI_IMMODE_v1hd_interleave_shift                                              (11)
#define VI_IMMODE_v1hd_interleave_mask                                               (0x00000800)
#define VI_IMMODE_v1hd_interleave(data)                                              (0x00000800&((data)<<11))
#define VI_IMMODE_v1hd_interleave_src(data)                                          ((0x00000800&(data))>>11)
#define VI_IMMODE_get_v1hd_interleave(data)                                          ((0x00000800&(data))>>11)
#define VI_IMMODE_v2hd_odd_shift                                                     (10)
#define VI_IMMODE_v2hd_odd_mask                                                      (0x00000400)
#define VI_IMMODE_v2hd_odd(data)                                                     (0x00000400&((data)<<10))
#define VI_IMMODE_v2hd_odd_src(data)                                                 ((0x00000400&(data))>>10)
#define VI_IMMODE_get_v2hd_odd(data)                                                 ((0x00000400&(data))>>10)
#define VI_IMMODE_v2hd_interleave_shift                                              (9)
#define VI_IMMODE_v2hd_interleave_mask                                               (0x00000200)
#define VI_IMMODE_v2hd_interleave(data)                                              (0x00000200&((data)<<9))
#define VI_IMMODE_v2hd_interleave_src(data)                                          ((0x00000200&(data))>>9)
#define VI_IMMODE_get_v2hd_interleave(data)                                          ((0x00000200&(data))>>9)
#define VI_IMMODE_v1_odd_shift                                                       (8)
#define VI_IMMODE_v1_odd_mask                                                        (0x00000100)
#define VI_IMMODE_v1_odd(data)                                                       (0x00000100&((data)<<8))
#define VI_IMMODE_v1_odd_src(data)                                                   ((0x00000100&(data))>>8)
#define VI_IMMODE_get_v1_odd(data)                                                   ((0x00000100&(data))>>8)
#define VI_IMMODE_v1_interleave_shift                                                (7)
#define VI_IMMODE_v1_interleave_mask                                                 (0x00000080)
#define VI_IMMODE_v1_interleave(data)                                                (0x00000080&((data)<<7))
#define VI_IMMODE_v1_interleave_src(data)                                            ((0x00000080&(data))>>7)
#define VI_IMMODE_get_v1_interleave(data)                                            ((0x00000080&(data))>>7)
#define VI_IMMODE_v2_odd_shift                                                       (6)
#define VI_IMMODE_v2_odd_mask                                                        (0x00000040)
#define VI_IMMODE_v2_odd(data)                                                       (0x00000040&((data)<<6))
#define VI_IMMODE_v2_odd_src(data)                                                   ((0x00000040&(data))>>6)
#define VI_IMMODE_get_v2_odd(data)                                                   ((0x00000040&(data))>>6)
#define VI_IMMODE_v2_interleave_shift                                                (5)
#define VI_IMMODE_v2_interleave_mask                                                 (0x00000020)
#define VI_IMMODE_v2_interleave(data)                                                (0x00000020&((data)<<5))
#define VI_IMMODE_v2_interleave_src(data)                                            ((0x00000020&(data))>>5)
#define VI_IMMODE_get_v2_interleave(data)                                            ((0x00000020&(data))>>5)
#define VI_IMMODE_dy_odd_shift                                                       (4)
#define VI_IMMODE_dy_odd_mask                                                        (0x00000010)
#define VI_IMMODE_dy_odd(data)                                                       (0x00000010&((data)<<4))
#define VI_IMMODE_dy_odd_src(data)                                                   ((0x00000010&(data))>>4)
#define VI_IMMODE_get_dy_odd(data)                                                   ((0x00000010&(data))>>4)
#define VI_IMMODE_dy_interleave_shift                                                (3)
#define VI_IMMODE_dy_interleave_mask                                                 (0x00000008)
#define VI_IMMODE_dy_interleave(data)                                                (0x00000008&((data)<<3))
#define VI_IMMODE_dy_interleave_src(data)                                            ((0x00000008&(data))>>3)
#define VI_IMMODE_get_dy_interleave(data)                                            ((0x00000008&(data))>>3)
#define VI_IMMODE_dy2_odd_shift                                                      (2)
#define VI_IMMODE_dy2_odd_mask                                                       (0x00000004)
#define VI_IMMODE_dy2_odd(data)                                                      (0x00000004&((data)<<2))
#define VI_IMMODE_dy2_odd_src(data)                                                  ((0x00000004&(data))>>2)
#define VI_IMMODE_get_dy2_odd(data)                                                  ((0x00000004&(data))>>2)
#define VI_IMMODE_dy2_interleave_shift                                               (1)
#define VI_IMMODE_dy2_interleave_mask                                                (0x00000002)
#define VI_IMMODE_dy2_interleave(data)                                               (0x00000002&((data)<<1))
#define VI_IMMODE_dy2_interleave_src(data)                                           ((0x00000002&(data))>>1)
#define VI_IMMODE_get_dy2_interleave(data)                                           ((0x00000002&(data))>>1)
#define VI_IMMODE_write_data_shift                                                   (0)
#define VI_IMMODE_write_data_mask                                                    (0x00000001)
#define VI_IMMODE_write_data(data)                                                   (0x00000001&((data)<<0))
#define VI_IMMODE_write_data_src(data)                                               ((0x00000001&(data))>>0)
#define VI_IMMODE_get_write_data(data)                                               ((0x00000001&(data))>>0)


#define VI_DMA_MIN_TIME                                                              0x18004260
#define VI_DMA_MIN_TIME_reg_addr                                                     "0xB8004260"
#define VI_DMA_MIN_TIME_reg                                                          0xB8004260
#define VI_DMA_MIN_TIME_inst_adr                                                     "0x0098"
#define VI_DMA_MIN_TIME_inst                                                         0x0098
#define VI_DMA_MIN_TIME_write_enable1_shift                                          (29)
#define VI_DMA_MIN_TIME_write_enable1_mask                                           (0x20000000)
#define VI_DMA_MIN_TIME_write_enable1(data)                                          (0x20000000&((data)<<29))
#define VI_DMA_MIN_TIME_write_enable1_src(data)                                      ((0x20000000&(data))>>29)
#define VI_DMA_MIN_TIME_get_write_enable1(data)                                      ((0x20000000&(data))>>29)
#define VI_DMA_MIN_TIME_y1c1_shift                                                   (25)
#define VI_DMA_MIN_TIME_y1c1_mask                                                    (0x1E000000)
#define VI_DMA_MIN_TIME_y1c1(data)                                                   (0x1E000000&((data)<<25))
#define VI_DMA_MIN_TIME_y1c1_src(data)                                               ((0x1E000000&(data))>>25)
#define VI_DMA_MIN_TIME_get_y1c1(data)                                               ((0x1E000000&(data))>>25)
#define VI_DMA_MIN_TIME_write_enable2_shift                                          (24)
#define VI_DMA_MIN_TIME_write_enable2_mask                                           (0x01000000)
#define VI_DMA_MIN_TIME_write_enable2(data)                                          (0x01000000&((data)<<24))
#define VI_DMA_MIN_TIME_write_enable2_src(data)                                      ((0x01000000&(data))>>24)
#define VI_DMA_MIN_TIME_get_write_enable2(data)                                      ((0x01000000&(data))>>24)
#define VI_DMA_MIN_TIME_y2c2_shift                                                   (20)
#define VI_DMA_MIN_TIME_y2c2_mask                                                    (0x00F00000)
#define VI_DMA_MIN_TIME_y2c2(data)                                                   (0x00F00000&((data)<<20))
#define VI_DMA_MIN_TIME_y2c2_src(data)                                               ((0x00F00000&(data))>>20)
#define VI_DMA_MIN_TIME_get_y2c2(data)                                               ((0x00F00000&(data))>>20)
#define VI_DMA_MIN_TIME_write_enable3_shift                                          (19)
#define VI_DMA_MIN_TIME_write_enable3_mask                                           (0x00080000)
#define VI_DMA_MIN_TIME_write_enable3(data)                                          (0x00080000&((data)<<19))
#define VI_DMA_MIN_TIME_write_enable3_src(data)                                      ((0x00080000&(data))>>19)
#define VI_DMA_MIN_TIME_get_write_enable3(data)                                      ((0x00080000&(data))>>19)
#define VI_DMA_MIN_TIME_vbi1_shift                                                   (15)
#define VI_DMA_MIN_TIME_vbi1_mask                                                    (0x00078000)
#define VI_DMA_MIN_TIME_vbi1(data)                                                   (0x00078000&((data)<<15))
#define VI_DMA_MIN_TIME_vbi1_src(data)                                               ((0x00078000&(data))>>15)
#define VI_DMA_MIN_TIME_get_vbi1(data)                                               ((0x00078000&(data))>>15)
#define VI_DMA_MIN_TIME_write_enable4_shift                                          (14)
#define VI_DMA_MIN_TIME_write_enable4_mask                                           (0x00004000)
#define VI_DMA_MIN_TIME_write_enable4(data)                                          (0x00004000&((data)<<14))
#define VI_DMA_MIN_TIME_write_enable4_src(data)                                      ((0x00004000&(data))>>14)
#define VI_DMA_MIN_TIME_get_write_enable4(data)                                      ((0x00004000&(data))>>14)
#define VI_DMA_MIN_TIME_vbi2_shift                                                   (10)
#define VI_DMA_MIN_TIME_vbi2_mask                                                    (0x00003C00)
#define VI_DMA_MIN_TIME_vbi2(data)                                                   (0x00003C00&((data)<<10))
#define VI_DMA_MIN_TIME_vbi2_src(data)                                               ((0x00003C00&(data))>>10)
#define VI_DMA_MIN_TIME_get_vbi2(data)                                               ((0x00003C00&(data))>>10)
#define VI_DMA_MIN_TIME_write_enable5_shift                                          (9)
#define VI_DMA_MIN_TIME_write_enable5_mask                                           (0x00000200)
#define VI_DMA_MIN_TIME_write_enable5(data)                                          (0x00000200&((data)<<9))
#define VI_DMA_MIN_TIME_write_enable5_src(data)                                      ((0x00000200&(data))>>9)
#define VI_DMA_MIN_TIME_get_write_enable5(data)                                      ((0x00000200&(data))>>9)
#define VI_DMA_MIN_TIME_dy_shift                                                     (5)
#define VI_DMA_MIN_TIME_dy_mask                                                      (0x000001E0)
#define VI_DMA_MIN_TIME_dy(data)                                                     (0x000001E0&((data)<<5))
#define VI_DMA_MIN_TIME_dy_src(data)                                                 ((0x000001E0&(data))>>5)
#define VI_DMA_MIN_TIME_get_dy(data)                                                 ((0x000001E0&(data))>>5)
#define VI_DMA_MIN_TIME_write_enable6_shift                                          (4)
#define VI_DMA_MIN_TIME_write_enable6_mask                                           (0x00000010)
#define VI_DMA_MIN_TIME_write_enable6(data)                                          (0x00000010&((data)<<4))
#define VI_DMA_MIN_TIME_write_enable6_src(data)                                      ((0x00000010&(data))>>4)
#define VI_DMA_MIN_TIME_get_write_enable6(data)                                      ((0x00000010&(data))>>4)
#define VI_DMA_MIN_TIME_dy2_shift                                                    (0)
#define VI_DMA_MIN_TIME_dy2_mask                                                     (0x0000000F)
#define VI_DMA_MIN_TIME_dy2(data)                                                    (0x0000000F&((data)<<0))
#define VI_DMA_MIN_TIME_dy2_src(data)                                                ((0x0000000F&(data))>>0)
#define VI_DMA_MIN_TIME_get_dy2(data)                                                ((0x0000000F&(data))>>0)


#define VI_HDDMA_MIN_TIME                                                            0x18004490
#define VI_HDDMA_MIN_TIME_reg_addr                                                   "0xB8004490"
#define VI_HDDMA_MIN_TIME_reg                                                        0xB8004490
#define VI_HDDMA_MIN_TIME_inst_adr                                                   "0x0024"
#define VI_HDDMA_MIN_TIME_inst                                                       0x0024
#define VI_HDDMA_MIN_TIME_write_enable1_shift                                        (9)
#define VI_HDDMA_MIN_TIME_write_enable1_mask                                         (0x00000200)
#define VI_HDDMA_MIN_TIME_write_enable1(data)                                        (0x00000200&((data)<<9))
#define VI_HDDMA_MIN_TIME_write_enable1_src(data)                                    ((0x00000200&(data))>>9)
#define VI_HDDMA_MIN_TIME_get_write_enable1(data)                                    ((0x00000200&(data))>>9)
#define VI_HDDMA_MIN_TIME_y1c1_shift                                                 (5)
#define VI_HDDMA_MIN_TIME_y1c1_mask                                                  (0x000001E0)
#define VI_HDDMA_MIN_TIME_y1c1(data)                                                 (0x000001E0&((data)<<5))
#define VI_HDDMA_MIN_TIME_y1c1_src(data)                                             ((0x000001E0&(data))>>5)
#define VI_HDDMA_MIN_TIME_get_y1c1(data)                                             ((0x000001E0&(data))>>5)
#define VI_HDDMA_MIN_TIME_write_enable2_shift                                        (4)
#define VI_HDDMA_MIN_TIME_write_enable2_mask                                         (0x00000010)
#define VI_HDDMA_MIN_TIME_write_enable2(data)                                        (0x00000010&((data)<<4))
#define VI_HDDMA_MIN_TIME_write_enable2_src(data)                                    ((0x00000010&(data))>>4)
#define VI_HDDMA_MIN_TIME_get_write_enable2(data)                                    ((0x00000010&(data))>>4)
#define VI_HDDMA_MIN_TIME_y2c2_shift                                                 (0)
#define VI_HDDMA_MIN_TIME_y2c2_mask                                                  (0x0000000F)
#define VI_HDDMA_MIN_TIME_y2c2(data)                                                 (0x0000000F&((data)<<0))
#define VI_HDDMA_MIN_TIME_y2c2_src(data)                                             ((0x0000000F&(data))>>0)
#define VI_HDDMA_MIN_TIME_get_y2c2(data)                                             ((0x0000000F&(data))>>0)


#define VI_DMAERR                                                                    0x18004264
#define VI_DMAERR_reg_addr                                                           "0xB8004264"
#define VI_DMAERR_reg                                                                0xB8004264
#define VI_DMAERR_inst_adr                                                           "0x0099"
#define VI_DMAERR_inst                                                               0x0099
#define VI_DMAERR_v2_err_shift                                                       (1)
#define VI_DMAERR_v2_err_mask                                                        (0x00000002)
#define VI_DMAERR_v2_err(data)                                                       (0x00000002&((data)<<1))
#define VI_DMAERR_v2_err_src(data)                                                   ((0x00000002&(data))>>1)
#define VI_DMAERR_get_v2_err(data)                                                   ((0x00000002&(data))>>1)
#define VI_DMAERR_v1_err_shift                                                       (0)
#define VI_DMAERR_v1_err_mask                                                        (0x00000001)
#define VI_DMAERR_v1_err(data)                                                       (0x00000001&((data)<<0))
#define VI_DMAERR_v1_err_src(data)                                                   ((0x00000001&(data))>>0)
#define VI_DMAERR_get_v1_err(data)                                                   ((0x00000001&(data))>>0)


#define VI_INTEN                                                                     0x18004268
#define VI_INTEN_reg_addr                                                            "0xB8004268"
#define VI_INTEN_reg                                                                 0xB8004268
#define VI_INTEN_inst_adr                                                            "0x009A"
#define VI_INTEN_inst                                                                0x009A
#define VI_INTEN_feinte1_shift                                                       (14)
#define VI_INTEN_feinte1_mask                                                        (0x00004000)
#define VI_INTEN_feinte1(data)                                                       (0x00004000&((data)<<14))
#define VI_INTEN_feinte1_src(data)                                                   ((0x00004000&(data))>>14)
#define VI_INTEN_get_feinte1(data)                                                   ((0x00004000&(data))>>14)
#define VI_INTEN_feinte2_shift                                                       (13)
#define VI_INTEN_feinte2_mask                                                        (0x00002000)
#define VI_INTEN_feinte2(data)                                                       (0x00002000&((data)<<13))
#define VI_INTEN_feinte2_src(data)                                                   ((0x00002000&(data))>>13)
#define VI_INTEN_get_feinte2(data)                                                   ((0x00002000&(data))>>13)
#define VI_INTEN_hdolinte1_shift                                                     (12)
#define VI_INTEN_hdolinte1_mask                                                      (0x00001000)
#define VI_INTEN_hdolinte1(data)                                                     (0x00001000&((data)<<12))
#define VI_INTEN_hdolinte1_src(data)                                                 ((0x00001000&(data))>>12)
#define VI_INTEN_get_hdolinte1(data)                                                 ((0x00001000&(data))>>12)
#define VI_INTEN_hdolinte2_shift                                                     (11)
#define VI_INTEN_hdolinte2_mask                                                      (0x00000800)
#define VI_INTEN_hdolinte2(data)                                                     (0x00000800&((data)<<11))
#define VI_INTEN_hdolinte2_src(data)                                                 ((0x00000800&(data))>>11)
#define VI_INTEN_get_hdolinte2(data)                                                 ((0x00000800&(data))>>11)
#define VI_INTEN_dmaerrinte_shift                                                    (10)
#define VI_INTEN_dmaerrinte_mask                                                     (0x00000400)
#define VI_INTEN_dmaerrinte(data)                                                    (0x00000400&((data)<<10))
#define VI_INTEN_dmaerrinte_src(data)                                                ((0x00000400&(data))>>10)
#define VI_INTEN_get_dmaerrinte(data)                                                ((0x00000400&(data))>>10)
#define VI_INTEN_sfinte1_shift                                                       (8)
#define VI_INTEN_sfinte1_mask                                                        (0x00000100)
#define VI_INTEN_sfinte1(data)                                                       (0x00000100&((data)<<8))
#define VI_INTEN_sfinte1_src(data)                                                   ((0x00000100&(data))>>8)
#define VI_INTEN_get_sfinte1(data)                                                   ((0x00000100&(data))>>8)
#define VI_INTEN_sfinte2_shift                                                       (7)
#define VI_INTEN_sfinte2_mask                                                        (0x00000080)
#define VI_INTEN_sfinte2(data)                                                       (0x00000080&((data)<<7))
#define VI_INTEN_sfinte2_src(data)                                                   ((0x00000080&(data))>>7)
#define VI_INTEN_get_sfinte2(data)                                                   ((0x00000080&(data))>>7)
#define VI_INTEN_vsinte1_shift                                                       (6)
#define VI_INTEN_vsinte1_mask                                                        (0x00000040)
#define VI_INTEN_vsinte1(data)                                                       (0x00000040&((data)<<6))
#define VI_INTEN_vsinte1_src(data)                                                   ((0x00000040&(data))>>6)
#define VI_INTEN_get_vsinte1(data)                                                   ((0x00000040&(data))>>6)
#define VI_INTEN_vsinte2_shift                                                       (5)
#define VI_INTEN_vsinte2_mask                                                        (0x00000020)
#define VI_INTEN_vsinte2(data)                                                       (0x00000020&((data)<<5))
#define VI_INTEN_vsinte2_src(data)                                                   ((0x00000020&(data))>>5)
#define VI_INTEN_get_vsinte2(data)                                                   ((0x00000020&(data))>>5)
#define VI_INTEN_tointe1_shift                                                       (4)
#define VI_INTEN_tointe1_mask                                                        (0x00000010)
#define VI_INTEN_tointe1(data)                                                       (0x00000010&((data)<<4))
#define VI_INTEN_tointe1_src(data)                                                   ((0x00000010&(data))>>4)
#define VI_INTEN_get_tointe1(data)                                                   ((0x00000010&(data))>>4)
#define VI_INTEN_tointe2_shift                                                       (3)
#define VI_INTEN_tointe2_mask                                                        (0x00000008)
#define VI_INTEN_tointe2(data)                                                       (0x00000008&((data)<<3))
#define VI_INTEN_tointe2_src(data)                                                   ((0x00000008&(data))>>3)
#define VI_INTEN_get_tointe2(data)                                                   ((0x00000008&(data))>>3)
#define VI_INTEN_olinte1_shift                                                       (2)
#define VI_INTEN_olinte1_mask                                                        (0x00000004)
#define VI_INTEN_olinte1(data)                                                       (0x00000004&((data)<<2))
#define VI_INTEN_olinte1_src(data)                                                   ((0x00000004&(data))>>2)
#define VI_INTEN_get_olinte1(data)                                                   ((0x00000004&(data))>>2)
#define VI_INTEN_olinte2_shift                                                       (1)
#define VI_INTEN_olinte2_mask                                                        (0x00000002)
#define VI_INTEN_olinte2(data)                                                       (0x00000002&((data)<<1))
#define VI_INTEN_olinte2_src(data)                                                   ((0x00000002&(data))>>1)
#define VI_INTEN_get_olinte2(data)                                                   ((0x00000002&(data))>>1)
#define VI_INTEN_write_data_shift                                                    (0)
#define VI_INTEN_write_data_mask                                                     (0x00000001)
#define VI_INTEN_write_data(data)                                                    (0x00000001&((data)<<0))
#define VI_INTEN_write_data_src(data)                                                ((0x00000001&(data))>>0)
#define VI_INTEN_get_write_data(data)                                                ((0x00000001&(data))>>0)


#define VI_INTST                                                                     0x1800426c
#define VI_INTST_reg_addr                                                            "0xB800426C"
#define VI_INTST_reg                                                                 0xB800426C
#define VI_INTST_inst_adr                                                            "0x009B"
#define VI_INTST_inst                                                                0x009B
#define VI_INTST_feints1_shift                                                       (14)
#define VI_INTST_feints1_mask                                                        (0x00004000)
#define VI_INTST_feints1(data)                                                       (0x00004000&((data)<<14))
#define VI_INTST_feints1_src(data)                                                   ((0x00004000&(data))>>14)
#define VI_INTST_get_feints1(data)                                                   ((0x00004000&(data))>>14)
#define VI_INTST_feints2_shift                                                       (13)
#define VI_INTST_feints2_mask                                                        (0x00002000)
#define VI_INTST_feints2(data)                                                       (0x00002000&((data)<<13))
#define VI_INTST_feints2_src(data)                                                   ((0x00002000&(data))>>13)
#define VI_INTST_get_feints2(data)                                                   ((0x00002000&(data))>>13)
#define VI_INTST_hdolints1_shift                                                     (12)
#define VI_INTST_hdolints1_mask                                                      (0x00001000)
#define VI_INTST_hdolints1(data)                                                     (0x00001000&((data)<<12))
#define VI_INTST_hdolints1_src(data)                                                 ((0x00001000&(data))>>12)
#define VI_INTST_get_hdolints1(data)                                                 ((0x00001000&(data))>>12)
#define VI_INTST_hdolints2_shift                                                     (11)
#define VI_INTST_hdolints2_mask                                                      (0x00000800)
#define VI_INTST_hdolints2(data)                                                     (0x00000800&((data)<<11))
#define VI_INTST_hdolints2_src(data)                                                 ((0x00000800&(data))>>11)
#define VI_INTST_get_hdolints2(data)                                                 ((0x00000800&(data))>>11)
#define VI_INTST_dmaerrints_shift                                                    (10)
#define VI_INTST_dmaerrints_mask                                                     (0x00000400)
#define VI_INTST_dmaerrints(data)                                                    (0x00000400&((data)<<10))
#define VI_INTST_dmaerrints_src(data)                                                ((0x00000400&(data))>>10)
#define VI_INTST_get_dmaerrints(data)                                                ((0x00000400&(data))>>10)
#define VI_INTST_sfints1_shift                                                       (8)
#define VI_INTST_sfints1_mask                                                        (0x00000100)
#define VI_INTST_sfints1(data)                                                       (0x00000100&((data)<<8))
#define VI_INTST_sfints1_src(data)                                                   ((0x00000100&(data))>>8)
#define VI_INTST_get_sfints1(data)                                                   ((0x00000100&(data))>>8)
#define VI_INTST_sfints2_shift                                                       (7)
#define VI_INTST_sfints2_mask                                                        (0x00000080)
#define VI_INTST_sfints2(data)                                                       (0x00000080&((data)<<7))
#define VI_INTST_sfints2_src(data)                                                   ((0x00000080&(data))>>7)
#define VI_INTST_get_sfints2(data)                                                   ((0x00000080&(data))>>7)
#define VI_INTST_vsints1_shift                                                       (6)
#define VI_INTST_vsints1_mask                                                        (0x00000040)
#define VI_INTST_vsints1(data)                                                       (0x00000040&((data)<<6))
#define VI_INTST_vsints1_src(data)                                                   ((0x00000040&(data))>>6)
#define VI_INTST_get_vsints1(data)                                                   ((0x00000040&(data))>>6)
#define VI_INTST_vsints2_shift                                                       (5)
#define VI_INTST_vsints2_mask                                                        (0x00000020)
#define VI_INTST_vsints2(data)                                                       (0x00000020&((data)<<5))
#define VI_INTST_vsints2_src(data)                                                   ((0x00000020&(data))>>5)
#define VI_INTST_get_vsints2(data)                                                   ((0x00000020&(data))>>5)
#define VI_INTST_toints1_shift                                                       (4)
#define VI_INTST_toints1_mask                                                        (0x00000010)
#define VI_INTST_toints1(data)                                                       (0x00000010&((data)<<4))
#define VI_INTST_toints1_src(data)                                                   ((0x00000010&(data))>>4)
#define VI_INTST_get_toints1(data)                                                   ((0x00000010&(data))>>4)
#define VI_INTST_toints2_shift                                                       (3)
#define VI_INTST_toints2_mask                                                        (0x00000008)
#define VI_INTST_toints2(data)                                                       (0x00000008&((data)<<3))
#define VI_INTST_toints2_src(data)                                                   ((0x00000008&(data))>>3)
#define VI_INTST_get_toints2(data)                                                   ((0x00000008&(data))>>3)
#define VI_INTST_olints1_shift                                                       (2)
#define VI_INTST_olints1_mask                                                        (0x00000004)
#define VI_INTST_olints1(data)                                                       (0x00000004&((data)<<2))
#define VI_INTST_olints1_src(data)                                                   ((0x00000004&(data))>>2)
#define VI_INTST_get_olints1(data)                                                   ((0x00000004&(data))>>2)
#define VI_INTST_olints2_shift                                                       (1)
#define VI_INTST_olints2_mask                                                        (0x00000002)
#define VI_INTST_olints2(data)                                                       (0x00000002&((data)<<1))
#define VI_INTST_olints2_src(data)                                                   ((0x00000002&(data))>>1)
#define VI_INTST_get_olints2(data)                                                   ((0x00000002&(data))>>1)
#define VI_INTST_write_data_shift                                                    (0)
#define VI_INTST_write_data_mask                                                     (0x00000001)
#define VI_INTST_write_data(data)                                                    (0x00000001&((data)<<0))
#define VI_INTST_write_data_src(data)                                                ((0x00000001&(data))>>0)
#define VI_INTST_get_write_data(data)                                                ((0x00000001&(data))>>0)


#define VI_OLN1                                                                      0x18004270
#define VI_OLN1_reg_addr                                                             "0xB8004270"
#define VI_OLN1_reg                                                                  0xB8004270
#define VI_OLN1_inst_adr                                                             "0x009C"
#define VI_OLN1_inst                                                                 0x009C
#define VI_OLN1_write_enable1_shift                                                  (23)
#define VI_OLN1_write_enable1_mask                                                   (0x00800000)
#define VI_OLN1_write_enable1(data)                                                  (0x00800000&((data)<<23))
#define VI_OLN1_write_enable1_src(data)                                              ((0x00800000&(data))>>23)
#define VI_OLN1_get_write_enable1(data)                                              ((0x00800000&(data))>>23)
#define VI_OLN1_y_shift                                                              (12)
#define VI_OLN1_y_mask                                                               (0x007FF000)
#define VI_OLN1_y(data)                                                              (0x007FF000&((data)<<12))
#define VI_OLN1_y_src(data)                                                          ((0x007FF000&(data))>>12)
#define VI_OLN1_get_y(data)                                                          ((0x007FF000&(data))>>12)
#define VI_OLN1_write_enable2_shift                                                  (11)
#define VI_OLN1_write_enable2_mask                                                   (0x00000800)
#define VI_OLN1_write_enable2(data)                                                  (0x00000800&((data)<<11))
#define VI_OLN1_write_enable2_src(data)                                              ((0x00000800&(data))>>11)
#define VI_OLN1_get_write_enable2(data)                                              ((0x00000800&(data))>>11)
#define VI_OLN1_c_shift                                                              (0)
#define VI_OLN1_c_mask                                                               (0x000007FF)
#define VI_OLN1_c(data)                                                              (0x000007FF&((data)<<0))
#define VI_OLN1_c_src(data)                                                          ((0x000007FF&(data))>>0)
#define VI_OLN1_get_c(data)                                                          ((0x000007FF&(data))>>0)


#define VI_OLN2                                                                      0x18004274
#define VI_OLN2_reg_addr                                                             "0xB8004274"
#define VI_OLN2_reg                                                                  0xB8004274
#define VI_OLN2_inst_adr                                                             "0x009D"
#define VI_OLN2_inst                                                                 0x009D
#define VI_OLN2_write_enable1_shift                                                  (23)
#define VI_OLN2_write_enable1_mask                                                   (0x00800000)
#define VI_OLN2_write_enable1(data)                                                  (0x00800000&((data)<<23))
#define VI_OLN2_write_enable1_src(data)                                              ((0x00800000&(data))>>23)
#define VI_OLN2_get_write_enable1(data)                                              ((0x00800000&(data))>>23)
#define VI_OLN2_y_shift                                                              (12)
#define VI_OLN2_y_mask                                                               (0x007FF000)
#define VI_OLN2_y(data)                                                              (0x007FF000&((data)<<12))
#define VI_OLN2_y_src(data)                                                          ((0x007FF000&(data))>>12)
#define VI_OLN2_get_y(data)                                                          ((0x007FF000&(data))>>12)
#define VI_OLN2_write_enable2_shift                                                  (11)
#define VI_OLN2_write_enable2_mask                                                   (0x00000800)
#define VI_OLN2_write_enable2(data)                                                  (0x00000800&((data)<<11))
#define VI_OLN2_write_enable2_src(data)                                              ((0x00000800&(data))>>11)
#define VI_OLN2_get_write_enable2(data)                                              ((0x00000800&(data))>>11)
#define VI_OLN2_c_shift                                                              (0)
#define VI_OLN2_c_mask                                                               (0x000007FF)
#define VI_OLN2_c(data)                                                              (0x000007FF&((data)<<0))
#define VI_OLN2_c_src(data)                                                          ((0x000007FF&(data))>>0)
#define VI_OLN2_get_c(data)                                                          ((0x000007FF&(data))>>0)


#define VI_HDOLN1                                                                    0x18004494
#define VI_HDOLN1_reg_addr                                                           "0xB8004494"
#define VI_HDOLN1_reg                                                                0xB8004494
#define VI_HDOLN1_inst_adr                                                           "0x0025"
#define VI_HDOLN1_inst                                                               0x0025
#define VI_HDOLN1_write_enable1_shift                                                (23)
#define VI_HDOLN1_write_enable1_mask                                                 (0x00800000)
#define VI_HDOLN1_write_enable1(data)                                                (0x00800000&((data)<<23))
#define VI_HDOLN1_write_enable1_src(data)                                            ((0x00800000&(data))>>23)
#define VI_HDOLN1_get_write_enable1(data)                                            ((0x00800000&(data))>>23)
#define VI_HDOLN1_y_shift                                                            (12)
#define VI_HDOLN1_y_mask                                                             (0x007FF000)
#define VI_HDOLN1_y(data)                                                            (0x007FF000&((data)<<12))
#define VI_HDOLN1_y_src(data)                                                        ((0x007FF000&(data))>>12)
#define VI_HDOLN1_get_y(data)                                                        ((0x007FF000&(data))>>12)
#define VI_HDOLN1_write_enable2_shift                                                (11)
#define VI_HDOLN1_write_enable2_mask                                                 (0x00000800)
#define VI_HDOLN1_write_enable2(data)                                                (0x00000800&((data)<<11))
#define VI_HDOLN1_write_enable2_src(data)                                            ((0x00000800&(data))>>11)
#define VI_HDOLN1_get_write_enable2(data)                                            ((0x00000800&(data))>>11)
#define VI_HDOLN1_c_shift                                                            (0)
#define VI_HDOLN1_c_mask                                                             (0x000007FF)
#define VI_HDOLN1_c(data)                                                            (0x000007FF&((data)<<0))
#define VI_HDOLN1_c_src(data)                                                        ((0x000007FF&(data))>>0)
#define VI_HDOLN1_get_c(data)                                                        ((0x000007FF&(data))>>0)


#define VI_HDOLN2                                                                    0x18004498
#define VI_HDOLN2_reg_addr                                                           "0xB8004498"
#define VI_HDOLN2_reg                                                                0xB8004498
#define VI_HDOLN2_inst_adr                                                           "0x0026"
#define VI_HDOLN2_inst                                                               0x0026
#define VI_HDOLN2_write_enable1_shift                                                (23)
#define VI_HDOLN2_write_enable1_mask                                                 (0x00800000)
#define VI_HDOLN2_write_enable1(data)                                                (0x00800000&((data)<<23))
#define VI_HDOLN2_write_enable1_src(data)                                            ((0x00800000&(data))>>23)
#define VI_HDOLN2_get_write_enable1(data)                                            ((0x00800000&(data))>>23)
#define VI_HDOLN2_y_shift                                                            (12)
#define VI_HDOLN2_y_mask                                                             (0x007FF000)
#define VI_HDOLN2_y(data)                                                            (0x007FF000&((data)<<12))
#define VI_HDOLN2_y_src(data)                                                        ((0x007FF000&(data))>>12)
#define VI_HDOLN2_get_y(data)                                                        ((0x007FF000&(data))>>12)
#define VI_HDOLN2_write_enable2_shift                                                (11)
#define VI_HDOLN2_write_enable2_mask                                                 (0x00000800)
#define VI_HDOLN2_write_enable2(data)                                                (0x00000800&((data)<<11))
#define VI_HDOLN2_write_enable2_src(data)                                            ((0x00000800&(data))>>11)
#define VI_HDOLN2_get_write_enable2(data)                                            ((0x00000800&(data))>>11)
#define VI_HDOLN2_c_shift                                                            (0)
#define VI_HDOLN2_c_mask                                                             (0x000007FF)
#define VI_HDOLN2_c(data)                                                            (0x000007FF&((data)<<0))
#define VI_HDOLN2_c_src(data)                                                        ((0x000007FF&(data))>>0)
#define VI_HDOLN2_get_c(data)                                                        ((0x000007FF&(data))>>0)


#define VI_OLNCNT1                                                                   0x18004278
#define VI_OLNCNT1_reg_addr                                                          "0xB8004278"
#define VI_OLNCNT1_reg                                                               0xB8004278
#define VI_OLNCNT1_inst_adr                                                          "0x009E"
#define VI_OLNCNT1_inst                                                              0x009E
#define VI_OLNCNT1_y_shift                                                           (11)
#define VI_OLNCNT1_y_mask                                                            (0x003FF800)
#define VI_OLNCNT1_y(data)                                                           (0x003FF800&((data)<<11))
#define VI_OLNCNT1_y_src(data)                                                       ((0x003FF800&(data))>>11)
#define VI_OLNCNT1_get_y(data)                                                       ((0x003FF800&(data))>>11)
#define VI_OLNCNT1_c_shift                                                           (0)
#define VI_OLNCNT1_c_mask                                                            (0x000007FF)
#define VI_OLNCNT1_c(data)                                                           (0x000007FF&((data)<<0))
#define VI_OLNCNT1_c_src(data)                                                       ((0x000007FF&(data))>>0)
#define VI_OLNCNT1_get_c(data)                                                       ((0x000007FF&(data))>>0)


#define VI_OLNCNT2                                                                   0x1800427c
#define VI_OLNCNT2_reg_addr                                                          "0xB800427C"
#define VI_OLNCNT2_reg                                                               0xB800427C
#define VI_OLNCNT2_inst_adr                                                          "0x009F"
#define VI_OLNCNT2_inst                                                              0x009F
#define VI_OLNCNT2_y_shift                                                           (11)
#define VI_OLNCNT2_y_mask                                                            (0x003FF800)
#define VI_OLNCNT2_y(data)                                                           (0x003FF800&((data)<<11))
#define VI_OLNCNT2_y_src(data)                                                       ((0x003FF800&(data))>>11)
#define VI_OLNCNT2_get_y(data)                                                       ((0x003FF800&(data))>>11)
#define VI_OLNCNT2_c_shift                                                           (0)
#define VI_OLNCNT2_c_mask                                                            (0x000007FF)
#define VI_OLNCNT2_c(data)                                                           (0x000007FF&((data)<<0))
#define VI_OLNCNT2_c_src(data)                                                       ((0x000007FF&(data))>>0)
#define VI_OLNCNT2_get_c(data)                                                       ((0x000007FF&(data))>>0)


#define VI_HDOLNCNT1                                                                 0x1800449c
#define VI_HDOLNCNT1_reg_addr                                                        "0xB800449C"
#define VI_HDOLNCNT1_reg                                                             0xB800449C
#define VI_HDOLNCNT1_inst_adr                                                        "0x0027"
#define VI_HDOLNCNT1_inst                                                            0x0027
#define VI_HDOLNCNT1_y_shift                                                         (11)
#define VI_HDOLNCNT1_y_mask                                                          (0x003FF800)
#define VI_HDOLNCNT1_y(data)                                                         (0x003FF800&((data)<<11))
#define VI_HDOLNCNT1_y_src(data)                                                     ((0x003FF800&(data))>>11)
#define VI_HDOLNCNT1_get_y(data)                                                     ((0x003FF800&(data))>>11)
#define VI_HDOLNCNT1_c_shift                                                         (0)
#define VI_HDOLNCNT1_c_mask                                                          (0x000007FF)
#define VI_HDOLNCNT1_c(data)                                                         (0x000007FF&((data)<<0))
#define VI_HDOLNCNT1_c_src(data)                                                     ((0x000007FF&(data))>>0)
#define VI_HDOLNCNT1_get_c(data)                                                     ((0x000007FF&(data))>>0)


#define VI_HDOLNCNT2                                                                 0x180044a0
#define VI_HDOLNCNT2_reg_addr                                                        "0xB80044A0"
#define VI_HDOLNCNT2_reg                                                             0xB80044A0
#define VI_HDOLNCNT2_inst_adr                                                        "0x0028"
#define VI_HDOLNCNT2_inst                                                            0x0028
#define VI_HDOLNCNT2_y_shift                                                         (11)
#define VI_HDOLNCNT2_y_mask                                                          (0x003FF800)
#define VI_HDOLNCNT2_y(data)                                                         (0x003FF800&((data)<<11))
#define VI_HDOLNCNT2_y_src(data)                                                     ((0x003FF800&(data))>>11)
#define VI_HDOLNCNT2_get_y(data)                                                     ((0x003FF800&(data))>>11)
#define VI_HDOLNCNT2_c_shift                                                         (0)
#define VI_HDOLNCNT2_c_mask                                                          (0x000007FF)
#define VI_HDOLNCNT2_c(data)                                                         (0x000007FF&((data)<<0))
#define VI_HDOLNCNT2_c_src(data)                                                     ((0x000007FF&(data))>>0)
#define VI_HDOLNCNT2_get_c(data)                                                     ((0x000007FF&(data))>>0)


#define VI_GCTL                                                                      0x18004280
#define VI_GCTL_reg_addr                                                             "0xB8004280"
#define VI_GCTL_reg                                                                  0xB8004280
#define VI_GCTL_inst_adr                                                             "0x00A0"
#define VI_GCTL_inst                                                                 0x00A0
#define VI_GCTL_write_enable3_shift                                                  (7)
#define VI_GCTL_write_enable3_mask                                                   (0x00000080)
#define VI_GCTL_write_enable3(data)                                                  (0x00000080&((data)<<7))
#define VI_GCTL_write_enable3_src(data)                                              ((0x00000080&(data))>>7)
#define VI_GCTL_get_write_enable3(data)                                              ((0x00000080&(data))>>7)
#define VI_GCTL_vsce1_shift                                                          (6)
#define VI_GCTL_vsce1_mask                                                           (0x00000040)
#define VI_GCTL_vsce1(data)                                                          (0x00000040&((data)<<6))
#define VI_GCTL_vsce1_src(data)                                                      ((0x00000040&(data))>>6)
#define VI_GCTL_get_vsce1(data)                                                      ((0x00000040&(data))>>6)
#define VI_GCTL_write_enable4_shift                                                  (5)
#define VI_GCTL_write_enable4_mask                                                   (0x00000020)
#define VI_GCTL_write_enable4(data)                                                  (0x00000020&((data)<<5))
#define VI_GCTL_write_enable4_src(data)                                              ((0x00000020&(data))>>5)
#define VI_GCTL_get_write_enable4(data)                                              ((0x00000020&(data))>>5)
#define VI_GCTL_vsce2_shift                                                          (4)
#define VI_GCTL_vsce2_mask                                                           (0x00000010)
#define VI_GCTL_vsce2(data)                                                          (0x00000010&((data)<<4))
#define VI_GCTL_vsce2_src(data)                                                      ((0x00000010&(data))>>4)
#define VI_GCTL_get_vsce2(data)                                                      ((0x00000010&(data))>>4)
#define VI_GCTL_write_enable7_shift                                                  (3)
#define VI_GCTL_write_enable7_mask                                                   (0x00000008)
#define VI_GCTL_write_enable7(data)                                                  (0x00000008&((data)<<3))
#define VI_GCTL_write_enable7_src(data)                                              ((0x00000008&(data))>>3)
#define VI_GCTL_get_write_enable7(data)                                              ((0x00000008&(data))>>3)
#define VI_GCTL_hdvsce1_shift                                                        (2)
#define VI_GCTL_hdvsce1_mask                                                         (0x00000004)
#define VI_GCTL_hdvsce1(data)                                                        (0x00000004&((data)<<2))
#define VI_GCTL_hdvsce1_src(data)                                                    ((0x00000004&(data))>>2)
#define VI_GCTL_get_hdvsce1(data)                                                    ((0x00000004&(data))>>2)
#define VI_GCTL_write_enable8_shift                                                  (1)
#define VI_GCTL_write_enable8_mask                                                   (0x00000002)
#define VI_GCTL_write_enable8(data)                                                  (0x00000002&((data)<<1))
#define VI_GCTL_write_enable8_src(data)                                              ((0x00000002&(data))>>1)
#define VI_GCTL_get_write_enable8(data)                                              ((0x00000002&(data))>>1)
#define VI_GCTL_hdvsce2_shift                                                        (0)
#define VI_GCTL_hdvsce2_mask                                                         (0x00000001)
#define VI_GCTL_hdvsce2(data)                                                        (0x00000001&((data)<<0))
#define VI_GCTL_hdvsce2_src(data)                                                    ((0x00000001&(data))>>0)
#define VI_GCTL_get_hdvsce2(data)                                                    ((0x00000001&(data))>>0)


#define VI_DYNAMIC_P                                                                 0x18004530
#define VI_DYNAMIC_P_reg_addr                                                        "0xB8004530"
#define VI_DYNAMIC_P_reg                                                             0xB8004530
#define VI_DYNAMIC_P_inst_adr                                                        "0x004C"
#define VI_DYNAMIC_P_inst                                                            0x004C
#define VI_DYNAMIC_P_write_enable1_shift                                             (1)
#define VI_DYNAMIC_P_write_enable1_mask                                              (0x00000002)
#define VI_DYNAMIC_P_write_enable1(data)                                             (0x00000002&((data)<<1))
#define VI_DYNAMIC_P_write_enable1_src(data)                                         ((0x00000002&(data))>>1)
#define VI_DYNAMIC_P_get_write_enable1(data)                                         ((0x00000002&(data))>>1)
#define VI_DYNAMIC_P_enable_shift                                                    (0)
#define VI_DYNAMIC_P_enable_mask                                                     (0x00000001)
#define VI_DYNAMIC_P_enable(data)                                                    (0x00000001&((data)<<0))
#define VI_DYNAMIC_P_enable_src(data)                                                ((0x00000001&(data))>>0)
#define VI_DYNAMIC_P_get_enable(data)                                                ((0x00000001&(data))>>0)


#define VI_Y1OBUFF                                                                   0x18004534
#define VI_Y1OBUFF_reg_addr                                                          "0xB8004534"
#define VI_Y1OBUFF_reg                                                               0xB8004534
#define VI_Y1OBUFF_inst_adr                                                          "0x004D"
#define VI_Y1OBUFF_inst                                                              0x004D
#define VI_Y1OBUFF_write_enable1_shift                                               (17)
#define VI_Y1OBUFF_write_enable1_mask                                                (0x00020000)
#define VI_Y1OBUFF_write_enable1(data)                                               (0x00020000&((data)<<17))
#define VI_Y1OBUFF_write_enable1_src(data)                                           ((0x00020000&(data))>>17)
#define VI_Y1OBUFF_get_write_enable1(data)                                           ((0x00020000&(data))>>17)
#define VI_Y1OBUFF_start_shift                                                       (9)
#define VI_Y1OBUFF_start_mask                                                        (0x0001FE00)
#define VI_Y1OBUFF_start(data)                                                       (0x0001FE00&((data)<<9))
#define VI_Y1OBUFF_start_src(data)                                                   ((0x0001FE00&(data))>>9)
#define VI_Y1OBUFF_get_start(data)                                                   ((0x0001FE00&(data))>>9)
#define VI_Y1OBUFF_write_enable2_shift                                               (8)
#define VI_Y1OBUFF_write_enable2_mask                                                (0x00000100)
#define VI_Y1OBUFF_write_enable2(data)                                               (0x00000100&((data)<<8))
#define VI_Y1OBUFF_write_enable2_src(data)                                           ((0x00000100&(data))>>8)
#define VI_Y1OBUFF_get_write_enable2(data)                                           ((0x00000100&(data))>>8)
#define VI_Y1OBUFF_end_shift                                                         (0)
#define VI_Y1OBUFF_end_mask                                                          (0x000000FF)
#define VI_Y1OBUFF_end(data)                                                         (0x000000FF&((data)<<0))
#define VI_Y1OBUFF_end_src(data)                                                     ((0x000000FF&(data))>>0)
#define VI_Y1OBUFF_get_end(data)                                                     ((0x000000FF&(data))>>0)


#define VI_Y2OBUFF                                                                   0x18004538
#define VI_Y2OBUFF_reg_addr                                                          "0xB8004538"
#define VI_Y2OBUFF_reg                                                               0xB8004538
#define VI_Y2OBUFF_inst_adr                                                          "0x004E"
#define VI_Y2OBUFF_inst                                                              0x004E
#define VI_Y2OBUFF_write_enable1_shift                                               (17)
#define VI_Y2OBUFF_write_enable1_mask                                                (0x00020000)
#define VI_Y2OBUFF_write_enable1(data)                                               (0x00020000&((data)<<17))
#define VI_Y2OBUFF_write_enable1_src(data)                                           ((0x00020000&(data))>>17)
#define VI_Y2OBUFF_get_write_enable1(data)                                           ((0x00020000&(data))>>17)
#define VI_Y2OBUFF_start_shift                                                       (9)
#define VI_Y2OBUFF_start_mask                                                        (0x0001FE00)
#define VI_Y2OBUFF_start(data)                                                       (0x0001FE00&((data)<<9))
#define VI_Y2OBUFF_start_src(data)                                                   ((0x0001FE00&(data))>>9)
#define VI_Y2OBUFF_get_start(data)                                                   ((0x0001FE00&(data))>>9)
#define VI_Y2OBUFF_write_enable2_shift                                               (8)
#define VI_Y2OBUFF_write_enable2_mask                                                (0x00000100)
#define VI_Y2OBUFF_write_enable2(data)                                               (0x00000100&((data)<<8))
#define VI_Y2OBUFF_write_enable2_src(data)                                           ((0x00000100&(data))>>8)
#define VI_Y2OBUFF_get_write_enable2(data)                                           ((0x00000100&(data))>>8)
#define VI_Y2OBUFF_end_shift                                                         (0)
#define VI_Y2OBUFF_end_mask                                                          (0x000000FF)
#define VI_Y2OBUFF_end(data)                                                         (0x000000FF&((data)<<0))
#define VI_Y2OBUFF_end_src(data)                                                     ((0x000000FF&(data))>>0)
#define VI_Y2OBUFF_get_end(data)                                                     ((0x000000FF&(data))>>0)


#define VI_C1OBUFF                                                                   0x1800453c
#define VI_C1OBUFF_reg_addr                                                          "0xB800453C"
#define VI_C1OBUFF_reg                                                               0xB800453C
#define VI_C1OBUFF_inst_adr                                                          "0x004F"
#define VI_C1OBUFF_inst                                                              0x004F
#define VI_C1OBUFF_write_enable1_shift                                               (17)
#define VI_C1OBUFF_write_enable1_mask                                                (0x00020000)
#define VI_C1OBUFF_write_enable1(data)                                               (0x00020000&((data)<<17))
#define VI_C1OBUFF_write_enable1_src(data)                                           ((0x00020000&(data))>>17)
#define VI_C1OBUFF_get_write_enable1(data)                                           ((0x00020000&(data))>>17)
#define VI_C1OBUFF_start_shift                                                       (9)
#define VI_C1OBUFF_start_mask                                                        (0x0001FE00)
#define VI_C1OBUFF_start(data)                                                       (0x0001FE00&((data)<<9))
#define VI_C1OBUFF_start_src(data)                                                   ((0x0001FE00&(data))>>9)
#define VI_C1OBUFF_get_start(data)                                                   ((0x0001FE00&(data))>>9)
#define VI_C1OBUFF_write_enable2_shift                                               (8)
#define VI_C1OBUFF_write_enable2_mask                                                (0x00000100)
#define VI_C1OBUFF_write_enable2(data)                                               (0x00000100&((data)<<8))
#define VI_C1OBUFF_write_enable2_src(data)                                           ((0x00000100&(data))>>8)
#define VI_C1OBUFF_get_write_enable2(data)                                           ((0x00000100&(data))>>8)
#define VI_C1OBUFF_end_shift                                                         (0)
#define VI_C1OBUFF_end_mask                                                          (0x000000FF)
#define VI_C1OBUFF_end(data)                                                         (0x000000FF&((data)<<0))
#define VI_C1OBUFF_end_src(data)                                                     ((0x000000FF&(data))>>0)
#define VI_C1OBUFF_get_end(data)                                                     ((0x000000FF&(data))>>0)


#define VI_C2OBUFF                                                                   0x18004540
#define VI_C2OBUFF_reg_addr                                                          "0xB8004540"
#define VI_C2OBUFF_reg                                                               0xB8004540
#define VI_C2OBUFF_inst_adr                                                          "0x0050"
#define VI_C2OBUFF_inst                                                              0x0050
#define VI_C2OBUFF_write_enable1_shift                                               (17)
#define VI_C2OBUFF_write_enable1_mask                                                (0x00020000)
#define VI_C2OBUFF_write_enable1(data)                                               (0x00020000&((data)<<17))
#define VI_C2OBUFF_write_enable1_src(data)                                           ((0x00020000&(data))>>17)
#define VI_C2OBUFF_get_write_enable1(data)                                           ((0x00020000&(data))>>17)
#define VI_C2OBUFF_start_shift                                                       (9)
#define VI_C2OBUFF_start_mask                                                        (0x0001FE00)
#define VI_C2OBUFF_start(data)                                                       (0x0001FE00&((data)<<9))
#define VI_C2OBUFF_start_src(data)                                                   ((0x0001FE00&(data))>>9)
#define VI_C2OBUFF_get_start(data)                                                   ((0x0001FE00&(data))>>9)
#define VI_C2OBUFF_write_enable2_shift                                               (8)
#define VI_C2OBUFF_write_enable2_mask                                                (0x00000100)
#define VI_C2OBUFF_write_enable2(data)                                               (0x00000100&((data)<<8))
#define VI_C2OBUFF_write_enable2_src(data)                                           ((0x00000100&(data))>>8)
#define VI_C2OBUFF_get_write_enable2(data)                                           ((0x00000100&(data))>>8)
#define VI_C2OBUFF_end_shift                                                         (0)
#define VI_C2OBUFF_end_mask                                                          (0x000000FF)
#define VI_C2OBUFF_end(data)                                                         (0x000000FF&((data)<<0))
#define VI_C2OBUFF_end_src(data)                                                     ((0x000000FF&(data))>>0)
#define VI_C2OBUFF_get_end(data)                                                     ((0x000000FF&(data))>>0)


#define VI_VBI1OBUFF                                                                 0x18004544
#define VI_VBI1OBUFF_reg_addr                                                        "0xB8004544"
#define VI_VBI1OBUFF_reg                                                             0xB8004544
#define VI_VBI1OBUFF_inst_adr                                                        "0x0051"
#define VI_VBI1OBUFF_inst                                                            0x0051
#define VI_VBI1OBUFF_write_enable1_shift                                             (17)
#define VI_VBI1OBUFF_write_enable1_mask                                              (0x00020000)
#define VI_VBI1OBUFF_write_enable1(data)                                             (0x00020000&((data)<<17))
#define VI_VBI1OBUFF_write_enable1_src(data)                                         ((0x00020000&(data))>>17)
#define VI_VBI1OBUFF_get_write_enable1(data)                                         ((0x00020000&(data))>>17)
#define VI_VBI1OBUFF_start_shift                                                     (9)
#define VI_VBI1OBUFF_start_mask                                                      (0x0001FE00)
#define VI_VBI1OBUFF_start(data)                                                     (0x0001FE00&((data)<<9))
#define VI_VBI1OBUFF_start_src(data)                                                 ((0x0001FE00&(data))>>9)
#define VI_VBI1OBUFF_get_start(data)                                                 ((0x0001FE00&(data))>>9)
#define VI_VBI1OBUFF_write_enable2_shift                                             (8)
#define VI_VBI1OBUFF_write_enable2_mask                                              (0x00000100)
#define VI_VBI1OBUFF_write_enable2(data)                                             (0x00000100&((data)<<8))
#define VI_VBI1OBUFF_write_enable2_src(data)                                         ((0x00000100&(data))>>8)
#define VI_VBI1OBUFF_get_write_enable2(data)                                         ((0x00000100&(data))>>8)
#define VI_VBI1OBUFF_end_shift                                                       (0)
#define VI_VBI1OBUFF_end_mask                                                        (0x000000FF)
#define VI_VBI1OBUFF_end(data)                                                       (0x000000FF&((data)<<0))
#define VI_VBI1OBUFF_end_src(data)                                                   ((0x000000FF&(data))>>0)
#define VI_VBI1OBUFF_get_end(data)                                                   ((0x000000FF&(data))>>0)


#define VI_VBI2OBUFF                                                                 0x18004548
#define VI_VBI2OBUFF_reg_addr                                                        "0xB8004548"
#define VI_VBI2OBUFF_reg                                                             0xB8004548
#define VI_VBI2OBUFF_inst_adr                                                        "0x0052"
#define VI_VBI2OBUFF_inst                                                            0x0052
#define VI_VBI2OBUFF_write_enable1_shift                                             (17)
#define VI_VBI2OBUFF_write_enable1_mask                                              (0x00020000)
#define VI_VBI2OBUFF_write_enable1(data)                                             (0x00020000&((data)<<17))
#define VI_VBI2OBUFF_write_enable1_src(data)                                         ((0x00020000&(data))>>17)
#define VI_VBI2OBUFF_get_write_enable1(data)                                         ((0x00020000&(data))>>17)
#define VI_VBI2OBUFF_start_shift                                                     (9)
#define VI_VBI2OBUFF_start_mask                                                      (0x0001FE00)
#define VI_VBI2OBUFF_start(data)                                                     (0x0001FE00&((data)<<9))
#define VI_VBI2OBUFF_start_src(data)                                                 ((0x0001FE00&(data))>>9)
#define VI_VBI2OBUFF_get_start(data)                                                 ((0x0001FE00&(data))>>9)
#define VI_VBI2OBUFF_write_enable2_shift                                             (8)
#define VI_VBI2OBUFF_write_enable2_mask                                              (0x00000100)
#define VI_VBI2OBUFF_write_enable2(data)                                             (0x00000100&((data)<<8))
#define VI_VBI2OBUFF_write_enable2_src(data)                                         ((0x00000100&(data))>>8)
#define VI_VBI2OBUFF_get_write_enable2(data)                                         ((0x00000100&(data))>>8)
#define VI_VBI2OBUFF_end_shift                                                       (0)
#define VI_VBI2OBUFF_end_mask                                                        (0x000000FF)
#define VI_VBI2OBUFF_end(data)                                                       (0x000000FF&((data)<<0))
#define VI_VBI2OBUFF_end_src(data)                                                   ((0x000000FF&(data))>>0)
#define VI_VBI2OBUFF_get_end(data)                                                   ((0x000000FF&(data))>>0)


#define VI_DYOBUFF                                                                   0x1800454c
#define VI_DYOBUFF_reg_addr                                                          "0xB800454C"
#define VI_DYOBUFF_reg                                                               0xB800454C
#define VI_DYOBUFF_inst_adr                                                          "0x0053"
#define VI_DYOBUFF_inst                                                              0x0053
#define VI_DYOBUFF_write_enable1_shift                                               (17)
#define VI_DYOBUFF_write_enable1_mask                                                (0x00020000)
#define VI_DYOBUFF_write_enable1(data)                                               (0x00020000&((data)<<17))
#define VI_DYOBUFF_write_enable1_src(data)                                           ((0x00020000&(data))>>17)
#define VI_DYOBUFF_get_write_enable1(data)                                           ((0x00020000&(data))>>17)
#define VI_DYOBUFF_start_shift                                                       (9)
#define VI_DYOBUFF_start_mask                                                        (0x0001FE00)
#define VI_DYOBUFF_start(data)                                                       (0x0001FE00&((data)<<9))
#define VI_DYOBUFF_start_src(data)                                                   ((0x0001FE00&(data))>>9)
#define VI_DYOBUFF_get_start(data)                                                   ((0x0001FE00&(data))>>9)
#define VI_DYOBUFF_write_enable2_shift                                               (8)
#define VI_DYOBUFF_write_enable2_mask                                                (0x00000100)
#define VI_DYOBUFF_write_enable2(data)                                               (0x00000100&((data)<<8))
#define VI_DYOBUFF_write_enable2_src(data)                                           ((0x00000100&(data))>>8)
#define VI_DYOBUFF_get_write_enable2(data)                                           ((0x00000100&(data))>>8)
#define VI_DYOBUFF_end_shift                                                         (0)
#define VI_DYOBUFF_end_mask                                                          (0x000000FF)
#define VI_DYOBUFF_end(data)                                                         (0x000000FF&((data)<<0))
#define VI_DYOBUFF_end_src(data)                                                     ((0x000000FF&(data))>>0)
#define VI_DYOBUFF_get_end(data)                                                     ((0x000000FF&(data))>>0)


#define VI_DYEXTOBUFF                                                                0x18004550
#define VI_DYEXTOBUFF_reg_addr                                                       "0xB8004550"
#define VI_DYEXTOBUFF_reg                                                            0xB8004550
#define VI_DYEXTOBUFF_inst_adr                                                       "0x0054"
#define VI_DYEXTOBUFF_inst                                                           0x0054
#define VI_DYEXTOBUFF_write_enable1_shift                                            (17)
#define VI_DYEXTOBUFF_write_enable1_mask                                             (0x00020000)
#define VI_DYEXTOBUFF_write_enable1(data)                                            (0x00020000&((data)<<17))
#define VI_DYEXTOBUFF_write_enable1_src(data)                                        ((0x00020000&(data))>>17)
#define VI_DYEXTOBUFF_get_write_enable1(data)                                        ((0x00020000&(data))>>17)
#define VI_DYEXTOBUFF_start_shift                                                    (9)
#define VI_DYEXTOBUFF_start_mask                                                     (0x0001FE00)
#define VI_DYEXTOBUFF_start(data)                                                    (0x0001FE00&((data)<<9))
#define VI_DYEXTOBUFF_start_src(data)                                                ((0x0001FE00&(data))>>9)
#define VI_DYEXTOBUFF_get_start(data)                                                ((0x0001FE00&(data))>>9)
#define VI_DYEXTOBUFF_write_enable2_shift                                            (8)
#define VI_DYEXTOBUFF_write_enable2_mask                                             (0x00000100)
#define VI_DYEXTOBUFF_write_enable2(data)                                            (0x00000100&((data)<<8))
#define VI_DYEXTOBUFF_write_enable2_src(data)                                        ((0x00000100&(data))>>8)
#define VI_DYEXTOBUFF_get_write_enable2(data)                                        ((0x00000100&(data))>>8)
#define VI_DYEXTOBUFF_end_shift                                                      (0)
#define VI_DYEXTOBUFF_end_mask                                                       (0x000000FF)
#define VI_DYEXTOBUFF_end(data)                                                      (0x000000FF&((data)<<0))
#define VI_DYEXTOBUFF_end_src(data)                                                  ((0x000000FF&(data))>>0)
#define VI_DYEXTOBUFF_get_end(data)                                                  ((0x000000FF&(data))>>0)


#define VI_HDY1OBUFF                                                                 0x18004554
#define VI_HDY1OBUFF_reg_addr                                                        "0xB8004554"
#define VI_HDY1OBUFF_reg                                                             0xB8004554
#define VI_HDY1OBUFF_inst_adr                                                        "0x0055"
#define VI_HDY1OBUFF_inst                                                            0x0055
#define VI_HDY1OBUFF_write_enable1_shift                                             (17)
#define VI_HDY1OBUFF_write_enable1_mask                                              (0x00020000)
#define VI_HDY1OBUFF_write_enable1(data)                                             (0x00020000&((data)<<17))
#define VI_HDY1OBUFF_write_enable1_src(data)                                         ((0x00020000&(data))>>17)
#define VI_HDY1OBUFF_get_write_enable1(data)                                         ((0x00020000&(data))>>17)
#define VI_HDY1OBUFF_start_shift                                                     (9)
#define VI_HDY1OBUFF_start_mask                                                      (0x0001FE00)
#define VI_HDY1OBUFF_start(data)                                                     (0x0001FE00&((data)<<9))
#define VI_HDY1OBUFF_start_src(data)                                                 ((0x0001FE00&(data))>>9)
#define VI_HDY1OBUFF_get_start(data)                                                 ((0x0001FE00&(data))>>9)
#define VI_HDY1OBUFF_write_enable2_shift                                             (8)
#define VI_HDY1OBUFF_write_enable2_mask                                              (0x00000100)
#define VI_HDY1OBUFF_write_enable2(data)                                             (0x00000100&((data)<<8))
#define VI_HDY1OBUFF_write_enable2_src(data)                                         ((0x00000100&(data))>>8)
#define VI_HDY1OBUFF_get_write_enable2(data)                                         ((0x00000100&(data))>>8)
#define VI_HDY1OBUFF_end_shift                                                       (0)
#define VI_HDY1OBUFF_end_mask                                                        (0x000000FF)
#define VI_HDY1OBUFF_end(data)                                                       (0x000000FF&((data)<<0))
#define VI_HDY1OBUFF_end_src(data)                                                   ((0x000000FF&(data))>>0)
#define VI_HDY1OBUFF_get_end(data)                                                   ((0x000000FF&(data))>>0)


#define VI_HDY2OBUFF                                                                 0x18004558
#define VI_HDY2OBUFF_reg_addr                                                        "0xB8004558"
#define VI_HDY2OBUFF_reg                                                             0xB8004558
#define VI_HDY2OBUFF_inst_adr                                                        "0x0056"
#define VI_HDY2OBUFF_inst                                                            0x0056
#define VI_HDY2OBUFF_write_enable1_shift                                             (17)
#define VI_HDY2OBUFF_write_enable1_mask                                              (0x00020000)
#define VI_HDY2OBUFF_write_enable1(data)                                             (0x00020000&((data)<<17))
#define VI_HDY2OBUFF_write_enable1_src(data)                                         ((0x00020000&(data))>>17)
#define VI_HDY2OBUFF_get_write_enable1(data)                                         ((0x00020000&(data))>>17)
#define VI_HDY2OBUFF_start_shift                                                     (9)
#define VI_HDY2OBUFF_start_mask                                                      (0x0001FE00)
#define VI_HDY2OBUFF_start(data)                                                     (0x0001FE00&((data)<<9))
#define VI_HDY2OBUFF_start_src(data)                                                 ((0x0001FE00&(data))>>9)
#define VI_HDY2OBUFF_get_start(data)                                                 ((0x0001FE00&(data))>>9)
#define VI_HDY2OBUFF_write_enable2_shift                                             (8)
#define VI_HDY2OBUFF_write_enable2_mask                                              (0x00000100)
#define VI_HDY2OBUFF_write_enable2(data)                                             (0x00000100&((data)<<8))
#define VI_HDY2OBUFF_write_enable2_src(data)                                         ((0x00000100&(data))>>8)
#define VI_HDY2OBUFF_get_write_enable2(data)                                         ((0x00000100&(data))>>8)
#define VI_HDY2OBUFF_end_shift                                                       (0)
#define VI_HDY2OBUFF_end_mask                                                        (0x000000FF)
#define VI_HDY2OBUFF_end(data)                                                       (0x000000FF&((data)<<0))
#define VI_HDY2OBUFF_end_src(data)                                                   ((0x000000FF&(data))>>0)
#define VI_HDY2OBUFF_get_end(data)                                                   ((0x000000FF&(data))>>0)


#define VI_HDC1OBUFF                                                                 0x1800455c
#define VI_HDC1OBUFF_reg_addr                                                        "0xB800455C"
#define VI_HDC1OBUFF_reg                                                             0xB800455C
#define VI_HDC1OBUFF_inst_adr                                                        "0x0057"
#define VI_HDC1OBUFF_inst                                                            0x0057
#define VI_HDC1OBUFF_write_enable1_shift                                             (17)
#define VI_HDC1OBUFF_write_enable1_mask                                              (0x00020000)
#define VI_HDC1OBUFF_write_enable1(data)                                             (0x00020000&((data)<<17))
#define VI_HDC1OBUFF_write_enable1_src(data)                                         ((0x00020000&(data))>>17)
#define VI_HDC1OBUFF_get_write_enable1(data)                                         ((0x00020000&(data))>>17)
#define VI_HDC1OBUFF_start_shift                                                     (9)
#define VI_HDC1OBUFF_start_mask                                                      (0x0001FE00)
#define VI_HDC1OBUFF_start(data)                                                     (0x0001FE00&((data)<<9))
#define VI_HDC1OBUFF_start_src(data)                                                 ((0x0001FE00&(data))>>9)
#define VI_HDC1OBUFF_get_start(data)                                                 ((0x0001FE00&(data))>>9)
#define VI_HDC1OBUFF_write_enable2_shift                                             (8)
#define VI_HDC1OBUFF_write_enable2_mask                                              (0x00000100)
#define VI_HDC1OBUFF_write_enable2(data)                                             (0x00000100&((data)<<8))
#define VI_HDC1OBUFF_write_enable2_src(data)                                         ((0x00000100&(data))>>8)
#define VI_HDC1OBUFF_get_write_enable2(data)                                         ((0x00000100&(data))>>8)
#define VI_HDC1OBUFF_end_shift                                                       (0)
#define VI_HDC1OBUFF_end_mask                                                        (0x000000FF)
#define VI_HDC1OBUFF_end(data)                                                       (0x000000FF&((data)<<0))
#define VI_HDC1OBUFF_end_src(data)                                                   ((0x000000FF&(data))>>0)
#define VI_HDC1OBUFF_get_end(data)                                                   ((0x000000FF&(data))>>0)


#define VI_HDC2OBUFF                                                                 0x18004560
#define VI_HDC2OBUFF_reg_addr                                                        "0xB8004560"
#define VI_HDC2OBUFF_reg                                                             0xB8004560
#define VI_HDC2OBUFF_inst_adr                                                        "0x0058"
#define VI_HDC2OBUFF_inst                                                            0x0058
#define VI_HDC2OBUFF_write_enable1_shift                                             (17)
#define VI_HDC2OBUFF_write_enable1_mask                                              (0x00020000)
#define VI_HDC2OBUFF_write_enable1(data)                                             (0x00020000&((data)<<17))
#define VI_HDC2OBUFF_write_enable1_src(data)                                         ((0x00020000&(data))>>17)
#define VI_HDC2OBUFF_get_write_enable1(data)                                         ((0x00020000&(data))>>17)
#define VI_HDC2OBUFF_start_shift                                                     (9)
#define VI_HDC2OBUFF_start_mask                                                      (0x0001FE00)
#define VI_HDC2OBUFF_start(data)                                                     (0x0001FE00&((data)<<9))
#define VI_HDC2OBUFF_start_src(data)                                                 ((0x0001FE00&(data))>>9)
#define VI_HDC2OBUFF_get_start(data)                                                 ((0x0001FE00&(data))>>9)
#define VI_HDC2OBUFF_write_enable2_shift                                             (8)
#define VI_HDC2OBUFF_write_enable2_mask                                              (0x00000100)
#define VI_HDC2OBUFF_write_enable2(data)                                             (0x00000100&((data)<<8))
#define VI_HDC2OBUFF_write_enable2_src(data)                                         ((0x00000100&(data))>>8)
#define VI_HDC2OBUFF_get_write_enable2(data)                                         ((0x00000100&(data))>>8)
#define VI_HDC2OBUFF_end_shift                                                       (0)
#define VI_HDC2OBUFF_end_mask                                                        (0x000000FF)
#define VI_HDC2OBUFF_end(data)                                                       (0x000000FF&((data)<<0))
#define VI_HDC2OBUFF_end_src(data)                                                   ((0x000000FF&(data))>>0)
#define VI_HDC2OBUFF_get_end(data)                                                   ((0x000000FF&(data))>>0)


#define VI_Y1EXTOBUFF                                                                0x18004564
#define VI_Y1EXTOBUFF_reg_addr                                                       "0xB8004564"
#define VI_Y1EXTOBUFF_reg                                                            0xB8004564
#define VI_Y1EXTOBUFF_inst_adr                                                       "0x0059"
#define VI_Y1EXTOBUFF_inst                                                           0x0059
#define VI_Y1EXTOBUFF_write_enable1_shift                                            (17)
#define VI_Y1EXTOBUFF_write_enable1_mask                                             (0x00020000)
#define VI_Y1EXTOBUFF_write_enable1(data)                                            (0x00020000&((data)<<17))
#define VI_Y1EXTOBUFF_write_enable1_src(data)                                        ((0x00020000&(data))>>17)
#define VI_Y1EXTOBUFF_get_write_enable1(data)                                        ((0x00020000&(data))>>17)
#define VI_Y1EXTOBUFF_start_shift                                                    (9)
#define VI_Y1EXTOBUFF_start_mask                                                     (0x0001FE00)
#define VI_Y1EXTOBUFF_start(data)                                                    (0x0001FE00&((data)<<9))
#define VI_Y1EXTOBUFF_start_src(data)                                                ((0x0001FE00&(data))>>9)
#define VI_Y1EXTOBUFF_get_start(data)                                                ((0x0001FE00&(data))>>9)
#define VI_Y1EXTOBUFF_write_enable2_shift                                            (8)
#define VI_Y1EXTOBUFF_write_enable2_mask                                             (0x00000100)
#define VI_Y1EXTOBUFF_write_enable2(data)                                            (0x00000100&((data)<<8))
#define VI_Y1EXTOBUFF_write_enable2_src(data)                                        ((0x00000100&(data))>>8)
#define VI_Y1EXTOBUFF_get_write_enable2(data)                                        ((0x00000100&(data))>>8)
#define VI_Y1EXTOBUFF_end_shift                                                      (0)
#define VI_Y1EXTOBUFF_end_mask                                                       (0x000000FF)
#define VI_Y1EXTOBUFF_end(data)                                                      (0x000000FF&((data)<<0))
#define VI_Y1EXTOBUFF_end_src(data)                                                  ((0x000000FF&(data))>>0)
#define VI_Y1EXTOBUFF_get_end(data)                                                  ((0x000000FF&(data))>>0)


#define VI_Y2EXTOBUFF                                                                0x18004568
#define VI_Y2EXTOBUFF_reg_addr                                                       "0xB8004568"
#define VI_Y2EXTOBUFF_reg                                                            0xB8004568
#define VI_Y2EXTOBUFF_inst_adr                                                       "0x005A"
#define VI_Y2EXTOBUFF_inst                                                           0x005A
#define VI_Y2EXTOBUFF_write_enable1_shift                                            (17)
#define VI_Y2EXTOBUFF_write_enable1_mask                                             (0x00020000)
#define VI_Y2EXTOBUFF_write_enable1(data)                                            (0x00020000&((data)<<17))
#define VI_Y2EXTOBUFF_write_enable1_src(data)                                        ((0x00020000&(data))>>17)
#define VI_Y2EXTOBUFF_get_write_enable1(data)                                        ((0x00020000&(data))>>17)
#define VI_Y2EXTOBUFF_start_shift                                                    (9)
#define VI_Y2EXTOBUFF_start_mask                                                     (0x0001FE00)
#define VI_Y2EXTOBUFF_start(data)                                                    (0x0001FE00&((data)<<9))
#define VI_Y2EXTOBUFF_start_src(data)                                                ((0x0001FE00&(data))>>9)
#define VI_Y2EXTOBUFF_get_start(data)                                                ((0x0001FE00&(data))>>9)
#define VI_Y2EXTOBUFF_write_enable2_shift                                            (8)
#define VI_Y2EXTOBUFF_write_enable2_mask                                             (0x00000100)
#define VI_Y2EXTOBUFF_write_enable2(data)                                            (0x00000100&((data)<<8))
#define VI_Y2EXTOBUFF_write_enable2_src(data)                                        ((0x00000100&(data))>>8)
#define VI_Y2EXTOBUFF_get_write_enable2(data)                                        ((0x00000100&(data))>>8)
#define VI_Y2EXTOBUFF_end_shift                                                      (0)
#define VI_Y2EXTOBUFF_end_mask                                                       (0x000000FF)
#define VI_Y2EXTOBUFF_end(data)                                                      (0x000000FF&((data)<<0))
#define VI_Y2EXTOBUFF_end_src(data)                                                  ((0x000000FF&(data))>>0)
#define VI_Y2EXTOBUFF_get_end(data)                                                  ((0x000000FF&(data))>>0)


#define VI_FA_ADDR                                                                   0x180044a8
#define VI_FA_ADDR_reg_addr                                                          "0xB80044A8"
#define VI_FA_ADDR_reg                                                               0xB80044A8
#define VI_FA_ADDR_inst_adr                                                          "0x002A"
#define VI_FA_ADDR_inst                                                              0x002A
#define VI_FA_ADDR_write_enable1_shift                                               (13)
#define VI_FA_ADDR_write_enable1_mask                                                (0x00002000)
#define VI_FA_ADDR_write_enable1(data)                                               (0x00002000&((data)<<13))
#define VI_FA_ADDR_write_enable1_src(data)                                           ((0x00002000&(data))>>13)
#define VI_FA_ADDR_get_write_enable1(data)                                           ((0x00002000&(data))>>13)
#define VI_FA_ADDR_fa_enable_shift                                                   (12)
#define VI_FA_ADDR_fa_enable_mask                                                    (0x00001000)
#define VI_FA_ADDR_fa_enable(data)                                                   (0x00001000&((data)<<12))
#define VI_FA_ADDR_fa_enable_src(data)                                               ((0x00001000&(data))>>12)
#define VI_FA_ADDR_get_fa_enable(data)                                               ((0x00001000&(data))>>12)
#define VI_FA_ADDR_write_enable2_shift                                               (11)
#define VI_FA_ADDR_write_enable2_mask                                                (0x00000800)
#define VI_FA_ADDR_write_enable2(data)                                               (0x00000800&((data)<<11))
#define VI_FA_ADDR_write_enable2_src(data)                                           ((0x00000800&(data))>>11)
#define VI_FA_ADDR_get_write_enable2(data)                                           ((0x00000800&(data))>>11)
#define VI_FA_ADDR_fa_buffer_sel_shift                                               (10)
#define VI_FA_ADDR_fa_buffer_sel_mask                                                (0x00000400)
#define VI_FA_ADDR_fa_buffer_sel(data)                                               (0x00000400&((data)<<10))
#define VI_FA_ADDR_fa_buffer_sel_src(data)                                           ((0x00000400&(data))>>10)
#define VI_FA_ADDR_get_fa_buffer_sel(data)                                           ((0x00000400&(data))>>10)
#define VI_FA_ADDR_write_enable3_shift                                               (9)
#define VI_FA_ADDR_write_enable3_mask                                                (0x00000200)
#define VI_FA_ADDR_write_enable3(data)                                               (0x00000200&((data)<<9))
#define VI_FA_ADDR_write_enable3_src(data)                                           ((0x00000200&(data))>>9)
#define VI_FA_ADDR_get_write_enable3(data)                                           ((0x00000200&(data))>>9)
#define VI_FA_ADDR_fa_addr_2_shift                                                   (0)
#define VI_FA_ADDR_fa_addr_2_mask                                                    (0x000001FF)
#define VI_FA_ADDR_fa_addr_2(data)                                                   (0x000001FF&((data)<<0))
#define VI_FA_ADDR_fa_addr_2_src(data)                                               ((0x000001FF&(data))>>0)
#define VI_FA_ADDR_get_fa_addr_2(data)                                               ((0x000001FF&(data))>>0)


#define VI_FA_DATA_MSB                                                               0x180044ac
#define VI_FA_DATA_MSB_reg_addr                                                      "0xB80044AC"
#define VI_FA_DATA_MSB_reg                                                           0xB80044AC
#define VI_FA_DATA_MSB_inst_adr                                                      "0x002B"
#define VI_FA_DATA_MSB_inst                                                          0x002B
#define VI_FA_DATA_MSB_data_shift                                                    (0)
#define VI_FA_DATA_MSB_data_mask                                                     (0xFFFFFFFF)
#define VI_FA_DATA_MSB_data(data)                                                    (0xFFFFFFFF&((data)<<0))
#define VI_FA_DATA_MSB_data_src(data)                                                ((0xFFFFFFFF&(data))>>0)
#define VI_FA_DATA_MSB_get_data(data)                                                ((0xFFFFFFFF&(data))>>0)


#define VI_FA_DATA_LSB                                                               0x18004570
#define VI_FA_DATA_LSB_reg_addr                                                      "0xB8004570"
#define VI_FA_DATA_LSB_reg                                                           0xB8004570
#define VI_FA_DATA_LSB_inst_adr                                                      "0x005C"
#define VI_FA_DATA_LSB_inst                                                          0x005C
#define VI_FA_DATA_LSB_data_shift                                                    (0)
#define VI_FA_DATA_LSB_data_mask                                                     (0xFFFFFFFF)
#define VI_FA_DATA_LSB_data(data)                                                    (0xFFFFFFFF&((data)<<0))
#define VI_FA_DATA_LSB_data_src(data)                                                ((0xFFFFFFFF&(data))>>0)
#define VI_FA_DATA_LSB_get_data(data)                                                ((0xFFFFFFFF&(data))>>0)


#define VI_DBG                                                                       0x18004284
#define VI_DBG_reg_addr                                                              "0xB8004284"
#define VI_DBG_reg                                                                   0xB8004284
#define VI_DBG_inst_adr                                                              "0x00A1"
#define VI_DBG_inst                                                                  0x00A1
#define VI_DBG_write_enable1_shift                                                   (17)
#define VI_DBG_write_enable1_mask                                                    (0x00020000)
#define VI_DBG_write_enable1(data)                                                   (0x00020000&((data)<<17))
#define VI_DBG_write_enable1_src(data)                                               ((0x00020000&(data))>>17)
#define VI_DBG_get_write_enable1(data)                                               ((0x00020000&(data))>>17)
#define VI_DBG_sel0_shift                                                            (10)
#define VI_DBG_sel0_mask                                                             (0x0001FC00)
#define VI_DBG_sel0(data)                                                            (0x0001FC00&((data)<<10))
#define VI_DBG_sel0_src(data)                                                        ((0x0001FC00&(data))>>10)
#define VI_DBG_get_sel0(data)                                                        ((0x0001FC00&(data))>>10)
#define VI_DBG_write_enable2_shift                                                   (9)
#define VI_DBG_write_enable2_mask                                                    (0x00000200)
#define VI_DBG_write_enable2(data)                                                   (0x00000200&((data)<<9))
#define VI_DBG_write_enable2_src(data)                                               ((0x00000200&(data))>>9)
#define VI_DBG_get_write_enable2(data)                                               ((0x00000200&(data))>>9)
#define VI_DBG_sel1_shift                                                            (2)
#define VI_DBG_sel1_mask                                                             (0x000001FC)
#define VI_DBG_sel1(data)                                                            (0x000001FC&((data)<<2))
#define VI_DBG_sel1_src(data)                                                        ((0x000001FC&(data))>>2)
#define VI_DBG_get_sel1(data)                                                        ((0x000001FC&(data))>>2)
#define VI_DBG_write_enable3_shift                                                   (1)
#define VI_DBG_write_enable3_mask                                                    (0x00000002)
#define VI_DBG_write_enable3(data)                                                   (0x00000002&((data)<<1))
#define VI_DBG_write_enable3_src(data)                                               ((0x00000002&(data))>>1)
#define VI_DBG_get_write_enable3(data)                                               ((0x00000002&(data))>>1)
#define VI_DBG_enable_shift                                                          (0)
#define VI_DBG_enable_mask                                                           (0x00000001)
#define VI_DBG_enable(data)                                                          (0x00000001&((data)<<0))
#define VI_DBG_enable_src(data)                                                      ((0x00000001&(data))>>0)
#define VI_DBG_get_enable(data)                                                      ((0x00000001&(data))>>0)


#define VI_DUMMY                                                                     0x18004584
#define VI_DUMMY_reg_addr                                                            "0xB8004584"
#define VI_DUMMY_reg                                                                 0xB8004584
#define VI_DUMMY_inst_adr                                                            "0x0061"
#define VI_DUMMY_inst                                                                0x0061
#define VI_DUMMY_dummy_shift                                                         (0)
#define VI_DUMMY_dummy_mask                                                          (0xFFFFFFFF)
#define VI_DUMMY_dummy(data)                                                         (0xFFFFFFFF&((data)<<0))
#define VI_DUMMY_dummy_src(data)                                                     ((0xFFFFFFFF&(data))>>0)
#define VI_DUMMY_get_dummy(data)                                                     ((0xFFFFFFFF&(data))>>0)


#endif
