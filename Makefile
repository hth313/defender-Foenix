VPATH = src

FOENIX = module/Calypsi-65816-Foenix

# Common source files
ASM_SRCS = test.s
C_SRCS = foo.c images.c # statemachine.c starship.c signal.c

MODEL = --code-model=large --data-model=medium
LIB_MODEL = lc-md
INCLUDE = -I$(FOENIX)/include

FOENIX_LIB = $(FOENIX)/Foenix-$(LIB_MODEL).a
FOENIX_LINKER_RULES = $(FOENIX)/linker-files/Foenix-U.scm

# Object files
OBJS = $(ASM_SRCS:%.s=obj/%.o) $(C_SRCS:%.c=obj/%.o)
OBJS_DEBUG = $(ASM_SRCS:%.s=obj/%-debug.o) $(C_SRCS:%.c=obj/%-debug.o)

obj/%.o: %.s
	as65816 --core=65816 $(MODEL) --target=Foenix --list-file=$(@:%.o=%.lst) -o $@ $<

obj/%.o: %.c
	cc65816 --core=65816 $(MODEL) $(INCLUDE) --always-inline --target=Foenix --list-file=$(@:%.o=%.lst) -o $@ $<

obj/%-debug.o: %.s
	as65816 --core=65816 $(MODEL) --target=Foenix --debug --list-file=$(@:%.o=%.lst) -o $@ $<

obj/%-debug.o: %.c
	cc65816 --core=65816 $(MODEL) $(INCLUDE) --always-inline --target=Foenix --debug --list-file=$(@:%.o=%.lst) -o $@ $<

defender.elf: $(OBJS_DEBUG) $(FOENIX_LIB)
	ln65816 --debug -o $@ $^ $(FOENIX_LINKER_RULES) clib-$(LIB_MODEL).a --list-file=defender-debug.lst --cross-reference --rtattr printf=reduced --rtattr cstartup=Foenix --semi-hosted --target=Foenix --heap-size=0 --copy-initialize vram

defender.pgz:  $(OBJS) $(FOENIX_LIB)
	ln65816 -o $@ $^ $(FOENIX_LINKER_RULES) clib-$(LIB_MODEL)-Foenix.a --output-format=pgz --list-file=defender-Foenix.lst --cross-reference --rtattr printf=reduced --rtattr cstartup=Foenix --target=Foenix --heap-size=0 --copy-initialize vram

$(FOENIX_LIB):
	(cd $(FOENIX) ; make all)

clean:
	-rm $(OBJS) $(OBJS:%.o=%.lst) $(OBJS_DEBUG) $(OBJS_DEBUG:%.o=%.lst) $(FOENIX_LIB)
	-rm defender.elf defender.pgz defender-debug.lst defender-Foenix.lst
	-(cd $(FOENIX) ; make clean)
