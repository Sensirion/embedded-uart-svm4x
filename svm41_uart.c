/*
 * THIS FILE IS AUTOMATICALLY GENERATED
 *
 * SHDLC-Generator: 0.8.2
 * Yaml Version: 0.8.1
 * Template Version: 0.7.0-84-g1150250
 */
/*
 * Copyright (c) 2021, Sensirion AG
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

#include "svm41_uart.h"
#include "sensirion_common.h"
#include "sensirion_shdlc.h"
#include "sensirion_uart_hal.h"

#define SVM41_UART_ADDRESS 0x00

int16_t svm41_start_measurement(void) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[12];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x00, SVM41_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x00);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    return sensirion_shdlc_rx_inplace(&frame, 0, &header);
}

int16_t svm41_stop_measurement(void) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[12];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x01, SVM41_UART_ADDRESS,
                                0);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    return sensirion_shdlc_rx_inplace(&frame, 0, &header);
}

int16_t svm41_read_measured_values_as_integers(int16_t* humidity,
                                               int16_t* temperature,
                                               int16_t* voc_index,
                                               int16_t* nox_index) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[28];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x03, SVM41_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x10);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 8, &header);
    if (error) {
        return error;
    }
    *humidity = sensirion_common_bytes_to_int16_t(&buffer[0]);
    *temperature = sensirion_common_bytes_to_int16_t(&buffer[2]);
    *voc_index = sensirion_common_bytes_to_int16_t(&buffer[4]);
    *nox_index = sensirion_common_bytes_to_int16_t(&buffer[6]);
    return NO_ERROR;
}

int16_t svm41_read_measured_raw_values(int16_t* raw_humidity,
                                       int16_t* raw_temperature,
                                       uint16_t* raw_voc_ticks,
                                       uint16_t* raw_nox_ticks) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[28];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x03, SVM41_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x0D);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 8, &header);
    if (error) {
        return error;
    }
    *raw_humidity = sensirion_common_bytes_to_int16_t(&buffer[0]);
    *raw_temperature = sensirion_common_bytes_to_int16_t(&buffer[2]);
    *raw_voc_ticks = sensirion_common_bytes_to_uint16_t(&buffer[4]);
    *raw_nox_ticks = sensirion_common_bytes_to_uint16_t(&buffer[6]);
    return NO_ERROR;
}

int16_t svm41_get_temperature_offset_for_rht_measurements(int16_t* t_offset) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[16];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x60, SVM41_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x01);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 2, &header);
    if (error) {
        return error;
    }
    *t_offset = sensirion_common_bytes_to_int16_t(&buffer[0]);
    return NO_ERROR;
}

int16_t svm41_get_voc_tuning_parameters(int16_t* voc_index_offset,
                                        int16_t* learning_time_offset_hours,
                                        int16_t* learning_time_gain_hours,
                                        int16_t* gating_max_duration_minutes,
                                        int16_t* std_initial,
                                        int16_t* gain_factor) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[36];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x60, SVM41_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x0D);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 12, &header);
    if (error) {
        return error;
    }
    *voc_index_offset = sensirion_common_bytes_to_int16_t(&buffer[0]);
    *learning_time_offset_hours = sensirion_common_bytes_to_int16_t(&buffer[2]);
    *learning_time_gain_hours = sensirion_common_bytes_to_int16_t(&buffer[4]);
    *gating_max_duration_minutes =
        sensirion_common_bytes_to_int16_t(&buffer[6]);
    *std_initial = sensirion_common_bytes_to_int16_t(&buffer[8]);
    *gain_factor = sensirion_common_bytes_to_int16_t(&buffer[10]);
    return NO_ERROR;
}

int16_t svm41_get_nox_tuning_parameters(int16_t* nox_index_offset,
                                        int16_t* learning_time_offset_hours,
                                        int16_t* learning_time_gain_hours,
                                        int16_t* gating_max_duration_minutes,
                                        int16_t* std_initial,
                                        int16_t* gain_factor) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[36];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x60, SVM41_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x0E);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 12, &header);
    if (error) {
        return error;
    }
    *nox_index_offset = sensirion_common_bytes_to_int16_t(&buffer[0]);
    *learning_time_offset_hours = sensirion_common_bytes_to_int16_t(&buffer[2]);
    *learning_time_gain_hours = sensirion_common_bytes_to_int16_t(&buffer[4]);
    *gating_max_duration_minutes =
        sensirion_common_bytes_to_int16_t(&buffer[6]);
    *std_initial = sensirion_common_bytes_to_int16_t(&buffer[8]);
    *gain_factor = sensirion_common_bytes_to_int16_t(&buffer[10]);
    return NO_ERROR;
}

int16_t svm41_store_nv_data(void) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[12];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x60, SVM41_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x80);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(500000);

    return sensirion_shdlc_rx_inplace(&frame, 0, &header);
}

int16_t svm41_set_temperature_offset_for_rht_measurements(int16_t t_offset) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[16];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x60, SVM41_UART_ADDRESS,
                                3);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x81);

    sensirion_shdlc_add_int16_t_to_frame(&frame, t_offset);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    return sensirion_shdlc_rx_inplace(&frame, 0, &header);
}

int16_t svm41_set_voc_tuning_parameters(int16_t voc_index_offset,
                                        int16_t learning_time_offset_hours,
                                        int16_t learning_time_gain_hours,
                                        int16_t gating_max_duration_minutes,
                                        int16_t std_initial,
                                        int16_t gain_factor) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[36];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x60, SVM41_UART_ADDRESS,
                                13);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x8D);

    sensirion_shdlc_add_int16_t_to_frame(&frame, voc_index_offset);
    sensirion_shdlc_add_int16_t_to_frame(&frame, learning_time_offset_hours);
    sensirion_shdlc_add_int16_t_to_frame(&frame, learning_time_gain_hours);
    sensirion_shdlc_add_int16_t_to_frame(&frame, gating_max_duration_minutes);
    sensirion_shdlc_add_int16_t_to_frame(&frame, std_initial);
    sensirion_shdlc_add_int16_t_to_frame(&frame, gain_factor);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    return sensirion_shdlc_rx_inplace(&frame, 0, &header);
}

int16_t svm41_set_nox_tuning_parameters(int16_t nox_index_offset,
                                        int16_t learning_time_offset_hours,
                                        int16_t learning_time_gain_hours,
                                        int16_t gating_max_duration_minutes,
                                        int16_t std_initial,
                                        int16_t gain_factor) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[36];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x60, SVM41_UART_ADDRESS,
                                13);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x8E);

    sensirion_shdlc_add_int16_t_to_frame(&frame, nox_index_offset);
    sensirion_shdlc_add_int16_t_to_frame(&frame, learning_time_offset_hours);
    sensirion_shdlc_add_int16_t_to_frame(&frame, learning_time_gain_hours);
    sensirion_shdlc_add_int16_t_to_frame(&frame, gating_max_duration_minutes);
    sensirion_shdlc_add_int16_t_to_frame(&frame, std_initial);
    sensirion_shdlc_add_int16_t_to_frame(&frame, gain_factor);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    if (error) {
        return error;
    }
    return NO_ERROR;
}

int16_t svm41_get_voc_state(uint8_t* state, uint8_t state_size) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[28];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x61, SVM41_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x08);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 8, &header);
    if (error) {
        return error;
    }
    sensirion_common_copy_bytes(&buffer[0], state, state_size);
    return NO_ERROR;
}

int16_t svm41_set_voc_state(const uint8_t* state, uint8_t state_size) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[28];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x61, SVM41_UART_ADDRESS,
                                9);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x88);

    sensirion_shdlc_add_bytes_to_frame(&frame, state, state_size);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    if (error) {
        return error;
    }
    return NO_ERROR;
}

int16_t svm41_get_product_type(unsigned char* product_type,
                               uint8_t product_type_size) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[76];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0xD0, SVM41_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x00);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 32, &header);
    if (error) {
        return error;
    }
    sensirion_common_copy_bytes(&buffer[0], product_type, product_type_size);
    return NO_ERROR;
}

int16_t svm41_get_product_name(unsigned char* product_name,
                               uint8_t product_name_size) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[76];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0xD0, SVM41_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x01);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 32, &header);
    if (error) {
        return error;
    }
    sensirion_common_copy_bytes(&buffer[0], product_name, product_name_size);
    return NO_ERROR;
}

int16_t svm41_get_serial_number(unsigned char* serial_number,
                                uint8_t serial_number_size) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[76];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0xD0, SVM41_UART_ADDRESS,
                                1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0x03);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 32, &header);
    if (error) {
        return error;
    }
    sensirion_common_copy_bytes(&buffer[0], serial_number, serial_number_size);
    return NO_ERROR;
}

int16_t svm41_get_version(uint8_t* firmware_major, uint8_t* firmware_minor,
                          bool* firmware_debug, uint8_t* hardware_major,
                          uint8_t* hardware_minor, uint8_t* protocol_major,
                          uint8_t* protocol_minor) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[26];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0xD1, SVM41_UART_ADDRESS,
                                0);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 7, &header);
    if (error) {
        return error;
    }
    *firmware_major = buffer[0];
    *firmware_minor = buffer[1];
    *firmware_debug = buffer[2];
    *hardware_major = buffer[3];
    *hardware_minor = buffer[4];
    *protocol_major = buffer[5];
    *protocol_minor = buffer[6];
    return NO_ERROR;
}

int16_t svm41_device_reset(void) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[12];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0xD3, SVM41_UART_ADDRESS,
                                0);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    if (error) {
        return error;
    }
    sensirion_uart_hal_sleep_usec(100000);
    return NO_ERROR;
}

int16_t svm41_get_system_up_time(uint32_t* system_up_time) {
    struct sensirion_shdlc_rx_header header;
    uint8_t buffer[20];
    struct sensirion_shdlc_buffer frame;
    sensirion_shdlc_begin_frame(&frame, &buffer[0], 0x93, SVM41_UART_ADDRESS,
                                0);

    sensirion_shdlc_finish_frame(&frame);
    int16_t error = sensirion_shdlc_tx_frame(&frame);
    if (error) {
        return error;
    }

    sensirion_uart_hal_sleep_usec(50000);

    error = sensirion_shdlc_rx_inplace(&frame, 4, &header);
    if (error) {
        return error;
    }
    *system_up_time = sensirion_common_bytes_to_uint32_t(&buffer[0]);
    return NO_ERROR;
}
