EXTRA_CFLAGS ?= --coverage
EXTRA_LDFLAGS ?= -coverage -lgcov

LDFLAGS = $(EXTRA_LDFLAGS)
CFLAGS = $(CROSSFLAGS) -Wall -Wextra -g -I./inc $(EXTRA_CFLAGS)


CXXFLAGS = $(CFLAGS)

TARGET = wavecat
GLUE := ../glue.ino

AR=ar
AS=as
CC=gcc
LD=gcc
CXX=g++
OBJDUMP=objdump
OBJCOPY=objcopy

PROJDIRS := inc src
SRCFILES := $(shell find -L $(PROJDIRS) -type f -name \*.c) test/main.c
HDRFILES := $(shell find -L $(PROJDIRS) -type f -name \*.h)
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES))
DEPFILES := $(patsubst %.c,%.d,$(SRCFILES) $(CPPFILES))
ALLFILES := $(SRCFILES) $(HDRFILES)

.PHONY: all bin clean cov covhtml tags ino

all: $(TARGET) $(GLUE)

cov:
	mkdir -p cov
	find . -iname "*.c" -o -iname "*.cpp" -o -iname "*.s" | xargs gcov
	mv *.gcov cov/

covhtml: cov
	lcov --capture --directory . --output-file cov/coverage.info
	genhtml cov/coverage.info --output-directory cov/

-include $(DEPFILES)

%.o: %.c Makefile
	@echo $(CC) $<
	@$(CROSS)$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(TARGET) : $(OBJFILES)
	$(LD) $(LDFLAGS) -o $(TARGET) $(LINKFILE) $(OBJFILES)

sine : test/sine.c
	gcc ./test/sine.c -lm -o sine 

clean:
	@rm -f *.bin *.elf *.list autogen/*.auto TAGS $(TARGET) sine
	@rm -rf cov/
	@rm -f $(OBJFILES)
	@rm -f $(DEPFILES)
	@find . -iname "*.gcda" -o -iname "*.gcno" -o -iname "*.gcov" | xargs --no-run-if-empty rm -f

tags:
	ctags -e -R .

$(GLUE): Makefile
	@echo "#include \"$(shell pwd)/inc/wc.h\"" > $@
	@echo "#include \"$(shell pwd)/inc/wc_compress.h\"" >> $@
	@echo "#include \"$(shell pwd)/inc/wc_sinetables.h\"" >> $@
	@echo "#include \"$(shell pwd)/inc/wc_basicwave.h\"" >> $@
	@echo "#include \"$(shell pwd)/inc/wc_morphwave.h\"" >> $@
	@echo "#include \"$(shell pwd)/inc/wc_crossfade.h\"" >> $@
	@echo "#include \"$(shell pwd)/inc/wc_resonance.h\"" >> $@
	@echo "#include \"$(shell pwd)/inc/wc_fold.h\"" >> $@
	@echo "#include \"$(shell pwd)/inc/wc_fm.h\"" >> $@
	@echo "#include \"$(shell pwd)/inc/wc_amp.h\"" >> $@
	@echo "#include \"$(shell pwd)/inc/wc_winres.h\"" >> $@
	@echo "#include \"$(shell pwd)/inc/wc_vosim.h\"" >> $@
	@echo "#include \"$(shell pwd)/inc/wc_main.h\"" >> $@
	@echo "#include \"$(shell pwd)/src/wc_main.c\"" >> $@
	@echo "#include \"$(shell pwd)/src/wc_fm.c\"" >> $@
	@echo "#include \"$(shell pwd)/src/wc_basicwave.c\"" >> $@
	@echo "#include \"$(shell pwd)/src/wc_sinetables.c\"" >> $@
	@echo "#include \"$(shell pwd)/src/wc_morphwave.c\"" >> $@
	@echo "#include \"$(shell pwd)/src/wc_resonance.c\"" >> $@
	@echo "#include \"$(shell pwd)/src/wc_fold.c\"" >> $@
	@echo "#include \"$(shell pwd)/src/wc_winres.c\"" >> $@
	@echo "#include \"$(shell pwd)/src/wc_vosim.c\"" >> $@
	@echo "#include \"$(shell pwd)/src/wc_amp.c\"" >> $@
	@echo "#include \"$(shell pwd)/src/wc_compress.c\"" >> $@

