                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 2.9.0 #5416 (Mar 22 2009) (MINGW32)
                              4 ; This file was generated Wed Nov 08 13:56:49 2017
                              5 ;--------------------------------------------------------
                              6 	.module buffer
                              7 	.optsdcc -mmcs51 --model-small
                              8 	
                              9 ;--------------------------------------------------------
                             10 ; Public variables in this module
                             11 ;--------------------------------------------------------
                             12 	.globl _false
                             13 	.globl _true
                             14 	.globl _SPR0
                             15 	.globl _SPR1
                             16 	.globl _CPHA
                             17 	.globl _CPOL
                             18 	.globl _SPIM
                             19 	.globl _SPE
                             20 	.globl _WCOL
                             21 	.globl _ISPI
                             22 	.globl _I2CI
                             23 	.globl _I2CTX
                             24 	.globl _I2CRS
                             25 	.globl _I2CM
                             26 	.globl _MDI
                             27 	.globl _MCO
                             28 	.globl _MDE
                             29 	.globl _MDO
                             30 	.globl _CS0
                             31 	.globl _CS1
                             32 	.globl _CS2
                             33 	.globl _CS3
                             34 	.globl _SCONV
                             35 	.globl _CCONV
                             36 	.globl _DMA
                             37 	.globl _ADCI
                             38 	.globl _P
                             39 	.globl _F1
                             40 	.globl _OV
                             41 	.globl _RS0
                             42 	.globl _RS1
                             43 	.globl _F0
                             44 	.globl _AC
                             45 	.globl _CY
                             46 	.globl _CAP2
                             47 	.globl _CNT2
                             48 	.globl _TR2
                             49 	.globl _XEN
                             50 	.globl _TCLK
                             51 	.globl _RCLK
                             52 	.globl _EXF2
                             53 	.globl _TF2
                             54 	.globl _WDE
                             55 	.globl _WDS
                             56 	.globl _WDR2
                             57 	.globl _WDR1
                             58 	.globl _PRE0
                             59 	.globl _PRE1
                             60 	.globl _PRE2
                             61 	.globl _PX0
                             62 	.globl _PT0
                             63 	.globl _PX1
                             64 	.globl _PT1
                             65 	.globl _PS
                             66 	.globl _PT2
                             67 	.globl _PADC
                             68 	.globl _PSI
                             69 	.globl _RXD
                             70 	.globl _TXD
                             71 	.globl _INT0
                             72 	.globl _INT1
                             73 	.globl _T0
                             74 	.globl _T1
                             75 	.globl _WR
                             76 	.globl _RD
                             77 	.globl _EX0
                             78 	.globl _ET0
                             79 	.globl _EX1
                             80 	.globl _ET1
                             81 	.globl _ES
                             82 	.globl _ET2
                             83 	.globl _EADC
                             84 	.globl _EA
                             85 	.globl _RI
                             86 	.globl _TI
                             87 	.globl _RB8
                             88 	.globl _TB8
                             89 	.globl _REN
                             90 	.globl _SM2
                             91 	.globl _SM1
                             92 	.globl _SM0
                             93 	.globl _T2
                             94 	.globl _T2EX
                             95 	.globl _IT0
                             96 	.globl _IE0
                             97 	.globl _IT1
                             98 	.globl _IE1
                             99 	.globl _TR0
                            100 	.globl _TF0
                            101 	.globl _TR1
                            102 	.globl _TF1
                            103 	.globl _DACCON
                            104 	.globl _DAC1H
                            105 	.globl _DAC1L
                            106 	.globl _DAC0H
                            107 	.globl _DAC0L
                            108 	.globl _SPICON
                            109 	.globl _SPIDAT
                            110 	.globl _ADCCON3
                            111 	.globl _ADCGAINH
                            112 	.globl _ADCGAINL
                            113 	.globl _ADCOFSH
                            114 	.globl _ADCOFSL
                            115 	.globl _B
                            116 	.globl _ADCCON1
                            117 	.globl _I2CCON
                            118 	.globl _ACC
                            119 	.globl _PSMCON
                            120 	.globl _ADCDATAH
                            121 	.globl _ADCDATAL
                            122 	.globl _ADCCON2
                            123 	.globl _DMAP
                            124 	.globl _DMAH
                            125 	.globl _DMAL
                            126 	.globl _PSW
                            127 	.globl _TH2
                            128 	.globl _TL2
                            129 	.globl _RCAP2H
                            130 	.globl _RCAP2L
                            131 	.globl _T2CON
                            132 	.globl _EADRL
                            133 	.globl _WDCON
                            134 	.globl _EDATA4
                            135 	.globl _EDATA3
                            136 	.globl _EDATA2
                            137 	.globl _EDATA1
                            138 	.globl _ETIM3
                            139 	.globl _ETIM2
                            140 	.globl _ETIM1
                            141 	.globl _ECON
                            142 	.globl _IP
                            143 	.globl _P3
                            144 	.globl _IE2
                            145 	.globl _IE
                            146 	.globl _P2
                            147 	.globl _I2CADD
                            148 	.globl _I2CDAT
                            149 	.globl _SBUF
                            150 	.globl _SCON
                            151 	.globl _P1
                            152 	.globl _TH1
                            153 	.globl _TH0
                            154 	.globl _TL1
                            155 	.globl _TL0
                            156 	.globl _TMOD
                            157 	.globl _TCON
                            158 	.globl _PCON
                            159 	.globl _DPP
                            160 	.globl _DPH
                            161 	.globl _DPL
                            162 	.globl _SP
                            163 	.globl _P0
                            164 	.globl _initialize_buffer
                            165 	.globl _is_buffer_empty
                            166 	.globl _is_buffer_full
                            167 	.globl _push_byte_to_buffer
                            168 	.globl _pop_byte_from_buffer
                            169 ;--------------------------------------------------------
                            170 ; special function registers
                            171 ;--------------------------------------------------------
                            172 	.area RSEG    (DATA)
                    0080    173 _P0	=	0x0080
                    0081    174 _SP	=	0x0081
                    0082    175 _DPL	=	0x0082
                    0083    176 _DPH	=	0x0083
                    0084    177 _DPP	=	0x0084
                    0087    178 _PCON	=	0x0087
                    0088    179 _TCON	=	0x0088
                    0089    180 _TMOD	=	0x0089
                    008A    181 _TL0	=	0x008a
                    008B    182 _TL1	=	0x008b
                    008C    183 _TH0	=	0x008c
                    008D    184 _TH1	=	0x008d
                    0090    185 _P1	=	0x0090
                    0098    186 _SCON	=	0x0098
                    0099    187 _SBUF	=	0x0099
                    009A    188 _I2CDAT	=	0x009a
                    009B    189 _I2CADD	=	0x009b
                    00A0    190 _P2	=	0x00a0
                    00A8    191 _IE	=	0x00a8
                    00A9    192 _IE2	=	0x00a9
                    00B0    193 _P3	=	0x00b0
                    00B8    194 _IP	=	0x00b8
                    00B9    195 _ECON	=	0x00b9
                    00BA    196 _ETIM1	=	0x00ba
                    00BB    197 _ETIM2	=	0x00bb
                    00C4    198 _ETIM3	=	0x00c4
                    00BC    199 _EDATA1	=	0x00bc
                    00BD    200 _EDATA2	=	0x00bd
                    00BE    201 _EDATA3	=	0x00be
                    00BF    202 _EDATA4	=	0x00bf
                    00C0    203 _WDCON	=	0x00c0
                    00C6    204 _EADRL	=	0x00c6
                    00C8    205 _T2CON	=	0x00c8
                    00CA    206 _RCAP2L	=	0x00ca
                    00CB    207 _RCAP2H	=	0x00cb
                    00CC    208 _TL2	=	0x00cc
                    00CD    209 _TH2	=	0x00cd
                    00D0    210 _PSW	=	0x00d0
                    00D2    211 _DMAL	=	0x00d2
                    00D3    212 _DMAH	=	0x00d3
                    00D4    213 _DMAP	=	0x00d4
                    00D8    214 _ADCCON2	=	0x00d8
                    00D9    215 _ADCDATAL	=	0x00d9
                    00DA    216 _ADCDATAH	=	0x00da
                    00DF    217 _PSMCON	=	0x00df
                    00E0    218 _ACC	=	0x00e0
                    00E8    219 _I2CCON	=	0x00e8
                    00EF    220 _ADCCON1	=	0x00ef
                    00F0    221 _B	=	0x00f0
                    00F1    222 _ADCOFSL	=	0x00f1
                    00F2    223 _ADCOFSH	=	0x00f2
                    00F3    224 _ADCGAINL	=	0x00f3
                    00F4    225 _ADCGAINH	=	0x00f4
                    00F5    226 _ADCCON3	=	0x00f5
                    00F7    227 _SPIDAT	=	0x00f7
                    00F8    228 _SPICON	=	0x00f8
                    00F9    229 _DAC0L	=	0x00f9
                    00FA    230 _DAC0H	=	0x00fa
                    00FB    231 _DAC1L	=	0x00fb
                    00FC    232 _DAC1H	=	0x00fc
                    00FD    233 _DACCON	=	0x00fd
                            234 ;--------------------------------------------------------
                            235 ; special function bits
                            236 ;--------------------------------------------------------
                            237 	.area RSEG    (DATA)
                    008F    238 _TF1	=	0x008f
                    008E    239 _TR1	=	0x008e
                    008D    240 _TF0	=	0x008d
                    008C    241 _TR0	=	0x008c
                    008B    242 _IE1	=	0x008b
                    008A    243 _IT1	=	0x008a
                    0089    244 _IE0	=	0x0089
                    0088    245 _IT0	=	0x0088
                    0091    246 _T2EX	=	0x0091
                    0090    247 _T2	=	0x0090
                    009F    248 _SM0	=	0x009f
                    009E    249 _SM1	=	0x009e
                    009D    250 _SM2	=	0x009d
                    009C    251 _REN	=	0x009c
                    009B    252 _TB8	=	0x009b
                    009A    253 _RB8	=	0x009a
                    0099    254 _TI	=	0x0099
                    0098    255 _RI	=	0x0098
                    00AF    256 _EA	=	0x00af
                    00AE    257 _EADC	=	0x00ae
                    00AD    258 _ET2	=	0x00ad
                    00AC    259 _ES	=	0x00ac
                    00AB    260 _ET1	=	0x00ab
                    00AA    261 _EX1	=	0x00aa
                    00A9    262 _ET0	=	0x00a9
                    00A8    263 _EX0	=	0x00a8
                    00B7    264 _RD	=	0x00b7
                    00B6    265 _WR	=	0x00b6
                    00B5    266 _T1	=	0x00b5
                    00B4    267 _T0	=	0x00b4
                    00B3    268 _INT1	=	0x00b3
                    00B2    269 _INT0	=	0x00b2
                    00B1    270 _TXD	=	0x00b1
                    00B0    271 _RXD	=	0x00b0
                    00BF    272 _PSI	=	0x00bf
                    00BE    273 _PADC	=	0x00be
                    00BD    274 _PT2	=	0x00bd
                    00BC    275 _PS	=	0x00bc
                    00BB    276 _PT1	=	0x00bb
                    00BA    277 _PX1	=	0x00ba
                    00B9    278 _PT0	=	0x00b9
                    00B8    279 _PX0	=	0x00b8
                    00C7    280 _PRE2	=	0x00c7
                    00C6    281 _PRE1	=	0x00c6
                    00C5    282 _PRE0	=	0x00c5
                    00C3    283 _WDR1	=	0x00c3
                    00C2    284 _WDR2	=	0x00c2
                    00C1    285 _WDS	=	0x00c1
                    00C0    286 _WDE	=	0x00c0
                    00CF    287 _TF2	=	0x00cf
                    00CE    288 _EXF2	=	0x00ce
                    00CD    289 _RCLK	=	0x00cd
                    00CC    290 _TCLK	=	0x00cc
                    00CB    291 _XEN	=	0x00cb
                    00CA    292 _TR2	=	0x00ca
                    00C9    293 _CNT2	=	0x00c9
                    00C8    294 _CAP2	=	0x00c8
                    00D7    295 _CY	=	0x00d7
                    00D6    296 _AC	=	0x00d6
                    00D5    297 _F0	=	0x00d5
                    00D4    298 _RS1	=	0x00d4
                    00D3    299 _RS0	=	0x00d3
                    00D2    300 _OV	=	0x00d2
                    00D1    301 _F1	=	0x00d1
                    00D0    302 _P	=	0x00d0
                    00DF    303 _ADCI	=	0x00df
                    00DE    304 _DMA	=	0x00de
                    00DD    305 _CCONV	=	0x00dd
                    00DC    306 _SCONV	=	0x00dc
                    00DB    307 _CS3	=	0x00db
                    00DA    308 _CS2	=	0x00da
                    00D9    309 _CS1	=	0x00d9
                    00D8    310 _CS0	=	0x00d8
                    00EF    311 _MDO	=	0x00ef
                    00EE    312 _MDE	=	0x00ee
                    00ED    313 _MCO	=	0x00ed
                    00EC    314 _MDI	=	0x00ec
                    00EB    315 _I2CM	=	0x00eb
                    00EA    316 _I2CRS	=	0x00ea
                    00E9    317 _I2CTX	=	0x00e9
                    00E8    318 _I2CI	=	0x00e8
                    00FF    319 _ISPI	=	0x00ff
                    00FE    320 _WCOL	=	0x00fe
                    00FD    321 _SPE	=	0x00fd
                    00FC    322 _SPIM	=	0x00fc
                    00FB    323 _CPOL	=	0x00fb
                    00FA    324 _CPHA	=	0x00fa
                    00F9    325 _SPR1	=	0x00f9
                    00F8    326 _SPR0	=	0x00f8
                            327 ;--------------------------------------------------------
                            328 ; overlayable register banks
                            329 ;--------------------------------------------------------
                            330 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     331 	.ds 8
                            332 ;--------------------------------------------------------
                            333 ; internal ram data
                            334 ;--------------------------------------------------------
                            335 	.area DSEG    (DATA)
                            336 ;--------------------------------------------------------
                            337 ; overlayable items in internal ram 
                            338 ;--------------------------------------------------------
                            339 	.area OSEG    (OVR,DATA)
                            340 ;--------------------------------------------------------
                            341 ; indirectly addressable internal ram data
                            342 ;--------------------------------------------------------
                            343 	.area ISEG    (DATA)
                            344 ;--------------------------------------------------------
                            345 ; absolute internal ram data
                            346 ;--------------------------------------------------------
                            347 	.area IABS    (ABS,DATA)
                            348 	.area IABS    (ABS,DATA)
                            349 ;--------------------------------------------------------
                            350 ; bit data
                            351 ;--------------------------------------------------------
                            352 	.area BSEG    (BIT)
                            353 ;--------------------------------------------------------
                            354 ; paged external ram data
                            355 ;--------------------------------------------------------
                            356 	.area PSEG    (PAG,XDATA)
                            357 ;--------------------------------------------------------
                            358 ; external ram data
                            359 ;--------------------------------------------------------
                            360 	.area XSEG    (XDATA)
                            361 ;--------------------------------------------------------
                            362 ; absolute external ram data
                            363 ;--------------------------------------------------------
                            364 	.area XABS    (ABS,XDATA)
                            365 ;--------------------------------------------------------
                            366 ; external initialized ram data
                            367 ;--------------------------------------------------------
                            368 	.area XISEG   (XDATA)
                            369 	.area HOME    (CODE)
                            370 	.area GSINIT0 (CODE)
                            371 	.area GSINIT1 (CODE)
                            372 	.area GSINIT2 (CODE)
                            373 	.area GSINIT3 (CODE)
                            374 	.area GSINIT4 (CODE)
                            375 	.area GSINIT5 (CODE)
                            376 	.area GSINIT  (CODE)
                            377 	.area GSFINAL (CODE)
                            378 	.area CSEG    (CODE)
                            379 ;--------------------------------------------------------
                            380 ; global & static initialisations
                            381 ;--------------------------------------------------------
                            382 	.area HOME    (CODE)
                            383 	.area GSINIT  (CODE)
                            384 	.area GSFINAL (CODE)
                            385 	.area GSINIT  (CODE)
                            386 ;--------------------------------------------------------
                            387 ; Home
                            388 ;--------------------------------------------------------
                            389 	.area HOME    (CODE)
                            390 	.area HOME    (CODE)
                            391 ;--------------------------------------------------------
                            392 ; code
                            393 ;--------------------------------------------------------
                            394 	.area CSEG    (CODE)
                            395 ;------------------------------------------------------------
                            396 ;Allocation info for local variables in function 'initialize_buffer'
                            397 ;------------------------------------------------------------
                            398 ;buffer                    Allocated to registers r2 r3 r4 
                            399 ;------------------------------------------------------------
                            400 ;	SRC/buffer.c:3: void initialize_buffer(Buffer* buffer) {
                            401 ;	-----------------------------------------
                            402 ;	 function initialize_buffer
                            403 ;	-----------------------------------------
   246C                     404 _initialize_buffer:
                    0002    405 	ar2 = 0x02
                    0003    406 	ar3 = 0x03
                    0004    407 	ar4 = 0x04
                    0005    408 	ar5 = 0x05
                    0006    409 	ar6 = 0x06
                    0007    410 	ar7 = 0x07
                    0000    411 	ar0 = 0x00
                    0001    412 	ar1 = 0x01
   246C AA 82               413 	mov	r2,dpl
   246E AB 83               414 	mov	r3,dph
   2470 AC F0               415 	mov	r4,b
                            416 ;	SRC/buffer.c:4: buffer->head=0;
   2472 74 2A               417 	mov	a,#0x2A
   2474 2A                  418 	add	a,r2
   2475 FD                  419 	mov	r5,a
   2476 E4                  420 	clr	a
   2477 3B                  421 	addc	a,r3
   2478 FE                  422 	mov	r6,a
   2479 8C 07               423 	mov	ar7,r4
   247B 8D 82               424 	mov	dpl,r5
   247D 8E 83               425 	mov	dph,r6
   247F 8F F0               426 	mov	b,r7
   2481 E4                  427 	clr	a
   2482 12 28 C3            428 	lcall	__gptrput
                            429 ;	SRC/buffer.c:5: buffer->tail=0;
   2485 74 2B               430 	mov	a,#0x2B
   2487 2A                  431 	add	a,r2
   2488 FD                  432 	mov	r5,a
   2489 E4                  433 	clr	a
   248A 3B                  434 	addc	a,r3
   248B FE                  435 	mov	r6,a
   248C 8C 07               436 	mov	ar7,r4
   248E 8D 82               437 	mov	dpl,r5
   2490 8E 83               438 	mov	dph,r6
   2492 8F F0               439 	mov	b,r7
   2494 E4                  440 	clr	a
   2495 12 28 C3            441 	lcall	__gptrput
                            442 ;	SRC/buffer.c:6: buffer->len=0;
   2498 74 2C               443 	mov	a,#0x2C
   249A 2A                  444 	add	a,r2
   249B FA                  445 	mov	r2,a
   249C E4                  446 	clr	a
   249D 3B                  447 	addc	a,r3
   249E FB                  448 	mov	r3,a
   249F 8A 82               449 	mov	dpl,r2
   24A1 8B 83               450 	mov	dph,r3
   24A3 8C F0               451 	mov	b,r4
   24A5 E4                  452 	clr	a
   24A6 02 28 C3            453 	ljmp	__gptrput
                            454 ;------------------------------------------------------------
                            455 ;Allocation info for local variables in function 'is_buffer_empty'
                            456 ;------------------------------------------------------------
                            457 ;buffer                    Allocated to registers r2 r3 r4 
                            458 ;------------------------------------------------------------
                            459 ;	SRC/buffer.c:9: bool is_buffer_empty(Buffer* buffer) {
                            460 ;	-----------------------------------------
                            461 ;	 function is_buffer_empty
                            462 ;	-----------------------------------------
   24A9                     463 _is_buffer_empty:
   24A9 AA 82               464 	mov	r2,dpl
   24AB AB 83               465 	mov	r3,dph
   24AD AC F0               466 	mov	r4,b
                            467 ;	SRC/buffer.c:10: return buffer->len == 0;
   24AF 74 2C               468 	mov	a,#0x2C
   24B1 2A                  469 	add	a,r2
   24B2 FA                  470 	mov	r2,a
   24B3 E4                  471 	clr	a
   24B4 3B                  472 	addc	a,r3
   24B5 FB                  473 	mov	r3,a
   24B6 8A 82               474 	mov	dpl,r2
   24B8 8B 83               475 	mov	dph,r3
   24BA 8C F0               476 	mov	b,r4
   24BC 12 28 DC            477 	lcall	__gptrget
   24BF FA                  478 	mov	r2,a
   24C0 E4                  479 	clr	a
   24C1 BA 00 01            480 	cjne	r2,#0x00,00103$
   24C4 04                  481 	inc	a
   24C5                     482 00103$:
   24C5 F5 82               483 	mov	dpl,a
   24C7 22                  484 	ret
                            485 ;------------------------------------------------------------
                            486 ;Allocation info for local variables in function 'is_buffer_full'
                            487 ;------------------------------------------------------------
                            488 ;buffer                    Allocated to registers r2 r3 r4 
                            489 ;------------------------------------------------------------
                            490 ;	SRC/buffer.c:13: bool is_buffer_full(Buffer* buffer) {
                            491 ;	-----------------------------------------
                            492 ;	 function is_buffer_full
                            493 ;	-----------------------------------------
   24C8                     494 _is_buffer_full:
   24C8 AA 82               495 	mov	r2,dpl
   24CA AB 83               496 	mov	r3,dph
   24CC AC F0               497 	mov	r4,b
                            498 ;	SRC/buffer.c:14: return buffer->len == BUFFER_LEN;
   24CE 74 2C               499 	mov	a,#0x2C
   24D0 2A                  500 	add	a,r2
   24D1 FA                  501 	mov	r2,a
   24D2 E4                  502 	clr	a
   24D3 3B                  503 	addc	a,r3
   24D4 FB                  504 	mov	r3,a
   24D5 8A 82               505 	mov	dpl,r2
   24D7 8B 83               506 	mov	dph,r3
   24D9 8C F0               507 	mov	b,r4
   24DB 12 28 DC            508 	lcall	__gptrget
   24DE FA                  509 	mov	r2,a
   24DF E4                  510 	clr	a
   24E0 BA 2A 01            511 	cjne	r2,#0x2A,00103$
   24E3 04                  512 	inc	a
   24E4                     513 00103$:
   24E4 F5 82               514 	mov	dpl,a
   24E6 22                  515 	ret
                            516 ;------------------------------------------------------------
                            517 ;Allocation info for local variables in function 'push_byte_to_buffer'
                            518 ;------------------------------------------------------------
                            519 ;dat                       Allocated to stack - offset -3
                            520 ;buffer                    Allocated to stack - offset 1
                            521 ;sloc0                     Allocated to stack - offset 4
                            522 ;sloc1                     Allocated to stack - offset 5
                            523 ;------------------------------------------------------------
                            524 ;	SRC/buffer.c:17: void push_byte_to_buffer(Buffer* buffer, u8 dat) {
                            525 ;	-----------------------------------------
                            526 ;	 function push_byte_to_buffer
                            527 ;	-----------------------------------------
   24E7                     528 _push_byte_to_buffer:
   24E7 C0 0D               529 	push	_bp
   24E9 85 81 0D            530 	mov	_bp,sp
   24EC C0 82               531 	push	dpl
   24EE C0 83               532 	push	dph
   24F0 C0 F0               533 	push	b
   24F2 E5 81               534 	mov	a,sp
   24F4 24 07               535 	add	a,#0x07
   24F6 F5 81               536 	mov	sp,a
                            537 ;	SRC/buffer.c:18: buffer->mem[buffer->head] = dat;
   24F8 A8 0D               538 	mov	r0,_bp
   24FA 08                  539 	inc	r0
   24FB 74 2A               540 	mov	a,#0x2A
   24FD 26                  541 	add	a,@r0
   24FE FD                  542 	mov	r5,a
   24FF E4                  543 	clr	a
   2500 08                  544 	inc	r0
   2501 36                  545 	addc	a,@r0
   2502 FE                  546 	mov	r6,a
   2503 08                  547 	inc	r0
   2504 86 07               548 	mov	ar7,@r0
   2506 8D 82               549 	mov	dpl,r5
   2508 8E 83               550 	mov	dph,r6
   250A 8F F0               551 	mov	b,r7
   250C E5 0D               552 	mov	a,_bp
   250E 24 04               553 	add	a,#0x04
   2510 F8                  554 	mov	r0,a
   2511 12 28 DC            555 	lcall	__gptrget
   2514 F6                  556 	mov	@r0,a
   2515 A8 0D               557 	mov	r0,_bp
   2517 08                  558 	inc	r0
   2518 E5 0D               559 	mov	a,_bp
   251A 24 04               560 	add	a,#0x04
   251C F9                  561 	mov	r1,a
   251D E7                  562 	mov	a,@r1
   251E 26                  563 	add	a,@r0
   251F FB                  564 	mov	r3,a
   2520 E4                  565 	clr	a
   2521 08                  566 	inc	r0
   2522 36                  567 	addc	a,@r0
   2523 FC                  568 	mov	r4,a
   2524 08                  569 	inc	r0
   2525 86 02               570 	mov	ar2,@r0
   2527 8B 82               571 	mov	dpl,r3
   2529 8C 83               572 	mov	dph,r4
   252B 8A F0               573 	mov	b,r2
   252D A8 0D               574 	mov	r0,_bp
   252F 18                  575 	dec	r0
   2530 18                  576 	dec	r0
   2531 18                  577 	dec	r0
   2532 E6                  578 	mov	a,@r0
   2533 12 28 C3            579 	lcall	__gptrput
                            580 ;	SRC/buffer.c:19: buffer->head++;
   2536 E5 0D               581 	mov	a,_bp
   2538 24 04               582 	add	a,#0x04
   253A F8                  583 	mov	r0,a
   253B E6                  584 	mov	a,@r0
   253C 04                  585 	inc	a
   253D FB                  586 	mov	r3,a
   253E 8D 82               587 	mov	dpl,r5
   2540 8E 83               588 	mov	dph,r6
   2542 8F F0               589 	mov	b,r7
   2544 12 28 C3            590 	lcall	__gptrput
                            591 ;	SRC/buffer.c:20: buffer->len++;
   2547 A8 0D               592 	mov	r0,_bp
   2549 08                  593 	inc	r0
   254A E5 0D               594 	mov	a,_bp
   254C 24 05               595 	add	a,#0x05
   254E F9                  596 	mov	r1,a
   254F 74 2C               597 	mov	a,#0x2C
   2551 26                  598 	add	a,@r0
   2552 F7                  599 	mov	@r1,a
   2553 E4                  600 	clr	a
   2554 08                  601 	inc	r0
   2555 36                  602 	addc	a,@r0
   2556 09                  603 	inc	r1
   2557 F7                  604 	mov	@r1,a
   2558 08                  605 	inc	r0
   2559 09                  606 	inc	r1
   255A E6                  607 	mov	a,@r0
   255B F7                  608 	mov	@r1,a
   255C E5 0D               609 	mov	a,_bp
   255E 24 05               610 	add	a,#0x05
   2560 F8                  611 	mov	r0,a
   2561 86 82               612 	mov	dpl,@r0
   2563 08                  613 	inc	r0
   2564 86 83               614 	mov	dph,@r0
   2566 08                  615 	inc	r0
   2567 86 F0               616 	mov	b,@r0
   2569 12 28 DC            617 	lcall	__gptrget
   256C FA                  618 	mov	r2,a
   256D 0A                  619 	inc	r2
   256E E5 0D               620 	mov	a,_bp
   2570 24 05               621 	add	a,#0x05
   2572 F8                  622 	mov	r0,a
   2573 86 82               623 	mov	dpl,@r0
   2575 08                  624 	inc	r0
   2576 86 83               625 	mov	dph,@r0
   2578 08                  626 	inc	r0
   2579 86 F0               627 	mov	b,@r0
   257B EA                  628 	mov	a,r2
   257C 12 28 C3            629 	lcall	__gptrput
                            630 ;	SRC/buffer.c:22: if (buffer->head == BUFFER_LEN) {
   257F BB 2A 0A            631 	cjne	r3,#0x2A,00103$
                            632 ;	SRC/buffer.c:23: buffer->head = 0;
   2582 8D 82               633 	mov	dpl,r5
   2584 8E 83               634 	mov	dph,r6
   2586 8F F0               635 	mov	b,r7
   2588 E4                  636 	clr	a
   2589 12 28 C3            637 	lcall	__gptrput
   258C                     638 00103$:
   258C 85 0D 81            639 	mov	sp,_bp
   258F D0 0D               640 	pop	_bp
   2591 22                  641 	ret
                            642 ;------------------------------------------------------------
                            643 ;Allocation info for local variables in function 'pop_byte_from_buffer'
                            644 ;------------------------------------------------------------
                            645 ;buffer                    Allocated to stack - offset 1
                            646 ;dat                       Allocated to registers r3 
                            647 ;sloc0                     Allocated to stack - offset 4
                            648 ;sloc1                     Allocated to stack - offset 5
                            649 ;------------------------------------------------------------
                            650 ;	SRC/buffer.c:27: u8 pop_byte_from_buffer(Buffer* buffer) {
                            651 ;	-----------------------------------------
                            652 ;	 function pop_byte_from_buffer
                            653 ;	-----------------------------------------
   2592                     654 _pop_byte_from_buffer:
   2592 C0 0D               655 	push	_bp
   2594 85 81 0D            656 	mov	_bp,sp
   2597 C0 82               657 	push	dpl
   2599 C0 83               658 	push	dph
   259B C0 F0               659 	push	b
   259D E5 81               660 	mov	a,sp
   259F 24 07               661 	add	a,#0x07
   25A1 F5 81               662 	mov	sp,a
                            663 ;	SRC/buffer.c:29: dat= buffer->mem[buffer->tail];
   25A3 A8 0D               664 	mov	r0,_bp
   25A5 08                  665 	inc	r0
   25A6 74 2B               666 	mov	a,#0x2B
   25A8 26                  667 	add	a,@r0
   25A9 FD                  668 	mov	r5,a
   25AA E4                  669 	clr	a
   25AB 08                  670 	inc	r0
   25AC 36                  671 	addc	a,@r0
   25AD FE                  672 	mov	r6,a
   25AE 08                  673 	inc	r0
   25AF 86 07               674 	mov	ar7,@r0
   25B1 8D 82               675 	mov	dpl,r5
   25B3 8E 83               676 	mov	dph,r6
   25B5 8F F0               677 	mov	b,r7
   25B7 E5 0D               678 	mov	a,_bp
   25B9 24 04               679 	add	a,#0x04
   25BB F8                  680 	mov	r0,a
   25BC 12 28 DC            681 	lcall	__gptrget
   25BF F6                  682 	mov	@r0,a
   25C0 A8 0D               683 	mov	r0,_bp
   25C2 08                  684 	inc	r0
   25C3 E5 0D               685 	mov	a,_bp
   25C5 24 04               686 	add	a,#0x04
   25C7 F9                  687 	mov	r1,a
   25C8 E7                  688 	mov	a,@r1
   25C9 26                  689 	add	a,@r0
   25CA FB                  690 	mov	r3,a
   25CB E4                  691 	clr	a
   25CC 08                  692 	inc	r0
   25CD 36                  693 	addc	a,@r0
   25CE FC                  694 	mov	r4,a
   25CF 08                  695 	inc	r0
   25D0 86 02               696 	mov	ar2,@r0
   25D2 8B 82               697 	mov	dpl,r3
   25D4 8C 83               698 	mov	dph,r4
   25D6 8A F0               699 	mov	b,r2
   25D8 12 28 DC            700 	lcall	__gptrget
   25DB FB                  701 	mov	r3,a
                            702 ;	SRC/buffer.c:30: buffer->tail++;
   25DC E5 0D               703 	mov	a,_bp
   25DE 24 04               704 	add	a,#0x04
   25E0 F8                  705 	mov	r0,a
   25E1 E6                  706 	mov	a,@r0
   25E2 04                  707 	inc	a
   25E3 FC                  708 	mov	r4,a
   25E4 8D 82               709 	mov	dpl,r5
   25E6 8E 83               710 	mov	dph,r6
   25E8 8F F0               711 	mov	b,r7
   25EA 12 28 C3            712 	lcall	__gptrput
                            713 ;	SRC/buffer.c:31: buffer->len--;
   25ED A8 0D               714 	mov	r0,_bp
   25EF 08                  715 	inc	r0
   25F0 E5 0D               716 	mov	a,_bp
   25F2 24 05               717 	add	a,#0x05
   25F4 F9                  718 	mov	r1,a
   25F5 74 2C               719 	mov	a,#0x2C
   25F7 26                  720 	add	a,@r0
   25F8 F7                  721 	mov	@r1,a
   25F9 E4                  722 	clr	a
   25FA 08                  723 	inc	r0
   25FB 36                  724 	addc	a,@r0
   25FC 09                  725 	inc	r1
   25FD F7                  726 	mov	@r1,a
   25FE 08                  727 	inc	r0
   25FF 09                  728 	inc	r1
   2600 E6                  729 	mov	a,@r0
   2601 F7                  730 	mov	@r1,a
   2602 E5 0D               731 	mov	a,_bp
   2604 24 05               732 	add	a,#0x05
   2606 F8                  733 	mov	r0,a
   2607 86 82               734 	mov	dpl,@r0
   2609 08                  735 	inc	r0
   260A 86 83               736 	mov	dph,@r0
   260C 08                  737 	inc	r0
   260D 86 F0               738 	mov	b,@r0
   260F 12 28 DC            739 	lcall	__gptrget
   2612 FA                  740 	mov	r2,a
   2613 1A                  741 	dec	r2
   2614 E5 0D               742 	mov	a,_bp
   2616 24 05               743 	add	a,#0x05
   2618 F8                  744 	mov	r0,a
   2619 86 82               745 	mov	dpl,@r0
   261B 08                  746 	inc	r0
   261C 86 83               747 	mov	dph,@r0
   261E 08                  748 	inc	r0
   261F 86 F0               749 	mov	b,@r0
   2621 EA                  750 	mov	a,r2
   2622 12 28 C3            751 	lcall	__gptrput
                            752 ;	SRC/buffer.c:33: if (buffer->tail == BUFFER_LEN) {
   2625 BC 2A 0A            753 	cjne	r4,#0x2A,00102$
                            754 ;	SRC/buffer.c:34: buffer->tail = 0;
   2628 8D 82               755 	mov	dpl,r5
   262A 8E 83               756 	mov	dph,r6
   262C 8F F0               757 	mov	b,r7
   262E E4                  758 	clr	a
   262F 12 28 C3            759 	lcall	__gptrput
   2632                     760 00102$:
                            761 ;	SRC/buffer.c:37: return dat;
   2632 8B 82               762 	mov	dpl,r3
   2634 85 0D 81            763 	mov	sp,_bp
   2637 D0 0D               764 	pop	_bp
   2639 22                  765 	ret
                            766 	.area CSEG    (CODE)
                            767 	.area CONST   (CODE)
   2901                     768 _true:
   2901 FF                  769 	.db #0xFF
   2902                     770 _false:
   2902 00                  771 	.db #0x00
                            772 	.area XINIT   (CODE)
                            773 	.area CABS    (ABS,CODE)
