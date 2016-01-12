
###########################################################
### Directory define
###########################################################
PRODIR = ./


###########################################################
### Cmd line args & Make variables
###########################################################
G = 1
ifeq ($(G),1)
DBGINF = -g
endif

V = 0
ifeq ($(V),1)
PRTINF = -v
endif

INCPATH = -I. -I./sqlite/include
LIBPATH = -L. -L./sqlite/lib
LIBS = -lsgui -lsqlite3 -lpthread

CROSS_COMPILE = arm-none-linux-gnueabi-

CC = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -O2 $(INCPATH) $(DBGINF) $(PRTINF)

LD = $(CROSS_COMPILE)ld
LDFLAGS = $(LIBPATH) $(LIBS)

AR = $(CROSS_COMPILE)ar


###########################################################
### File list
###########################################################
GUISRC = $(wildcard ./gui*.c)
GUIOBJ = $(patsubst ./%.c,./obj/%.o,$(GUISRC))

INPSRC = $(wildcard ./input*.c)
INPOBJ = $(patsubst ./%.c,./obj/%.o,$(INPSRC))

WNDSRC = $(wildcard ./wnd*.c)
WNDOBJ = $(patsubst ./%.c,./obj/%.o,$(WNDSRC))

SRCLST = $(GUISRC) $(INPSRC) $(WNDSRC)
DEPLST = $(patsubst ./%.c,./dep/%.d,$(SRCLST))
OBJLST = $(patsubst ./%.c,./obj/%.o,$(SRCLST))
PRELST = $(patsubst ./%.c,./pre/%.i,$(SRCLST))


###########################################################
### Phony object
###########################################################
.PHONY: all clean distclean

all: sgui wndproc

clean:
	@ echo "Delete object file ..."
	@ if test -e ./libsgui.a; then rm ./libsgui.a; fi
	@ if test -e ./wndproc; then rm ./wndproc; fi
	@ if test -d ./dep; then \
	    if test -n "`ls ./dep`"; then rm ./dep/*; fi; \
	  fi
	@ if test -d ./obj; then \
	    if test -n "`ls ./obj`"; then rm ./obj/*; fi; \
	  fi
	@ if test -d ./pre; then \
	    if test -n "`ls ./pre`"; then rm ./pre/*; fi; \
	  fi
	@ echo "Delete all object file OK!"
	@ echo "Reserved file list: '.o'"
	@ -find . -type f -name "*.o"|xargs echo
	@ echo "Reserved file list: '.i'"
	@ -find . -type f -name "*.i"|xargs echo
	@ echo "Reserved file list: '.d'"
	@ -find . -type f -name "*.d"|xargs echo

distclean:
	@ echo "Clear all build file ..."
	@ if test -e ./libsgui.a; then rm ./libsgui.a; fi
	@ if test -e ./wndproc; then rm ./wndproc; fi
	@ if test -d ./dep; then rm ./dep -rf; fi
	@ if test -d ./obj; then rm ./obj -rf; fi
	@ if test -d ./pre; then rm ./pre -rf; fi


###########################################################
### Create object
###########################################################
# GUI library
sgui: $(GUIOBJ)
	$(AR) -rc libsgui.a $(GUIOBJ)

# Window process
wndproc: sgui $(INPOBJ) $(WNDOBJ)
	$(CC) $(CFLAGS) -o wndproc $(INPOBJ) $(WNDOBJ) $(LDFLAGS)


###########################################################
### For debug
###########################################################
cpre: $(PRELST)


###########################################################
### Rule define
###########################################################
# Build depend
dep/%.d: %.c
	@ if test -d ./dep; then :; else mkdir ./dep; fi
	@ $(CC) -MM $(CFLAGS) $< > $@.tmp
	@ sed 's,\($*\)\.o[:]*,obj/\1.o $@ :,g' < $@.tmp > $@
	@ rm -f $@.tmp

# Comp rule
obj/%.o: %.c
	@ if test -d ./obj; then :; else mkdir ./obj; fi
	$(CC) -c $(CFLAGS) -o $@ $< 

# Pre rule
pre/%.i: %.c
	@ if test -d ./pre; then :; else mkdir ./pre; fi
	$(CC) -E $(CFLAGS) $< -o $@


###########################################################
### Read depend
###########################################################
-include $(DEPLST)

