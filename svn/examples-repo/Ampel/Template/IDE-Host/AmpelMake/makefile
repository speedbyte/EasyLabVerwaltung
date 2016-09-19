################################################################################
# This is my manually created makefile for Ampel, not the one form Eclipse
################################################################################


RM := rm -rf

INCDIR="../../Application"
CFLAGS=-I$(INCDIR) -O0 -g3 -Wall   
ODIR=obj
APPDIR=../../Application
HALDIR=../../HAL-Host

_DEPS = buttonh.h button.h button.h ticker.h hal.h led.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJS = ampel.o \
buttonh.o \
states.o \
button.o \
ticker.o \
hal.o  led.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

# All Target
all: Ampel

# Tool invocations
Ampel: $(OBJS) 
	@echo 'Building target: $@'
	@echo 'Invoking: C Linker'
	gcc  -o "Ampel.exe" $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(EXECUTABLES) Ampel
	-@echo ' '

$(ODIR)/ampel.o: $(APPDIR)/ampel.c
	gcc $(CFLAGS) -c -o "$@" "$<"

$(ODIR)/buttonh.o: $(APPDIR)/buttonh.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc $(CFLAGS) -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(ODIR)/states.o: $(APPDIR)/states.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc $(CFLAGS) -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(ODIR)/button.o: $(HALDIR)/button.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc $(CFLAGS) -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(ODIR)/ticker.o: $(HALDIR)/ticker.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc $(CFLAGS) -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(ODIR)/hal.o: $(HALDIR)/hal.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc $(CFLAGS) -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(ODIR)/led.o: $(HALDIR)/led.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc $(CFLAGS) -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

.PHONY: clean

