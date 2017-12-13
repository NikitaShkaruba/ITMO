                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 2.9.0 #5416 (Mar 22 2009) (MINGW32)
                              4 ; This file was generated Wed Nov 22 10:14:02 2017
                              5 ;--------------------------------------------------------
                              6 	.module speaker
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
                            164 	.globl _speaker_on
                            165 	.globl _initialize_speaker
                            166 	.globl _enable_speaker
                            167 	.globl _disable_speaker
                            168 	.globl _T0_ISR
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
                            333 ; overlayable bit register bank
                            334 ;--------------------------------------------------------
                            335 	.area BIT_BANK	(REL,OVR,DATA)
   0020                     336 bits:
   0020                     337 	.ds 1
                    8000    338 	b0 = bits[0]
                    8100    339 	b1 = bits[1]
                    8200    340 	b2 = bits[2]
                    8300    341 	b3 = bits[3]
                    8400    342 	b4 = bits[4]
                    8500    343 	b5 = bits[5]
                    8600    344 	b6 = bits[6]
                    8700    345 	b7 = bits[7]
                            346 ;--------------------------------------------------------
                            347 ; internal ram data
                            348 ;--------------------------------------------------------
                            349 	.area DSEG    (DATA)
   0016                     350 _speaker_on::
   0016                     351 	.ds 1
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
                            402 ;--------------------------------------------------------
                            403 ; Home
                            404 ;--------------------------------------------------------
                            405 	.area HOME    (CODE)
                            406 	.area HOME    (CODE)
                            407 ;--------------------------------------------------------
                            408 ; code
                            409 ;--------------------------------------------------------
                            410 	.area CSEG    (CODE)
                            411 ;------------------------------------------------------------
                            412 ;Allocation info for local variables in function 'initialize_speaker'
                            413 ;------------------------------------------------------------
                            414 ;------------------------------------------------------------
                            415 ;	SRC/speaker.c:10: void initialize_speaker(){
                            416 ;	-----------------------------------------
                            417 ;	 function initialize_speaker
                            418 ;	-----------------------------------------
   2B52                     419 _initialize_speaker:
                    0002    420 	ar2 = 0x02
                    0003    421 	ar3 = 0x03
                    0004    422 	ar4 = 0x04
                    0005    423 	ar5 = 0x05
                    0006    424 	ar6 = 0x06
                    0007    425 	ar7 = 0x07
                    0000    426 	ar0 = 0x00
                    0001    427 	ar1 = 0x01
                            428 ;	SRC/speaker.c:11: SetVector( 0x200B, (void *)T0_ISR );
   2B52 7A 96               429 	mov	r2,#_T0_ISR
   2B54 7B 2B               430 	mov	r3,#(_T0_ISR >> 8)
   2B56 7C 80               431 	mov	r4,#0x80
   2B58 C0 02               432 	push	ar2
   2B5A C0 03               433 	push	ar3
   2B5C C0 04               434 	push	ar4
   2B5E 90 20 0B            435 	mov	dptr,#0x200B
   2B61 12 22 3B            436 	lcall	_SetVector
   2B64 15 81               437 	dec	sp
   2B66 15 81               438 	dec	sp
   2B68 15 81               439 	dec	sp
                            440 ;	SRC/speaker.c:12: TMOD|=0b00000010; //Timer0, внутренний генератор, 8 бит счетчик
   2B6A 43 89 02            441 	orl	_TMOD,#0x02
                            442 ;	SRC/speaker.c:13: ET0=1;       //включаем прерывание от таймера 0
   2B6D D2 A9               443 	setb	_ET0
                            444 ;	SRC/speaker.c:14: TH0=-250;
   2B6F 75 8C 06            445 	mov	_TH0,#0x06
   2B72 22                  446 	ret
                            447 ;------------------------------------------------------------
                            448 ;Allocation info for local variables in function 'enable_speaker'
                            449 ;------------------------------------------------------------
                            450 ;------------------------------------------------------------
                            451 ;	SRC/speaker.c:17: void enable_speaker(){
                            452 ;	-----------------------------------------
                            453 ;	 function enable_speaker
                            454 ;	-----------------------------------------
   2B73                     455 _enable_speaker:
                            456 ;	SRC/speaker.c:18: speaker_on=false;
   2B73 90 2C 9C            457 	mov	dptr,#_false
   2B76 E4                  458 	clr	a
   2B77 93                  459 	movc	a,@a+dptr
   2B78 F5 16               460 	mov	_speaker_on,a
                            461 ;	SRC/speaker.c:19: TL0=-250;
   2B7A 75 8A 06            462 	mov	_TL0,#0x06
                            463 ;	SRC/speaker.c:20: TR0=1;      //разрешаем счет таймера 0
   2B7D D2 8C               464 	setb	_TR0
   2B7F 22                  465 	ret
                            466 ;------------------------------------------------------------
                            467 ;Allocation info for local variables in function 'disable_speaker'
                            468 ;------------------------------------------------------------
                            469 ;------------------------------------------------------------
                            470 ;	SRC/speaker.c:23: void disable_speaker(){
                            471 ;	-----------------------------------------
                            472 ;	 function disable_speaker
                            473 ;	-----------------------------------------
   2B80                     474 _disable_speaker:
                            475 ;	SRC/speaker.c:24: TR0=0;      //запрещаем счет таймера 0
   2B80 C2 8C               476 	clr	_TR0
                            477 ;	SRC/speaker.c:26: speaker_on=false;
   2B82 90 2C 9C            478 	mov	dptr,#_false
   2B85 E4                  479 	clr	a
   2B86 93                  480 	movc	a,@a+dptr
   2B87 F5 16               481 	mov	_speaker_on,a
                            482 ;	SRC/speaker.c:27: write_max(ENA, 0b0100000);
   2B89 74 20               483 	mov	a,#0x20
   2B8B C0 E0               484 	push	acc
   2B8D 90 00 04            485 	mov	dptr,#0x0004
   2B90 12 22 01            486 	lcall	_write_max
   2B93 15 81               487 	dec	sp
   2B95 22                  488 	ret
                            489 ;------------------------------------------------------------
                            490 ;Allocation info for local variables in function 'T0_ISR'
                            491 ;------------------------------------------------------------
                            492 ;------------------------------------------------------------
                            493 ;	SRC/speaker.c:30: void T0_ISR( void ) __interrupt ( 2 ){
                            494 ;	-----------------------------------------
                            495 ;	 function T0_ISR
                            496 ;	-----------------------------------------
   2B96                     497 _T0_ISR:
   2B96 C0 20               498 	push	bits
   2B98 C0 E0               499 	push	acc
   2B9A C0 F0               500 	push	b
   2B9C C0 82               501 	push	dpl
   2B9E C0 83               502 	push	dph
   2BA0 C0 02               503 	push	(0+2)
   2BA2 C0 03               504 	push	(0+3)
   2BA4 C0 04               505 	push	(0+4)
   2BA6 C0 05               506 	push	(0+5)
   2BA8 C0 06               507 	push	(0+6)
   2BAA C0 07               508 	push	(0+7)
   2BAC C0 00               509 	push	(0+0)
   2BAE C0 01               510 	push	(0+1)
   2BB0 C0 D0               511 	push	psw
   2BB2 75 D0 00            512 	mov	psw,#0x00
                            513 ;	SRC/speaker.c:31: if( speaker_on ){
   2BB5 E5 16               514 	mov	a,_speaker_on
   2BB7 60 0E               515 	jz	00102$
                            516 ;	SRC/speaker.c:32: write_max(ENA, 0b0111100);
   2BB9 74 3C               517 	mov	a,#0x3C
   2BBB C0 E0               518 	push	acc
   2BBD 90 00 04            519 	mov	dptr,#0x0004
   2BC0 12 22 01            520 	lcall	_write_max
   2BC3 15 81               521 	dec	sp
   2BC5 80 0C               522 	sjmp	00103$
   2BC7                     523 00102$:
                            524 ;	SRC/speaker.c:34: write_max(ENA, 0b0100000);
   2BC7 74 20               525 	mov	a,#0x20
   2BC9 C0 E0               526 	push	acc
   2BCB 90 00 04            527 	mov	dptr,#0x0004
   2BCE 12 22 01            528 	lcall	_write_max
   2BD1 15 81               529 	dec	sp
   2BD3                     530 00103$:
                            531 ;	SRC/speaker.c:37: speaker_on=!speaker_on;
   2BD3 E5 16               532 	mov	a,_speaker_on
   2BD5 B4 01 00            533 	cjne	a,#0x01,00108$
   2BD8                     534 00108$:
   2BD8 E4                  535 	clr	a
   2BD9 33                  536 	rlc	a
   2BDA F5 16               537 	mov	_speaker_on,a
   2BDC D0 D0               538 	pop	psw
   2BDE D0 01               539 	pop	(0+1)
   2BE0 D0 00               540 	pop	(0+0)
   2BE2 D0 07               541 	pop	(0+7)
   2BE4 D0 06               542 	pop	(0+6)
   2BE6 D0 05               543 	pop	(0+5)
   2BE8 D0 04               544 	pop	(0+4)
   2BEA D0 03               545 	pop	(0+3)
   2BEC D0 02               546 	pop	(0+2)
   2BEE D0 83               547 	pop	dph
   2BF0 D0 82               548 	pop	dpl
   2BF2 D0 F0               549 	pop	b
   2BF4 D0 E0               550 	pop	acc
   2BF6 D0 20               551 	pop	bits
   2BF8 32                  552 	reti
                            553 	.area CSEG    (CODE)
                            554 	.area CONST   (CODE)
   2C9B                     555 _true:
   2C9B FF                  556 	.db #0xFF
   2C9C                     557 _false:
   2C9C 00                  558 	.db #0x00
                            559 	.area XINIT   (CODE)
                            560 	.area CABS    (ABS,CODE)
