                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 2.9.0 #5416 (Mar 22 2009) (MINGW32)
                              4 ; This file was generated Wed Nov 22 10:14:02 2017
                              5 ;--------------------------------------------------------
                              6 	.module system_timer
                              7 	.optsdcc -mmcs51 --model-small
                              8 	
                              9 ;--------------------------------------------------------
                             10 ; Public variables in this module
                             11 ;--------------------------------------------------------
                             12 	.globl _LEVEL_OFF
                             13 	.globl _LEVEL_ON
                             14 	.globl _false
                             15 	.globl _true
                             16 	.globl _SPR0
                             17 	.globl _SPR1
                             18 	.globl _CPHA
                             19 	.globl _CPOL
                             20 	.globl _SPIM
                             21 	.globl _SPE
                             22 	.globl _WCOL
                             23 	.globl _ISPI
                             24 	.globl _I2CI
                             25 	.globl _I2CTX
                             26 	.globl _I2CRS
                             27 	.globl _I2CM
                             28 	.globl _MDI
                             29 	.globl _MCO
                             30 	.globl _MDE
                             31 	.globl _MDO
                             32 	.globl _CS0
                             33 	.globl _CS1
                             34 	.globl _CS2
                             35 	.globl _CS3
                             36 	.globl _SCONV
                             37 	.globl _CCONV
                             38 	.globl _DMA
                             39 	.globl _ADCI
                             40 	.globl _P
                             41 	.globl _F1
                             42 	.globl _OV
                             43 	.globl _RS0
                             44 	.globl _RS1
                             45 	.globl _F0
                             46 	.globl _AC
                             47 	.globl _CY
                             48 	.globl _CAP2
                             49 	.globl _CNT2
                             50 	.globl _TR2
                             51 	.globl _XEN
                             52 	.globl _TCLK
                             53 	.globl _RCLK
                             54 	.globl _EXF2
                             55 	.globl _TF2
                             56 	.globl _WDE
                             57 	.globl _WDS
                             58 	.globl _WDR2
                             59 	.globl _WDR1
                             60 	.globl _PRE0
                             61 	.globl _PRE1
                             62 	.globl _PRE2
                             63 	.globl _PX0
                             64 	.globl _PT0
                             65 	.globl _PX1
                             66 	.globl _PT1
                             67 	.globl _PS
                             68 	.globl _PT2
                             69 	.globl _PADC
                             70 	.globl _PSI
                             71 	.globl _RXD
                             72 	.globl _TXD
                             73 	.globl _INT0
                             74 	.globl _INT1
                             75 	.globl _T0
                             76 	.globl _T1
                             77 	.globl _WR
                             78 	.globl _RD
                             79 	.globl _EX0
                             80 	.globl _ET0
                             81 	.globl _EX1
                             82 	.globl _ET1
                             83 	.globl _ES
                             84 	.globl _ET2
                             85 	.globl _EADC
                             86 	.globl _EA
                             87 	.globl _RI
                             88 	.globl _TI
                             89 	.globl _RB8
                             90 	.globl _TB8
                             91 	.globl _REN
                             92 	.globl _SM2
                             93 	.globl _SM1
                             94 	.globl _SM0
                             95 	.globl _T2
                             96 	.globl _T2EX
                             97 	.globl _IT0
                             98 	.globl _IE0
                             99 	.globl _IT1
                            100 	.globl _IE1
                            101 	.globl _TR0
                            102 	.globl _TF0
                            103 	.globl _TR1
                            104 	.globl _TF1
                            105 	.globl _DACCON
                            106 	.globl _DAC1H
                            107 	.globl _DAC1L
                            108 	.globl _DAC0H
                            109 	.globl _DAC0L
                            110 	.globl _SPICON
                            111 	.globl _SPIDAT
                            112 	.globl _ADCCON3
                            113 	.globl _ADCGAINH
                            114 	.globl _ADCGAINL
                            115 	.globl _ADCOFSH
                            116 	.globl _ADCOFSL
                            117 	.globl _B
                            118 	.globl _ADCCON1
                            119 	.globl _I2CCON
                            120 	.globl _ACC
                            121 	.globl _PSMCON
                            122 	.globl _ADCDATAH
                            123 	.globl _ADCDATAL
                            124 	.globl _ADCCON2
                            125 	.globl _DMAP
                            126 	.globl _DMAH
                            127 	.globl _DMAL
                            128 	.globl _PSW
                            129 	.globl _TH2
                            130 	.globl _TL2
                            131 	.globl _RCAP2H
                            132 	.globl _RCAP2L
                            133 	.globl _T2CON
                            134 	.globl _EADRL
                            135 	.globl _WDCON
                            136 	.globl _EDATA4
                            137 	.globl _EDATA3
                            138 	.globl _EDATA2
                            139 	.globl _EDATA1
                            140 	.globl _ETIM3
                            141 	.globl _ETIM2
                            142 	.globl _ETIM1
                            143 	.globl _ECON
                            144 	.globl _IP
                            145 	.globl _P3
                            146 	.globl _IE2
                            147 	.globl _IE
                            148 	.globl _P2
                            149 	.globl _I2CADD
                            150 	.globl _I2CDAT
                            151 	.globl _SBUF
                            152 	.globl _SCON
                            153 	.globl _P1
                            154 	.globl _TH1
                            155 	.globl _TH0
                            156 	.globl _TL1
                            157 	.globl _TL0
                            158 	.globl _TMOD
                            159 	.globl _TCON
                            160 	.globl _PCON
                            161 	.globl _DPP
                            162 	.globl _DPH
                            163 	.globl _DPL
                            164 	.globl _SP
                            165 	.globl _P0
                            166 	.globl _cur_ms
                            167 	.globl _cnt
                            168 	.globl _initialize_system_timer
                            169 	.globl _get_ms
                            170 	.globl _get_ms_after
                            171 	.globl _delay_ms
                            172 	.globl _T2_ISR
                            173 ;--------------------------------------------------------
                            174 ; special function registers
                            175 ;--------------------------------------------------------
                            176 	.area RSEG    (DATA)
                    0080    177 _P0	=	0x0080
                    0081    178 _SP	=	0x0081
                    0082    179 _DPL	=	0x0082
                    0083    180 _DPH	=	0x0083
                    0084    181 _DPP	=	0x0084
                    0087    182 _PCON	=	0x0087
                    0088    183 _TCON	=	0x0088
                    0089    184 _TMOD	=	0x0089
                    008A    185 _TL0	=	0x008a
                    008B    186 _TL1	=	0x008b
                    008C    187 _TH0	=	0x008c
                    008D    188 _TH1	=	0x008d
                    0090    189 _P1	=	0x0090
                    0098    190 _SCON	=	0x0098
                    0099    191 _SBUF	=	0x0099
                    009A    192 _I2CDAT	=	0x009a
                    009B    193 _I2CADD	=	0x009b
                    00A0    194 _P2	=	0x00a0
                    00A8    195 _IE	=	0x00a8
                    00A9    196 _IE2	=	0x00a9
                    00B0    197 _P3	=	0x00b0
                    00B8    198 _IP	=	0x00b8
                    00B9    199 _ECON	=	0x00b9
                    00BA    200 _ETIM1	=	0x00ba
                    00BB    201 _ETIM2	=	0x00bb
                    00C4    202 _ETIM3	=	0x00c4
                    00BC    203 _EDATA1	=	0x00bc
                    00BD    204 _EDATA2	=	0x00bd
                    00BE    205 _EDATA3	=	0x00be
                    00BF    206 _EDATA4	=	0x00bf
                    00C0    207 _WDCON	=	0x00c0
                    00C6    208 _EADRL	=	0x00c6
                    00C8    209 _T2CON	=	0x00c8
                    00CA    210 _RCAP2L	=	0x00ca
                    00CB    211 _RCAP2H	=	0x00cb
                    00CC    212 _TL2	=	0x00cc
                    00CD    213 _TH2	=	0x00cd
                    00D0    214 _PSW	=	0x00d0
                    00D2    215 _DMAL	=	0x00d2
                    00D3    216 _DMAH	=	0x00d3
                    00D4    217 _DMAP	=	0x00d4
                    00D8    218 _ADCCON2	=	0x00d8
                    00D9    219 _ADCDATAL	=	0x00d9
                    00DA    220 _ADCDATAH	=	0x00da
                    00DF    221 _PSMCON	=	0x00df
                    00E0    222 _ACC	=	0x00e0
                    00E8    223 _I2CCON	=	0x00e8
                    00EF    224 _ADCCON1	=	0x00ef
                    00F0    225 _B	=	0x00f0
                    00F1    226 _ADCOFSL	=	0x00f1
                    00F2    227 _ADCOFSH	=	0x00f2
                    00F3    228 _ADCGAINL	=	0x00f3
                    00F4    229 _ADCGAINH	=	0x00f4
                    00F5    230 _ADCCON3	=	0x00f5
                    00F7    231 _SPIDAT	=	0x00f7
                    00F8    232 _SPICON	=	0x00f8
                    00F9    233 _DAC0L	=	0x00f9
                    00FA    234 _DAC0H	=	0x00fa
                    00FB    235 _DAC1L	=	0x00fb
                    00FC    236 _DAC1H	=	0x00fc
                    00FD    237 _DACCON	=	0x00fd
                            238 ;--------------------------------------------------------
                            239 ; special function bits
                            240 ;--------------------------------------------------------
                            241 	.area RSEG    (DATA)
                    008F    242 _TF1	=	0x008f
                    008E    243 _TR1	=	0x008e
                    008D    244 _TF0	=	0x008d
                    008C    245 _TR0	=	0x008c
                    008B    246 _IE1	=	0x008b
                    008A    247 _IT1	=	0x008a
                    0089    248 _IE0	=	0x0089
                    0088    249 _IT0	=	0x0088
                    0091    250 _T2EX	=	0x0091
                    0090    251 _T2	=	0x0090
                    009F    252 _SM0	=	0x009f
                    009E    253 _SM1	=	0x009e
                    009D    254 _SM2	=	0x009d
                    009C    255 _REN	=	0x009c
                    009B    256 _TB8	=	0x009b
                    009A    257 _RB8	=	0x009a
                    0099    258 _TI	=	0x0099
                    0098    259 _RI	=	0x0098
                    00AF    260 _EA	=	0x00af
                    00AE    261 _EADC	=	0x00ae
                    00AD    262 _ET2	=	0x00ad
                    00AC    263 _ES	=	0x00ac
                    00AB    264 _ET1	=	0x00ab
                    00AA    265 _EX1	=	0x00aa
                    00A9    266 _ET0	=	0x00a9
                    00A8    267 _EX0	=	0x00a8
                    00B7    268 _RD	=	0x00b7
                    00B6    269 _WR	=	0x00b6
                    00B5    270 _T1	=	0x00b5
                    00B4    271 _T0	=	0x00b4
                    00B3    272 _INT1	=	0x00b3
                    00B2    273 _INT0	=	0x00b2
                    00B1    274 _TXD	=	0x00b1
                    00B0    275 _RXD	=	0x00b0
                    00BF    276 _PSI	=	0x00bf
                    00BE    277 _PADC	=	0x00be
                    00BD    278 _PT2	=	0x00bd
                    00BC    279 _PS	=	0x00bc
                    00BB    280 _PT1	=	0x00bb
                    00BA    281 _PX1	=	0x00ba
                    00B9    282 _PT0	=	0x00b9
                    00B8    283 _PX0	=	0x00b8
                    00C7    284 _PRE2	=	0x00c7
                    00C6    285 _PRE1	=	0x00c6
                    00C5    286 _PRE0	=	0x00c5
                    00C3    287 _WDR1	=	0x00c3
                    00C2    288 _WDR2	=	0x00c2
                    00C1    289 _WDS	=	0x00c1
                    00C0    290 _WDE	=	0x00c0
                    00CF    291 _TF2	=	0x00cf
                    00CE    292 _EXF2	=	0x00ce
                    00CD    293 _RCLK	=	0x00cd
                    00CC    294 _TCLK	=	0x00cc
                    00CB    295 _XEN	=	0x00cb
                    00CA    296 _TR2	=	0x00ca
                    00C9    297 _CNT2	=	0x00c9
                    00C8    298 _CAP2	=	0x00c8
                    00D7    299 _CY	=	0x00d7
                    00D6    300 _AC	=	0x00d6
                    00D5    301 _F0	=	0x00d5
                    00D4    302 _RS1	=	0x00d4
                    00D3    303 _RS0	=	0x00d3
                    00D2    304 _OV	=	0x00d2
                    00D1    305 _F1	=	0x00d1
                    00D0    306 _P	=	0x00d0
                    00DF    307 _ADCI	=	0x00df
                    00DE    308 _DMA	=	0x00de
                    00DD    309 _CCONV	=	0x00dd
                    00DC    310 _SCONV	=	0x00dc
                    00DB    311 _CS3	=	0x00db
                    00DA    312 _CS2	=	0x00da
                    00D9    313 _CS1	=	0x00d9
                    00D8    314 _CS0	=	0x00d8
                    00EF    315 _MDO	=	0x00ef
                    00EE    316 _MDE	=	0x00ee
                    00ED    317 _MCO	=	0x00ed
                    00EC    318 _MDI	=	0x00ec
                    00EB    319 _I2CM	=	0x00eb
                    00EA    320 _I2CRS	=	0x00ea
                    00E9    321 _I2CTX	=	0x00e9
                    00E8    322 _I2CI	=	0x00e8
                    00FF    323 _ISPI	=	0x00ff
                    00FE    324 _WCOL	=	0x00fe
                    00FD    325 _SPE	=	0x00fd
                    00FC    326 _SPIM	=	0x00fc
                    00FB    327 _CPOL	=	0x00fb
                    00FA    328 _CPHA	=	0x00fa
                    00F9    329 _SPR1	=	0x00f9
                    00F8    330 _SPR0	=	0x00f8
                            331 ;--------------------------------------------------------
                            332 ; overlayable register banks
                            333 ;--------------------------------------------------------
                            334 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     335 	.ds 8
                            336 ;--------------------------------------------------------
                            337 ; overlayable bit register bank
                            338 ;--------------------------------------------------------
                            339 	.area BIT_BANK	(REL,OVR,DATA)
   0020                     340 bits:
   0020                     341 	.ds 1
                    8000    342 	b0 = bits[0]
                    8100    343 	b1 = bits[1]
                    8200    344 	b2 = bits[2]
                    8300    345 	b3 = bits[3]
                    8400    346 	b4 = bits[4]
                    8500    347 	b5 = bits[5]
                    8600    348 	b6 = bits[6]
                    8700    349 	b7 = bits[7]
                            350 ;--------------------------------------------------------
                            351 ; internal ram data
                            352 ;--------------------------------------------------------
                            353 	.area DSEG    (DATA)
   0009                     354 _cnt::
   0009                     355 	.ds 2
   000B                     356 _cur_ms::
   000B                     357 	.ds 4
                            358 ;--------------------------------------------------------
                            359 ; overlayable items in internal ram 
                            360 ;--------------------------------------------------------
                            361 	.area OSEG    (OVR,DATA)
                            362 ;--------------------------------------------------------
                            363 ; indirectly addressable internal ram data
                            364 ;--------------------------------------------------------
                            365 	.area ISEG    (DATA)
                            366 ;--------------------------------------------------------
                            367 ; absolute internal ram data
                            368 ;--------------------------------------------------------
                            369 	.area IABS    (ABS,DATA)
                            370 	.area IABS    (ABS,DATA)
                            371 ;--------------------------------------------------------
                            372 ; bit data
                            373 ;--------------------------------------------------------
                            374 	.area BSEG    (BIT)
                            375 ;--------------------------------------------------------
                            376 ; paged external ram data
                            377 ;--------------------------------------------------------
                            378 	.area PSEG    (PAG,XDATA)
                            379 ;--------------------------------------------------------
                            380 ; external ram data
                            381 ;--------------------------------------------------------
                            382 	.area XSEG    (XDATA)
                            383 ;--------------------------------------------------------
                            384 ; absolute external ram data
                            385 ;--------------------------------------------------------
                            386 	.area XABS    (ABS,XDATA)
                            387 ;--------------------------------------------------------
                            388 ; external initialized ram data
                            389 ;--------------------------------------------------------
                            390 	.area XISEG   (XDATA)
                            391 	.area HOME    (CODE)
                            392 	.area GSINIT0 (CODE)
                            393 	.area GSINIT1 (CODE)
                            394 	.area GSINIT2 (CODE)
                            395 	.area GSINIT3 (CODE)
                            396 	.area GSINIT4 (CODE)
                            397 	.area GSINIT5 (CODE)
                            398 	.area GSINIT  (CODE)
                            399 	.area GSFINAL (CODE)
                            400 	.area CSEG    (CODE)
                            401 ;--------------------------------------------------------
                            402 ; global & static initialisations
                            403 ;--------------------------------------------------------
                            404 	.area HOME    (CODE)
                            405 	.area GSINIT  (CODE)
                            406 	.area GSFINAL (CODE)
                            407 	.area GSINIT  (CODE)
                            408 ;	SRC/system_timer.c:7: u16 cnt=0;
   2164 E4                  409 	clr	a
   2165 F5 09               410 	mov	_cnt,a
   2167 F5 0A               411 	mov	(_cnt + 1),a
                            412 ;--------------------------------------------------------
                            413 ; Home
                            414 ;--------------------------------------------------------
                            415 	.area HOME    (CODE)
                            416 	.area HOME    (CODE)
                            417 ;--------------------------------------------------------
                            418 ; code
                            419 ;--------------------------------------------------------
                            420 	.area CSEG    (CODE)
                            421 ;------------------------------------------------------------
                            422 ;Allocation info for local variables in function 'initialize_system_timer'
                            423 ;------------------------------------------------------------
                            424 ;------------------------------------------------------------
                            425 ;	SRC/system_timer.c:16: void initialize_system_timer() {
                            426 ;	-----------------------------------------
                            427 ;	 function initialize_system_timer
                            428 ;	-----------------------------------------
   2273                     429 _initialize_system_timer:
                    0002    430 	ar2 = 0x02
                    0003    431 	ar3 = 0x03
                    0004    432 	ar4 = 0x04
                    0005    433 	ar5 = 0x05
                    0006    434 	ar6 = 0x06
                    0007    435 	ar7 = 0x07
                    0000    436 	ar0 = 0x00
                    0001    437 	ar1 = 0x01
                            438 ;	SRC/system_timer.c:17: cur_ms=0;
                            439 ;	SRC/system_timer.c:18: cnt=0;
   2273 E4                  440 	clr	a
   2274 F5 0B               441 	mov	_cur_ms,a
   2276 F5 0C               442 	mov	(_cur_ms + 1),a
   2278 F5 0D               443 	mov	(_cur_ms + 2),a
   227A F5 0E               444 	mov	(_cur_ms + 3),a
   227C F5 09               445 	mov	_cnt,a
   227E F5 0A               446 	mov	(_cnt + 1),a
                            447 ;	SRC/system_timer.c:20: SetVector( 0x202B, (void *)T2_ISR );
   2280 7A 30               448 	mov	r2,#_T2_ISR
   2282 7B 23               449 	mov	r3,#(_T2_ISR >> 8)
   2284 7C 80               450 	mov	r4,#0x80
   2286 C0 02               451 	push	ar2
   2288 C0 03               452 	push	ar3
   228A C0 04               453 	push	ar4
   228C 90 20 2B            454 	mov	dptr,#0x202B
   228F 12 22 3B            455 	lcall	_SetVector
   2292 15 81               456 	dec	sp
   2294 15 81               457 	dec	sp
   2296 15 81               458 	dec	sp
                            459 ;	SRC/system_timer.c:23: TH2=(-1000)>>8;0;
   2298 75 CD FC            460 	mov	_TH2,#0xFC
                            461 ;	SRC/system_timer.c:24: TL2=(-1000)&0xFF;
   229B 75 CC 18            462 	mov	_TL2,#0x18
                            463 ;	SRC/system_timer.c:25: RCAP2H=(-1000)>>8;
   229E 75 CB FC            464 	mov	_RCAP2H,#0xFC
                            465 ;	SRC/system_timer.c:26: RCAP2L=(-1000)&0xFF;
   22A1 75 CA 18            466 	mov	_RCAP2L,#0x18
                            467 ;	SRC/system_timer.c:28: ET2=1;       //включаем прерывание от таймера 2
   22A4 D2 AD               468 	setb	_ET2
                            469 ;	SRC/system_timer.c:29: TR2=1;      //разрешаем счет таймера 2
   22A6 D2 CA               470 	setb	_TR2
   22A8 22                  471 	ret
                            472 ;------------------------------------------------------------
                            473 ;Allocation info for local variables in function 'get_ms'
                            474 ;------------------------------------------------------------
                            475 ;------------------------------------------------------------
                            476 ;	SRC/system_timer.c:32: time get_ms(void){
                            477 ;	-----------------------------------------
                            478 ;	 function get_ms
                            479 ;	-----------------------------------------
   22A9                     480 _get_ms:
                            481 ;	SRC/system_timer.c:33: return cur_ms;
   22A9 85 0B 82            482 	mov	dpl,_cur_ms
   22AC 85 0C 83            483 	mov	dph,(_cur_ms + 1)
   22AF 85 0D F0            484 	mov	b,(_cur_ms + 2)
   22B2 E5 0E               485 	mov	a,(_cur_ms + 3)
   22B4 22                  486 	ret
                            487 ;------------------------------------------------------------
                            488 ;Allocation info for local variables in function 'get_ms_after'
                            489 ;------------------------------------------------------------
                            490 ;t0                        Allocated to registers r2 r3 r4 r5 
                            491 ;------------------------------------------------------------
                            492 ;	SRC/system_timer.c:36: time get_ms_after(time t0){
                            493 ;	-----------------------------------------
                            494 ;	 function get_ms_after
                            495 ;	-----------------------------------------
   22B5                     496 _get_ms_after:
   22B5 AA 82               497 	mov	r2,dpl
   22B7 AB 83               498 	mov	r3,dph
   22B9 AC F0               499 	mov	r4,b
   22BB FD                  500 	mov	r5,a
                            501 ;	SRC/system_timer.c:37: return cur_ms-t0;
   22BC E5 0B               502 	mov	a,_cur_ms
   22BE C3                  503 	clr	c
   22BF 9A                  504 	subb	a,r2
   22C0 FA                  505 	mov	r2,a
   22C1 E5 0C               506 	mov	a,(_cur_ms + 1)
   22C3 9B                  507 	subb	a,r3
   22C4 FB                  508 	mov	r3,a
   22C5 E5 0D               509 	mov	a,(_cur_ms + 2)
   22C7 9C                  510 	subb	a,r4
   22C8 FC                  511 	mov	r4,a
   22C9 E5 0E               512 	mov	a,(_cur_ms + 3)
   22CB 9D                  513 	subb	a,r5
   22CC 8A 82               514 	mov	dpl,r2
   22CE 8B 83               515 	mov	dph,r3
   22D0 8C F0               516 	mov	b,r4
   22D2 22                  517 	ret
                            518 ;------------------------------------------------------------
                            519 ;Allocation info for local variables in function 'delay_ms'
                            520 ;------------------------------------------------------------
                            521 ;t                         Allocated to stack - offset 1
                            522 ;now                       Allocated to stack - offset 5
                            523 ;------------------------------------------------------------
                            524 ;	SRC/system_timer.c:40: void delay_ms(time t){
                            525 ;	-----------------------------------------
                            526 ;	 function delay_ms
                            527 ;	-----------------------------------------
   22D3                     528 _delay_ms:
   22D3 C0 18               529 	push	_bp
   22D5 85 81 18            530 	mov	_bp,sp
   22D8 C0 82               531 	push	dpl
   22DA C0 83               532 	push	dph
   22DC C0 F0               533 	push	b
   22DE C0 E0               534 	push	acc
   22E0 E5 81               535 	mov	a,sp
   22E2 24 08               536 	add	a,#0x08
   22E4 F5 81               537 	mov	sp,a
                            538 ;	SRC/system_timer.c:41: time now=get_ms();
   22E6 12 22 A9            539 	lcall	_get_ms
   22E9 AA 82               540 	mov	r2,dpl
   22EB AB 83               541 	mov	r3,dph
   22ED AC F0               542 	mov	r4,b
   22EF FD                  543 	mov	r5,a
   22F0 E5 18               544 	mov	a,_bp
   22F2 24 05               545 	add	a,#0x05
   22F4 F8                  546 	mov	r0,a
   22F5 A6 02               547 	mov	@r0,ar2
   22F7 08                  548 	inc	r0
   22F8 A6 03               549 	mov	@r0,ar3
   22FA 08                  550 	inc	r0
   22FB A6 04               551 	mov	@r0,ar4
   22FD 08                  552 	inc	r0
   22FE A6 05               553 	mov	@r0,ar5
                            554 ;	SRC/system_timer.c:43: while( get_ms_after(now)<t){}
   2300                     555 00101$:
   2300 E5 18               556 	mov	a,_bp
   2302 24 05               557 	add	a,#0x05
   2304 F8                  558 	mov	r0,a
   2305 86 82               559 	mov	dpl,@r0
   2307 08                  560 	inc	r0
   2308 86 83               561 	mov	dph,@r0
   230A 08                  562 	inc	r0
   230B 86 F0               563 	mov	b,@r0
   230D 08                  564 	inc	r0
   230E E6                  565 	mov	a,@r0
   230F 12 22 B5            566 	lcall	_get_ms_after
   2312 AC 82               567 	mov	r4,dpl
   2314 AD 83               568 	mov	r5,dph
   2316 AA F0               569 	mov	r2,b
   2318 FB                  570 	mov	r3,a
   2319 A8 18               571 	mov	r0,_bp
   231B 08                  572 	inc	r0
   231C C3                  573 	clr	c
   231D EC                  574 	mov	a,r4
   231E 96                  575 	subb	a,@r0
   231F ED                  576 	mov	a,r5
   2320 08                  577 	inc	r0
   2321 96                  578 	subb	a,@r0
   2322 EA                  579 	mov	a,r2
   2323 08                  580 	inc	r0
   2324 96                  581 	subb	a,@r0
   2325 EB                  582 	mov	a,r3
   2326 08                  583 	inc	r0
   2327 96                  584 	subb	a,@r0
   2328 40 D6               585 	jc	00101$
   232A 85 18 81            586 	mov	sp,_bp
   232D D0 18               587 	pop	_bp
   232F 22                  588 	ret
                            589 ;------------------------------------------------------------
                            590 ;Allocation info for local variables in function 'T2_ISR'
                            591 ;------------------------------------------------------------
                            592 ;------------------------------------------------------------
                            593 ;	SRC/system_timer.c:46: void T2_ISR( void ) __interrupt ( 2 ){
                            594 ;	-----------------------------------------
                            595 ;	 function T2_ISR
                            596 ;	-----------------------------------------
   2330                     597 _T2_ISR:
   2330 C0 20               598 	push	bits
   2332 C0 E0               599 	push	acc
   2334 C0 F0               600 	push	b
   2336 C0 82               601 	push	dpl
   2338 C0 83               602 	push	dph
   233A C0 02               603 	push	(0+2)
   233C C0 03               604 	push	(0+3)
   233E C0 04               605 	push	(0+4)
   2340 C0 05               606 	push	(0+5)
   2342 C0 06               607 	push	(0+6)
   2344 C0 07               608 	push	(0+7)
   2346 C0 00               609 	push	(0+0)
   2348 C0 01               610 	push	(0+1)
   234A C0 D0               611 	push	psw
   234C 75 D0 00            612 	mov	psw,#0x00
                            613 ;	SRC/system_timer.c:47: cur_ms++;
   234F 05 0B               614 	inc	_cur_ms
   2351 E4                  615 	clr	a
   2352 B5 0B 0C            616 	cjne	a,_cur_ms,00103$
   2355 05 0C               617 	inc	(_cur_ms + 1)
   2357 B5 0C 07            618 	cjne	a,(_cur_ms + 1),00103$
   235A 05 0D               619 	inc	(_cur_ms + 2)
   235C B5 0D 02            620 	cjne	a,(_cur_ms + 2),00103$
   235F 05 0E               621 	inc	(_cur_ms + 3)
   2361                     622 00103$:
                            623 ;	SRC/system_timer.c:49: scan_keyboard_int();
   2361 12 2A 49            624 	lcall	_scan_keyboard_int
   2364 D0 D0               625 	pop	psw
   2366 D0 01               626 	pop	(0+1)
   2368 D0 00               627 	pop	(0+0)
   236A D0 07               628 	pop	(0+7)
   236C D0 06               629 	pop	(0+6)
   236E D0 05               630 	pop	(0+5)
   2370 D0 04               631 	pop	(0+4)
   2372 D0 03               632 	pop	(0+3)
   2374 D0 02               633 	pop	(0+2)
   2376 D0 83               634 	pop	dph
   2378 D0 82               635 	pop	dpl
   237A D0 F0               636 	pop	b
   237C D0 E0               637 	pop	acc
   237E D0 20               638 	pop	bits
   2380 32                  639 	reti
                            640 	.area CSEG    (CODE)
                            641 	.area CONST   (CODE)
   2C4B                     642 _true:
   2C4B FF                  643 	.db #0xFF
   2C4C                     644 _false:
   2C4C 00                  645 	.db #0x00
   2C4D                     646 _LEVEL_ON:
   2C4D F0                  647 	.db #0xF0
   2C4E                     648 _LEVEL_OFF:
   2C4E 0F                  649 	.db #0x0F
                            650 	.area XINIT   (CODE)
                            651 	.area CABS    (ABS,CODE)
