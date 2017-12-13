                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 2.9.0 #5416 (Mar 22 2009) (MINGW32)
                              4 ; This file was generated Wed Nov 22 12:36:27 2017
                              5 ;--------------------------------------------------------
                              6 	.module handler
                              7 	.optsdcc -mmcs51 --model-small
                              8 	
                              9 ;--------------------------------------------------------
                             10 ; Public variables in this module
                             11 ;--------------------------------------------------------
                             12 	.globl _NUMBER_LIMIT
                             13 	.globl _DIP_POLL_MODE
                             14 	.globl _false
                             15 	.globl _true
                             16 	.globl _to_hex
                             17 	.globl _error
                             18 	.globl _reset
                             19 	.globl _read_dip
                             20 	.globl _SPR0
                             21 	.globl _SPR1
                             22 	.globl _CPHA
                             23 	.globl _CPOL
                             24 	.globl _SPIM
                             25 	.globl _SPE
                             26 	.globl _WCOL
                             27 	.globl _ISPI
                             28 	.globl _I2CI
                             29 	.globl _I2CTX
                             30 	.globl _I2CRS
                             31 	.globl _I2CM
                             32 	.globl _MDI
                             33 	.globl _MCO
                             34 	.globl _MDE
                             35 	.globl _MDO
                             36 	.globl _CS0
                             37 	.globl _CS1
                             38 	.globl _CS2
                             39 	.globl _CS3
                             40 	.globl _SCONV
                             41 	.globl _CCONV
                             42 	.globl _DMA
                             43 	.globl _ADCI
                             44 	.globl _P
                             45 	.globl _F1
                             46 	.globl _OV
                             47 	.globl _RS0
                             48 	.globl _RS1
                             49 	.globl _F0
                             50 	.globl _AC
                             51 	.globl _CY
                             52 	.globl _CAP2
                             53 	.globl _CNT2
                             54 	.globl _TR2
                             55 	.globl _XEN
                             56 	.globl _TCLK
                             57 	.globl _RCLK
                             58 	.globl _EXF2
                             59 	.globl _TF2
                             60 	.globl _WDE
                             61 	.globl _WDS
                             62 	.globl _WDR2
                             63 	.globl _WDR1
                             64 	.globl _PRE0
                             65 	.globl _PRE1
                             66 	.globl _PRE2
                             67 	.globl _PX0
                             68 	.globl _PT0
                             69 	.globl _PX1
                             70 	.globl _PT1
                             71 	.globl _PS
                             72 	.globl _PT2
                             73 	.globl _PADC
                             74 	.globl _PSI
                             75 	.globl _RXD
                             76 	.globl _TXD
                             77 	.globl _INT0
                             78 	.globl _INT1
                             79 	.globl _T0
                             80 	.globl _T1
                             81 	.globl _WR
                             82 	.globl _RD
                             83 	.globl _EX0
                             84 	.globl _ET0
                             85 	.globl _EX1
                             86 	.globl _ET1
                             87 	.globl _ES
                             88 	.globl _ET2
                             89 	.globl _EADC
                             90 	.globl _EA
                             91 	.globl _RI
                             92 	.globl _TI
                             93 	.globl _RB8
                             94 	.globl _TB8
                             95 	.globl _REN
                             96 	.globl _SM2
                             97 	.globl _SM1
                             98 	.globl _SM0
                             99 	.globl _T2
                            100 	.globl _T2EX
                            101 	.globl _IT0
                            102 	.globl _IE0
                            103 	.globl _IT1
                            104 	.globl _IE1
                            105 	.globl _TR0
                            106 	.globl _TF0
                            107 	.globl _TR1
                            108 	.globl _TF1
                            109 	.globl _DACCON
                            110 	.globl _DAC1H
                            111 	.globl _DAC1L
                            112 	.globl _DAC0H
                            113 	.globl _DAC0L
                            114 	.globl _SPICON
                            115 	.globl _SPIDAT
                            116 	.globl _ADCCON3
                            117 	.globl _ADCGAINH
                            118 	.globl _ADCGAINL
                            119 	.globl _ADCOFSH
                            120 	.globl _ADCOFSL
                            121 	.globl _B
                            122 	.globl _ADCCON1
                            123 	.globl _I2CCON
                            124 	.globl _ACC
                            125 	.globl _PSMCON
                            126 	.globl _ADCDATAH
                            127 	.globl _ADCDATAL
                            128 	.globl _ADCCON2
                            129 	.globl _DMAP
                            130 	.globl _DMAH
                            131 	.globl _DMAL
                            132 	.globl _PSW
                            133 	.globl _TH2
                            134 	.globl _TL2
                            135 	.globl _RCAP2H
                            136 	.globl _RCAP2L
                            137 	.globl _T2CON
                            138 	.globl _EADRL
                            139 	.globl _WDCON
                            140 	.globl _EDATA4
                            141 	.globl _EDATA3
                            142 	.globl _EDATA2
                            143 	.globl _EDATA1
                            144 	.globl _ETIM3
                            145 	.globl _ETIM2
                            146 	.globl _ETIM1
                            147 	.globl _ECON
                            148 	.globl _IP
                            149 	.globl _P3
                            150 	.globl _IE2
                            151 	.globl _IE
                            152 	.globl _P2
                            153 	.globl _I2CADD
                            154 	.globl _I2CDAT
                            155 	.globl _SBUF
                            156 	.globl _SCON
                            157 	.globl _P1
                            158 	.globl _TH1
                            159 	.globl _TH0
                            160 	.globl _TL1
                            161 	.globl _TL0
                            162 	.globl _TMOD
                            163 	.globl _TCON
                            164 	.globl _PCON
                            165 	.globl _DPP
                            166 	.globl _DPH
                            167 	.globl _DPL
                            168 	.globl _SP
                            169 	.globl _P0
                            170 	.globl _v
                            171 	.globl _state
                            172 	.globl _number
                            173 	.globl _mode
                            174 	.globl _initialize_handler
                            175 	.globl _test_loop
                            176 	.globl _int_loop
                            177 	.globl _handler_loop
                            178 	.globl _handler_int
                            179 ;--------------------------------------------------------
                            180 ; special function registers
                            181 ;--------------------------------------------------------
                            182 	.area RSEG    (DATA)
                    0080    183 _P0	=	0x0080
                    0081    184 _SP	=	0x0081
                    0082    185 _DPL	=	0x0082
                    0083    186 _DPH	=	0x0083
                    0084    187 _DPP	=	0x0084
                    0087    188 _PCON	=	0x0087
                    0088    189 _TCON	=	0x0088
                    0089    190 _TMOD	=	0x0089
                    008A    191 _TL0	=	0x008a
                    008B    192 _TL1	=	0x008b
                    008C    193 _TH0	=	0x008c
                    008D    194 _TH1	=	0x008d
                    0090    195 _P1	=	0x0090
                    0098    196 _SCON	=	0x0098
                    0099    197 _SBUF	=	0x0099
                    009A    198 _I2CDAT	=	0x009a
                    009B    199 _I2CADD	=	0x009b
                    00A0    200 _P2	=	0x00a0
                    00A8    201 _IE	=	0x00a8
                    00A9    202 _IE2	=	0x00a9
                    00B0    203 _P3	=	0x00b0
                    00B8    204 _IP	=	0x00b8
                    00B9    205 _ECON	=	0x00b9
                    00BA    206 _ETIM1	=	0x00ba
                    00BB    207 _ETIM2	=	0x00bb
                    00C4    208 _ETIM3	=	0x00c4
                    00BC    209 _EDATA1	=	0x00bc
                    00BD    210 _EDATA2	=	0x00bd
                    00BE    211 _EDATA3	=	0x00be
                    00BF    212 _EDATA4	=	0x00bf
                    00C0    213 _WDCON	=	0x00c0
                    00C6    214 _EADRL	=	0x00c6
                    00C8    215 _T2CON	=	0x00c8
                    00CA    216 _RCAP2L	=	0x00ca
                    00CB    217 _RCAP2H	=	0x00cb
                    00CC    218 _TL2	=	0x00cc
                    00CD    219 _TH2	=	0x00cd
                    00D0    220 _PSW	=	0x00d0
                    00D2    221 _DMAL	=	0x00d2
                    00D3    222 _DMAH	=	0x00d3
                    00D4    223 _DMAP	=	0x00d4
                    00D8    224 _ADCCON2	=	0x00d8
                    00D9    225 _ADCDATAL	=	0x00d9
                    00DA    226 _ADCDATAH	=	0x00da
                    00DF    227 _PSMCON	=	0x00df
                    00E0    228 _ACC	=	0x00e0
                    00E8    229 _I2CCON	=	0x00e8
                    00EF    230 _ADCCON1	=	0x00ef
                    00F0    231 _B	=	0x00f0
                    00F1    232 _ADCOFSL	=	0x00f1
                    00F2    233 _ADCOFSH	=	0x00f2
                    00F3    234 _ADCGAINL	=	0x00f3
                    00F4    235 _ADCGAINH	=	0x00f4
                    00F5    236 _ADCCON3	=	0x00f5
                    00F7    237 _SPIDAT	=	0x00f7
                    00F8    238 _SPICON	=	0x00f8
                    00F9    239 _DAC0L	=	0x00f9
                    00FA    240 _DAC0H	=	0x00fa
                    00FB    241 _DAC1L	=	0x00fb
                    00FC    242 _DAC1H	=	0x00fc
                    00FD    243 _DACCON	=	0x00fd
                            244 ;--------------------------------------------------------
                            245 ; special function bits
                            246 ;--------------------------------------------------------
                            247 	.area RSEG    (DATA)
                    008F    248 _TF1	=	0x008f
                    008E    249 _TR1	=	0x008e
                    008D    250 _TF0	=	0x008d
                    008C    251 _TR0	=	0x008c
                    008B    252 _IE1	=	0x008b
                    008A    253 _IT1	=	0x008a
                    0089    254 _IE0	=	0x0089
                    0088    255 _IT0	=	0x0088
                    0091    256 _T2EX	=	0x0091
                    0090    257 _T2	=	0x0090
                    009F    258 _SM0	=	0x009f
                    009E    259 _SM1	=	0x009e
                    009D    260 _SM2	=	0x009d
                    009C    261 _REN	=	0x009c
                    009B    262 _TB8	=	0x009b
                    009A    263 _RB8	=	0x009a
                    0099    264 _TI	=	0x0099
                    0098    265 _RI	=	0x0098
                    00AF    266 _EA	=	0x00af
                    00AE    267 _EADC	=	0x00ae
                    00AD    268 _ET2	=	0x00ad
                    00AC    269 _ES	=	0x00ac
                    00AB    270 _ET1	=	0x00ab
                    00AA    271 _EX1	=	0x00aa
                    00A9    272 _ET0	=	0x00a9
                    00A8    273 _EX0	=	0x00a8
                    00B7    274 _RD	=	0x00b7
                    00B6    275 _WR	=	0x00b6
                    00B5    276 _T1	=	0x00b5
                    00B4    277 _T0	=	0x00b4
                    00B3    278 _INT1	=	0x00b3
                    00B2    279 _INT0	=	0x00b2
                    00B1    280 _TXD	=	0x00b1
                    00B0    281 _RXD	=	0x00b0
                    00BF    282 _PSI	=	0x00bf
                    00BE    283 _PADC	=	0x00be
                    00BD    284 _PT2	=	0x00bd
                    00BC    285 _PS	=	0x00bc
                    00BB    286 _PT1	=	0x00bb
                    00BA    287 _PX1	=	0x00ba
                    00B9    288 _PT0	=	0x00b9
                    00B8    289 _PX0	=	0x00b8
                    00C7    290 _PRE2	=	0x00c7
                    00C6    291 _PRE1	=	0x00c6
                    00C5    292 _PRE0	=	0x00c5
                    00C3    293 _WDR1	=	0x00c3
                    00C2    294 _WDR2	=	0x00c2
                    00C1    295 _WDS	=	0x00c1
                    00C0    296 _WDE	=	0x00c0
                    00CF    297 _TF2	=	0x00cf
                    00CE    298 _EXF2	=	0x00ce
                    00CD    299 _RCLK	=	0x00cd
                    00CC    300 _TCLK	=	0x00cc
                    00CB    301 _XEN	=	0x00cb
                    00CA    302 _TR2	=	0x00ca
                    00C9    303 _CNT2	=	0x00c9
                    00C8    304 _CAP2	=	0x00c8
                    00D7    305 _CY	=	0x00d7
                    00D6    306 _AC	=	0x00d6
                    00D5    307 _F0	=	0x00d5
                    00D4    308 _RS1	=	0x00d4
                    00D3    309 _RS0	=	0x00d3
                    00D2    310 _OV	=	0x00d2
                    00D1    311 _F1	=	0x00d1
                    00D0    312 _P	=	0x00d0
                    00DF    313 _ADCI	=	0x00df
                    00DE    314 _DMA	=	0x00de
                    00DD    315 _CCONV	=	0x00dd
                    00DC    316 _SCONV	=	0x00dc
                    00DB    317 _CS3	=	0x00db
                    00DA    318 _CS2	=	0x00da
                    00D9    319 _CS1	=	0x00d9
                    00D8    320 _CS0	=	0x00d8
                    00EF    321 _MDO	=	0x00ef
                    00EE    322 _MDE	=	0x00ee
                    00ED    323 _MCO	=	0x00ed
                    00EC    324 _MDI	=	0x00ec
                    00EB    325 _I2CM	=	0x00eb
                    00EA    326 _I2CRS	=	0x00ea
                    00E9    327 _I2CTX	=	0x00e9
                    00E8    328 _I2CI	=	0x00e8
                    00FF    329 _ISPI	=	0x00ff
                    00FE    330 _WCOL	=	0x00fe
                    00FD    331 _SPE	=	0x00fd
                    00FC    332 _SPIM	=	0x00fc
                    00FB    333 _CPOL	=	0x00fb
                    00FA    334 _CPHA	=	0x00fa
                    00F9    335 _SPR1	=	0x00f9
                    00F8    336 _SPR0	=	0x00f8
                            337 ;--------------------------------------------------------
                            338 ; overlayable register banks
                            339 ;--------------------------------------------------------
                            340 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     341 	.ds 8
                            342 ;--------------------------------------------------------
                            343 ; internal ram data
                            344 ;--------------------------------------------------------
                            345 	.area DSEG    (DATA)
   0011                     346 _MODE_INT:
   0011                     347 	.ds 1
   0012                     348 _mode::
   0012                     349 	.ds 1
   0013                     350 _number::
   0013                     351 	.ds 1
   0014                     352 _state::
   0014                     353 	.ds 1
   0015                     354 _v::
   0015                     355 	.ds 1
                            356 ;--------------------------------------------------------
                            357 ; overlayable items in internal ram 
                            358 ;--------------------------------------------------------
                            359 	.area OSEG    (OVR,DATA)
                            360 ;--------------------------------------------------------
                            361 ; indirectly addressable internal ram data
                            362 ;--------------------------------------------------------
                            363 	.area ISEG    (DATA)
                            364 ;--------------------------------------------------------
                            365 ; absolute internal ram data
                            366 ;--------------------------------------------------------
                            367 	.area IABS    (ABS,DATA)
                            368 	.area IABS    (ABS,DATA)
                            369 ;--------------------------------------------------------
                            370 ; bit data
                            371 ;--------------------------------------------------------
                            372 	.area BSEG    (BIT)
                            373 ;--------------------------------------------------------
                            374 ; paged external ram data
                            375 ;--------------------------------------------------------
                            376 	.area PSEG    (PAG,XDATA)
                            377 ;--------------------------------------------------------
                            378 ; external ram data
                            379 ;--------------------------------------------------------
                            380 	.area XSEG    (XDATA)
                            381 ;--------------------------------------------------------
                            382 ; absolute external ram data
                            383 ;--------------------------------------------------------
                            384 	.area XABS    (ABS,XDATA)
                            385 ;--------------------------------------------------------
                            386 ; external initialized ram data
                            387 ;--------------------------------------------------------
                            388 	.area XISEG   (XDATA)
                            389 	.area HOME    (CODE)
                            390 	.area GSINIT0 (CODE)
                            391 	.area GSINIT1 (CODE)
                            392 	.area GSINIT2 (CODE)
                            393 	.area GSINIT3 (CODE)
                            394 	.area GSINIT4 (CODE)
                            395 	.area GSINIT5 (CODE)
                            396 	.area GSINIT  (CODE)
                            397 	.area GSFINAL (CODE)
                            398 	.area CSEG    (CODE)
                            399 ;--------------------------------------------------------
                            400 ; global & static initialisations
                            401 ;--------------------------------------------------------
                            402 	.area HOME    (CODE)
                            403 	.area GSINIT  (CODE)
                            404 	.area GSFINAL (CODE)
                            405 	.area GSINIT  (CODE)
                            406 ;	./INCLUDE/handler.h:9: static u8 MODE_INT=0xFF;
   216C 75 11 FF            407 	mov	_MODE_INT,#0xFF
                            408 ;--------------------------------------------------------
                            409 ; Home
                            410 ;--------------------------------------------------------
                            411 	.area HOME    (CODE)
                            412 	.area HOME    (CODE)
                            413 ;--------------------------------------------------------
                            414 ; code
                            415 ;--------------------------------------------------------
                            416 	.area CSEG    (CODE)
                            417 ;------------------------------------------------------------
                            418 ;Allocation info for local variables in function 'read_dip'
                            419 ;------------------------------------------------------------
                            420 ;dip                       Allocated to registers 
                            421 ;------------------------------------------------------------
                            422 ;	SRC/handler.c:21: u8 read_dip(){
                            423 ;	-----------------------------------------
                            424 ;	 function read_dip
                            425 ;	-----------------------------------------
   2710                     426 _read_dip:
                    0002    427 	ar2 = 0x02
                    0003    428 	ar3 = 0x03
                    0004    429 	ar4 = 0x04
                    0005    430 	ar5 = 0x05
                    0006    431 	ar6 = 0x06
                    0007    432 	ar7 = 0x07
                    0000    433 	ar0 = 0x00
                    0001    434 	ar1 = 0x01
                            435 ;	SRC/handler.c:24: dip=read_max(EXT_LO);
   2710 90 00 02            436 	mov	dptr,#0x0002
                            437 ;	SRC/handler.c:26: return dip;
   2713 02 22 23            438 	ljmp	_read_max
                            439 ;------------------------------------------------------------
                            440 ;Allocation info for local variables in function 'reset'
                            441 ;------------------------------------------------------------
                            442 ;------------------------------------------------------------
                            443 ;	SRC/handler.c:29: void reset() {
                            444 ;	-----------------------------------------
                            445 ;	 function reset
                            446 ;	-----------------------------------------
   2716                     447 _reset:
                            448 ;	SRC/handler.c:30: number=0;
   2716 75 13 00            449 	mov	_number,#0x00
                            450 ;	SRC/handler.c:31: state=STATE_NUMBER;
   2719 75 14 00            451 	mov	_state,#0x00
   271C 22                  452 	ret
                            453 ;------------------------------------------------------------
                            454 ;Allocation info for local variables in function 'initialize_handler'
                            455 ;------------------------------------------------------------
                            456 ;------------------------------------------------------------
                            457 ;	SRC/handler.c:34: void initialize_handler() {
                            458 ;	-----------------------------------------
                            459 ;	 function initialize_handler
                            460 ;	-----------------------------------------
   271D                     461 _initialize_handler:
                            462 ;	SRC/handler.c:35: mode = MODE_TEST;
   271D 90 2C 56            463 	mov	dptr,#_MODE_TEST
   2720 E4                  464 	clr	a
   2721 93                  465 	movc	a,@a+dptr
   2722 F5 12               466 	mov	_mode,a
                            467 ;	SRC/handler.c:36: reset();
   2724 02 27 16            468 	ljmp	_reset
                            469 ;------------------------------------------------------------
                            470 ;Allocation info for local variables in function 'test_loop'
                            471 ;------------------------------------------------------------
                            472 ;byte_in                   Allocated to stack - offset 1
                            473 ;------------------------------------------------------------
                            474 ;	SRC/handler.c:39: void test_loop() {
                            475 ;	-----------------------------------------
                            476 ;	 function test_loop
                            477 ;	-----------------------------------------
   2727                     478 _test_loop:
   2727 C0 18               479 	push	_bp
   2729 85 81 18            480 	mov	_bp,sp
   272C 05 81               481 	inc	sp
                            482 ;	SRC/handler.c:42: while( read_dip()!=DIP_POLL_MODE ){
   272E                     483 00103$:
   272E 12 27 10            484 	lcall	_read_dip
   2731 AA 82               485 	mov	r2,dpl
   2733 90 2C 57            486 	mov	dptr,#_DIP_POLL_MODE
   2736 E4                  487 	clr	a
   2737 93                  488 	movc	a,@a+dptr
   2738 FB                  489 	mov	r3,a
   2739 EA                  490 	mov	a,r2
   273A B5 03 02            491 	cjne	a,ar3,00111$
   273D 80 30               492 	sjmp	00105$
   273F                     493 00111$:
                            494 ;	SRC/handler.c:43: if( keyboard_read_byte(&byte_in) ){
   273F AA 18               495 	mov	r2,_bp
   2741 0A                  496 	inc	r2
   2742 7B 00               497 	mov	r3,#0x00
   2744 7C 40               498 	mov	r4,#0x40
   2746 8A 82               499 	mov	dpl,r2
   2748 8B 83               500 	mov	dph,r3
   274A 8C F0               501 	mov	b,r4
   274C 12 29 8B            502 	lcall	_keyboard_read_byte
   274F E5 82               503 	mov	a,dpl
   2751 60 11               504 	jz	00102$
                            505 ;	SRC/handler.c:44: send_byte(byte_in);
   2753 A8 18               506 	mov	r0,_bp
   2755 08                  507 	inc	r0
   2756 86 82               508 	mov	dpl,@r0
   2758 12 23 BF            509 	lcall	_send_byte
                            510 ;	SRC/handler.c:45: send_string("\r\n");
   275B 90 2C 59            511 	mov	dptr,#__str_0
   275E 75 F0 80            512 	mov	b,#0x80
   2761 12 23 F3            513 	lcall	_send_string
   2764                     514 00102$:
                            515 ;	SRC/handler.c:47: delay_ms(1);
   2764 90 00 01            516 	mov	dptr,#(0x01&0x00ff)
   2767 E4                  517 	clr	a
   2768 F5 F0               518 	mov	b,a
   276A 12 22 D3            519 	lcall	_delay_ms
   276D 80 BF               520 	sjmp	00103$
   276F                     521 00105$:
                            522 ;	SRC/handler.c:50: mode=MODE_INT;
   276F 85 11 12            523 	mov	_mode,_MODE_INT
   2772 85 18 81            524 	mov	sp,_bp
   2775 D0 18               525 	pop	_bp
   2777 22                  526 	ret
                            527 ;------------------------------------------------------------
                            528 ;Allocation info for local variables in function 'int_loop'
                            529 ;------------------------------------------------------------
                            530 ;byte_in                   Allocated to stack - offset 1
                            531 ;------------------------------------------------------------
                            532 ;	SRC/handler.c:53: void int_loop() {
                            533 ;	-----------------------------------------
                            534 ;	 function int_loop
                            535 ;	-----------------------------------------
   2778                     536 _int_loop:
   2778 C0 18               537 	push	_bp
   277A 85 81 18            538 	mov	_bp,sp
   277D 05 81               539 	inc	sp
                            540 ;	SRC/handler.c:56: while( read_dip()==DIP_POLL_MODE ){
   277F                     541 00103$:
   277F 12 27 10            542 	lcall	_read_dip
   2782 AA 82               543 	mov	r2,dpl
   2784 90 2C 57            544 	mov	dptr,#_DIP_POLL_MODE
   2787 E4                  545 	clr	a
   2788 93                  546 	movc	a,@a+dptr
   2789 FB                  547 	mov	r3,a
   278A EA                  548 	mov	a,r2
   278B B5 03 27            549 	cjne	a,ar3,00105$
                            550 ;	SRC/handler.c:57: if( keyboard_read_byte(&byte_in) ){
   278E AA 18               551 	mov	r2,_bp
   2790 0A                  552 	inc	r2
   2791 7B 00               553 	mov	r3,#0x00
   2793 7C 40               554 	mov	r4,#0x40
   2795 8A 82               555 	mov	dpl,r2
   2797 8B 83               556 	mov	dph,r3
   2799 8C F0               557 	mov	b,r4
   279B 12 29 8B            558 	lcall	_keyboard_read_byte
   279E E5 82               559 	mov	a,dpl
   27A0 60 08               560 	jz	00102$
                            561 ;	SRC/handler.c:58: handler_int(byte_in);
   27A2 A8 18               562 	mov	r0,_bp
   27A4 08                  563 	inc	r0
   27A5 86 82               564 	mov	dpl,@r0
   27A7 12 28 0D            565 	lcall	_handler_int
   27AA                     566 00102$:
                            567 ;	SRC/handler.c:61: delay_ms(1);
   27AA 90 00 01            568 	mov	dptr,#(0x01&0x00ff)
   27AD E4                  569 	clr	a
   27AE F5 F0               570 	mov	b,a
   27B0 12 22 D3            571 	lcall	_delay_ms
   27B3 80 CA               572 	sjmp	00103$
   27B5                     573 00105$:
                            574 ;	SRC/handler.c:64: mode=MODE_TEST;
   27B5 90 2C 56            575 	mov	dptr,#_MODE_TEST
   27B8 E4                  576 	clr	a
   27B9 93                  577 	movc	a,@a+dptr
   27BA F5 12               578 	mov	_mode,a
   27BC 85 18 81            579 	mov	sp,_bp
   27BF D0 18               580 	pop	_bp
   27C1 22                  581 	ret
                            582 ;------------------------------------------------------------
                            583 ;Allocation info for local variables in function 'handler_loop'
                            584 ;------------------------------------------------------------
                            585 ;------------------------------------------------------------
                            586 ;	SRC/handler.c:67: void handler_loop() {
                            587 ;	-----------------------------------------
                            588 ;	 function handler_loop
                            589 ;	-----------------------------------------
   27C2                     590 _handler_loop:
                            591 ;	SRC/handler.c:68: while(1) {
   27C2                     592 00105$:
                            593 ;	SRC/handler.c:69: if( mode==MODE_TEST ) {
   27C2 90 2C 56            594 	mov	dptr,#_MODE_TEST
   27C5 E4                  595 	clr	a
   27C6 93                  596 	movc	a,@a+dptr
   27C7 FA                  597 	mov	r2,a
   27C8 B5 12 0E            598 	cjne	a,_mode,00102$
                            599 ;	SRC/handler.c:70: send_string("\r\ntest mode\r\n");
   27CB 90 2C 5C            600 	mov	dptr,#__str_1
   27CE 75 F0 80            601 	mov	b,#0x80
   27D1 12 23 F3            602 	lcall	_send_string
                            603 ;	SRC/handler.c:71: test_loop();
   27D4 12 27 27            604 	lcall	_test_loop
   27D7 80 E9               605 	sjmp	00105$
   27D9                     606 00102$:
                            607 ;	SRC/handler.c:73: send_string("\r\ninteruption mode\r\n");
   27D9 90 2C 6A            608 	mov	dptr,#__str_2
   27DC 75 F0 80            609 	mov	b,#0x80
   27DF 12 23 F3            610 	lcall	_send_string
                            611 ;	SRC/handler.c:74: int_loop();
   27E2 12 27 78            612 	lcall	_int_loop
   27E5 80 DB               613 	sjmp	00105$
                            614 ;------------------------------------------------------------
                            615 ;Allocation info for local variables in function 'error'
                            616 ;------------------------------------------------------------
                            617 ;------------------------------------------------------------
                            618 ;	SRC/handler.c:79: void error() {
                            619 ;	-----------------------------------------
                            620 ;	 function error
                            621 ;	-----------------------------------------
   27E7                     622 _error:
                            623 ;	SRC/handler.c:80: send_string("\r\nerror\r\n");
   27E7 90 2C 7F            624 	mov	dptr,#__str_3
   27EA 75 F0 80            625 	mov	b,#0x80
   27ED 12 23 F3            626 	lcall	_send_string
                            627 ;	SRC/handler.c:81: leds(0xAA);
   27F0 75 82 AA            628 	mov	dpl,#0xAA
   27F3 12 21 EE            629 	lcall	_leds
                            630 ;	SRC/handler.c:82: state=STATE_ERROR;
   27F6 75 14 01            631 	mov	_state,#0x01
   27F9 22                  632 	ret
                            633 ;------------------------------------------------------------
                            634 ;Allocation info for local variables in function 'to_hex'
                            635 ;------------------------------------------------------------
                            636 ;val                       Allocated to registers r2 
                            637 ;------------------------------------------------------------
                            638 ;	SRC/handler.c:85: u8 to_hex(u8 val) {
                            639 ;	-----------------------------------------
                            640 ;	 function to_hex
                            641 ;	-----------------------------------------
   27FA                     642 _to_hex:
                            643 ;	SRC/handler.c:86: if( val>9 ) {
   27FA E5 82               644 	mov	a,dpl
   27FC FA                  645 	mov	r2,a
   27FD 24 F6               646 	add	a,#0xff - 0x09
   27FF 50 06               647 	jnc	00102$
                            648 ;	SRC/handler.c:87: return 'A'+val-10;
   2801 74 37               649 	mov	a,#0x37
   2803 2A                  650 	add	a,r2
   2804 F5 82               651 	mov	dpl,a
   2806 22                  652 	ret
   2807                     653 00102$:
                            654 ;	SRC/handler.c:90: return '0'+val;
   2807 74 30               655 	mov	a,#0x30
   2809 2A                  656 	add	a,r2
   280A F5 82               657 	mov	dpl,a
   280C 22                  658 	ret
                            659 ;------------------------------------------------------------
                            660 ;Allocation info for local variables in function 'handler_int'
                            661 ;------------------------------------------------------------
                            662 ;sym                       Allocated to registers r2 
                            663 ;num                       Allocated to registers r3 
                            664 ;array                     Allocated to stack - offset 1
                            665 ;i                         Allocated to registers r2 r3 
                            666 ;count                     Allocated to registers r2 r3 
                            667 ;------------------------------------------------------------
                            668 ;	SRC/handler.c:93: void handler_int(u8 sym) {
                            669 ;	-----------------------------------------
                            670 ;	 function handler_int
                            671 ;	-----------------------------------------
   280D                     672 _handler_int:
   280D C0 18               673 	push	_bp
   280F E5 81               674 	mov	a,sp
   2811 F5 18               675 	mov	_bp,a
   2813 24 10               676 	add	a,#0x10
   2815 F5 81               677 	mov	sp,a
   2817 AA 82               678 	mov	r2,dpl
                            679 ;	SRC/handler.c:95: int array[8] = {0, 0, 0, 0, 0, 0, 0, 0};
   2819 A8 18               680 	mov	r0,_bp
   281B 08                  681 	inc	r0
   281C 76 00               682 	mov	@r0,#0x00
   281E 08                  683 	inc	r0
   281F 76 00               684 	mov	@r0,#0x00
   2821 18                  685 	dec	r0
   2822 74 02               686 	mov	a,#0x02
   2824 28                  687 	add	a,r0
   2825 F9                  688 	mov	r1,a
   2826 77 00               689 	mov	@r1,#0x00
   2828 09                  690 	inc	r1
   2829 77 00               691 	mov	@r1,#0x00
   282B 74 04               692 	mov	a,#0x04
   282D 28                  693 	add	a,r0
   282E F9                  694 	mov	r1,a
   282F 77 00               695 	mov	@r1,#0x00
   2831 09                  696 	inc	r1
   2832 77 00               697 	mov	@r1,#0x00
   2834 74 06               698 	mov	a,#0x06
   2836 28                  699 	add	a,r0
   2837 F9                  700 	mov	r1,a
   2838 77 00               701 	mov	@r1,#0x00
   283A 09                  702 	inc	r1
   283B 77 00               703 	mov	@r1,#0x00
   283D 74 08               704 	mov	a,#0x08
   283F 28                  705 	add	a,r0
   2840 F9                  706 	mov	r1,a
   2841 77 00               707 	mov	@r1,#0x00
   2843 09                  708 	inc	r1
   2844 77 00               709 	mov	@r1,#0x00
   2846 74 0A               710 	mov	a,#0x0A
   2848 28                  711 	add	a,r0
   2849 F9                  712 	mov	r1,a
   284A 77 00               713 	mov	@r1,#0x00
   284C 09                  714 	inc	r1
   284D 77 00               715 	mov	@r1,#0x00
   284F 74 0C               716 	mov	a,#0x0C
   2851 28                  717 	add	a,r0
   2852 F9                  718 	mov	r1,a
   2853 77 00               719 	mov	@r1,#0x00
   2855 09                  720 	inc	r1
   2856 77 00               721 	mov	@r1,#0x00
   2858 74 0E               722 	mov	a,#0x0E
   285A 28                  723 	add	a,r0
   285B F9                  724 	mov	r1,a
   285C 77 00               725 	mov	@r1,#0x00
   285E 09                  726 	inc	r1
                            727 ;	SRC/handler.c:99: switch (state) {
   285F E4                  728 	clr	a
   2860 F7                  729 	mov	@r1,a
   2861 B5 14 02            730 	cjne	a,_state,00134$
   2864 80 16               731 	sjmp	00102$
   2866                     732 00134$:
   2866 74 01               733 	mov	a,#0x01
   2868 B5 14 02            734 	cjne	a,_state,00135$
   286B 80 03               735 	sjmp	00136$
   286D                     736 00135$:
   286D 02 29 75            737 	ljmp	00120$
   2870                     738 00136$:
                            739 ;	SRC/handler.c:101: reset();
   2870 12 27 16            740 	lcall	_reset
                            741 ;	SRC/handler.c:102: leds(0x00);
   2873 75 82 00            742 	mov	dpl,#0x00
   2876 12 21 EE            743 	lcall	_leds
                            744 ;	SRC/handler.c:103: break;
   2879 02 29 75            745 	ljmp	00120$
                            746 ;	SRC/handler.c:104: case STATE_NUMBER:
   287C                     747 00102$:
                            748 ;	SRC/handler.c:105: if(sym>='0' && sym<='9'){
   287C BA 30 00            749 	cjne	r2,#0x30,00137$
   287F                     750 00137$:
   287F 40 4E               751 	jc	00112$
   2881 EA                  752 	mov	a,r2
   2882 24 C6               753 	add	a,#0xff - 0x39
   2884 40 49               754 	jc	00112$
                            755 ;	SRC/handler.c:106: send_byte(sym);
   2886 8A 82               756 	mov	dpl,r2
   2888 C0 02               757 	push	ar2
   288A 12 23 BF            758 	lcall	_send_byte
   288D D0 02               759 	pop	ar2
                            760 ;	SRC/handler.c:107: num=sym-'0';
   288F EA                  761 	mov	a,r2
   2890 24 D0               762 	add	a,#0xd0
   2892 FB                  763 	mov	r3,a
                            764 ;	SRC/handler.c:109: if( num > NUMBER_LIMIT-number*10 ) {//станет больше, чем NUMBER_LIMIT
   2893 90 2C 58            765 	mov	dptr,#_NUMBER_LIMIT
   2896 E4                  766 	clr	a
   2897 93                  767 	movc	a,@a+dptr
   2898 FC                  768 	mov	r4,a
   2899 7D 00               769 	mov	r5,#0x00
   289B E5 13               770 	mov	a,_number
   289D 75 F0 0A            771 	mov	b,#0x0A
   28A0 A4                  772 	mul	ab
   28A1 D3                  773 	setb	c
   28A2 9C                  774 	subb	a,r4
   28A3 F4                  775 	cpl	a
   28A4 B3                  776 	cpl	c
   28A5 FC                  777 	mov	r4,a
   28A6 ED                  778 	mov	a,r5
   28A7 95 F0               779 	subb	a,b
   28A9 FD                  780 	mov	r5,a
   28AA 8B 06               781 	mov	ar6,r3
   28AC 7F 00               782 	mov	r7,#0x00
   28AE C3                  783 	clr	c
   28AF EC                  784 	mov	a,r4
   28B0 9E                  785 	subb	a,r6
   28B1 ED                  786 	mov	a,r5
   28B2 64 80               787 	xrl	a,#0x80
   28B4 8F F0               788 	mov	b,r7
   28B6 63 F0 80            789 	xrl	b,#0x80
   28B9 95 F0               790 	subb	a,b
   28BB 50 06               791 	jnc	00104$
                            792 ;	SRC/handler.c:110: error();
   28BD 12 27 E7            793 	lcall	_error
                            794 ;	SRC/handler.c:111: return;
   28C0 02 29 75            795 	ljmp	00120$
   28C3                     796 00104$:
                            797 ;	SRC/handler.c:114: number*=10;
   28C3 E5 13               798 	mov	a,_number
   28C5 75 F0 0A            799 	mov	b,#0x0A
   28C8 A4                  800 	mul	ab
                            801 ;	SRC/handler.c:115: number+=num;
   28C9 2B                  802 	add	a,r3
   28CA F5 13               803 	mov	_number,a
   28CC 02 29 75            804 	ljmp	00120$
   28CF                     805 00112$:
                            806 ;	SRC/handler.c:116: }else if( sym=='*' ) {
   28CF BA 2A 02            807 	cjne	r2,#0x2A,00141$
   28D2 80 03               808 	sjmp	00142$
   28D4                     809 00141$:
   28D4 02 29 72            810 	ljmp	00109$
   28D7                     811 00142$:
                            812 ;	SRC/handler.c:117: send_string("\r\nBin:");
   28D7 90 2C 89            813 	mov	dptr,#__str_4
   28DA 75 F0 80            814 	mov	b,#0x80
   28DD C0 00               815 	push	ar0
   28DF 12 23 F3            816 	lcall	_send_string
   28E2 D0 00               817 	pop	ar0
                            818 ;	SRC/handler.c:118: while (number > 0) {
   28E4 7A 00               819 	mov	r2,#0x00
   28E6 7B 00               820 	mov	r3,#0x00
   28E8                     821 00105$:
   28E8 E5 13               822 	mov	a,_number
   28EA 60 25               823 	jz	00107$
                            824 ;	SRC/handler.c:119: array[count] = number % 2;
   28EC 8A 04               825 	mov	ar4,r2
   28EE EB                  826 	mov	a,r3
   28EF CC                  827 	xch	a,r4
   28F0 25 E0               828 	add	a,acc
   28F2 CC                  829 	xch	a,r4
   28F3 33                  830 	rlc	a
   28F4 EC                  831 	mov	a,r4
   28F5 28                  832 	add	a,r0
   28F6 F9                  833 	mov	r1,a
   28F7 74 01               834 	mov	a,#0x01
   28F9 55 13               835 	anl	a,_number
   28FB FC                  836 	mov	r4,a
   28FC 7D 00               837 	mov	r5,#0x00
   28FE A7 04               838 	mov	@r1,ar4
   2900 09                  839 	inc	r1
   2901 A7 05               840 	mov	@r1,ar5
   2903 19                  841 	dec	r1
                            842 ;	SRC/handler.c:120: number = number / 2;
   2904 E5 13               843 	mov	a,_number
   2906 C3                  844 	clr	c
   2907 13                  845 	rrc	a
   2908 F5 13               846 	mov	_number,a
                            847 ;	SRC/handler.c:121: count++;
   290A 0A                  848 	inc	r2
   290B BA 00 DA            849 	cjne	r2,#0x00,00105$
   290E 0B                  850 	inc	r3
   290F 80 D7               851 	sjmp	00105$
   2911                     852 00107$:
                            853 ;	SRC/handler.c:123: for (i = 7; i >= 0; i--) {
   2911 7A 07               854 	mov	r2,#0x07
   2913 7B 00               855 	mov	r3,#0x00
   2915                     856 00116$:
   2915 EB                  857 	mov	a,r3
   2916 20 E7 4B            858 	jb	acc.7,00119$
                            859 ;	SRC/handler.c:124: send_byte(array[i] + '0');
   2919 8A 04               860 	mov	ar4,r2
   291B EB                  861 	mov	a,r3
   291C CC                  862 	xch	a,r4
   291D 25 E0               863 	add	a,acc
   291F CC                  864 	xch	a,r4
   2920 33                  865 	rlc	a
   2921 EC                  866 	mov	a,r4
   2922 28                  867 	add	a,r0
   2923 F9                  868 	mov	r1,a
   2924 87 04               869 	mov	ar4,@r1
   2926 09                  870 	inc	r1
   2927 87 05               871 	mov	ar5,@r1
   2929 19                  872 	dec	r1
   292A 74 30               873 	mov	a,#0x30
   292C 2C                  874 	add	a,r4
   292D F5 82               875 	mov	dpl,a
   292F C0 02               876 	push	ar2
   2931 C0 03               877 	push	ar3
   2933 C0 00               878 	push	ar0
   2935 C0 01               879 	push	ar1
   2937 12 23 BF            880 	lcall	_send_byte
   293A D0 01               881 	pop	ar1
   293C D0 00               882 	pop	ar0
   293E D0 03               883 	pop	ar3
   2940 D0 02               884 	pop	ar2
                            885 ;	SRC/handler.c:125: led(i, array[i]);
   2942 87 04               886 	mov	ar4,@r1
   2944 09                  887 	inc	r1
   2945 87 05               888 	mov	ar5,@r1
   2947 19                  889 	dec	r1
   2948 8A 82               890 	mov	dpl,r2
   294A C0 02               891 	push	ar2
   294C C0 03               892 	push	ar3
   294E C0 00               893 	push	ar0
   2950 C0 04               894 	push	ar4
   2952 12 21 AB            895 	lcall	_led
   2955 15 81               896 	dec	sp
   2957 D0 00               897 	pop	ar0
   2959 D0 03               898 	pop	ar3
   295B D0 02               899 	pop	ar2
                            900 ;	SRC/handler.c:123: for (i = 7; i >= 0; i--) {
   295D 1A                  901 	dec	r2
   295E BA FF 01            902 	cjne	r2,#0xff,00145$
   2961 1B                  903 	dec	r3
   2962                     904 00145$:
   2962 80 B1               905 	sjmp	00116$
   2964                     906 00119$:
                            907 ;	SRC/handler.c:127: send_string("\r\n");
   2964 90 2C 59            908 	mov	dptr,#__str_0
   2967 75 F0 80            909 	mov	b,#0x80
   296A 12 23 F3            910 	lcall	_send_string
                            911 ;	SRC/handler.c:128: reset();
   296D 12 27 16            912 	lcall	_reset
   2970 80 03               913 	sjmp	00120$
   2972                     914 00109$:
                            915 ;	SRC/handler.c:131: error();
   2972 12 27 E7            916 	lcall	_error
                            917 ;	SRC/handler.c:134: }
   2975                     918 00120$:
   2975 85 18 81            919 	mov	sp,_bp
   2978 D0 18               920 	pop	_bp
   297A 22                  921 	ret
                            922 	.area CSEG    (CODE)
                            923 	.area CONST   (CODE)
   2C54                     924 _true:
   2C54 FF                  925 	.db #0xFF
   2C55                     926 _false:
   2C55 00                  927 	.db #0x00
   2C56                     928 _MODE_TEST:
   2C56 00                  929 	.db #0x00
   2C57                     930 _DIP_POLL_MODE:
   2C57 01                  931 	.db #0x01
   2C58                     932 _NUMBER_LIMIT:
   2C58 FF                  933 	.db #0xFF
   2C59                     934 __str_0:
   2C59 0D                  935 	.db 0x0D
   2C5A 0A                  936 	.db 0x0A
   2C5B 00                  937 	.db 0x00
   2C5C                     938 __str_1:
   2C5C 0D                  939 	.db 0x0D
   2C5D 0A                  940 	.db 0x0A
   2C5E 74 65 73 74 20 6D   941 	.ascii "test mode"
        6F 64 65
   2C67 0D                  942 	.db 0x0D
   2C68 0A                  943 	.db 0x0A
   2C69 00                  944 	.db 0x00
   2C6A                     945 __str_2:
   2C6A 0D                  946 	.db 0x0D
   2C6B 0A                  947 	.db 0x0A
   2C6C 69 6E 74 65 72 75   948 	.ascii "interuption mode"
        70 74 69 6F 6E 20
        6D 6F 64 65
   2C7C 0D                  949 	.db 0x0D
   2C7D 0A                  950 	.db 0x0A
   2C7E 00                  951 	.db 0x00
   2C7F                     952 __str_3:
   2C7F 0D                  953 	.db 0x0D
   2C80 0A                  954 	.db 0x0A
   2C81 65 72 72 6F 72      955 	.ascii "error"
   2C86 0D                  956 	.db 0x0D
   2C87 0A                  957 	.db 0x0A
   2C88 00                  958 	.db 0x00
   2C89                     959 __str_4:
   2C89 0D                  960 	.db 0x0D
   2C8A 0A                  961 	.db 0x0A
   2C8B 42 69 6E 3A         962 	.ascii "Bin:"
   2C8F 00                  963 	.db 0x00
                            964 	.area XINIT   (CODE)
                            965 	.area CABS    (ABS,CODE)
