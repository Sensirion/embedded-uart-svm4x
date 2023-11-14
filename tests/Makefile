driver_dir := ..

common_sources = ${driver_dir}/sensirion_config.h ${driver_dir}/sensirion_common.h ${driver_dir}/sensirion_common.c
uart_sources = ${driver_dir}/sensirion_uart_hal.h ${driver_dir}/sensirion_shdlc.h ${driver_dir}/sensirion_shdlc.c
sensirion_test_sources = sensirion_test_setup.cpp

uart_impl_src = ${driver_dir}/sample-implementations/linux_user_space/sensirion_uart_hal.c

svm4x_sources = $(driver_dir)/svm4x_uart.h $(driver_dir)/svm4x_uart.c

CXXFLAGS ?= $(CFLAGS) -fsanitize=address -I$(driver_dir)
ifdef CI
	CXXFLAGS += -Werror
endif
LDFLAGS ?= -lasan -lstdc++ -lCppUTest -lCppUTestExt

.PHONY: clean test

all: svm4x_uart_test

svm4x_uart_test: svm4x_uart_test.cpp $(svm4x_sources) $(sensirion_test_sources) $(uart_sources) $(uart_impl_src) $(common_sources)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)


test: svm4x_uart_test
	set -ex; for test in svm4x_uart_test; do echo $${test}; ./$${test}; echo; done;

clean:
	$(RM) svm4x_uart_test
