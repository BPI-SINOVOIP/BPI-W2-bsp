// This file is generated using the spec version 0.99, firmware template version 1.39and DVR_Parser_0.43
#ifndef _VO_REG_H_INCLUDED_
#define _VO_REG_H_INCLUDED_


typedef struct
{
  unsigned char  y ;
  unsigned char cb ;
  unsigned char cr ;
} VO_COLOR ;

//#define _VO_USE_STRUCT
#ifdef _VO_USE_STRUCT

typedef struct
{
    unsigned int    reserved_0:30;
    unsigned int    mode:2;
}vo_V1MODE;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    write_enable1:1;
    unsigned int    scoe:1;
    unsigned int    write_enable2:1;
    unsigned int    reintle:1;
    unsigned int    write_enable3:1;
    unsigned int    reintlt:1;
    unsigned int    write_enable4:1;
    unsigned int    cvde:1;
    unsigned int    write_enable5:1;
    unsigned int    cvdtp:2;
}vo_V1SCO;

typedef struct
{
    unsigned int    reserved_0:26;
    unsigned int    write_enable1:1;
    unsigned int    vdimd:3;
    unsigned int    write_enable2:1;
    unsigned int    topfield:1;
}vo_V1DIMD;

typedef struct
{
    unsigned int    reserved_0:30;
    unsigned int    mode:2;
}vo_TELECINE;

typedef struct
{
    unsigned int    reserved_0:9;
    unsigned int    write_enable1:1;
    unsigned int    th:9;
    unsigned int    write_enable2:1;
    unsigned int    wad:12;
}vo_WADTB;

typedef struct
{
    unsigned int    reserved_0:12;
    unsigned int    write_enable1:1;
    unsigned int    vstart:9;
    unsigned int    write_enable2:1;
    unsigned int    vend:9;
}vo_TWV1;

typedef struct
{
    unsigned int    reserved_0:12;
    unsigned int    write_enable1:1;
    unsigned int    vstart:9;
    unsigned int    write_enable2:1;
    unsigned int    vend:9;
}vo_CTWV1;

typedef struct
{
    unsigned int    reserved_0:10;
    unsigned int    write_enable1:1;
    unsigned int    hstart:10;
    unsigned int    write_enable2:1;
    unsigned int    hsize:10;
}vo_TWH1;

typedef struct
{
    unsigned int    reserved_0:7;
    unsigned int    pnswad:25;
}vo_YPNSWAD1;

typedef struct
{
    unsigned int    reserved_0:7;
    unsigned int    pcswad:25;
}vo_YPCSWAD1;

typedef struct
{
    unsigned int    reserved_0:7;
    unsigned int    ncswad:25;
}vo_YNCSWAD1;

typedef struct
{
    unsigned int    reserved_0:7;
    unsigned int    pnthreld:25;
}vo_YPNTHRELD1;

typedef struct
{
    unsigned int    reserved_0:7;
    unsigned int    pcthreld:25;
}vo_YPCTHRELD1;

typedef struct
{
    unsigned int    reserved_0:7;
    unsigned int    ncthreld:25;
}vo_YNCTHRELD1;

typedef struct
{
    unsigned int    reserved_0:7;
    unsigned int    pnswad:25;
}vo_CPNSWAD1;

typedef struct
{
    unsigned int    reserved_0:7;
    unsigned int    pcswad:25;
}vo_CPCSWAD1;

typedef struct
{
    unsigned int    reserved_0:7;
    unsigned int    ncswad:25;
}vo_CNCSWAD1;

typedef struct
{
    unsigned int    reserved_0:7;
    unsigned int    pnthreld:25;
}vo_CPNTHRELD1;

typedef struct
{
    unsigned int    reserved_0:7;
    unsigned int    pcthreld:25;
}vo_CPCTHRELD1;

typedef struct
{
    unsigned int    reserved_0:7;
    unsigned int    ncthreld:25;
}vo_CNCTHRELD1;

typedef struct
{
    unsigned int    reserved_0:1;
    unsigned int    write_enable1:1;
    unsigned int    candinum:2;
    unsigned int    write_enable2:1;
    unsigned int    thpositive:5;
    unsigned int    write_enable3:1;
    unsigned int    thnegative:6;
    unsigned int    write_enable4:1;
    unsigned int    thcompdecision:7;
    unsigned int    write_enable5:1;
    unsigned int    thcompreverse:6;
}vo_YBOB;

typedef struct
{
    unsigned int    reserved_0:10;
    unsigned int    write_enable1:1;
    unsigned int    weavemode:1;
    unsigned int    write_enable2:1;
    unsigned int    thrnoisesp:5;
    unsigned int    write_enable3:1;
    unsigned int    thrstilly:6;
    unsigned int    write_enable4:1;
    unsigned int    thrstillc:6;
}vo_NOISETH;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    lastline:11;
}vo_STILL;

typedef struct
{
    unsigned int    reserved_0:19;
    unsigned int    write_enable1:1;
    unsigned int    thrblndlow:8;
    unsigned int    write_enable2:1;
    unsigned int    thrblnddiff2:3;
}vo_YBLEND;

typedef struct
{
    unsigned int    reserved_0:19;
    unsigned int    write_enable1:1;
    unsigned int    thrblndlow:8;
    unsigned int    write_enable2:1;
    unsigned int    thrblnddiff2:3;
}vo_CBLEND;

typedef struct
{
    unsigned int    reserved_0:23;
    unsigned int    y4ch:1;
    unsigned int    c4ch:1;
    unsigned int    yen:1;
    unsigned int    yoddtype:1;
    unsigned int    y2tap:1;
    unsigned int    cen:1;
    unsigned int    coddtype:1;
    unsigned int    c2tap:1;
    unsigned int    write_data:1;
}vo_VSCCTL1;

typedef struct
{
    unsigned int    reserved_0:2;
    unsigned int    write_enable1:1;
    unsigned int    yonp:11;
    unsigned int    write_enable2:1;
    unsigned int    ydphs:17;
}vo_VYSC1;

typedef struct
{
    unsigned int    reserved_0:2;
    unsigned int    write_enable1:1;
    unsigned int    conp:11;
    unsigned int    write_enable2:1;
    unsigned int    cdphs:17;
}vo_VCSC1;

typedef struct
{
    unsigned int    reserved_0:7;
    unsigned int    init_offset:11;
    unsigned int    init_phase:14;
}vo_VYIPOS1;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    endline:11;
}vo_VYEPOS1;

typedef struct
{
    unsigned int    reserved_0:7;
    unsigned int    init_offset:11;
    unsigned int    init_phase:14;
}vo_VCIPOS1;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    endline:11;
}vo_VCEPOS1;

typedef struct
{
    unsigned int    reserved_0:18;
    unsigned int    ysccoef:14;
}vo_VYSCCOEF1;

typedef struct
{
    unsigned int    reserved_0:18;
    unsigned int    csccoef:14;
}vo_VCSCCOEF1;

typedef struct
{
    unsigned int    reserved_0:27;
    unsigned int    yen:1;
    unsigned int    yoddtype:1;
    unsigned int    cen:1;
    unsigned int    coddtype:1;
    unsigned int    write_data:1;
}vo_HSCCTL1;

typedef struct
{
    unsigned int    reserved_0:2;
    unsigned int    write_enable1:1;
    unsigned int    yonp:11;
    unsigned int    write_enable2:1;
    unsigned int    ydphs:17;
}vo_HYSC1;

typedef struct
{
    unsigned int    reserved_0:18;
    unsigned int    init_phase:14;
}vo_HYIPOS1;

typedef struct
{
    unsigned int    reserved_0:10;
    unsigned int    begin_point:11;
    unsigned int    end_point:11;
}vo_HYEPOS1;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    shift:5;
    unsigned int    width:11;
}vo_HYWIDTH1;

typedef struct
{
    unsigned int    reserved_0:2;
    unsigned int    write_enable1:1;
    unsigned int    conp:11;
    unsigned int    write_enable2:1;
    unsigned int    cdphs:17;
}vo_HCSC1;

typedef struct
{
    unsigned int    reserved_0:18;
    unsigned int    init_phase:14;
}vo_HCIPOS1;

typedef struct
{
    unsigned int    reserved_0:10;
    unsigned int    begin_point:11;
    unsigned int    end_point:11;
}vo_HCEPOS1;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    shift:5;
    unsigned int    width:11;
}vo_HCWIDTH1;

typedef struct
{
    unsigned int    reserved_0:18;
    unsigned int    ysccoef:14;
}vo_HYSCCOEF1;

typedef struct
{
    unsigned int    reserved_0:18;
    unsigned int    csccoef:14;
}vo_HCSCCOEF1;

typedef struct
{
    unsigned int    reserved_0:29;
    unsigned int    weave:1;
    unsigned int    topfield:1;
    unsigned int    write_data:1;
}vo_V2WEAVE;

typedef struct
{
    unsigned int    reserved_0:27;
    unsigned int    yen:1;
    unsigned int    yoddtype:1;
    unsigned int    cen:1;
    unsigned int    coddtype:1;
    unsigned int    write_data:1;
}vo_VSCCTL2;

typedef struct
{
    unsigned int    reserved_0:3;
    unsigned int    write_enable1:1;
    unsigned int    yonp:10;
    unsigned int    write_enable2:1;
    unsigned int    ydphs:17;
}vo_VYSC2;

typedef struct
{
    unsigned int    reserved_0:3;
    unsigned int    write_enable1:1;
    unsigned int    conp:10;
    unsigned int    write_enable2:1;
    unsigned int    cdphs:17;
}vo_VCSC2;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    init_offset:10;
    unsigned int    init_phase:14;
}vo_VYIPOS2;

typedef struct
{
    unsigned int    reserved_0:22;
    unsigned int    endline:10;
}vo_VYEPOS2;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    init_offset:10;
    unsigned int    init_phase:14;
}vo_VCIPOS2;

typedef struct
{
    unsigned int    reserved_0:22;
    unsigned int    endline:10;
}vo_VCEPOS2;

typedef struct
{
    unsigned int    reserved_0:18;
    unsigned int    ysccoef:14;
}vo_VYSCCOEF2;

typedef struct
{
    unsigned int    reserved_0:18;
    unsigned int    csccoef:14;
}vo_VCSCCOEF2;

typedef struct
{
    unsigned int    reserved_0:27;
    unsigned int    yen:1;
    unsigned int    yoddtype:1;
    unsigned int    cen:1;
    unsigned int    coddtype:1;
    unsigned int    write_data:1;
}vo_HSCCTL2;

typedef struct
{
    unsigned int    reserved_0:2;
    unsigned int    write_enable1:1;
    unsigned int    yonp:11;
    unsigned int    write_enable2:1;
    unsigned int    ydphs:17;
}vo_HYSC2;

typedef struct
{
    unsigned int    reserved_0:18;
    unsigned int    init_phase:14;
}vo_HYIPOS2;

typedef struct
{
    unsigned int    reserved_0:10;
    unsigned int    begin_point:11;
    unsigned int    end_point:11;
}vo_HYEPOS2;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    shift:5;
    unsigned int    width:11;
}vo_HYWIDTH2;

typedef struct
{
    unsigned int    reserved_0:2;
    unsigned int    write_enable1:1;
    unsigned int    conp:11;
    unsigned int    write_enable2:1;
    unsigned int    cdphs:17;
}vo_HCSC2;

typedef struct
{
    unsigned int    reserved_0:18;
    unsigned int    init_phase:14;
}vo_HCIPOS2;

typedef struct
{
    unsigned int    reserved_0:10;
    unsigned int    begin_point:11;
    unsigned int    end_point:11;
}vo_HCEPOS2;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    shift:5;
    unsigned int    width:11;
}vo_HCWIDTH2;

typedef struct
{
    unsigned int    reserved_0:18;
    unsigned int    ysccoef:14;
}vo_HYSCCOEF2;

typedef struct
{
    unsigned int    reserved_0:18;
    unsigned int    csccoef:14;
}vo_HCSCCOEF2;

typedef struct
{
    unsigned int    reserved_0:11;
    unsigned int    write_enable1:1;
    unsigned int    en:1;
    unsigned int    write_enable2:1;
    unsigned int    size:18;
}vo_DUMP;

typedef struct
{
    unsigned int    reserved_0:19;
    unsigned int    write_enable1:1;
    unsigned int    en:1;
    unsigned int    write_enable2:1;
    unsigned int    size:10;
}vo_TT;

typedef struct
{
    unsigned int    reserved_0:29;
    unsigned int    hlen:1;
    unsigned int    en:1;
    unsigned int    write_data:1;
}vo_SPU;

typedef struct
{
    unsigned int    reserved_0:22;
    unsigned int    x:10;
}vo_SPIXEND;

typedef struct
{
    unsigned int    reserved_0:10;
    unsigned int    write_enable1:1;
    unsigned int    top:10;
    unsigned int    write_enable2:1;
    unsigned int    bot:10;
}vo_SPIYEND;

typedef struct
{
    unsigned int    alpha3:4;
    unsigned int    alpha2:4;
    unsigned int    alpha1:4;
    unsigned int    alpha0:4;
    unsigned int    color3:4;
    unsigned int    color2:4;
    unsigned int    color1:4;
    unsigned int    color0:4;
}vo_SPDFTMAP;

typedef struct
{
    unsigned int    reserved_0:14;
    unsigned int    bot_num:9;
    unsigned int    top_num:9;
}vo_SP_LNCTLI;

typedef struct
{
    unsigned int    reserved_0:10;
    unsigned int    write_enable1:1;
    unsigned int    end:10;
    unsigned int    write_enable2:1;
    unsigned int    st:10;
}vo_SPHLX;

typedef struct
{
    unsigned int    reserved_0:10;
    unsigned int    write_enable1:1;
    unsigned int    end:10;
    unsigned int    write_enable2:1;
    unsigned int    st:10;
}vo_SPHLY;

typedef struct
{
    unsigned int    alpha3:4;
    unsigned int    alpha2:4;
    unsigned int    alpha1:4;
    unsigned int    alpha0:4;
    unsigned int    color3:4;
    unsigned int    color2:4;
    unsigned int    color1:4;
    unsigned int    color0:4;
}vo_SPHLMAP;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    cr:8;
    unsigned int    cb:8;
    unsigned int    y:8;
}vo_SPCLUT;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    write_enable1:1;
    unsigned int    end:11;
    unsigned int    write_enable2:1;
    unsigned int    st:11;
}vo_SPX;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    write_enable1:1;
    unsigned int    end:11;
    unsigned int    write_enable2:1;
    unsigned int    st:11;
}vo_SPY;

typedef struct
{
    unsigned int    reserved_0:30;
    unsigned int    oddtype:1;
    unsigned int    write_data:1;
}vo_SPVSCCTL;

typedef struct
{
    unsigned int    reserved_0:15;
    unsigned int    dphs:17;
}vo_SPVSC;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    init_offset:10;
    unsigned int    init_phase:14;
}vo_SPVIPOS;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    c:11;
}vo_SPVSCCOEF;

typedef struct
{
    unsigned int    reserved_0:27;
    unsigned int    st_transp:1;
    unsigned int    end_transp:1;
    unsigned int    yoddtype:1;
    unsigned int    coddtype:1;
    unsigned int    write_data:1;
}vo_SPHSCCTL;

typedef struct
{
    unsigned int    reserved_0:15;
    unsigned int    ydphs:17;
}vo_SPHYSC;

typedef struct
{
    unsigned int    reserved_0:7;
    unsigned int    init_offset:11;
    unsigned int    init_phase:14;
}vo_SPHIPOS;

typedef struct
{
    unsigned int    reserved_0:20;
    unsigned int    c:12;
}vo_SPHYSCCOEF;

typedef struct
{
    unsigned int    reserved_0:20;
    unsigned int    c:12;
}vo_SPHCSCCOEF;

typedef struct
{
    unsigned int    reserved_0:5;
    unsigned int    sub:9;
    unsigned int    v2:9;
    unsigned int    v1:9;
}vo_BUFEND;

typedef struct
{
    unsigned int    reserved_0:20;
    unsigned int    write_enable1:1;
    unsigned int    interlace:1;
    unsigned int    write_enable2:1;
    unsigned int    alpha_msb:1;
    unsigned int    write_enable3:1;
    unsigned int    lpf:2;
    unsigned int    write_enable4:1;
    unsigned int    wn:2;
    unsigned int    write_enable5:1;
    unsigned int    en:1;
}vo_OSD;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    write_enable1:1;
    unsigned int    a:8;
    unsigned int    write_enable2:1;
    unsigned int    en:1;
}vo_OSDCA;

typedef struct
{
    unsigned int    reserved_0:5;
    unsigned int    write_enable1:1;
    unsigned int    k:24;
    unsigned int    write_enable2:1;
    unsigned int    en:1;
}vo_OSDKEY;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    write_enable1:1;
    unsigned int    end:11;
    unsigned int    write_enable2:1;
    unsigned int    st:11;
}vo_OSDX;

typedef struct
{
    unsigned int    reserved_0:5;
    unsigned int    write_enable1:1;
    unsigned int    format:2;
    unsigned int    write_enable2:1;
    unsigned int    end:11;
    unsigned int    write_enable3:1;
    unsigned int    st:11;
}vo_OSDY;

typedef struct
{
    unsigned int    reserved_0:22;
    unsigned int    m:10;
}vo_OSDM;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    a2:8;
    unsigned int    a1:8;
    unsigned int    a0:8;
}vo_OSDA;

typedef struct
{
    unsigned int    reserved_0:15;
    unsigned int    write_enable1:1;
    unsigned int    const_alpha:4;
    unsigned int    write_enable2:1;
    unsigned int    key:2;
    unsigned int    write_enable3:1;
    unsigned int    keyen:1;
    unsigned int    write_enable4:1;
    unsigned int    lpf:2;
    unsigned int    write_enable5:1;
    unsigned int    load:1;
    unsigned int    write_enable6:1;
    unsigned int    en:1;
}vo_CURSOR;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    write_enable1:1;
    unsigned int    yst:11;
    unsigned int    write_enable2:1;
    unsigned int    xst:11;
}vo_CURSORST;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    cr:8;
    unsigned int    cb:8;
    unsigned int    y:8;
}vo_CURCLUT;

typedef struct
{
    unsigned int    reserved_0:26;
    unsigned int    v1boren:1;
    unsigned int    v2boren:1;
    unsigned int    v1en:1;
    unsigned int    v2en:1;
    unsigned int    v2sub:1;
    unsigned int    write_data:1;
}vo_Mix;

typedef struct
{
    unsigned int    reserved_0:28;
    unsigned int    a:4;
}vo_V2ALPHA;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    write_enable1:1;
    unsigned int    yend:11;
    unsigned int    write_enable2:1;
    unsigned int    xend:11;
}vo_MixWindow;

typedef struct
{
    unsigned int    reserved_0:3;
    unsigned int    write_enable1:1;
    unsigned int    en:1;
    unsigned int    write_enable2:1;
    unsigned int    cr:8;
    unsigned int    write_enable3:1;
    unsigned int    cb:8;
    unsigned int    write_enable4:1;
    unsigned int    y:8;
}vo_MixBG;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    write_enable1:1;
    unsigned int    end:11;
    unsigned int    write_enable2:1;
    unsigned int    st:11;
}vo_MixV1X;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    write_enable1:1;
    unsigned int    end:11;
    unsigned int    write_enable2:1;
    unsigned int    st:11;
}vo_MixV1Y;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    write_enable1:1;
    unsigned int    end:11;
    unsigned int    write_enable2:1;
    unsigned int    st:11;
}vo_MixV2X;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    write_enable1:1;
    unsigned int    end:11;
    unsigned int    write_enable2:1;
    unsigned int    st:11;
}vo_MixV2Y;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    write_enable1:1;
    unsigned int    end:11;
    unsigned int    write_enable2:1;
    unsigned int    st:11;
}vo_MixV1BX;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    write_enable1:1;
    unsigned int    end:11;
    unsigned int    write_enable2:1;
    unsigned int    st:11;
}vo_MixV1BY;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    write_enable1:1;
    unsigned int    end:11;
    unsigned int    write_enable2:1;
    unsigned int    st:11;
}vo_MixV2BX;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    write_enable1:1;
    unsigned int    end:11;
    unsigned int    write_enable2:1;
    unsigned int    st:11;
}vo_MixV2BY;

typedef struct
{
    unsigned int    reserved_0:5;
    unsigned int    write_enable1:1;
    unsigned int    cr:8;
    unsigned int    write_enable2:1;
    unsigned int    cb:8;
    unsigned int    write_enable3:1;
    unsigned int    y:8;
}vo_MixV1BC;

typedef struct
{
    unsigned int    reserved_0:5;
    unsigned int    write_enable1:1;
    unsigned int    cr:8;
    unsigned int    write_enable2:1;
    unsigned int    cb:8;
    unsigned int    write_enable3:1;
    unsigned int    y:8;
}vo_MixV2BC;

typedef struct
{
    unsigned int    reserved_0:31;
    unsigned int    en:1;
}vo_PeakEn;

typedef struct
{
    unsigned int    reserved_0:3;
    unsigned int    lv:5;
    unsigned int    c2:8;
    unsigned int    c1:8;
    unsigned int    c0:8;
}vo_PeakC;

typedef struct
{
    unsigned int    reserved_0:6;
    unsigned int    write_enable1:1;
    unsigned int    m10:12;
    unsigned int    write_enable2:1;
    unsigned int    m00:12;
}vo_ContrastM0;

typedef struct
{
    unsigned int    reserved_0:6;
    unsigned int    write_enable1:1;
    unsigned int    m01:12;
    unsigned int    write_enable2:1;
    unsigned int    m20:12;
}vo_ContrastM1;

typedef struct
{
    unsigned int    reserved_0:6;
    unsigned int    write_enable1:1;
    unsigned int    m21:12;
    unsigned int    write_enable2:1;
    unsigned int    m11:12;
}vo_ContrastM2;

typedef struct
{
    unsigned int    reserved_0:6;
    unsigned int    write_enable1:1;
    unsigned int    m12:12;
    unsigned int    write_enable2:1;
    unsigned int    m02:12;
}vo_ContrastM3;

typedef struct
{
    unsigned int    reserved_0:20;
    unsigned int    m22:12;
}vo_ContrastM4;

typedef struct
{
    unsigned int    reserved_0:2;
    unsigned int    write_enable1:1;
    unsigned int    a2:9;
    unsigned int    write_enable2:1;
    unsigned int    a1:9;
    unsigned int    write_enable3:1;
    unsigned int    a0:9;
}vo_ContrastA;

typedef struct
{
    unsigned int    cmax:8;
    unsigned int    cmin:8;
    unsigned int    ymax:8;
    unsigned int    ymin:8;
}vo_ContrastLimit;

typedef struct
{
    unsigned int    reserved_0:28;
    unsigned int    topfld:1;
    unsigned int    pen:1;
    unsigned int    ien:1;
    unsigned int    write_data:1;
}vo_REINTERLACE;

typedef struct
{
    unsigned int    reserved_0:20;
    unsigned int    end:12;
}vo_REINT_DISPBUF;

typedef struct
{
    unsigned int    reserved_0:29;
    unsigned int    l:3;
}vo_BSTLEN;

typedef struct
{
    unsigned int    reserved_0:29;
    unsigned int    video2:1;
    unsigned int    video1:1;
    unsigned int    write_data:1;
}vo_VIDEOST;

typedef struct
{
    unsigned int    reserved_0:4;
    unsigned int    write_enable1:1;
    unsigned int    wr:6;
    unsigned int    write_enable2:1;
    unsigned int    cur:6;
    unsigned int    write_enable3:1;
    unsigned int    pre:6;
    unsigned int    write_enable4:1;
    unsigned int    nxt:6;
}vo_Y1PICSET;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    y1rsadr:24;
}vo_Y1RSADR;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    y1wsadr:24;
}vo_Y1WSADR;

typedef struct
{
    unsigned int    reserved_0:4;
    unsigned int    write_enable1:1;
    unsigned int    wr:6;
    unsigned int    write_enable2:1;
    unsigned int    cur:6;
    unsigned int    write_enable3:1;
    unsigned int    pre:6;
    unsigned int    write_enable4:1;
    unsigned int    nxt:6;
}vo_C1PICSET;

typedef struct
{
    unsigned int    reserved_0:4;
    unsigned int    write_enable1:1;
    unsigned int    y2cur:6;
    unsigned int    write_enable2:1;
    unsigned int    y2alt:6;
    unsigned int    write_enable3:1;
    unsigned int    c2cur:6;
    unsigned int    write_enable4:1;
    unsigned int    c2alt:6;
}vo_V2PICSET;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    a:24;
}vo_VBIADR;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    a:24;
}vo_TTADR;

typedef struct
{
    unsigned int    reserved_0:5;
    unsigned int    a:27;
}vo_TPXDADR;

typedef struct
{
    unsigned int    reserved_0:5;
    unsigned int    a:27;
}vo_BPXDADR;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    a:24;
}vo_TCMDADR;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    a:24;
}vo_BCMDADR;

typedef struct
{
    unsigned int    reserved_0:13;
    unsigned int    write_enable1:1;
    unsigned int    pic_set:6;
    unsigned int    write_enable2:1;
    unsigned int    yst:11;
}vo_OSDDMA0;

typedef struct
{
    unsigned int    reserved_0:10;
    unsigned int    write_enable2:1;
    unsigned int    length:10;
    unsigned int    write_enable3:1;
    unsigned int    xst:10;
}vo_OSDDMA1;

typedef struct
{
    unsigned int    reserved_0:8;
    unsigned int    a:24;
}vo_CURSORADR;

typedef struct
{
    unsigned int    reserved_0:28;
    unsigned int    channel:4;
}vo_PRIORITY;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    b:11;
}vo_Y1C2_BASE;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    b:11;
}vo_Y1P_BASE;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    b:11;
}vo_Y1N_BASE;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    b:11;
}vo_C1C1_BASE;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    b:11;
}vo_C1C2_BASE;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    b:11;
}vo_C1P_BASE;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    b:11;
}vo_C1N_BASE;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    b:11;
}vo_Y2C1_BASE;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    b:11;
}vo_Y2C2_BASE;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    b:11;
}vo_C2C1_BASE;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    b:11;
}vo_C2C2_BASE;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    b:11;
}vo_TCMD_BASE;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    b:11;
}vo_TPXD_BASE;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    b:11;
}vo_BCMD_BASE;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    b:11;
}vo_BPXD_BASE;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    b:11;
}vo_OSD_BASE;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    b:11;
}vo_CUR_BASE;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    b:11;
}vo_SP1_BASE;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    b:11;
}vo_SP2_BASE;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    b:11;
}vo_SP3_BASE;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    b:8;
}vo_C1O_BASE;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    b:8;
}vo_SC_BASE;

typedef struct
{
    unsigned int    reserved_0:23;
    unsigned int    rld_dmy_err:1;
    unsigned int    rld_ln_err:1;
    unsigned int    rld_s4_err:1;
    unsigned int    pudflw:1;
    unsigned int    iudflw:1;
    unsigned int    finish:1;
    unsigned int    ysdscfi:1;
    unsigned int    csdscfi:1;
    unsigned int    write_data:1;
}vo_VINTEN;

typedef struct
{
    unsigned int    reserved_0:23;
    unsigned int    rld_dmy_err:1;
    unsigned int    rld_ln_err:1;
    unsigned int    rld_s4_err:1;
    unsigned int    pudflw:1;
    unsigned int    iudflw:1;
    unsigned int    finish:1;
    unsigned int    ysdscfi:1;
    unsigned int    csdscfi:1;
    unsigned int    write_data:1;
}vo_VINTST;

typedef struct
{
    unsigned int    reserved_0:5;
    unsigned int    spbuf:9;
    unsigned int    v2buf:9;
    unsigned int    v1buf:9;
}vo_UDFLCNT;

typedef struct
{
    unsigned int    reserved_0:21;
    unsigned int    osdbuf:11;
}vo_UDFLECNT;

typedef struct
{
    unsigned int    reserved_0:28;
    unsigned int    go:1;
    unsigned int    ysdscgo:1;
    unsigned int    csdscgo:1;
    unsigned int    write_data:1;
}vo_GCTL;
#endif

#define VO_V1MODE                                                     0x18005000
#define VO_V1MODE_reg_addr                                            "0xB8005000"
#define VO_V1MODE_reg                                                 0xB8005000
#define VO_V1MODE_inst_addr                                           "0x0000"
#define VO_V1MODE_inst                                                0x0000
#define VO_V1MODE_mode_shift                                          (0)
#define VO_V1MODE_mode_mask                                           (0x00000003)
#define VO_V1MODE_mode(data)                                          (0x00000003&(data))
#define VO_V1MODE_get_mode(data)                                      (0x00000003&(data))

#define VO_V1SCO                                                      0x18005004
#define VO_V1SCO_reg_addr                                             "0xB8005004"
#define VO_V1SCO_reg                                                  0xB8005004
#define VO_V1SCO_inst_addr                                            "0x0001"
#define VO_V1SCO_inst                                                 0x0001
#define VO_V1SCO_write_enable1_shift                                  (10)
#define VO_V1SCO_scoe_shift                                           (9)
#define VO_V1SCO_write_enable2_shift                                  (8)
#define VO_V1SCO_reintle_shift                                        (7)
#define VO_V1SCO_write_enable3_shift                                  (6)
#define VO_V1SCO_reintlt_shift                                        (5)
#define VO_V1SCO_write_enable4_shift                                  (4)
#define VO_V1SCO_cvde_shift                                           (3)
#define VO_V1SCO_write_enable5_shift                                  (2)
#define VO_V1SCO_cvdtp_shift                                          (0)
#define VO_V1SCO_write_enable1_mask                                   (0x00000400)
#define VO_V1SCO_scoe_mask                                            (0x00000200)
#define VO_V1SCO_write_enable2_mask                                   (0x00000100)
#define VO_V1SCO_reintle_mask                                         (0x00000080)
#define VO_V1SCO_write_enable3_mask                                   (0x00000040)
#define VO_V1SCO_reintlt_mask                                         (0x00000020)
#define VO_V1SCO_write_enable4_mask                                   (0x00000010)
#define VO_V1SCO_cvde_mask                                            (0x00000008)
#define VO_V1SCO_write_enable5_mask                                   (0x00000004)
#define VO_V1SCO_cvdtp_mask                                           (0x00000003)
#define VO_V1SCO_write_enable1(data)                                  (0x00000400&((data)<<10))
#define VO_V1SCO_scoe(data)                                           (0x00000200&((data)<<9))
#define VO_V1SCO_write_enable2(data)                                  (0x00000100&((data)<<8))
#define VO_V1SCO_reintle(data)                                        (0x00000080&((data)<<7))
#define VO_V1SCO_write_enable3(data)                                  (0x00000040&((data)<<6))
#define VO_V1SCO_reintlt(data)                                        (0x00000020&((data)<<5))
#define VO_V1SCO_write_enable4(data)                                  (0x00000010&((data)<<4))
#define VO_V1SCO_cvde(data)                                           (0x00000008&((data)<<3))
#define VO_V1SCO_write_enable5(data)                                  (0x00000004&((data)<<2))
#define VO_V1SCO_cvdtp(data)                                          (0x00000003&(data))
#define VO_V1SCO_get_write_enable1(data)                              ((0x00000400&(data))>>10)
#define VO_V1SCO_get_scoe(data)                                       ((0x00000200&(data))>>9)
#define VO_V1SCO_get_write_enable2(data)                              ((0x00000100&(data))>>8)
#define VO_V1SCO_get_reintle(data)                                    ((0x00000080&(data))>>7)
#define VO_V1SCO_get_write_enable3(data)                              ((0x00000040&(data))>>6)
#define VO_V1SCO_get_reintlt(data)                                    ((0x00000020&(data))>>5)
#define VO_V1SCO_get_write_enable4(data)                              ((0x00000010&(data))>>4)
#define VO_V1SCO_get_cvde(data)                                       ((0x00000008&(data))>>3)
#define VO_V1SCO_get_write_enable5(data)                              ((0x00000004&(data))>>2)
#define VO_V1SCO_get_cvdtp(data)                                      (0x00000003&(data))

#define VO_V1DIMD                                                     0x18005008
#define VO_V1DIMD_reg_addr                                            "0xB8005008"
#define VO_V1DIMD_reg                                                 0xB8005008
#define VO_V1DIMD_inst_addr                                           "0x0002"
#define VO_V1DIMD_inst                                                0x0002
#define VO_V1DIMD_write_enable1_shift                                 (5)
#define VO_V1DIMD_vdimd_shift                                         (2)
#define VO_V1DIMD_write_enable2_shift                                 (1)
#define VO_V1DIMD_topfield_shift                                      (0)
#define VO_V1DIMD_write_enable1_mask                                  (0x00000020)
#define VO_V1DIMD_vdimd_mask                                          (0x0000001C)
#define VO_V1DIMD_write_enable2_mask                                  (0x00000002)
#define VO_V1DIMD_topfield_mask                                       (0x00000001)
#define VO_V1DIMD_write_enable1(data)                                 (0x00000020&((data)<<5))
#define VO_V1DIMD_vdimd(data)                                         (0x0000001C&((data)<<2))
#define VO_V1DIMD_write_enable2(data)                                 (0x00000002&((data)<<1))
#define VO_V1DIMD_topfield(data)                                      (0x00000001&(data))
#define VO_V1DIMD_get_write_enable1(data)                             ((0x00000020&(data))>>5)
#define VO_V1DIMD_get_vdimd(data)                                     ((0x0000001C&(data))>>2)
#define VO_V1DIMD_get_write_enable2(data)                             ((0x00000002&(data))>>1)
#define VO_V1DIMD_get_topfield(data)                                  (0x00000001&(data))

#define VO_TELECINE                                                   0x1800500C
#define VO_TELECINE_reg_addr                                          "0xB800500C"
#define VO_TELECINE_reg                                               0xB800500C
#define VO_TELECINE_inst_addr                                         "0x0003"
#define VO_TELECINE_inst                                              0x0003
#define VO_TELECINE_mode_shift                                        (0)
#define VO_TELECINE_mode_mask                                         (0x00000003)
#define VO_TELECINE_mode(data)                                        (0x00000003&(data))
#define VO_TELECINE_get_mode(data)                                    (0x00000003&(data))

#define VO_WADTB_0                                                    0x18005010
#define VO_WADTB_1                                                    0x18005014
#define VO_WADTB_2                                                    0x18005018
#define VO_WADTB_3                                                    0x1800501C
#define VO_WADTB_4                                                    0x18005020
#define VO_WADTB_5                                                    0x18005024
#define VO_WADTB_6                                                    0x18005028
#define VO_WADTB_7                                                    0x1800502C
#define VO_WADTB_8                                                    0x18005030
#define VO_WADTB_0_reg_addr                                           "0xB8005010"
#define VO_WADTB_1_reg_addr                                           "0xB8005014"
#define VO_WADTB_2_reg_addr                                           "0xB8005018"
#define VO_WADTB_3_reg_addr                                           "0xB800501C"
#define VO_WADTB_4_reg_addr                                           "0xB8005020"
#define VO_WADTB_5_reg_addr                                           "0xB8005024"
#define VO_WADTB_6_reg_addr                                           "0xB8005028"
#define VO_WADTB_7_reg_addr                                           "0xB800502C"
#define VO_WADTB_8_reg_addr                                           "0xB8005030"
#define VO_WADTB_0_reg                                                0xB8005010
#define VO_WADTB_1_reg                                                0xB8005014
#define VO_WADTB_2_reg                                                0xB8005018
#define VO_WADTB_3_reg                                                0xB800501C
#define VO_WADTB_4_reg                                                0xB8005020
#define VO_WADTB_5_reg                                                0xB8005024
#define VO_WADTB_6_reg                                                0xB8005028
#define VO_WADTB_7_reg                                                0xB800502C
#define VO_WADTB_8_reg                                                0xB8005030
#define VO_WADTB_0_inst_addr                                          "0x0004"
#define VO_WADTB_0_inst                                               0x0004
#define VO_WADTB_1_inst_addr                                          "0x0005"
#define VO_WADTB_1_inst                                               0x0005
#define VO_WADTB_2_inst_addr                                          "0x0006"
#define VO_WADTB_2_inst                                               0x0006
#define VO_WADTB_3_inst_addr                                          "0x0007"
#define VO_WADTB_3_inst                                               0x0007
#define VO_WADTB_4_inst_addr                                          "0x0008"
#define VO_WADTB_4_inst                                               0x0008
#define VO_WADTB_5_inst_addr                                          "0x0009"
#define VO_WADTB_5_inst                                               0x0009
#define VO_WADTB_6_inst_addr                                          "0x000A"
#define VO_WADTB_6_inst                                               0x000A
#define VO_WADTB_7_inst_addr                                          "0x000B"
#define VO_WADTB_7_inst                                               0x000B
#define VO_WADTB_8_inst_addr                                          "0x000C"
#define VO_WADTB_8_inst                                               0x000C
#define VO_WADTB_write_enable1_shift                                  (22)
#define VO_WADTB_th_shift                                             (13)
#define VO_WADTB_write_enable2_shift                                  (12)
#define VO_WADTB_wad_shift                                            (0)
#define VO_WADTB_write_enable1_mask                                   (0x00400000)
#define VO_WADTB_th_mask                                              (0x003FE000)
#define VO_WADTB_write_enable2_mask                                   (0x00001000)
#define VO_WADTB_wad_mask                                             (0x00000FFF)
#define VO_WADTB_write_enable1(data)                                  (0x00400000&((data)<<22))
#define VO_WADTB_th(data)                                             (0x003FE000&((data)<<13))
#define VO_WADTB_write_enable2(data)                                  (0x00001000&((data)<<12))
#define VO_WADTB_wad(data)                                            (0x00000FFF&(data))
#define VO_WADTB_get_write_enable1(data)                              ((0x00400000&(data))>>22)
#define VO_WADTB_get_th(data)                                         ((0x003FE000&(data))>>13)
#define VO_WADTB_get_write_enable2(data)                              ((0x00001000&(data))>>12)
#define VO_WADTB_get_wad(data)                                        (0x00000FFF&(data))

#define VO_TWV1                                                       0x18005034
#define VO_TWV1_reg_addr                                              "0xB8005034"
#define VO_TWV1_reg                                                   0xB8005034
#define VO_TWV1_inst_addr                                             "0x000D"
#define VO_TWV1_inst                                                  0x000D
#define VO_TWV1_write_enable1_shift                                   (19)
#define VO_TWV1_vstart_shift                                          (10)
#define VO_TWV1_write_enable2_shift                                   (9)
#define VO_TWV1_vend_shift                                            (0)
#define VO_TWV1_write_enable1_mask                                    (0x00080000)
#define VO_TWV1_vstart_mask                                           (0x0007FC00)
#define VO_TWV1_write_enable2_mask                                    (0x00000200)
#define VO_TWV1_vend_mask                                             (0x000001FF)
#define VO_TWV1_write_enable1(data)                                   (0x00080000&((data)<<19))
#define VO_TWV1_vstart(data)                                          (0x0007FC00&((data)<<10))
#define VO_TWV1_write_enable2(data)                                   (0x00000200&((data)<<9))
#define VO_TWV1_vend(data)                                            (0x000001FF&(data))
#define VO_TWV1_get_write_enable1(data)                               ((0x00080000&(data))>>19)
#define VO_TWV1_get_vstart(data)                                      ((0x0007FC00&(data))>>10)
#define VO_TWV1_get_write_enable2(data)                               ((0x00000200&(data))>>9)
#define VO_TWV1_get_vend(data)                                        (0x000001FF&(data))

#define VO_CTWV1                                                      0x18005038
#define VO_CTWV1_reg_addr                                             "0xB8005038"
#define VO_CTWV1_reg                                                  0xB8005038
#define VO_CTWV1_inst_addr                                            "0x000E"
#define VO_CTWV1_inst                                                 0x000E
#define VO_CTWV1_write_enable1_shift                                  (19)
#define VO_CTWV1_vstart_shift                                         (10)
#define VO_CTWV1_write_enable2_shift                                  (9)
#define VO_CTWV1_vend_shift                                           (0)
#define VO_CTWV1_write_enable1_mask                                   (0x00080000)
#define VO_CTWV1_vstart_mask                                          (0x0007FC00)
#define VO_CTWV1_write_enable2_mask                                   (0x00000200)
#define VO_CTWV1_vend_mask                                            (0x000001FF)
#define VO_CTWV1_write_enable1(data)                                  (0x00080000&((data)<<19))
#define VO_CTWV1_vstart(data)                                         (0x0007FC00&((data)<<10))
#define VO_CTWV1_write_enable2(data)                                  (0x00000200&((data)<<9))
#define VO_CTWV1_vend(data)                                           (0x000001FF&(data))
#define VO_CTWV1_get_write_enable1(data)                              ((0x00080000&(data))>>19)
#define VO_CTWV1_get_vstart(data)                                     ((0x0007FC00&(data))>>10)
#define VO_CTWV1_get_write_enable2(data)                              ((0x00000200&(data))>>9)
#define VO_CTWV1_get_vend(data)                                       (0x000001FF&(data))

#define VO_TWH1                                                       0x1800503C
#define VO_TWH1_reg_addr                                              "0xB800503C"
#define VO_TWH1_reg                                                   0xB800503C
#define VO_TWH1_inst_addr                                             "0x000F"
#define VO_TWH1_inst                                                  0x000F
#define VO_TWH1_write_enable1_shift                                   (21)
#define VO_TWH1_hstart_shift                                          (11)
#define VO_TWH1_write_enable2_shift                                   (10)
#define VO_TWH1_hsize_shift                                           (0)
#define VO_TWH1_write_enable1_mask                                    (0x00200000)
#define VO_TWH1_hstart_mask                                           (0x001FF800)
#define VO_TWH1_write_enable2_mask                                    (0x00000400)
#define VO_TWH1_hsize_mask                                            (0x000003FF)
#define VO_TWH1_write_enable1(data)                                   (0x00200000&((data)<<21))
#define VO_TWH1_hstart(data)                                          (0x001FF800&((data)<<11))
#define VO_TWH1_write_enable2(data)                                   (0x00000400&((data)<<10))
#define VO_TWH1_hsize(data)                                           (0x000003FF&(data))
#define VO_TWH1_get_write_enable1(data)                               ((0x00200000&(data))>>21)
#define VO_TWH1_get_hstart(data)                                      ((0x001FF800&(data))>>11)
#define VO_TWH1_get_write_enable2(data)                               ((0x00000400&(data))>>10)
#define VO_TWH1_get_hsize(data)                                       (0x000003FF&(data))

#define VO_YPNSWAD1                                                   0x18005040
#define VO_YPNSWAD1_reg_addr                                          "0xB8005040"
#define VO_YPNSWAD1_reg                                               0xB8005040
#define VO_YPNSWAD1_inst_addr                                         "0x0010"
#define VO_YPNSWAD1_inst                                              0x0010
#define VO_YPNSWAD1_pnswad_shift                                      (0)
#define VO_YPNSWAD1_pnswad_mask                                       (0x01FFFFFF)
#define VO_YPNSWAD1_pnswad(data)                                      (0x01FFFFFF&(data))
#define VO_YPNSWAD1_get_pnswad(data)                                  (0x01FFFFFF&(data))

#define VO_YPCSWAD1                                                   0x18005044
#define VO_YPCSWAD1_reg_addr                                          "0xB8005044"
#define VO_YPCSWAD1_reg                                               0xB8005044
#define VO_YPCSWAD1_inst_addr                                         "0x0011"
#define VO_YPCSWAD1_inst                                              0x0011
#define VO_YPCSWAD1_pcswad_shift                                      (0)
#define VO_YPCSWAD1_pcswad_mask                                       (0x01FFFFFF)
#define VO_YPCSWAD1_pcswad(data)                                      (0x01FFFFFF&(data))
#define VO_YPCSWAD1_get_pcswad(data)                                  (0x01FFFFFF&(data))

#define VO_YNCSWAD1                                                   0x18005048
#define VO_YNCSWAD1_reg_addr                                          "0xB8005048"
#define VO_YNCSWAD1_reg                                               0xB8005048
#define VO_YNCSWAD1_inst_addr                                         "0x0012"
#define VO_YNCSWAD1_inst                                              0x0012
#define VO_YNCSWAD1_ncswad_shift                                      (0)
#define VO_YNCSWAD1_ncswad_mask                                       (0x01FFFFFF)
#define VO_YNCSWAD1_ncswad(data)                                      (0x01FFFFFF&(data))
#define VO_YNCSWAD1_get_ncswad(data)                                  (0x01FFFFFF&(data))

#define VO_YPNTHRELD1                                                 0x1800504C
#define VO_YPNTHRELD1_reg_addr                                        "0xB800504C"
#define VO_YPNTHRELD1_reg                                             0xB800504C
#define VO_YPNTHRELD1_inst_addr                                       "0x0013"
#define VO_YPNTHRELD1_inst                                            0x0013
#define VO_YPNTHRELD1_pnthreld_shift                                  (0)
#define VO_YPNTHRELD1_pnthreld_mask                                   (0x01FFFFFF)
#define VO_YPNTHRELD1_pnthreld(data)                                  (0x01FFFFFF&(data))
#define VO_YPNTHRELD1_get_pnthreld(data)                              (0x01FFFFFF&(data))

#define VO_YPCTHRELD1                                                 0x18005050
#define VO_YPCTHRELD1_reg_addr                                        "0xB8005050"
#define VO_YPCTHRELD1_reg                                             0xB8005050
#define VO_YPCTHRELD1_inst_addr                                       "0x0014"
#define VO_YPCTHRELD1_inst                                            0x0014
#define VO_YPCTHRELD1_pcthreld_shift                                  (0)
#define VO_YPCTHRELD1_pcthreld_mask                                   (0x01FFFFFF)
#define VO_YPCTHRELD1_pcthreld(data)                                  (0x01FFFFFF&(data))
#define VO_YPCTHRELD1_get_pcthreld(data)                              (0x01FFFFFF&(data))

#define VO_YNCTHRELD1                                                 0x18005054
#define VO_YNCTHRELD1_reg_addr                                        "0xB8005054"
#define VO_YNCTHRELD1_reg                                             0xB8005054
#define VO_YNCTHRELD1_inst_addr                                       "0x0015"
#define VO_YNCTHRELD1_inst                                            0x0015
#define VO_YNCTHRELD1_ncthreld_shift                                  (0)
#define VO_YNCTHRELD1_ncthreld_mask                                   (0x01FFFFFF)
#define VO_YNCTHRELD1_ncthreld(data)                                  (0x01FFFFFF&(data))
#define VO_YNCTHRELD1_get_ncthreld(data)                              (0x01FFFFFF&(data))

#define VO_CPNSWAD1                                                   0x18005058
#define VO_CPNSWAD1_reg_addr                                          "0xB8005058"
#define VO_CPNSWAD1_reg                                               0xB8005058
#define VO_CPNSWAD1_inst_addr                                         "0x0016"
#define VO_CPNSWAD1_inst                                              0x0016
#define VO_CPNSWAD1_pnswad_shift                                      (0)
#define VO_CPNSWAD1_pnswad_mask                                       (0x01FFFFFF)
#define VO_CPNSWAD1_pnswad(data)                                      (0x01FFFFFF&(data))
#define VO_CPNSWAD1_get_pnswad(data)                                  (0x01FFFFFF&(data))

#define VO_CPCSWAD1                                                   0x1800505C
#define VO_CPCSWAD1_reg_addr                                          "0xB800505C"
#define VO_CPCSWAD1_reg                                               0xB800505C
#define VO_CPCSWAD1_inst_addr                                         "0x0017"
#define VO_CPCSWAD1_inst                                              0x0017
#define VO_CPCSWAD1_pcswad_shift                                      (0)
#define VO_CPCSWAD1_pcswad_mask                                       (0x01FFFFFF)
#define VO_CPCSWAD1_pcswad(data)                                      (0x01FFFFFF&(data))
#define VO_CPCSWAD1_get_pcswad(data)                                  (0x01FFFFFF&(data))

#define VO_CNCSWAD1                                                   0x18005060
#define VO_CNCSWAD1_reg_addr                                          "0xB8005060"
#define VO_CNCSWAD1_reg                                               0xB8005060
#define VO_CNCSWAD1_inst_addr                                         "0x0018"
#define VO_CNCSWAD1_inst                                              0x0018
#define VO_CNCSWAD1_ncswad_shift                                      (0)
#define VO_CNCSWAD1_ncswad_mask                                       (0x01FFFFFF)
#define VO_CNCSWAD1_ncswad(data)                                      (0x01FFFFFF&(data))
#define VO_CNCSWAD1_get_ncswad(data)                                  (0x01FFFFFF&(data))

#define VO_CPNTHRELD1                                                 0x18005064
#define VO_CPNTHRELD1_reg_addr                                        "0xB8005064"
#define VO_CPNTHRELD1_reg                                             0xB8005064
#define VO_CPNTHRELD1_inst_addr                                       "0x0019"
#define VO_CPNTHRELD1_inst                                            0x0019
#define VO_CPNTHRELD1_pnthreld_shift                                  (0)
#define VO_CPNTHRELD1_pnthreld_mask                                   (0x01FFFFFF)
#define VO_CPNTHRELD1_pnthreld(data)                                  (0x01FFFFFF&(data))
#define VO_CPNTHRELD1_get_pnthreld(data)                              (0x01FFFFFF&(data))

#define VO_CPCTHRELD1                                                 0x18005068
#define VO_CPCTHRELD1_reg_addr                                        "0xB8005068"
#define VO_CPCTHRELD1_reg                                             0xB8005068
#define VO_CPCTHRELD1_inst_addr                                       "0x001A"
#define VO_CPCTHRELD1_inst                                            0x001A
#define VO_CPCTHRELD1_pcthreld_shift                                  (0)
#define VO_CPCTHRELD1_pcthreld_mask                                   (0x01FFFFFF)
#define VO_CPCTHRELD1_pcthreld(data)                                  (0x01FFFFFF&(data))
#define VO_CPCTHRELD1_get_pcthreld(data)                              (0x01FFFFFF&(data))

#define VO_CNCTHRELD1                                                 0x1800506C
#define VO_CNCTHRELD1_reg_addr                                        "0xB800506C"
#define VO_CNCTHRELD1_reg                                             0xB800506C
#define VO_CNCTHRELD1_inst_addr                                       "0x001B"
#define VO_CNCTHRELD1_inst                                            0x001B
#define VO_CNCTHRELD1_ncthreld_shift                                  (0)
#define VO_CNCTHRELD1_ncthreld_mask                                   (0x01FFFFFF)
#define VO_CNCTHRELD1_ncthreld(data)                                  (0x01FFFFFF&(data))
#define VO_CNCTHRELD1_get_ncthreld(data)                              (0x01FFFFFF&(data))

#define VO_YBOB                                                       0x18005070
#define VO_YBOB_reg_addr                                              "0xB8005070"
#define VO_YBOB_reg                                                   0xB8005070
#define VO_YBOB_inst_addr                                             "0x001C"
#define VO_YBOB_inst                                                  0x001C
#define VO_YBOB_write_enable1_shift                                   (30)
#define VO_YBOB_candinum_shift                                        (28)
#define VO_YBOB_write_enable2_shift                                   (27)
#define VO_YBOB_thpositive_shift                                      (22)
#define VO_YBOB_write_enable3_shift                                   (21)
#define VO_YBOB_thnegative_shift                                      (15)
#define VO_YBOB_write_enable4_shift                                   (14)
#define VO_YBOB_thcompdecision_shift                                  (7)
#define VO_YBOB_write_enable5_shift                                   (6)
#define VO_YBOB_thcompreverse_shift                                   (0)
#define VO_YBOB_write_enable1_mask                                    (0x40000000)
#define VO_YBOB_candinum_mask                                         (0x30000000)
#define VO_YBOB_write_enable2_mask                                    (0x08000000)
#define VO_YBOB_thpositive_mask                                       (0x07C00000)
#define VO_YBOB_write_enable3_mask                                    (0x00200000)
#define VO_YBOB_thnegative_mask                                       (0x001F8000)
#define VO_YBOB_write_enable4_mask                                    (0x00004000)
#define VO_YBOB_thcompdecision_mask                                   (0x00003F80)
#define VO_YBOB_write_enable5_mask                                    (0x00000040)
#define VO_YBOB_thcompreverse_mask                                    (0x0000003F)
#define VO_YBOB_write_enable1(data)                                   (0x40000000&((data)<<30))
#define VO_YBOB_candinum(data)                                        (0x30000000&((data)<<28))
#define VO_YBOB_write_enable2(data)                                   (0x08000000&((data)<<27))
#define VO_YBOB_thpositive(data)                                      (0x07C00000&((data)<<22))
#define VO_YBOB_write_enable3(data)                                   (0x00200000&((data)<<21))
#define VO_YBOB_thnegative(data)                                      (0x001F8000&((data)<<15))
#define VO_YBOB_write_enable4(data)                                   (0x00004000&((data)<<14))
#define VO_YBOB_thcompdecision(data)                                  (0x00003F80&((data)<<7))
#define VO_YBOB_write_enable5(data)                                   (0x00000040&((data)<<6))
#define VO_YBOB_thcompreverse(data)                                   (0x0000003F&(data))
#define VO_YBOB_get_write_enable1(data)                               ((0x40000000&(data))>>30)
#define VO_YBOB_get_candinum(data)                                    ((0x30000000&(data))>>28)
#define VO_YBOB_get_write_enable2(data)                               ((0x08000000&(data))>>27)
#define VO_YBOB_get_thpositive(data)                                  ((0x07C00000&(data))>>22)
#define VO_YBOB_get_write_enable3(data)                               ((0x00200000&(data))>>21)
#define VO_YBOB_get_thnegative(data)                                  ((0x001F8000&(data))>>15)
#define VO_YBOB_get_write_enable4(data)                               ((0x00004000&(data))>>14)
#define VO_YBOB_get_thcompdecision(data)                              ((0x00003F80&(data))>>7)
#define VO_YBOB_get_write_enable5(data)                               ((0x00000040&(data))>>6)
#define VO_YBOB_get_thcompreverse(data)                               (0x0000003F&(data))

#define VO_NOISETH                                                    0x18005074
#define VO_NOISETH_reg_addr                                           "0xB8005074"
#define VO_NOISETH_reg                                                0xB8005074
#define VO_NOISETH_inst_addr                                          "0x001D"
#define VO_NOISETH_inst                                               0x001D
#define VO_NOISETH_write_enable1_shift                                (21)
#define VO_NOISETH_weavemode_shift                                    (20)
#define VO_NOISETH_write_enable2_shift                                (19)
#define VO_NOISETH_thrnoisesp_shift                                   (14)
#define VO_NOISETH_write_enable3_shift                                (13)
#define VO_NOISETH_thrstilly_shift                                    (7)
#define VO_NOISETH_write_enable4_shift                                (6)
#define VO_NOISETH_thrstillc_shift                                    (0)
#define VO_NOISETH_write_enable1_mask                                 (0x00200000)
#define VO_NOISETH_weavemode_mask                                     (0x00100000)
#define VO_NOISETH_write_enable2_mask                                 (0x00080000)
#define VO_NOISETH_thrnoisesp_mask                                    (0x0007C000)
#define VO_NOISETH_write_enable3_mask                                 (0x00002000)
#define VO_NOISETH_thrstilly_mask                                     (0x00001F80)
#define VO_NOISETH_write_enable4_mask                                 (0x00000040)
#define VO_NOISETH_thrstillc_mask                                     (0x0000003F)
#define VO_NOISETH_write_enable1(data)                                (0x00200000&((data)<<21))
#define VO_NOISETH_weavemode(data)                                    (0x00100000&((data)<<20))
#define VO_NOISETH_write_enable2(data)                                (0x00080000&((data)<<19))
#define VO_NOISETH_thrnoisesp(data)                                   (0x0007C000&((data)<<14))
#define VO_NOISETH_write_enable3(data)                                (0x00002000&((data)<<13))
#define VO_NOISETH_thrstilly(data)                                    (0x00001F80&((data)<<7))
#define VO_NOISETH_write_enable4(data)                                (0x00000040&((data)<<6))
#define VO_NOISETH_thrstillc(data)                                    (0x0000003F&(data))
#define VO_NOISETH_get_write_enable1(data)                            ((0x00200000&(data))>>21)
#define VO_NOISETH_get_weavemode(data)                                ((0x00100000&(data))>>20)
#define VO_NOISETH_get_write_enable2(data)                            ((0x00080000&(data))>>19)
#define VO_NOISETH_get_thrnoisesp(data)                               ((0x0007C000&(data))>>14)
#define VO_NOISETH_get_write_enable3(data)                            ((0x00002000&(data))>>13)
#define VO_NOISETH_get_thrstilly(data)                                ((0x00001F80&(data))>>7)
#define VO_NOISETH_get_write_enable4(data)                            ((0x00000040&(data))>>6)
#define VO_NOISETH_get_thrstillc(data)                                (0x0000003F&(data))

#define VO_STILL                                                      0x18005078
#define VO_STILL_reg_addr                                             "0xB8005078"
#define VO_STILL_reg                                                  0xB8005078
#define VO_STILL_inst_addr                                            "0x001E"
#define VO_STILL_inst                                                 0x001E
#define VO_STILL_lastline_shift                                       (0)
#define VO_STILL_lastline_mask                                        (0x000007FF)
#define VO_STILL_lastline(data)                                       (0x000007FF&(data))
#define VO_STILL_get_lastline(data)                                   (0x000007FF&(data))

#define VO_YBLEND                                                     0x1800507C
#define VO_YBLEND_reg_addr                                            "0xB800507C"
#define VO_YBLEND_reg                                                 0xB800507C
#define VO_YBLEND_inst_addr                                           "0x001F"
#define VO_YBLEND_inst                                                0x001F
#define VO_YBLEND_write_enable1_shift                                 (12)
#define VO_YBLEND_thrblndlow_shift                                    (4)
#define VO_YBLEND_write_enable2_shift                                 (3)
#define VO_YBLEND_thrblnddiff2_shift                                  (0)
#define VO_YBLEND_write_enable1_mask                                  (0x00001000)
#define VO_YBLEND_thrblndlow_mask                                     (0x00000FF0)
#define VO_YBLEND_write_enable2_mask                                  (0x00000008)
#define VO_YBLEND_thrblnddiff2_mask                                   (0x00000007)
#define VO_YBLEND_write_enable1(data)                                 (0x00001000&((data)<<12))
#define VO_YBLEND_thrblndlow(data)                                    (0x00000FF0&((data)<<4))
#define VO_YBLEND_write_enable2(data)                                 (0x00000008&((data)<<3))
#define VO_YBLEND_thrblnddiff2(data)                                  (0x00000007&(data))
#define VO_YBLEND_get_write_enable1(data)                             ((0x00001000&(data))>>12)
#define VO_YBLEND_get_thrblndlow(data)                                ((0x00000FF0&(data))>>4)
#define VO_YBLEND_get_write_enable2(data)                             ((0x00000008&(data))>>3)
#define VO_YBLEND_get_thrblnddiff2(data)                              (0x00000007&(data))

#define VO_CBLEND                                                     0x18005080
#define VO_CBLEND_reg_addr                                            "0xB8005080"
#define VO_CBLEND_reg                                                 0xB8005080
#define VO_CBLEND_inst_addr                                           "0x0020"
#define VO_CBLEND_inst                                                0x0020
#define VO_CBLEND_write_enable1_shift                                 (12)
#define VO_CBLEND_thrblndlow_shift                                    (4)
#define VO_CBLEND_write_enable2_shift                                 (3)
#define VO_CBLEND_thrblnddiff2_shift                                  (0)
#define VO_CBLEND_write_enable1_mask                                  (0x00001000)
#define VO_CBLEND_thrblndlow_mask                                     (0x00000FF0)
#define VO_CBLEND_write_enable2_mask                                  (0x00000008)
#define VO_CBLEND_thrblnddiff2_mask                                   (0x00000007)
#define VO_CBLEND_write_enable1(data)                                 (0x00001000&((data)<<12))
#define VO_CBLEND_thrblndlow(data)                                    (0x00000FF0&((data)<<4))
#define VO_CBLEND_write_enable2(data)                                 (0x00000008&((data)<<3))
#define VO_CBLEND_thrblnddiff2(data)                                  (0x00000007&(data))
#define VO_CBLEND_get_write_enable1(data)                             ((0x00001000&(data))>>12)
#define VO_CBLEND_get_thrblndlow(data)                                ((0x00000FF0&(data))>>4)
#define VO_CBLEND_get_write_enable2(data)                             ((0x00000008&(data))>>3)
#define VO_CBLEND_get_thrblnddiff2(data)                              (0x00000007&(data))

#define VO_VSCCTL1                                                    0x18005084
#define VO_VSCCTL1_reg_addr                                           "0xB8005084"
#define VO_VSCCTL1_reg                                                0xB8005084
#define VO_VSCCTL1_inst_addr                                          "0x0021"
#define VO_VSCCTL1_inst                                               0x0021
#define VO_VSCCTL1_y4ch_shift                                         (8)
#define VO_VSCCTL1_c4ch_shift                                         (7)
#define VO_VSCCTL1_yen_shift                                          (6)
#define VO_VSCCTL1_yoddtype_shift                                     (5)
#define VO_VSCCTL1_y2tap_shift                                        (4)
#define VO_VSCCTL1_cen_shift                                          (3)
#define VO_VSCCTL1_coddtype_shift                                     (2)
#define VO_VSCCTL1_c2tap_shift                                        (1)
#define VO_VSCCTL1_write_data_shift                                   (0)
#define VO_VSCCTL1_y4ch_mask                                          (0x00000100)
#define VO_VSCCTL1_c4ch_mask                                          (0x00000080)
#define VO_VSCCTL1_yen_mask                                           (0x00000040)
#define VO_VSCCTL1_yoddtype_mask                                      (0x00000020)
#define VO_VSCCTL1_y2tap_mask                                         (0x00000010)
#define VO_VSCCTL1_cen_mask                                           (0x00000008)
#define VO_VSCCTL1_coddtype_mask                                      (0x00000004)
#define VO_VSCCTL1_c2tap_mask                                         (0x00000002)
#define VO_VSCCTL1_write_data_mask                                    (0x00000001)
#define VO_VSCCTL1_y4ch(data)                                         (0x00000100&((data)<<8))
#define VO_VSCCTL1_c4ch(data)                                         (0x00000080&((data)<<7))
#define VO_VSCCTL1_yen(data)                                          (0x00000040&((data)<<6))
#define VO_VSCCTL1_yoddtype(data)                                     (0x00000020&((data)<<5))
#define VO_VSCCTL1_y2tap(data)                                        (0x00000010&((data)<<4))
#define VO_VSCCTL1_cen(data)                                          (0x00000008&((data)<<3))
#define VO_VSCCTL1_coddtype(data)                                     (0x00000004&((data)<<2))
#define VO_VSCCTL1_c2tap(data)                                        (0x00000002&((data)<<1))
#define VO_VSCCTL1_write_data(data)                                   (0x00000001&(data))
#define VO_VSCCTL1_get_y4ch(data)                                     ((0x00000100&(data))>>8)
#define VO_VSCCTL1_get_c4ch(data)                                     ((0x00000080&(data))>>7)
#define VO_VSCCTL1_get_yen(data)                                      ((0x00000040&(data))>>6)
#define VO_VSCCTL1_get_yoddtype(data)                                 ((0x00000020&(data))>>5)
#define VO_VSCCTL1_get_y2tap(data)                                    ((0x00000010&(data))>>4)
#define VO_VSCCTL1_get_cen(data)                                      ((0x00000008&(data))>>3)
#define VO_VSCCTL1_get_coddtype(data)                                 ((0x00000004&(data))>>2)
#define VO_VSCCTL1_get_c2tap(data)                                    ((0x00000002&(data))>>1)
#define VO_VSCCTL1_get_write_data(data)                               (0x00000001&(data))

#define VO_VYSC1                                                      0x18005088
#define VO_VYSC1_reg_addr                                             "0xB8005088"
#define VO_VYSC1_reg                                                  0xB8005088
#define VO_VYSC1_inst_addr                                            "0x0022"
#define VO_VYSC1_inst                                                 0x0022
#define VO_VYSC1_write_enable1_shift                                  (29)
#define VO_VYSC1_yonp_shift                                           (18)
#define VO_VYSC1_write_enable2_shift                                  (17)
#define VO_VYSC1_ydphs_shift                                          (0)
#define VO_VYSC1_write_enable1_mask                                   (0x20000000)
#define VO_VYSC1_yonp_mask                                            (0x1FFC0000)
#define VO_VYSC1_write_enable2_mask                                   (0x00020000)
#define VO_VYSC1_ydphs_mask                                           (0x0001FFFF)
#define VO_VYSC1_write_enable1(data)                                  (0x20000000&((data)<<29))
#define VO_VYSC1_yonp(data)                                           (0x1FFC0000&((data)<<18))
#define VO_VYSC1_write_enable2(data)                                  (0x00020000&((data)<<17))
#define VO_VYSC1_ydphs(data)                                          (0x0001FFFF&(data))
#define VO_VYSC1_get_write_enable1(data)                              ((0x20000000&(data))>>29)
#define VO_VYSC1_get_yonp(data)                                       ((0x1FFC0000&(data))>>18)
#define VO_VYSC1_get_write_enable2(data)                              ((0x00020000&(data))>>17)
#define VO_VYSC1_get_ydphs(data)                                      (0x0001FFFF&(data))

#define VO_VCSC1                                                      0x1800508C
#define VO_VCSC1_reg_addr                                             "0xB800508C"
#define VO_VCSC1_reg                                                  0xB800508C
#define VO_VCSC1_inst_addr                                            "0x0023"
#define VO_VCSC1_inst                                                 0x0023
#define VO_VCSC1_write_enable1_shift                                  (29)
#define VO_VCSC1_conp_shift                                           (18)
#define VO_VCSC1_write_enable2_shift                                  (17)
#define VO_VCSC1_cdphs_shift                                          (0)
#define VO_VCSC1_write_enable1_mask                                   (0x20000000)
#define VO_VCSC1_conp_mask                                            (0x1FFC0000)
#define VO_VCSC1_write_enable2_mask                                   (0x00020000)
#define VO_VCSC1_cdphs_mask                                           (0x0001FFFF)
#define VO_VCSC1_write_enable1(data)                                  (0x20000000&((data)<<29))
#define VO_VCSC1_conp(data)                                           (0x1FFC0000&((data)<<18))
#define VO_VCSC1_write_enable2(data)                                  (0x00020000&((data)<<17))
#define VO_VCSC1_cdphs(data)                                          (0x0001FFFF&(data))
#define VO_VCSC1_get_write_enable1(data)                              ((0x20000000&(data))>>29)
#define VO_VCSC1_get_conp(data)                                       ((0x1FFC0000&(data))>>18)
#define VO_VCSC1_get_write_enable2(data)                              ((0x00020000&(data))>>17)
#define VO_VCSC1_get_cdphs(data)                                      (0x0001FFFF&(data))

#define VO_VYIPOS1                                                    0x18005090
#define VO_VYIPOS1_reg_addr                                           "0xB8005090"
#define VO_VYIPOS1_reg                                                0xB8005090
#define VO_VYIPOS1_inst_addr                                          "0x0024"
#define VO_VYIPOS1_inst                                               0x0024
#define VO_VYIPOS1_init_offset_shift                                  (14)
#define VO_VYIPOS1_init_phase_shift                                   (0)
#define VO_VYIPOS1_init_offset_mask                                   (0x01FFC000)
#define VO_VYIPOS1_init_phase_mask                                    (0x00003FFF)
#define VO_VYIPOS1_init_offset(data)                                  (0x01FFC000&((data)<<14))
#define VO_VYIPOS1_init_phase(data)                                   (0x00003FFF&(data))
#define VO_VYIPOS1_get_init_offset(data)                              ((0x01FFC000&(data))>>14)
#define VO_VYIPOS1_get_init_phase(data)                               (0x00003FFF&(data))

#define VO_VYEPOS1                                                    0x18005094
#define VO_VYEPOS1_reg_addr                                           "0xB8005094"
#define VO_VYEPOS1_reg                                                0xB8005094
#define VO_VYEPOS1_inst_addr                                          "0x0025"
#define VO_VYEPOS1_inst                                               0x0025
#define VO_VYEPOS1_endline_shift                                      (0)
#define VO_VYEPOS1_endline_mask                                       (0x000007FF)
#define VO_VYEPOS1_endline(data)                                      (0x000007FF&(data))
#define VO_VYEPOS1_get_endline(data)                                  (0x000007FF&(data))

#define VO_VCIPOS1                                                    0x18005098
#define VO_VCIPOS1_reg_addr                                           "0xB8005098"
#define VO_VCIPOS1_reg                                                0xB8005098
#define VO_VCIPOS1_inst_addr                                          "0x0026"
#define VO_VCIPOS1_inst                                               0x0026
#define VO_VCIPOS1_init_offset_shift                                  (14)
#define VO_VCIPOS1_init_phase_shift                                   (0)
#define VO_VCIPOS1_init_offset_mask                                   (0x01FFC000)
#define VO_VCIPOS1_init_phase_mask                                    (0x00003FFF)
#define VO_VCIPOS1_init_offset(data)                                  (0x01FFC000&((data)<<14))
#define VO_VCIPOS1_init_phase(data)                                   (0x00003FFF&(data))
#define VO_VCIPOS1_get_init_offset(data)                              ((0x01FFC000&(data))>>14)
#define VO_VCIPOS1_get_init_phase(data)                               (0x00003FFF&(data))

#define VO_VCEPOS1                                                    0x1800509C
#define VO_VCEPOS1_reg_addr                                           "0xB800509C"
#define VO_VCEPOS1_reg                                                0xB800509C
#define VO_VCEPOS1_inst_addr                                          "0x0027"
#define VO_VCEPOS1_inst                                               0x0027
#define VO_VCEPOS1_endline_shift                                      (0)
#define VO_VCEPOS1_endline_mask                                       (0x000007FF)
#define VO_VCEPOS1_endline(data)                                      (0x000007FF&(data))
#define VO_VCEPOS1_get_endline(data)                                  (0x000007FF&(data))

#define VO_VYSCCOEF1_0                                                0x180050A0
#define VO_VYSCCOEF1_1                                                0x180050A4
#define VO_VYSCCOEF1_2                                                0x180050A8
#define VO_VYSCCOEF1_3                                                0x180050AC
#define VO_VYSCCOEF1_4                                                0x180050B0
#define VO_VYSCCOEF1_5                                                0x180050B4
#define VO_VYSCCOEF1_6                                                0x180050B8
#define VO_VYSCCOEF1_7                                                0x180050BC
#define VO_VYSCCOEF1_8                                                0x180050C0
#define VO_VYSCCOEF1_9                                                0x180050C4
#define VO_VYSCCOEF1_10                                               0x180050C8
#define VO_VYSCCOEF1_11                                               0x180050CC
#define VO_VYSCCOEF1_12                                               0x180050D0
#define VO_VYSCCOEF1_13                                               0x180050D4
#define VO_VYSCCOEF1_14                                               0x180050D8
#define VO_VYSCCOEF1_15                                               0x180050DC
#define VO_VYSCCOEF1_0_reg_addr                                       "0xB80050A0"
#define VO_VYSCCOEF1_1_reg_addr                                       "0xB80050A4"
#define VO_VYSCCOEF1_2_reg_addr                                       "0xB80050A8"
#define VO_VYSCCOEF1_3_reg_addr                                       "0xB80050AC"
#define VO_VYSCCOEF1_4_reg_addr                                       "0xB80050B0"
#define VO_VYSCCOEF1_5_reg_addr                                       "0xB80050B4"
#define VO_VYSCCOEF1_6_reg_addr                                       "0xB80050B8"
#define VO_VYSCCOEF1_7_reg_addr                                       "0xB80050BC"
#define VO_VYSCCOEF1_8_reg_addr                                       "0xB80050C0"
#define VO_VYSCCOEF1_9_reg_addr                                       "0xB80050C4"
#define VO_VYSCCOEF1_10_reg_addr                                      "0xB80050C8"
#define VO_VYSCCOEF1_11_reg_addr                                      "0xB80050CC"
#define VO_VYSCCOEF1_12_reg_addr                                      "0xB80050D0"
#define VO_VYSCCOEF1_13_reg_addr                                      "0xB80050D4"
#define VO_VYSCCOEF1_14_reg_addr                                      "0xB80050D8"
#define VO_VYSCCOEF1_15_reg_addr                                      "0xB80050DC"
#define VO_VYSCCOEF1_0_reg                                            0xB80050A0
#define VO_VYSCCOEF1_1_reg                                            0xB80050A4
#define VO_VYSCCOEF1_2_reg                                            0xB80050A8
#define VO_VYSCCOEF1_3_reg                                            0xB80050AC
#define VO_VYSCCOEF1_4_reg                                            0xB80050B0
#define VO_VYSCCOEF1_5_reg                                            0xB80050B4
#define VO_VYSCCOEF1_6_reg                                            0xB80050B8
#define VO_VYSCCOEF1_7_reg                                            0xB80050BC
#define VO_VYSCCOEF1_8_reg                                            0xB80050C0
#define VO_VYSCCOEF1_9_reg                                            0xB80050C4
#define VO_VYSCCOEF1_10_reg                                           0xB80050C8
#define VO_VYSCCOEF1_11_reg                                           0xB80050CC
#define VO_VYSCCOEF1_12_reg                                           0xB80050D0
#define VO_VYSCCOEF1_13_reg                                           0xB80050D4
#define VO_VYSCCOEF1_14_reg                                           0xB80050D8
#define VO_VYSCCOEF1_15_reg                                           0xB80050DC
#define VO_VYSCCOEF1_0_inst_addr                                      "0x0028"
#define VO_VYSCCOEF1_0_inst                                           0x0028
#define VO_VYSCCOEF1_1_inst_addr                                      "0x0029"
#define VO_VYSCCOEF1_1_inst                                           0x0029
#define VO_VYSCCOEF1_2_inst_addr                                      "0x002A"
#define VO_VYSCCOEF1_2_inst                                           0x002A
#define VO_VYSCCOEF1_3_inst_addr                                      "0x002B"
#define VO_VYSCCOEF1_3_inst                                           0x002B
#define VO_VYSCCOEF1_4_inst_addr                                      "0x002C"
#define VO_VYSCCOEF1_4_inst                                           0x002C
#define VO_VYSCCOEF1_5_inst_addr                                      "0x002D"
#define VO_VYSCCOEF1_5_inst                                           0x002D
#define VO_VYSCCOEF1_6_inst_addr                                      "0x002E"
#define VO_VYSCCOEF1_6_inst                                           0x002E
#define VO_VYSCCOEF1_7_inst_addr                                      "0x002F"
#define VO_VYSCCOEF1_7_inst                                           0x002F
#define VO_VYSCCOEF1_8_inst_addr                                      "0x0030"
#define VO_VYSCCOEF1_8_inst                                           0x0030
#define VO_VYSCCOEF1_9_inst_addr                                      "0x0031"
#define VO_VYSCCOEF1_9_inst                                           0x0031
#define VO_VYSCCOEF1_10_inst_addr                                     "0x0032"
#define VO_VYSCCOEF1_10_inst                                          0x0032
#define VO_VYSCCOEF1_11_inst_addr                                     "0x0033"
#define VO_VYSCCOEF1_11_inst                                          0x0033
#define VO_VYSCCOEF1_12_inst_addr                                     "0x0034"
#define VO_VYSCCOEF1_12_inst                                          0x0034
#define VO_VYSCCOEF1_13_inst_addr                                     "0x0035"
#define VO_VYSCCOEF1_13_inst                                          0x0035
#define VO_VYSCCOEF1_14_inst_addr                                     "0x0036"
#define VO_VYSCCOEF1_14_inst                                          0x0036
#define VO_VYSCCOEF1_15_inst_addr                                     "0x0037"
#define VO_VYSCCOEF1_15_inst                                          0x0037
#define VO_VYSCCOEF1_ysccoef_shift                                    (0)
#define VO_VYSCCOEF1_ysccoef_mask                                     (0x00003FFF)
#define VO_VYSCCOEF1_ysccoef(data)                                    (0x00003FFF&(data))
#define VO_VYSCCOEF1_get_ysccoef(data)                                (0x00003FFF&(data))

#define VO_VCSCCOEF1_0                                                0x180050E0
#define VO_VCSCCOEF1_1                                                0x180050E4
#define VO_VCSCCOEF1_2                                                0x180050E8
#define VO_VCSCCOEF1_3                                                0x180050EC
#define VO_VCSCCOEF1_4                                                0x180050F0
#define VO_VCSCCOEF1_5                                                0x180050F4
#define VO_VCSCCOEF1_6                                                0x180050F8
#define VO_VCSCCOEF1_7                                                0x180050FC
#define VO_VCSCCOEF1_8                                                0x18005100
#define VO_VCSCCOEF1_9                                                0x18005104
#define VO_VCSCCOEF1_10                                               0x18005108
#define VO_VCSCCOEF1_11                                               0x1800510C
#define VO_VCSCCOEF1_12                                               0x18005110
#define VO_VCSCCOEF1_13                                               0x18005114
#define VO_VCSCCOEF1_14                                               0x18005118
#define VO_VCSCCOEF1_15                                               0x1800511C
#define VO_VCSCCOEF1_0_reg_addr                                       "0xB80050E0"
#define VO_VCSCCOEF1_1_reg_addr                                       "0xB80050E4"
#define VO_VCSCCOEF1_2_reg_addr                                       "0xB80050E8"
#define VO_VCSCCOEF1_3_reg_addr                                       "0xB80050EC"
#define VO_VCSCCOEF1_4_reg_addr                                       "0xB80050F0"
#define VO_VCSCCOEF1_5_reg_addr                                       "0xB80050F4"
#define VO_VCSCCOEF1_6_reg_addr                                       "0xB80050F8"
#define VO_VCSCCOEF1_7_reg_addr                                       "0xB80050FC"
#define VO_VCSCCOEF1_8_reg_addr                                       "0xB8005100"
#define VO_VCSCCOEF1_9_reg_addr                                       "0xB8005104"
#define VO_VCSCCOEF1_10_reg_addr                                      "0xB8005108"
#define VO_VCSCCOEF1_11_reg_addr                                      "0xB800510C"
#define VO_VCSCCOEF1_12_reg_addr                                      "0xB8005110"
#define VO_VCSCCOEF1_13_reg_addr                                      "0xB8005114"
#define VO_VCSCCOEF1_14_reg_addr                                      "0xB8005118"
#define VO_VCSCCOEF1_15_reg_addr                                      "0xB800511C"
#define VO_VCSCCOEF1_0_reg                                            0xB80050E0
#define VO_VCSCCOEF1_1_reg                                            0xB80050E4
#define VO_VCSCCOEF1_2_reg                                            0xB80050E8
#define VO_VCSCCOEF1_3_reg                                            0xB80050EC
#define VO_VCSCCOEF1_4_reg                                            0xB80050F0
#define VO_VCSCCOEF1_5_reg                                            0xB80050F4
#define VO_VCSCCOEF1_6_reg                                            0xB80050F8
#define VO_VCSCCOEF1_7_reg                                            0xB80050FC
#define VO_VCSCCOEF1_8_reg                                            0xB8005100
#define VO_VCSCCOEF1_9_reg                                            0xB8005104
#define VO_VCSCCOEF1_10_reg                                           0xB8005108
#define VO_VCSCCOEF1_11_reg                                           0xB800510C
#define VO_VCSCCOEF1_12_reg                                           0xB8005110
#define VO_VCSCCOEF1_13_reg                                           0xB8005114
#define VO_VCSCCOEF1_14_reg                                           0xB8005118
#define VO_VCSCCOEF1_15_reg                                           0xB800511C
#define VO_VCSCCOEF1_0_inst_addr                                      "0x0038"
#define VO_VCSCCOEF1_0_inst                                           0x0038
#define VO_VCSCCOEF1_1_inst_addr                                      "0x0039"
#define VO_VCSCCOEF1_1_inst                                           0x0039
#define VO_VCSCCOEF1_2_inst_addr                                      "0x003A"
#define VO_VCSCCOEF1_2_inst                                           0x003A
#define VO_VCSCCOEF1_3_inst_addr                                      "0x003B"
#define VO_VCSCCOEF1_3_inst                                           0x003B
#define VO_VCSCCOEF1_4_inst_addr                                      "0x003C"
#define VO_VCSCCOEF1_4_inst                                           0x003C
#define VO_VCSCCOEF1_5_inst_addr                                      "0x003D"
#define VO_VCSCCOEF1_5_inst                                           0x003D
#define VO_VCSCCOEF1_6_inst_addr                                      "0x003E"
#define VO_VCSCCOEF1_6_inst                                           0x003E
#define VO_VCSCCOEF1_7_inst_addr                                      "0x003F"
#define VO_VCSCCOEF1_7_inst                                           0x003F
#define VO_VCSCCOEF1_8_inst_addr                                      "0x0040"
#define VO_VCSCCOEF1_8_inst                                           0x0040
#define VO_VCSCCOEF1_9_inst_addr                                      "0x0041"
#define VO_VCSCCOEF1_9_inst                                           0x0041
#define VO_VCSCCOEF1_10_inst_addr                                     "0x0042"
#define VO_VCSCCOEF1_10_inst                                          0x0042
#define VO_VCSCCOEF1_11_inst_addr                                     "0x0043"
#define VO_VCSCCOEF1_11_inst                                          0x0043
#define VO_VCSCCOEF1_12_inst_addr                                     "0x0044"
#define VO_VCSCCOEF1_12_inst                                          0x0044
#define VO_VCSCCOEF1_13_inst_addr                                     "0x0045"
#define VO_VCSCCOEF1_13_inst                                          0x0045
#define VO_VCSCCOEF1_14_inst_addr                                     "0x0046"
#define VO_VCSCCOEF1_14_inst                                          0x0046
#define VO_VCSCCOEF1_15_inst_addr                                     "0x0047"
#define VO_VCSCCOEF1_15_inst                                          0x0047
#define VO_VCSCCOEF1_csccoef_shift                                    (0)
#define VO_VCSCCOEF1_csccoef_mask                                     (0x00003FFF)
#define VO_VCSCCOEF1_csccoef(data)                                    (0x00003FFF&(data))
#define VO_VCSCCOEF1_get_csccoef(data)                                (0x00003FFF&(data))

#define VO_HSCCTL1                                                    0x18005120
#define VO_HSCCTL1_reg_addr                                           "0xB8005120"
#define VO_HSCCTL1_reg                                                0xB8005120
#define VO_HSCCTL1_inst_addr                                          "0x0048"
#define VO_HSCCTL1_inst                                               0x0048
#define VO_HSCCTL1_yen_shift                                          (4)
#define VO_HSCCTL1_yoddtype_shift                                     (3)
#define VO_HSCCTL1_cen_shift                                          (2)
#define VO_HSCCTL1_coddtype_shift                                     (1)
#define VO_HSCCTL1_write_data_shift                                   (0)
#define VO_HSCCTL1_yen_mask                                           (0x00000010)
#define VO_HSCCTL1_yoddtype_mask                                      (0x00000008)
#define VO_HSCCTL1_cen_mask                                           (0x00000004)
#define VO_HSCCTL1_coddtype_mask                                      (0x00000002)
#define VO_HSCCTL1_write_data_mask                                    (0x00000001)
#define VO_HSCCTL1_yen(data)                                          (0x00000010&((data)<<4))
#define VO_HSCCTL1_yoddtype(data)                                     (0x00000008&((data)<<3))
#define VO_HSCCTL1_cen(data)                                          (0x00000004&((data)<<2))
#define VO_HSCCTL1_coddtype(data)                                     (0x00000002&((data)<<1))
#define VO_HSCCTL1_write_data(data)                                   (0x00000001&(data))
#define VO_HSCCTL1_get_yen(data)                                      ((0x00000010&(data))>>4)
#define VO_HSCCTL1_get_yoddtype(data)                                 ((0x00000008&(data))>>3)
#define VO_HSCCTL1_get_cen(data)                                      ((0x00000004&(data))>>2)
#define VO_HSCCTL1_get_coddtype(data)                                 ((0x00000002&(data))>>1)
#define VO_HSCCTL1_get_write_data(data)                               (0x00000001&(data))

#define VO_HYSC1                                                      0x18005124
#define VO_HYSC1_reg_addr                                             "0xB8005124"
#define VO_HYSC1_reg                                                  0xB8005124
#define VO_HYSC1_inst_addr                                            "0x0049"
#define VO_HYSC1_inst                                                 0x0049
#define VO_HYSC1_write_enable1_shift                                  (29)
#define VO_HYSC1_yonp_shift                                           (18)
#define VO_HYSC1_write_enable2_shift                                  (17)
#define VO_HYSC1_ydphs_shift                                          (0)
#define VO_HYSC1_write_enable1_mask                                   (0x20000000)
#define VO_HYSC1_yonp_mask                                            (0x1FFC0000)
#define VO_HYSC1_write_enable2_mask                                   (0x00020000)
#define VO_HYSC1_ydphs_mask                                           (0x0001FFFF)
#define VO_HYSC1_write_enable1(data)                                  (0x20000000&((data)<<29))
#define VO_HYSC1_yonp(data)                                           (0x1FFC0000&((data)<<18))
#define VO_HYSC1_write_enable2(data)                                  (0x00020000&((data)<<17))
#define VO_HYSC1_ydphs(data)                                          (0x0001FFFF&(data))
#define VO_HYSC1_get_write_enable1(data)                              ((0x20000000&(data))>>29)
#define VO_HYSC1_get_yonp(data)                                       ((0x1FFC0000&(data))>>18)
#define VO_HYSC1_get_write_enable2(data)                              ((0x00020000&(data))>>17)
#define VO_HYSC1_get_ydphs(data)                                      (0x0001FFFF&(data))

#define VO_HYIPOS1                                                    0x18005128
#define VO_HYIPOS1_reg_addr                                           "0xB8005128"
#define VO_HYIPOS1_reg                                                0xB8005128
#define VO_HYIPOS1_inst_addr                                          "0x004A"
#define VO_HYIPOS1_inst                                               0x004A
#define VO_HYIPOS1_init_phase_shift                                   (0)
#define VO_HYIPOS1_init_phase_mask                                    (0x00003FFF)
#define VO_HYIPOS1_init_phase(data)                                   (0x00003FFF&(data))
#define VO_HYIPOS1_get_init_phase(data)                               (0x00003FFF&(data))

#define VO_HYEPOS1                                                    0x1800512C
#define VO_HYEPOS1_reg_addr                                           "0xB800512C"
#define VO_HYEPOS1_reg                                                0xB800512C
#define VO_HYEPOS1_inst_addr                                          "0x004B"
#define VO_HYEPOS1_inst                                               0x004B
#define VO_HYEPOS1_begin_point_shift                                  (11)
#define VO_HYEPOS1_end_point_shift                                    (0)
#define VO_HYEPOS1_begin_point_mask                                   (0x003FF800)
#define VO_HYEPOS1_end_point_mask                                     (0x000007FF)
#define VO_HYEPOS1_begin_point(data)                                  (0x003FF800&((data)<<11))
#define VO_HYEPOS1_end_point(data)                                    (0x000007FF&(data))
#define VO_HYEPOS1_get_begin_point(data)                              ((0x003FF800&(data))>>11)
#define VO_HYEPOS1_get_end_point(data)                                (0x000007FF&(data))

#define VO_HYWIDTH1                                                   0x18005130
#define VO_HYWIDTH1_reg_addr                                          "0xB8005130"
#define VO_HYWIDTH1_reg                                               0xB8005130
#define VO_HYWIDTH1_inst_addr                                         "0x004C"
#define VO_HYWIDTH1_inst                                              0x004C
#define VO_HYWIDTH1_shift_shift                                       (11)
#define VO_HYWIDTH1_width_shift                                       (0)
#define VO_HYWIDTH1_shift_mask                                        (0x0000F800)
#define VO_HYWIDTH1_width_mask                                        (0x000007FF)
#define VO_HYWIDTH1_shift(data)                                       (0x0000F800&((data)<<11))
#define VO_HYWIDTH1_width(data)                                       (0x000007FF&(data))
#define VO_HYWIDTH1_get_shift(data)                                   ((0x0000F800&(data))>>11)
#define VO_HYWIDTH1_get_width(data)                                   (0x000007FF&(data))

#define VO_HCSC1                                                      0x18005134
#define VO_HCSC1_reg_addr                                             "0xB8005134"
#define VO_HCSC1_reg                                                  0xB8005134
#define VO_HCSC1_inst_addr                                            "0x004D"
#define VO_HCSC1_inst                                                 0x004D
#define VO_HCSC1_write_enable1_shift                                  (29)
#define VO_HCSC1_conp_shift                                           (18)
#define VO_HCSC1_write_enable2_shift                                  (17)
#define VO_HCSC1_cdphs_shift                                          (0)
#define VO_HCSC1_write_enable1_mask                                   (0x20000000)
#define VO_HCSC1_conp_mask                                            (0x1FFC0000)
#define VO_HCSC1_write_enable2_mask                                   (0x00020000)
#define VO_HCSC1_cdphs_mask                                           (0x0001FFFF)
#define VO_HCSC1_write_enable1(data)                                  (0x20000000&((data)<<29))
#define VO_HCSC1_conp(data)                                           (0x1FFC0000&((data)<<18))
#define VO_HCSC1_write_enable2(data)                                  (0x00020000&((data)<<17))
#define VO_HCSC1_cdphs(data)                                          (0x0001FFFF&(data))
#define VO_HCSC1_get_write_enable1(data)                              ((0x20000000&(data))>>29)
#define VO_HCSC1_get_conp(data)                                       ((0x1FFC0000&(data))>>18)
#define VO_HCSC1_get_write_enable2(data)                              ((0x00020000&(data))>>17)
#define VO_HCSC1_get_cdphs(data)                                      (0x0001FFFF&(data))

#define VO_HCIPOS1                                                    0x18005138
#define VO_HCIPOS1_reg_addr                                           "0xB8005138"
#define VO_HCIPOS1_reg                                                0xB8005138
#define VO_HCIPOS1_inst_addr                                          "0x004E"
#define VO_HCIPOS1_inst                                               0x004E
#define VO_HCIPOS1_init_phase_shift                                   (0)
#define VO_HCIPOS1_init_phase_mask                                    (0x00003FFF)
#define VO_HCIPOS1_init_phase(data)                                   (0x00003FFF&(data))
#define VO_HCIPOS1_get_init_phase(data)                               (0x00003FFF&(data))

#define VO_HCEPOS1                                                    0x1800513C
#define VO_HCEPOS1_reg_addr                                           "0xB800513C"
#define VO_HCEPOS1_reg                                                0xB800513C
#define VO_HCEPOS1_inst_addr                                          "0x004F"
#define VO_HCEPOS1_inst                                               0x004F
#define VO_HCEPOS1_begin_point_shift                                  (11)
#define VO_HCEPOS1_end_point_shift                                    (0)
#define VO_HCEPOS1_begin_point_mask                                   (0x003FF800)
#define VO_HCEPOS1_end_point_mask                                     (0x000007FF)
#define VO_HCEPOS1_begin_point(data)                                  (0x003FF800&((data)<<11))
#define VO_HCEPOS1_end_point(data)                                    (0x000007FF&(data))
#define VO_HCEPOS1_get_begin_point(data)                              ((0x003FF800&(data))>>11)
#define VO_HCEPOS1_get_end_point(data)                                (0x000007FF&(data))

#define VO_HCWIDTH1                                                   0x18005140
#define VO_HCWIDTH1_reg_addr                                          "0xB8005140"
#define VO_HCWIDTH1_reg                                               0xB8005140
#define VO_HCWIDTH1_inst_addr                                         "0x0050"
#define VO_HCWIDTH1_inst                                              0x0050
#define VO_HCWIDTH1_shift_shift                                       (11)
#define VO_HCWIDTH1_width_shift                                       (0)
#define VO_HCWIDTH1_shift_mask                                        (0x0000F800)
#define VO_HCWIDTH1_width_mask                                        (0x000007FF)
#define VO_HCWIDTH1_shift(data)                                       (0x0000F800&((data)<<11))
#define VO_HCWIDTH1_width(data)                                       (0x000007FF&(data))
#define VO_HCWIDTH1_get_shift(data)                                   ((0x0000F800&(data))>>11)
#define VO_HCWIDTH1_get_width(data)                                   (0x000007FF&(data))

#define VO_HYSCCOEF1_0                                                0x18005144
#define VO_HYSCCOEF1_1                                                0x18005148
#define VO_HYSCCOEF1_2                                                0x1800514C
#define VO_HYSCCOEF1_3                                                0x18005150
#define VO_HYSCCOEF1_4                                                0x18005154
#define VO_HYSCCOEF1_5                                                0x18005158
#define VO_HYSCCOEF1_6                                                0x1800515C
#define VO_HYSCCOEF1_7                                                0x18005160
#define VO_HYSCCOEF1_8                                                0x18005164
#define VO_HYSCCOEF1_9                                                0x18005168
#define VO_HYSCCOEF1_10                                               0x1800516C
#define VO_HYSCCOEF1_11                                               0x18005170
#define VO_HYSCCOEF1_12                                               0x18005174
#define VO_HYSCCOEF1_13                                               0x18005178
#define VO_HYSCCOEF1_14                                               0x1800517C
#define VO_HYSCCOEF1_15                                               0x18005180
#define VO_HYSCCOEF1_16                                               0x18005184
#define VO_HYSCCOEF1_17                                               0x18005188
#define VO_HYSCCOEF1_18                                               0x1800518C
#define VO_HYSCCOEF1_19                                               0x18005190
#define VO_HYSCCOEF1_20                                               0x18005194
#define VO_HYSCCOEF1_21                                               0x18005198
#define VO_HYSCCOEF1_22                                               0x1800519C
#define VO_HYSCCOEF1_23                                               0x180051A0
#define VO_HYSCCOEF1_24                                               0x180051A4
#define VO_HYSCCOEF1_25                                               0x180051A8
#define VO_HYSCCOEF1_26                                               0x180051AC
#define VO_HYSCCOEF1_27                                               0x180051B0
#define VO_HYSCCOEF1_28                                               0x180051B4
#define VO_HYSCCOEF1_29                                               0x180051B8
#define VO_HYSCCOEF1_30                                               0x180051BC
#define VO_HYSCCOEF1_31                                               0x180051C0
#define VO_HYSCCOEF1_0_reg_addr                                       "0xB8005144"
#define VO_HYSCCOEF1_1_reg_addr                                       "0xB8005148"
#define VO_HYSCCOEF1_2_reg_addr                                       "0xB800514C"
#define VO_HYSCCOEF1_3_reg_addr                                       "0xB8005150"
#define VO_HYSCCOEF1_4_reg_addr                                       "0xB8005154"
#define VO_HYSCCOEF1_5_reg_addr                                       "0xB8005158"
#define VO_HYSCCOEF1_6_reg_addr                                       "0xB800515C"
#define VO_HYSCCOEF1_7_reg_addr                                       "0xB8005160"
#define VO_HYSCCOEF1_8_reg_addr                                       "0xB8005164"
#define VO_HYSCCOEF1_9_reg_addr                                       "0xB8005168"
#define VO_HYSCCOEF1_10_reg_addr                                      "0xB800516C"
#define VO_HYSCCOEF1_11_reg_addr                                      "0xB8005170"
#define VO_HYSCCOEF1_12_reg_addr                                      "0xB8005174"
#define VO_HYSCCOEF1_13_reg_addr                                      "0xB8005178"
#define VO_HYSCCOEF1_14_reg_addr                                      "0xB800517C"
#define VO_HYSCCOEF1_15_reg_addr                                      "0xB8005180"
#define VO_HYSCCOEF1_16_reg_addr                                      "0xB8005184"
#define VO_HYSCCOEF1_17_reg_addr                                      "0xB8005188"
#define VO_HYSCCOEF1_18_reg_addr                                      "0xB800518C"
#define VO_HYSCCOEF1_19_reg_addr                                      "0xB8005190"
#define VO_HYSCCOEF1_20_reg_addr                                      "0xB8005194"
#define VO_HYSCCOEF1_21_reg_addr                                      "0xB8005198"
#define VO_HYSCCOEF1_22_reg_addr                                      "0xB800519C"
#define VO_HYSCCOEF1_23_reg_addr                                      "0xB80051A0"
#define VO_HYSCCOEF1_24_reg_addr                                      "0xB80051A4"
#define VO_HYSCCOEF1_25_reg_addr                                      "0xB80051A8"
#define VO_HYSCCOEF1_26_reg_addr                                      "0xB80051AC"
#define VO_HYSCCOEF1_27_reg_addr                                      "0xB80051B0"
#define VO_HYSCCOEF1_28_reg_addr                                      "0xB80051B4"
#define VO_HYSCCOEF1_29_reg_addr                                      "0xB80051B8"
#define VO_HYSCCOEF1_30_reg_addr                                      "0xB80051BC"
#define VO_HYSCCOEF1_31_reg_addr                                      "0xB80051C0"
#define VO_HYSCCOEF1_0_reg                                            0xB8005144
#define VO_HYSCCOEF1_1_reg                                            0xB8005148
#define VO_HYSCCOEF1_2_reg                                            0xB800514C
#define VO_HYSCCOEF1_3_reg                                            0xB8005150
#define VO_HYSCCOEF1_4_reg                                            0xB8005154
#define VO_HYSCCOEF1_5_reg                                            0xB8005158
#define VO_HYSCCOEF1_6_reg                                            0xB800515C
#define VO_HYSCCOEF1_7_reg                                            0xB8005160
#define VO_HYSCCOEF1_8_reg                                            0xB8005164
#define VO_HYSCCOEF1_9_reg                                            0xB8005168
#define VO_HYSCCOEF1_10_reg                                           0xB800516C
#define VO_HYSCCOEF1_11_reg                                           0xB8005170
#define VO_HYSCCOEF1_12_reg                                           0xB8005174
#define VO_HYSCCOEF1_13_reg                                           0xB8005178
#define VO_HYSCCOEF1_14_reg                                           0xB800517C
#define VO_HYSCCOEF1_15_reg                                           0xB8005180
#define VO_HYSCCOEF1_16_reg                                           0xB8005184
#define VO_HYSCCOEF1_17_reg                                           0xB8005188
#define VO_HYSCCOEF1_18_reg                                           0xB800518C
#define VO_HYSCCOEF1_19_reg                                           0xB8005190
#define VO_HYSCCOEF1_20_reg                                           0xB8005194
#define VO_HYSCCOEF1_21_reg                                           0xB8005198
#define VO_HYSCCOEF1_22_reg                                           0xB800519C
#define VO_HYSCCOEF1_23_reg                                           0xB80051A0
#define VO_HYSCCOEF1_24_reg                                           0xB80051A4
#define VO_HYSCCOEF1_25_reg                                           0xB80051A8
#define VO_HYSCCOEF1_26_reg                                           0xB80051AC
#define VO_HYSCCOEF1_27_reg                                           0xB80051B0
#define VO_HYSCCOEF1_28_reg                                           0xB80051B4
#define VO_HYSCCOEF1_29_reg                                           0xB80051B8
#define VO_HYSCCOEF1_30_reg                                           0xB80051BC
#define VO_HYSCCOEF1_31_reg                                           0xB80051C0
#define VO_HYSCCOEF1_0_inst_addr                                      "0x0051"
#define VO_HYSCCOEF1_0_inst                                           0x0051
#define VO_HYSCCOEF1_1_inst_addr                                      "0x0052"
#define VO_HYSCCOEF1_1_inst                                           0x0052
#define VO_HYSCCOEF1_2_inst_addr                                      "0x0053"
#define VO_HYSCCOEF1_2_inst                                           0x0053
#define VO_HYSCCOEF1_3_inst_addr                                      "0x0054"
#define VO_HYSCCOEF1_3_inst                                           0x0054
#define VO_HYSCCOEF1_4_inst_addr                                      "0x0055"
#define VO_HYSCCOEF1_4_inst                                           0x0055
#define VO_HYSCCOEF1_5_inst_addr                                      "0x0056"
#define VO_HYSCCOEF1_5_inst                                           0x0056
#define VO_HYSCCOEF1_6_inst_addr                                      "0x0057"
#define VO_HYSCCOEF1_6_inst                                           0x0057
#define VO_HYSCCOEF1_7_inst_addr                                      "0x0058"
#define VO_HYSCCOEF1_7_inst                                           0x0058
#define VO_HYSCCOEF1_8_inst_addr                                      "0x0059"
#define VO_HYSCCOEF1_8_inst                                           0x0059
#define VO_HYSCCOEF1_9_inst_addr                                      "0x005A"
#define VO_HYSCCOEF1_9_inst                                           0x005A
#define VO_HYSCCOEF1_10_inst_addr                                     "0x005B"
#define VO_HYSCCOEF1_10_inst                                          0x005B
#define VO_HYSCCOEF1_11_inst_addr                                     "0x005C"
#define VO_HYSCCOEF1_11_inst                                          0x005C
#define VO_HYSCCOEF1_12_inst_addr                                     "0x005D"
#define VO_HYSCCOEF1_12_inst                                          0x005D
#define VO_HYSCCOEF1_13_inst_addr                                     "0x005E"
#define VO_HYSCCOEF1_13_inst                                          0x005E
#define VO_HYSCCOEF1_14_inst_addr                                     "0x005F"
#define VO_HYSCCOEF1_14_inst                                          0x005F
#define VO_HYSCCOEF1_15_inst_addr                                     "0x0060"
#define VO_HYSCCOEF1_15_inst                                          0x0060
#define VO_HYSCCOEF1_16_inst_addr                                     "0x0061"
#define VO_HYSCCOEF1_16_inst                                          0x0061
#define VO_HYSCCOEF1_17_inst_addr                                     "0x0062"
#define VO_HYSCCOEF1_17_inst                                          0x0062
#define VO_HYSCCOEF1_18_inst_addr                                     "0x0063"
#define VO_HYSCCOEF1_18_inst                                          0x0063
#define VO_HYSCCOEF1_19_inst_addr                                     "0x0064"
#define VO_HYSCCOEF1_19_inst                                          0x0064
#define VO_HYSCCOEF1_20_inst_addr                                     "0x0065"
#define VO_HYSCCOEF1_20_inst                                          0x0065
#define VO_HYSCCOEF1_21_inst_addr                                     "0x0066"
#define VO_HYSCCOEF1_21_inst                                          0x0066
#define VO_HYSCCOEF1_22_inst_addr                                     "0x0067"
#define VO_HYSCCOEF1_22_inst                                          0x0067
#define VO_HYSCCOEF1_23_inst_addr                                     "0x0068"
#define VO_HYSCCOEF1_23_inst                                          0x0068
#define VO_HYSCCOEF1_24_inst_addr                                     "0x0069"
#define VO_HYSCCOEF1_24_inst                                          0x0069
#define VO_HYSCCOEF1_25_inst_addr                                     "0x006A"
#define VO_HYSCCOEF1_25_inst                                          0x006A
#define VO_HYSCCOEF1_26_inst_addr                                     "0x006B"
#define VO_HYSCCOEF1_26_inst                                          0x006B
#define VO_HYSCCOEF1_27_inst_addr                                     "0x006C"
#define VO_HYSCCOEF1_27_inst                                          0x006C
#define VO_HYSCCOEF1_28_inst_addr                                     "0x006D"
#define VO_HYSCCOEF1_28_inst                                          0x006D
#define VO_HYSCCOEF1_29_inst_addr                                     "0x006E"
#define VO_HYSCCOEF1_29_inst                                          0x006E
#define VO_HYSCCOEF1_30_inst_addr                                     "0x006F"
#define VO_HYSCCOEF1_30_inst                                          0x006F
#define VO_HYSCCOEF1_31_inst_addr                                     "0x0070"
#define VO_HYSCCOEF1_31_inst                                          0x0070
#define VO_HYSCCOEF1_ysccoef_shift                                    (0)
#define VO_HYSCCOEF1_ysccoef_mask                                     (0x00003FFF)
#define VO_HYSCCOEF1_ysccoef(data)                                    (0x00003FFF&(data))
#define VO_HYSCCOEF1_get_ysccoef(data)                                (0x00003FFF&(data))

#define VO_HCSCCOEF1_0                                                0x180051C4
#define VO_HCSCCOEF1_1                                                0x180051C8
#define VO_HCSCCOEF1_2                                                0x180051CC
#define VO_HCSCCOEF1_3                                                0x180051D0
#define VO_HCSCCOEF1_4                                                0x180051D4
#define VO_HCSCCOEF1_5                                                0x180051D8
#define VO_HCSCCOEF1_6                                                0x180051DC
#define VO_HCSCCOEF1_7                                                0x180051E0
#define VO_HCSCCOEF1_8                                                0x180051E4
#define VO_HCSCCOEF1_9                                                0x180051E8
#define VO_HCSCCOEF1_10                                               0x180051EC
#define VO_HCSCCOEF1_11                                               0x180051F0
#define VO_HCSCCOEF1_12                                               0x180051F4
#define VO_HCSCCOEF1_13                                               0x180051F8
#define VO_HCSCCOEF1_14                                               0x180051FC
#define VO_HCSCCOEF1_15                                               0x18005200
#define VO_HCSCCOEF1_0_reg_addr                                       "0xB80051C4"
#define VO_HCSCCOEF1_1_reg_addr                                       "0xB80051C8"
#define VO_HCSCCOEF1_2_reg_addr                                       "0xB80051CC"
#define VO_HCSCCOEF1_3_reg_addr                                       "0xB80051D0"
#define VO_HCSCCOEF1_4_reg_addr                                       "0xB80051D4"
#define VO_HCSCCOEF1_5_reg_addr                                       "0xB80051D8"
#define VO_HCSCCOEF1_6_reg_addr                                       "0xB80051DC"
#define VO_HCSCCOEF1_7_reg_addr                                       "0xB80051E0"
#define VO_HCSCCOEF1_8_reg_addr                                       "0xB80051E4"
#define VO_HCSCCOEF1_9_reg_addr                                       "0xB80051E8"
#define VO_HCSCCOEF1_10_reg_addr                                      "0xB80051EC"
#define VO_HCSCCOEF1_11_reg_addr                                      "0xB80051F0"
#define VO_HCSCCOEF1_12_reg_addr                                      "0xB80051F4"
#define VO_HCSCCOEF1_13_reg_addr                                      "0xB80051F8"
#define VO_HCSCCOEF1_14_reg_addr                                      "0xB80051FC"
#define VO_HCSCCOEF1_15_reg_addr                                      "0xB8005200"
#define VO_HCSCCOEF1_0_reg                                            0xB80051C4
#define VO_HCSCCOEF1_1_reg                                            0xB80051C8
#define VO_HCSCCOEF1_2_reg                                            0xB80051CC
#define VO_HCSCCOEF1_3_reg                                            0xB80051D0
#define VO_HCSCCOEF1_4_reg                                            0xB80051D4
#define VO_HCSCCOEF1_5_reg                                            0xB80051D8
#define VO_HCSCCOEF1_6_reg                                            0xB80051DC
#define VO_HCSCCOEF1_7_reg                                            0xB80051E0
#define VO_HCSCCOEF1_8_reg                                            0xB80051E4
#define VO_HCSCCOEF1_9_reg                                            0xB80051E8
#define VO_HCSCCOEF1_10_reg                                           0xB80051EC
#define VO_HCSCCOEF1_11_reg                                           0xB80051F0
#define VO_HCSCCOEF1_12_reg                                           0xB80051F4
#define VO_HCSCCOEF1_13_reg                                           0xB80051F8
#define VO_HCSCCOEF1_14_reg                                           0xB80051FC
#define VO_HCSCCOEF1_15_reg                                           0xB8005200
#define VO_HCSCCOEF1_0_inst_addr                                      "0x0071"
#define VO_HCSCCOEF1_0_inst                                           0x0071
#define VO_HCSCCOEF1_1_inst_addr                                      "0x0072"
#define VO_HCSCCOEF1_1_inst                                           0x0072
#define VO_HCSCCOEF1_2_inst_addr                                      "0x0073"
#define VO_HCSCCOEF1_2_inst                                           0x0073
#define VO_HCSCCOEF1_3_inst_addr                                      "0x0074"
#define VO_HCSCCOEF1_3_inst                                           0x0074
#define VO_HCSCCOEF1_4_inst_addr                                      "0x0075"
#define VO_HCSCCOEF1_4_inst                                           0x0075
#define VO_HCSCCOEF1_5_inst_addr                                      "0x0076"
#define VO_HCSCCOEF1_5_inst                                           0x0076
#define VO_HCSCCOEF1_6_inst_addr                                      "0x0077"
#define VO_HCSCCOEF1_6_inst                                           0x0077
#define VO_HCSCCOEF1_7_inst_addr                                      "0x0078"
#define VO_HCSCCOEF1_7_inst                                           0x0078
#define VO_HCSCCOEF1_8_inst_addr                                      "0x0079"
#define VO_HCSCCOEF1_8_inst                                           0x0079
#define VO_HCSCCOEF1_9_inst_addr                                      "0x007A"
#define VO_HCSCCOEF1_9_inst                                           0x007A
#define VO_HCSCCOEF1_10_inst_addr                                     "0x007B"
#define VO_HCSCCOEF1_10_inst                                          0x007B
#define VO_HCSCCOEF1_11_inst_addr                                     "0x007C"
#define VO_HCSCCOEF1_11_inst                                          0x007C
#define VO_HCSCCOEF1_12_inst_addr                                     "0x007D"
#define VO_HCSCCOEF1_12_inst                                          0x007D
#define VO_HCSCCOEF1_13_inst_addr                                     "0x007E"
#define VO_HCSCCOEF1_13_inst                                          0x007E
#define VO_HCSCCOEF1_14_inst_addr                                     "0x007F"
#define VO_HCSCCOEF1_14_inst                                          0x007F
#define VO_HCSCCOEF1_15_inst_addr                                     "0x0080"
#define VO_HCSCCOEF1_15_inst                                          0x0080
#define VO_HCSCCOEF1_csccoef_shift                                    (0)
#define VO_HCSCCOEF1_csccoef_mask                                     (0x00003FFF)
#define VO_HCSCCOEF1_csccoef(data)                                    (0x00003FFF&(data))
#define VO_HCSCCOEF1_get_csccoef(data)                                (0x00003FFF&(data))

#define VO_V2WEAVE                                                    0x18005204
#define VO_V2WEAVE_reg_addr                                           "0xB8005204"
#define VO_V2WEAVE_reg                                                0xB8005204
#define VO_V2WEAVE_inst_addr                                          "0x0081"
#define VO_V2WEAVE_inst                                               0x0081
#define VO_V2WEAVE_weave_shift                                        (2)
#define VO_V2WEAVE_topfield_shift                                     (1)
#define VO_V2WEAVE_write_data_shift                                   (0)
#define VO_V2WEAVE_weave_mask                                         (0x00000004)
#define VO_V2WEAVE_topfield_mask                                      (0x00000002)
#define VO_V2WEAVE_write_data_mask                                    (0x00000001)
#define VO_V2WEAVE_weave(data)                                        (0x00000004&((data)<<2))
#define VO_V2WEAVE_topfield(data)                                     (0x00000002&((data)<<1))
#define VO_V2WEAVE_write_data(data)                                   (0x00000001&(data))
#define VO_V2WEAVE_get_weave(data)                                    ((0x00000004&(data))>>2)
#define VO_V2WEAVE_get_topfield(data)                                 ((0x00000002&(data))>>1)
#define VO_V2WEAVE_get_write_data(data)                               (0x00000001&(data))

#define VO_VSCCTL2                                                    0x18005208
#define VO_VSCCTL2_reg_addr                                           "0xB8005208"
#define VO_VSCCTL2_reg                                                0xB8005208
#define VO_VSCCTL2_inst_addr                                          "0x0082"
#define VO_VSCCTL2_inst                                               0x0082
#define VO_VSCCTL2_yen_shift                                          (4)
#define VO_VSCCTL2_yoddtype_shift                                     (3)
#define VO_VSCCTL2_cen_shift                                          (2)
#define VO_VSCCTL2_coddtype_shift                                     (1)
#define VO_VSCCTL2_write_data_shift                                   (0)
#define VO_VSCCTL2_yen_mask                                           (0x00000010)
#define VO_VSCCTL2_yoddtype_mask                                      (0x00000008)
#define VO_VSCCTL2_cen_mask                                           (0x00000004)
#define VO_VSCCTL2_coddtype_mask                                      (0x00000002)
#define VO_VSCCTL2_write_data_mask                                    (0x00000001)
#define VO_VSCCTL2_yen(data)                                          (0x00000010&((data)<<4))
#define VO_VSCCTL2_yoddtype(data)                                     (0x00000008&((data)<<3))
#define VO_VSCCTL2_cen(data)                                          (0x00000004&((data)<<2))
#define VO_VSCCTL2_coddtype(data)                                     (0x00000002&((data)<<1))
#define VO_VSCCTL2_write_data(data)                                   (0x00000001&(data))
#define VO_VSCCTL2_get_yen(data)                                      ((0x00000010&(data))>>4)
#define VO_VSCCTL2_get_yoddtype(data)                                 ((0x00000008&(data))>>3)
#define VO_VSCCTL2_get_cen(data)                                      ((0x00000004&(data))>>2)
#define VO_VSCCTL2_get_coddtype(data)                                 ((0x00000002&(data))>>1)
#define VO_VSCCTL2_get_write_data(data)                               (0x00000001&(data))

#define VO_VYSC2                                                      0x1800520C
#define VO_VYSC2_reg_addr                                             "0xB800520C"
#define VO_VYSC2_reg                                                  0xB800520C
#define VO_VYSC2_inst_addr                                            "0x0083"
#define VO_VYSC2_inst                                                 0x0083
#define VO_VYSC2_write_enable1_shift                                  (28)
#define VO_VYSC2_yonp_shift                                           (18)
#define VO_VYSC2_write_enable2_shift                                  (17)
#define VO_VYSC2_ydphs_shift                                          (0)
#define VO_VYSC2_write_enable1_mask                                   (0x10000000)
#define VO_VYSC2_yonp_mask                                            (0x0FFC0000)
#define VO_VYSC2_write_enable2_mask                                   (0x00020000)
#define VO_VYSC2_ydphs_mask                                           (0x0001FFFF)
#define VO_VYSC2_write_enable1(data)                                  (0x10000000&((data)<<28))
#define VO_VYSC2_yonp(data)                                           (0x0FFC0000&((data)<<18))
#define VO_VYSC2_write_enable2(data)                                  (0x00020000&((data)<<17))
#define VO_VYSC2_ydphs(data)                                          (0x0001FFFF&(data))
#define VO_VYSC2_get_write_enable1(data)                              ((0x10000000&(data))>>28)
#define VO_VYSC2_get_yonp(data)                                       ((0x0FFC0000&(data))>>18)
#define VO_VYSC2_get_write_enable2(data)                              ((0x00020000&(data))>>17)
#define VO_VYSC2_get_ydphs(data)                                      (0x0001FFFF&(data))

#define VO_VCSC2                                                      0x18005210
#define VO_VCSC2_reg_addr                                             "0xB8005210"
#define VO_VCSC2_reg                                                  0xB8005210
#define VO_VCSC2_inst_addr                                            "0x0084"
#define VO_VCSC2_inst                                                 0x0084
#define VO_VCSC2_write_enable1_shift                                  (28)
#define VO_VCSC2_conp_shift                                           (18)
#define VO_VCSC2_write_enable2_shift                                  (17)
#define VO_VCSC2_cdphs_shift                                          (0)
#define VO_VCSC2_write_enable1_mask                                   (0x10000000)
#define VO_VCSC2_conp_mask                                            (0x0FFC0000)
#define VO_VCSC2_write_enable2_mask                                   (0x00020000)
#define VO_VCSC2_cdphs_mask                                           (0x0001FFFF)
#define VO_VCSC2_write_enable1(data)                                  (0x10000000&((data)<<28))
#define VO_VCSC2_conp(data)                                           (0x0FFC0000&((data)<<18))
#define VO_VCSC2_write_enable2(data)                                  (0x00020000&((data)<<17))
#define VO_VCSC2_cdphs(data)                                          (0x0001FFFF&(data))
#define VO_VCSC2_get_write_enable1(data)                              ((0x10000000&(data))>>28)
#define VO_VCSC2_get_conp(data)                                       ((0x0FFC0000&(data))>>18)
#define VO_VCSC2_get_write_enable2(data)                              ((0x00020000&(data))>>17)
#define VO_VCSC2_get_cdphs(data)                                      (0x0001FFFF&(data))

#define VO_VYIPOS2                                                    0x18005214
#define VO_VYIPOS2_reg_addr                                           "0xB8005214"
#define VO_VYIPOS2_reg                                                0xB8005214
#define VO_VYIPOS2_inst_addr                                          "0x0085"
#define VO_VYIPOS2_inst                                               0x0085
#define VO_VYIPOS2_init_offset_shift                                  (14)
#define VO_VYIPOS2_init_phase_shift                                   (0)
#define VO_VYIPOS2_init_offset_mask                                   (0x00FFC000)
#define VO_VYIPOS2_init_phase_mask                                    (0x00003FFF)
#define VO_VYIPOS2_init_offset(data)                                  (0x00FFC000&((data)<<14))
#define VO_VYIPOS2_init_phase(data)                                   (0x00003FFF&(data))
#define VO_VYIPOS2_get_init_offset(data)                              ((0x00FFC000&(data))>>14)
#define VO_VYIPOS2_get_init_phase(data)                               (0x00003FFF&(data))

#define VO_VYEPOS2                                                    0x18005218
#define VO_VYEPOS2_reg_addr                                           "0xB8005218"
#define VO_VYEPOS2_reg                                                0xB8005218
#define VO_VYEPOS2_inst_addr                                          "0x0086"
#define VO_VYEPOS2_inst                                               0x0086
#define VO_VYEPOS2_endline_shift                                      (0)
#define VO_VYEPOS2_endline_mask                                       (0x000003FF)
#define VO_VYEPOS2_endline(data)                                      (0x000003FF&(data))
#define VO_VYEPOS2_get_endline(data)                                  (0x000003FF&(data))

#define VO_VCIPOS2                                                    0x1800521C
#define VO_VCIPOS2_reg_addr                                           "0xB800521C"
#define VO_VCIPOS2_reg                                                0xB800521C
#define VO_VCIPOS2_inst_addr                                          "0x0087"
#define VO_VCIPOS2_inst                                               0x0087
#define VO_VCIPOS2_init_offset_shift                                  (14)
#define VO_VCIPOS2_init_phase_shift                                   (0)
#define VO_VCIPOS2_init_offset_mask                                   (0x00FFC000)
#define VO_VCIPOS2_init_phase_mask                                    (0x00003FFF)
#define VO_VCIPOS2_init_offset(data)                                  (0x00FFC000&((data)<<14))
#define VO_VCIPOS2_init_phase(data)                                   (0x00003FFF&(data))
#define VO_VCIPOS2_get_init_offset(data)                              ((0x00FFC000&(data))>>14)
#define VO_VCIPOS2_get_init_phase(data)                               (0x00003FFF&(data))

#define VO_VCEPOS2                                                    0x18005220
#define VO_VCEPOS2_reg_addr                                           "0xB8005220"
#define VO_VCEPOS2_reg                                                0xB8005220
#define VO_VCEPOS2_inst_addr                                          "0x0088"
#define VO_VCEPOS2_inst                                               0x0088
#define VO_VCEPOS2_endline_shift                                      (0)
#define VO_VCEPOS2_endline_mask                                       (0x000003FF)
#define VO_VCEPOS2_endline(data)                                      (0x000003FF&(data))
#define VO_VCEPOS2_get_endline(data)                                  (0x000003FF&(data))

#define VO_VYSCCOEF2_0                                                0x18005224
#define VO_VYSCCOEF2_1                                                0x18005228
#define VO_VYSCCOEF2_2                                                0x1800522C
#define VO_VYSCCOEF2_3                                                0x18005230
#define VO_VYSCCOEF2_4                                                0x18005234
#define VO_VYSCCOEF2_5                                                0x18005238
#define VO_VYSCCOEF2_6                                                0x1800523C
#define VO_VYSCCOEF2_7                                                0x18005240
#define VO_VYSCCOEF2_0_reg_addr                                       "0xB8005224"
#define VO_VYSCCOEF2_1_reg_addr                                       "0xB8005228"
#define VO_VYSCCOEF2_2_reg_addr                                       "0xB800522C"
#define VO_VYSCCOEF2_3_reg_addr                                       "0xB8005230"
#define VO_VYSCCOEF2_4_reg_addr                                       "0xB8005234"
#define VO_VYSCCOEF2_5_reg_addr                                       "0xB8005238"
#define VO_VYSCCOEF2_6_reg_addr                                       "0xB800523C"
#define VO_VYSCCOEF2_7_reg_addr                                       "0xB8005240"
#define VO_VYSCCOEF2_0_reg                                            0xB8005224
#define VO_VYSCCOEF2_1_reg                                            0xB8005228
#define VO_VYSCCOEF2_2_reg                                            0xB800522C
#define VO_VYSCCOEF2_3_reg                                            0xB8005230
#define VO_VYSCCOEF2_4_reg                                            0xB8005234
#define VO_VYSCCOEF2_5_reg                                            0xB8005238
#define VO_VYSCCOEF2_6_reg                                            0xB800523C
#define VO_VYSCCOEF2_7_reg                                            0xB8005240
#define VO_VYSCCOEF2_0_inst_addr                                      "0x0089"
#define VO_VYSCCOEF2_0_inst                                           0x0089
#define VO_VYSCCOEF2_1_inst_addr                                      "0x008A"
#define VO_VYSCCOEF2_1_inst                                           0x008A
#define VO_VYSCCOEF2_2_inst_addr                                      "0x008B"
#define VO_VYSCCOEF2_2_inst                                           0x008B
#define VO_VYSCCOEF2_3_inst_addr                                      "0x008C"
#define VO_VYSCCOEF2_3_inst                                           0x008C
#define VO_VYSCCOEF2_4_inst_addr                                      "0x008D"
#define VO_VYSCCOEF2_4_inst                                           0x008D
#define VO_VYSCCOEF2_5_inst_addr                                      "0x008E"
#define VO_VYSCCOEF2_5_inst                                           0x008E
#define VO_VYSCCOEF2_6_inst_addr                                      "0x008F"
#define VO_VYSCCOEF2_6_inst                                           0x008F
#define VO_VYSCCOEF2_7_inst_addr                                      "0x0090"
#define VO_VYSCCOEF2_7_inst                                           0x0090
#define VO_VYSCCOEF2_ysccoef_shift                                    (0)
#define VO_VYSCCOEF2_ysccoef_mask                                     (0x00003FFF)
#define VO_VYSCCOEF2_ysccoef(data)                                    (0x00003FFF&(data))
#define VO_VYSCCOEF2_get_ysccoef(data)                                (0x00003FFF&(data))

#define VO_VCSCCOEF2_0                                                0x18005244
#define VO_VCSCCOEF2_1                                                0x18005248
#define VO_VCSCCOEF2_2                                                0x1800524C
#define VO_VCSCCOEF2_3                                                0x18005250
#define VO_VCSCCOEF2_4                                                0x18005254
#define VO_VCSCCOEF2_5                                                0x18005258
#define VO_VCSCCOEF2_6                                                0x1800525C
#define VO_VCSCCOEF2_7                                                0x18005260
#define VO_VCSCCOEF2_0_reg_addr                                       "0xB8005244"
#define VO_VCSCCOEF2_1_reg_addr                                       "0xB8005248"
#define VO_VCSCCOEF2_2_reg_addr                                       "0xB800524C"
#define VO_VCSCCOEF2_3_reg_addr                                       "0xB8005250"
#define VO_VCSCCOEF2_4_reg_addr                                       "0xB8005254"
#define VO_VCSCCOEF2_5_reg_addr                                       "0xB8005258"
#define VO_VCSCCOEF2_6_reg_addr                                       "0xB800525C"
#define VO_VCSCCOEF2_7_reg_addr                                       "0xB8005260"
#define VO_VCSCCOEF2_0_reg                                            0xB8005244
#define VO_VCSCCOEF2_1_reg                                            0xB8005248
#define VO_VCSCCOEF2_2_reg                                            0xB800524C
#define VO_VCSCCOEF2_3_reg                                            0xB8005250
#define VO_VCSCCOEF2_4_reg                                            0xB8005254
#define VO_VCSCCOEF2_5_reg                                            0xB8005258
#define VO_VCSCCOEF2_6_reg                                            0xB800525C
#define VO_VCSCCOEF2_7_reg                                            0xB8005260
#define VO_VCSCCOEF2_0_inst_addr                                      "0x0091"
#define VO_VCSCCOEF2_0_inst                                           0x0091
#define VO_VCSCCOEF2_1_inst_addr                                      "0x0092"
#define VO_VCSCCOEF2_1_inst                                           0x0092
#define VO_VCSCCOEF2_2_inst_addr                                      "0x0093"
#define VO_VCSCCOEF2_2_inst                                           0x0093
#define VO_VCSCCOEF2_3_inst_addr                                      "0x0094"
#define VO_VCSCCOEF2_3_inst                                           0x0094
#define VO_VCSCCOEF2_4_inst_addr                                      "0x0095"
#define VO_VCSCCOEF2_4_inst                                           0x0095
#define VO_VCSCCOEF2_5_inst_addr                                      "0x0096"
#define VO_VCSCCOEF2_5_inst                                           0x0096
#define VO_VCSCCOEF2_6_inst_addr                                      "0x0097"
#define VO_VCSCCOEF2_6_inst                                           0x0097
#define VO_VCSCCOEF2_7_inst_addr                                      "0x0098"
#define VO_VCSCCOEF2_7_inst                                           0x0098
#define VO_VCSCCOEF2_csccoef_shift                                    (0)
#define VO_VCSCCOEF2_csccoef_mask                                     (0x00003FFF)
#define VO_VCSCCOEF2_csccoef(data)                                    (0x00003FFF&(data))
#define VO_VCSCCOEF2_get_csccoef(data)                                (0x00003FFF&(data))

#define VO_HSCCTL2                                                    0x18005264
#define VO_HSCCTL2_reg_addr                                           "0xB8005264"
#define VO_HSCCTL2_reg                                                0xB8005264
#define VO_HSCCTL2_inst_addr                                          "0x0099"
#define VO_HSCCTL2_inst                                               0x0099
#define VO_HSCCTL2_yen_shift                                          (4)
#define VO_HSCCTL2_yoddtype_shift                                     (3)
#define VO_HSCCTL2_cen_shift                                          (2)
#define VO_HSCCTL2_coddtype_shift                                     (1)
#define VO_HSCCTL2_write_data_shift                                   (0)
#define VO_HSCCTL2_yen_mask                                           (0x00000010)
#define VO_HSCCTL2_yoddtype_mask                                      (0x00000008)
#define VO_HSCCTL2_cen_mask                                           (0x00000004)
#define VO_HSCCTL2_coddtype_mask                                      (0x00000002)
#define VO_HSCCTL2_write_data_mask                                    (0x00000001)
#define VO_HSCCTL2_yen(data)                                          (0x00000010&((data)<<4))
#define VO_HSCCTL2_yoddtype(data)                                     (0x00000008&((data)<<3))
#define VO_HSCCTL2_cen(data)                                          (0x00000004&((data)<<2))
#define VO_HSCCTL2_coddtype(data)                                     (0x00000002&((data)<<1))
#define VO_HSCCTL2_write_data(data)                                   (0x00000001&(data))
#define VO_HSCCTL2_get_yen(data)                                      ((0x00000010&(data))>>4)
#define VO_HSCCTL2_get_yoddtype(data)                                 ((0x00000008&(data))>>3)
#define VO_HSCCTL2_get_cen(data)                                      ((0x00000004&(data))>>2)
#define VO_HSCCTL2_get_coddtype(data)                                 ((0x00000002&(data))>>1)
#define VO_HSCCTL2_get_write_data(data)                               (0x00000001&(data))

#define VO_HYSC2                                                      0x18005268
#define VO_HYSC2_reg_addr                                             "0xB8005268"
#define VO_HYSC2_reg                                                  0xB8005268
#define VO_HYSC2_inst_addr                                            "0x009A"
#define VO_HYSC2_inst                                                 0x009A
#define VO_HYSC2_write_enable1_shift                                  (29)
#define VO_HYSC2_yonp_shift                                           (18)
#define VO_HYSC2_write_enable2_shift                                  (17)
#define VO_HYSC2_ydphs_shift                                          (0)
#define VO_HYSC2_write_enable1_mask                                   (0x20000000)
#define VO_HYSC2_yonp_mask                                            (0x1FFC0000)
#define VO_HYSC2_write_enable2_mask                                   (0x00020000)
#define VO_HYSC2_ydphs_mask                                           (0x0001FFFF)
#define VO_HYSC2_write_enable1(data)                                  (0x20000000&((data)<<29))
#define VO_HYSC2_yonp(data)                                           (0x1FFC0000&((data)<<18))
#define VO_HYSC2_write_enable2(data)                                  (0x00020000&((data)<<17))
#define VO_HYSC2_ydphs(data)                                          (0x0001FFFF&(data))
#define VO_HYSC2_get_write_enable1(data)                              ((0x20000000&(data))>>29)
#define VO_HYSC2_get_yonp(data)                                       ((0x1FFC0000&(data))>>18)
#define VO_HYSC2_get_write_enable2(data)                              ((0x00020000&(data))>>17)
#define VO_HYSC2_get_ydphs(data)                                      (0x0001FFFF&(data))

#define VO_HYIPOS2                                                    0x1800526C
#define VO_HYIPOS2_reg_addr                                           "0xB800526C"
#define VO_HYIPOS2_reg                                                0xB800526C
#define VO_HYIPOS2_inst_addr                                          "0x009B"
#define VO_HYIPOS2_inst                                               0x009B
#define VO_HYIPOS2_init_phase_shift                                   (0)
#define VO_HYIPOS2_init_phase_mask                                    (0x00003FFF)
#define VO_HYIPOS2_init_phase(data)                                   (0x00003FFF&(data))
#define VO_HYIPOS2_get_init_phase(data)                               (0x00003FFF&(data))

#define VO_HYEPOS2                                                    0x18005270
#define VO_HYEPOS2_reg_addr                                           "0xB8005270"
#define VO_HYEPOS2_reg                                                0xB8005270
#define VO_HYEPOS2_inst_addr                                          "0x009C"
#define VO_HYEPOS2_inst                                               0x009C
#define VO_HYEPOS2_begin_point_shift                                  (11)
#define VO_HYEPOS2_end_point_shift                                    (0)
#define VO_HYEPOS2_begin_point_mask                                   (0x003FF800)
#define VO_HYEPOS2_end_point_mask                                     (0x000007FF)
#define VO_HYEPOS2_begin_point(data)                                  (0x003FF800&((data)<<11))
#define VO_HYEPOS2_end_point(data)                                    (0x000007FF&(data))
#define VO_HYEPOS2_get_begin_point(data)                              ((0x003FF800&(data))>>11)
#define VO_HYEPOS2_get_end_point(data)                                (0x000007FF&(data))

#define VO_HYWIDTH2                                                   0x18005274
#define VO_HYWIDTH2_reg_addr                                          "0xB8005274"
#define VO_HYWIDTH2_reg                                               0xB8005274
#define VO_HYWIDTH2_inst_addr                                         "0x009D"
#define VO_HYWIDTH2_inst                                              0x009D
#define VO_HYWIDTH2_shift_shift                                       (11)
#define VO_HYWIDTH2_width_shift                                       (0)
#define VO_HYWIDTH2_shift_mask                                        (0x0000F800)
#define VO_HYWIDTH2_width_mask                                        (0x000007FF)
#define VO_HYWIDTH2_shift(data)                                       (0x0000F800&((data)<<11))
#define VO_HYWIDTH2_width(data)                                       (0x000007FF&(data))
#define VO_HYWIDTH2_get_shift(data)                                   ((0x0000F800&(data))>>11)
#define VO_HYWIDTH2_get_width(data)                                   (0x000007FF&(data))

#define VO_HCSC2                                                      0x18005278
#define VO_HCSC2_reg_addr                                             "0xB8005278"
#define VO_HCSC2_reg                                                  0xB8005278
#define VO_HCSC2_inst_addr                                            "0x009E"
#define VO_HCSC2_inst                                                 0x009E
#define VO_HCSC2_write_enable1_shift                                  (29)
#define VO_HCSC2_conp_shift                                           (18)
#define VO_HCSC2_write_enable2_shift                                  (17)
#define VO_HCSC2_cdphs_shift                                          (0)
#define VO_HCSC2_write_enable1_mask                                   (0x20000000)
#define VO_HCSC2_conp_mask                                            (0x1FFC0000)
#define VO_HCSC2_write_enable2_mask                                   (0x00020000)
#define VO_HCSC2_cdphs_mask                                           (0x0001FFFF)
#define VO_HCSC2_write_enable1(data)                                  (0x20000000&((data)<<29))
#define VO_HCSC2_conp(data)                                           (0x1FFC0000&((data)<<18))
#define VO_HCSC2_write_enable2(data)                                  (0x00020000&((data)<<17))
#define VO_HCSC2_cdphs(data)                                          (0x0001FFFF&(data))
#define VO_HCSC2_get_write_enable1(data)                              ((0x20000000&(data))>>29)
#define VO_HCSC2_get_conp(data)                                       ((0x1FFC0000&(data))>>18)
#define VO_HCSC2_get_write_enable2(data)                              ((0x00020000&(data))>>17)
#define VO_HCSC2_get_cdphs(data)                                      (0x0001FFFF&(data))

#define VO_HCIPOS2                                                    0x1800527C
#define VO_HCIPOS2_reg_addr                                           "0xB800527C"
#define VO_HCIPOS2_reg                                                0xB800527C
#define VO_HCIPOS2_inst_addr                                          "0x009F"
#define VO_HCIPOS2_inst                                               0x009F
#define VO_HCIPOS2_init_phase_shift                                   (0)
#define VO_HCIPOS2_init_phase_mask                                    (0x00003FFF)
#define VO_HCIPOS2_init_phase(data)                                   (0x00003FFF&(data))
#define VO_HCIPOS2_get_init_phase(data)                               (0x00003FFF&(data))

#define VO_HCEPOS2                                                    0x18005280
#define VO_HCEPOS2_reg_addr                                           "0xB8005280"
#define VO_HCEPOS2_reg                                                0xB8005280
#define VO_HCEPOS2_inst_addr                                          "0x00A0"
#define VO_HCEPOS2_inst                                               0x00A0
#define VO_HCEPOS2_begin_point_shift                                  (11)
#define VO_HCEPOS2_end_point_shift                                    (0)
#define VO_HCEPOS2_begin_point_mask                                   (0x003FF800)
#define VO_HCEPOS2_end_point_mask                                     (0x000007FF)
#define VO_HCEPOS2_begin_point(data)                                  (0x003FF800&((data)<<11))
#define VO_HCEPOS2_end_point(data)                                    (0x000007FF&(data))
#define VO_HCEPOS2_get_begin_point(data)                              ((0x003FF800&(data))>>11)
#define VO_HCEPOS2_get_end_point(data)                                (0x000007FF&(data))

#define VO_HCWIDTH2                                                   0x18005284
#define VO_HCWIDTH2_reg_addr                                          "0xB8005284"
#define VO_HCWIDTH2_reg                                               0xB8005284
#define VO_HCWIDTH2_inst_addr                                         "0x00A1"
#define VO_HCWIDTH2_inst                                              0x00A1
#define VO_HCWIDTH2_shift_shift                                       (11)
#define VO_HCWIDTH2_width_shift                                       (0)
#define VO_HCWIDTH2_shift_mask                                        (0x0000F800)
#define VO_HCWIDTH2_width_mask                                        (0x000007FF)
#define VO_HCWIDTH2_shift(data)                                       (0x0000F800&((data)<<11))
#define VO_HCWIDTH2_width(data)                                       (0x000007FF&(data))
#define VO_HCWIDTH2_get_shift(data)                                   ((0x0000F800&(data))>>11)
#define VO_HCWIDTH2_get_width(data)                                   (0x000007FF&(data))

#define VO_HYSCCOEF2_0                                                0x18005288
#define VO_HYSCCOEF2_1                                                0x1800528C
#define VO_HYSCCOEF2_2                                                0x18005290
#define VO_HYSCCOEF2_3                                                0x18005294
#define VO_HYSCCOEF2_4                                                0x18005298
#define VO_HYSCCOEF2_5                                                0x1800529C
#define VO_HYSCCOEF2_6                                                0x180052A0
#define VO_HYSCCOEF2_7                                                0x180052A4
#define VO_HYSCCOEF2_8                                                0x180052A8
#define VO_HYSCCOEF2_9                                                0x180052AC
#define VO_HYSCCOEF2_10                                               0x180052B0
#define VO_HYSCCOEF2_11                                               0x180052B4
#define VO_HYSCCOEF2_12                                               0x180052B8
#define VO_HYSCCOEF2_13                                               0x180052BC
#define VO_HYSCCOEF2_14                                               0x180052C0
#define VO_HYSCCOEF2_15                                               0x180052C4
#define VO_HYSCCOEF2_16                                               0x180052C8
#define VO_HYSCCOEF2_17                                               0x180052CC
#define VO_HYSCCOEF2_18                                               0x180052D0
#define VO_HYSCCOEF2_19                                               0x180052D4
#define VO_HYSCCOEF2_20                                               0x180052D8
#define VO_HYSCCOEF2_21                                               0x180052DC
#define VO_HYSCCOEF2_22                                               0x180052E0
#define VO_HYSCCOEF2_23                                               0x180052E4
#define VO_HYSCCOEF2_24                                               0x180052E8
#define VO_HYSCCOEF2_25                                               0x180052EC
#define VO_HYSCCOEF2_26                                               0x180052F0
#define VO_HYSCCOEF2_27                                               0x180052F4
#define VO_HYSCCOEF2_28                                               0x180052F8
#define VO_HYSCCOEF2_29                                               0x180052FC
#define VO_HYSCCOEF2_30                                               0x18005300
#define VO_HYSCCOEF2_31                                               0x18005304
#define VO_HYSCCOEF2_0_reg_addr                                       "0xB8005288"
#define VO_HYSCCOEF2_1_reg_addr                                       "0xB800528C"
#define VO_HYSCCOEF2_2_reg_addr                                       "0xB8005290"
#define VO_HYSCCOEF2_3_reg_addr                                       "0xB8005294"
#define VO_HYSCCOEF2_4_reg_addr                                       "0xB8005298"
#define VO_HYSCCOEF2_5_reg_addr                                       "0xB800529C"
#define VO_HYSCCOEF2_6_reg_addr                                       "0xB80052A0"
#define VO_HYSCCOEF2_7_reg_addr                                       "0xB80052A4"
#define VO_HYSCCOEF2_8_reg_addr                                       "0xB80052A8"
#define VO_HYSCCOEF2_9_reg_addr                                       "0xB80052AC"
#define VO_HYSCCOEF2_10_reg_addr                                      "0xB80052B0"
#define VO_HYSCCOEF2_11_reg_addr                                      "0xB80052B4"
#define VO_HYSCCOEF2_12_reg_addr                                      "0xB80052B8"
#define VO_HYSCCOEF2_13_reg_addr                                      "0xB80052BC"
#define VO_HYSCCOEF2_14_reg_addr                                      "0xB80052C0"
#define VO_HYSCCOEF2_15_reg_addr                                      "0xB80052C4"
#define VO_HYSCCOEF2_16_reg_addr                                      "0xB80052C8"
#define VO_HYSCCOEF2_17_reg_addr                                      "0xB80052CC"
#define VO_HYSCCOEF2_18_reg_addr                                      "0xB80052D0"
#define VO_HYSCCOEF2_19_reg_addr                                      "0xB80052D4"
#define VO_HYSCCOEF2_20_reg_addr                                      "0xB80052D8"
#define VO_HYSCCOEF2_21_reg_addr                                      "0xB80052DC"
#define VO_HYSCCOEF2_22_reg_addr                                      "0xB80052E0"
#define VO_HYSCCOEF2_23_reg_addr                                      "0xB80052E4"
#define VO_HYSCCOEF2_24_reg_addr                                      "0xB80052E8"
#define VO_HYSCCOEF2_25_reg_addr                                      "0xB80052EC"
#define VO_HYSCCOEF2_26_reg_addr                                      "0xB80052F0"
#define VO_HYSCCOEF2_27_reg_addr                                      "0xB80052F4"
#define VO_HYSCCOEF2_28_reg_addr                                      "0xB80052F8"
#define VO_HYSCCOEF2_29_reg_addr                                      "0xB80052FC"
#define VO_HYSCCOEF2_30_reg_addr                                      "0xB8005300"
#define VO_HYSCCOEF2_31_reg_addr                                      "0xB8005304"
#define VO_HYSCCOEF2_0_reg                                            0xB8005288
#define VO_HYSCCOEF2_1_reg                                            0xB800528C
#define VO_HYSCCOEF2_2_reg                                            0xB8005290
#define VO_HYSCCOEF2_3_reg                                            0xB8005294
#define VO_HYSCCOEF2_4_reg                                            0xB8005298
#define VO_HYSCCOEF2_5_reg                                            0xB800529C
#define VO_HYSCCOEF2_6_reg                                            0xB80052A0
#define VO_HYSCCOEF2_7_reg                                            0xB80052A4
#define VO_HYSCCOEF2_8_reg                                            0xB80052A8
#define VO_HYSCCOEF2_9_reg                                            0xB80052AC
#define VO_HYSCCOEF2_10_reg                                           0xB80052B0
#define VO_HYSCCOEF2_11_reg                                           0xB80052B4
#define VO_HYSCCOEF2_12_reg                                           0xB80052B8
#define VO_HYSCCOEF2_13_reg                                           0xB80052BC
#define VO_HYSCCOEF2_14_reg                                           0xB80052C0
#define VO_HYSCCOEF2_15_reg                                           0xB80052C4
#define VO_HYSCCOEF2_16_reg                                           0xB80052C8
#define VO_HYSCCOEF2_17_reg                                           0xB80052CC
#define VO_HYSCCOEF2_18_reg                                           0xB80052D0
#define VO_HYSCCOEF2_19_reg                                           0xB80052D4
#define VO_HYSCCOEF2_20_reg                                           0xB80052D8
#define VO_HYSCCOEF2_21_reg                                           0xB80052DC
#define VO_HYSCCOEF2_22_reg                                           0xB80052E0
#define VO_HYSCCOEF2_23_reg                                           0xB80052E4
#define VO_HYSCCOEF2_24_reg                                           0xB80052E8
#define VO_HYSCCOEF2_25_reg                                           0xB80052EC
#define VO_HYSCCOEF2_26_reg                                           0xB80052F0
#define VO_HYSCCOEF2_27_reg                                           0xB80052F4
#define VO_HYSCCOEF2_28_reg                                           0xB80052F8
#define VO_HYSCCOEF2_29_reg                                           0xB80052FC
#define VO_HYSCCOEF2_30_reg                                           0xB8005300
#define VO_HYSCCOEF2_31_reg                                           0xB8005304
#define VO_HYSCCOEF2_0_inst_addr                                      "0x00A2"
#define VO_HYSCCOEF2_0_inst                                           0x00A2
#define VO_HYSCCOEF2_1_inst_addr                                      "0x00A3"
#define VO_HYSCCOEF2_1_inst                                           0x00A3
#define VO_HYSCCOEF2_2_inst_addr                                      "0x00A4"
#define VO_HYSCCOEF2_2_inst                                           0x00A4
#define VO_HYSCCOEF2_3_inst_addr                                      "0x00A5"
#define VO_HYSCCOEF2_3_inst                                           0x00A5
#define VO_HYSCCOEF2_4_inst_addr                                      "0x00A6"
#define VO_HYSCCOEF2_4_inst                                           0x00A6
#define VO_HYSCCOEF2_5_inst_addr                                      "0x00A7"
#define VO_HYSCCOEF2_5_inst                                           0x00A7
#define VO_HYSCCOEF2_6_inst_addr                                      "0x00A8"
#define VO_HYSCCOEF2_6_inst                                           0x00A8
#define VO_HYSCCOEF2_7_inst_addr                                      "0x00A9"
#define VO_HYSCCOEF2_7_inst                                           0x00A9
#define VO_HYSCCOEF2_8_inst_addr                                      "0x00AA"
#define VO_HYSCCOEF2_8_inst                                           0x00AA
#define VO_HYSCCOEF2_9_inst_addr                                      "0x00AB"
#define VO_HYSCCOEF2_9_inst                                           0x00AB
#define VO_HYSCCOEF2_10_inst_addr                                     "0x00AC"
#define VO_HYSCCOEF2_10_inst                                          0x00AC
#define VO_HYSCCOEF2_11_inst_addr                                     "0x00AD"
#define VO_HYSCCOEF2_11_inst                                          0x00AD
#define VO_HYSCCOEF2_12_inst_addr                                     "0x00AE"
#define VO_HYSCCOEF2_12_inst                                          0x00AE
#define VO_HYSCCOEF2_13_inst_addr                                     "0x00AF"
#define VO_HYSCCOEF2_13_inst                                          0x00AF
#define VO_HYSCCOEF2_14_inst_addr                                     "0x00B0"
#define VO_HYSCCOEF2_14_inst                                          0x00B0
#define VO_HYSCCOEF2_15_inst_addr                                     "0x00B1"
#define VO_HYSCCOEF2_15_inst                                          0x00B1
#define VO_HYSCCOEF2_16_inst_addr                                     "0x00B2"
#define VO_HYSCCOEF2_16_inst                                          0x00B2
#define VO_HYSCCOEF2_17_inst_addr                                     "0x00B3"
#define VO_HYSCCOEF2_17_inst                                          0x00B3
#define VO_HYSCCOEF2_18_inst_addr                                     "0x00B4"
#define VO_HYSCCOEF2_18_inst                                          0x00B4
#define VO_HYSCCOEF2_19_inst_addr                                     "0x00B5"
#define VO_HYSCCOEF2_19_inst                                          0x00B5
#define VO_HYSCCOEF2_20_inst_addr                                     "0x00B6"
#define VO_HYSCCOEF2_20_inst                                          0x00B6
#define VO_HYSCCOEF2_21_inst_addr                                     "0x00B7"
#define VO_HYSCCOEF2_21_inst                                          0x00B7
#define VO_HYSCCOEF2_22_inst_addr                                     "0x00B8"
#define VO_HYSCCOEF2_22_inst                                          0x00B8
#define VO_HYSCCOEF2_23_inst_addr                                     "0x00B9"
#define VO_HYSCCOEF2_23_inst                                          0x00B9
#define VO_HYSCCOEF2_24_inst_addr                                     "0x00BA"
#define VO_HYSCCOEF2_24_inst                                          0x00BA
#define VO_HYSCCOEF2_25_inst_addr                                     "0x00BB"
#define VO_HYSCCOEF2_25_inst                                          0x00BB
#define VO_HYSCCOEF2_26_inst_addr                                     "0x00BC"
#define VO_HYSCCOEF2_26_inst                                          0x00BC
#define VO_HYSCCOEF2_27_inst_addr                                     "0x00BD"
#define VO_HYSCCOEF2_27_inst                                          0x00BD
#define VO_HYSCCOEF2_28_inst_addr                                     "0x00BE"
#define VO_HYSCCOEF2_28_inst                                          0x00BE
#define VO_HYSCCOEF2_29_inst_addr                                     "0x00BF"
#define VO_HYSCCOEF2_29_inst                                          0x00BF
#define VO_HYSCCOEF2_30_inst_addr                                     "0x00C0"
#define VO_HYSCCOEF2_30_inst                                          0x00C0
#define VO_HYSCCOEF2_31_inst_addr                                     "0x00C1"
#define VO_HYSCCOEF2_31_inst                                          0x00C1
#define VO_HYSCCOEF2_ysccoef_shift                                    (0)
#define VO_HYSCCOEF2_ysccoef_mask                                     (0x00003FFF)
#define VO_HYSCCOEF2_ysccoef(data)                                    (0x00003FFF&(data))
#define VO_HYSCCOEF2_get_ysccoef(data)                                (0x00003FFF&(data))

#define VO_HCSCCOEF2_0                                                0x18005308
#define VO_HCSCCOEF2_1                                                0x1800530C
#define VO_HCSCCOEF2_2                                                0x18005310
#define VO_HCSCCOEF2_3                                                0x18005314
#define VO_HCSCCOEF2_4                                                0x18005318
#define VO_HCSCCOEF2_5                                                0x1800531C
#define VO_HCSCCOEF2_6                                                0x18005320
#define VO_HCSCCOEF2_7                                                0x18005324
#define VO_HCSCCOEF2_8                                                0x18005328
#define VO_HCSCCOEF2_9                                                0x1800532C
#define VO_HCSCCOEF2_10                                               0x18005330
#define VO_HCSCCOEF2_11                                               0x18005334
#define VO_HCSCCOEF2_12                                               0x18005338
#define VO_HCSCCOEF2_13                                               0x1800533C
#define VO_HCSCCOEF2_14                                               0x18005340
#define VO_HCSCCOEF2_15                                               0x18005344
#define VO_HCSCCOEF2_0_reg_addr                                       "0xB8005308"
#define VO_HCSCCOEF2_1_reg_addr                                       "0xB800530C"
#define VO_HCSCCOEF2_2_reg_addr                                       "0xB8005310"
#define VO_HCSCCOEF2_3_reg_addr                                       "0xB8005314"
#define VO_HCSCCOEF2_4_reg_addr                                       "0xB8005318"
#define VO_HCSCCOEF2_5_reg_addr                                       "0xB800531C"
#define VO_HCSCCOEF2_6_reg_addr                                       "0xB8005320"
#define VO_HCSCCOEF2_7_reg_addr                                       "0xB8005324"
#define VO_HCSCCOEF2_8_reg_addr                                       "0xB8005328"
#define VO_HCSCCOEF2_9_reg_addr                                       "0xB800532C"
#define VO_HCSCCOEF2_10_reg_addr                                      "0xB8005330"
#define VO_HCSCCOEF2_11_reg_addr                                      "0xB8005334"
#define VO_HCSCCOEF2_12_reg_addr                                      "0xB8005338"
#define VO_HCSCCOEF2_13_reg_addr                                      "0xB800533C"
#define VO_HCSCCOEF2_14_reg_addr                                      "0xB8005340"
#define VO_HCSCCOEF2_15_reg_addr                                      "0xB8005344"
#define VO_HCSCCOEF2_0_reg                                            0xB8005308
#define VO_HCSCCOEF2_1_reg                                            0xB800530C
#define VO_HCSCCOEF2_2_reg                                            0xB8005310
#define VO_HCSCCOEF2_3_reg                                            0xB8005314
#define VO_HCSCCOEF2_4_reg                                            0xB8005318
#define VO_HCSCCOEF2_5_reg                                            0xB800531C
#define VO_HCSCCOEF2_6_reg                                            0xB8005320
#define VO_HCSCCOEF2_7_reg                                            0xB8005324
#define VO_HCSCCOEF2_8_reg                                            0xB8005328
#define VO_HCSCCOEF2_9_reg                                            0xB800532C
#define VO_HCSCCOEF2_10_reg                                           0xB8005330
#define VO_HCSCCOEF2_11_reg                                           0xB8005334
#define VO_HCSCCOEF2_12_reg                                           0xB8005338
#define VO_HCSCCOEF2_13_reg                                           0xB800533C
#define VO_HCSCCOEF2_14_reg                                           0xB8005340
#define VO_HCSCCOEF2_15_reg                                           0xB8005344
#define VO_HCSCCOEF2_0_inst_addr                                      "0x00C2"
#define VO_HCSCCOEF2_0_inst                                           0x00C2
#define VO_HCSCCOEF2_1_inst_addr                                      "0x00C3"
#define VO_HCSCCOEF2_1_inst                                           0x00C3
#define VO_HCSCCOEF2_2_inst_addr                                      "0x00C4"
#define VO_HCSCCOEF2_2_inst                                           0x00C4
#define VO_HCSCCOEF2_3_inst_addr                                      "0x00C5"
#define VO_HCSCCOEF2_3_inst                                           0x00C5
#define VO_HCSCCOEF2_4_inst_addr                                      "0x00C6"
#define VO_HCSCCOEF2_4_inst                                           0x00C6
#define VO_HCSCCOEF2_5_inst_addr                                      "0x00C7"
#define VO_HCSCCOEF2_5_inst                                           0x00C7
#define VO_HCSCCOEF2_6_inst_addr                                      "0x00C8"
#define VO_HCSCCOEF2_6_inst                                           0x00C8
#define VO_HCSCCOEF2_7_inst_addr                                      "0x00C9"
#define VO_HCSCCOEF2_7_inst                                           0x00C9
#define VO_HCSCCOEF2_8_inst_addr                                      "0x00CA"
#define VO_HCSCCOEF2_8_inst                                           0x00CA
#define VO_HCSCCOEF2_9_inst_addr                                      "0x00CB"
#define VO_HCSCCOEF2_9_inst                                           0x00CB
#define VO_HCSCCOEF2_10_inst_addr                                     "0x00CC"
#define VO_HCSCCOEF2_10_inst                                          0x00CC
#define VO_HCSCCOEF2_11_inst_addr                                     "0x00CD"
#define VO_HCSCCOEF2_11_inst                                          0x00CD
#define VO_HCSCCOEF2_12_inst_addr                                     "0x00CE"
#define VO_HCSCCOEF2_12_inst                                          0x00CE
#define VO_HCSCCOEF2_13_inst_addr                                     "0x00CF"
#define VO_HCSCCOEF2_13_inst                                          0x00CF
#define VO_HCSCCOEF2_14_inst_addr                                     "0x00D0"
#define VO_HCSCCOEF2_14_inst                                          0x00D0
#define VO_HCSCCOEF2_15_inst_addr                                     "0x00D1"
#define VO_HCSCCOEF2_15_inst                                          0x00D1
#define VO_HCSCCOEF2_csccoef_shift                                    (0)
#define VO_HCSCCOEF2_csccoef_mask                                     (0x00003FFF)
#define VO_HCSCCOEF2_csccoef(data)                                    (0x00003FFF&(data))
#define VO_HCSCCOEF2_get_csccoef(data)                                (0x00003FFF&(data))

#define VO_DUMP                                                       0x18005348
#define VO_DUMP_reg_addr                                              "0xB8005348"
#define VO_DUMP_reg                                                   0xB8005348
#define VO_DUMP_inst_addr                                             "0x00D2"
#define VO_DUMP_inst                                                  0x00D2
#define VO_DUMP_write_enable1_shift                                   (20)
#define VO_DUMP_en_shift                                              (19)
#define VO_DUMP_write_enable2_shift                                   (18)
#define VO_DUMP_size_shift                                            (0)
#define VO_DUMP_write_enable1_mask                                    (0x00100000)
#define VO_DUMP_en_mask                                               (0x00080000)
#define VO_DUMP_write_enable2_mask                                    (0x00040000)
#define VO_DUMP_size_mask                                             (0x0003FFFF)
#define VO_DUMP_write_enable1(data)                                   (0x00100000&((data)<<20))
#define VO_DUMP_en(data)                                              (0x00080000&((data)<<19))
#define VO_DUMP_write_enable2(data)                                   (0x00040000&((data)<<18))
#define VO_DUMP_size(data)                                            (0x0003FFFF&(data))
#define VO_DUMP_get_write_enable1(data)                               ((0x00100000&(data))>>20)
#define VO_DUMP_get_en(data)                                          ((0x00080000&(data))>>19)
#define VO_DUMP_get_write_enable2(data)                               ((0x00040000&(data))>>18)
#define VO_DUMP_get_size(data)                                        (0x0003FFFF&(data))

#define VO_TT                                                         0x1800534C
#define VO_TT_reg_addr                                                "0xB800534C"
#define VO_TT_reg                                                     0xB800534C
#define VO_TT_inst_addr                                               "0x00D3"
#define VO_TT_inst                                                    0x00D3
#define VO_TT_write_enable1_shift                                     (12)
#define VO_TT_en_shift                                                (11)
#define VO_TT_write_enable2_shift                                     (10)
#define VO_TT_size_shift                                              (0)
#define VO_TT_write_enable1_mask                                      (0x00001000)
#define VO_TT_en_mask                                                 (0x00000800)
#define VO_TT_write_enable2_mask                                      (0x00000400)
#define VO_TT_size_mask                                               (0x000003FF)
#define VO_TT_write_enable1(data)                                     (0x00001000&((data)<<12))
#define VO_TT_en(data)                                                (0x00000800&((data)<<11))
#define VO_TT_write_enable2(data)                                     (0x00000400&((data)<<10))
#define VO_TT_size(data)                                              (0x000003FF&(data))
#define VO_TT_get_write_enable1(data)                                 ((0x00001000&(data))>>12)
#define VO_TT_get_en(data)                                            ((0x00000800&(data))>>11)
#define VO_TT_get_write_enable2(data)                                 ((0x00000400&(data))>>10)
#define VO_TT_get_size(data)                                          (0x000003FF&(data))

#define VO_SPU                                                        0x18005350
#define VO_SPU_reg_addr                                               "0xB8005350"
#define VO_SPU_reg                                                    0xB8005350
#define VO_SPU_inst_addr                                              "0x00D4"
#define VO_SPU_inst                                                   0x00D4
#define VO_SPU_hlen_shift                                             (2)
#define VO_SPU_en_shift                                               (1)
#define VO_SPU_write_data_shift                                       (0)
#define VO_SPU_hlen_mask                                              (0x00000004)
#define VO_SPU_en_mask                                                (0x00000002)
#define VO_SPU_write_data_mask                                        (0x00000001)
#define VO_SPU_hlen(data)                                             (0x00000004&((data)<<2))
#define VO_SPU_en(data)                                               (0x00000002&((data)<<1))
#define VO_SPU_write_data(data)                                       (0x00000001&(data))
#define VO_SPU_get_hlen(data)                                         ((0x00000004&(data))>>2)
#define VO_SPU_get_en(data)                                           ((0x00000002&(data))>>1)
#define VO_SPU_get_write_data(data)                                   (0x00000001&(data))

#define VO_SPIXEND                                                    0x18005354
#define VO_SPIXEND_reg_addr                                           "0xB8005354"
#define VO_SPIXEND_reg                                                0xB8005354
#define VO_SPIXEND_inst_addr                                          "0x00D5"
#define VO_SPIXEND_inst                                               0x00D5
#define VO_SPIXEND_x_shift                                            (0)
#define VO_SPIXEND_x_mask                                             (0x000003FF)
#define VO_SPIXEND_x(data)                                            (0x000003FF&(data))
#define VO_SPIXEND_get_x(data)                                        (0x000003FF&(data))

#define VO_SPIYEND                                                    0x18005358
#define VO_SPIYEND_reg_addr                                           "0xB8005358"
#define VO_SPIYEND_reg                                                0xB8005358
#define VO_SPIYEND_inst_addr                                          "0x00D6"
#define VO_SPIYEND_inst                                               0x00D6
#define VO_SPIYEND_write_enable1_shift                                (21)
#define VO_SPIYEND_top_shift                                          (11)
#define VO_SPIYEND_write_enable2_shift                                (10)
#define VO_SPIYEND_bot_shift                                          (0)
#define VO_SPIYEND_write_enable1_mask                                 (0x00200000)
#define VO_SPIYEND_top_mask                                           (0x001FF800)
#define VO_SPIYEND_write_enable2_mask                                 (0x00000400)
#define VO_SPIYEND_bot_mask                                           (0x000003FF)
#define VO_SPIYEND_write_enable1(data)                                (0x00200000&((data)<<21))
#define VO_SPIYEND_top(data)                                          (0x001FF800&((data)<<11))
#define VO_SPIYEND_write_enable2(data)                                (0x00000400&((data)<<10))
#define VO_SPIYEND_bot(data)                                          (0x000003FF&(data))
#define VO_SPIYEND_get_write_enable1(data)                            ((0x00200000&(data))>>21)
#define VO_SPIYEND_get_top(data)                                      ((0x001FF800&(data))>>11)
#define VO_SPIYEND_get_write_enable2(data)                            ((0x00000400&(data))>>10)
#define VO_SPIYEND_get_bot(data)                                      (0x000003FF&(data))

#define VO_SPDFTMAP                                                   0x1800535C
#define VO_SPDFTMAP_reg_addr                                          "0xB800535C"
#define VO_SPDFTMAP_reg                                               0xB800535C
#define VO_SPDFTMAP_inst_addr                                         "0x00D7"
#define VO_SPDFTMAP_inst                                              0x00D7
#define VO_SPDFTMAP_alpha3_shift                                      (28)
#define VO_SPDFTMAP_alpha2_shift                                      (24)
#define VO_SPDFTMAP_alpha1_shift                                      (20)
#define VO_SPDFTMAP_alpha0_shift                                      (16)
#define VO_SPDFTMAP_color3_shift                                      (12)
#define VO_SPDFTMAP_color2_shift                                      (8)
#define VO_SPDFTMAP_color1_shift                                      (4)
#define VO_SPDFTMAP_color0_shift                                      (0)
#define VO_SPDFTMAP_alpha3_mask                                       (0xF0000000)
#define VO_SPDFTMAP_alpha2_mask                                       (0x0F000000)
#define VO_SPDFTMAP_alpha1_mask                                       (0x00F00000)
#define VO_SPDFTMAP_alpha0_mask                                       (0x000F0000)
#define VO_SPDFTMAP_color3_mask                                       (0x0000F000)
#define VO_SPDFTMAP_color2_mask                                       (0x00000F00)
#define VO_SPDFTMAP_color1_mask                                       (0x000000F0)
#define VO_SPDFTMAP_color0_mask                                       (0x0000000F)
#define VO_SPDFTMAP_alpha3(data)                                      (0xF0000000&((data)<<28))
#define VO_SPDFTMAP_alpha2(data)                                      (0x0F000000&((data)<<24))
#define VO_SPDFTMAP_alpha1(data)                                      (0x00F00000&((data)<<20))
#define VO_SPDFTMAP_alpha0(data)                                      (0x000F0000&((data)<<16))
#define VO_SPDFTMAP_color3(data)                                      (0x0000F000&((data)<<12))
#define VO_SPDFTMAP_color2(data)                                      (0x00000F00&((data)<<8))
#define VO_SPDFTMAP_color1(data)                                      (0x000000F0&((data)<<4))
#define VO_SPDFTMAP_color0(data)                                      (0x0000000F&(data))
#define VO_SPDFTMAP_get_alpha3(data)                                  ((0xF0000000&(data))>>28)
#define VO_SPDFTMAP_get_alpha2(data)                                  ((0x0F000000&(data))>>24)
#define VO_SPDFTMAP_get_alpha1(data)                                  ((0x00F00000&(data))>>20)
#define VO_SPDFTMAP_get_alpha0(data)                                  ((0x000F0000&(data))>>16)
#define VO_SPDFTMAP_get_color3(data)                                  ((0x0000F000&(data))>>12)
#define VO_SPDFTMAP_get_color2(data)                                  ((0x00000F00&(data))>>8)
#define VO_SPDFTMAP_get_color1(data)                                  ((0x000000F0&(data))>>4)
#define VO_SPDFTMAP_get_color0(data)                                  (0x0000000F&(data))

#define VO_SP_LNCTLI                                                  0x18005360
#define VO_SP_LNCTLI_reg_addr                                         "0xB8005360"
#define VO_SP_LNCTLI_reg                                              0xB8005360
#define VO_SP_LNCTLI_inst_addr                                        "0x00D8"
#define VO_SP_LNCTLI_inst                                             0x00D8
#define VO_SP_LNCTLI_bot_num_shift                                    (9)
#define VO_SP_LNCTLI_top_num_shift                                    (0)
#define VO_SP_LNCTLI_bot_num_mask                                     (0x0003FE00)
#define VO_SP_LNCTLI_top_num_mask                                     (0x000001FF)
#define VO_SP_LNCTLI_bot_num(data)                                    (0x0003FE00&((data)<<9))
#define VO_SP_LNCTLI_top_num(data)                                    (0x000001FF&(data))
#define VO_SP_LNCTLI_get_bot_num(data)                                ((0x0003FE00&(data))>>9)
#define VO_SP_LNCTLI_get_top_num(data)                                (0x000001FF&(data))

#define VO_SPHLX                                                      0x18005364
#define VO_SPHLX_reg_addr                                             "0xB8005364"
#define VO_SPHLX_reg                                                  0xB8005364
#define VO_SPHLX_inst_addr                                            "0x00D9"
#define VO_SPHLX_inst                                                 0x00D9
#define VO_SPHLX_write_enable1_shift                                  (21)
#define VO_SPHLX_end_shift                                            (11)
#define VO_SPHLX_write_enable2_shift                                  (10)
#define VO_SPHLX_st_shift                                             (0)
#define VO_SPHLX_write_enable1_mask                                   (0x00200000)
#define VO_SPHLX_end_mask                                             (0x001FF800)
#define VO_SPHLX_write_enable2_mask                                   (0x00000400)
#define VO_SPHLX_st_mask                                              (0x000003FF)
#define VO_SPHLX_write_enable1(data)                                  (0x00200000&((data)<<21))
#define VO_SPHLX_end(data)                                            (0x001FF800&((data)<<11))
#define VO_SPHLX_write_enable2(data)                                  (0x00000400&((data)<<10))
#define VO_SPHLX_st(data)                                             (0x000003FF&(data))
#define VO_SPHLX_get_write_enable1(data)                              ((0x00200000&(data))>>21)
#define VO_SPHLX_get_end(data)                                        ((0x001FF800&(data))>>11)
#define VO_SPHLX_get_write_enable2(data)                              ((0x00000400&(data))>>10)
#define VO_SPHLX_get_st(data)                                         (0x000003FF&(data))

#define VO_SPHLY                                                      0x18005368
#define VO_SPHLY_reg_addr                                             "0xB8005368"
#define VO_SPHLY_reg                                                  0xB8005368
#define VO_SPHLY_inst_addr                                            "0x00DA"
#define VO_SPHLY_inst                                                 0x00DA
#define VO_SPHLY_write_enable1_shift                                  (21)
#define VO_SPHLY_end_shift                                            (11)
#define VO_SPHLY_write_enable2_shift                                  (10)
#define VO_SPHLY_st_shift                                             (0)
#define VO_SPHLY_write_enable1_mask                                   (0x00200000)
#define VO_SPHLY_end_mask                                             (0x001FF800)
#define VO_SPHLY_write_enable2_mask                                   (0x00000400)
#define VO_SPHLY_st_mask                                              (0x000003FF)
#define VO_SPHLY_write_enable1(data)                                  (0x00200000&((data)<<21))
#define VO_SPHLY_end(data)                                            (0x001FF800&((data)<<11))
#define VO_SPHLY_write_enable2(data)                                  (0x00000400&((data)<<10))
#define VO_SPHLY_st(data)                                             (0x000003FF&(data))
#define VO_SPHLY_get_write_enable1(data)                              ((0x00200000&(data))>>21)
#define VO_SPHLY_get_end(data)                                        ((0x001FF800&(data))>>11)
#define VO_SPHLY_get_write_enable2(data)                              ((0x00000400&(data))>>10)
#define VO_SPHLY_get_st(data)                                         (0x000003FF&(data))

#define VO_SPHLMAP                                                    0x1800536C
#define VO_SPHLMAP_reg_addr                                           "0xB800536C"
#define VO_SPHLMAP_reg                                                0xB800536C
#define VO_SPHLMAP_inst_addr                                          "0x00DB"
#define VO_SPHLMAP_inst                                               0x00DB
#define VO_SPHLMAP_alpha3_shift                                       (28)
#define VO_SPHLMAP_alpha2_shift                                       (24)
#define VO_SPHLMAP_alpha1_shift                                       (20)
#define VO_SPHLMAP_alpha0_shift                                       (16)
#define VO_SPHLMAP_color3_shift                                       (12)
#define VO_SPHLMAP_color2_shift                                       (8)
#define VO_SPHLMAP_color1_shift                                       (4)
#define VO_SPHLMAP_color0_shift                                       (0)
#define VO_SPHLMAP_alpha3_mask                                        (0xF0000000)
#define VO_SPHLMAP_alpha2_mask                                        (0x0F000000)
#define VO_SPHLMAP_alpha1_mask                                        (0x00F00000)
#define VO_SPHLMAP_alpha0_mask                                        (0x000F0000)
#define VO_SPHLMAP_color3_mask                                        (0x0000F000)
#define VO_SPHLMAP_color2_mask                                        (0x00000F00)
#define VO_SPHLMAP_color1_mask                                        (0x000000F0)
#define VO_SPHLMAP_color0_mask                                        (0x0000000F)
#define VO_SPHLMAP_alpha3(data)                                       (0xF0000000&((data)<<28))
#define VO_SPHLMAP_alpha2(data)                                       (0x0F000000&((data)<<24))
#define VO_SPHLMAP_alpha1(data)                                       (0x00F00000&((data)<<20))
#define VO_SPHLMAP_alpha0(data)                                       (0x000F0000&((data)<<16))
#define VO_SPHLMAP_color3(data)                                       (0x0000F000&((data)<<12))
#define VO_SPHLMAP_color2(data)                                       (0x00000F00&((data)<<8))
#define VO_SPHLMAP_color1(data)                                       (0x000000F0&((data)<<4))
#define VO_SPHLMAP_color0(data)                                       (0x0000000F&(data))
#define VO_SPHLMAP_get_alpha3(data)                                   ((0xF0000000&(data))>>28)
#define VO_SPHLMAP_get_alpha2(data)                                   ((0x0F000000&(data))>>24)
#define VO_SPHLMAP_get_alpha1(data)                                   ((0x00F00000&(data))>>20)
#define VO_SPHLMAP_get_alpha0(data)                                   ((0x000F0000&(data))>>16)
#define VO_SPHLMAP_get_color3(data)                                   ((0x0000F000&(data))>>12)
#define VO_SPHLMAP_get_color2(data)                                   ((0x00000F00&(data))>>8)
#define VO_SPHLMAP_get_color1(data)                                   ((0x000000F0&(data))>>4)
#define VO_SPHLMAP_get_color0(data)                                   (0x0000000F&(data))

#define VO_SPCLUT_0                                                   0x18005370
#define VO_SPCLUT_1                                                   0x18005374
#define VO_SPCLUT_2                                                   0x18005378
#define VO_SPCLUT_3                                                   0x1800537C
#define VO_SPCLUT_4                                                   0x18005380
#define VO_SPCLUT_5                                                   0x18005384
#define VO_SPCLUT_6                                                   0x18005388
#define VO_SPCLUT_7                                                   0x1800538C
#define VO_SPCLUT_8                                                   0x18005390
#define VO_SPCLUT_9                                                   0x18005394
#define VO_SPCLUT_10                                                  0x18005398
#define VO_SPCLUT_11                                                  0x1800539C
#define VO_SPCLUT_12                                                  0x180053A0
#define VO_SPCLUT_13                                                  0x180053A4
#define VO_SPCLUT_14                                                  0x180053A8
#define VO_SPCLUT_15                                                  0x180053AC
#define VO_SPCLUT_0_reg_addr                                          "0xB8005370"
#define VO_SPCLUT_1_reg_addr                                          "0xB8005374"
#define VO_SPCLUT_2_reg_addr                                          "0xB8005378"
#define VO_SPCLUT_3_reg_addr                                          "0xB800537C"
#define VO_SPCLUT_4_reg_addr                                          "0xB8005380"
#define VO_SPCLUT_5_reg_addr                                          "0xB8005384"
#define VO_SPCLUT_6_reg_addr                                          "0xB8005388"
#define VO_SPCLUT_7_reg_addr                                          "0xB800538C"
#define VO_SPCLUT_8_reg_addr                                          "0xB8005390"
#define VO_SPCLUT_9_reg_addr                                          "0xB8005394"
#define VO_SPCLUT_10_reg_addr                                         "0xB8005398"
#define VO_SPCLUT_11_reg_addr                                         "0xB800539C"
#define VO_SPCLUT_12_reg_addr                                         "0xB80053A0"
#define VO_SPCLUT_13_reg_addr                                         "0xB80053A4"
#define VO_SPCLUT_14_reg_addr                                         "0xB80053A8"
#define VO_SPCLUT_15_reg_addr                                         "0xB80053AC"
#define VO_SPCLUT_0_reg                                               0xB8005370
#define VO_SPCLUT_1_reg                                               0xB8005374
#define VO_SPCLUT_2_reg                                               0xB8005378
#define VO_SPCLUT_3_reg                                               0xB800537C
#define VO_SPCLUT_4_reg                                               0xB8005380
#define VO_SPCLUT_5_reg                                               0xB8005384
#define VO_SPCLUT_6_reg                                               0xB8005388
#define VO_SPCLUT_7_reg                                               0xB800538C
#define VO_SPCLUT_8_reg                                               0xB8005390
#define VO_SPCLUT_9_reg                                               0xB8005394
#define VO_SPCLUT_10_reg                                              0xB8005398
#define VO_SPCLUT_11_reg                                              0xB800539C
#define VO_SPCLUT_12_reg                                              0xB80053A0
#define VO_SPCLUT_13_reg                                              0xB80053A4
#define VO_SPCLUT_14_reg                                              0xB80053A8
#define VO_SPCLUT_15_reg                                              0xB80053AC
#define VO_SPCLUT_0_inst_addr                                         "0x00DC"
#define VO_SPCLUT_0_inst                                              0x00DC
#define VO_SPCLUT_1_inst_addr                                         "0x00DD"
#define VO_SPCLUT_1_inst                                              0x00DD
#define VO_SPCLUT_2_inst_addr                                         "0x00DE"
#define VO_SPCLUT_2_inst                                              0x00DE
#define VO_SPCLUT_3_inst_addr                                         "0x00DF"
#define VO_SPCLUT_3_inst                                              0x00DF
#define VO_SPCLUT_4_inst_addr                                         "0x00E0"
#define VO_SPCLUT_4_inst                                              0x00E0
#define VO_SPCLUT_5_inst_addr                                         "0x00E1"
#define VO_SPCLUT_5_inst                                              0x00E1
#define VO_SPCLUT_6_inst_addr                                         "0x00E2"
#define VO_SPCLUT_6_inst                                              0x00E2
#define VO_SPCLUT_7_inst_addr                                         "0x00E3"
#define VO_SPCLUT_7_inst                                              0x00E3
#define VO_SPCLUT_8_inst_addr                                         "0x00E4"
#define VO_SPCLUT_8_inst                                              0x00E4
#define VO_SPCLUT_9_inst_addr                                         "0x00E5"
#define VO_SPCLUT_9_inst                                              0x00E5
#define VO_SPCLUT_10_inst_addr                                        "0x00E6"
#define VO_SPCLUT_10_inst                                             0x00E6
#define VO_SPCLUT_11_inst_addr                                        "0x00E7"
#define VO_SPCLUT_11_inst                                             0x00E7
#define VO_SPCLUT_12_inst_addr                                        "0x00E8"
#define VO_SPCLUT_12_inst                                             0x00E8
#define VO_SPCLUT_13_inst_addr                                        "0x00E9"
#define VO_SPCLUT_13_inst                                             0x00E9
#define VO_SPCLUT_14_inst_addr                                        "0x00EA"
#define VO_SPCLUT_14_inst                                             0x00EA
#define VO_SPCLUT_15_inst_addr                                        "0x00EB"
#define VO_SPCLUT_15_inst                                             0x00EB
#define VO_SPCLUT_cr_shift                                            (16)
#define VO_SPCLUT_cb_shift                                            (8)
#define VO_SPCLUT_y_shift                                             (0)
#define VO_SPCLUT_cr_mask                                             (0x00FF0000)
#define VO_SPCLUT_cb_mask                                             (0x0000FF00)
#define VO_SPCLUT_y_mask                                              (0x000000FF)
#define VO_SPCLUT_cr(data)                                            (0x00FF0000&((data)<<16))
#define VO_SPCLUT_cb(data)                                            (0x0000FF00&((data)<<8))
#define VO_SPCLUT_y(data)                                             (0x000000FF&(data))
#define VO_SPCLUT_get_cr(data)                                        ((0x00FF0000&(data))>>16)
#define VO_SPCLUT_get_cb(data)                                        ((0x0000FF00&(data))>>8)
#define VO_SPCLUT_get_y(data)                                         (0x000000FF&(data))

#define VO_SPX                                                        0x180053B0
#define VO_SPX_reg_addr                                               "0xB80053B0"
#define VO_SPX_reg                                                    0xB80053B0
#define VO_SPX_inst_addr                                              "0x00EC"
#define VO_SPX_inst                                                   0x00EC
#define VO_SPX_write_enable1_shift                                    (23)
#define VO_SPX_end_shift                                              (12)
#define VO_SPX_write_enable2_shift                                    (11)
#define VO_SPX_st_shift                                               (0)
#define VO_SPX_write_enable1_mask                                     (0x00800000)
#define VO_SPX_end_mask                                               (0x007FF000)
#define VO_SPX_write_enable2_mask                                     (0x00000800)
#define VO_SPX_st_mask                                                (0x000007FF)
#define VO_SPX_write_enable1(data)                                    (0x00800000&((data)<<23))
#define VO_SPX_end(data)                                              (0x007FF000&((data)<<12))
#define VO_SPX_write_enable2(data)                                    (0x00000800&((data)<<11))
#define VO_SPX_st(data)                                               (0x000007FF&(data))
#define VO_SPX_get_write_enable1(data)                                ((0x00800000&(data))>>23)
#define VO_SPX_get_end(data)                                          ((0x007FF000&(data))>>12)
#define VO_SPX_get_write_enable2(data)                                ((0x00000800&(data))>>11)
#define VO_SPX_get_st(data)                                           (0x000007FF&(data))

#define VO_SPY                                                        0x180053B4
#define VO_SPY_reg_addr                                               "0xB80053B4"
#define VO_SPY_reg                                                    0xB80053B4
#define VO_SPY_inst_addr                                              "0x00ED"
#define VO_SPY_inst                                                   0x00ED
#define VO_SPY_write_enable1_shift                                    (23)
#define VO_SPY_end_shift                                              (12)
#define VO_SPY_write_enable2_shift                                    (11)
#define VO_SPY_st_shift                                               (0)
#define VO_SPY_write_enable1_mask                                     (0x00800000)
#define VO_SPY_end_mask                                               (0x007FF000)
#define VO_SPY_write_enable2_mask                                     (0x00000800)
#define VO_SPY_st_mask                                                (0x000007FF)
#define VO_SPY_write_enable1(data)                                    (0x00800000&((data)<<23))
#define VO_SPY_end(data)                                              (0x007FF000&((data)<<12))
#define VO_SPY_write_enable2(data)                                    (0x00000800&((data)<<11))
#define VO_SPY_st(data)                                               (0x000007FF&(data))
#define VO_SPY_get_write_enable1(data)                                ((0x00800000&(data))>>23)
#define VO_SPY_get_end(data)                                          ((0x007FF000&(data))>>12)
#define VO_SPY_get_write_enable2(data)                                ((0x00000800&(data))>>11)
#define VO_SPY_get_st(data)                                           (0x000007FF&(data))

#define VO_SPVSCCTL                                                   0x180053B8
#define VO_SPVSCCTL_reg_addr                                          "0xB80053B8"
#define VO_SPVSCCTL_reg                                               0xB80053B8
#define VO_SPVSCCTL_inst_addr                                         "0x00EE"
#define VO_SPVSCCTL_inst                                              0x00EE
#define VO_SPVSCCTL_oddtype_shift                                     (1)
#define VO_SPVSCCTL_write_data_shift                                  (0)
#define VO_SPVSCCTL_oddtype_mask                                      (0x00000002)
#define VO_SPVSCCTL_write_data_mask                                   (0x00000001)
#define VO_SPVSCCTL_oddtype(data)                                     (0x00000002&((data)<<1))
#define VO_SPVSCCTL_write_data(data)                                  (0x00000001&(data))
#define VO_SPVSCCTL_get_oddtype(data)                                 ((0x00000002&(data))>>1)
#define VO_SPVSCCTL_get_write_data(data)                              (0x00000001&(data))

#define VO_SPVSC                                                      0x180053BC
#define VO_SPVSC_reg_addr                                             "0xB80053BC"
#define VO_SPVSC_reg                                                  0xB80053BC
#define VO_SPVSC_inst_addr                                            "0x00EF"
#define VO_SPVSC_inst                                                 0x00EF
#define VO_SPVSC_dphs_shift                                           (0)
#define VO_SPVSC_dphs_mask                                            (0x0001FFFF)
#define VO_SPVSC_dphs(data)                                           (0x0001FFFF&(data))
#define VO_SPVSC_get_dphs(data)                                       (0x0001FFFF&(data))

#define VO_SPVIPOS                                                    0x180053C0
#define VO_SPVIPOS_reg_addr                                           "0xB80053C0"
#define VO_SPVIPOS_reg                                                0xB80053C0
#define VO_SPVIPOS_inst_addr                                          "0x00F0"
#define VO_SPVIPOS_inst                                               0x00F0
#define VO_SPVIPOS_init_offset_shift                                  (14)
#define VO_SPVIPOS_init_phase_shift                                   (0)
#define VO_SPVIPOS_init_offset_mask                                   (0x00FFC000)
#define VO_SPVIPOS_init_phase_mask                                    (0x00003FFF)
#define VO_SPVIPOS_init_offset(data)                                  (0x00FFC000&((data)<<14))
#define VO_SPVIPOS_init_phase(data)                                   (0x00003FFF&(data))
#define VO_SPVIPOS_get_init_offset(data)                              ((0x00FFC000&(data))>>14)
#define VO_SPVIPOS_get_init_phase(data)                               (0x00003FFF&(data))

#define VO_SPVSCCOEF_0                                                0x180053C4
#define VO_SPVSCCOEF_1                                                0x180053C8
#define VO_SPVSCCOEF_2                                                0x180053CC
#define VO_SPVSCCOEF_3                                                0x180053D0
#define VO_SPVSCCOEF_0_reg_addr                                       "0xB80053C4"
#define VO_SPVSCCOEF_1_reg_addr                                       "0xB80053C8"
#define VO_SPVSCCOEF_2_reg_addr                                       "0xB80053CC"
#define VO_SPVSCCOEF_3_reg_addr                                       "0xB80053D0"
#define VO_SPVSCCOEF_0_reg                                            0xB80053C4
#define VO_SPVSCCOEF_1_reg                                            0xB80053C8
#define VO_SPVSCCOEF_2_reg                                            0xB80053CC
#define VO_SPVSCCOEF_3_reg                                            0xB80053D0
#define VO_SPVSCCOEF_0_inst_addr                                      "0x00F1"
#define VO_SPVSCCOEF_0_inst                                           0x00F1
#define VO_SPVSCCOEF_1_inst_addr                                      "0x00F2"
#define VO_SPVSCCOEF_1_inst                                           0x00F2
#define VO_SPVSCCOEF_2_inst_addr                                      "0x00F3"
#define VO_SPVSCCOEF_2_inst                                           0x00F3
#define VO_SPVSCCOEF_3_inst_addr                                      "0x00F4"
#define VO_SPVSCCOEF_3_inst                                           0x00F4
#define VO_SPVSCCOEF_c_shift                                          (0)
#define VO_SPVSCCOEF_c_mask                                           (0x000007FF)
#define VO_SPVSCCOEF_c(data)                                          (0x000007FF&(data))
#define VO_SPVSCCOEF_get_c(data)                                      (0x000007FF&(data))

#define VO_SPHSCCTL                                                   0x180053D4
#define VO_SPHSCCTL_reg_addr                                          "0xB80053D4"
#define VO_SPHSCCTL_reg                                               0xB80053D4
#define VO_SPHSCCTL_inst_addr                                         "0x00F5"
#define VO_SPHSCCTL_inst                                              0x00F5
#define VO_SPHSCCTL_st_transp_shift                                   (4)
#define VO_SPHSCCTL_end_transp_shift                                  (3)
#define VO_SPHSCCTL_yoddtype_shift                                    (2)
#define VO_SPHSCCTL_coddtype_shift                                    (1)
#define VO_SPHSCCTL_write_data_shift                                  (0)
#define VO_SPHSCCTL_st_transp_mask                                    (0x00000010)
#define VO_SPHSCCTL_end_transp_mask                                   (0x00000008)
#define VO_SPHSCCTL_yoddtype_mask                                     (0x00000004)
#define VO_SPHSCCTL_coddtype_mask                                     (0x00000002)
#define VO_SPHSCCTL_write_data_mask                                   (0x00000001)
#define VO_SPHSCCTL_st_transp(data)                                   (0x00000010&((data)<<4))
#define VO_SPHSCCTL_end_transp(data)                                  (0x00000008&((data)<<3))
#define VO_SPHSCCTL_yoddtype(data)                                    (0x00000004&((data)<<2))
#define VO_SPHSCCTL_coddtype(data)                                    (0x00000002&((data)<<1))
#define VO_SPHSCCTL_write_data(data)                                  (0x00000001&(data))
#define VO_SPHSCCTL_get_st_transp(data)                               ((0x00000010&(data))>>4)
#define VO_SPHSCCTL_get_end_transp(data)                              ((0x00000008&(data))>>3)
#define VO_SPHSCCTL_get_yoddtype(data)                                ((0x00000004&(data))>>2)
#define VO_SPHSCCTL_get_coddtype(data)                                ((0x00000002&(data))>>1)
#define VO_SPHSCCTL_get_write_data(data)                              (0x00000001&(data))

#define VO_SPHYSC                                                     0x180053D8
#define VO_SPHYSC_reg_addr                                            "0xB80053D8"
#define VO_SPHYSC_reg                                                 0xB80053D8
#define VO_SPHYSC_inst_addr                                           "0x00F6"
#define VO_SPHYSC_inst                                                0x00F6
#define VO_SPHYSC_ydphs_shift                                         (0)
#define VO_SPHYSC_ydphs_mask                                          (0x0001FFFF)
#define VO_SPHYSC_ydphs(data)                                         (0x0001FFFF&(data))
#define VO_SPHYSC_get_ydphs(data)                                     (0x0001FFFF&(data))

#define VO_SPHIPOS                                                    0x180053DC
#define VO_SPHIPOS_reg_addr                                           "0xB80053DC"
#define VO_SPHIPOS_reg                                                0xB80053DC
#define VO_SPHIPOS_inst_addr                                          "0x00F7"
#define VO_SPHIPOS_inst                                               0x00F7
#define VO_SPHIPOS_init_offset_shift                                  (14)
#define VO_SPHIPOS_init_phase_shift                                   (0)
#define VO_SPHIPOS_init_offset_mask                                   (0x01FFC000)
#define VO_SPHIPOS_init_phase_mask                                    (0x00003FFF)
#define VO_SPHIPOS_init_offset(data)                                  (0x01FFC000&((data)<<14))
#define VO_SPHIPOS_init_phase(data)                                   (0x00003FFF&(data))
#define VO_SPHIPOS_get_init_offset(data)                              ((0x01FFC000&(data))>>14)
#define VO_SPHIPOS_get_init_phase(data)                               (0x00003FFF&(data))

#define VO_SPHYSCCOEF_0                                               0x180053E0
#define VO_SPHYSCCOEF_1                                               0x180053E4
#define VO_SPHYSCCOEF_2                                               0x180053E8
#define VO_SPHYSCCOEF_3                                               0x180053EC
#define VO_SPHYSCCOEF_4                                               0x180053F0
#define VO_SPHYSCCOEF_5                                               0x180053F4
#define VO_SPHYSCCOEF_6                                               0x180053F8
#define VO_SPHYSCCOEF_7                                               0x180053FC
#define VO_SPHYSCCOEF_0_reg_addr                                      "0xB80053E0"
#define VO_SPHYSCCOEF_1_reg_addr                                      "0xB80053E4"
#define VO_SPHYSCCOEF_2_reg_addr                                      "0xB80053E8"
#define VO_SPHYSCCOEF_3_reg_addr                                      "0xB80053EC"
#define VO_SPHYSCCOEF_4_reg_addr                                      "0xB80053F0"
#define VO_SPHYSCCOEF_5_reg_addr                                      "0xB80053F4"
#define VO_SPHYSCCOEF_6_reg_addr                                      "0xB80053F8"
#define VO_SPHYSCCOEF_7_reg_addr                                      "0xB80053FC"
#define VO_SPHYSCCOEF_0_reg                                           0xB80053E0
#define VO_SPHYSCCOEF_1_reg                                           0xB80053E4
#define VO_SPHYSCCOEF_2_reg                                           0xB80053E8
#define VO_SPHYSCCOEF_3_reg                                           0xB80053EC
#define VO_SPHYSCCOEF_4_reg                                           0xB80053F0
#define VO_SPHYSCCOEF_5_reg                                           0xB80053F4
#define VO_SPHYSCCOEF_6_reg                                           0xB80053F8
#define VO_SPHYSCCOEF_7_reg                                           0xB80053FC
#define VO_SPHYSCCOEF_0_inst_addr                                     "0x00F8"
#define VO_SPHYSCCOEF_0_inst                                          0x00F8
#define VO_SPHYSCCOEF_1_inst_addr                                     "0x00F9"
#define VO_SPHYSCCOEF_1_inst                                          0x00F9
#define VO_SPHYSCCOEF_2_inst_addr                                     "0x00FA"
#define VO_SPHYSCCOEF_2_inst                                          0x00FA
#define VO_SPHYSCCOEF_3_inst_addr                                     "0x00FB"
#define VO_SPHYSCCOEF_3_inst                                          0x00FB
#define VO_SPHYSCCOEF_4_inst_addr                                     "0x00FC"
#define VO_SPHYSCCOEF_4_inst                                          0x00FC
#define VO_SPHYSCCOEF_5_inst_addr                                     "0x00FD"
#define VO_SPHYSCCOEF_5_inst                                          0x00FD
#define VO_SPHYSCCOEF_6_inst_addr                                     "0x00FE"
#define VO_SPHYSCCOEF_6_inst                                          0x00FE
#define VO_SPHYSCCOEF_7_inst_addr                                     "0x00FF"
#define VO_SPHYSCCOEF_7_inst                                          0x00FF
#define VO_SPHYSCCOEF_c_shift                                         (0)
#define VO_SPHYSCCOEF_c_mask                                          (0x00000FFF)
#define VO_SPHYSCCOEF_c(data)                                         (0x00000FFF&(data))
#define VO_SPHYSCCOEF_get_c(data)                                     (0x00000FFF&(data))

#define VO_SPHCSCCOEF_0                                               0x18005400
#define VO_SPHCSCCOEF_1                                               0x18005404
#define VO_SPHCSCCOEF_2                                               0x18005408
#define VO_SPHCSCCOEF_3                                               0x1800540C
#define VO_SPHCSCCOEF_4                                               0x18005410
#define VO_SPHCSCCOEF_5                                               0x18005414
#define VO_SPHCSCCOEF_6                                               0x18005418
#define VO_SPHCSCCOEF_7                                               0x1800541C
#define VO_SPHCSCCOEF_0_reg_addr                                      "0xB8005400"
#define VO_SPHCSCCOEF_1_reg_addr                                      "0xB8005404"
#define VO_SPHCSCCOEF_2_reg_addr                                      "0xB8005408"
#define VO_SPHCSCCOEF_3_reg_addr                                      "0xB800540C"
#define VO_SPHCSCCOEF_4_reg_addr                                      "0xB8005410"
#define VO_SPHCSCCOEF_5_reg_addr                                      "0xB8005414"
#define VO_SPHCSCCOEF_6_reg_addr                                      "0xB8005418"
#define VO_SPHCSCCOEF_7_reg_addr                                      "0xB800541C"
#define VO_SPHCSCCOEF_0_reg                                           0xB8005400
#define VO_SPHCSCCOEF_1_reg                                           0xB8005404
#define VO_SPHCSCCOEF_2_reg                                           0xB8005408
#define VO_SPHCSCCOEF_3_reg                                           0xB800540C
#define VO_SPHCSCCOEF_4_reg                                           0xB8005410
#define VO_SPHCSCCOEF_5_reg                                           0xB8005414
#define VO_SPHCSCCOEF_6_reg                                           0xB8005418
#define VO_SPHCSCCOEF_7_reg                                           0xB800541C
#define VO_SPHCSCCOEF_0_inst_addr                                     "0x0100"
#define VO_SPHCSCCOEF_0_inst                                          0x0100
#define VO_SPHCSCCOEF_1_inst_addr                                     "0x0101"
#define VO_SPHCSCCOEF_1_inst                                          0x0101
#define VO_SPHCSCCOEF_2_inst_addr                                     "0x0102"
#define VO_SPHCSCCOEF_2_inst                                          0x0102
#define VO_SPHCSCCOEF_3_inst_addr                                     "0x0103"
#define VO_SPHCSCCOEF_3_inst                                          0x0103
#define VO_SPHCSCCOEF_4_inst_addr                                     "0x0104"
#define VO_SPHCSCCOEF_4_inst                                          0x0104
#define VO_SPHCSCCOEF_5_inst_addr                                     "0x0105"
#define VO_SPHCSCCOEF_5_inst                                          0x0105
#define VO_SPHCSCCOEF_6_inst_addr                                     "0x0106"
#define VO_SPHCSCCOEF_6_inst                                          0x0106
#define VO_SPHCSCCOEF_7_inst_addr                                     "0x0107"
#define VO_SPHCSCCOEF_7_inst                                          0x0107
#define VO_SPHCSCCOEF_c_shift                                         (0)
#define VO_SPHCSCCOEF_c_mask                                          (0x00000FFF)
#define VO_SPHCSCCOEF_c(data)                                         (0x00000FFF&(data))
#define VO_SPHCSCCOEF_get_c(data)                                     (0x00000FFF&(data))

#define VO_BUFEND                                                     0x18005420
#define VO_BUFEND_reg_addr                                            "0xB8005420"
#define VO_BUFEND_reg                                                 0xB8005420
#define VO_BUFEND_inst_addr                                           "0x0108"
#define VO_BUFEND_inst                                                0x0108
#define VO_BUFEND_sub_shift                                           (18)
#define VO_BUFEND_v2_shift                                            (9)
#define VO_BUFEND_v1_shift                                            (0)
#define VO_BUFEND_sub_mask                                            (0x07FC0000)
#define VO_BUFEND_v2_mask                                             (0x0003FE00)
#define VO_BUFEND_v1_mask                                             (0x000001FF)
#define VO_BUFEND_sub(data)                                           (0x07FC0000&((data)<<18))
#define VO_BUFEND_v2(data)                                            (0x0003FE00&((data)<<9))
#define VO_BUFEND_v1(data)                                            (0x000001FF&(data))
#define VO_BUFEND_get_sub(data)                                       ((0x07FC0000&(data))>>18)
#define VO_BUFEND_get_v2(data)                                        ((0x0003FE00&(data))>>9)
#define VO_BUFEND_get_v1(data)                                        (0x000001FF&(data))

#define VO_OSD                                                        0x18005424
#define VO_OSD_reg_addr                                               "0xB8005424"
#define VO_OSD_reg                                                    0xB8005424
#define VO_OSD_inst_addr                                              "0x0109"
#define VO_OSD_inst                                                   0x0109
#define VO_OSD_write_enable1_shift                                    (11)
#define VO_OSD_interlace_shift                                        (10)
#define VO_OSD_write_enable2_shift                                    (9)
#define VO_OSD_alpha_msb_shift                                        (8)
#define VO_OSD_write_enable3_shift                                    (7)
#define VO_OSD_lpf_shift                                              (5)
#define VO_OSD_write_enable4_shift                                    (4)
#define VO_OSD_wn_shift                                               (2)
#define VO_OSD_write_enable5_shift                                    (1)
#define VO_OSD_en_shift                                               (0)
#define VO_OSD_write_enable1_mask                                     (0x00000800)
#define VO_OSD_interlace_mask                                         (0x00000400)
#define VO_OSD_write_enable2_mask                                     (0x00000200)
#define VO_OSD_alpha_msb_mask                                         (0x00000100)
#define VO_OSD_write_enable3_mask                                     (0x00000080)
#define VO_OSD_lpf_mask                                               (0x00000060)
#define VO_OSD_write_enable4_mask                                     (0x00000010)
#define VO_OSD_wn_mask                                                (0x0000000C)
#define VO_OSD_write_enable5_mask                                     (0x00000002)
#define VO_OSD_en_mask                                                (0x00000001)
#define VO_OSD_write_enable1(data)                                    (0x00000800&((data)<<11))
#define VO_OSD_interlace(data)                                        (0x00000400&((data)<<10))
#define VO_OSD_write_enable2(data)                                    (0x00000200&((data)<<9))
#define VO_OSD_alpha_msb(data)                                        (0x00000100&((data)<<8))
#define VO_OSD_write_enable3(data)                                    (0x00000080&((data)<<7))
#define VO_OSD_lpf(data)                                              (0x00000060&((data)<<5))
#define VO_OSD_write_enable4(data)                                    (0x00000010&((data)<<4))
#define VO_OSD_wn(data)                                               (0x0000000C&((data)<<2))
#define VO_OSD_write_enable5(data)                                    (0x00000002&((data)<<1))
#define VO_OSD_en(data)                                               (0x00000001&(data))
#define VO_OSD_get_write_enable1(data)                                ((0x00000800&(data))>>11)
#define VO_OSD_get_interlace(data)                                    ((0x00000400&(data))>>10)
#define VO_OSD_get_write_enable2(data)                                ((0x00000200&(data))>>9)
#define VO_OSD_get_alpha_msb(data)                                    ((0x00000100&(data))>>8)
#define VO_OSD_get_write_enable3(data)                                ((0x00000080&(data))>>7)
#define VO_OSD_get_lpf(data)                                          ((0x00000060&(data))>>5)
#define VO_OSD_get_write_enable4(data)                                ((0x00000010&(data))>>4)
#define VO_OSD_get_wn(data)                                           ((0x0000000C&(data))>>2)
#define VO_OSD_get_write_enable5(data)                                ((0x00000002&(data))>>1)
#define VO_OSD_get_en(data)                                           (0x00000001&(data))

#define VO_OSDCA_0                                                    0x18005428
#define VO_OSDCA_1                                                    0x1800542C
#define VO_OSDCA_2                                                    0x18005430
#define VO_OSDCA_3                                                    0x18005434
#define VO_OSDCA_0_reg_addr                                           "0xB8005428"
#define VO_OSDCA_1_reg_addr                                           "0xB800542C"
#define VO_OSDCA_2_reg_addr                                           "0xB8005430"
#define VO_OSDCA_3_reg_addr                                           "0xB8005434"
#define VO_OSDCA_0_reg                                                0xB8005428
#define VO_OSDCA_1_reg                                                0xB800542C
#define VO_OSDCA_2_reg                                                0xB8005430
#define VO_OSDCA_3_reg                                                0xB8005434
#define VO_OSDCA_0_inst_addr                                          "0x010A"
#define VO_OSDCA_0_inst                                               0x010A
#define VO_OSDCA_1_inst_addr                                          "0x010B"
#define VO_OSDCA_1_inst                                               0x010B
#define VO_OSDCA_2_inst_addr                                          "0x010C"
#define VO_OSDCA_2_inst                                               0x010C
#define VO_OSDCA_3_inst_addr                                          "0x010D"
#define VO_OSDCA_3_inst                                               0x010D
#define VO_OSDCA_write_enable1_shift                                  (10)
#define VO_OSDCA_a_shift                                              (2)
#define VO_OSDCA_write_enable2_shift                                  (1)
#define VO_OSDCA_en_shift                                             (0)
#define VO_OSDCA_write_enable1_mask                                   (0x00000400)
#define VO_OSDCA_a_mask                                               (0x000003FC)
#define VO_OSDCA_write_enable2_mask                                   (0x00000002)
#define VO_OSDCA_en_mask                                              (0x00000001)
#define VO_OSDCA_write_enable1(data)                                  (0x00000400&((data)<<10))
#define VO_OSDCA_a(data)                                              (0x000003FC&((data)<<2))
#define VO_OSDCA_write_enable2(data)                                  (0x00000002&((data)<<1))
#define VO_OSDCA_en(data)                                             (0x00000001&(data))
#define VO_OSDCA_get_write_enable1(data)                              ((0x00000400&(data))>>10)
#define VO_OSDCA_get_a(data)                                          ((0x000003FC&(data))>>2)
#define VO_OSDCA_get_write_enable2(data)                              ((0x00000002&(data))>>1)
#define VO_OSDCA_get_en(data)                                         (0x00000001&(data))

#define VO_OSDKEY_0                                                   0x18005438
#define VO_OSDKEY_1                                                   0x1800543C
#define VO_OSDKEY_2                                                   0x18005440
#define VO_OSDKEY_3                                                   0x18005444
#define VO_OSDKEY_0_reg_addr                                          "0xB8005438"
#define VO_OSDKEY_1_reg_addr                                          "0xB800543C"
#define VO_OSDKEY_2_reg_addr                                          "0xB8005440"
#define VO_OSDKEY_3_reg_addr                                          "0xB8005444"
#define VO_OSDKEY_0_reg                                               0xB8005438
#define VO_OSDKEY_1_reg                                               0xB800543C
#define VO_OSDKEY_2_reg                                               0xB8005440
#define VO_OSDKEY_3_reg                                               0xB8005444
#define VO_OSDKEY_0_inst_addr                                         "0x010E"
#define VO_OSDKEY_0_inst                                              0x010E
#define VO_OSDKEY_1_inst_addr                                         "0x010F"
#define VO_OSDKEY_1_inst                                              0x010F
#define VO_OSDKEY_2_inst_addr                                         "0x0110"
#define VO_OSDKEY_2_inst                                              0x0110
#define VO_OSDKEY_3_inst_addr                                         "0x0111"
#define VO_OSDKEY_3_inst                                              0x0111
#define VO_OSDKEY_write_enable1_shift                                 (26)
#define VO_OSDKEY_k_shift                                             (2)
#define VO_OSDKEY_write_enable2_shift                                 (1)
#define VO_OSDKEY_en_shift                                            (0)
#define VO_OSDKEY_write_enable1_mask                                  (0x04000000)
#define VO_OSDKEY_k_mask                                              (0x03FFFFFC)
#define VO_OSDKEY_write_enable2_mask                                  (0x00000002)
#define VO_OSDKEY_en_mask                                             (0x00000001)
#define VO_OSDKEY_write_enable1(data)                                 (0x04000000&((data)<<26))
#define VO_OSDKEY_k(data)                                             (0x03FFFFFC&((data)<<2))
#define VO_OSDKEY_write_enable2(data)                                 (0x00000002&((data)<<1))
#define VO_OSDKEY_en(data)                                            (0x00000001&(data))
#define VO_OSDKEY_get_write_enable1(data)                             ((0x04000000&(data))>>26)
#define VO_OSDKEY_get_k(data)                                         ((0x03FFFFFC&(data))>>2)
#define VO_OSDKEY_get_write_enable2(data)                             ((0x00000002&(data))>>1)
#define VO_OSDKEY_get_en(data)                                        (0x00000001&(data))

#define VO_OSDX_0                                                     0x18005448
#define VO_OSDX_1                                                     0x1800544C
#define VO_OSDX_2                                                     0x18005450
#define VO_OSDX_3                                                     0x18005454
#define VO_OSDX_0_reg_addr                                            "0xB8005448"
#define VO_OSDX_1_reg_addr                                            "0xB800544C"
#define VO_OSDX_2_reg_addr                                            "0xB8005450"
#define VO_OSDX_3_reg_addr                                            "0xB8005454"
#define VO_OSDX_0_reg                                                 0xB8005448
#define VO_OSDX_1_reg                                                 0xB800544C
#define VO_OSDX_2_reg                                                 0xB8005450
#define VO_OSDX_3_reg                                                 0xB8005454
#define VO_OSDX_0_inst_addr                                           "0x0112"
#define VO_OSDX_0_inst                                                0x0112
#define VO_OSDX_1_inst_addr                                           "0x0113"
#define VO_OSDX_1_inst                                                0x0113
#define VO_OSDX_2_inst_addr                                           "0x0114"
#define VO_OSDX_2_inst                                                0x0114
#define VO_OSDX_3_inst_addr                                           "0x0115"
#define VO_OSDX_3_inst                                                0x0115
#define VO_OSDX_write_enable1_shift                                   (23)
#define VO_OSDX_end_shift                                             (12)
#define VO_OSDX_write_enable2_shift                                   (11)
#define VO_OSDX_st_shift                                              (0)
#define VO_OSDX_write_enable1_mask                                    (0x00800000)
#define VO_OSDX_end_mask                                              (0x007FF000)
#define VO_OSDX_write_enable2_mask                                    (0x00000800)
#define VO_OSDX_st_mask                                               (0x000007FF)
#define VO_OSDX_write_enable1(data)                                   (0x00800000&((data)<<23))
#define VO_OSDX_end(data)                                             (0x007FF000&((data)<<12))
#define VO_OSDX_write_enable2(data)                                   (0x00000800&((data)<<11))
#define VO_OSDX_st(data)                                              (0x000007FF&(data))
#define VO_OSDX_get_write_enable1(data)                               ((0x00800000&(data))>>23)
#define VO_OSDX_get_end(data)                                         ((0x007FF000&(data))>>12)
#define VO_OSDX_get_write_enable2(data)                               ((0x00000800&(data))>>11)
#define VO_OSDX_get_st(data)                                          (0x000007FF&(data))

#define VO_OSDY_0                                                     0x18005458
#define VO_OSDY_1                                                     0x1800545C
#define VO_OSDY_2                                                     0x18005460
#define VO_OSDY_3                                                     0x18005464
#define VO_OSDY_0_reg_addr                                            "0xB8005458"
#define VO_OSDY_1_reg_addr                                            "0xB800545C"
#define VO_OSDY_2_reg_addr                                            "0xB8005460"
#define VO_OSDY_3_reg_addr                                            "0xB8005464"
#define VO_OSDY_0_reg                                                 0xB8005458
#define VO_OSDY_1_reg                                                 0xB800545C
#define VO_OSDY_2_reg                                                 0xB8005460
#define VO_OSDY_3_reg                                                 0xB8005464
#define VO_OSDY_0_inst_addr                                           "0x0116"
#define VO_OSDY_0_inst                                                0x0116
#define VO_OSDY_1_inst_addr                                           "0x0117"
#define VO_OSDY_1_inst                                                0x0117
#define VO_OSDY_2_inst_addr                                           "0x0118"
#define VO_OSDY_2_inst                                                0x0118
#define VO_OSDY_3_inst_addr                                           "0x0119"
#define VO_OSDY_3_inst                                                0x0119
#define VO_OSDY_write_enable1_shift                                   (26)
#define VO_OSDY_format_shift                                          (24)
#define VO_OSDY_write_enable2_shift                                   (23)
#define VO_OSDY_end_shift                                             (12)
#define VO_OSDY_write_enable3_shift                                   (11)
#define VO_OSDY_st_shift                                              (0)
#define VO_OSDY_write_enable1_mask                                    (0x04000000)
#define VO_OSDY_format_mask                                           (0x03000000)
#define VO_OSDY_write_enable2_mask                                    (0x00800000)
#define VO_OSDY_end_mask                                              (0x007FF000)
#define VO_OSDY_write_enable3_mask                                    (0x00000800)
#define VO_OSDY_st_mask                                               (0x000007FF)
#define VO_OSDY_write_enable1(data)                                   (0x04000000&((data)<<26))
#define VO_OSDY_format(data)                                          (0x03000000&((data)<<24))
#define VO_OSDY_write_enable2(data)                                   (0x00800000&((data)<<23))
#define VO_OSDY_end(data)                                             (0x007FF000&((data)<<12))
#define VO_OSDY_write_enable3(data)                                   (0x00000800&((data)<<11))
#define VO_OSDY_st(data)                                              (0x000007FF&(data))
#define VO_OSDY_get_write_enable1(data)                               ((0x04000000&(data))>>26)
#define VO_OSDY_get_format(data)                                      ((0x03000000&(data))>>24)
#define VO_OSDY_get_write_enable2(data)                               ((0x00800000&(data))>>23)
#define VO_OSDY_get_end(data)                                         ((0x007FF000&(data))>>12)
#define VO_OSDY_get_write_enable3(data)                               ((0x00000800&(data))>>11)
#define VO_OSDY_get_st(data)                                          (0x000007FF&(data))

#define VO_OSDM_0                                                     0x18005468
#define VO_OSDM_1                                                     0x1800546C
#define VO_OSDM_2                                                     0x18005470
#define VO_OSDM_3                                                     0x18005474
#define VO_OSDM_4                                                     0x18005478
#define VO_OSDM_5                                                     0x1800547C
#define VO_OSDM_6                                                     0x18005480
#define VO_OSDM_7                                                     0x18005484
#define VO_OSDM_8                                                     0x18005488
#define VO_OSDM_0_reg_addr                                            "0xB8005468"
#define VO_OSDM_1_reg_addr                                            "0xB800546C"
#define VO_OSDM_2_reg_addr                                            "0xB8005470"
#define VO_OSDM_3_reg_addr                                            "0xB8005474"
#define VO_OSDM_4_reg_addr                                            "0xB8005478"
#define VO_OSDM_5_reg_addr                                            "0xB800547C"
#define VO_OSDM_6_reg_addr                                            "0xB8005480"
#define VO_OSDM_7_reg_addr                                            "0xB8005484"
#define VO_OSDM_8_reg_addr                                            "0xB8005488"
#define VO_OSDM_0_reg                                                 0xB8005468
#define VO_OSDM_1_reg                                                 0xB800546C
#define VO_OSDM_2_reg                                                 0xB8005470
#define VO_OSDM_3_reg                                                 0xB8005474
#define VO_OSDM_4_reg                                                 0xB8005478
#define VO_OSDM_5_reg                                                 0xB800547C
#define VO_OSDM_6_reg                                                 0xB8005480
#define VO_OSDM_7_reg                                                 0xB8005484
#define VO_OSDM_8_reg                                                 0xB8005488
#define VO_OSDM_0_inst_addr                                           "0x011A"
#define VO_OSDM_0_inst                                                0x011A
#define VO_OSDM_1_inst_addr                                           "0x011B"
#define VO_OSDM_1_inst                                                0x011B
#define VO_OSDM_2_inst_addr                                           "0x011C"
#define VO_OSDM_2_inst                                                0x011C
#define VO_OSDM_3_inst_addr                                           "0x011D"
#define VO_OSDM_3_inst                                                0x011D
#define VO_OSDM_4_inst_addr                                           "0x011E"
#define VO_OSDM_4_inst                                                0x011E
#define VO_OSDM_5_inst_addr                                           "0x011F"
#define VO_OSDM_5_inst                                                0x011F
#define VO_OSDM_6_inst_addr                                           "0x0120"
#define VO_OSDM_6_inst                                                0x0120
#define VO_OSDM_7_inst_addr                                           "0x0121"
#define VO_OSDM_7_inst                                                0x0121
#define VO_OSDM_8_inst_addr                                           "0x0122"
#define VO_OSDM_8_inst                                                0x0122
#define VO_OSDM_m_shift                                               (0)
#define VO_OSDM_m_mask                                                (0x000003FF)
#define VO_OSDM_m(data)                                               (0x000003FF&(data))
#define VO_OSDM_get_m(data)                                           (0x000003FF&(data))

#define VO_OSDA                                                       0x1800548C
#define VO_OSDA_reg_addr                                              "0xB800548C"
#define VO_OSDA_reg                                                   0xB800548C
#define VO_OSDA_inst_addr                                             "0x0123"
#define VO_OSDA_inst                                                  0x0123
#define VO_OSDA_a2_shift                                              (16)
#define VO_OSDA_a1_shift                                              (8)
#define VO_OSDA_a0_shift                                              (0)
#define VO_OSDA_a2_mask                                               (0x00FF0000)
#define VO_OSDA_a1_mask                                               (0x0000FF00)
#define VO_OSDA_a0_mask                                               (0x000000FF)
#define VO_OSDA_a2(data)                                              (0x00FF0000&((data)<<16))
#define VO_OSDA_a1(data)                                              (0x0000FF00&((data)<<8))
#define VO_OSDA_a0(data)                                              (0x000000FF&(data))
#define VO_OSDA_get_a2(data)                                          ((0x00FF0000&(data))>>16)
#define VO_OSDA_get_a1(data)                                          ((0x0000FF00&(data))>>8)
#define VO_OSDA_get_a0(data)                                          (0x000000FF&(data))

#define VO_CURSOR                                                     0x18005490
#define VO_CURSOR_reg_addr                                            "0xB8005490"
#define VO_CURSOR_reg                                                 0xB8005490
#define VO_CURSOR_inst_addr                                           "0x0124"
#define VO_CURSOR_inst                                                0x0124
#define VO_CURSOR_write_enable1_shift                                 (16)
#define VO_CURSOR_const_alpha_shift                                   (12)
#define VO_CURSOR_write_enable2_shift                                 (11)
#define VO_CURSOR_key_shift                                           (9)
#define VO_CURSOR_write_enable3_shift                                 (8)
#define VO_CURSOR_keyen_shift                                         (7)
#define VO_CURSOR_write_enable4_shift                                 (6)
#define VO_CURSOR_lpf_shift                                           (4)
#define VO_CURSOR_write_enable5_shift                                 (3)
#define VO_CURSOR_load_shift                                          (2)
#define VO_CURSOR_write_enable6_shift                                 (1)
#define VO_CURSOR_en_shift                                            (0)
#define VO_CURSOR_write_enable1_mask                                  (0x00010000)
#define VO_CURSOR_const_alpha_mask                                    (0x0000F000)
#define VO_CURSOR_write_enable2_mask                                  (0x00000800)
#define VO_CURSOR_key_mask                                            (0x00000600)
#define VO_CURSOR_write_enable3_mask                                  (0x00000100)
#define VO_CURSOR_keyen_mask                                          (0x00000080)
#define VO_CURSOR_write_enable4_mask                                  (0x00000040)
#define VO_CURSOR_lpf_mask                                            (0x00000030)
#define VO_CURSOR_write_enable5_mask                                  (0x00000008)
#define VO_CURSOR_load_mask                                           (0x00000004)
#define VO_CURSOR_write_enable6_mask                                  (0x00000002)
#define VO_CURSOR_en_mask                                             (0x00000001)
#define VO_CURSOR_write_enable1(data)                                 (0x00010000&((data)<<16))
#define VO_CURSOR_const_alpha(data)                                   (0x0000F000&((data)<<12))
#define VO_CURSOR_write_enable2(data)                                 (0x00000800&((data)<<11))
#define VO_CURSOR_key(data)                                           (0x00000600&((data)<<9))
#define VO_CURSOR_write_enable3(data)                                 (0x00000100&((data)<<8))
#define VO_CURSOR_keyen(data)                                         (0x00000080&((data)<<7))
#define VO_CURSOR_write_enable4(data)                                 (0x00000040&((data)<<6))
#define VO_CURSOR_lpf(data)                                           (0x00000030&((data)<<4))
#define VO_CURSOR_write_enable5(data)                                 (0x00000008&((data)<<3))
#define VO_CURSOR_load(data)                                          (0x00000004&((data)<<2))
#define VO_CURSOR_write_enable6(data)                                 (0x00000002&((data)<<1))
#define VO_CURSOR_en(data)                                            (0x00000001&(data))
#define VO_CURSOR_get_write_enable1(data)                             ((0x00010000&(data))>>16)
#define VO_CURSOR_get_const_alpha(data)                               ((0x0000F000&(data))>>12)
#define VO_CURSOR_get_write_enable2(data)                             ((0x00000800&(data))>>11)
#define VO_CURSOR_get_key(data)                                       ((0x00000600&(data))>>9)
#define VO_CURSOR_get_write_enable3(data)                             ((0x00000100&(data))>>8)
#define VO_CURSOR_get_keyen(data)                                     ((0x00000080&(data))>>7)
#define VO_CURSOR_get_write_enable4(data)                             ((0x00000040&(data))>>6)
#define VO_CURSOR_get_lpf(data)                                       ((0x00000030&(data))>>4)
#define VO_CURSOR_get_write_enable5(data)                             ((0x00000008&(data))>>3)
#define VO_CURSOR_get_load(data)                                      ((0x00000004&(data))>>2)
#define VO_CURSOR_get_write_enable6(data)                             ((0x00000002&(data))>>1)
#define VO_CURSOR_get_en(data)                                        (0x00000001&(data))

#define VO_CURSORST                                                   0x18005494
#define VO_CURSORST_reg_addr                                          "0xB8005494"
#define VO_CURSORST_reg                                               0xB8005494
#define VO_CURSORST_inst_addr                                         "0x0125"
#define VO_CURSORST_inst                                              0x0125
#define VO_CURSORST_write_enable1_shift                               (23)
#define VO_CURSORST_yst_shift                                         (12)
#define VO_CURSORST_write_enable2_shift                               (11)
#define VO_CURSORST_xst_shift                                         (0)
#define VO_CURSORST_write_enable1_mask                                (0x00800000)
#define VO_CURSORST_yst_mask                                          (0x007FF000)
#define VO_CURSORST_write_enable2_mask                                (0x00000800)
#define VO_CURSORST_xst_mask                                          (0x000007FF)
#define VO_CURSORST_write_enable1(data)                               (0x00800000&((data)<<23))
#define VO_CURSORST_yst(data)                                         (0x007FF000&((data)<<12))
#define VO_CURSORST_write_enable2(data)                               (0x00000800&((data)<<11))
#define VO_CURSORST_xst(data)                                         (0x000007FF&(data))
#define VO_CURSORST_get_write_enable1(data)                           ((0x00800000&(data))>>23)
#define VO_CURSORST_get_yst(data)                                     ((0x007FF000&(data))>>12)
#define VO_CURSORST_get_write_enable2(data)                           ((0x00000800&(data))>>11)
#define VO_CURSORST_get_xst(data)                                     (0x000007FF&(data))

#define VO_CURCLUT_0                                                  0x18005498
#define VO_CURCLUT_1                                                  0x1800549C
#define VO_CURCLUT_2                                                  0x180054A0
#define VO_CURCLUT_3                                                  0x180054A4
#define VO_CURCLUT_0_reg_addr                                         "0xB8005498"
#define VO_CURCLUT_1_reg_addr                                         "0xB800549C"
#define VO_CURCLUT_2_reg_addr                                         "0xB80054A0"
#define VO_CURCLUT_3_reg_addr                                         "0xB80054A4"
#define VO_CURCLUT_0_reg                                              0xB8005498
#define VO_CURCLUT_1_reg                                              0xB800549C
#define VO_CURCLUT_2_reg                                              0xB80054A0
#define VO_CURCLUT_3_reg                                              0xB80054A4
#define VO_CURCLUT_0_inst_addr                                        "0x0126"
#define VO_CURCLUT_0_inst                                             0x0126
#define VO_CURCLUT_1_inst_addr                                        "0x0127"
#define VO_CURCLUT_1_inst                                             0x0127
#define VO_CURCLUT_2_inst_addr                                        "0x0128"
#define VO_CURCLUT_2_inst                                             0x0128
#define VO_CURCLUT_3_inst_addr                                        "0x0129"
#define VO_CURCLUT_3_inst                                             0x0129
#define VO_CURCLUT_cr_shift                                           (16)
#define VO_CURCLUT_cb_shift                                           (8)
#define VO_CURCLUT_y_shift                                            (0)
#define VO_CURCLUT_cr_mask                                            (0x00FF0000)
#define VO_CURCLUT_cb_mask                                            (0x0000FF00)
#define VO_CURCLUT_y_mask                                             (0x000000FF)
#define VO_CURCLUT_cr(data)                                           (0x00FF0000&((data)<<16))
#define VO_CURCLUT_cb(data)                                           (0x0000FF00&((data)<<8))
#define VO_CURCLUT_y(data)                                            (0x000000FF&(data))
#define VO_CURCLUT_get_cr(data)                                       ((0x00FF0000&(data))>>16)
#define VO_CURCLUT_get_cb(data)                                       ((0x0000FF00&(data))>>8)
#define VO_CURCLUT_get_y(data)                                        (0x000000FF&(data))

#define VO_Mix                                                        0x180054A8
#define VO_Mix_reg_addr                                               "0xB80054A8"
#define VO_Mix_reg                                                    0xB80054A8
#define VO_Mix_inst_addr                                              "0x012A"
#define VO_Mix_inst                                                   0x012A
#define VO_Mix_v1boren_shift                                          (5)
#define VO_Mix_v2boren_shift                                          (4)
#define VO_Mix_v1en_shift                                             (3)
#define VO_Mix_v2en_shift                                             (2)
#define VO_Mix_v2sub_shift                                            (1)
#define VO_Mix_write_data_shift                                       (0)
#define VO_Mix_v1boren_mask                                           (0x00000020)
#define VO_Mix_v2boren_mask                                           (0x00000010)
#define VO_Mix_v1en_mask                                              (0x00000008)
#define VO_Mix_v2en_mask                                              (0x00000004)
#define VO_Mix_v2sub_mask                                             (0x00000002)
#define VO_Mix_write_data_mask                                        (0x00000001)
#define VO_Mix_v1boren(data)                                          (0x00000020&((data)<<5))
#define VO_Mix_v2boren(data)                                          (0x00000010&((data)<<4))
#define VO_Mix_v1en(data)                                             (0x00000008&((data)<<3))
#define VO_Mix_v2en(data)                                             (0x00000004&((data)<<2))
#define VO_Mix_v2sub(data)                                            (0x00000002&((data)<<1))
#define VO_Mix_write_data(data)                                       (0x00000001&(data))
#define VO_Mix_get_v1boren(data)                                      ((0x00000020&(data))>>5)
#define VO_Mix_get_v2boren(data)                                      ((0x00000010&(data))>>4)
#define VO_Mix_get_v1en(data)                                         ((0x00000008&(data))>>3)
#define VO_Mix_get_v2en(data)                                         ((0x00000004&(data))>>2)
#define VO_Mix_get_v2sub(data)                                        ((0x00000002&(data))>>1)
#define VO_Mix_get_write_data(data)                                   (0x00000001&(data))

#define VO_V2ALPHA                                                    0x180054AC
#define VO_V2ALPHA_reg_addr                                           "0xB80054AC"
#define VO_V2ALPHA_reg                                                0xB80054AC
#define VO_V2ALPHA_inst_addr                                          "0x012B"
#define VO_V2ALPHA_inst                                               0x012B
#define VO_V2ALPHA_a_shift                                            (0)
#define VO_V2ALPHA_a_mask                                             (0x0000000F)
#define VO_V2ALPHA_a(data)                                            (0x0000000F&(data))
#define VO_V2ALPHA_get_a(data)                                        (0x0000000F&(data))

#define VO_MixWindow                                                  0x180054B0
#define VO_MixWindow_reg_addr                                         "0xB80054B0"
#define VO_MixWindow_reg                                              0xB80054B0
#define VO_MixWindow_inst_addr                                        "0x012C"
#define VO_MixWindow_inst                                             0x012C
#define VO_MixWindow_write_enable1_shift                              (23)
#define VO_MixWindow_yend_shift                                       (12)
#define VO_MixWindow_write_enable2_shift                              (11)
#define VO_MixWindow_xend_shift                                       (0)
#define VO_MixWindow_write_enable1_mask                               (0x00800000)
#define VO_MixWindow_yend_mask                                        (0x007FF000)
#define VO_MixWindow_write_enable2_mask                               (0x00000800)
#define VO_MixWindow_xend_mask                                        (0x000007FF)
#define VO_MixWindow_write_enable1(data)                              (0x00800000&((data)<<23))
#define VO_MixWindow_yend(data)                                       (0x007FF000&((data)<<12))
#define VO_MixWindow_write_enable2(data)                              (0x00000800&((data)<<11))
#define VO_MixWindow_xend(data)                                       (0x000007FF&(data))
#define VO_MixWindow_get_write_enable1(data)                          ((0x00800000&(data))>>23)
#define VO_MixWindow_get_yend(data)                                   ((0x007FF000&(data))>>12)
#define VO_MixWindow_get_write_enable2(data)                          ((0x00000800&(data))>>11)
#define VO_MixWindow_get_xend(data)                                   (0x000007FF&(data))

#define VO_MixBG                                                      0x180054B4
#define VO_MixBG_reg_addr                                             "0xB80054B4"
#define VO_MixBG_reg                                                  0xB80054B4
#define VO_MixBG_inst_addr                                            "0x012D"
#define VO_MixBG_inst                                                 0x012D
#define VO_MixBG_write_enable1_shift                                  (28)
#define VO_MixBG_en_shift                                             (27)
#define VO_MixBG_write_enable2_shift                                  (26)
#define VO_MixBG_cr_shift                                             (18)
#define VO_MixBG_write_enable3_shift                                  (17)
#define VO_MixBG_cb_shift                                             (9)
#define VO_MixBG_write_enable4_shift                                  (8)
#define VO_MixBG_y_shift                                              (0)
#define VO_MixBG_write_enable1_mask                                   (0x10000000)
#define VO_MixBG_en_mask                                              (0x08000000)
#define VO_MixBG_write_enable2_mask                                   (0x04000000)
#define VO_MixBG_cr_mask                                              (0x03FC0000)
#define VO_MixBG_write_enable3_mask                                   (0x00020000)
#define VO_MixBG_cb_mask                                              (0x0001FE00)
#define VO_MixBG_write_enable4_mask                                   (0x00000100)
#define VO_MixBG_y_mask                                               (0x000000FF)
#define VO_MixBG_write_enable1(data)                                  (0x10000000&((data)<<28))
#define VO_MixBG_en(data)                                             (0x08000000&((data)<<27))
#define VO_MixBG_write_enable2(data)                                  (0x04000000&((data)<<26))
#define VO_MixBG_cr(data)                                             (0x03FC0000&((data)<<18))
#define VO_MixBG_write_enable3(data)                                  (0x00020000&((data)<<17))
#define VO_MixBG_cb(data)                                             (0x0001FE00&((data)<<9))
#define VO_MixBG_write_enable4(data)                                  (0x00000100&((data)<<8))
#define VO_MixBG_y(data)                                              (0x000000FF&(data))
#define VO_MixBG_get_write_enable1(data)                              ((0x10000000&(data))>>28)
#define VO_MixBG_get_en(data)                                         ((0x08000000&(data))>>27)
#define VO_MixBG_get_write_enable2(data)                              ((0x04000000&(data))>>26)
#define VO_MixBG_get_cr(data)                                         ((0x03FC0000&(data))>>18)
#define VO_MixBG_get_write_enable3(data)                              ((0x00020000&(data))>>17)
#define VO_MixBG_get_cb(data)                                         ((0x0001FE00&(data))>>9)
#define VO_MixBG_get_write_enable4(data)                              ((0x00000100&(data))>>8)
#define VO_MixBG_get_y(data)                                          (0x000000FF&(data))

#define VO_MixV1X                                                     0x180054B8
#define VO_MixV1X_reg_addr                                            "0xB80054B8"
#define VO_MixV1X_reg                                                 0xB80054B8
#define VO_MixV1X_inst_addr                                           "0x012E"
#define VO_MixV1X_inst                                                0x012E
#define VO_MixV1X_write_enable1_shift                                 (23)
#define VO_MixV1X_end_shift                                           (12)
#define VO_MixV1X_write_enable2_shift                                 (11)
#define VO_MixV1X_st_shift                                            (0)
#define VO_MixV1X_write_enable1_mask                                  (0x00800000)
#define VO_MixV1X_end_mask                                            (0x007FF000)
#define VO_MixV1X_write_enable2_mask                                  (0x00000800)
#define VO_MixV1X_st_mask                                             (0x000007FF)
#define VO_MixV1X_write_enable1(data)                                 (0x00800000&((data)<<23))
#define VO_MixV1X_end(data)                                           (0x007FF000&((data)<<12))
#define VO_MixV1X_write_enable2(data)                                 (0x00000800&((data)<<11))
#define VO_MixV1X_st(data)                                            (0x000007FF&(data))
#define VO_MixV1X_get_write_enable1(data)                             ((0x00800000&(data))>>23)
#define VO_MixV1X_get_end(data)                                       ((0x007FF000&(data))>>12)
#define VO_MixV1X_get_write_enable2(data)                             ((0x00000800&(data))>>11)
#define VO_MixV1X_get_st(data)                                        (0x000007FF&(data))

#define VO_MixV1Y                                                     0x180054BC
#define VO_MixV1Y_reg_addr                                            "0xB80054BC"
#define VO_MixV1Y_reg                                                 0xB80054BC
#define VO_MixV1Y_inst_addr                                           "0x012F"
#define VO_MixV1Y_inst                                                0x012F
#define VO_MixV1Y_write_enable1_shift                                 (23)
#define VO_MixV1Y_end_shift                                           (12)
#define VO_MixV1Y_write_enable2_shift                                 (11)
#define VO_MixV1Y_st_shift                                            (0)
#define VO_MixV1Y_write_enable1_mask                                  (0x00800000)
#define VO_MixV1Y_end_mask                                            (0x007FF000)
#define VO_MixV1Y_write_enable2_mask                                  (0x00000800)
#define VO_MixV1Y_st_mask                                             (0x000007FF)
#define VO_MixV1Y_write_enable1(data)                                 (0x00800000&((data)<<23))
#define VO_MixV1Y_end(data)                                           (0x007FF000&((data)<<12))
#define VO_MixV1Y_write_enable2(data)                                 (0x00000800&((data)<<11))
#define VO_MixV1Y_st(data)                                            (0x000007FF&(data))
#define VO_MixV1Y_get_write_enable1(data)                             ((0x00800000&(data))>>23)
#define VO_MixV1Y_get_end(data)                                       ((0x007FF000&(data))>>12)
#define VO_MixV1Y_get_write_enable2(data)                             ((0x00000800&(data))>>11)
#define VO_MixV1Y_get_st(data)                                        (0x000007FF&(data))

#define VO_MixV2X                                                     0x180054C0
#define VO_MixV2X_reg_addr                                            "0xB80054C0"
#define VO_MixV2X_reg                                                 0xB80054C0
#define VO_MixV2X_inst_addr                                           "0x0130"
#define VO_MixV2X_inst                                                0x0130
#define VO_MixV2X_write_enable1_shift                                 (23)
#define VO_MixV2X_end_shift                                           (12)
#define VO_MixV2X_write_enable2_shift                                 (11)
#define VO_MixV2X_st_shift                                            (0)
#define VO_MixV2X_write_enable1_mask                                  (0x00800000)
#define VO_MixV2X_end_mask                                            (0x007FF000)
#define VO_MixV2X_write_enable2_mask                                  (0x00000800)
#define VO_MixV2X_st_mask                                             (0x000007FF)
#define VO_MixV2X_write_enable1(data)                                 (0x00800000&((data)<<23))
#define VO_MixV2X_end(data)                                           (0x007FF000&((data)<<12))
#define VO_MixV2X_write_enable2(data)                                 (0x00000800&((data)<<11))
#define VO_MixV2X_st(data)                                            (0x000007FF&(data))
#define VO_MixV2X_get_write_enable1(data)                             ((0x00800000&(data))>>23)
#define VO_MixV2X_get_end(data)                                       ((0x007FF000&(data))>>12)
#define VO_MixV2X_get_write_enable2(data)                             ((0x00000800&(data))>>11)
#define VO_MixV2X_get_st(data)                                        (0x000007FF&(data))

#define VO_MixV2Y                                                     0x180054C4
#define VO_MixV2Y_reg_addr                                            "0xB80054C4"
#define VO_MixV2Y_reg                                                 0xB80054C4
#define VO_MixV2Y_inst_addr                                           "0x0131"
#define VO_MixV2Y_inst                                                0x0131
#define VO_MixV2Y_write_enable1_shift                                 (23)
#define VO_MixV2Y_end_shift                                           (12)
#define VO_MixV2Y_write_enable2_shift                                 (11)
#define VO_MixV2Y_st_shift                                            (0)
#define VO_MixV2Y_write_enable1_mask                                  (0x00800000)
#define VO_MixV2Y_end_mask                                            (0x007FF000)
#define VO_MixV2Y_write_enable2_mask                                  (0x00000800)
#define VO_MixV2Y_st_mask                                             (0x000007FF)
#define VO_MixV2Y_write_enable1(data)                                 (0x00800000&((data)<<23))
#define VO_MixV2Y_end(data)                                           (0x007FF000&((data)<<12))
#define VO_MixV2Y_write_enable2(data)                                 (0x00000800&((data)<<11))
#define VO_MixV2Y_st(data)                                            (0x000007FF&(data))
#define VO_MixV2Y_get_write_enable1(data)                             ((0x00800000&(data))>>23)
#define VO_MixV2Y_get_end(data)                                       ((0x007FF000&(data))>>12)
#define VO_MixV2Y_get_write_enable2(data)                             ((0x00000800&(data))>>11)
#define VO_MixV2Y_get_st(data)                                        (0x000007FF&(data))

#define VO_MixV1BX                                                    0x180054C8
#define VO_MixV1BX_reg_addr                                           "0xB80054C8"
#define VO_MixV1BX_reg                                                0xB80054C8
#define VO_MixV1BX_inst_addr                                          "0x0132"
#define VO_MixV1BX_inst                                               0x0132
#define VO_MixV1BX_write_enable1_shift                                (23)
#define VO_MixV1BX_end_shift                                          (12)
#define VO_MixV1BX_write_enable2_shift                                (11)
#define VO_MixV1BX_st_shift                                           (0)
#define VO_MixV1BX_write_enable1_mask                                 (0x00800000)
#define VO_MixV1BX_end_mask                                           (0x007FF000)
#define VO_MixV1BX_write_enable2_mask                                 (0x00000800)
#define VO_MixV1BX_st_mask                                            (0x000007FF)
#define VO_MixV1BX_write_enable1(data)                                (0x00800000&((data)<<23))
#define VO_MixV1BX_end(data)                                          (0x007FF000&((data)<<12))
#define VO_MixV1BX_write_enable2(data)                                (0x00000800&((data)<<11))
#define VO_MixV1BX_st(data)                                           (0x000007FF&(data))
#define VO_MixV1BX_get_write_enable1(data)                            ((0x00800000&(data))>>23)
#define VO_MixV1BX_get_end(data)                                      ((0x007FF000&(data))>>12)
#define VO_MixV1BX_get_write_enable2(data)                            ((0x00000800&(data))>>11)
#define VO_MixV1BX_get_st(data)                                       (0x000007FF&(data))

#define VO_MixV1BY                                                    0x180054CC
#define VO_MixV1BY_reg_addr                                           "0xB80054CC"
#define VO_MixV1BY_reg                                                0xB80054CC
#define VO_MixV1BY_inst_addr                                          "0x0133"
#define VO_MixV1BY_inst                                               0x0133
#define VO_MixV1BY_write_enable1_shift                                (23)
#define VO_MixV1BY_end_shift                                          (12)
#define VO_MixV1BY_write_enable2_shift                                (11)
#define VO_MixV1BY_st_shift                                           (0)
#define VO_MixV1BY_write_enable1_mask                                 (0x00800000)
#define VO_MixV1BY_end_mask                                           (0x007FF000)
#define VO_MixV1BY_write_enable2_mask                                 (0x00000800)
#define VO_MixV1BY_st_mask                                            (0x000007FF)
#define VO_MixV1BY_write_enable1(data)                                (0x00800000&((data)<<23))
#define VO_MixV1BY_end(data)                                          (0x007FF000&((data)<<12))
#define VO_MixV1BY_write_enable2(data)                                (0x00000800&((data)<<11))
#define VO_MixV1BY_st(data)                                           (0x000007FF&(data))
#define VO_MixV1BY_get_write_enable1(data)                            ((0x00800000&(data))>>23)
#define VO_MixV1BY_get_end(data)                                      ((0x007FF000&(data))>>12)
#define VO_MixV1BY_get_write_enable2(data)                            ((0x00000800&(data))>>11)
#define VO_MixV1BY_get_st(data)                                       (0x000007FF&(data))

#define VO_MixV2BX                                                    0x180054D0
#define VO_MixV2BX_reg_addr                                           "0xB80054D0"
#define VO_MixV2BX_reg                                                0xB80054D0
#define VO_MixV2BX_inst_addr                                          "0x0134"
#define VO_MixV2BX_inst                                               0x0134
#define VO_MixV2BX_write_enable1_shift                                (23)
#define VO_MixV2BX_end_shift                                          (12)
#define VO_MixV2BX_write_enable2_shift                                (11)
#define VO_MixV2BX_st_shift                                           (0)
#define VO_MixV2BX_write_enable1_mask                                 (0x00800000)
#define VO_MixV2BX_end_mask                                           (0x007FF000)
#define VO_MixV2BX_write_enable2_mask                                 (0x00000800)
#define VO_MixV2BX_st_mask                                            (0x000007FF)
#define VO_MixV2BX_write_enable1(data)                                (0x00800000&((data)<<23))
#define VO_MixV2BX_end(data)                                          (0x007FF000&((data)<<12))
#define VO_MixV2BX_write_enable2(data)                                (0x00000800&((data)<<11))
#define VO_MixV2BX_st(data)                                           (0x000007FF&(data))
#define VO_MixV2BX_get_write_enable1(data)                            ((0x00800000&(data))>>23)
#define VO_MixV2BX_get_end(data)                                      ((0x007FF000&(data))>>12)
#define VO_MixV2BX_get_write_enable2(data)                            ((0x00000800&(data))>>11)
#define VO_MixV2BX_get_st(data)                                       (0x000007FF&(data))

#define VO_MixV2BY                                                    0x180054D4
#define VO_MixV2BY_reg_addr                                           "0xB80054D4"
#define VO_MixV2BY_reg                                                0xB80054D4
#define VO_MixV2BY_inst_addr                                          "0x0135"
#define VO_MixV2BY_inst                                               0x0135
#define VO_MixV2BY_write_enable1_shift                                (23)
#define VO_MixV2BY_end_shift                                          (12)
#define VO_MixV2BY_write_enable2_shift                                (11)
#define VO_MixV2BY_st_shift                                           (0)
#define VO_MixV2BY_write_enable1_mask                                 (0x00800000)
#define VO_MixV2BY_end_mask                                           (0x007FF000)
#define VO_MixV2BY_write_enable2_mask                                 (0x00000800)
#define VO_MixV2BY_st_mask                                            (0x000007FF)
#define VO_MixV2BY_write_enable1(data)                                (0x00800000&((data)<<23))
#define VO_MixV2BY_end(data)                                          (0x007FF000&((data)<<12))
#define VO_MixV2BY_write_enable2(data)                                (0x00000800&((data)<<11))
#define VO_MixV2BY_st(data)                                           (0x000007FF&(data))
#define VO_MixV2BY_get_write_enable1(data)                            ((0x00800000&(data))>>23)
#define VO_MixV2BY_get_end(data)                                      ((0x007FF000&(data))>>12)
#define VO_MixV2BY_get_write_enable2(data)                            ((0x00000800&(data))>>11)
#define VO_MixV2BY_get_st(data)                                       (0x000007FF&(data))

#define VO_MixV1BC                                                    0x180054D8
#define VO_MixV1BC_reg_addr                                           "0xB80054D8"
#define VO_MixV1BC_reg                                                0xB80054D8
#define VO_MixV1BC_inst_addr                                          "0x0136"
#define VO_MixV1BC_inst                                               0x0136
#define VO_MixV1BC_write_enable1_shift                                (26)
#define VO_MixV1BC_cr_shift                                           (18)
#define VO_MixV1BC_write_enable2_shift                                (17)
#define VO_MixV1BC_cb_shift                                           (9)
#define VO_MixV1BC_write_enable3_shift                                (8)
#define VO_MixV1BC_y_shift                                            (0)
#define VO_MixV1BC_write_enable1_mask                                 (0x04000000)
#define VO_MixV1BC_cr_mask                                            (0x03FC0000)
#define VO_MixV1BC_write_enable2_mask                                 (0x00020000)
#define VO_MixV1BC_cb_mask                                            (0x0001FE00)
#define VO_MixV1BC_write_enable3_mask                                 (0x00000100)
#define VO_MixV1BC_y_mask                                             (0x000000FF)
#define VO_MixV1BC_write_enable1(data)                                (0x04000000&((data)<<26))
#define VO_MixV1BC_cr(data)                                           (0x03FC0000&((data)<<18))
#define VO_MixV1BC_write_enable2(data)                                (0x00020000&((data)<<17))
#define VO_MixV1BC_cb(data)                                           (0x0001FE00&((data)<<9))
#define VO_MixV1BC_write_enable3(data)                                (0x00000100&((data)<<8))
#define VO_MixV1BC_y(data)                                            (0x000000FF&(data))
#define VO_MixV1BC_get_write_enable1(data)                            ((0x04000000&(data))>>26)
#define VO_MixV1BC_get_cr(data)                                       ((0x03FC0000&(data))>>18)
#define VO_MixV1BC_get_write_enable2(data)                            ((0x00020000&(data))>>17)
#define VO_MixV1BC_get_cb(data)                                       ((0x0001FE00&(data))>>9)
#define VO_MixV1BC_get_write_enable3(data)                            ((0x00000100&(data))>>8)
#define VO_MixV1BC_get_y(data)                                        (0x000000FF&(data))

#define VO_MixV2BC                                                    0x180054DC
#define VO_MixV2BC_reg_addr                                           "0xB80054DC"
#define VO_MixV2BC_reg                                                0xB80054DC
#define VO_MixV2BC_inst_addr                                          "0x0137"
#define VO_MixV2BC_inst                                               0x0137
#define VO_MixV2BC_write_enable1_shift                                (26)
#define VO_MixV2BC_cr_shift                                           (18)
#define VO_MixV2BC_write_enable2_shift                                (17)
#define VO_MixV2BC_cb_shift                                           (9)
#define VO_MixV2BC_write_enable3_shift                                (8)
#define VO_MixV2BC_y_shift                                            (0)
#define VO_MixV2BC_write_enable1_mask                                 (0x04000000)
#define VO_MixV2BC_cr_mask                                            (0x03FC0000)
#define VO_MixV2BC_write_enable2_mask                                 (0x00020000)
#define VO_MixV2BC_cb_mask                                            (0x0001FE00)
#define VO_MixV2BC_write_enable3_mask                                 (0x00000100)
#define VO_MixV2BC_y_mask                                             (0x000000FF)
#define VO_MixV2BC_write_enable1(data)                                (0x04000000&((data)<<26))
#define VO_MixV2BC_cr(data)                                           (0x03FC0000&((data)<<18))
#define VO_MixV2BC_write_enable2(data)                                (0x00020000&((data)<<17))
#define VO_MixV2BC_cb(data)                                           (0x0001FE00&((data)<<9))
#define VO_MixV2BC_write_enable3(data)                                (0x00000100&((data)<<8))
#define VO_MixV2BC_y(data)                                            (0x000000FF&(data))
#define VO_MixV2BC_get_write_enable1(data)                            ((0x04000000&(data))>>26)
#define VO_MixV2BC_get_cr(data)                                       ((0x03FC0000&(data))>>18)
#define VO_MixV2BC_get_write_enable2(data)                            ((0x00020000&(data))>>17)
#define VO_MixV2BC_get_cb(data)                                       ((0x0001FE00&(data))>>9)
#define VO_MixV2BC_get_write_enable3(data)                            ((0x00000100&(data))>>8)
#define VO_MixV2BC_get_y(data)                                        (0x000000FF&(data))

#define VO_PeakEn                                                     0x180054E0
#define VO_PeakEn_reg_addr                                            "0xB80054E0"
#define VO_PeakEn_reg                                                 0xB80054E0
#define VO_PeakEn_inst_addr                                           "0x0138"
#define VO_PeakEn_inst                                                0x0138
#define VO_PeakEn_en_shift                                            (0)
#define VO_PeakEn_en_mask                                             (0x00000001)
#define VO_PeakEn_en(data)                                            (0x00000001&(data))
#define VO_PeakEn_get_en(data)                                        (0x00000001&(data))

#define VO_PeakC                                                      0x180054E4
#define VO_PeakC_reg_addr                                             "0xB80054E4"
#define VO_PeakC_reg                                                  0xB80054E4
#define VO_PeakC_inst_addr                                            "0x0139"
#define VO_PeakC_inst                                                 0x0139
#define VO_PeakC_lv_shift                                             (24)
#define VO_PeakC_c2_shift                                             (16)
#define VO_PeakC_c1_shift                                             (8)
#define VO_PeakC_c0_shift                                             (0)
#define VO_PeakC_lv_mask                                              (0x1F000000)
#define VO_PeakC_c2_mask                                              (0x00FF0000)
#define VO_PeakC_c1_mask                                              (0x0000FF00)
#define VO_PeakC_c0_mask                                              (0x000000FF)
#define VO_PeakC_lv(data)                                             (0x1F000000&((data)<<24))
#define VO_PeakC_c2(data)                                             (0x00FF0000&((data)<<16))
#define VO_PeakC_c1(data)                                             (0x0000FF00&((data)<<8))
#define VO_PeakC_c0(data)                                             (0x000000FF&(data))
#define VO_PeakC_get_lv(data)                                         ((0x1F000000&(data))>>24)
#define VO_PeakC_get_c2(data)                                         ((0x00FF0000&(data))>>16)
#define VO_PeakC_get_c1(data)                                         ((0x0000FF00&(data))>>8)
#define VO_PeakC_get_c0(data)                                         (0x000000FF&(data))

#define VO_ContrastM0                                                 0x180054E8
#define VO_ContrastM0_reg_addr                                        "0xB80054E8"
#define VO_ContrastM0_reg                                             0xB80054E8
#define VO_ContrastM0_inst_addr                                       "0x013A"
#define VO_ContrastM0_inst                                            0x013A
#define VO_ContrastM0_write_enable1_shift                             (25)
#define VO_ContrastM0_m10_shift                                       (13)
#define VO_ContrastM0_write_enable2_shift                             (12)
#define VO_ContrastM0_m00_shift                                       (0)
#define VO_ContrastM0_write_enable1_mask                              (0x02000000)
#define VO_ContrastM0_m10_mask                                        (0x01FFE000)
#define VO_ContrastM0_write_enable2_mask                              (0x00001000)
#define VO_ContrastM0_m00_mask                                        (0x00000FFF)
#define VO_ContrastM0_write_enable1(data)                             (0x02000000&((data)<<25))
#define VO_ContrastM0_m10(data)                                       (0x01FFE000&((data)<<13))
#define VO_ContrastM0_write_enable2(data)                             (0x00001000&((data)<<12))
#define VO_ContrastM0_m00(data)                                       (0x00000FFF&(data))
#define VO_ContrastM0_get_write_enable1(data)                         ((0x02000000&(data))>>25)
#define VO_ContrastM0_get_m10(data)                                   ((0x01FFE000&(data))>>13)
#define VO_ContrastM0_get_write_enable2(data)                         ((0x00001000&(data))>>12)
#define VO_ContrastM0_get_m00(data)                                   (0x00000FFF&(data))

#define VO_ContrastM1                                                 0x180054EC
#define VO_ContrastM1_reg_addr                                        "0xB80054EC"
#define VO_ContrastM1_reg                                             0xB80054EC
#define VO_ContrastM1_inst_addr                                       "0x013B"
#define VO_ContrastM1_inst                                            0x013B
#define VO_ContrastM1_write_enable1_shift                             (25)
#define VO_ContrastM1_m01_shift                                       (13)
#define VO_ContrastM1_write_enable2_shift                             (12)
#define VO_ContrastM1_m20_shift                                       (0)
#define VO_ContrastM1_write_enable1_mask                              (0x02000000)
#define VO_ContrastM1_m01_mask                                        (0x01FFE000)
#define VO_ContrastM1_write_enable2_mask                              (0x00001000)
#define VO_ContrastM1_m20_mask                                        (0x00000FFF)
#define VO_ContrastM1_write_enable1(data)                             (0x02000000&((data)<<25))
#define VO_ContrastM1_m01(data)                                       (0x01FFE000&((data)<<13))
#define VO_ContrastM1_write_enable2(data)                             (0x00001000&((data)<<12))
#define VO_ContrastM1_m20(data)                                       (0x00000FFF&(data))
#define VO_ContrastM1_get_write_enable1(data)                         ((0x02000000&(data))>>25)
#define VO_ContrastM1_get_m01(data)                                   ((0x01FFE000&(data))>>13)
#define VO_ContrastM1_get_write_enable2(data)                         ((0x00001000&(data))>>12)
#define VO_ContrastM1_get_m20(data)                                   (0x00000FFF&(data))

#define VO_ContrastM2                                                 0x180054F0
#define VO_ContrastM2_reg_addr                                        "0xB80054F0"
#define VO_ContrastM2_reg                                             0xB80054F0
#define VO_ContrastM2_inst_addr                                       "0x013C"
#define VO_ContrastM2_inst                                            0x013C
#define VO_ContrastM2_write_enable1_shift                             (25)
#define VO_ContrastM2_m21_shift                                       (13)
#define VO_ContrastM2_write_enable2_shift                             (12)
#define VO_ContrastM2_m11_shift                                       (0)
#define VO_ContrastM2_write_enable1_mask                              (0x02000000)
#define VO_ContrastM2_m21_mask                                        (0x01FFE000)
#define VO_ContrastM2_write_enable2_mask                              (0x00001000)
#define VO_ContrastM2_m11_mask                                        (0x00000FFF)
#define VO_ContrastM2_write_enable1(data)                             (0x02000000&((data)<<25))
#define VO_ContrastM2_m21(data)                                       (0x01FFE000&((data)<<13))
#define VO_ContrastM2_write_enable2(data)                             (0x00001000&((data)<<12))
#define VO_ContrastM2_m11(data)                                       (0x00000FFF&(data))
#define VO_ContrastM2_get_write_enable1(data)                         ((0x02000000&(data))>>25)
#define VO_ContrastM2_get_m21(data)                                   ((0x01FFE000&(data))>>13)
#define VO_ContrastM2_get_write_enable2(data)                         ((0x00001000&(data))>>12)
#define VO_ContrastM2_get_m11(data)                                   (0x00000FFF&(data))

#define VO_ContrastM3                                                 0x180054F4
#define VO_ContrastM3_reg_addr                                        "0xB80054F4"
#define VO_ContrastM3_reg                                             0xB80054F4
#define VO_ContrastM3_inst_addr                                       "0x013D"
#define VO_ContrastM3_inst                                            0x013D
#define VO_ContrastM3_write_enable1_shift                             (25)
#define VO_ContrastM3_m12_shift                                       (13)
#define VO_ContrastM3_write_enable2_shift                             (12)
#define VO_ContrastM3_m02_shift                                       (0)
#define VO_ContrastM3_write_enable1_mask                              (0x02000000)
#define VO_ContrastM3_m12_mask                                        (0x01FFE000)
#define VO_ContrastM3_write_enable2_mask                              (0x00001000)
#define VO_ContrastM3_m02_mask                                        (0x00000FFF)
#define VO_ContrastM3_write_enable1(data)                             (0x02000000&((data)<<25))
#define VO_ContrastM3_m12(data)                                       (0x01FFE000&((data)<<13))
#define VO_ContrastM3_write_enable2(data)                             (0x00001000&((data)<<12))
#define VO_ContrastM3_m02(data)                                       (0x00000FFF&(data))
#define VO_ContrastM3_get_write_enable1(data)                         ((0x02000000&(data))>>25)
#define VO_ContrastM3_get_m12(data)                                   ((0x01FFE000&(data))>>13)
#define VO_ContrastM3_get_write_enable2(data)                         ((0x00001000&(data))>>12)
#define VO_ContrastM3_get_m02(data)                                   (0x00000FFF&(data))

#define VO_ContrastM4                                                 0x180054F8
#define VO_ContrastM4_reg_addr                                        "0xB80054F8"
#define VO_ContrastM4_reg                                             0xB80054F8
#define VO_ContrastM4_inst_addr                                       "0x013E"
#define VO_ContrastM4_inst                                            0x013E
#define VO_ContrastM4_m22_shift                                       (0)
#define VO_ContrastM4_m22_mask                                        (0x00000FFF)
#define VO_ContrastM4_m22(data)                                       (0x00000FFF&(data))
#define VO_ContrastM4_get_m22(data)                                   (0x00000FFF&(data))

#define VO_ContrastA                                                  0x180054FC
#define VO_ContrastA_reg_addr                                         "0xB80054FC"
#define VO_ContrastA_reg                                              0xB80054FC
#define VO_ContrastA_inst_addr                                        "0x013F"
#define VO_ContrastA_inst                                             0x013F
#define VO_ContrastA_write_enable1_shift                              (29)
#define VO_ContrastA_a2_shift                                         (20)
#define VO_ContrastA_write_enable2_shift                              (19)
#define VO_ContrastA_a1_shift                                         (10)
#define VO_ContrastA_write_enable3_shift                              (9)
#define VO_ContrastA_a0_shift                                         (0)
#define VO_ContrastA_write_enable1_mask                               (0x20000000)
#define VO_ContrastA_a2_mask                                          (0x1FF00000)
#define VO_ContrastA_write_enable2_mask                               (0x00080000)
#define VO_ContrastA_a1_mask                                          (0x0007FC00)
#define VO_ContrastA_write_enable3_mask                               (0x00000200)
#define VO_ContrastA_a0_mask                                          (0x000001FF)
#define VO_ContrastA_write_enable1(data)                              (0x20000000&((data)<<29))
#define VO_ContrastA_a2(data)                                         (0x1FF00000&((data)<<20))
#define VO_ContrastA_write_enable2(data)                              (0x00080000&((data)<<19))
#define VO_ContrastA_a1(data)                                         (0x0007FC00&((data)<<10))
#define VO_ContrastA_write_enable3(data)                              (0x00000200&((data)<<9))
#define VO_ContrastA_a0(data)                                         (0x000001FF&(data))
#define VO_ContrastA_get_write_enable1(data)                          ((0x20000000&(data))>>29)
#define VO_ContrastA_get_a2(data)                                     ((0x1FF00000&(data))>>20)
#define VO_ContrastA_get_write_enable2(data)                          ((0x00080000&(data))>>19)
#define VO_ContrastA_get_a1(data)                                     ((0x0007FC00&(data))>>10)
#define VO_ContrastA_get_write_enable3(data)                          ((0x00000200&(data))>>9)
#define VO_ContrastA_get_a0(data)                                     (0x000001FF&(data))

#define VO_ContrastLimit                                              0x18005500
#define VO_ContrastLimit_reg_addr                                     "0xB8005500"
#define VO_ContrastLimit_reg                                          0xB8005500
#define VO_ContrastLimit_inst_addr                                    "0x0140"
#define VO_ContrastLimit_inst                                         0x0140
#define VO_ContrastLimit_cmax_shift                                   (24)
#define VO_ContrastLimit_cmin_shift                                   (16)
#define VO_ContrastLimit_ymax_shift                                   (8)
#define VO_ContrastLimit_ymin_shift                                   (0)
#define VO_ContrastLimit_cmax_mask                                    (0xFF000000)
#define VO_ContrastLimit_cmin_mask                                    (0x00FF0000)
#define VO_ContrastLimit_ymax_mask                                    (0x0000FF00)
#define VO_ContrastLimit_ymin_mask                                    (0x000000FF)
#define VO_ContrastLimit_cmax(data)                                   (0xFF000000&((data)<<24))
#define VO_ContrastLimit_cmin(data)                                   (0x00FF0000&((data)<<16))
#define VO_ContrastLimit_ymax(data)                                   (0x0000FF00&((data)<<8))
#define VO_ContrastLimit_ymin(data)                                   (0x000000FF&(data))
#define VO_ContrastLimit_get_cmax(data)                               ((0xFF000000&(data))>>24)
#define VO_ContrastLimit_get_cmin(data)                               ((0x00FF0000&(data))>>16)
#define VO_ContrastLimit_get_ymax(data)                               ((0x0000FF00&(data))>>8)
#define VO_ContrastLimit_get_ymin(data)                               (0x000000FF&(data))

#define VO_REINTERLACE                                                0x18005504
#define VO_REINTERLACE_reg_addr                                       "0xB8005504"
#define VO_REINTERLACE_reg                                            0xB8005504
#define VO_REINTERLACE_inst_addr                                      "0x0141"
#define VO_REINTERLACE_inst                                           0x0141
#define VO_REINTERLACE_topfld_shift                                   (3)
#define VO_REINTERLACE_pen_shift                                      (2)
#define VO_REINTERLACE_ien_shift                                      (1)
#define VO_REINTERLACE_write_data_shift                               (0)
#define VO_REINTERLACE_topfld_mask                                    (0x00000008)
#define VO_REINTERLACE_pen_mask                                       (0x00000004)
#define VO_REINTERLACE_ien_mask                                       (0x00000002)
#define VO_REINTERLACE_write_data_mask                                (0x00000001)
#define VO_REINTERLACE_topfld(data)                                   (0x00000008&((data)<<3))
#define VO_REINTERLACE_pen(data)                                      (0x00000004&((data)<<2))
#define VO_REINTERLACE_ien(data)                                      (0x00000002&((data)<<1))
#define VO_REINTERLACE_write_data(data)                               (0x00000001&(data))
#define VO_REINTERLACE_get_topfld(data)                               ((0x00000008&(data))>>3)
#define VO_REINTERLACE_get_pen(data)                                  ((0x00000004&(data))>>2)
#define VO_REINTERLACE_get_ien(data)                                  ((0x00000002&(data))>>1)
#define VO_REINTERLACE_get_write_data(data)                           (0x00000001&(data))

#define VO_REINT_DISPBUF                                              0x18005508
#define VO_REINT_DISPBUF_reg_addr                                     "0xB8005508"
#define VO_REINT_DISPBUF_reg                                          0xB8005508
#define VO_REINT_DISPBUF_inst_addr                                    "0x0142"
#define VO_REINT_DISPBUF_inst                                         0x0142
#define VO_REINT_DISPBUF_end_shift                                    (0)
#define VO_REINT_DISPBUF_end_mask                                     (0x00000FFF)
#define VO_REINT_DISPBUF_end(data)                                    (0x00000FFF&(data))
#define VO_REINT_DISPBUF_get_end(data)                                (0x00000FFF&(data))

#define VO_BSTLEN                                                     0x1800550C
#define VO_BSTLEN_reg_addr                                            "0xB800550C"
#define VO_BSTLEN_reg                                                 0xB800550C
#define VO_BSTLEN_inst_addr                                           "0x0143"
#define VO_BSTLEN_inst                                                0x0143
#define VO_BSTLEN_l_shift                                             (0)
#define VO_BSTLEN_l_mask                                              (0x00000007)
#define VO_BSTLEN_l(data)                                             (0x00000007&(data))
#define VO_BSTLEN_get_l(data)                                         (0x00000007&(data))

#define VO_VIDEOST                                                    0x18005510
#define VO_VIDEOST_reg_addr                                           "0xB8005510"
#define VO_VIDEOST_reg                                                0xB8005510
#define VO_VIDEOST_inst_addr                                          "0x0144"
#define VO_VIDEOST_inst                                               0x0144
#define VO_VIDEOST_video2_shift                                       (2)
#define VO_VIDEOST_video1_shift                                       (1)
#define VO_VIDEOST_write_data_shift                                   (0)
#define VO_VIDEOST_video2_mask                                        (0x00000004)
#define VO_VIDEOST_video1_mask                                        (0x00000002)
#define VO_VIDEOST_write_data_mask                                    (0x00000001)
#define VO_VIDEOST_video2(data)                                       (0x00000004&((data)<<2))
#define VO_VIDEOST_video1(data)                                       (0x00000002&((data)<<1))
#define VO_VIDEOST_write_data(data)                                   (0x00000001&(data))
#define VO_VIDEOST_get_video2(data)                                   ((0x00000004&(data))>>2)
#define VO_VIDEOST_get_video1(data)                                   ((0x00000002&(data))>>1)
#define VO_VIDEOST_get_write_data(data)                               (0x00000001&(data))

#define VO_Y1PICSET                                                   0x18005514
#define VO_Y1PICSET_reg_addr                                          "0xB8005514"
#define VO_Y1PICSET_reg                                               0xB8005514
#define VO_Y1PICSET_inst_addr                                         "0x0145"
#define VO_Y1PICSET_inst                                              0x0145
#define VO_Y1PICSET_write_enable1_shift                               (27)
#define VO_Y1PICSET_wr_shift                                          (21)
#define VO_Y1PICSET_write_enable2_shift                               (20)
#define VO_Y1PICSET_cur_shift                                         (14)
#define VO_Y1PICSET_write_enable3_shift                               (13)
#define VO_Y1PICSET_pre_shift                                         (7)
#define VO_Y1PICSET_write_enable4_shift                               (6)
#define VO_Y1PICSET_nxt_shift                                         (0)
#define VO_Y1PICSET_write_enable1_mask                                (0x08000000)
#define VO_Y1PICSET_wr_mask                                           (0x07E00000)
#define VO_Y1PICSET_write_enable2_mask                                (0x00100000)
#define VO_Y1PICSET_cur_mask                                          (0x000FC000)
#define VO_Y1PICSET_write_enable3_mask                                (0x00002000)
#define VO_Y1PICSET_pre_mask                                          (0x00001F80)
#define VO_Y1PICSET_write_enable4_mask                                (0x00000040)
#define VO_Y1PICSET_nxt_mask                                          (0x0000003F)
#define VO_Y1PICSET_write_enable1(data)                               (0x08000000&((data)<<27))
#define VO_Y1PICSET_wr(data)                                          (0x07E00000&((data)<<21))
#define VO_Y1PICSET_write_enable2(data)                               (0x00100000&((data)<<20))
#define VO_Y1PICSET_cur(data)                                         (0x000FC000&((data)<<14))
#define VO_Y1PICSET_write_enable3(data)                               (0x00002000&((data)<<13))
#define VO_Y1PICSET_pre(data)                                         (0x00001F80&((data)<<7))
#define VO_Y1PICSET_write_enable4(data)                               (0x00000040&((data)<<6))
#define VO_Y1PICSET_nxt(data)                                         (0x0000003F&(data))
#define VO_Y1PICSET_get_write_enable1(data)                           ((0x08000000&(data))>>27)
#define VO_Y1PICSET_get_wr(data)                                      ((0x07E00000&(data))>>21)
#define VO_Y1PICSET_get_write_enable2(data)                           ((0x00100000&(data))>>20)
#define VO_Y1PICSET_get_cur(data)                                     ((0x000FC000&(data))>>14)
#define VO_Y1PICSET_get_write_enable3(data)                           ((0x00002000&(data))>>13)
#define VO_Y1PICSET_get_pre(data)                                     ((0x00001F80&(data))>>7)
#define VO_Y1PICSET_get_write_enable4(data)                           ((0x00000040&(data))>>6)
#define VO_Y1PICSET_get_nxt(data)                                     (0x0000003F&(data))

#define VO_Y1RSADR                                                    0x18005518
#define VO_Y1RSADR_reg_addr                                           "0xB8005518"
#define VO_Y1RSADR_reg                                                0xB8005518
#define VO_Y1RSADR_inst_addr                                          "0x0146"
#define VO_Y1RSADR_inst                                               0x0146
#define VO_Y1RSADR_y1rsadr_shift                                      (0)
#define VO_Y1RSADR_y1rsadr_mask                                       (0x00FFFFFF)
#define VO_Y1RSADR_y1rsadr(data)                                      (0x00FFFFFF&(data))
#define VO_Y1RSADR_get_y1rsadr(data)                                  (0x00FFFFFF&(data))

#define VO_Y1WSADR                                                    0x1800551C
#define VO_Y1WSADR_reg_addr                                           "0xB800551C"
#define VO_Y1WSADR_reg                                                0xB800551C
#define VO_Y1WSADR_inst_addr                                          "0x0147"
#define VO_Y1WSADR_inst                                               0x0147
#define VO_Y1WSADR_y1wsadr_shift                                      (0)
#define VO_Y1WSADR_y1wsadr_mask                                       (0x00FFFFFF)
#define VO_Y1WSADR_y1wsadr(data)                                      (0x00FFFFFF&(data))
#define VO_Y1WSADR_get_y1wsadr(data)                                  (0x00FFFFFF&(data))

#define VO_C1PICSET                                                   0x18005520
#define VO_C1PICSET_reg_addr                                          "0xB8005520"
#define VO_C1PICSET_reg                                               0xB8005520
#define VO_C1PICSET_inst_addr                                         "0x0148"
#define VO_C1PICSET_inst                                              0x0148
#define VO_C1PICSET_write_enable1_shift                               (27)
#define VO_C1PICSET_wr_shift                                          (21)
#define VO_C1PICSET_write_enable2_shift                               (20)
#define VO_C1PICSET_cur_shift                                         (14)
#define VO_C1PICSET_write_enable3_shift                               (13)
#define VO_C1PICSET_pre_shift                                         (7)
#define VO_C1PICSET_write_enable4_shift                               (6)
#define VO_C1PICSET_nxt_shift                                         (0)
#define VO_C1PICSET_write_enable1_mask                                (0x08000000)
#define VO_C1PICSET_wr_mask                                           (0x07E00000)
#define VO_C1PICSET_write_enable2_mask                                (0x00100000)
#define VO_C1PICSET_cur_mask                                          (0x000FC000)
#define VO_C1PICSET_write_enable3_mask                                (0x00002000)
#define VO_C1PICSET_pre_mask                                          (0x00001F80)
#define VO_C1PICSET_write_enable4_mask                                (0x00000040)
#define VO_C1PICSET_nxt_mask                                          (0x0000003F)
#define VO_C1PICSET_write_enable1(data)                               (0x08000000&((data)<<27))
#define VO_C1PICSET_wr(data)                                          (0x07E00000&((data)<<21))
#define VO_C1PICSET_write_enable2(data)                               (0x00100000&((data)<<20))
#define VO_C1PICSET_cur(data)                                         (0x000FC000&((data)<<14))
#define VO_C1PICSET_write_enable3(data)                               (0x00002000&((data)<<13))
#define VO_C1PICSET_pre(data)                                         (0x00001F80&((data)<<7))
#define VO_C1PICSET_write_enable4(data)                               (0x00000040&((data)<<6))
#define VO_C1PICSET_nxt(data)                                         (0x0000003F&(data))
#define VO_C1PICSET_get_write_enable1(data)                           ((0x08000000&(data))>>27)
#define VO_C1PICSET_get_wr(data)                                      ((0x07E00000&(data))>>21)
#define VO_C1PICSET_get_write_enable2(data)                           ((0x00100000&(data))>>20)
#define VO_C1PICSET_get_cur(data)                                     ((0x000FC000&(data))>>14)
#define VO_C1PICSET_get_write_enable3(data)                           ((0x00002000&(data))>>13)
#define VO_C1PICSET_get_pre(data)                                     ((0x00001F80&(data))>>7)
#define VO_C1PICSET_get_write_enable4(data)                           ((0x00000040&(data))>>6)
#define VO_C1PICSET_get_nxt(data)                                     (0x0000003F&(data))

#define VO_V2PICSET                                                   0x18005524
#define VO_V2PICSET_reg_addr                                          "0xB8005524"
#define VO_V2PICSET_reg                                               0xB8005524
#define VO_V2PICSET_inst_addr                                         "0x0149"
#define VO_V2PICSET_inst                                              0x0149
#define VO_V2PICSET_write_enable1_shift                               (27)
#define VO_V2PICSET_y2cur_shift                                       (21)
#define VO_V2PICSET_write_enable2_shift                               (20)
#define VO_V2PICSET_y2alt_shift                                       (14)
#define VO_V2PICSET_write_enable3_shift                               (13)
#define VO_V2PICSET_c2cur_shift                                       (7)
#define VO_V2PICSET_write_enable4_shift                               (6)
#define VO_V2PICSET_c2alt_shift                                       (0)
#define VO_V2PICSET_write_enable1_mask                                (0x08000000)
#define VO_V2PICSET_y2cur_mask                                        (0x07E00000)
#define VO_V2PICSET_write_enable2_mask                                (0x00100000)
#define VO_V2PICSET_y2alt_mask                                        (0x000FC000)
#define VO_V2PICSET_write_enable3_mask                                (0x00002000)
#define VO_V2PICSET_c2cur_mask                                        (0x00001F80)
#define VO_V2PICSET_write_enable4_mask                                (0x00000040)
#define VO_V2PICSET_c2alt_mask                                        (0x0000003F)
#define VO_V2PICSET_write_enable1(data)                               (0x08000000&((data)<<27))
#define VO_V2PICSET_y2cur(data)                                       (0x07E00000&((data)<<21))
#define VO_V2PICSET_write_enable2(data)                               (0x00100000&((data)<<20))
#define VO_V2PICSET_y2alt(data)                                       (0x000FC000&((data)<<14))
#define VO_V2PICSET_write_enable3(data)                               (0x00002000&((data)<<13))
#define VO_V2PICSET_c2cur(data)                                       (0x00001F80&((data)<<7))
#define VO_V2PICSET_write_enable4(data)                               (0x00000040&((data)<<6))
#define VO_V2PICSET_c2alt(data)                                       (0x0000003F&(data))
#define VO_V2PICSET_get_write_enable1(data)                           ((0x08000000&(data))>>27)
#define VO_V2PICSET_get_y2cur(data)                                   ((0x07E00000&(data))>>21)
#define VO_V2PICSET_get_write_enable2(data)                           ((0x00100000&(data))>>20)
#define VO_V2PICSET_get_y2alt(data)                                   ((0x000FC000&(data))>>14)
#define VO_V2PICSET_get_write_enable3(data)                           ((0x00002000&(data))>>13)
#define VO_V2PICSET_get_c2cur(data)                                   ((0x00001F80&(data))>>7)
#define VO_V2PICSET_get_write_enable4(data)                           ((0x00000040&(data))>>6)
#define VO_V2PICSET_get_c2alt(data)                                   (0x0000003F&(data))

#define VO_VBIADR                                                     0x18005528
#define VO_VBIADR_reg_addr                                            "0xB8005528"
#define VO_VBIADR_reg                                                 0xB8005528
#define VO_VBIADR_inst_addr                                           "0x014A"
#define VO_VBIADR_inst                                                0x014A
#define VO_VBIADR_a_shift                                             (0)
#define VO_VBIADR_a_mask                                              (0x00FFFFFF)
#define VO_VBIADR_a(data)                                             (0x00FFFFFF&(data))
#define VO_VBIADR_get_a(data)                                         (0x00FFFFFF&(data))

#define VO_TTADR                                                      0x1800552C
#define VO_TTADR_reg_addr                                             "0xB800552C"
#define VO_TTADR_reg                                                  0xB800552C
#define VO_TTADR_inst_addr                                            "0x014B"
#define VO_TTADR_inst                                                 0x014B
#define VO_TTADR_a_shift                                              (0)
#define VO_TTADR_a_mask                                               (0x00FFFFFF)
#define VO_TTADR_a(data)                                              (0x00FFFFFF&(data))
#define VO_TTADR_get_a(data)                                          (0x00FFFFFF&(data))

#define VO_TPXDADR                                                    0x18005530
#define VO_TPXDADR_reg_addr                                           "0xB8005530"
#define VO_TPXDADR_reg                                                0xB8005530
#define VO_TPXDADR_inst_addr                                          "0x014C"
#define VO_TPXDADR_inst                                               0x014C
#define VO_TPXDADR_a_shift                                            (0)
#define VO_TPXDADR_a_mask                                             (0x07FFFFFF)
#define VO_TPXDADR_a(data)                                            (0x07FFFFFF&(data))
#define VO_TPXDADR_get_a(data)                                        (0x07FFFFFF&(data))

#define VO_BPXDADR                                                    0x18005534
#define VO_BPXDADR_reg_addr                                           "0xB8005534"
#define VO_BPXDADR_reg                                                0xB8005534
#define VO_BPXDADR_inst_addr                                          "0x014D"
#define VO_BPXDADR_inst                                               0x014D
#define VO_BPXDADR_a_shift                                            (0)
#define VO_BPXDADR_a_mask                                             (0x07FFFFFF)
#define VO_BPXDADR_a(data)                                            (0x07FFFFFF&(data))
#define VO_BPXDADR_get_a(data)                                        (0x07FFFFFF&(data))

#define VO_TCMDADR                                                    0x18005538
#define VO_TCMDADR_reg_addr                                           "0xB8005538"
#define VO_TCMDADR_reg                                                0xB8005538
#define VO_TCMDADR_inst_addr                                          "0x014E"
#define VO_TCMDADR_inst                                               0x014E
#define VO_TCMDADR_a_shift                                            (0)
#define VO_TCMDADR_a_mask                                             (0x00FFFFFF)
#define VO_TCMDADR_a(data)                                            (0x00FFFFFF&(data))
#define VO_TCMDADR_get_a(data)                                        (0x00FFFFFF&(data))

#define VO_BCMDADR                                                    0x1800553C
#define VO_BCMDADR_reg_addr                                           "0xB800553C"
#define VO_BCMDADR_reg                                                0xB800553C
#define VO_BCMDADR_inst_addr                                          "0x014F"
#define VO_BCMDADR_inst                                               0x014F
#define VO_BCMDADR_a_shift                                            (0)
#define VO_BCMDADR_a_mask                                             (0x00FFFFFF)
#define VO_BCMDADR_a(data)                                            (0x00FFFFFF&(data))
#define VO_BCMDADR_get_a(data)                                        (0x00FFFFFF&(data))

#define VO_OSDDMA0_0                                                  0x18005540
#define VO_OSDDMA0_1                                                  0x18005544
#define VO_OSDDMA0_2                                                  0x18005548
#define VO_OSDDMA0_3                                                  0x1800554C
#define VO_OSDDMA0_0_reg_addr                                         "0xB8005540"
#define VO_OSDDMA0_1_reg_addr                                         "0xB8005544"
#define VO_OSDDMA0_2_reg_addr                                         "0xB8005548"
#define VO_OSDDMA0_3_reg_addr                                         "0xB800554C"
#define VO_OSDDMA0_0_reg                                              0xB8005540
#define VO_OSDDMA0_1_reg                                              0xB8005544
#define VO_OSDDMA0_2_reg                                              0xB8005548
#define VO_OSDDMA0_3_reg                                              0xB800554C
#define VO_OSDDMA0_0_inst_addr                                        "0x0150"
#define VO_OSDDMA0_0_inst                                             0x0150
#define VO_OSDDMA0_1_inst_addr                                        "0x0151"
#define VO_OSDDMA0_1_inst                                             0x0151
#define VO_OSDDMA0_2_inst_addr                                        "0x0152"
#define VO_OSDDMA0_2_inst                                             0x0152
#define VO_OSDDMA0_3_inst_addr                                        "0x0153"
#define VO_OSDDMA0_3_inst                                             0x0153
#define VO_OSDDMA0_write_enable1_shift                                (18)
#define VO_OSDDMA0_pic_set_shift                                      (12)
#define VO_OSDDMA0_write_enable2_shift                                (11)
#define VO_OSDDMA0_yst_shift                                          (0)
#define VO_OSDDMA0_write_enable1_mask                                 (0x00040000)
#define VO_OSDDMA0_pic_set_mask                                       (0x0003F000)
#define VO_OSDDMA0_write_enable2_mask                                 (0x00000800)
#define VO_OSDDMA0_yst_mask                                           (0x000007FF)
#define VO_OSDDMA0_write_enable1(data)                                (0x00040000&((data)<<18))
#define VO_OSDDMA0_pic_set(data)                                      (0x0003F000&((data)<<12))
#define VO_OSDDMA0_write_enable2(data)                                (0x00000800&((data)<<11))
#define VO_OSDDMA0_yst(data)                                          (0x000007FF&(data))
#define VO_OSDDMA0_get_write_enable1(data)                            ((0x00040000&(data))>>18)
#define VO_OSDDMA0_get_pic_set(data)                                  ((0x0003F000&(data))>>12)
#define VO_OSDDMA0_get_write_enable2(data)                            ((0x00000800&(data))>>11)
#define VO_OSDDMA0_get_yst(data)                                      (0x000007FF&(data))

#define VO_OSDDMA1_0                                                  0x18005550
#define VO_OSDDMA1_1                                                  0x18005554
#define VO_OSDDMA1_2                                                  0x18005558
#define VO_OSDDMA1_3                                                  0x1800555C
#define VO_OSDDMA1_0_reg_addr                                         "0xB8005550"
#define VO_OSDDMA1_1_reg_addr                                         "0xB8005554"
#define VO_OSDDMA1_2_reg_addr                                         "0xB8005558"
#define VO_OSDDMA1_3_reg_addr                                         "0xB800555C"
#define VO_OSDDMA1_0_reg                                              0xB8005550
#define VO_OSDDMA1_1_reg                                              0xB8005554
#define VO_OSDDMA1_2_reg                                              0xB8005558
#define VO_OSDDMA1_3_reg                                              0xB800555C
#define VO_OSDDMA1_0_inst_addr                                        "0x0154"
#define VO_OSDDMA1_0_inst                                             0x0154
#define VO_OSDDMA1_1_inst_addr                                        "0x0155"
#define VO_OSDDMA1_1_inst                                             0x0155
#define VO_OSDDMA1_2_inst_addr                                        "0x0156"
#define VO_OSDDMA1_2_inst                                             0x0156
#define VO_OSDDMA1_3_inst_addr                                        "0x0157"
#define VO_OSDDMA1_3_inst                                             0x0157
#define VO_OSDDMA1_write_enable2_shift                                (21)
#define VO_OSDDMA1_length_shift                                       (11)
#define VO_OSDDMA1_write_enable3_shift                                (10)
#define VO_OSDDMA1_xst_shift                                          (0)
#define VO_OSDDMA1_write_enable2_mask                                 (0x00200000)
#define VO_OSDDMA1_length_mask                                        (0x001FF800)
#define VO_OSDDMA1_write_enable3_mask                                 (0x00000400)
#define VO_OSDDMA1_xst_mask                                           (0x000003FF)
#define VO_OSDDMA1_write_enable2(data)                                (0x00200000&((data)<<21))
#define VO_OSDDMA1_length(data)                                       (0x001FF800&((data)<<11))
#define VO_OSDDMA1_write_enable3(data)                                (0x00000400&((data)<<10))
#define VO_OSDDMA1_xst(data)                                          (0x000003FF&(data))
#define VO_OSDDMA1_get_write_enable2(data)                            ((0x00200000&(data))>>21)
#define VO_OSDDMA1_get_length(data)                                   ((0x001FF800&(data))>>11)
#define VO_OSDDMA1_get_write_enable3(data)                            ((0x00000400&(data))>>10)
#define VO_OSDDMA1_get_xst(data)                                      (0x000003FF&(data))

#define VO_CURSORADR                                                  0x18005560
#define VO_CURSORADR_reg_addr                                         "0xB8005560"
#define VO_CURSORADR_reg                                              0xB8005560
#define VO_CURSORADR_inst_addr                                        "0x0158"
#define VO_CURSORADR_inst                                             0x0158
#define VO_CURSORADR_a_shift                                          (0)
#define VO_CURSORADR_a_mask                                           (0x00FFFFFF)
#define VO_CURSORADR_a(data)                                          (0x00FFFFFF&(data))
#define VO_CURSORADR_get_a(data)                                      (0x00FFFFFF&(data))

#define VO_PRIORITY_0                                                 0x18005564
#define VO_PRIORITY_1                                                 0x18005568
#define VO_PRIORITY_2                                                 0x1800556C
#define VO_PRIORITY_3                                                 0x18005570
#define VO_PRIORITY_4                                                 0x18005574
#define VO_PRIORITY_5                                                 0x18005578
#define VO_PRIORITY_6                                                 0x1800557C
#define VO_PRIORITY_7                                                 0x18005580
#define VO_PRIORITY_8                                                 0x18005584
#define VO_PRIORITY_0_reg_addr                                        "0xB8005564"
#define VO_PRIORITY_1_reg_addr                                        "0xB8005568"
#define VO_PRIORITY_2_reg_addr                                        "0xB800556C"
#define VO_PRIORITY_3_reg_addr                                        "0xB8005570"
#define VO_PRIORITY_4_reg_addr                                        "0xB8005574"
#define VO_PRIORITY_5_reg_addr                                        "0xB8005578"
#define VO_PRIORITY_6_reg_addr                                        "0xB800557C"
#define VO_PRIORITY_7_reg_addr                                        "0xB8005580"
#define VO_PRIORITY_8_reg_addr                                        "0xB8005584"
#define VO_PRIORITY_0_reg                                             0xB8005564
#define VO_PRIORITY_1_reg                                             0xB8005568
#define VO_PRIORITY_2_reg                                             0xB800556C
#define VO_PRIORITY_3_reg                                             0xB8005570
#define VO_PRIORITY_4_reg                                             0xB8005574
#define VO_PRIORITY_5_reg                                             0xB8005578
#define VO_PRIORITY_6_reg                                             0xB800557C
#define VO_PRIORITY_7_reg                                             0xB8005580
#define VO_PRIORITY_8_reg                                             0xB8005584
#define VO_PRIORITY_0_inst_addr                                       "0x0159"
#define VO_PRIORITY_0_inst                                            0x0159
#define VO_PRIORITY_1_inst_addr                                       "0x015A"
#define VO_PRIORITY_1_inst                                            0x015A
#define VO_PRIORITY_2_inst_addr                                       "0x015B"
#define VO_PRIORITY_2_inst                                            0x015B
#define VO_PRIORITY_3_inst_addr                                       "0x015C"
#define VO_PRIORITY_3_inst                                            0x015C
#define VO_PRIORITY_4_inst_addr                                       "0x015D"
#define VO_PRIORITY_4_inst                                            0x015D
#define VO_PRIORITY_5_inst_addr                                       "0x015E"
#define VO_PRIORITY_5_inst                                            0x015E
#define VO_PRIORITY_6_inst_addr                                       "0x015F"
#define VO_PRIORITY_6_inst                                            0x015F
#define VO_PRIORITY_7_inst_addr                                       "0x0160"
#define VO_PRIORITY_7_inst                                            0x0160
#define VO_PRIORITY_8_inst_addr                                       "0x0161"
#define VO_PRIORITY_8_inst                                            0x0161
#define VO_PRIORITY_channel_shift                                     (0)
#define VO_PRIORITY_channel_mask                                      (0x0000000F)
#define VO_PRIORITY_channel(data)                                     (0x0000000F&(data))
#define VO_PRIORITY_get_channel(data)                                 (0x0000000F&(data))

#define VO_Y1C2_BASE                                                  0x18005588
#define VO_Y1C2_BASE_reg_addr                                         "0xB8005588"
#define VO_Y1C2_BASE_reg                                              0xB8005588
#define VO_Y1C2_BASE_inst_addr                                        "0x0162"
#define VO_Y1C2_BASE_inst                                             0x0162
#define VO_Y1C2_BASE_b_shift                                          (0)
#define VO_Y1C2_BASE_b_mask                                           (0x000007FF)
#define VO_Y1C2_BASE_b(data)                                          (0x000007FF&(data))
#define VO_Y1C2_BASE_get_b(data)                                      (0x000007FF&(data))

#define VO_Y1P_BASE                                                   0x1800558C
#define VO_Y1P_BASE_reg_addr                                          "0xB800558C"
#define VO_Y1P_BASE_reg                                               0xB800558C
#define VO_Y1P_BASE_inst_addr                                         "0x0163"
#define VO_Y1P_BASE_inst                                              0x0163
#define VO_Y1P_BASE_b_shift                                           (0)
#define VO_Y1P_BASE_b_mask                                            (0x000007FF)
#define VO_Y1P_BASE_b(data)                                           (0x000007FF&(data))
#define VO_Y1P_BASE_get_b(data)                                       (0x000007FF&(data))

#define VO_Y1N_BASE                                                   0x18005590
#define VO_Y1N_BASE_reg_addr                                          "0xB8005590"
#define VO_Y1N_BASE_reg                                               0xB8005590
#define VO_Y1N_BASE_inst_addr                                         "0x0164"
#define VO_Y1N_BASE_inst                                              0x0164
#define VO_Y1N_BASE_b_shift                                           (0)
#define VO_Y1N_BASE_b_mask                                            (0x000007FF)
#define VO_Y1N_BASE_b(data)                                           (0x000007FF&(data))
#define VO_Y1N_BASE_get_b(data)                                       (0x000007FF&(data))

#define VO_C1C1_BASE                                                  0x18005594
#define VO_C1C1_BASE_reg_addr                                         "0xB8005594"
#define VO_C1C1_BASE_reg                                              0xB8005594
#define VO_C1C1_BASE_inst_addr                                        "0x0165"
#define VO_C1C1_BASE_inst                                             0x0165
#define VO_C1C1_BASE_b_shift                                          (0)
#define VO_C1C1_BASE_b_mask                                           (0x000007FF)
#define VO_C1C1_BASE_b(data)                                          (0x000007FF&(data))
#define VO_C1C1_BASE_get_b(data)                                      (0x000007FF&(data))

#define VO_C1C2_BASE                                                  0x18005598
#define VO_C1C2_BASE_reg_addr                                         "0xB8005598"
#define VO_C1C2_BASE_reg                                              0xB8005598
#define VO_C1C2_BASE_inst_addr                                        "0x0166"
#define VO_C1C2_BASE_inst                                             0x0166
#define VO_C1C2_BASE_b_shift                                          (0)
#define VO_C1C2_BASE_b_mask                                           (0x000007FF)
#define VO_C1C2_BASE_b(data)                                          (0x000007FF&(data))
#define VO_C1C2_BASE_get_b(data)                                      (0x000007FF&(data))

#define VO_C1P_BASE                                                   0x1800559C
#define VO_C1P_BASE_reg_addr                                          "0xB800559C"
#define VO_C1P_BASE_reg                                               0xB800559C
#define VO_C1P_BASE_inst_addr                                         "0x0167"
#define VO_C1P_BASE_inst                                              0x0167
#define VO_C1P_BASE_b_shift                                           (0)
#define VO_C1P_BASE_b_mask                                            (0x000007FF)
#define VO_C1P_BASE_b(data)                                           (0x000007FF&(data))
#define VO_C1P_BASE_get_b(data)                                       (0x000007FF&(data))

#define VO_C1N_BASE                                                   0x180055A0
#define VO_C1N_BASE_reg_addr                                          "0xB80055A0"
#define VO_C1N_BASE_reg                                               0xB80055A0
#define VO_C1N_BASE_inst_addr                                         "0x0168"
#define VO_C1N_BASE_inst                                              0x0168
#define VO_C1N_BASE_b_shift                                           (0)
#define VO_C1N_BASE_b_mask                                            (0x000007FF)
#define VO_C1N_BASE_b(data)                                           (0x000007FF&(data))
#define VO_C1N_BASE_get_b(data)                                       (0x000007FF&(data))

#define VO_Y2C1_BASE                                                  0x180055A4
#define VO_Y2C1_BASE_reg_addr                                         "0xB80055A4"
#define VO_Y2C1_BASE_reg                                              0xB80055A4
#define VO_Y2C1_BASE_inst_addr                                        "0x0169"
#define VO_Y2C1_BASE_inst                                             0x0169
#define VO_Y2C1_BASE_b_shift                                          (0)
#define VO_Y2C1_BASE_b_mask                                           (0x000007FF)
#define VO_Y2C1_BASE_b(data)                                          (0x000007FF&(data))
#define VO_Y2C1_BASE_get_b(data)                                      (0x000007FF&(data))

#define VO_Y2C2_BASE                                                  0x180055A8
#define VO_Y2C2_BASE_reg_addr                                         "0xB80055A8"
#define VO_Y2C2_BASE_reg                                              0xB80055A8
#define VO_Y2C2_BASE_inst_addr                                        "0x016A"
#define VO_Y2C2_BASE_inst                                             0x016A
#define VO_Y2C2_BASE_b_shift                                          (0)
#define VO_Y2C2_BASE_b_mask                                           (0x000007FF)
#define VO_Y2C2_BASE_b(data)                                          (0x000007FF&(data))
#define VO_Y2C2_BASE_get_b(data)                                      (0x000007FF&(data))

#define VO_C2C1_BASE                                                  0x180055AC
#define VO_C2C1_BASE_reg_addr                                         "0xB80055AC"
#define VO_C2C1_BASE_reg                                              0xB80055AC
#define VO_C2C1_BASE_inst_addr                                        "0x016B"
#define VO_C2C1_BASE_inst                                             0x016B
#define VO_C2C1_BASE_b_shift                                          (0)
#define VO_C2C1_BASE_b_mask                                           (0x000007FF)
#define VO_C2C1_BASE_b(data)                                          (0x000007FF&(data))
#define VO_C2C1_BASE_get_b(data)                                      (0x000007FF&(data))

#define VO_C2C2_BASE                                                  0x180055B0
#define VO_C2C2_BASE_reg_addr                                         "0xB80055B0"
#define VO_C2C2_BASE_reg                                              0xB80055B0
#define VO_C2C2_BASE_inst_addr                                        "0x016C"
#define VO_C2C2_BASE_inst                                             0x016C
#define VO_C2C2_BASE_b_shift                                          (0)
#define VO_C2C2_BASE_b_mask                                           (0x000007FF)
#define VO_C2C2_BASE_b(data)                                          (0x000007FF&(data))
#define VO_C2C2_BASE_get_b(data)                                      (0x000007FF&(data))

#define VO_TCMD_BASE                                                  0x180055B4
#define VO_TCMD_BASE_reg_addr                                         "0xB80055B4"
#define VO_TCMD_BASE_reg                                              0xB80055B4
#define VO_TCMD_BASE_inst_addr                                        "0x016D"
#define VO_TCMD_BASE_inst                                             0x016D
#define VO_TCMD_BASE_b_shift                                          (0)
#define VO_TCMD_BASE_b_mask                                           (0x000007FF)
#define VO_TCMD_BASE_b(data)                                          (0x000007FF&(data))
#define VO_TCMD_BASE_get_b(data)                                      (0x000007FF&(data))

#define VO_TPXD_BASE                                                  0x180055B8
#define VO_TPXD_BASE_reg_addr                                         "0xB80055B8"
#define VO_TPXD_BASE_reg                                              0xB80055B8
#define VO_TPXD_BASE_inst_addr                                        "0x016E"
#define VO_TPXD_BASE_inst                                             0x016E
#define VO_TPXD_BASE_b_shift                                          (0)
#define VO_TPXD_BASE_b_mask                                           (0x000007FF)
#define VO_TPXD_BASE_b(data)                                          (0x000007FF&(data))
#define VO_TPXD_BASE_get_b(data)                                      (0x000007FF&(data))

#define VO_BCMD_BASE                                                  0x180055BC
#define VO_BCMD_BASE_reg_addr                                         "0xB80055BC"
#define VO_BCMD_BASE_reg                                              0xB80055BC
#define VO_BCMD_BASE_inst_addr                                        "0x016F"
#define VO_BCMD_BASE_inst                                             0x016F
#define VO_BCMD_BASE_b_shift                                          (0)
#define VO_BCMD_BASE_b_mask                                           (0x000007FF)
#define VO_BCMD_BASE_b(data)                                          (0x000007FF&(data))
#define VO_BCMD_BASE_get_b(data)                                      (0x000007FF&(data))

#define VO_BPXD_BASE                                                  0x180055C0
#define VO_BPXD_BASE_reg_addr                                         "0xB80055C0"
#define VO_BPXD_BASE_reg                                              0xB80055C0
#define VO_BPXD_BASE_inst_addr                                        "0x0170"
#define VO_BPXD_BASE_inst                                             0x0170
#define VO_BPXD_BASE_b_shift                                          (0)
#define VO_BPXD_BASE_b_mask                                           (0x000007FF)
#define VO_BPXD_BASE_b(data)                                          (0x000007FF&(data))
#define VO_BPXD_BASE_get_b(data)                                      (0x000007FF&(data))

#define VO_OSD_BASE                                                   0x180055C4
#define VO_OSD_BASE_reg_addr                                          "0xB80055C4"
#define VO_OSD_BASE_reg                                               0xB80055C4
#define VO_OSD_BASE_inst_addr                                         "0x0171"
#define VO_OSD_BASE_inst                                              0x0171
#define VO_OSD_BASE_b_shift                                           (0)
#define VO_OSD_BASE_b_mask                                            (0x000007FF)
#define VO_OSD_BASE_b(data)                                           (0x000007FF&(data))
#define VO_OSD_BASE_get_b(data)                                       (0x000007FF&(data))

#define VO_CUR_BASE                                                   0x180055C8
#define VO_CUR_BASE_reg_addr                                          "0xB80055C8"
#define VO_CUR_BASE_reg                                               0xB80055C8
#define VO_CUR_BASE_inst_addr                                         "0x0172"
#define VO_CUR_BASE_inst                                              0x0172
#define VO_CUR_BASE_b_shift                                           (0)
#define VO_CUR_BASE_b_mask                                            (0x000007FF)
#define VO_CUR_BASE_b(data)                                           (0x000007FF&(data))
#define VO_CUR_BASE_get_b(data)                                       (0x000007FF&(data))

#define VO_SP1_BASE                                                   0x180055CC
#define VO_SP1_BASE_reg_addr                                          "0xB80055CC"
#define VO_SP1_BASE_reg                                               0xB80055CC
#define VO_SP1_BASE_inst_addr                                         "0x0173"
#define VO_SP1_BASE_inst                                              0x0173
#define VO_SP1_BASE_b_shift                                           (0)
#define VO_SP1_BASE_b_mask                                            (0x000007FF)
#define VO_SP1_BASE_b(data)                                           (0x000007FF&(data))
#define VO_SP1_BASE_get_b(data)                                       (0x000007FF&(data))

#define VO_SP2_BASE                                                   0x180055D0
#define VO_SP2_BASE_reg_addr                                          "0xB80055D0"
#define VO_SP2_BASE_reg                                               0xB80055D0
#define VO_SP2_BASE_inst_addr                                         "0x0174"
#define VO_SP2_BASE_inst                                              0x0174
#define VO_SP2_BASE_b_shift                                           (0)
#define VO_SP2_BASE_b_mask                                            (0x000007FF)
#define VO_SP2_BASE_b(data)                                           (0x000007FF&(data))
#define VO_SP2_BASE_get_b(data)                                       (0x000007FF&(data))

#define VO_SP3_BASE                                                   0x180055D4
#define VO_SP3_BASE_reg_addr                                          "0xB80055D4"
#define VO_SP3_BASE_reg                                               0xB80055D4
#define VO_SP3_BASE_inst_addr                                         "0x0175"
#define VO_SP3_BASE_inst                                              0x0175
#define VO_SP3_BASE_b_shift                                           (0)
#define VO_SP3_BASE_b_mask                                            (0x000007FF)
#define VO_SP3_BASE_b(data)                                           (0x000007FF&(data))
#define VO_SP3_BASE_get_b(data)                                       (0x000007FF&(data))

#define VO_C1O_BASE                                                   0x180055D8
#define VO_C1O_BASE_reg_addr                                          "0xB80055D8"
#define VO_C1O_BASE_reg                                               0xB80055D8
#define VO_C1O_BASE_inst_addr                                         "0x0176"
#define VO_C1O_BASE_inst                                              0x0176
#define VO_C1O_BASE_b_shift                                           (0)
#define VO_C1O_BASE_b_mask                                            (0x000000FF)
#define VO_C1O_BASE_b(data)                                           (0x000000FF&(data))
#define VO_C1O_BASE_get_b(data)                                       (0x000000FF&(data))

#define VO_SC_BASE                                                    0x180055DC
#define VO_SC_BASE_reg_addr                                           "0xB80055DC"
#define VO_SC_BASE_reg                                                0xB80055DC
#define VO_SC_BASE_inst_addr                                          "0x0177"
#define VO_SC_BASE_inst                                               0x0177
#define VO_SC_BASE_b_shift                                            (0)
#define VO_SC_BASE_b_mask                                             (0x000000FF)
#define VO_SC_BASE_b(data)                                            (0x000000FF&(data))
#define VO_SC_BASE_get_b(data)                                        (0x000000FF&(data))

#define VO_VINTEN                                                     0x180055E0
#define VO_VINTEN_reg_addr                                            "0xB80055E0"
#define VO_VINTEN_reg                                                 0xB80055E0
#define VO_VINTEN_inst_addr                                           "0x0178"
#define VO_VINTEN_inst                                                0x0178
#define VO_VINTEN_rld_dmy_err_shift                                   (8)
#define VO_VINTEN_rld_ln_err_shift                                    (7)
#define VO_VINTEN_rld_s4_err_shift                                    (6)
#define VO_VINTEN_pudflw_shift                                        (5)
#define VO_VINTEN_iudflw_shift                                        (4)
#define VO_VINTEN_finish_shift                                        (3)
#define VO_VINTEN_ysdscfi_shift                                       (2)
#define VO_VINTEN_csdscfi_shift                                       (1)
#define VO_VINTEN_write_data_shift                                    (0)
#define VO_VINTEN_rld_dmy_err_mask                                    (0x00000100)
#define VO_VINTEN_rld_ln_err_mask                                     (0x00000080)
#define VO_VINTEN_rld_s4_err_mask                                     (0x00000040)
#define VO_VINTEN_pudflw_mask                                         (0x00000020)
#define VO_VINTEN_iudflw_mask                                         (0x00000010)
#define VO_VINTEN_finish_mask                                         (0x00000008)
#define VO_VINTEN_ysdscfi_mask                                        (0x00000004)
#define VO_VINTEN_csdscfi_mask                                        (0x00000002)
#define VO_VINTEN_write_data_mask                                     (0x00000001)
#define VO_VINTEN_rld_dmy_err(data)                                   (0x00000100&((data)<<8))
#define VO_VINTEN_rld_ln_err(data)                                    (0x00000080&((data)<<7))
#define VO_VINTEN_rld_s4_err(data)                                    (0x00000040&((data)<<6))
#define VO_VINTEN_pudflw(data)                                        (0x00000020&((data)<<5))
#define VO_VINTEN_iudflw(data)                                        (0x00000010&((data)<<4))
#define VO_VINTEN_finish(data)                                        (0x00000008&((data)<<3))
#define VO_VINTEN_ysdscfi(data)                                       (0x00000004&((data)<<2))
#define VO_VINTEN_csdscfi(data)                                       (0x00000002&((data)<<1))
#define VO_VINTEN_write_data(data)                                    (0x00000001&(data))
#define VO_VINTEN_get_rld_dmy_err(data)                               ((0x00000100&(data))>>8)
#define VO_VINTEN_get_rld_ln_err(data)                                ((0x00000080&(data))>>7)
#define VO_VINTEN_get_rld_s4_err(data)                                ((0x00000040&(data))>>6)
#define VO_VINTEN_get_pudflw(data)                                    ((0x00000020&(data))>>5)
#define VO_VINTEN_get_iudflw(data)                                    ((0x00000010&(data))>>4)
#define VO_VINTEN_get_finish(data)                                    ((0x00000008&(data))>>3)
#define VO_VINTEN_get_ysdscfi(data)                                   ((0x00000004&(data))>>2)
#define VO_VINTEN_get_csdscfi(data)                                   ((0x00000002&(data))>>1)
#define VO_VINTEN_get_write_data(data)                                (0x00000001&(data))

#define VO_VINTST                                                     0x180055E4
#define VO_VINTST_reg_addr                                            "0xB80055E4"
#define VO_VINTST_reg                                                 0xB80055E4
#define VO_VINTST_inst_addr                                           "0x0179"
#define VO_VINTST_inst                                                0x0179
#define VO_VINTST_rld_dmy_err_shift                                   (8)
#define VO_VINTST_rld_ln_err_shift                                    (7)
#define VO_VINTST_rld_s4_err_shift                                    (6)
#define VO_VINTST_pudflw_shift                                        (5)
#define VO_VINTST_iudflw_shift                                        (4)
#define VO_VINTST_finish_shift                                        (3)
#define VO_VINTST_ysdscfi_shift                                       (2)
#define VO_VINTST_csdscfi_shift                                       (1)
#define VO_VINTST_write_data_shift                                    (0)
#define VO_VINTST_rld_dmy_err_mask                                    (0x00000100)
#define VO_VINTST_rld_ln_err_mask                                     (0x00000080)
#define VO_VINTST_rld_s4_err_mask                                     (0x00000040)
#define VO_VINTST_pudflw_mask                                         (0x00000020)
#define VO_VINTST_iudflw_mask                                         (0x00000010)
#define VO_VINTST_finish_mask                                         (0x00000008)
#define VO_VINTST_ysdscfi_mask                                        (0x00000004)
#define VO_VINTST_csdscfi_mask                                        (0x00000002)
#define VO_VINTST_write_data_mask                                     (0x00000001)
#define VO_VINTST_rld_dmy_err(data)                                   (0x00000100&((data)<<8))
#define VO_VINTST_rld_ln_err(data)                                    (0x00000080&((data)<<7))
#define VO_VINTST_rld_s4_err(data)                                    (0x00000040&((data)<<6))
#define VO_VINTST_pudflw(data)                                        (0x00000020&((data)<<5))
#define VO_VINTST_iudflw(data)                                        (0x00000010&((data)<<4))
#define VO_VINTST_finish(data)                                        (0x00000008&((data)<<3))
#define VO_VINTST_ysdscfi(data)                                       (0x00000004&((data)<<2))
#define VO_VINTST_csdscfi(data)                                       (0x00000002&((data)<<1))
#define VO_VINTST_write_data(data)                                    (0x00000001&(data))
#define VO_VINTST_get_rld_dmy_err(data)                               ((0x00000100&(data))>>8)
#define VO_VINTST_get_rld_ln_err(data)                                ((0x00000080&(data))>>7)
#define VO_VINTST_get_rld_s4_err(data)                                ((0x00000040&(data))>>6)
#define VO_VINTST_get_pudflw(data)                                    ((0x00000020&(data))>>5)
#define VO_VINTST_get_iudflw(data)                                    ((0x00000010&(data))>>4)
#define VO_VINTST_get_finish(data)                                    ((0x00000008&(data))>>3)
#define VO_VINTST_get_ysdscfi(data)                                   ((0x00000004&(data))>>2)
#define VO_VINTST_get_csdscfi(data)                                   ((0x00000002&(data))>>1)
#define VO_VINTST_get_write_data(data)                                (0x00000001&(data))

#define VO_UDFLCNT                                                    0x180055E8
#define VO_UDFLCNT_reg_addr                                           "0xB80055E8"
#define VO_UDFLCNT_reg                                                0xB80055E8
#define VO_UDFLCNT_inst_addr                                          "0x017A"
#define VO_UDFLCNT_inst                                               0x017A
#define VO_UDFLCNT_spbuf_shift                                        (18)
#define VO_UDFLCNT_v2buf_shift                                        (9)
#define VO_UDFLCNT_v1buf_shift                                        (0)
#define VO_UDFLCNT_spbuf_mask                                         (0x07FC0000)
#define VO_UDFLCNT_v2buf_mask                                         (0x0003FE00)
#define VO_UDFLCNT_v1buf_mask                                         (0x000001FF)
#define VO_UDFLCNT_spbuf(data)                                        (0x07FC0000&((data)<<18))
#define VO_UDFLCNT_v2buf(data)                                        (0x0003FE00&((data)<<9))
#define VO_UDFLCNT_v1buf(data)                                        (0x000001FF&(data))
#define VO_UDFLCNT_get_spbuf(data)                                    ((0x07FC0000&(data))>>18)
#define VO_UDFLCNT_get_v2buf(data)                                    ((0x0003FE00&(data))>>9)
#define VO_UDFLCNT_get_v1buf(data)                                    (0x000001FF&(data))

#define VO_UDFLECNT                                                   0x180055EC
#define VO_UDFLECNT_reg_addr                                          "0xB80055EC"
#define VO_UDFLECNT_reg                                               0xB80055EC
#define VO_UDFLECNT_inst_addr                                         "0x017B"
#define VO_UDFLECNT_inst                                              0x017B
#define VO_UDFLECNT_osdbuf_shift                                      (0)
#define VO_UDFLECNT_osdbuf_mask                                       (0x000007FF)
#define VO_UDFLECNT_osdbuf(data)                                      (0x000007FF&(data))
#define VO_UDFLECNT_get_osdbuf(data)                                  (0x000007FF&(data))

#define VO_GCTL                                                       0x180055F0
#define VO_GCTL_reg_addr                                              "0xB80055F0"
#define VO_GCTL_reg                                                   0xB80055F0
#define VO_GCTL_inst_addr                                             "0x017C"
#define VO_GCTL_inst                                                  0x017C
#define VO_GCTL_go_shift                                              (3)
#define VO_GCTL_ysdscgo_shift                                         (2)
#define VO_GCTL_csdscgo_shift                                         (1)
#define VO_GCTL_write_data_shift                                      (0)
#define VO_GCTL_go_mask                                               (0x00000008)
#define VO_GCTL_ysdscgo_mask                                          (0x00000004)
#define VO_GCTL_csdscgo_mask                                          (0x00000002)
#define VO_GCTL_write_data_mask                                       (0x00000001)
#define VO_GCTL_go(data)                                              (0x00000008&((data)<<3))
#define VO_GCTL_ysdscgo(data)                                         (0x00000004&((data)<<2))
#define VO_GCTL_csdscgo(data)                                         (0x00000002&((data)<<1))
#define VO_GCTL_write_data(data)                                      (0x00000001&(data))
#define VO_GCTL_get_go(data)                                          ((0x00000008&(data))>>3)
#define VO_GCTL_get_ysdscgo(data)                                     ((0x00000004&(data))>>2)
#define VO_GCTL_get_csdscgo(data)                                     ((0x00000002&(data))>>1)
#define VO_GCTL_get_write_data(data)                                  (0x00000001&(data))
#endif
