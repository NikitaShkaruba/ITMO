                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 2.9.0 #5416 (Mar 22 2009) (MINGW32)
                              4 ; This file was generated Wed Nov 08 13:56:49 2017
                              5 ;--------------------------------------------------------
                              6 	.module interrupt
                              7 	.optsdcc -mmcs51 --model-small
                              8 	
                              9 ;--------------------------------------------------------
                             10 ; Public variables in this module
                             11 ;--------------------------------------------------------
                             12 	.globl _SetVector
                             13 ;--------------------------------------------------------
                             14 ; special function registers
                             15 ;--------------------------------------------------------
                             16 	.area RSEG    (DATA)
                             17 ;--------------------------------------------------------
                             18 ; special function bits
                             19 ;--------------------------------------------------------
                             20 	.area RSEG    (DATA)
                             21 ;--------------------------------------------------------
                             22 ; overlayable register banks
                             23 ;--------------------------------------------------------
                             24 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                      25 	.ds 8
                             26 ;--------------------------------------------------------
                             27 ; internal ram data
                             28 ;--------------------------------------------------------
                             29 	.area DSEG    (DATA)
                             30 ;--------------------------------------------------------
                             31 ; overlayable items in internal ram 
                             32 ;--------------------------------------------------------
                             33 	.area OSEG    (OVR,DATA)
                             34 ;--------------------------------------------------------
                             35 ; indirectly addressable internal ram data
                             36 ;--------------------------------------------------------
                             37 	.area ISEG    (DATA)
                             38 ;--------------------------------------------------------
                             39 ; absolute internal ram data
                             40 ;--------------------------------------------------------
                             41 	.area IABS    (ABS,DATA)
                             42 	.area IABS    (ABS,DATA)
                             43 ;--------------------------------------------------------
                             44 ; bit data
                             45 ;--------------------------------------------------------
                             46 	.area BSEG    (BIT)
                             47 ;--------------------------------------------------------
                             48 ; paged external ram data
                             49 ;--------------------------------------------------------
                             50 	.area PSEG    (PAG,XDATA)
                             51 ;--------------------------------------------------------
                             52 ; external ram data
                             53 ;--------------------------------------------------------
                             54 	.area XSEG    (XDATA)
                             55 ;--------------------------------------------------------
                             56 ; absolute external ram data
                             57 ;--------------------------------------------------------
                             58 	.area XABS    (ABS,XDATA)
                             59 ;--------------------------------------------------------
                             60 ; external initialized ram data
                             61 ;--------------------------------------------------------
                             62 	.area XISEG   (XDATA)
                             63 	.area HOME    (CODE)
                             64 	.area GSINIT0 (CODE)
                             65 	.area GSINIT1 (CODE)
                             66 	.area GSINIT2 (CODE)
                             67 	.area GSINIT3 (CODE)
                             68 	.area GSINIT4 (CODE)
                             69 	.area GSINIT5 (CODE)
                             70 	.area GSINIT  (CODE)
                             71 	.area GSFINAL (CODE)
                             72 	.area CSEG    (CODE)
                             73 ;--------------------------------------------------------
                             74 ; global & static initialisations
                             75 ;--------------------------------------------------------
                             76 	.area HOME    (CODE)
                             77 	.area GSINIT  (CODE)
                             78 	.area GSFINAL (CODE)
                             79 	.area GSINIT  (CODE)
                             80 ;--------------------------------------------------------
                             81 ; Home
                             82 ;--------------------------------------------------------
                             83 	.area HOME    (CODE)
                             84 	.area HOME    (CODE)
                             85 ;--------------------------------------------------------
                             86 ; code
                             87 ;--------------------------------------------------------
                             88 	.area CSEG    (CODE)
                             89 ;------------------------------------------------------------
                             90 ;Allocation info for local variables in function 'SetVector'
                             91 ;------------------------------------------------------------
                             92 ;Vector                    Allocated to stack - offset -5
                             93 ;Address                   Allocated to registers r2 r3 
                             94 ;TmpVector                 Allocated to registers r2 r3 
                             95 ;------------------------------------------------------------
                             96 ;	SRC/interrupt.c:8: void SetVector(unsigned char xdata * Address, void * Vector) {
                             97 ;	-----------------------------------------
                             98 ;	 function SetVector
                             99 ;	-----------------------------------------
   218F                     100 _SetVector:
                    0002    101 	ar2 = 0x02
                    0003    102 	ar3 = 0x03
                    0004    103 	ar4 = 0x04
                    0005    104 	ar5 = 0x05
                    0006    105 	ar6 = 0x06
                    0007    106 	ar7 = 0x07
                    0000    107 	ar0 = 0x00
                    0001    108 	ar1 = 0x01
   218F C0 0D               109 	push	_bp
   2191 85 81 0D            110 	mov	_bp,sp
                            111 ;	SRC/interrupt.c:11: *Address = 0x02;
   2194 AA 82               112 	mov	r2,dpl
   2196 AB 83               113 	mov  r3,dph
   2198 74 02               114 	mov	a,#0x02
   219A F0                  115 	movx	@dptr,a
                            116 ;	SRC/interrupt.c:13: TmpVector = (unsigned char xdata *) (Address + 1);
   219B 0A                  117 	inc	r2
   219C BA 00 01            118 	cjne	r2,#0x00,00103$
   219F 0B                  119 	inc	r3
   21A0                     120 00103$:
                            121 ;	SRC/interrupt.c:14: *TmpVector = (unsigned char) ((unsigned short)Vector >> 8);
   21A0 E5 0D               122 	mov	a,_bp
   21A2 24 FB               123 	add	a,#0xfb
   21A4 F8                  124 	mov	r0,a
   21A5 86 04               125 	mov	ar4,@r0
   21A7 08                  126 	inc	r0
   21A8 86 05               127 	mov	ar5,@r0
   21AA 8D 04               128 	mov	ar4,r5
   21AC 8A 82               129 	mov	dpl,r2
   21AE 8B 83               130 	mov	dph,r3
   21B0 EC                  131 	mov	a,r4
   21B1 F0                  132 	movx	@dptr,a
   21B2 A3                  133 	inc	dptr
   21B3 AA 82               134 	mov	r2,dpl
   21B5 AB 83               135 	mov	r3,dph
                            136 ;	SRC/interrupt.c:15: ++TmpVector;
                            137 ;	SRC/interrupt.c:16: *TmpVector = (unsigned char) Vector;
   21B7 E5 0D               138 	mov	a,_bp
   21B9 24 FB               139 	add	a,#0xfb
   21BB F8                  140 	mov	r0,a
   21BC 86 04               141 	mov	ar4,@r0
   21BE 8A 82               142 	mov	dpl,r2
   21C0 8B 83               143 	mov	dph,r3
   21C2 EC                  144 	mov	a,r4
   21C3 F0                  145 	movx	@dptr,a
   21C4 D0 0D               146 	pop	_bp
   21C6 22                  147 	ret
                            148 	.area CSEG    (CODE)
                            149 	.area CONST   (CODE)
                            150 	.area XINIT   (CODE)
                            151 	.area CABS    (ABS,CODE)
