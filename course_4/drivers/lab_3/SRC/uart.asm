;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 2.9.0 #5416 (Mar 22 2009) (MINGW32)
; This file was generated Wed Nov 08 15:20:25 2017
;--------------------------------------------------------
	.module uart
	.optsdcc -mmcs51 --model-small
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _false
	.globl _true
	.globl _SPR0
	.globl _SPR1
	.globl _CPHA
	.globl _CPOL
	.globl _SPIM
	.globl _SPE
	.globl _WCOL
	.globl _ISPI
	.globl _I2CI
	.globl _I2CTX
	.globl _I2CRS
	.globl _I2CM
	.globl _MDI
	.globl _MCO
	.globl _MDE
	.globl _MDO
	.globl _CS0
	.globl _CS1
	.globl _CS2
	.globl _CS3
	.globl _SCONV
	.globl _CCONV
	.globl _DMA
	.globl _ADCI
	.globl _P
	.globl _F1
	.globl _OV
	.globl _RS0
	.globl _RS1
	.globl _F0
	.globl _AC
	.globl _CY
	.globl _CAP2
	.globl _CNT2
	.globl _TR2
	.globl _XEN
	.globl _TCLK
	.globl _RCLK
	.globl _EXF2
	.globl _TF2
	.globl _WDE
	.globl _WDS
	.globl _WDR2
	.globl _WDR1
	.globl _PRE0
	.globl _PRE1
	.globl _PRE2
	.globl _PX0
	.globl _PT0
	.globl _PX1
	.globl _PT1
	.globl _PS
	.globl _PT2
	.globl _PADC
	.globl _PSI
	.globl _RXD
	.globl _TXD
	.globl _INT0
	.globl _INT1
	.globl _T0
	.globl _T1
	.globl _WR
	.globl _RD
	.globl _EX0
	.globl _ET0
	.globl _EX1
	.globl _ET1
	.globl _ES
	.globl _ET2
	.globl _EADC
	.globl _EA
	.globl _RI
	.globl _TI
	.globl _RB8
	.globl _TB8
	.globl _REN
	.globl _SM2
	.globl _SM1
	.globl _SM0
	.globl _T2
	.globl _T2EX
	.globl _IT0
	.globl _IE0
	.globl _IT1
	.globl _IE1
	.globl _TR0
	.globl _TF0
	.globl _TR1
	.globl _TF1
	.globl _DACCON
	.globl _DAC1H
	.globl _DAC1L
	.globl _DAC0H
	.globl _DAC0L
	.globl _SPICON
	.globl _SPIDAT
	.globl _ADCCON3
	.globl _ADCGAINH
	.globl _ADCGAINL
	.globl _ADCOFSH
	.globl _ADCOFSL
	.globl _B
	.globl _ADCCON1
	.globl _I2CCON
	.globl _ACC
	.globl _PSMCON
	.globl _ADCDATAH
	.globl _ADCDATAL
	.globl _ADCCON2
	.globl _DMAP
	.globl _DMAH
	.globl _DMAL
	.globl _PSW
	.globl _TH2
	.globl _TL2
	.globl _RCAP2H
	.globl _RCAP2L
	.globl _T2CON
	.globl _EADRL
	.globl _WDCON
	.globl _EDATA4
	.globl _EDATA3
	.globl _EDATA2
	.globl _EDATA1
	.globl _ETIM3
	.globl _ETIM2
	.globl _ETIM1
	.globl _ECON
	.globl _IP
	.globl _P3
	.globl _IE2
	.globl _IE
	.globl _P2
	.globl _I2CADD
	.globl _I2CDAT
	.globl _SBUF
	.globl _SCON
	.globl _P1
	.globl _TH1
	.globl _TH0
	.globl _TL1
	.globl _TL0
	.globl _TMOD
	.globl _TCON
	.globl _PCON
	.globl _DPP
	.globl _DPH
	.globl _DPL
	.globl _SP
	.globl _P0
	.globl _sending_byte
	.globl _buffer_out
	.globl _buffer_in
	.globl _initialize_uart
	.globl _send_byte
	.globl _send_string
	.globl _read_byte
	.globl _UART_ISR
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area RSEG    (DATA)
_P0	=	0x0080
_SP	=	0x0081
_DPL	=	0x0082
_DPH	=	0x0083
_DPP	=	0x0084
_PCON	=	0x0087
_TCON	=	0x0088
_TMOD	=	0x0089
_TL0	=	0x008a
_TL1	=	0x008b
_TH0	=	0x008c
_TH1	=	0x008d
_P1	=	0x0090
_SCON	=	0x0098
_SBUF	=	0x0099
_I2CDAT	=	0x009a
_I2CADD	=	0x009b
_P2	=	0x00a0
_IE	=	0x00a8
_IE2	=	0x00a9
_P3	=	0x00b0
_IP	=	0x00b8
_ECON	=	0x00b9
_ETIM1	=	0x00ba
_ETIM2	=	0x00bb
_ETIM3	=	0x00c4
_EDATA1	=	0x00bc
_EDATA2	=	0x00bd
_EDATA3	=	0x00be
_EDATA4	=	0x00bf
_WDCON	=	0x00c0
_EADRL	=	0x00c6
_T2CON	=	0x00c8
_RCAP2L	=	0x00ca
_RCAP2H	=	0x00cb
_TL2	=	0x00cc
_TH2	=	0x00cd
_PSW	=	0x00d0
_DMAL	=	0x00d2
_DMAH	=	0x00d3
_DMAP	=	0x00d4
_ADCCON2	=	0x00d8
_ADCDATAL	=	0x00d9
_ADCDATAH	=	0x00da
_PSMCON	=	0x00df
_ACC	=	0x00e0
_I2CCON	=	0x00e8
_ADCCON1	=	0x00ef
_B	=	0x00f0
_ADCOFSL	=	0x00f1
_ADCOFSH	=	0x00f2
_ADCGAINL	=	0x00f3
_ADCGAINH	=	0x00f4
_ADCCON3	=	0x00f5
_SPIDAT	=	0x00f7
_SPICON	=	0x00f8
_DAC0L	=	0x00f9
_DAC0H	=	0x00fa
_DAC1L	=	0x00fb
_DAC1H	=	0x00fc
_DACCON	=	0x00fd
;--------------------------------------------------------
; special function bits
;--------------------------------------------------------
	.area RSEG    (DATA)
_TF1	=	0x008f
_TR1	=	0x008e
_TF0	=	0x008d
_TR0	=	0x008c
_IE1	=	0x008b
_IT1	=	0x008a
_IE0	=	0x0089
_IT0	=	0x0088
_T2EX	=	0x0091
_T2	=	0x0090
_SM0	=	0x009f
_SM1	=	0x009e
_SM2	=	0x009d
_REN	=	0x009c
_TB8	=	0x009b
_RB8	=	0x009a
_TI	=	0x0099
_RI	=	0x0098
_EA	=	0x00af
_EADC	=	0x00ae
_ET2	=	0x00ad
_ES	=	0x00ac
_ET1	=	0x00ab
_EX1	=	0x00aa
_ET0	=	0x00a9
_EX0	=	0x00a8
_RD	=	0x00b7
_WR	=	0x00b6
_T1	=	0x00b5
_T0	=	0x00b4
_INT1	=	0x00b3
_INT0	=	0x00b2
_TXD	=	0x00b1
_RXD	=	0x00b0
_PSI	=	0x00bf
_PADC	=	0x00be
_PT2	=	0x00bd
_PS	=	0x00bc
_PT1	=	0x00bb
_PX1	=	0x00ba
_PT0	=	0x00b9
_PX0	=	0x00b8
_PRE2	=	0x00c7
_PRE1	=	0x00c6
_PRE0	=	0x00c5
_WDR1	=	0x00c3
_WDR2	=	0x00c2
_WDS	=	0x00c1
_WDE	=	0x00c0
_TF2	=	0x00cf
_EXF2	=	0x00ce
_RCLK	=	0x00cd
_TCLK	=	0x00cc
_XEN	=	0x00cb
_TR2	=	0x00ca
_CNT2	=	0x00c9
_CAP2	=	0x00c8
_CY	=	0x00d7
_AC	=	0x00d6
_F0	=	0x00d5
_RS1	=	0x00d4
_RS0	=	0x00d3
_OV	=	0x00d2
_F1	=	0x00d1
_P	=	0x00d0
_ADCI	=	0x00df
_DMA	=	0x00de
_CCONV	=	0x00dd
_SCONV	=	0x00dc
_CS3	=	0x00db
_CS2	=	0x00da
_CS1	=	0x00d9
_CS0	=	0x00d8
_MDO	=	0x00ef
_MDE	=	0x00ee
_MCO	=	0x00ed
_MDI	=	0x00ec
_I2CM	=	0x00eb
_I2CRS	=	0x00ea
_I2CTX	=	0x00e9
_I2CI	=	0x00e8
_ISPI	=	0x00ff
_WCOL	=	0x00fe
_SPE	=	0x00fd
_SPIM	=	0x00fc
_CPOL	=	0x00fb
_CPHA	=	0x00fa
_SPR1	=	0x00f9
_SPR0	=	0x00f8
;--------------------------------------------------------
; overlayable register banks
;--------------------------------------------------------
	.area REG_BANK_0	(REL,OVR,DATA)
	.ds 8
;--------------------------------------------------------
; overlayable bit register bank
;--------------------------------------------------------
	.area BIT_BANK	(REL,OVR,DATA)
bits:
	.ds 1
	b0 = bits[0]
	b1 = bits[1]
	b2 = bits[2]
	b3 = bits[3]
	b4 = bits[4]
	b5 = bits[5]
	b6 = bits[6]
	b7 = bits[7]
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	.area DSEG    (DATA)
_MODE_INT:
	.ds 1
_buffer_in::
	.ds 45
_buffer_out::
	.ds 45
_sending_byte::
	.ds 1
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
	.area OSEG    (OVR,DATA)
;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	.area ISEG    (DATA)
;--------------------------------------------------------
; absolute internal ram data
;--------------------------------------------------------
	.area IABS    (ABS,DATA)
	.area IABS    (ABS,DATA)
;--------------------------------------------------------
; bit data
;--------------------------------------------------------
	.area BSEG    (BIT)
;--------------------------------------------------------
; paged external ram data
;--------------------------------------------------------
	.area PSEG    (PAG,XDATA)
;--------------------------------------------------------
; external ram data
;--------------------------------------------------------
	.area XSEG    (XDATA)
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area XABS    (ABS,XDATA)
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	.area XISEG   (XDATA)
	.area HOME    (CODE)
	.area GSINIT0 (CODE)
	.area GSINIT1 (CODE)
	.area GSINIT2 (CODE)
	.area GSINIT3 (CODE)
	.area GSINIT4 (CODE)
	.area GSINIT5 (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area CSEG    (CODE)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME    (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area GSINIT  (CODE)
;	./INCLUDE/handler.h:9: static u8 MODE_INT=0xFF;
	mov	_MODE_INT,#0xFF
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME    (CODE)
	.area HOME    (CODE)
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CSEG    (CODE)
;------------------------------------------------------------
;Allocation info for local variables in function 'initialize_uart'
;------------------------------------------------------------
;speed                     Allocated to registers r2 
;------------------------------------------------------------
;	SRC/uart.c:12: void initialize_uart(char speed) {
;	-----------------------------------------
;	 function initialize_uart
;	-----------------------------------------
_initialize_uart:
	ar2 = 0x02
	ar3 = 0x03
	ar4 = 0x04
	ar5 = 0x05
	ar6 = 0x06
	ar7 = 0x07
	ar0 = 0x00
	ar1 = 0x01
	mov	r2,dpl
;	SRC/uart.c:13: initialize_buffer(&buffer_in);
	mov	dptr,#_buffer_in
	mov	b,#0x40
	push	ar2
	lcall	_initialize_buffer
;	SRC/uart.c:14: initialize_buffer(&buffer_out);
	mov	dptr,#_buffer_out
	mov	b,#0x40
	lcall	_initialize_buffer
;	SRC/uart.c:15: SetVector( 0x2023, (void *)UART_ISR );
	mov	r3,#_UART_ISR
	mov	r4,#(_UART_ISR >> 8)
	mov	r5,#0x80
	push	ar3
	push	ar4
	push	ar5
	mov	dptr,#0x2023
	lcall	_SetVector
	dec	sp
	dec	sp
	dec	sp
	pop	ar2
;	SRC/uart.c:17: TH1       =  speed; //Код скорости
	mov	_TH1,r2
;	SRC/uart.c:18: TMOD     |=  0x20; //Таймер 1 будет работать в режиме autoreload
	orl	_TMOD,#0x20
;	SRC/uart.c:19: TCON     |=  0x40; //Запуск таймера 1
	orl	_TCON,#0x40
;	SRC/uart.c:20: SCON      =  0x50; //Настройки последовательного канала
	mov	_SCON,#0x50
;	SRC/uart.c:22: ES=1;
	setb	_ES
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'send_byte'
;------------------------------------------------------------
;dat                       Allocated to registers r2 
;------------------------------------------------------------
;	SRC/uart.c:25: void send_byte(char dat) {
;	-----------------------------------------
;	 function send_byte
;	-----------------------------------------
_send_byte:
	mov	r2,dpl
;	SRC/uart.c:26: ES=0;
	clr	_ES
;	SRC/uart.c:28: if( !sending_byte ){//начинаем процесс передачи
	mov	a,_sending_byte
	jnz	00104$
;	SRC/uart.c:29: sending_byte=true;
	mov	dptr,#_true
	clr	a
	movc	a,@a+dptr
	mov	_sending_byte,a
;	SRC/uart.c:30: SBUF=dat;
	mov	_SBUF,r2
	sjmp	00105$
00104$:
;	SRC/uart.c:31: }else if( !is_buffer_full(&buffer_out) ){
	mov	dptr,#_buffer_out
	mov	b,#0x40
	push	ar2
	lcall	_is_buffer_full
	mov	a,dpl
	pop	ar2
	jnz	00105$
;	SRC/uart.c:32: push_byte_to_buffer(&buffer_out,dat);
	push	ar2
	mov	dptr,#_buffer_out
	mov	b,#0x40
	lcall	_push_byte_to_buffer
	dec	sp
00105$:
;	SRC/uart.c:35: ES=1;
	setb	_ES
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'send_string'
;------------------------------------------------------------
;str                       Allocated to registers r2 r3 r4 
;------------------------------------------------------------
;	SRC/uart.c:38: void send_string(char * str){
;	-----------------------------------------
;	 function send_string
;	-----------------------------------------
_send_string:
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
;	SRC/uart.c:39: ES=0;
	clr	_ES
;	SRC/uart.c:41: if( !sending_byte ){//начинаем процесс передачи
	mov	a,_sending_byte
	jnz	00112$
;	SRC/uart.c:42: sending_byte=true;
	mov	dptr,#_true
	clr	a
	movc	a,@a+dptr
	mov	_sending_byte,a
;	SRC/uart.c:43: SBUF=*str;
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	_SBUF,a
	inc	dptr
	mov	r2,dpl
	mov	r3,dph
;	SRC/uart.c:44: str++;
;	SRC/uart.c:47: while( *str ) {
00112$:
00105$:
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	jz	00107$
;	SRC/uart.c:48: if( !is_buffer_full(&buffer_out) ){
	mov	dptr,#_buffer_out
	mov	b,#0x40
	push	ar2
	push	ar3
	push	ar4
	lcall	_is_buffer_full
	mov	a,dpl
	pop	ar4
	pop	ar3
	pop	ar2
	jnz	00105$
;	SRC/uart.c:49: push_byte_to_buffer(&buffer_out,*str);
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	lcall	__gptrget
	mov	r5,a
	inc	dptr
	mov	r2,dpl
	mov	r3,dph
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	mov	dptr,#_buffer_out
	mov	b,#0x40
	lcall	_push_byte_to_buffer
	dec	sp
	pop	ar4
	pop	ar3
	pop	ar2
;	SRC/uart.c:50: str++;
	sjmp	00105$
00107$:
;	SRC/uart.c:54: ES=1;
	setb	_ES
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'read_byte'
;------------------------------------------------------------
;dat                       Allocated to registers r2 r3 r4 
;is_data                   Allocated to registers r5 
;------------------------------------------------------------
;	SRC/uart.c:57: bool read_byte(char* dat) {
;	-----------------------------------------
;	 function read_byte
;	-----------------------------------------
_read_byte:
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
;	SRC/uart.c:60: ES=0;
	clr	_ES
;	SRC/uart.c:62: is_data=!is_buffer_empty(&buffer_in);
	mov	dptr,#_buffer_in
	mov	b,#0x40
	push	ar2
	push	ar3
	push	ar4
	lcall	_is_buffer_empty
	mov	r5,dpl
	pop	ar4
	pop	ar3
	pop	ar2
	mov	a,r5
	cjne	a,#0x01,00106$
00106$:
	clr	a
	rlc	a
;	SRC/uart.c:64: if( is_data ){
	mov	r5,a
	jz	00102$
;	SRC/uart.c:65: *dat=pop_byte_from_buffer(&buffer_in);
	mov	dptr,#_buffer_in
	mov	b,#0x40
	push	ar2
	push	ar3
	push	ar4
	push	ar5
	lcall	_pop_byte_from_buffer
	mov	r6,dpl
	pop	ar5
	pop	ar4
	pop	ar3
	pop	ar2
	mov	dpl,r2
	mov	dph,r3
	mov	b,r4
	mov	a,r6
	lcall	__gptrput
00102$:
;	SRC/uart.c:68: ES=1;
	setb	_ES
;	SRC/uart.c:69: return is_data;
	mov	dpl,r5
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'UART_ISR'
;------------------------------------------------------------
;dat                       Allocated to registers r2 
;------------------------------------------------------------
;	SRC/uart.c:72: void UART_ISR( void ) __interrupt ( 4 ) {
;	-----------------------------------------
;	 function UART_ISR
;	-----------------------------------------
_UART_ISR:
	push	bits
	push	acc
	push	b
	push	dpl
	push	dph
	push	(0+2)
	push	(0+3)
	push	(0+4)
	push	(0+5)
	push	(0+6)
	push	(0+7)
	push	(0+0)
	push	(0+1)
	push	psw
	mov	psw,#0x00
;	SRC/uart.c:75: if( TI ){// Передача байта
	jnb	_TI,00105$
;	SRC/uart.c:76: if( is_buffer_empty(&buffer_out) ){
	mov	dptr,#_buffer_out
	mov	b,#0x40
	lcall	_is_buffer_empty
	mov	a,dpl
	jz	00102$
;	SRC/uart.c:77: sending_byte=false;
	mov	dptr,#_false
	clr	a
	movc	a,@a+dptr
	mov	_sending_byte,a
	sjmp	00103$
00102$:
;	SRC/uart.c:79: dat=pop_byte_from_buffer(&buffer_out);
	mov	dptr,#_buffer_out
	mov	b,#0x40
	lcall	_pop_byte_from_buffer
	mov	r2,dpl
;	SRC/uart.c:80: SBUF=dat;
	mov	_SBUF,r2
00103$:
;	SRC/uart.c:83: TI=0;
	clr	_TI
00105$:
;	SRC/uart.c:86: if( RI ){// Прием байта
;	SRC/uart.c:87: RI=0;
	jbc	_RI,00121$
	sjmp	00112$
00121$:
;	SRC/uart.c:88: dat=SBUF;
	mov	r3,_SBUF
	mov	ar2,r3
;	SRC/uart.c:90: if( !is_buffer_full(&buffer_in) ){//Если полон, то теряем байт
	mov	dptr,#_buffer_in
	mov	b,#0x40
	push	ar2
	lcall	_is_buffer_full
	mov	a,dpl
	pop	ar2
	jnz	00107$
;	SRC/uart.c:91: push_byte_to_buffer(&buffer_in,dat);
	push	ar2
	mov	dptr,#_buffer_in
	mov	b,#0x40
	lcall	_push_byte_to_buffer
	dec	sp
00107$:
;	SRC/uart.c:94: if( mode==MODE_INT ) {
	mov	a,_MODE_INT
	cjne	a,_mode,00112$
;	SRC/uart.c:95: handler_int();
	lcall	_handler_int
00112$:
	pop	psw
	pop	(0+1)
	pop	(0+0)
	pop	(0+7)
	pop	(0+6)
	pop	(0+5)
	pop	(0+4)
	pop	(0+3)
	pop	(0+2)
	pop	dph
	pop	dpl
	pop	b
	pop	acc
	pop	bits
	reti
	.area CSEG    (CODE)
	.area CONST   (CODE)
_true:
	.db #0xFF
_false:
	.db #0x00
_MODE_POLL:
	.db #0x00
	.area XINIT   (CODE)
	.area CABS    (ABS,CODE)
