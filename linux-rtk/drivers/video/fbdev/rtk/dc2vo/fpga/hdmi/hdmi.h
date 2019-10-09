#ifndef __FPGA_HDMI_H__
#define __FPGA_HDMI_H__
void SET_HDMI_Video_480p(
        unsigned short int Pixel_Colocr_Format,
        unsigned short int DVI_or_HDMI,
        unsigned short int Deep_Color,
        unsigned short int Deep_Depth,
        unsigned short int xv_YCC,
        unsigned short int Timing_Gen,
        unsigned short int En_3D,
        unsigned short int Format_3D);
#endif
