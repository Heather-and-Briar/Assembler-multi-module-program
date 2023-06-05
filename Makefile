CFLAGS ?= -O2 -g

CFLAGS += -std=gnu99

CFLAGS += -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self \
	-Wswitch-default -Wpointer-arith -Wtype-limits -Wempty-body \
	-Wstrict-prototypes -Wold-style-declaration -Wold-style-definition \
	-Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs \
	-Wstack-usage=4096 -Wmissing-prototypes -Wfloat-equal -Wabsolute-value

CFLAGS += -fsanitize=undefined -fsanitize-undefined-trap-on-error

CC = gcc

CC += -m32 -no-pie -fno-pie

LDLIBS = -lm

AS = nasm
ASMFLAGS += -g -f elf32

.PHONY: all		#bisectional method
all: integral
	
integral: main.o functions.o root.o calc.o
	$(CC) $(CFLAGS) $^ -lm -o $@

functions.o: functions.asm
	$(AS) $(ASMFLAGS) $< -o $@
	
%.o: %.c functions.h				
	$(CC) $(CFLAGS) -c $< -o $@
	
		
test:
	$ ./integral --test-root 1:2:-3.0:-1.0:0.0001:-2.0
	$ ./integral --test-root 2:3:-1.45:0.5:0.0001:-0.5
	$ ./integral --test-root 1:3:0.0:2.0:0.0001:1.0

	$ ./integral --test-integral 1:-2.0:1.0:0.0001:3.0
	$ ./integral --test-integral 2:-2.0:-0.5:0.0001:7.125
	$ ./integral --test-integral 3:-0.5:1.0:0.0001:4.875

.PHONY: clean
clean:
	-rm -rf *.o
