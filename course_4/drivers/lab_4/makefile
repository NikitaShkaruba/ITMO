# ---------------------------------------------------------------------------
# Имя проекта

NAME	= lab4

# Настройки компилятора и линкера

CC      = C:\\Program\ Files\ \(x86\)\\SDCC\\bin\\sdcc.exe
CFLAGS  = -I./INCLUDE -c --stack-auto
LFLAGS  = --code-loc 0x2100 --xram-loc 0x6000 --stack-auto --stack-loc 0x80 

# Настройки системы автоинкремента версии сборки

PROJECT  = $(shell type PROJECT)
VERSION  = $(shell type VERSION)
BUILD    = $(shell type BUILD)
TYPE     = $(shell type TYPE)

PROJNAME = ${PROJECT}-${VERSION}-${BUILD}-${TYPE}
TARBALL  = ${PROJNAME}.tar

# Настройки M3P

M3P		 = m3p
COMPORT	 = com2
COMLOG	 = $(COMPORT)_log.txt
BAUD	 = 9600	

# Каталоги с исходными текстами

SRC_DIR = SRC
# ---------------------------------------------------------------------------

all: lab4

clean:
	del $(NAME).hex
	del $(NAME).bin
	del $(NAME).map
	del $(NAME).mem
	del $(NAME).lnk
	del pm3p_*.txt
	del com?_log.txt
	del $(TARBALL).gz
	del $(SRC_DIR)\*.asm
	del $(SRC_DIR)\*.rel
	del $(SRC_DIR)\*.rst
	del $(SRC_DIR)\*.sym
	del $(SRC_DIR)\*.lst 

load:
	$(M3P) lfile load.m3p


dist:
	tar -cvf $(TARBALL) --exclude=*.tar .
	gzip $(TARBALL)

term:
	$(M3P) echo $(COMLOG) $(BAUD)  openchannel $(COMPORT) +echo 6 term -echo bye


TEST_SERIAL_SRC = \
$(SRC_DIR)/led.c \
$(SRC_DIR)/max.c \
$(SRC_DIR)/common.c \
$(SRC_DIR)/system_timer.c \
$(SRC_DIR)/uart.c \
$(SRC_DIR)/buffer.c \
$(SRC_DIR)/handler.c \
$(SRC_DIR)/keyboard.c \
$(SRC_DIR)/speaker.c \
$(SRC_DIR)/lab4.c 

TEST_SERIAL_OBJ = $(TEST_SERIAL_SRC:.c=.rel)

lab4 : $(TEST_SERIAL_OBJ) makefile
	$(CC) $(TEST_SERIAL_OBJ) -o lab4.hex $(LFLAGS)
	$(M3P) hb166 lab4.hex lab4.bin bye


$(TEST_SERIAL_OBJ) : %.rel : %.c makefile
	$(CC) -c $(CFLAGS) $< -o $@  
