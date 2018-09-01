
 

INT8U DVIorHDMI_flag=1; //0:DVI, 1:HDMI

INT8U xvYCC=0; //Extended-gamut YCC color space

INT8U PixelColorFormat=2; //0:RGB444, 1:Reserved, 2:YCbCr444, 3:YCbCr422

INT8U DeepColorEnable=1; //0:disable 1:enable

INT8U DeepColorDepth=4; //0:not indicated, 4:24bits, 5:30bits, 6:36bits, other:reserved

INT8U TimingGen=1;        //0: TVE 1:HDMI

INT8U Enable3D=0;

INT8U Format3D=0;         //0: frame packing 1: field alternative 2: line alternative 3: side-by-side

                           //4: l+depth 5: l+depth+graphics+graphics-depth 6: top-and-down

                           //8: side-by-side(half)


SET_HDMI_Video_480p(PixelColorFormat, DVIorHDMI_flag, DeepColorEnable, DeepColorDepth, xvYCC, TimingGen, Enable3D, Format3D);
VO_480p(Test_Pattern, TimingGen, Enable3D, Format3D);//Test_Pattern= 0 or 1, to switch frame buffer addr
GO_function(0, DVIorHDMI_flag, TimingGen);