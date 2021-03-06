CROSS	= arm-hisiv300-linux-
CC	= @echo " GCC	$@"; $(CROSS)gcc
CPP	= @echo " G++	$@"; $(CROSS)g++
LD	= @echo " LD	$@"; $(CROSS)ld
AR	= @echo " AR	$@"; $(CROSS)ar
RM	= @echo " RM	$@"; rm -f
STRIP 	= @echo " STRIP $@"; $(CROSS)strip

LIBDIR = Lib/HI3518EV200
LDFLAGS += -L$(TOPDIR)/Lib -lpthread

TOPDIR = ./

CFLAGS	+= -I$(TOPDIR)Include
CFLAGS	+= -I$(SRCDIR)Include
CFLAGS  += -Wall -O2 -Os 
CFLAGS  += -D_GNU_SOURCE -DLINUX
#CFLAGS  += -fomit-frame-pointer
#CFLAGS  += -Wstrict-prototypes

AFLAGS	+= -rv

EXTLIBS = $(LIBDIR)/libLocalSDK.a	\
		$(LIBDIR)/libInfra.a	\
		$(LIBDIR)/libTPBase.a	\
		$(LIBDIR)/libStreamReader.a
		
		
TEST_OBJS = girrafe.o	

TEST_TARGET = girrafe

TARGET	= $(TEST_TARGET)

all: $(TARGET)
	
$(TEST_TARGET): $(TEST_OBJS) $(EXTLIBS)
	$(CPP) -static -o $@ $^ $(LDFLAGS)
	
.c.o:
	$(CC) -c $(CFLAGS) $^ -o $@

.cpp.o:
	$(CPP) -c $(CFLAGS) $^ -o $@

clean:
	$(RM) $(TARGET) $(LIB_OBJS) $(TEST_OBJS);

