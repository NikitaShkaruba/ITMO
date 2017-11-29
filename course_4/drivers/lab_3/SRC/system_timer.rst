                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 2.9.0 #5416 (Mar 22 2009) (MINGW32)
                              4 ; This file was generated Wed Nov 08 13:56:49 2017
                              5 ;--------------------------------------------------------
                              6 	.module system_timer
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
                            164 	.globl _delay_ms
                            165 ;--------------------------------------------------------
                            166 ; special function registers
                            167 ;--------------------------------------------------------
                            168 	.area RSEG    (DATA)
                    0080    169 _P0	=	0x0080
                    0081    170 _SP	=	0x0081
                    0082    171 _DPL	=	0x0082
                    0083    172 _DPH	=	0x0083
                    0084    173 _DPP	=	0x0084
                    0087    174 _PCON	=	0x0087
                    0088    175 _TCON	=	0x0088
                    0089    176 _TMOD	=	0x0089
                    008A    177 _TL0	=	0x008a
                    008B    178 _TL1	=	0x008b
                    008C    179 _TH0	=	0x008c
                    008D    180 _TH1	=	0x008d
                    0090    181 _P1	=	0x0090
                    0098    182 _SCON	=	0x0098
                    0099    183 _SBUF	=	0x0099
                    009A    184 _I2CDAT	=	0x009a
                    009B    185 _I2CADD	=	0x009b
                    00A0    186 _P2	=	0x00a0
                    00A8    187 _IE	=	0x00a8
                    00A9    188 _IE2	=	0x00a9
                    00B0    189 _P3	=	0x00b0
                    00B8    190 _IP	=	0x00b8
                    00B9    191 _ECON	=	0x00b9
                    00BA    192 _ETIM1	=	0x00ba
                    00BB    193 _ETIM2	=	0x00bb
                    00C4    194 _ETIM3	=	0x00c4
                    00BC    195 _EDATA1	=	0x00bc
                    00BD    196 _EDATA2	=	0x00bd
                    00BE    197 _EDATA3	=	0x00be
                    00BF    198 _EDATA4	=	0x00bf
                    00C0    199 _WDCON	=	0x00c0
                    00C6    200 _EADRL	=	0x00c6
                    00C8    201 _T2CON	=	0x00c8
                    00CA    202 _RCAP2L	=	0x00ca
                    00CB    203 _RCAP2H	=	0x00cb
                    00CC    204 _TL2	=	0x00cc
                    00CD    205 _TH2	=	0x00cd
                    00D0    206 _PSW	=	0x00d0
                    00D2    207 _DMAL	=	0x00d2
                    00D3    208 _DMAH	=	0x00d3
                    00D4    209 _DMAP	=	0x00d4
                    00D8    210 _ADCCON2	=	0x00d8
                    00D9    211 _ADCDATAL	=	0x00d9
                    00DA    212 _ADCDATAH	=	0x00da
                    00DF    213 _PSMCON	=	0x00df
                    00E0    214 _ACC	=	0x00e0
                    00E8    215 _I2CCON	=	0x00e8
                    00EF    216 _ADCCON1	=	0x00ef
                    00F0    217 _B	=	0x00f0
                    00F1    218 _ADCOFSL	=	0x00f1
                    00F2    219 _ADCOFSH	=	0x00f2
                    00F3    220 _ADCGAINL	=	0x00f3
                    00F4    221 _ADCGAINH	=	0x00f4
                    00F5    222 _ADCCON3	=	0x00f5
                    00F7    223 _SPIDAT	=	0x00f7
                    00F8    224 _SPICON	=	0x00f8
                    00F9    225 _DAC0L	=	0x00f9
                    00FA    226 _DAC0H	=	0x00fa
                    00FB    227 _DAC1L	=	0x00fb
                    00FC    228 _DAC1H	=	0x00fc
                    00FD    229 _DACCON	=	0x00fd
                            230 ;--------------------------------------------------------
                            231 ; special function bits
                            232 ;--------------------------------------------------------
                            233 	.area RSEG    (DATA)
                    008F    234 _TF1	=	0x008f
                    008E    235 _TR1	=	0x008e
                    008D    236 _TF0	=	0x008d
                    008C    237 _TR0	=	0x008c
                    008B    238 _IE1	=	0x008b
                    008A    239 _IT1	=	0x008a
                    0089    240 _IE0	=	0x0089
                    0088    241 _IT0	=	0x0088
                    0091    242 _T2EX	=	0x0091
                    0090    243 _T2	=	0x0090
                    009F    244 _SM0	=	0x009f
                    009E    245 _SM1	=	0x009e
                    009D    246 _SM2	=	0x009d
                    009C    247 _REN	=	0x009c
                    009B    248 _TB8	=	0x009b
                    009A    249 _RB8	=	0x009a
                    0099    250 _TI	=	0x0099
                    0098    251 _RI	=	0x0098
                    00AF    252 _EA	=	0x00af
                    00AE    253 _EADC	=	0x00ae
                    00AD    254 _ET2	=	0x00ad
                    00AC    255 _ES	=	0x00ac
                    00AB    256 _ET1	=	0x00ab
                    00AA    257 _EX1	=	0x00aa
                    00A9    258 _ET0	=	0x00a9
                    00A8    259 _EX0	=	0x00a8
                    00B7    260 _RD	=	0x00b7
                    00B6    261 _WR	=	0x00b6
                    00B5    262 _T1	=	0x00b5
                    00B4    263 _T0	=	0x00b4
                    00B3    264 _INT1	=	0x00b3
                    00B2    265 _INT0	=	0x00b2
                    00B1    266 _TXD	=	0x00b1
                    00B0    267 _RXD	=	0x00b0
                    00BF    268 _PSI	=	0x00bf
                    00BE    269 _PADC	=	0x00be
                    00BD    270 _PT2	=	0x00bd
                    00BC    271 _PS	=	0x00bc
                    00BB    272 _PT1	=	0x00bb
                    00BA    273 _PX1	=	0x00ba
                    00B9    274 _PT0	=	0x00b9
                    00B8    275 _PX0	=	0x00b8
                    00C7    276 _PRE2	=	0x00c7
                    00C6    277 _PRE1	=	0x00c6
                    00C5    278 _PRE0	=	0x00c5
                    00C3    279 _WDR1	=	0x00c3
                    00C2    280 _WDR2	=	0x00c2
                    00C1    281 _WDS	=	0x00c1
                    00C0    282 _WDE	=	0x00c0
                    00CF    283 _TF2	=	0x00cf
                    00CE    284 _EXF2	=	0x00ce
                    00CD    285 _RCLK	=	0x00cd
                    00CC    286 _TCLK	=	0x00cc
                    00CB    287 _XEN	=	0x00cb
                    00CA    288 _TR2	=	0x00ca
                    00C9    289 _CNT2	=	0x00c9
                    00C8    290 _CAP2	=	0x00c8
                    00D7    291 _CY	=	0x00d7
                    00D6    292 _AC	=	0x00d6
                    00D5    293 _F0	=	0x00d5
                    00D4    294 _RS1	=	0x00d4
                    00D3    295 _RS0	=	0x00d3
                    00D2    296 _OV	=	0x00d2
                    00D1    297 _F1	=	0x00d1
                    00D0    298 _P	=	0x00d0
                    00DF    299 _ADCI	=	0x00df
                    00DE    300 _DMA	=	0x00de
                    00DD    301 _CCONV	=	0x00dd
                    00DC    302 _SCONV	=	0x00dc
                    00DB    303 _CS3	=	0x00db
                    00DA    304 _CS2	=	0x00da
                    00D9    305 _CS1	=	0x00d9
                    00D8    306 _CS0	=	0x00d8
                    00EF    307 _MDO	=	0x00ef
                    00EE    308 _MDE	=	0x00ee
                    00ED    309 _MCO	=	0x00ed
                    00EC    310 _MDI	=	0x00ec
                    00EB    311 _I2CM	=	0x00eb
                    00EA    312 _I2CRS	=	0x00ea
                    00E9    313 _I2CTX	=	0x00e9
                    00E8    314 _I2CI	=	0x00e8
                    00FF    315 _ISPI	=	0x00ff
                    00FE    316 _WCOL	=	0x00fe
                    00FD    317 _SPE	=	0x00fd
                    00FC    318 _SPIM	=	0x00fc
                    00FB    319 _CPOL	=	0x00fb
                    00FA    320 _CPHA	=	0x00fa
                    00F9    321 _SPR1	=	0x00f9
                    00F8    322 _SPR0	=	0x00f8
                            323 ;--------------------------------------------------------
                            324 ; overlayable register banks
                            325 ;--------------------------------------------------------
                            326 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     327 	.ds 8
                            328 ;--------------------------------------------------------
                            329 ; internal ram data
                            330 ;--------------------------------------------------------
                            331 	.area DSEG    (DATA)
                            332 ;--------------------------------------------------------
                            333 ; overlayable items in internal ram 
                            334 ;--------------------------------------------------------
                            335 	.area OSEG    (OVR,DATA)
                            336 ;--------------------------------------------------------
                            337 ; indirectly addressable internal ram data
                            338 ;--------------------------------------------------------
                            339 	.area ISEG    (DATA)
                            340 ;--------------------------------------------------------
                            341 ; absolute internal ram data
                            342 ;--------------------------------------------------------
                            343 	.area IABS    (ABS,DATA)
                            344 	.area IABS    (ABS,DATA)
                            345 ;--------------------------------------------------------
                            346 ; bit data
                            347 ;--------------------------------------------------------
                            348 	.area BSEG    (BIT)
                            349 ;--------------------------------------------------------
                            350 ; paged external ram data
                            351 ;--------------------------------------------------------
                            352 	.area PSEG    (PAG,XDATA)
                            353 ;--------------------------------------------------------
                            354 ; external ram data
                            355 ;--------------------------------------------------------
                            356 	.area XSEG    (XDATA)
                            357 ;--------------------------------------------------------
                            358 ; absolute external ram data
                            359 ;--------------------------------------------------------
                            360 	.area XABS    (ABS,XDATA)
                            361 ;--------------------------------------------------------
                            362 ; external initialized ram data
                            363 ;--------------------------------------------------------
                            364 	.area XISEG   (XDATA)
                            365 	.area HOME    (CODE)
                            366 	.area GSINIT0 (CODE)
                            367 	.area GSINIT1 (CODE)
                            368 	.area GSINIT2 (CODE)
                            369 	.area GSINIT3 (CODE)
                            370 	.area GSINIT4 (CODE)
                            371 	.area GSINIT5 (CODE)
                            372 	.area GSINIT  (CODE)
                            373 	.area GSFINAL (CODE)
                            374 	.area CSEG    (CODE)
                            375 ;--------------------------------------------------------
                            376 ; global & static initialisations
                            377 ;--------------------------------------------------------
                            378 	.area HOME    (CODE)
                            379 	.area GSINIT  (CODE)
                            380 	.area GSFINAL (CODE)
                            381 	.area GSINIT  (CODE)
                            382 ;--------------------------------------------------------
                            383 ; Home
                            384 ;--------------------------------------------------------
                            385 	.area HOME    (CODE)
                            386 	.area HOME    (CODE)
                            387 ;--------------------------------------------------------
                            388 ; code
                            389 ;--------------------------------------------------------
                            390 	.area CSEG    (CODE)
                            391 ;------------------------------------------------------------
                            392 ;Allocation info for local variables in function 'delay_ms'
                            393 ;------------------------------------------------------------
                            394 ;ms                        Allocated to registers r2 r3 r4 r5 
                            395 ;i                         Allocated to stack - offset 1
                            396 ;j                         Allocated to stack - offset 5
                            397 ;------------------------------------------------------------
                            398 ;	SRC/system_timer.c:3: void delay_ms ( unsigned long ms )
                            399 ;	-----------------------------------------
                            400 ;	 function delay_ms
                            401 ;	-----------------------------------------
   21C7                     402 _delay_ms:
                    0002    403 	ar2 = 0x02
                    0003    404 	ar3 = 0x03
                    0004    405 	ar4 = 0x04
                    0005    406 	ar5 = 0x05
                    0006    407 	ar6 = 0x06
                    0007    408 	ar7 = 0x07
                    0000    409 	ar0 = 0x00
                    0001    410 	ar1 = 0x01
   21C7 C0 0D               411 	push	_bp
   21C9 85 81 0D            412 	mov	_bp,sp
   21CC AA 82               413 	mov	r2,dpl
   21CE AB 83               414 	mov	r3,dph
   21D0 AC F0               415 	mov	r4,b
   21D2 FD                  416 	mov	r5,a
   21D3 E5 81               417 	mov	a,sp
   21D5 24 08               418 	add	a,#0x08
   21D7 F5 81               419 	mov	sp,a
                            420 ;	SRC/system_timer.c:6: for( j = 0; j < ms; j++ )
   21D9 E5 0D               421 	mov	a,_bp
   21DB 24 05               422 	add	a,#0x05
   21DD F8                  423 	mov	r0,a
   21DE E4                  424 	clr	a
   21DF F6                  425 	mov	@r0,a
   21E0 08                  426 	inc	r0
   21E1 F6                  427 	mov	@r0,a
   21E2 08                  428 	inc	r0
   21E3 F6                  429 	mov	@r0,a
   21E4 08                  430 	inc	r0
   21E5 F6                  431 	mov	@r0,a
   21E6                     432 00105$:
   21E6 E5 0D               433 	mov	a,_bp
   21E8 24 05               434 	add	a,#0x05
   21EA F8                  435 	mov	r0,a
   21EB C3                  436 	clr	c
   21EC E6                  437 	mov	a,@r0
   21ED 9A                  438 	subb	a,r2
   21EE 08                  439 	inc	r0
   21EF E6                  440 	mov	a,@r0
   21F0 9B                  441 	subb	a,r3
   21F1 08                  442 	inc	r0
   21F2 E6                  443 	mov	a,@r0
   21F3 9C                  444 	subb	a,r4
   21F4 08                  445 	inc	r0
   21F5 E6                  446 	mov	a,@r0
   21F6 9D                  447 	subb	a,r5
   21F7 50 4C               448 	jnc	00109$
                            449 ;	SRC/system_timer.c:8: for( i = 0; i < 50; i++ );
   21F9 A8 0D               450 	mov	r0,_bp
   21FB 08                  451 	inc	r0
   21FC E4                  452 	clr	a
   21FD F6                  453 	mov	@r0,a
   21FE 08                  454 	inc	r0
   21FF F6                  455 	mov	@r0,a
   2200 08                  456 	inc	r0
   2201 F6                  457 	mov	@r0,a
   2202 08                  458 	inc	r0
   2203 F6                  459 	mov	@r0,a
   2204                     460 00101$:
   2204 A8 0D               461 	mov	r0,_bp
   2206 08                  462 	inc	r0
   2207 C3                  463 	clr	c
   2208 E6                  464 	mov	a,@r0
   2209 94 32               465 	subb	a,#0x32
   220B 08                  466 	inc	r0
   220C E6                  467 	mov	a,@r0
   220D 94 00               468 	subb	a,#0x00
   220F 08                  469 	inc	r0
   2210 E6                  470 	mov	a,@r0
   2211 94 00               471 	subb	a,#0x00
   2213 08                  472 	inc	r0
   2214 E6                  473 	mov	a,@r0
   2215 94 00               474 	subb	a,#0x00
   2217 50 15               475 	jnc	00107$
   2219 A8 0D               476 	mov	r0,_bp
   221B 08                  477 	inc	r0
   221C 74 01               478 	mov	a,#0x01
   221E 26                  479 	add	a,@r0
   221F F6                  480 	mov	@r0,a
   2220 E4                  481 	clr	a
   2221 08                  482 	inc	r0
   2222 36                  483 	addc	a,@r0
   2223 F6                  484 	mov	@r0,a
   2224 E4                  485 	clr	a
   2225 08                  486 	inc	r0
   2226 36                  487 	addc	a,@r0
   2227 F6                  488 	mov	@r0,a
   2228 E4                  489 	clr	a
   2229 08                  490 	inc	r0
   222A 36                  491 	addc	a,@r0
   222B F6                  492 	mov	@r0,a
   222C 80 D6               493 	sjmp	00101$
   222E                     494 00107$:
                            495 ;	SRC/system_timer.c:6: for( j = 0; j < ms; j++ )
   222E E5 0D               496 	mov	a,_bp
   2230 24 05               497 	add	a,#0x05
   2232 F8                  498 	mov	r0,a
   2233 74 01               499 	mov	a,#0x01
   2235 26                  500 	add	a,@r0
   2236 F6                  501 	mov	@r0,a
   2237 E4                  502 	clr	a
   2238 08                  503 	inc	r0
   2239 36                  504 	addc	a,@r0
   223A F6                  505 	mov	@r0,a
   223B E4                  506 	clr	a
   223C 08                  507 	inc	r0
   223D 36                  508 	addc	a,@r0
   223E F6                  509 	mov	@r0,a
   223F E4                  510 	clr	a
   2240 08                  511 	inc	r0
   2241 36                  512 	addc	a,@r0
   2242 F6                  513 	mov	@r0,a
   2243 80 A1               514 	sjmp	00105$
   2245                     515 00109$:
   2245 85 0D 81            516 	mov	sp,_bp
   2248 D0 0D               517 	pop	_bp
   224A 22                  518 	ret
                            519 	.area CSEG    (CODE)
                            520 	.area CONST   (CODE)
   28FC                     521 _true:
   28FC FF                  522 	.db #0xFF
   28FD                     523 _false:
   28FD 00                  524 	.db #0x00
                            525 	.area XINIT   (CODE)
                            526 	.area CABS    (ABS,CODE)
