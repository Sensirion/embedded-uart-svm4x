common_sources = sensirion_config.h sensirion_common.h sensirion_common.c
uart_sources = sensirion_uart_hal.h sensirion_shdlc.h sensirion_shdlc.c
svm41_sources = svm41_uart.h svm41_uart.c

uart_implementation ?= sensirion_uart_hal.c

CFLAGS = -Os -Wall -fstrict-aliasing -Wstrict-aliasing=1 -Wsign-conversion -fPIC -I.

ifdef CI
    CFLAGS += -Werror
endif

.PHONY: all clean

all: svm41_uart_example_usage

svm41_uart_example_usage: clean
	$(CC) $(CFLAGS) -o $@ ${svm41_sources} ${uart_sources} \
		${uart_implementation} ${common_sources} svm41_uart_example_usage.c

clean:
	$(RM) svm41_uart_example_usage
