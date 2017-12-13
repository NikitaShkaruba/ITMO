;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 2.9.0 #5416 (Mar 22 2009) (MINGW32)
; This file was generated Wed Nov 22 10:14:02 2017
;--------------------------------------------------------
	.module keyboard
	.optsdcc -mmcs51 --model-small
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _SPEAKER_TIME
	.globl _KEY_REPEAT_DELAY
	.globl _KEY_START_REPEAT_DELAY
	.globl _KEY_COUNT_LIMIT
	.globl _RELEASE_COUNT
	.globl _PRESS_COUNT
	.globl _COLS
	.globl _ROWS
	.globl _false
	.globl _true
	.globl _key_click
	.globl _scan_keyboard
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
	.globl _key_clicks
	.globl _speaker
	.globl _prescaler
	.globl _col
	.globl _key_value
	.globl _key_repeat_time
	.globl _key_pressed_time
	.globl _key_count
	.globl _initialize_keyboard
	.globl _keyboard_read_byte
	.globl _scan_keyboard_int
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
; internal ram data
;--------------------------------------------------------
	.area DSEG    (DATA)
_MODE_INT:
	.ds 1
_key_count::
	.ds 16
_key_pressed_time::
	.ds 16
_key_repeat_time::
	.ds 16
_key_value::
	.ds 17
_col::
	.ds 1
_prescaler::
	.ds 1
_speaker::
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
_key_clicks::
	.ds 67
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
;	SRC/keyboard.c:25: char key_value[]="147*2580369#ABCD";
	mov	_key_value,#0x31
	mov	(_key_value + 0x0001),#0x34
	mov	(_key_value + 0x0002),#0x37
	mov	(_key_value + 0x0003),#0x2A
	mov	(_key_value + 0x0004),#0x32
	mov	(_key_value + 0x0005),#0x35
	mov	(_key_value + 0x0006),#0x38
	mov	(_key_value + 0x0007),#0x30
	mov	(_key_value + 0x0008),#0x33
	mov	(_key_value + 0x0009),#0x36
	mov	(_key_value + 0x000a),#0x39
	mov	(_key_value + 0x000b),#0x23
	mov	(_key_value + 0x000c),#0x41
	mov	(_key_value + 0x000d),#0x42
	mov	(_key_value + 0x000e),#0x43
	mov	(_key_value + 0x000f),#0x44
	mov	(_key_value + 0x0010),#0x00
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
;Allocation info for local variables in function 'initialize_keyboard'
;------------------------------------------------------------
;------------------------------------------------------------
;	SRC/keyboard.c:30: void initialize_keyboard() {
;	-----------------------------------------
;	 function initialize_keyboard
;	-----------------------------------------
_initialize_keyboard:
	ar2 = 0x02
	ar3 = 0x03
	ar4 = 0x04
	ar5 = 0x05
	ar6 = 0x06
	ar7 = 0x07
	ar0 = 0x00
	ar1 = 0x01
;	SRC/keyboard.c:31: initialize_buffer(&key_clicks);
	mov	dptr,#_key_clicks
	mov	b,#0x00
	lcall	_initialize_buffer
;	SRC/keyboard.c:32: col=0;
	mov	_col,#0x00
;	SRC/keyboard.c:33: prescaler=0;
	mov	_prescaler,#0x00
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'keyboard_read_byte'
;------------------------------------------------------------
;dat                       Allocated to registers r2 r3 r4 
;is_data                   Allocated to registers r5 
;------------------------------------------------------------
;	SRC/keyboard.c:36: bool keyboard_read_byte(u8* dat) {
;	-----------------------------------------
;	 function keyboard_read_byte
;	-----------------------------------------
_keyboard_read_byte:
	mov	r2,dpl
	mov	r3,dph
	mov	r4,b
;	SRC/keyboard.c:39: ET2=0;
	clr	_ET2
;	SRC/keyboard.c:41: is_data=!is_buffer_empty(&key_clicks);
	mov	dptr,#_key_clicks
	mov	b,#0x00
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
;	SRC/keyboard.c:43: if( is_data ){
	mov	r5,a
	jz	00102$
;	SRC/keyboard.c:44: *dat=pop_byte_from_buffer(&key_clicks);
	mov	dptr,#_key_clicks
	mov	b,#0x00
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
;	SRC/keyboard.c:47: ET2=1;
	setb	_ET2
;	SRC/keyboard.c:48: return is_data;
	mov	dpl,r5
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'scan_keyboard'
;------------------------------------------------------------
;scan_mask                 Allocated to registers 
;row_mask                  Allocated to registers 
;------------------------------------------------------------
;	SRC/keyboard.c:51: u8 scan_keyboard() {
;	-----------------------------------------
;	 function scan_keyboard
;	-----------------------------------------
_scan_keyboard:
;	SRC/keyboard.c:55: scan_mask=~(1 << col);
	mov	b,_col
	inc	b
	mov	a,#0x01
	sjmp	00105$
00103$:
	add	a,acc
00105$:
	djnz	b,00103$
	cpl	a
	mov	r2,a
;	SRC/keyboard.c:56: write_max(KB, scan_mask);
	push	ar2
	mov	dptr,#0x0000
	lcall	_write_max
	dec	sp
;	SRC/keyboard.c:57: row_mask=~(read_max(KB) & 0xF0)>>4;
	mov	dptr,#0x0000
	lcall	_read_max
	mov	a,dpl
	anl	a,#0xF0
	mov	r3,#0x00
	cpl	a
	mov	r2,a
	mov	a,r3
	cpl	a
	mov	r3,a
	swap	a
	xch	a,r2
	swap	a
	anl	a,#0x0f
	xrl	a,r2
	xch	a,r2
	anl	a,#0x0f
	xch	a,r2
	xrl	a,r2
	xch	a,r2
	jnb	acc.3,00106$
	orl	a,#0xf0
00106$:
	mov	dpl,r2
;	SRC/keyboard.c:59: return row_mask;
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'key_click'
;------------------------------------------------------------
;key                       Allocated to registers r2 
;------------------------------------------------------------
;	SRC/keyboard.c:62: void key_click(u8 key){
;	-----------------------------------------
;	 function key_click
;	-----------------------------------------
_key_click:
	mov	r2,dpl
;	SRC/keyboard.c:63: speaker=1;//включаем спикер
	mov	_speaker,#0x01
;	SRC/keyboard.c:64: enable_speaker();
	push	ar2
	lcall	_enable_speaker
;	SRC/keyboard.c:66: if( !is_buffer_full(&key_clicks) ){
	mov	dptr,#_key_clicks
	mov	b,#0x00
	lcall	_is_buffer_full
	mov	a,dpl
	pop	ar2
	jnz	00103$
;	SRC/keyboard.c:67: push_byte_to_buffer(&key_clicks, key_value[key]);
	mov	a,r2
	add	a,#_key_value
	mov	r0,a
	mov	ar2,@r0
	push	ar2
	mov	dptr,#_key_clicks
	mov	b,#0x00
	lcall	_push_byte_to_buffer
	dec	sp
00103$:
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'scan_keyboard_int'
;------------------------------------------------------------
;row                       Allocated to registers r3 
;row_mask                  Allocated to registers r2 
;key                       Allocated to registers r4 
;------------------------------------------------------------
;	SRC/keyboard.c:71: void scan_keyboard_int(){
;	-----------------------------------------
;	 function scan_keyboard_int
;	-----------------------------------------
_scan_keyboard_int:
;	SRC/keyboard.c:76: prescaler++;
	inc	_prescaler
;	SRC/keyboard.c:77: if( prescaler==2 ){
	mov	a,#0x02
	cjne	a,_prescaler,00152$
	sjmp	00153$
00152$:
	ljmp	00124$
00153$:
;	SRC/keyboard.c:79: prescaler=0;
	mov	_prescaler,#0x00
;	SRC/keyboard.c:81: row_mask=scan_keyboard();
	lcall	_scan_keyboard
	mov	r2,dpl
;	SRC/keyboard.c:83: for( row=0;row<ROWS;row++ ){
	mov	r3,#0x00
00129$:
	mov	dptr,#_ROWS
	clr	a
	movc	a,@a+dptr
	mov	r4,a
	clr	c
	mov	a,r3
	subb	a,r4
	jc	00154$
	ljmp	00132$
00154$:
;	SRC/keyboard.c:84: key=col*ROWS + row;
	mov	b,_col
	mov	a,r4
	mul	ab
	mov	r4,a
	mov	a,r3
	add	a,r4
	mov	r4,a
;	SRC/keyboard.c:86: if( row_mask>>row & 1 ){//клавиша нажата
	mov	b,r3
	inc	b
	mov	a,r2
	sjmp	00156$
00155$:
	clr	c
	rrc	a
00156$:
	djnz	b,00155$
	jnb	acc.0,00112$
;	SRC/keyboard.c:87: if( key_count[key]<KEY_COUNT_LIMIT ) {
	mov	a,r4
	add	a,#_key_count
	mov	r0,a
	mov	ar5,@r0
	mov	dptr,#_KEY_COUNT_LIMIT
	clr	a
	movc	a,@a+dptr
	mov	r6,a
	clr	c
	mov	a,r5
	subb	a,r6
	jnc	00113$
;	SRC/keyboard.c:88: key_count[key]++;
	inc	r5
	mov	@r0,ar5
;	SRC/keyboard.c:90: if( key_count[key]>PRESS_COUNT && key_pressed_time[key]==0 ){//помечаем, как нажатую
	mov	dptr,#_PRESS_COUNT
	clr	a
	movc	a,@a+dptr
	mov	r6,a
	clr	c
	subb	a,r5
	jnc	00113$
	mov	a,r4
	add	a,#_key_pressed_time
	mov	r0,a
	mov	a,@r0
	jnz	00113$
;	SRC/keyboard.c:91: key_click(key);
	mov	dpl,r4
	push	ar2
	push	ar3
	push	ar4
	lcall	_key_click
	pop	ar4
	pop	ar3
	pop	ar2
;	SRC/keyboard.c:92: key_pressed_time[key]=1;
	mov	a,r4
	add	a,#_key_pressed_time
	mov	r0,a
	mov	@r0,#0x01
	sjmp	00113$
00112$:
;	SRC/keyboard.c:96: if( key_count[key]>0 ) {
	mov	a,r4
	add	a,#_key_count
	mov	r0,a
	mov	a,@r0
	mov	r5,a
	jz	00113$
;	SRC/keyboard.c:97: key_count[key]--;
	dec	r5
	mov	@r0,ar5
;	SRC/keyboard.c:99: if( key_count[key]<RELEASE_COUNT && key_pressed_time[key]>0 ){//помечаем как отпущенную
	mov	dptr,#_RELEASE_COUNT
	clr	a
	movc	a,@a+dptr
	mov	r6,a
	clr	c
	mov	a,r5
	subb	a,r6
	jnc	00113$
	mov	a,r4
	add	a,#_key_pressed_time
	mov	r0,a
	mov	a,@r0
	jz	00113$
;	SRC/keyboard.c:100: key_pressed_time[key]=0;
	mov	@r0,#0x00
;	SRC/keyboard.c:101: key_repeat_time[key]=0;
	mov	a,r4
	add	a,#_key_repeat_time
	mov	r0,a
	mov	@r0,#0x00
00113$:
;	SRC/keyboard.c:106: if( key_pressed_time[key]>0 ){//Клавиша помечена как нажатая
	mov	a,r4
	add	a,#_key_pressed_time
	mov	r0,a
	mov	a,@r0
	mov	r5,a
	jz	00131$
;	SRC/keyboard.c:107: if( key_pressed_time[key]<KEY_START_REPEAT_DELAY ){
	mov	dptr,#_KEY_START_REPEAT_DELAY
	clr	a
	movc	a,@a+dptr
	mov	r6,a
	clr	c
	mov	a,r5
	subb	a,r6
	jnc	00117$
;	SRC/keyboard.c:108: key_pressed_time[key]++;
	mov	a,r5
	inc	a
	mov	@r0,a
	sjmp	00131$
00117$:
;	SRC/keyboard.c:110: key_repeat_time[key]++;
	mov	a,r4
	add	a,#_key_repeat_time
	mov	r0,a
	mov	ar5,@r0
	inc	r5
	mov	@r0,ar5
;	SRC/keyboard.c:112: if( key_repeat_time[key]==KEY_REPEAT_DELAY ) {//повторяем каждые KEY_REPEAT_DELAY
	mov	dptr,#_KEY_REPEAT_DELAY
	clr	a
	movc	a,@a+dptr
	mov	r6,a
	mov	a,r5
	cjne	a,ar6,00131$
;	SRC/keyboard.c:113: key_click(key);
	mov	dpl,r4
	push	ar2
	push	ar3
	push	ar4
	lcall	_key_click
	pop	ar4
	pop	ar3
	pop	ar2
;	SRC/keyboard.c:114: key_repeat_time[key]=0;
	mov	a,r4
	add	a,#_key_repeat_time
	mov	r0,a
	mov	@r0,#0x00
00131$:
;	SRC/keyboard.c:83: for( row=0;row<ROWS;row++ ){
	inc	r3
	ljmp	00129$
00132$:
;	SRC/keyboard.c:120: col++;
	inc	_col
;	SRC/keyboard.c:122: if( col==COLS ){
	mov	dptr,#_COLS
	clr	a
	movc	a,@a+dptr
	mov	r2,a
	cjne	a,_col,00124$
;	SRC/keyboard.c:123: col=0;
	mov	_col,#0x00
00124$:
;	SRC/keyboard.c:127: if( speaker>0 ){//Спикер работает
	mov	a,_speaker
	jz	00133$
;	SRC/keyboard.c:128: speaker++;
	inc	_speaker
;	SRC/keyboard.c:130: if(speaker==SPEAKER_TIME){
	mov	dptr,#_SPEAKER_TIME
	clr	a
	movc	a,@a+dptr
	mov	r2,a
	cjne	a,_speaker,00133$
;	SRC/keyboard.c:131: disable_speaker();
	lcall	_disable_speaker
;	SRC/keyboard.c:132: speaker=0;//выключаем спикер
	mov	_speaker,#0x00
00133$:
	ret
	.area CSEG    (CODE)
	.area CONST   (CODE)
_true:
	.db #0xFF
_false:
	.db #0x00
_MODE_TEST:
	.db #0x00
_ROWS:
	.db #0x04
_COLS:
	.db #0x04
_PRESS_COUNT:
	.db #0x08
_RELEASE_COUNT:
	.db #0x03
_KEY_COUNT_LIMIT:
	.db #0x14
_KEY_START_REPEAT_DELAY:
	.db #0x3C
_KEY_REPEAT_DELAY:
	.db #0x64
_SPEAKER_TIME:
	.db #0x64
	.area XINIT   (CODE)
	.area CABS    (ABS,CODE)
