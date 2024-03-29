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

#include "svm4x_uart.h"
#include "sensirion_common.h"
#include "sensirion_shdlc.h"
#include "sensirion_uart_hal.h"

#define sensirion_hal_sleep_us sensirion_uart_hal_sleep_usec

static uint8_t communication_buffer[76] = {0};

int16_t svm4x_get_product_type(int8_t* product_type,
                               uint16_t product_type_size) {
    struct sensirion_shdlc_rx_header header;
    struct sensirion_shdlc_buffer frame;
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    sensirion_shdlc_begin_frame(&frame, buffer_ptr, 0xd0, SVM4X_SHDLC_ADDR, 1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0);
    sensirion_shdlc_finish_frame(&frame);
    local_error = sensirion_shdlc_tx_frame(&frame);
    if (local_error) {
        return local_error;
    }
    sensirion_uart_hal_sleep_usec(50 * 1000);
    local_error = sensirion_shdlc_rx_inplace(&frame, 32, &header);
    sensirion_common_copy_bytes(&buffer_ptr[0], (uint8_t*)product_type,
                                product_type_size);
    return local_error;
}

int16_t svm4x_get_product_name(int8_t* product_name,
                               uint16_t product_name_size) {
    struct sensirion_shdlc_rx_header header;
    struct sensirion_shdlc_buffer frame;
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    sensirion_shdlc_begin_frame(&frame, buffer_ptr, 0xd0, SVM4X_SHDLC_ADDR, 1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 1);
    sensirion_shdlc_finish_frame(&frame);
    local_error = sensirion_shdlc_tx_frame(&frame);
    if (local_error) {
        return local_error;
    }
    sensirion_uart_hal_sleep_usec(50 * 1000);
    local_error = sensirion_shdlc_rx_inplace(&frame, 8, &header);
    sensirion_common_copy_bytes(&buffer_ptr[0], (uint8_t*)product_name,
                                product_name_size);
    return local_error;
}

int16_t svm4x_get_serial_number(int8_t* serial_number,
                                uint16_t serial_number_size) {
    struct sensirion_shdlc_rx_header header;
    struct sensirion_shdlc_buffer frame;
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    sensirion_shdlc_begin_frame(&frame, buffer_ptr, 0xd0, SVM4X_SHDLC_ADDR, 1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 3);
    sensirion_shdlc_finish_frame(&frame);
    local_error = sensirion_shdlc_tx_frame(&frame);
    if (local_error) {
        return local_error;
    }
    sensirion_uart_hal_sleep_usec(50 * 1000);
    local_error = sensirion_shdlc_rx_inplace(&frame, 32, &header);
    sensirion_common_copy_bytes(&buffer_ptr[0], (uint8_t*)serial_number,
                                serial_number_size);
    return local_error;
}

int16_t svm4x_get_version(uint8_t* firmware_major, uint8_t* firmware_minor,
                          bool* firmware_debug, uint8_t* hardware_major,
                          uint8_t* hardware_minor, uint8_t* protocol_major,
                          uint8_t* protocol_minor) {
    struct sensirion_shdlc_rx_header header;
    struct sensirion_shdlc_buffer frame;
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    sensirion_shdlc_begin_frame(&frame, buffer_ptr, 0xd1, SVM4X_SHDLC_ADDR, 0);
    sensirion_shdlc_finish_frame(&frame);
    local_error = sensirion_shdlc_tx_frame(&frame);
    if (local_error) {
        return local_error;
    }
    sensirion_uart_hal_sleep_usec(50 * 1000);
    local_error = sensirion_shdlc_rx_inplace(&frame, 7, &header);
    *firmware_major = (uint8_t)buffer_ptr[0];
    *firmware_minor = (uint8_t)buffer_ptr[1];
    *firmware_debug = (bool)buffer_ptr[2];
    *hardware_major = (uint8_t)buffer_ptr[3];
    *hardware_minor = (uint8_t)buffer_ptr[4];
    *protocol_major = (uint8_t)buffer_ptr[5];
    *protocol_minor = (uint8_t)buffer_ptr[6];
    return local_error;
}

int16_t svm4x_device_reset() {
    struct sensirion_shdlc_rx_header header;
    struct sensirion_shdlc_buffer frame;
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    sensirion_shdlc_begin_frame(&frame, buffer_ptr, 0xd3, SVM4X_SHDLC_ADDR, 0);
    sensirion_shdlc_finish_frame(&frame);
    local_error = sensirion_shdlc_tx_frame(&frame);
    if (local_error) {
        return local_error;
    }
    sensirion_uart_hal_sleep_usec(50 * 1000);
    local_error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    sensirion_uart_hal_sleep_usec(100 * 1000);
    return local_error;
}

int16_t svm4x_get_system_up_time(uint32_t* system_up_time) {
    struct sensirion_shdlc_rx_header header;
    struct sensirion_shdlc_buffer frame;
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    sensirion_shdlc_begin_frame(&frame, buffer_ptr, 0x93, SVM4X_SHDLC_ADDR, 0);
    sensirion_shdlc_finish_frame(&frame);
    local_error = sensirion_shdlc_tx_frame(&frame);
    if (local_error) {
        return local_error;
    }
    sensirion_uart_hal_sleep_usec(50 * 1000);
    local_error = sensirion_shdlc_rx_inplace(&frame, 4, &header);
    *system_up_time = sensirion_common_bytes_to_uint32_t(&buffer_ptr[0]);
    return local_error;
}

int16_t svm4x_start_measurement() {
    struct sensirion_shdlc_rx_header header;
    struct sensirion_shdlc_buffer frame;
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    sensirion_shdlc_begin_frame(&frame, buffer_ptr, 0x0, SVM4X_SHDLC_ADDR, 1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 0);
    sensirion_shdlc_finish_frame(&frame);
    local_error = sensirion_shdlc_tx_frame(&frame);
    if (local_error) {
        return local_error;
    }
    sensirion_uart_hal_sleep_usec(50 * 1000);
    local_error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    return local_error;
}

int16_t svm4x_stop_measurement() {
    struct sensirion_shdlc_rx_header header;
    struct sensirion_shdlc_buffer frame;
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    sensirion_shdlc_begin_frame(&frame, buffer_ptr, 0x1, SVM4X_SHDLC_ADDR, 0);
    sensirion_shdlc_finish_frame(&frame);
    local_error = sensirion_shdlc_tx_frame(&frame);
    if (local_error) {
        return local_error;
    }
    sensirion_uart_hal_sleep_usec(50 * 1000);
    local_error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    return local_error;
}

int16_t svm4x_read_measured_values_as_integers(int16_t* humidity,
                                               int16_t* temperature,
                                               int16_t* voc_index,
                                               int16_t* nox_index) {
    struct sensirion_shdlc_rx_header header;
    struct sensirion_shdlc_buffer frame;
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    sensirion_shdlc_begin_frame(&frame, buffer_ptr, 0x3, SVM4X_SHDLC_ADDR, 1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 16);
    sensirion_shdlc_finish_frame(&frame);
    local_error = sensirion_shdlc_tx_frame(&frame);
    if (local_error) {
        return local_error;
    }
    sensirion_uart_hal_sleep_usec(50 * 1000);
    local_error = sensirion_shdlc_rx_inplace(&frame, 8, &header);
    *humidity = sensirion_common_bytes_to_int16_t(&buffer_ptr[0]);
    *temperature = sensirion_common_bytes_to_int16_t(&buffer_ptr[2]);
    *voc_index = sensirion_common_bytes_to_int16_t(&buffer_ptr[4]);
    *nox_index = sensirion_common_bytes_to_int16_t(&buffer_ptr[6]);
    return local_error;
}

int16_t svm4x_read_measured_raw_values(int16_t* raw_humidity,
                                       int16_t* raw_temperature,
                                       uint16_t* raw_voc_ticks,
                                       uint16_t* raw_nox_ticks) {
    struct sensirion_shdlc_rx_header header;
    struct sensirion_shdlc_buffer frame;
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    sensirion_shdlc_begin_frame(&frame, buffer_ptr, 0x3, SVM4X_SHDLC_ADDR, 1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 13);
    sensirion_shdlc_finish_frame(&frame);
    local_error = sensirion_shdlc_tx_frame(&frame);
    if (local_error) {
        return local_error;
    }
    sensirion_uart_hal_sleep_usec(50 * 1000);
    local_error = sensirion_shdlc_rx_inplace(&frame, 8, &header);
    *raw_humidity = sensirion_common_bytes_to_int16_t(&buffer_ptr[0]);
    *raw_temperature = sensirion_common_bytes_to_int16_t(&buffer_ptr[2]);
    *raw_voc_ticks = sensirion_common_bytes_to_uint16_t(&buffer_ptr[4]);
    *raw_nox_ticks = sensirion_common_bytes_to_uint16_t(&buffer_ptr[6]);
    return local_error;
}

int16_t svm4x_get_temperature_offset_for_rht_measurements(int16_t* t_offset) {
    struct sensirion_shdlc_rx_header header;
    struct sensirion_shdlc_buffer frame;
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    sensirion_shdlc_begin_frame(&frame, buffer_ptr, 0x60, SVM4X_SHDLC_ADDR, 1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 1);
    sensirion_shdlc_finish_frame(&frame);
    local_error = sensirion_shdlc_tx_frame(&frame);
    if (local_error) {
        return local_error;
    }
    sensirion_uart_hal_sleep_usec(50 * 1000);
    local_error = sensirion_shdlc_rx_inplace(&frame, 2, &header);
    *t_offset = sensirion_common_bytes_to_int16_t(&buffer_ptr[0]);
    return local_error;
}

int16_t svm4x_get_voc_tuning_parameters(int16_t* voc_index_offset,
                                        int16_t* learning_time_offset_hours,
                                        int16_t* learning_time_gain_hours,
                                        int16_t* gating_max_duration_minutes,
                                        int16_t* std_initial,
                                        int16_t* gain_factor) {
    struct sensirion_shdlc_rx_header header;
    struct sensirion_shdlc_buffer frame;
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    sensirion_shdlc_begin_frame(&frame, buffer_ptr, 0x60, SVM4X_SHDLC_ADDR, 1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 13);
    sensirion_shdlc_finish_frame(&frame);
    local_error = sensirion_shdlc_tx_frame(&frame);
    if (local_error) {
        return local_error;
    }
    sensirion_uart_hal_sleep_usec(50 * 1000);
    local_error = sensirion_shdlc_rx_inplace(&frame, 12, &header);
    *voc_index_offset = sensirion_common_bytes_to_int16_t(&buffer_ptr[0]);
    *learning_time_offset_hours =
        sensirion_common_bytes_to_int16_t(&buffer_ptr[2]);
    *learning_time_gain_hours =
        sensirion_common_bytes_to_int16_t(&buffer_ptr[4]);
    *gating_max_duration_minutes =
        sensirion_common_bytes_to_int16_t(&buffer_ptr[6]);
    *std_initial = sensirion_common_bytes_to_int16_t(&buffer_ptr[8]);
    *gain_factor = sensirion_common_bytes_to_int16_t(&buffer_ptr[10]);
    return local_error;
}

int16_t svm4x_get_nox_tuning_parameters(int16_t* nox_index_offset,
                                        int16_t* learning_time_offset_hours,
                                        int16_t* learning_time_gain_hours,
                                        int16_t* gating_max_duration_minutes,
                                        int16_t* std_initial,
                                        int16_t* gain_factor) {
    struct sensirion_shdlc_rx_header header;
    struct sensirion_shdlc_buffer frame;
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    sensirion_shdlc_begin_frame(&frame, buffer_ptr, 0x60, SVM4X_SHDLC_ADDR, 1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 14);
    sensirion_shdlc_finish_frame(&frame);
    local_error = sensirion_shdlc_tx_frame(&frame);
    if (local_error) {
        return local_error;
    }
    sensirion_uart_hal_sleep_usec(50 * 1000);
    local_error = sensirion_shdlc_rx_inplace(&frame, 12, &header);
    *nox_index_offset = sensirion_common_bytes_to_int16_t(&buffer_ptr[0]);
    *learning_time_offset_hours =
        sensirion_common_bytes_to_int16_t(&buffer_ptr[2]);
    *learning_time_gain_hours =
        sensirion_common_bytes_to_int16_t(&buffer_ptr[4]);
    *gating_max_duration_minutes =
        sensirion_common_bytes_to_int16_t(&buffer_ptr[6]);
    *std_initial = sensirion_common_bytes_to_int16_t(&buffer_ptr[8]);
    *gain_factor = sensirion_common_bytes_to_int16_t(&buffer_ptr[10]);
    return local_error;
}

int16_t svm4x_store_nv_data() {
    struct sensirion_shdlc_rx_header header;
    struct sensirion_shdlc_buffer frame;
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    sensirion_shdlc_begin_frame(&frame, buffer_ptr, 0x60, SVM4X_SHDLC_ADDR, 1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 128);
    sensirion_shdlc_finish_frame(&frame);
    local_error = sensirion_shdlc_tx_frame(&frame);
    if (local_error) {
        return local_error;
    }
    sensirion_uart_hal_sleep_usec(50 * 1000);
    local_error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    return local_error;
}

int16_t svm4x_set_temperature_offset_for_rht_measurements(int16_t t_offset) {
    struct sensirion_shdlc_rx_header header;
    struct sensirion_shdlc_buffer frame;
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    sensirion_shdlc_begin_frame(&frame, buffer_ptr, 0x60, SVM4X_SHDLC_ADDR, 3);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 129);
    sensirion_shdlc_add_int16_t_to_frame(&frame, t_offset);
    sensirion_shdlc_finish_frame(&frame);
    local_error = sensirion_shdlc_tx_frame(&frame);
    if (local_error) {
        return local_error;
    }
    sensirion_uart_hal_sleep_usec(50 * 1000);
    local_error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    return local_error;
}

int16_t svm4x_set_voc_tuning_parameters(int16_t voc_index_offset,
                                        int16_t learning_time_offset_hours,
                                        int16_t learning_time_gain_hours,
                                        int16_t gating_max_duration_minutes,
                                        int16_t std_initial,
                                        int16_t gain_factor) {
    struct sensirion_shdlc_rx_header header;
    struct sensirion_shdlc_buffer frame;
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    sensirion_shdlc_begin_frame(&frame, buffer_ptr, 0x60, SVM4X_SHDLC_ADDR, 13);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 141);
    sensirion_shdlc_add_int16_t_to_frame(&frame, voc_index_offset);
    sensirion_shdlc_add_int16_t_to_frame(&frame, learning_time_offset_hours);
    sensirion_shdlc_add_int16_t_to_frame(&frame, learning_time_gain_hours);
    sensirion_shdlc_add_int16_t_to_frame(&frame, gating_max_duration_minutes);
    sensirion_shdlc_add_int16_t_to_frame(&frame, std_initial);
    sensirion_shdlc_add_int16_t_to_frame(&frame, gain_factor);
    sensirion_shdlc_finish_frame(&frame);
    local_error = sensirion_shdlc_tx_frame(&frame);
    if (local_error) {
        return local_error;
    }
    sensirion_uart_hal_sleep_usec(50 * 1000);
    local_error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    return local_error;
}

int16_t svm4x_set_nox_tuning_parameters(int16_t nox_index_offset,
                                        int16_t learning_time_offset_hours,
                                        int16_t learning_time_gain_hours,
                                        int16_t gating_max_duration_minutes,
                                        int16_t std_initial,
                                        int16_t gain_factor) {
    struct sensirion_shdlc_rx_header header;
    struct sensirion_shdlc_buffer frame;
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    sensirion_shdlc_begin_frame(&frame, buffer_ptr, 0x60, SVM4X_SHDLC_ADDR, 13);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 142);
    sensirion_shdlc_add_int16_t_to_frame(&frame, nox_index_offset);
    sensirion_shdlc_add_int16_t_to_frame(&frame, learning_time_offset_hours);
    sensirion_shdlc_add_int16_t_to_frame(&frame, learning_time_gain_hours);
    sensirion_shdlc_add_int16_t_to_frame(&frame, gating_max_duration_minutes);
    sensirion_shdlc_add_int16_t_to_frame(&frame, std_initial);
    sensirion_shdlc_add_int16_t_to_frame(&frame, gain_factor);
    sensirion_shdlc_finish_frame(&frame);
    local_error = sensirion_shdlc_tx_frame(&frame);
    if (local_error) {
        return local_error;
    }
    sensirion_uart_hal_sleep_usec(50 * 1000);
    local_error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    return local_error;
}

int16_t svm4x_get_voc_state(uint8_t* state, uint16_t state_size) {
    struct sensirion_shdlc_rx_header header;
    struct sensirion_shdlc_buffer frame;
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    sensirion_shdlc_begin_frame(&frame, buffer_ptr, 0x61, SVM4X_SHDLC_ADDR, 1);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 8);
    sensirion_shdlc_finish_frame(&frame);
    local_error = sensirion_shdlc_tx_frame(&frame);
    if (local_error) {
        return local_error;
    }
    sensirion_uart_hal_sleep_usec(50 * 1000);
    local_error = sensirion_shdlc_rx_inplace(&frame, 8, &header);
    sensirion_common_copy_bytes(&buffer_ptr[0], (uint8_t*)state, state_size);
    return local_error;
}

int16_t svm4x_set_voc_state(const uint8_t* state, uint16_t state_size) {
    struct sensirion_shdlc_rx_header header;
    struct sensirion_shdlc_buffer frame;
    int16_t local_error = NO_ERROR;
    uint8_t* buffer_ptr = communication_buffer;
    sensirion_shdlc_begin_frame(&frame, buffer_ptr, 0x61, SVM4X_SHDLC_ADDR, 9);
    sensirion_shdlc_add_uint8_t_to_frame(&frame, 136);
    sensirion_shdlc_add_bytes_to_frame(&frame, (uint8_t*)state, state_size);

    sensirion_shdlc_finish_frame(&frame);
    local_error = sensirion_shdlc_tx_frame(&frame);
    if (local_error) {
        return local_error;
    }
    sensirion_uart_hal_sleep_usec(50 * 1000);
    local_error = sensirion_shdlc_rx_inplace(&frame, 0, &header);
    return local_error;
}
