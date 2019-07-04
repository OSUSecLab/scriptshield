SQUIRREL= ..
OUT= sqlib.a
CC = g++ -O2 -fno-exceptions -fno-rtti -fPIC -nostdlib
AR= ar rcu
RANLIB= ranlib
RM= rm -f
OUT= $(SQUIRREL)/bin/sq
INCZ= -I$(SQUIRREL)/include -I. -I$(SQUIRREL)/sqlibs
LIBZ= -L$(SQUIRREL)/lib
LIB= -lsquirrel -lsqstdlib

OBJS= sq.o\
      new_delete.o

SRCS= sq.c \
	 new_delete.c


$(OBJS): 
	$(CC) -U_FORTIFY_SOURCE -c $(SRCS) $(INCZ) $(LIBZ) $(LIB)

$(OUT): $(OBJS)
	$(AR) $@ $(OBJS)
	$(RANLIB) $@

	

#sq32:
	#g++ -O2 -fno-exceptions -fno-rtti -o $(OUT) $(SRCS) $(INCZ) $(LIBZ) $(LIB)
	#g++ -O2 -fno-exceptions -fno-rtti -o $(SRCS) $(INCZ) $(LIBZ) $(LIB)

sqprof:
	g++ -O2 -pg -fno-exceptions -fno-rtti -pie -gstabs -g3 -o $(OUT) $(SRCS) $(INCZ) $(LIBZ) $(LIB)

sq64:
	g++ -O2 -m64 -fno-exceptions -fno-rtti -D_SQ64 -o $(OUT) $(SRCS) $(INCZ) $(LIBZ) $(LIB)


clean:
	$(RM) $(OBJS)
