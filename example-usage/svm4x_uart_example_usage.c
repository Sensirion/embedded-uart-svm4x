/*
 * THIS FILE IS AUTOMATICALLY GENERATED
 *
 * Generator:     sensirion-driver-generator 0.33.0
 * Product:       svm4x
 * Model-Version: 2.0.2
 */
/*
 * Copyright (c) 2023, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include "sensirion_common.h"
#include "sensirion_uart_hal.h"
#include "svm4x_uart.h"
#include <stdio.h>  // printf

#define sensirion_hal_sleep_us sensirion_uart_hal_sleep_usec

int main(void) {
    int16_t error = NO_ERROR;

    // for non linux systems modify the header file sensirion_uart_descriptor.h
    // SERIAL_0 defaults to "/dev/ttyUSB0" for linux user space implementation
    sensirion_uart_hal_init(SERIAL_0);

    error = svm4x_device_reset();
    if (error != NO_ERROR) {
        printf("error executing device_reset(): %i\n", error);
        return error;
    }
    sensirion_hal_sleep_us(2000000);
    int8_t serial_number[32] = {0};
    error = svm4x_get_serial_number(serial_number, 32);
    if (error != NO_ERROR) {
        printf("error executing get_serial_number(): %i\n", error);
        return error;
    }
    printf("serial_number: %s\n", serial_number);
    int8_t product_type[32] = {0};
    error = svm4x_get_product_type(product_type, 32);
    if (error != NO_ERROR) {
        printf("error executing get_product_type(): %i\n", error);
        return error;
    }
    printf("product_type: %s\n", product_type);
    int8_t product_name[8] = {0};
    error = svm4x_get_product_name(product_name, 8);
    if (error != NO_ERROR) {
        printf("error executing get_product_name(): %i\n", error);
        return error;
    }
    printf("product_name: %s\n", product_name);
    uint8_t firmware_major = 0;
    uint8_t firmware_minor = 0;
    bool firmware_debug = false;
    uint8_t hardware_major = 0;
    uint8_t hardware_minor = 0;
    uint8_t protocol_major = 0;
    uint8_t protocol_minor = 0;
    error = svm4x_get_version(&firmware_major, &firmware_minor, &firmware_debug,
                              &hardware_major, &hardware_minor, &protocol_major,
                              &protocol_minor);
    if (error != NO_ERROR) {
        printf("error executing get_version(): %i\n", error);
        return error;
    }
    printf("firmware_major: %u ", firmware_major);
    printf("firmware_minor: %u ", firmware_minor);
    printf("firmware_debug: %d ", firmware_debug);
    printf("hardware_major: %u ", hardware_major);
    printf("hardware_minor: %u ", hardware_minor);
    printf("protocol_major: %u ", protocol_major);
    printf("protocol_minor: %u\n", protocol_minor);

    int16_t t_offset = 0;
    error = svm4x_get_temperature_offset_for_rht_measurements(&t_offset);
    if (error != NO_ERROR) {
        printf("error executing get_temperature_offset_for_rht_measurements(): "
               "%i\n",
               error);
        return error;
    }
    printf("t_offset [degC with scaling factor 200]: %i\n", t_offset);
    error = svm4x_set_temperature_offset_for_rht_measurements(0);
    if (error != NO_ERROR) {
        printf("error executing set_temperature_offset_for_rht_measurements(): "
               "%i\n",
               error);
        return error;
    }
    error = svm4x_start_measurement();
    if (error != NO_ERROR) {
        printf("error executing start_measurement(): %i\n", error);
        return error;
    }
    int16_t humidity = 0;
    int16_t temperature = 0;
    int16_t voc_index = 0;
    int16_t nox_index = 0;
    uint16_t repetition = 0;
    for (repetition = 0; repetition < 100; repetition++) {
        sensirion_hal_sleep_us(1000000);
        error = svm4x_read_measured_values_as_integers(&humidity, &temperature,
                                                       &voc_index, &nox_index);
        if (error != NO_ERROR) {
            printf("error executing read_measured_values_as_integers(): %i\n",
                   error);
            continue;
        }
        printf("humidity [RH with scaling 100]: %i ", humidity);
        printf("temperature [°C with scaling 200]: %i ", temperature);
        printf("voc_index (with scaling 10): %i ", voc_index);
        printf("nox_index (with scaling 10): %i\n", nox_index);
    }

    error = svm4x_stop_measurement();
    if (error != NO_ERROR) {
        return error;
    }
    return NO_ERROR;
}
