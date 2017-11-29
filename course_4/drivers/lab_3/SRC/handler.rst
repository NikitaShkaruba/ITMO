                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 2.9.0 #5416 (Mar 22 2009) (MINGW32)
                              4 ; This file was generated Wed Nov 08 14:01:43 2017
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
                             16 	.globl _error
                             17 	.globl _reset
                             18 	.globl _read_dip
                             19 	.globl _SPR0
                             20 	.globl _SPR1
                             21 	.globl _CPHA
                             22 	.globl _CPOL
                             23 	.globl _SPIM
                             24 	.globl _SPE
                             25 	.globl _WCOL
                             26 	.globl _ISPI
                             27 	.globl _I2CI
                             28 	.globl _I2CTX
                             29 	.globl _I2CRS
                             30 	.globl _I2CM
                             31 	.globl _MDI
                             32 	.globl _MCO
                             33 	.globl _MDE
                             34 	.globl _MDO
                             35 	.globl _CS0
                             36 	.globl _CS1
                             37 	.globl _CS2
                             38 	.globl _CS3
                             39 	.globl _SCONV
                             40 	.globl _CCONV
                             41 	.globl _DMA
                             42 	.globl _ADCI
                             43 	.globl _P
                             44 	.globl _F1
                             45 	.globl _OV
                             46 	.globl _RS0
                             47 	.globl _RS1
                             48 	.globl _F0
                             49 	.globl _AC
                             50 	.globl _CY
                             51 	.globl _CAP2
                             52 	.globl _CNT2
                             53 	.globl _TR2
                             54 	.globl _XEN
                             55 	.globl _TCLK
                             56 	.globl _RCLK
                             57 	.globl _EXF2
                             58 	.globl _TF2
                             59 	.globl _WDE
                             60 	.globl _WDS
                             61 	.globl _WDR2
                             62 	.globl _WDR1
                             63 	.globl _PRE0
                             64 	.globl _PRE1
                             65 	.globl _PRE2
                             66 	.globl _PX0
                             67 	.globl _PT0
                             68 	.globl _PX1
                             69 	.globl _PT1
                             70 	.globl _PS
                             71 	.globl _PT2
                             72 	.globl _PADC
                             73 	.globl _PSI
                             74 	.globl _RXD
                             75 	.globl _TXD
                             76 	.globl _INT0
                             77 	.globl _INT1
                             78 	.globl _T0
                             79 	.globl _T1
                             80 	.globl _WR
                             81 	.globl _RD
                             82 	.globl _EX0
                             83 	.globl _ET0
                             84 	.globl _EX1
                             85 	.globl _ET1
                             86 	.globl _ES
                             87 	.globl _ET2
                             88 	.globl _EADC
                             89 	.globl _EA
                             90 	.globl _RI
                             91 	.globl _TI
                             92 	.globl _RB8
                             93 	.globl _TB8
                             94 	.globl _REN
                             95 	.globl _SM2
                             96 	.globl _SM1
                             97 	.globl _SM0
                             98 	.globl _T2
                             99 	.globl _T2EX
                            100 	.globl _IT0
                            101 	.globl _IE0
                            102 	.globl _IT1
                            103 	.globl _IE1
                            104 	.globl _TR0
                            105 	.globl _TF0
                            106 	.globl _TR1
                            107 	.globl _TF1
                            108 	.globl _DACCON
                            109 	.globl _DAC1H
                            110 	.globl _DAC1L
                            111 	.globl _DAC0H
                            112 	.globl _DAC0L
                            113 	.globl _SPICON
                            114 	.globl _SPIDAT
                            115 	.globl _ADCCON3
                            116 	.globl _ADCGAINH
                            117 	.globl _ADCGAINL
                            118 	.globl _ADCOFSH
                            119 	.globl _ADCOFSL
                            120 	.globl _B
                            121 	.globl _ADCCON1
                            122 	.globl _I2CCON
                            123 	.globl _ACC
                            124 	.globl _PSMCON
                            125 	.globl _ADCDATAH
                            126 	.globl _ADCDATAL
                            127 	.globl _ADCCON2
                            128 	.globl _DMAP
                            129 	.globl _DMAH
                            130 	.globl _DMAL
                            131 	.globl _PSW
                            132 	.globl _TH2
                            133 	.globl _TL2
                            134 	.globl _RCAP2H
                            135 	.globl _RCAP2L
                            136 	.globl _T2CON
                            137 	.globl _EADRL
                            138 	.globl _WDCON
                            139 	.globl _EDATA4
                            140 	.globl _EDATA3
                            141 	.globl _EDATA2
                            142 	.globl _EDATA1
                            143 	.globl _ETIM3
                            144 	.globl _ETIM2
                            145 	.globl _ETIM1
                            146 	.globl _ECON
                            147 	.globl _IP
                            148 	.globl _P3
                            149 	.globl _IE2
                            150 	.globl _IE
                            151 	.globl _P2
                            152 	.globl _I2CADD
                            153 	.globl _I2CDAT
                            154 	.globl _SBUF
                            155 	.globl _SCON
                            156 	.globl _P1
                            157 	.globl _TH1
                            158 	.globl _TH0
                            159 	.globl _TL1
                            160 	.globl _TL0
                            161 	.globl _TMOD
                            162 	.globl _TCON
                            163 	.globl _PCON
                            164 	.globl _DPP
                            165 	.globl _DPH
                            166 	.globl _DPL
                            167 	.globl _SP
                            168 	.globl _P0
                            169 	.globl _state
                            170 	.globl _number
                            171 	.globl _mode
                            172 	.globl _initialize_handler
                            173 	.globl _poll_loop
                            174 	.globl _int_loop
                            175 	.globl _handler_loop
                            176 	.globl _handler_int
                            177 ;--------------------------------------------------------
                            178 ; special function registers
                            179 ;--------------------------------------------------------
                            180 	.area RSEG    (DATA)
                    0080    181 _P0	=	0x0080
                    0081    182 _SP	=	0x0081
                    0082    183 _DPL	=	0x0082
                    0083    184 _DPH	=	0x0083
                    0084    185 _DPP	=	0x0084
                    0087    186 _PCON	=	0x0087
                    0088    187 _TCON	=	0x0088
                    0089    188 _TMOD	=	0x0089
                    008A    189 _TL0	=	0x008a
                    008B    190 _TL1	=	0x008b
                    008C    191 _TH0	=	0x008c
                    008D    192 _TH1	=	0x008d
                    0090    193 _P1	=	0x0090
                    0098    194 _SCON	=	0x0098
                    0099    195 _SBUF	=	0x0099
                    009A    196 _I2CDAT	=	0x009a
                    009B    197 _I2CADD	=	0x009b
                    00A0    198 _P2	=	0x00a0
                    00A8    199 _IE	=	0x00a8
                    00A9    200 _IE2	=	0x00a9
                    00B0    201 _P3	=	0x00b0
                    00B8    202 _IP	=	0x00b8
                    00B9    203 _ECON	=	0x00b9
                    00BA    204 _ETIM1	=	0x00ba
                    00BB    205 _ETIM2	=	0x00bb
                    00C4    206 _ETIM3	=	0x00c4
                    00BC    207 _EDATA1	=	0x00bc
                    00BD    208 _EDATA2	=	0x00bd
                    00BE    209 _EDATA3	=	0x00be
                    00BF    210 _EDATA4	=	0x00bf
                    00C0    211 _WDCON	=	0x00c0
                    00C6    212 _EADRL	=	0x00c6
                    00C8    213 _T2CON	=	0x00c8
                    00CA    214 _RCAP2L	=	0x00ca
                    00CB    215 _RCAP2H	=	0x00cb
                    00CC    216 _TL2	=	0x00cc
                    00CD    217 _TH2	=	0x00cd
                    00D0    218 _PSW	=	0x00d0
                    00D2    219 _DMAL	=	0x00d2
                    00D3    220 _DMAH	=	0x00d3
                    00D4    221 _DMAP	=	0x00d4
                    00D8    222 _ADCCON2	=	0x00d8
                    00D9    223 _ADCDATAL	=	0x00d9
                    00DA    224 _ADCDATAH	=	0x00da
                    00DF    225 _PSMCON	=	0x00df
                    00E0    226 _ACC	=	0x00e0
                    00E8    227 _I2CCON	=	0x00e8
                    00EF    228 _ADCCON1	=	0x00ef
                    00F0    229 _B	=	0x00f0
                    00F1    230 _ADCOFSL	=	0x00f1
                    00F2    231 _ADCOFSH	=	0x00f2
                    00F3    232 _ADCGAINL	=	0x00f3
                    00F4    233 _ADCGAINH	=	0x00f4
                    00F5    234 _ADCCON3	=	0x00f5
                    00F7    235 _SPIDAT	=	0x00f7
                    00F8    236 _SPICON	=	0x00f8
                    00F9    237 _DAC0L	=	0x00f9
                    00FA    238 _DAC0H	=	0x00fa
                    00FB    239 _DAC1L	=	0x00fb
                    00FC    240 _DAC1H	=	0x00fc
                    00FD    241 _DACCON	=	0x00fd
                            242 ;--------------------------------------------------------
                            243 ; special function bits
                            244 ;--------------------------------------------------------
                            245 	.area RSEG    (DATA)
                    008F    246 _TF1	=	0x008f
                    008E    247 _TR1	=	0x008e
                    008D    248 _TF0	=	0x008d
                    008C    249 _TR0	=	0x008c
                    008B    250 _IE1	=	0x008b
                    008A    251 _IT1	=	0x008a
                    0089    252 _IE0	=	0x0089
                    0088    253 _IT0	=	0x0088
                    0091    254 _T2EX	=	0x0091
                    0090    255 _T2	=	0x0090
                    009F    256 _SM0	=	0x009f
                    009E    257 _SM1	=	0x009e
                    009D    258 _SM2	=	0x009d
                    009C    259 _REN	=	0x009c
                    009B    260 _TB8	=	0x009b
                    009A    261 _RB8	=	0x009a
                    0099    262 _TI	=	0x0099
                    0098    263 _RI	=	0x0098
                    00AF    264 _EA	=	0x00af
                    00AE    265 _EADC	=	0x00ae
                    00AD    266 _ET2	=	0x00ad
                    00AC    267 _ES	=	0x00ac
                    00AB    268 _ET1	=	0x00ab
                    00AA    269 _EX1	=	0x00aa
                    00A9    270 _ET0	=	0x00a9
                    00A8    271 _EX0	=	0x00a8
                    00B7    272 _RD	=	0x00b7
                    00B6    273 _WR	=	0x00b6
                    00B5    274 _T1	=	0x00b5
                    00B4    275 _T0	=	0x00b4
                    00B3    276 _INT1	=	0x00b3
                    00B2    277 _INT0	=	0x00b2
                    00B1    278 _TXD	=	0x00b1
                    00B0    279 _RXD	=	0x00b0
                    00BF    280 _PSI	=	0x00bf
                    00BE    281 _PADC	=	0x00be
                    00BD    282 _PT2	=	0x00bd
                    00BC    283 _PS	=	0x00bc
                    00BB    284 _PT1	=	0x00bb
                    00BA    285 _PX1	=	0x00ba
                    00B9    286 _PT0	=	0x00b9
                    00B8    287 _PX0	=	0x00b8
                    00C7    288 _PRE2	=	0x00c7
                    00C6    289 _PRE1	=	0x00c6
                    00C5    290 _PRE0	=	0x00c5
                    00C3    291 _WDR1	=	0x00c3
                    00C2    292 _WDR2	=	0x00c2
                    00C1    293 _WDS	=	0x00c1
                    00C0    294 _WDE	=	0x00c0
                    00CF    295 _TF2	=	0x00cf
                    00CE    296 _EXF2	=	0x00ce
                    00CD    297 _RCLK	=	0x00cd
                    00CC    298 _TCLK	=	0x00cc
                    00CB    299 _XEN	=	0x00cb
                    00CA    300 _TR2	=	0x00ca
                    00C9    301 _CNT2	=	0x00c9
                    00C8    302 _CAP2	=	0x00c8
                    00D7    303 _CY	=	0x00d7
                    00D6    304 _AC	=	0x00d6
                    00D5    305 _F0	=	0x00d5
                    00D4    306 _RS1	=	0x00d4
                    00D3    307 _RS0	=	0x00d3
                    00D2    308 _OV	=	0x00d2
                    00D1    309 _F1	=	0x00d1
                    00D0    310 _P	=	0x00d0
                    00DF    311 _ADCI	=	0x00df
                    00DE    312 _DMA	=	0x00de
                    00DD    313 _CCONV	=	0x00dd
                    00DC    314 _SCONV	=	0x00dc
                    00DB    315 _CS3	=	0x00db
                    00DA    316 _CS2	=	0x00da
                    00D9    317 _CS1	=	0x00d9
                    00D8    318 _CS0	=	0x00d8
                    00EF    319 _MDO	=	0x00ef
                    00EE    320 _MDE	=	0x00ee
                    00ED    321 _MCO	=	0x00ed
                    00EC    322 _MDI	=	0x00ec
                    00EB    323 _I2CM	=	0x00eb
                    00EA    324 _I2CRS	=	0x00ea
                    00E9    325 _I2CTX	=	0x00e9
                    00E8    326 _I2CI	=	0x00e8
                    00FF    327 _ISPI	=	0x00ff
                    00FE    328 _WCOL	=	0x00fe
                    00FD    329 _SPE	=	0x00fd
                    00FC    330 _SPIM	=	0x00fc
                    00FB    331 _CPOL	=	0x00fb
                    00FA    332 _CPHA	=	0x00fa
                    00F9    333 _SPR1	=	0x00f9
                    00F8    334 _SPR0	=	0x00f8
                            335 ;--------------------------------------------------------
                            336 ; overlayable register banks
                            337 ;--------------------------------------------------------
                            338 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     339 	.ds 8
                            340 ;--------------------------------------------------------
                            341 ; internal ram data
                            342 ;--------------------------------------------------------
                            343 	.area DSEG    (DATA)
   0009                     344 _MODE_INT:
   0009                     345 	.ds 1
   000A                     346 _mode::
   000A                     347 	.ds 1
   000B                     348 _number::
   000B                     349 	.ds 1
   000C                     350 _state::
   000C                     351 	.ds 1
                            352 ;--------------------------------------------------------
                            353 ; overlayable items in internal ram 
                            354 ;--------------------------------------------------------
                            355 	.area OSEG    (OVR,DATA)
                            356 ;--------------------------------------------------------
                            357 ; indirectly addressable internal ram data
                            358 ;--------------------------------------------------------
                            359 	.area ISEG    (DATA)
                            360 ;--------------------------------------------------------
                            361 ; absolute internal ram data
                            362 ;--------------------------------------------------------
                            363 	.area IABS    (ABS,DATA)
                            364 	.area IABS    (ABS,DATA)
                            365 ;--------------------------------------------------------
                            366 ; bit data
                            367 ;--------------------------------------------------------
                            368 	.area BSEG    (BIT)
                            369 ;--------------------------------------------------------
                            370 ; paged external ram data
                            371 ;--------------------------------------------------------
                            372 	.area PSEG    (PAG,XDATA)
                            373 ;--------------------------------------------------------
                            374 ; external ram data
                            375 ;--------------------------------------------------------
                            376 	.area XSEG    (XDATA)
                            377 ;--------------------------------------------------------
                            378 ; absolute external ram data
                            379 ;--------------------------------------------------------
                            380 	.area XABS    (ABS,XDATA)
                            381 ;--------------------------------------------------------
                            382 ; external initialized ram data
                            383 ;--------------------------------------------------------
                            384 	.area XISEG   (XDATA)
                            385 	.area HOME    (CODE)
                            386 	.area GSINIT0 (CODE)
                            387 	.area GSINIT1 (CODE)
                            388 	.area GSINIT2 (CODE)
                            389 	.area GSINIT3 (CODE)
                            390 	.area GSINIT4 (CODE)
                            391 	.area GSINIT5 (CODE)
                            392 	.area GSINIT  (CODE)
                            393 	.area GSFINAL (CODE)
                            394 	.area CSEG    (CODE)
                            395 ;--------------------------------------------------------
                            396 ; global & static initialisations
                            397 ;--------------------------------------------------------
                            398 	.area HOME    (CODE)
                            399 	.area GSINIT  (CODE)
                            400 	.area GSFINAL (CODE)
                            401 	.area GSINIT  (CODE)
                            402 ;	./INCLUDE/handler.h:9: static u8 MODE_INT=0xFF;
   2167 75 09 FF            403 	mov	_MODE_INT,#0xFF
                            404 ;--------------------------------------------------------
                            405 ; Home
                            406 ;--------------------------------------------------------
                            407 	.area HOME    (CODE)
                            408 	.area HOME    (CODE)
                            409 ;--------------------------------------------------------
                            410 ; code
                            411 ;--------------------------------------------------------
                            412 	.area CSEG    (CODE)
                            413 ;------------------------------------------------------------
                            414 ;Allocation info for local variables in function 'read_dip'
                            415 ;------------------------------------------------------------
                            416 ;------------------------------------------------------------
                            417 ;	SRC/handler.c:19: u8 read_dip(){
                            418 ;	-----------------------------------------
                            419 ;	 function read_dip
                            420 ;	-----------------------------------------
   263A                     421 _read_dip:
                    0002    422 	ar2 = 0x02
                    0003    423 	ar3 = 0x03
                    0004    424 	ar4 = 0x04
                    0005    425 	ar5 = 0x05
                    0006    426 	ar6 = 0x06
                    0007    427 	ar7 = 0x07
                    0000    428 	ar0 = 0x00
                    0001    429 	ar1 = 0x01
                            430 ;	SRC/handler.c:20: return read_max(EXT_LO);
   263A 90 00 02            431 	mov	dptr,#0x0002
   263D 02 21 83            432 	ljmp	_read_max
                            433 ;------------------------------------------------------------
                            434 ;Allocation info for local variables in function 'reset'
                            435 ;------------------------------------------------------------
                            436 ;------------------------------------------------------------
                            437 ;	SRC/handler.c:23: void reset() {
                            438 ;	-----------------------------------------
                            439 ;	 function reset
                            440 ;	-----------------------------------------
   2640                     441 _reset:
                            442 ;	SRC/handler.c:24: number=0;
   2640 75 0B 00            443 	mov	_number,#0x00
                            444 ;	SRC/handler.c:25: state=STATE_NUMBER;
   2643 75 0C 00            445 	mov	_state,#0x00
   2646 22                  446 	ret
                            447 ;------------------------------------------------------------
                            448 ;Allocation info for local variables in function 'initialize_handler'
                            449 ;------------------------------------------------------------
                            450 ;------------------------------------------------------------
                            451 ;	SRC/handler.c:28: void initialize_handler() {
                            452 ;	-----------------------------------------
                            453 ;	 function initialize_handler
                            454 ;	-----------------------------------------
   2647                     455 _initialize_handler:
                            456 ;	SRC/handler.c:29: mode = MODE_POLL;
   2647 90 29 05            457 	mov	dptr,#_MODE_POLL
   264A E4                  458 	clr	a
   264B 93                  459 	movc	a,@a+dptr
   264C F5 0A               460 	mov	_mode,a
                            461 ;	SRC/handler.c:30: reset();
   264E 02 26 40            462 	ljmp	_reset
                            463 ;------------------------------------------------------------
                            464 ;Allocation info for local variables in function 'poll_loop'
                            465 ;------------------------------------------------------------
                            466 ;i                         Allocated to registers r3 
                            467 ;byte_in                   Allocated to stack - offset 1
                            468 ;------------------------------------------------------------
                            469 ;	SRC/handler.c:33: void poll_loop() {
                            470 ;	-----------------------------------------
                            471 ;	 function poll_loop
                            472 ;	-----------------------------------------
   2651                     473 _poll_loop:
   2651 C0 0D               474 	push	_bp
   2653 85 81 0D            475 	mov	_bp,sp
   2656 05 81               476 	inc	sp
                            477 ;	SRC/handler.c:36: leds(0);
   2658 75 82 00            478 	mov	dpl,#0x00
   265B 12 24 59            479 	lcall	_leds
                            480 ;	SRC/handler.c:38: while( read_dip()==DIP_POLL_MODE ){
   265E                     481 00106$:
   265E 12 26 3A            482 	lcall	_read_dip
   2661 AA 82               483 	mov	r2,dpl
   2663 90 29 06            484 	mov	dptr,#_DIP_POLL_MODE
   2666 E4                  485 	clr	a
   2667 93                  486 	movc	a,@a+dptr
   2668 FB                  487 	mov	r3,a
   2669 EA                  488 	mov	a,r2
   266A B5 03 56            489 	cjne	a,ar3,00108$
                            490 ;	SRC/handler.c:39: if( read_byte(&byte_in) ){
   266D AA 0D               491 	mov	r2,_bp
   266F 0A                  492 	inc	r2
   2670 7B 00               493 	mov	r3,#0x00
   2672 7C 40               494 	mov	r4,#0x40
   2674 8A 82               495 	mov	dpl,r2
   2676 8B 83               496 	mov	dph,r3
   2678 8C F0               497 	mov	b,r4
   267A 12 23 31            498 	lcall	_read_byte
   267D E5 82               499 	mov	a,dpl
   267F 60 37               500 	jz	00105$
                            501 ;	SRC/handler.c:40: for( i=1;i<=3;i++ ){
   2681 A8 0D               502 	mov	r0,_bp
   2683 08                  503 	inc	r0
   2684 86 02               504 	mov	ar2,@r0
   2686 7B 03               505 	mov	r3,#0x03
   2688                     506 00111$:
                            507 ;	SRC/handler.c:41: if (byte_in > 96 && byte_in < 123) {
   2688 EA                  508 	mov	a,r2
   2689 24 9F               509 	add	a,#0xff - 0x60
   268B 50 0E               510 	jnc	00102$
   268D BA 7B 00            511 	cjne	r2,#0x7B,00126$
   2690                     512 00126$:
   2690 50 09               513 	jnc	00102$
                            514 ;	SRC/handler.c:42: byte_in = byte_in - 32;
   2692 EA                  515 	mov	a,r2
   2693 24 E0               516 	add	a,#0xe0
   2695 FA                  517 	mov	r2,a
   2696 A8 0D               518 	mov	r0,_bp
   2698 08                  519 	inc	r0
   2699 A6 02               520 	mov	@r0,ar2
   269B                     521 00102$:
                            522 ;	SRC/handler.c:47: send_byte(byte_in);
   269B 8A 82               523 	mov	dpl,r2
   269D C0 02               524 	push	ar2
   269F C0 03               525 	push	ar3
   26A1 12 22 89            526 	lcall	_send_byte
   26A4 D0 03               527 	pop	ar3
   26A6 D0 02               528 	pop	ar2
   26A8 DB DE               529 	djnz	r3,00111$
                            530 ;	SRC/handler.c:40: for( i=1;i<=3;i++ ){
                            531 ;	SRC/handler.c:49: send_string("\r\n");
   26AA A8 0D               532 	mov	r0,_bp
   26AC 08                  533 	inc	r0
   26AD A6 02               534 	mov	@r0,ar2
   26AF 90 29 08            535 	mov	dptr,#__str_0
   26B2 75 F0 80            536 	mov	b,#0x80
   26B5 12 22 BD            537 	lcall	_send_string
   26B8                     538 00105$:
                            539 ;	SRC/handler.c:52: delay_ms(1);
   26B8 90 00 01            540 	mov	dptr,#(0x01&0x00ff)
   26BB E4                  541 	clr	a
   26BC F5 F0               542 	mov	b,a
   26BE 12 21 C7            543 	lcall	_delay_ms
   26C1 80 9B               544 	sjmp	00106$
   26C3                     545 00108$:
                            546 ;	SRC/handler.c:55: mode=MODE_INT;
   26C3 85 09 0A            547 	mov	_mode,_MODE_INT
   26C6 85 0D 81            548 	mov	sp,_bp
   26C9 D0 0D               549 	pop	_bp
   26CB 22                  550 	ret
                            551 ;------------------------------------------------------------
                            552 ;Allocation info for local variables in function 'int_loop'
                            553 ;------------------------------------------------------------
                            554 ;------------------------------------------------------------
                            555 ;	SRC/handler.c:58: void int_loop() {
                            556 ;	-----------------------------------------
                            557 ;	 function int_loop
                            558 ;	-----------------------------------------
   26CC                     559 _int_loop:
                            560 ;	SRC/handler.c:59: while( read_dip()!=DIP_POLL_MODE ){
   26CC                     561 00101$:
   26CC 12 26 3A            562 	lcall	_read_dip
   26CF AA 82               563 	mov	r2,dpl
   26D1 90 29 06            564 	mov	dptr,#_DIP_POLL_MODE
   26D4 E4                  565 	clr	a
   26D5 93                  566 	movc	a,@a+dptr
   26D6 FB                  567 	mov	r3,a
   26D7 EA                  568 	mov	a,r2
   26D8 B5 03 02            569 	cjne	a,ar3,00108$
   26DB 80 0B               570 	sjmp	00103$
   26DD                     571 00108$:
                            572 ;	SRC/handler.c:60: delay_ms(1);
   26DD 90 00 01            573 	mov	dptr,#(0x01&0x00ff)
   26E0 E4                  574 	clr	a
   26E1 F5 F0               575 	mov	b,a
   26E3 12 21 C7            576 	lcall	_delay_ms
   26E6 80 E4               577 	sjmp	00101$
   26E8                     578 00103$:
                            579 ;	SRC/handler.c:63: mode=MODE_POLL;
   26E8 90 29 05            580 	mov	dptr,#_MODE_POLL
   26EB E4                  581 	clr	a
   26EC 93                  582 	movc	a,@a+dptr
   26ED F5 0A               583 	mov	_mode,a
   26EF 22                  584 	ret
                            585 ;------------------------------------------------------------
                            586 ;Allocation info for local variables in function 'handler_loop'
                            587 ;------------------------------------------------------------
                            588 ;------------------------------------------------------------
                            589 ;	SRC/handler.c:66: void handler_loop() {
                            590 ;	-----------------------------------------
                            591 ;	 function handler_loop
                            592 ;	-----------------------------------------
   26F0                     593 _handler_loop:
                            594 ;	SRC/handler.c:67: while(1) {
   26F0                     595 00105$:
                            596 ;	SRC/handler.c:68: if( mode==MODE_POLL ) {
   26F0 90 29 05            597 	mov	dptr,#_MODE_POLL
   26F3 E4                  598 	clr	a
   26F4 93                  599 	movc	a,@a+dptr
   26F5 FA                  600 	mov	r2,a
   26F6 B5 0A 0E            601 	cjne	a,_mode,00102$
                            602 ;	SRC/handler.c:69: send_string("\r\npoll mode\r\n");
   26F9 90 29 0B            603 	mov	dptr,#__str_1
   26FC 75 F0 80            604 	mov	b,#0x80
   26FF 12 22 BD            605 	lcall	_send_string
                            606 ;	SRC/handler.c:70: poll_loop();
   2702 12 26 51            607 	lcall	_poll_loop
   2705 80 E9               608 	sjmp	00105$
   2707                     609 00102$:
                            610 ;	SRC/handler.c:72: send_string("\r\ninteruption mode\r\n");
   2707 90 29 19            611 	mov	dptr,#__str_2
   270A 75 F0 80            612 	mov	b,#0x80
   270D 12 22 BD            613 	lcall	_send_string
                            614 ;	SRC/handler.c:73: int_loop();
   2710 12 26 CC            615 	lcall	_int_loop
   2713 80 DB               616 	sjmp	00105$
                            617 ;------------------------------------------------------------
                            618 ;Allocation info for local variables in function 'error'
                            619 ;------------------------------------------------------------
                            620 ;------------------------------------------------------------
                            621 ;	SRC/handler.c:78: void error() {
                            622 ;	-----------------------------------------
                            623 ;	 function error
                            624 ;	-----------------------------------------
   2715                     625 _error:
                            626 ;	SRC/handler.c:79: send_string("\r\nerror\r\n");
   2715 90 29 2E            627 	mov	dptr,#__str_3
   2718 75 F0 80            628 	mov	b,#0x80
   271B 12 22 BD            629 	lcall	_send_string
                            630 ;	SRC/handler.c:80: state=STATE_ERROR;
   271E 75 0C 02            631 	mov	_state,#0x02
   2721 22                  632 	ret
                            633 ;------------------------------------------------------------
                            634 ;Allocation info for local variables in function 'handler_int'
                            635 ;------------------------------------------------------------
                            636 ;num                       Allocated to registers r2 
                            637 ;sym                       Allocated to stack - offset 1
                            638 ;array                     Allocated to stack - offset 2
                            639 ;i                         Allocated to registers r2 r3 
                            640 ;count                     Allocated to registers r2 r3 
                            641 ;------------------------------------------------------------
                            642 ;	SRC/handler.c:84: void handler_int() {
                            643 ;	-----------------------------------------
                            644 ;	 function handler_int
                            645 ;	-----------------------------------------
   2722                     646 _handler_int:
   2722 C0 0D               647 	push	_bp
   2724 E5 81               648 	mov	a,sp
   2726 F5 0D               649 	mov	_bp,a
   2728 24 11               650 	add	a,#0x11
   272A F5 81               651 	mov	sp,a
                            652 ;	SRC/handler.c:87: int array[8] = {0, 0, 0, 0, 0, 0, 0, 0};
   272C E5 0D               653 	mov	a,_bp
   272E 24 02               654 	add	a,#0x02
   2730 F8                  655 	mov	r0,a
   2731 76 00               656 	mov	@r0,#0x00
   2733 08                  657 	inc	r0
   2734 76 00               658 	mov	@r0,#0x00
   2736 18                  659 	dec	r0
   2737 74 02               660 	mov	a,#0x02
   2739 28                  661 	add	a,r0
   273A F9                  662 	mov	r1,a
   273B 77 00               663 	mov	@r1,#0x00
   273D 09                  664 	inc	r1
   273E 77 00               665 	mov	@r1,#0x00
   2740 74 04               666 	mov	a,#0x04
   2742 28                  667 	add	a,r0
   2743 F9                  668 	mov	r1,a
   2744 77 00               669 	mov	@r1,#0x00
   2746 09                  670 	inc	r1
   2747 77 00               671 	mov	@r1,#0x00
   2749 74 06               672 	mov	a,#0x06
   274B 28                  673 	add	a,r0
   274C F9                  674 	mov	r1,a
   274D 77 00               675 	mov	@r1,#0x00
   274F 09                  676 	inc	r1
   2750 77 00               677 	mov	@r1,#0x00
   2752 74 08               678 	mov	a,#0x08
   2754 28                  679 	add	a,r0
   2755 F9                  680 	mov	r1,a
   2756 77 00               681 	mov	@r1,#0x00
   2758 09                  682 	inc	r1
   2759 77 00               683 	mov	@r1,#0x00
   275B 74 0A               684 	mov	a,#0x0A
   275D 28                  685 	add	a,r0
   275E F9                  686 	mov	r1,a
   275F 77 00               687 	mov	@r1,#0x00
   2761 09                  688 	inc	r1
   2762 77 00               689 	mov	@r1,#0x00
   2764 74 0C               690 	mov	a,#0x0C
   2766 28                  691 	add	a,r0
   2767 F9                  692 	mov	r1,a
   2768 77 00               693 	mov	@r1,#0x00
   276A 09                  694 	inc	r1
   276B 77 00               695 	mov	@r1,#0x00
   276D 74 0E               696 	mov	a,#0x0E
   276F 28                  697 	add	a,r0
   2770 F9                  698 	mov	r1,a
   2771 77 00               699 	mov	@r1,#0x00
   2773 09                  700 	inc	r1
   2774 77 00               701 	mov	@r1,#0x00
                            702 ;	SRC/handler.c:91: if( state==STATE_ERROR ){//i?euaai iinea ioeaee
   2776 74 02               703 	mov	a,#0x02
   2778 B5 0C 07            704 	cjne	a,_state,00102$
                            705 ;	SRC/handler.c:92: reset();
   277B C0 00               706 	push	ar0
   277D 12 26 40            707 	lcall	_reset
   2780 D0 00               708 	pop	ar0
   2782                     709 00102$:
                            710 ;	SRC/handler.c:95: if( read_byte(&sym) ){
   2782 AA 0D               711 	mov	r2,_bp
   2784 0A                  712 	inc	r2
   2785 7B 00               713 	mov	r3,#0x00
   2787 7C 40               714 	mov	r4,#0x40
   2789 8A 82               715 	mov	dpl,r2
   278B 8B 83               716 	mov	dph,r3
   278D 8C F0               717 	mov	b,r4
   278F C0 00               718 	push	ar0
   2791 12 23 31            719 	lcall	_read_byte
   2794 E5 82               720 	mov	a,dpl
   2796 D0 00               721 	pop	ar0
   2798 70 03               722 	jnz	00141$
   279A 02 28 AC            723 	ljmp	00118$
   279D                     724 00141$:
                            725 ;	SRC/handler.c:96: switch (state) {
   279D E4                  726 	clr	a
   279E B5 0C 02            727 	cjne	a,_state,00142$
   27A1 80 03               728 	sjmp	00143$
   27A3                     729 00142$:
   27A3 02 28 AF            730 	ljmp	00124$
   27A6                     731 00143$:
                            732 ;	SRC/handler.c:98: if(sym>='0' && sym<='9'){
   27A6 A9 0D               733 	mov	r1,_bp
   27A8 09                  734 	inc	r1
   27A9 B7 30 00            735 	cjne	@r1,#0x30,00144$
   27AC                     736 00144$:
   27AC 40 53               737 	jc	00113$
   27AE A9 0D               738 	mov	r1,_bp
   27B0 09                  739 	inc	r1
   27B1 E7                  740 	mov	a,@r1
   27B2 24 C6               741 	add	a,#0xff - 0x39
   27B4 40 4B               742 	jc	00113$
                            743 ;	SRC/handler.c:99: send_byte(sym);
   27B6 A8 0D               744 	mov	r0,_bp
   27B8 08                  745 	inc	r0
   27B9 86 82               746 	mov	dpl,@r0
   27BB 12 22 89            747 	lcall	_send_byte
                            748 ;	SRC/handler.c:100: num=sym-'0';
   27BE A8 0D               749 	mov	r0,_bp
   27C0 08                  750 	inc	r0
   27C1 E6                  751 	mov	a,@r0
   27C2 24 D0               752 	add	a,#0xd0
   27C4 FA                  753 	mov	r2,a
                            754 ;	SRC/handler.c:102: if( num > NUMBER_LIMIT-number*10 ) {//noaiao aieuoa, ?ai NUMBER_LIMIT
   27C5 90 29 07            755 	mov	dptr,#_NUMBER_LIMIT
   27C8 E4                  756 	clr	a
   27C9 93                  757 	movc	a,@a+dptr
   27CA FB                  758 	mov	r3,a
   27CB 7C 00               759 	mov	r4,#0x00
   27CD E5 0B               760 	mov	a,_number
   27CF 75 F0 0A            761 	mov	b,#0x0A
   27D2 A4                  762 	mul	ab
   27D3 D3                  763 	setb	c
   27D4 9B                  764 	subb	a,r3
   27D5 F4                  765 	cpl	a
   27D6 B3                  766 	cpl	c
   27D7 FB                  767 	mov	r3,a
   27D8 EC                  768 	mov	a,r4
   27D9 95 F0               769 	subb	a,b
   27DB FC                  770 	mov	r4,a
   27DC 8A 05               771 	mov	ar5,r2
   27DE 7E 00               772 	mov	r6,#0x00
   27E0 C3                  773 	clr	c
   27E1 EB                  774 	mov	a,r3
   27E2 9D                  775 	subb	a,r5
   27E3 EC                  776 	mov	a,r4
   27E4 64 80               777 	xrl	a,#0x80
   27E6 8E F0               778 	mov	b,r6
   27E8 63 F0 80            779 	xrl	b,#0x80
   27EB 95 F0               780 	subb	a,b
   27ED 50 06               781 	jnc	00105$
                            782 ;	SRC/handler.c:103: error();
   27EF 12 27 15            783 	lcall	_error
                            784 ;	SRC/handler.c:104: return;
   27F2 02 28 AF            785 	ljmp	00124$
   27F5                     786 00105$:
                            787 ;	SRC/handler.c:107: number*=10;
   27F5 E5 0B               788 	mov	a,_number
   27F7 75 F0 0A            789 	mov	b,#0x0A
   27FA A4                  790 	mul	ab
                            791 ;	SRC/handler.c:108: number+=num;
   27FB 2A                  792 	add	a,r2
   27FC F5 0B               793 	mov	_number,a
   27FE 02 28 AF            794 	ljmp	00124$
   2801                     795 00113$:
                            796 ;	SRC/handler.c:109: }else if (sym == '\r'){
   2801 A9 0D               797 	mov	r1,_bp
   2803 09                  798 	inc	r1
   2804 B7 0D 02            799 	cjne	@r1,#0x0D,00148$
   2807 80 03               800 	sjmp	00149$
   2809                     801 00148$:
   2809 02 28 A7            802 	ljmp	00110$
   280C                     803 00149$:
                            804 ;	SRC/handler.c:110: send_string("\r\nBin:");
   280C 90 29 38            805 	mov	dptr,#__str_4
   280F 75 F0 80            806 	mov	b,#0x80
   2812 C0 00               807 	push	ar0
   2814 12 22 BD            808 	lcall	_send_string
   2817 D0 00               809 	pop	ar0
                            810 ;	SRC/handler.c:111: while (number > 0) {
   2819 7A 00               811 	mov	r2,#0x00
   281B 7B 00               812 	mov	r3,#0x00
   281D                     813 00106$:
   281D E5 0B               814 	mov	a,_number
   281F 60 25               815 	jz	00108$
                            816 ;	SRC/handler.c:112: array[count] = number % 2;
   2821 8A 04               817 	mov	ar4,r2
   2823 EB                  818 	mov	a,r3
   2824 CC                  819 	xch	a,r4
   2825 25 E0               820 	add	a,acc
   2827 CC                  821 	xch	a,r4
   2828 33                  822 	rlc	a
   2829 EC                  823 	mov	a,r4
   282A 28                  824 	add	a,r0
   282B F9                  825 	mov	r1,a
   282C 74 01               826 	mov	a,#0x01
   282E 55 0B               827 	anl	a,_number
   2830 FC                  828 	mov	r4,a
   2831 7D 00               829 	mov	r5,#0x00
   2833 A7 04               830 	mov	@r1,ar4
   2835 09                  831 	inc	r1
   2836 A7 05               832 	mov	@r1,ar5
   2838 19                  833 	dec	r1
                            834 ;	SRC/handler.c:113: number = number / 2;
   2839 E5 0B               835 	mov	a,_number
   283B C3                  836 	clr	c
   283C 13                  837 	rrc	a
   283D F5 0B               838 	mov	_number,a
                            839 ;	SRC/handler.c:114: count++;
   283F 0A                  840 	inc	r2
   2840 BA 00 DA            841 	cjne	r2,#0x00,00106$
   2843 0B                  842 	inc	r3
   2844 80 D7               843 	sjmp	00106$
   2846                     844 00108$:
                            845 ;	SRC/handler.c:116: for (i = 7; i >= 0; i--) {
   2846 7A 07               846 	mov	r2,#0x07
   2848 7B 00               847 	mov	r3,#0x00
   284A                     848 00120$:
   284A EB                  849 	mov	a,r3
   284B 20 E7 4B            850 	jb	acc.7,00123$
                            851 ;	SRC/handler.c:117: send_byte(array[i] + '0');
   284E 8A 04               852 	mov	ar4,r2
   2850 EB                  853 	mov	a,r3
   2851 CC                  854 	xch	a,r4
   2852 25 E0               855 	add	a,acc
   2854 CC                  856 	xch	a,r4
   2855 33                  857 	rlc	a
   2856 EC                  858 	mov	a,r4
   2857 28                  859 	add	a,r0
   2858 F9                  860 	mov	r1,a
   2859 87 04               861 	mov	ar4,@r1
   285B 09                  862 	inc	r1
   285C 87 05               863 	mov	ar5,@r1
   285E 19                  864 	dec	r1
   285F 74 30               865 	mov	a,#0x30
   2861 2C                  866 	add	a,r4
   2862 F5 82               867 	mov	dpl,a
   2864 C0 02               868 	push	ar2
   2866 C0 03               869 	push	ar3
   2868 C0 00               870 	push	ar0
   286A C0 01               871 	push	ar1
   286C 12 22 89            872 	lcall	_send_byte
   286F D0 01               873 	pop	ar1
   2871 D0 00               874 	pop	ar0
   2873 D0 03               875 	pop	ar3
   2875 D0 02               876 	pop	ar2
                            877 ;	SRC/handler.c:118: led(i, array[i]);
   2877 87 04               878 	mov	ar4,@r1
   2879 09                  879 	inc	r1
   287A 87 05               880 	mov	ar5,@r1
   287C 19                  881 	dec	r1
   287D 8A 82               882 	mov	dpl,r2
   287F C0 02               883 	push	ar2
   2881 C0 03               884 	push	ar3
   2883 C0 00               885 	push	ar0
   2885 C0 04               886 	push	ar4
   2887 12 24 16            887 	lcall	_led
   288A 15 81               888 	dec	sp
   288C D0 00               889 	pop	ar0
   288E D0 03               890 	pop	ar3
   2890 D0 02               891 	pop	ar2
                            892 ;	SRC/handler.c:116: for (i = 7; i >= 0; i--) {
   2892 1A                  893 	dec	r2
   2893 BA FF 01            894 	cjne	r2,#0xff,00152$
   2896 1B                  895 	dec	r3
   2897                     896 00152$:
   2897 80 B1               897 	sjmp	00120$
   2899                     898 00123$:
                            899 ;	SRC/handler.c:121: send_string("\r\n");
   2899 90 29 08            900 	mov	dptr,#__str_0
   289C 75 F0 80            901 	mov	b,#0x80
   289F 12 22 BD            902 	lcall	_send_string
                            903 ;	SRC/handler.c:122: reset();
   28A2 12 26 40            904 	lcall	_reset
   28A5 80 08               905 	sjmp	00124$
   28A7                     906 00110$:
                            907 ;	SRC/handler.c:125: error();
   28A7 12 27 15            908 	lcall	_error
                            909 ;	SRC/handler.c:128: }
   28AA 80 03               910 	sjmp	00124$
   28AC                     911 00118$:
                            912 ;	SRC/handler.c:130: error();
   28AC 12 27 15            913 	lcall	_error
   28AF                     914 00124$:
   28AF 85 0D 81            915 	mov	sp,_bp
   28B2 D0 0D               916 	pop	_bp
   28B4 22                  917 	ret
                            918 	.area CSEG    (CODE)
                            919 	.area CONST   (CODE)
   2903                     920 _true:
   2903 FF                  921 	.db #0xFF
   2904                     922 _false:
   2904 00                  923 	.db #0x00
   2905                     924 _MODE_POLL:
   2905 00                  925 	.db #0x00
   2906                     926 _DIP_POLL_MODE:
   2906 01                  927 	.db #0x01
   2907                     928 _NUMBER_LIMIT:
   2907 FF                  929 	.db #0xFF
   2908                     930 __str_0:
   2908 0D                  931 	.db 0x0D
   2909 0A                  932 	.db 0x0A
   290A 00                  933 	.db 0x00
   290B                     934 __str_1:
   290B 0D                  935 	.db 0x0D
   290C 0A                  936 	.db 0x0A
   290D 70 6F 6C 6C 20 6D   937 	.ascii "poll mode"
        6F 64 65
   2916 0D                  938 	.db 0x0D
   2917 0A                  939 	.db 0x0A
   2918 00                  940 	.db 0x00
   2919                     941 __str_2:
   2919 0D                  942 	.db 0x0D
   291A 0A                  943 	.db 0x0A
   291B 69 6E 74 65 72 75   944 	.ascii "interuption mode"
        70 74 69 6F 6E 20
        6D 6F 64 65
   292B 0D                  945 	.db 0x0D
   292C 0A                  946 	.db 0x0A
   292D 00                  947 	.db 0x00
   292E                     948 __str_3:
   292E 0D                  949 	.db 0x0D
   292F 0A                  950 	.db 0x0A
   2930 65 72 72 6F 72      951 	.ascii "error"
   2935 0D                  952 	.db 0x0D
   2936 0A                  953 	.db 0x0A
   2937 00                  954 	.db 0x00
   2938                     955 __str_4:
   2938 0D                  956 	.db 0x0D
   2939 0A                  957 	.db 0x0A
   293A 42 69 6E 3A         958 	.ascii "Bin:"
   293E 00                  959 	.db 0x00
                            960 	.area XINIT   (CODE)
                            961 	.area CABS    (ABS,CODE)
