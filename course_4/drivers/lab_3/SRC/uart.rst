                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 2.9.0 #5416 (Mar 22 2009) (MINGW32)
                              4 ; This file was generated Wed Nov 08 15:20:25 2017
                              5 ;--------------------------------------------------------
                              6 	.module uart
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
                            164 	.globl _sending_byte
                            165 	.globl _buffer_out
                            166 	.globl _buffer_in
                            167 	.globl _initialize_uart
                            168 	.globl _send_byte
                            169 	.globl _send_string
                            170 	.globl _read_byte
                            171 	.globl _UART_ISR
                            172 ;--------------------------------------------------------
                            173 ; special function registers
                            174 ;--------------------------------------------------------
                            175 	.area RSEG    (DATA)
                    0080    176 _P0	=	0x0080
                    0081    177 _SP	=	0x0081
                    0082    178 _DPL	=	0x0082
                    0083    179 _DPH	=	0x0083
                    0084    180 _DPP	=	0x0084
                    0087    181 _PCON	=	0x0087
                    0088    182 _TCON	=	0x0088
                    0089    183 _TMOD	=	0x0089
                    008A    184 _TL0	=	0x008a
                    008B    185 _TL1	=	0x008b
                    008C    186 _TH0	=	0x008c
                    008D    187 _TH1	=	0x008d
                    0090    188 _P1	=	0x0090
                    0098    189 _SCON	=	0x0098
                    0099    190 _SBUF	=	0x0099
                    009A    191 _I2CDAT	=	0x009a
                    009B    192 _I2CADD	=	0x009b
                    00A0    193 _P2	=	0x00a0
                    00A8    194 _IE	=	0x00a8
                    00A9    195 _IE2	=	0x00a9
                    00B0    196 _P3	=	0x00b0
                    00B8    197 _IP	=	0x00b8
                    00B9    198 _ECON	=	0x00b9
                    00BA    199 _ETIM1	=	0x00ba
                    00BB    200 _ETIM2	=	0x00bb
                    00C4    201 _ETIM3	=	0x00c4
                    00BC    202 _EDATA1	=	0x00bc
                    00BD    203 _EDATA2	=	0x00bd
                    00BE    204 _EDATA3	=	0x00be
                    00BF    205 _EDATA4	=	0x00bf
                    00C0    206 _WDCON	=	0x00c0
                    00C6    207 _EADRL	=	0x00c6
                    00C8    208 _T2CON	=	0x00c8
                    00CA    209 _RCAP2L	=	0x00ca
                    00CB    210 _RCAP2H	=	0x00cb
                    00CC    211 _TL2	=	0x00cc
                    00CD    212 _TH2	=	0x00cd
                    00D0    213 _PSW	=	0x00d0
                    00D2    214 _DMAL	=	0x00d2
                    00D3    215 _DMAH	=	0x00d3
                    00D4    216 _DMAP	=	0x00d4
                    00D8    217 _ADCCON2	=	0x00d8
                    00D9    218 _ADCDATAL	=	0x00d9
                    00DA    219 _ADCDATAH	=	0x00da
                    00DF    220 _PSMCON	=	0x00df
                    00E0    221 _ACC	=	0x00e0
                    00E8    222 _I2CCON	=	0x00e8
                    00EF    223 _ADCCON1	=	0x00ef
                    00F0    224 _B	=	0x00f0
                    00F1    225 _ADCOFSL	=	0x00f1
                    00F2    226 _ADCOFSH	=	0x00f2
                    00F3    227 _ADCGAINL	=	0x00f3
                    00F4    228 _ADCGAINH	=	0x00f4
                    00F5    229 _ADCCON3	=	0x00f5
                    00F7    230 _SPIDAT	=	0x00f7
                    00F8    231 _SPICON	=	0x00f8
                    00F9    232 _DAC0L	=	0x00f9
                    00FA    233 _DAC0H	=	0x00fa
                    00FB    234 _DAC1L	=	0x00fb
                    00FC    235 _DAC1H	=	0x00fc
                    00FD    236 _DACCON	=	0x00fd
                            237 ;--------------------------------------------------------
                            238 ; special function bits
                            239 ;--------------------------------------------------------
                            240 	.area RSEG    (DATA)
                    008F    241 _TF1	=	0x008f
                    008E    242 _TR1	=	0x008e
                    008D    243 _TF0	=	0x008d
                    008C    244 _TR0	=	0x008c
                    008B    245 _IE1	=	0x008b
                    008A    246 _IT1	=	0x008a
                    0089    247 _IE0	=	0x0089
                    0088    248 _IT0	=	0x0088
                    0091    249 _T2EX	=	0x0091
                    0090    250 _T2	=	0x0090
                    009F    251 _SM0	=	0x009f
                    009E    252 _SM1	=	0x009e
                    009D    253 _SM2	=	0x009d
                    009C    254 _REN	=	0x009c
                    009B    255 _TB8	=	0x009b
                    009A    256 _RB8	=	0x009a
                    0099    257 _TI	=	0x0099
                    0098    258 _RI	=	0x0098
                    00AF    259 _EA	=	0x00af
                    00AE    260 _EADC	=	0x00ae
                    00AD    261 _ET2	=	0x00ad
                    00AC    262 _ES	=	0x00ac
                    00AB    263 _ET1	=	0x00ab
                    00AA    264 _EX1	=	0x00aa
                    00A9    265 _ET0	=	0x00a9
                    00A8    266 _EX0	=	0x00a8
                    00B7    267 _RD	=	0x00b7
                    00B6    268 _WR	=	0x00b6
                    00B5    269 _T1	=	0x00b5
                    00B4    270 _T0	=	0x00b4
                    00B3    271 _INT1	=	0x00b3
                    00B2    272 _INT0	=	0x00b2
                    00B1    273 _TXD	=	0x00b1
                    00B0    274 _RXD	=	0x00b0
                    00BF    275 _PSI	=	0x00bf
                    00BE    276 _PADC	=	0x00be
                    00BD    277 _PT2	=	0x00bd
                    00BC    278 _PS	=	0x00bc
                    00BB    279 _PT1	=	0x00bb
                    00BA    280 _PX1	=	0x00ba
                    00B9    281 _PT0	=	0x00b9
                    00B8    282 _PX0	=	0x00b8
                    00C7    283 _PRE2	=	0x00c7
                    00C6    284 _PRE1	=	0x00c6
                    00C5    285 _PRE0	=	0x00c5
                    00C3    286 _WDR1	=	0x00c3
                    00C2    287 _WDR2	=	0x00c2
                    00C1    288 _WDS	=	0x00c1
                    00C0    289 _WDE	=	0x00c0
                    00CF    290 _TF2	=	0x00cf
                    00CE    291 _EXF2	=	0x00ce
                    00CD    292 _RCLK	=	0x00cd
                    00CC    293 _TCLK	=	0x00cc
                    00CB    294 _XEN	=	0x00cb
                    00CA    295 _TR2	=	0x00ca
                    00C9    296 _CNT2	=	0x00c9
                    00C8    297 _CAP2	=	0x00c8
                    00D7    298 _CY	=	0x00d7
                    00D6    299 _AC	=	0x00d6
                    00D5    300 _F0	=	0x00d5
                    00D4    301 _RS1	=	0x00d4
                    00D3    302 _RS0	=	0x00d3
                    00D2    303 _OV	=	0x00d2
                    00D1    304 _F1	=	0x00d1
                    00D0    305 _P	=	0x00d0
                    00DF    306 _ADCI	=	0x00df
                    00DE    307 _DMA	=	0x00de
                    00DD    308 _CCONV	=	0x00dd
                    00DC    309 _SCONV	=	0x00dc
                    00DB    310 _CS3	=	0x00db
                    00DA    311 _CS2	=	0x00da
                    00D9    312 _CS1	=	0x00d9
                    00D8    313 _CS0	=	0x00d8
                    00EF    314 _MDO	=	0x00ef
                    00EE    315 _MDE	=	0x00ee
                    00ED    316 _MCO	=	0x00ed
                    00EC    317 _MDI	=	0x00ec
                    00EB    318 _I2CM	=	0x00eb
                    00EA    319 _I2CRS	=	0x00ea
                    00E9    320 _I2CTX	=	0x00e9
                    00E8    321 _I2CI	=	0x00e8
                    00FF    322 _ISPI	=	0x00ff
                    00FE    323 _WCOL	=	0x00fe
                    00FD    324 _SPE	=	0x00fd
                    00FC    325 _SPIM	=	0x00fc
                    00FB    326 _CPOL	=	0x00fb
                    00FA    327 _CPHA	=	0x00fa
                    00F9    328 _SPR1	=	0x00f9
                    00F8    329 _SPR0	=	0x00f8
                            330 ;--------------------------------------------------------
                            331 ; overlayable register banks
                            332 ;--------------------------------------------------------
                            333 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     334 	.ds 8
                            335 ;--------------------------------------------------------
                            336 ; overlayable bit register bank
                            337 ;--------------------------------------------------------
                            338 	.area BIT_BANK	(REL,OVR,DATA)
   0020                     339 bits:
   0020                     340 	.ds 1
                    8000    341 	b0 = bits[0]
                    8100    342 	b1 = bits[1]
                    8200    343 	b2 = bits[2]
                    8300    344 	b3 = bits[3]
                    8400    345 	b4 = bits[4]
                    8500    346 	b5 = bits[5]
                    8600    347 	b6 = bits[6]
                    8700    348 	b7 = bits[7]
                            349 ;--------------------------------------------------------
                            350 ; internal ram data
                            351 ;--------------------------------------------------------
                            352 	.area DSEG    (DATA)
   0021                     353 _MODE_INT:
   0021                     354 	.ds 1
   0022                     355 _buffer_in::
   0022                     356 	.ds 45
   004F                     357 _buffer_out::
   004F                     358 	.ds 45
   007C                     359 _sending_byte::
   007C                     360 	.ds 1
                            361 ;--------------------------------------------------------
                            362 ; overlayable items in internal ram 
                            363 ;--------------------------------------------------------
                            364 	.area OSEG    (OVR,DATA)
                            365 ;--------------------------------------------------------
                            366 ; indirectly addressable internal ram data
                            367 ;--------------------------------------------------------
                            368 	.area ISEG    (DATA)
                            369 ;--------------------------------------------------------
                            370 ; absolute internal ram data
                            371 ;--------------------------------------------------------
                            372 	.area IABS    (ABS,DATA)
                            373 	.area IABS    (ABS,DATA)
                            374 ;--------------------------------------------------------
                            375 ; bit data
                            376 ;--------------------------------------------------------
                            377 	.area BSEG    (BIT)
                            378 ;--------------------------------------------------------
                            379 ; paged external ram data
                            380 ;--------------------------------------------------------
                            381 	.area PSEG    (PAG,XDATA)
                            382 ;--------------------------------------------------------
                            383 ; external ram data
                            384 ;--------------------------------------------------------
                            385 	.area XSEG    (XDATA)
                            386 ;--------------------------------------------------------
                            387 ; absolute external ram data
                            388 ;--------------------------------------------------------
                            389 	.area XABS    (ABS,XDATA)
                            390 ;--------------------------------------------------------
                            391 ; external initialized ram data
                            392 ;--------------------------------------------------------
                            393 	.area XISEG   (XDATA)
                            394 	.area HOME    (CODE)
                            395 	.area GSINIT0 (CODE)
                            396 	.area GSINIT1 (CODE)
                            397 	.area GSINIT2 (CODE)
                            398 	.area GSINIT3 (CODE)
                            399 	.area GSINIT4 (CODE)
                            400 	.area GSINIT5 (CODE)
                            401 	.area GSINIT  (CODE)
                            402 	.area GSFINAL (CODE)
                            403 	.area CSEG    (CODE)
                            404 ;--------------------------------------------------------
                            405 ; global & static initialisations
                            406 ;--------------------------------------------------------
                            407 	.area HOME    (CODE)
                            408 	.area GSINIT  (CODE)
                            409 	.area GSFINAL (CODE)
                            410 	.area GSINIT  (CODE)
                            411 ;	./INCLUDE/handler.h:9: static u8 MODE_INT=0xFF;
   2161 75 21 FF            412 	mov	_MODE_INT,#0xFF
                            413 ;--------------------------------------------------------
                            414 ; Home
                            415 ;--------------------------------------------------------
                            416 	.area HOME    (CODE)
                            417 	.area HOME    (CODE)
                            418 ;--------------------------------------------------------
                            419 ; code
                            420 ;--------------------------------------------------------
                            421 	.area CSEG    (CODE)
                            422 ;------------------------------------------------------------
                            423 ;Allocation info for local variables in function 'initialize_uart'
                            424 ;------------------------------------------------------------
                            425 ;speed                     Allocated to registers r2 
                            426 ;------------------------------------------------------------
                            427 ;	SRC/uart.c:12: void initialize_uart(char speed) {
                            428 ;	-----------------------------------------
                            429 ;	 function initialize_uart
                            430 ;	-----------------------------------------
   224B                     431 _initialize_uart:
                    0002    432 	ar2 = 0x02
                    0003    433 	ar3 = 0x03
                    0004    434 	ar4 = 0x04
                    0005    435 	ar5 = 0x05
                    0006    436 	ar6 = 0x06
                    0007    437 	ar7 = 0x07
                    0000    438 	ar0 = 0x00
                    0001    439 	ar1 = 0x01
   224B AA 82               440 	mov	r2,dpl
                            441 ;	SRC/uart.c:13: initialize_buffer(&buffer_in);
   224D 90 00 22            442 	mov	dptr,#_buffer_in
   2250 75 F0 40            443 	mov	b,#0x40
   2253 C0 02               444 	push	ar2
   2255 12 24 6C            445 	lcall	_initialize_buffer
                            446 ;	SRC/uart.c:14: initialize_buffer(&buffer_out);
   2258 90 00 4F            447 	mov	dptr,#_buffer_out
   225B 75 F0 40            448 	mov	b,#0x40
   225E 12 24 6C            449 	lcall	_initialize_buffer
                            450 ;	SRC/uart.c:15: SetVector( 0x2023, (void *)UART_ISR );
   2261 7B 83               451 	mov	r3,#_UART_ISR
   2263 7C 23               452 	mov	r4,#(_UART_ISR >> 8)
   2265 7D 80               453 	mov	r5,#0x80
   2267 C0 03               454 	push	ar3
   2269 C0 04               455 	push	ar4
   226B C0 05               456 	push	ar5
   226D 90 20 23            457 	mov	dptr,#0x2023
   2270 12 21 8F            458 	lcall	_SetVector
   2273 15 81               459 	dec	sp
   2275 15 81               460 	dec	sp
   2277 15 81               461 	dec	sp
   2279 D0 02               462 	pop	ar2
                            463 ;	SRC/uart.c:17: TH1       =  speed; //Код скорости
   227B 8A 8D               464 	mov	_TH1,r2
                            465 ;	SRC/uart.c:18: TMOD     |=  0x20; //Таймер 1 будет работать в режиме autoreload
   227D 43 89 20            466 	orl	_TMOD,#0x20
                            467 ;	SRC/uart.c:19: TCON     |=  0x40; //Запуск таймера 1
   2280 43 88 40            468 	orl	_TCON,#0x40
                            469 ;	SRC/uart.c:20: SCON      =  0x50; //Настройки последовательного канала
   2283 75 98 50            470 	mov	_SCON,#0x50
                            471 ;	SRC/uart.c:22: ES=1;
   2286 D2 AC               472 	setb	_ES
   2288 22                  473 	ret
                            474 ;------------------------------------------------------------
                            475 ;Allocation info for local variables in function 'send_byte'
                            476 ;------------------------------------------------------------
                            477 ;dat                       Allocated to registers r2 
                            478 ;------------------------------------------------------------
                            479 ;	SRC/uart.c:25: void send_byte(char dat) {
                            480 ;	-----------------------------------------
                            481 ;	 function send_byte
                            482 ;	-----------------------------------------
   2289                     483 _send_byte:
   2289 AA 82               484 	mov	r2,dpl
                            485 ;	SRC/uart.c:26: ES=0;
   228B C2 AC               486 	clr	_ES
                            487 ;	SRC/uart.c:28: if( !sending_byte ){//начинаем процесс передачи
   228D E5 7C               488 	mov	a,_sending_byte
   228F 70 0B               489 	jnz	00104$
                            490 ;	SRC/uart.c:29: sending_byte=true;
   2291 90 28 FE            491 	mov	dptr,#_true
   2294 E4                  492 	clr	a
   2295 93                  493 	movc	a,@a+dptr
   2296 F5 7C               494 	mov	_sending_byte,a
                            495 ;	SRC/uart.c:30: SBUF=dat;
   2298 8A 99               496 	mov	_SBUF,r2
   229A 80 1E               497 	sjmp	00105$
   229C                     498 00104$:
                            499 ;	SRC/uart.c:31: }else if( !is_buffer_full(&buffer_out) ){
   229C 90 00 4F            500 	mov	dptr,#_buffer_out
   229F 75 F0 40            501 	mov	b,#0x40
   22A2 C0 02               502 	push	ar2
   22A4 12 24 C8            503 	lcall	_is_buffer_full
   22A7 E5 82               504 	mov	a,dpl
   22A9 D0 02               505 	pop	ar2
   22AB 70 0D               506 	jnz	00105$
                            507 ;	SRC/uart.c:32: push_byte_to_buffer(&buffer_out,dat);
   22AD C0 02               508 	push	ar2
   22AF 90 00 4F            509 	mov	dptr,#_buffer_out
   22B2 75 F0 40            510 	mov	b,#0x40
   22B5 12 24 E7            511 	lcall	_push_byte_to_buffer
   22B8 15 81               512 	dec	sp
   22BA                     513 00105$:
                            514 ;	SRC/uart.c:35: ES=1;
   22BA D2 AC               515 	setb	_ES
   22BC 22                  516 	ret
                            517 ;------------------------------------------------------------
                            518 ;Allocation info for local variables in function 'send_string'
                            519 ;------------------------------------------------------------
                            520 ;str                       Allocated to registers r2 r3 r4 
                            521 ;------------------------------------------------------------
                            522 ;	SRC/uart.c:38: void send_string(char * str){
                            523 ;	-----------------------------------------
                            524 ;	 function send_string
                            525 ;	-----------------------------------------
   22BD                     526 _send_string:
   22BD AA 82               527 	mov	r2,dpl
   22BF AB 83               528 	mov	r3,dph
   22C1 AC F0               529 	mov	r4,b
                            530 ;	SRC/uart.c:39: ES=0;
   22C3 C2 AC               531 	clr	_ES
                            532 ;	SRC/uart.c:41: if( !sending_byte ){//начинаем процесс передачи
   22C5 E5 7C               533 	mov	a,_sending_byte
   22C7 70 17               534 	jnz	00112$
                            535 ;	SRC/uart.c:42: sending_byte=true;
   22C9 90 28 FE            536 	mov	dptr,#_true
   22CC E4                  537 	clr	a
   22CD 93                  538 	movc	a,@a+dptr
   22CE F5 7C               539 	mov	_sending_byte,a
                            540 ;	SRC/uart.c:43: SBUF=*str;
   22D0 8A 82               541 	mov	dpl,r2
   22D2 8B 83               542 	mov	dph,r3
   22D4 8C F0               543 	mov	b,r4
   22D6 12 28 DC            544 	lcall	__gptrget
   22D9 F5 99               545 	mov	_SBUF,a
   22DB A3                  546 	inc	dptr
   22DC AA 82               547 	mov	r2,dpl
   22DE AB 83               548 	mov	r3,dph
                            549 ;	SRC/uart.c:44: str++;
                            550 ;	SRC/uart.c:47: while( *str ) {
   22E0                     551 00112$:
   22E0                     552 00105$:
   22E0 8A 82               553 	mov	dpl,r2
   22E2 8B 83               554 	mov	dph,r3
   22E4 8C F0               555 	mov	b,r4
   22E6 12 28 DC            556 	lcall	__gptrget
   22E9 60 43               557 	jz	00107$
                            558 ;	SRC/uart.c:48: if( !is_buffer_full(&buffer_out) ){
   22EB 90 00 4F            559 	mov	dptr,#_buffer_out
   22EE 75 F0 40            560 	mov	b,#0x40
   22F1 C0 02               561 	push	ar2
   22F3 C0 03               562 	push	ar3
   22F5 C0 04               563 	push	ar4
   22F7 12 24 C8            564 	lcall	_is_buffer_full
   22FA E5 82               565 	mov	a,dpl
   22FC D0 04               566 	pop	ar4
   22FE D0 03               567 	pop	ar3
   2300 D0 02               568 	pop	ar2
   2302 70 DC               569 	jnz	00105$
                            570 ;	SRC/uart.c:49: push_byte_to_buffer(&buffer_out,*str);
   2304 8A 82               571 	mov	dpl,r2
   2306 8B 83               572 	mov	dph,r3
   2308 8C F0               573 	mov	b,r4
   230A 12 28 DC            574 	lcall	__gptrget
   230D FD                  575 	mov	r5,a
   230E A3                  576 	inc	dptr
   230F AA 82               577 	mov	r2,dpl
   2311 AB 83               578 	mov	r3,dph
   2313 C0 02               579 	push	ar2
   2315 C0 03               580 	push	ar3
   2317 C0 04               581 	push	ar4
   2319 C0 05               582 	push	ar5
   231B 90 00 4F            583 	mov	dptr,#_buffer_out
   231E 75 F0 40            584 	mov	b,#0x40
   2321 12 24 E7            585 	lcall	_push_byte_to_buffer
   2324 15 81               586 	dec	sp
   2326 D0 04               587 	pop	ar4
   2328 D0 03               588 	pop	ar3
   232A D0 02               589 	pop	ar2
                            590 ;	SRC/uart.c:50: str++;
   232C 80 B2               591 	sjmp	00105$
   232E                     592 00107$:
                            593 ;	SRC/uart.c:54: ES=1;
   232E D2 AC               594 	setb	_ES
   2330 22                  595 	ret
                            596 ;------------------------------------------------------------
                            597 ;Allocation info for local variables in function 'read_byte'
                            598 ;------------------------------------------------------------
                            599 ;dat                       Allocated to registers r2 r3 r4 
                            600 ;is_data                   Allocated to registers r5 
                            601 ;------------------------------------------------------------
                            602 ;	SRC/uart.c:57: bool read_byte(char* dat) {
                            603 ;	-----------------------------------------
                            604 ;	 function read_byte
                            605 ;	-----------------------------------------
   2331                     606 _read_byte:
   2331 AA 82               607 	mov	r2,dpl
   2333 AB 83               608 	mov	r3,dph
   2335 AC F0               609 	mov	r4,b
                            610 ;	SRC/uart.c:60: ES=0;
   2337 C2 AC               611 	clr	_ES
                            612 ;	SRC/uart.c:62: is_data=!is_buffer_empty(&buffer_in);
   2339 90 00 22            613 	mov	dptr,#_buffer_in
   233C 75 F0 40            614 	mov	b,#0x40
   233F C0 02               615 	push	ar2
   2341 C0 03               616 	push	ar3
   2343 C0 04               617 	push	ar4
   2345 12 24 A9            618 	lcall	_is_buffer_empty
   2348 AD 82               619 	mov	r5,dpl
   234A D0 04               620 	pop	ar4
   234C D0 03               621 	pop	ar3
   234E D0 02               622 	pop	ar2
   2350 ED                  623 	mov	a,r5
   2351 B4 01 00            624 	cjne	a,#0x01,00106$
   2354                     625 00106$:
   2354 E4                  626 	clr	a
   2355 33                  627 	rlc	a
                            628 ;	SRC/uart.c:64: if( is_data ){
   2356 FD                  629 	mov	r5,a
   2357 60 25               630 	jz	00102$
                            631 ;	SRC/uart.c:65: *dat=pop_byte_from_buffer(&buffer_in);
   2359 90 00 22            632 	mov	dptr,#_buffer_in
   235C 75 F0 40            633 	mov	b,#0x40
   235F C0 02               634 	push	ar2
   2361 C0 03               635 	push	ar3
   2363 C0 04               636 	push	ar4
   2365 C0 05               637 	push	ar5
   2367 12 25 92            638 	lcall	_pop_byte_from_buffer
   236A AE 82               639 	mov	r6,dpl
   236C D0 05               640 	pop	ar5
   236E D0 04               641 	pop	ar4
   2370 D0 03               642 	pop	ar3
   2372 D0 02               643 	pop	ar2
   2374 8A 82               644 	mov	dpl,r2
   2376 8B 83               645 	mov	dph,r3
   2378 8C F0               646 	mov	b,r4
   237A EE                  647 	mov	a,r6
   237B 12 28 C3            648 	lcall	__gptrput
   237E                     649 00102$:
                            650 ;	SRC/uart.c:68: ES=1;
   237E D2 AC               651 	setb	_ES
                            652 ;	SRC/uart.c:69: return is_data;
   2380 8D 82               653 	mov	dpl,r5
   2382 22                  654 	ret
                            655 ;------------------------------------------------------------
                            656 ;Allocation info for local variables in function 'UART_ISR'
                            657 ;------------------------------------------------------------
                            658 ;dat                       Allocated to registers r2 
                            659 ;------------------------------------------------------------
                            660 ;	SRC/uart.c:72: void UART_ISR( void ) __interrupt ( 4 ) {
                            661 ;	-----------------------------------------
                            662 ;	 function UART_ISR
                            663 ;	-----------------------------------------
   2383                     664 _UART_ISR:
   2383 C0 20               665 	push	bits
   2385 C0 E0               666 	push	acc
   2387 C0 F0               667 	push	b
   2389 C0 82               668 	push	dpl
   238B C0 83               669 	push	dph
   238D C0 02               670 	push	(0+2)
   238F C0 03               671 	push	(0+3)
   2391 C0 04               672 	push	(0+4)
   2393 C0 05               673 	push	(0+5)
   2395 C0 06               674 	push	(0+6)
   2397 C0 07               675 	push	(0+7)
   2399 C0 00               676 	push	(0+0)
   239B C0 01               677 	push	(0+1)
   239D C0 D0               678 	push	psw
   239F 75 D0 00            679 	mov	psw,#0x00
                            680 ;	SRC/uart.c:75: if( TI ){// Передача байта
   23A2 30 99 25            681 	jnb	_TI,00105$
                            682 ;	SRC/uart.c:76: if( is_buffer_empty(&buffer_out) ){
   23A5 90 00 4F            683 	mov	dptr,#_buffer_out
   23A8 75 F0 40            684 	mov	b,#0x40
   23AB 12 24 A9            685 	lcall	_is_buffer_empty
   23AE E5 82               686 	mov	a,dpl
   23B0 60 09               687 	jz	00102$
                            688 ;	SRC/uart.c:77: sending_byte=false;
   23B2 90 28 FF            689 	mov	dptr,#_false
   23B5 E4                  690 	clr	a
   23B6 93                  691 	movc	a,@a+dptr
   23B7 F5 7C               692 	mov	_sending_byte,a
   23B9 80 0D               693 	sjmp	00103$
   23BB                     694 00102$:
                            695 ;	SRC/uart.c:79: dat=pop_byte_from_buffer(&buffer_out);
   23BB 90 00 4F            696 	mov	dptr,#_buffer_out
   23BE 75 F0 40            697 	mov	b,#0x40
   23C1 12 25 92            698 	lcall	_pop_byte_from_buffer
   23C4 AA 82               699 	mov	r2,dpl
                            700 ;	SRC/uart.c:80: SBUF=dat;
   23C6 8A 99               701 	mov	_SBUF,r2
   23C8                     702 00103$:
                            703 ;	SRC/uart.c:83: TI=0;
   23C8 C2 99               704 	clr	_TI
   23CA                     705 00105$:
                            706 ;	SRC/uart.c:86: if( RI ){// Прием байта
                            707 ;	SRC/uart.c:87: RI=0;
   23CA 10 98 02            708 	jbc	_RI,00121$
   23CD 80 2A               709 	sjmp	00112$
   23CF                     710 00121$:
                            711 ;	SRC/uart.c:88: dat=SBUF;
   23CF AB 99               712 	mov	r3,_SBUF
   23D1 8B 02               713 	mov	ar2,r3
                            714 ;	SRC/uart.c:90: if( !is_buffer_full(&buffer_in) ){//Если полон, то теряем байт
   23D3 90 00 22            715 	mov	dptr,#_buffer_in
   23D6 75 F0 40            716 	mov	b,#0x40
   23D9 C0 02               717 	push	ar2
   23DB 12 24 C8            718 	lcall	_is_buffer_full
   23DE E5 82               719 	mov	a,dpl
   23E0 D0 02               720 	pop	ar2
   23E2 70 0D               721 	jnz	00107$
                            722 ;	SRC/uart.c:91: push_byte_to_buffer(&buffer_in,dat);
   23E4 C0 02               723 	push	ar2
   23E6 90 00 22            724 	mov	dptr,#_buffer_in
   23E9 75 F0 40            725 	mov	b,#0x40
   23EC 12 24 E7            726 	lcall	_push_byte_to_buffer
   23EF 15 81               727 	dec	sp
   23F1                     728 00107$:
                            729 ;	SRC/uart.c:94: if( mode==MODE_INT ) {
   23F1 E5 21               730 	mov	a,_MODE_INT
   23F3 B5 0A 03            731 	cjne	a,_mode,00112$
                            732 ;	SRC/uart.c:95: handler_int();
   23F6 12 27 22            733 	lcall	_handler_int
   23F9                     734 00112$:
   23F9 D0 D0               735 	pop	psw
   23FB D0 01               736 	pop	(0+1)
   23FD D0 00               737 	pop	(0+0)
   23FF D0 07               738 	pop	(0+7)
   2401 D0 06               739 	pop	(0+6)
   2403 D0 05               740 	pop	(0+5)
   2405 D0 04               741 	pop	(0+4)
   2407 D0 03               742 	pop	(0+3)
   2409 D0 02               743 	pop	(0+2)
   240B D0 83               744 	pop	dph
   240D D0 82               745 	pop	dpl
   240F D0 F0               746 	pop	b
   2411 D0 E0               747 	pop	acc
   2413 D0 20               748 	pop	bits
   2415 32                  749 	reti
                            750 	.area CSEG    (CODE)
                            751 	.area CONST   (CODE)
   28FE                     752 _true:
   28FE FF                  753 	.db #0xFF
   28FF                     754 _false:
   28FF 00                  755 	.db #0x00
   2900                     756 _MODE_POLL:
   2900 00                  757 	.db #0x00
                            758 	.area XINIT   (CODE)
                            759 	.area CABS    (ABS,CODE)
