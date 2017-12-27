# ---------------------------------------------------------------------------
# ��� �������

NAME	= lab2

# ��������� ����������� � �������
# ����� ������ ������� ������ =)
CC      = sdcc.exe
CFLAGS  = -I./INCLUDE -c --stack-auto
LFLAGS  = --code-loc 0x2100 --xram-loc 0x6000 --stack-auto --stack-loc 0x80 

# ��������� ������� �������������� ������ ������

PROJECT  = $(shell type PROJECT)
VERSION  = $(shell type VERSION)
BUILD    = $(shell type BUILD)
TYPE     = $(shell type TYPE)

PROJNAME = ${PROJECT}-${VERSION}-${BUILD}-${TYPE}
TARBALL  = ${PROJNAME}.tar

# ��������� M3P

M3P		 = m3p.exe
COMPORT	 = com1
COMLOG	 = $(COMPORT)_log.txt
BAUD	 = 9600	

# �������� � ��������� ��������

SRC_DIR = SRC
# ---------------------------------------------------------------------------

all: lab2

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



LIST_SRC = \
$(SRC_DIR)/led.c \
$(SRC_DIR)/max.c \
$(SRC_DIR)/common.c \
$(SRC_DIR)/animation.c \
$(SRC_DIR)/mode_selector.c \
$(SRC_DIR)/counter.c \
$(SRC_DIR)/system_timer.c \
$(SRC_DIR)/lab2.c 

LIST_OBJ = $(LIST_SRC:.c=.rel)

lab2 : $(LIST_OBJ) makefile
	$(CC) $(LIST_OBJ) -o lab2.hex $(LFLAGS)
	$(M3P) hb166 lab2.hex lab2.bin bye


$(LIST_OBJ) : %.rel : %.c makefile
	$(CC) -c $(CFLAGS) $< -o $@  

