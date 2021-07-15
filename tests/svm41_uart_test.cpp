/*
 * THIS FILE IS AUTOMATICALLY GENERATED
 *
 * SHDLC-Generator: 0.8.2
 * Yaml Version: 0.4.0
 * Template Version: 0.7.0-19-g64160bc
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

#include "sensirion_common.h"
#include "sensirion_shdlc.h"
#include "sensirion_test_setup.h"
#include "sensirion_uart_hal.h"
#include "svm41_uart.h"
#include <inttypes.h>
#include <stdio.h>

TEST_GROUP (SVM41_Tests) {
    void setup() {
        int16_t error;
        error = sensirion_uart_hal_init();
        CHECK_EQUAL_ZERO_TEXT(error, "sensirion_uart_hal_init");

        error = svm41_device_reset();
        CHECK_EQUAL_ZERO_TEXT(error, "svm41_device_reset");
    }

    void teardown() {
        int16_t error;

        error = svm41_device_reset();
        CHECK_EQUAL_ZERO_TEXT(error, "svm41_device_reset");

        error = sensirion_uart_hal_free();
        CHECK_EQUAL_ZERO_TEXT(error, "sensirion_uart_hal_free");
    }
};

TEST (SVM41_Tests, SVM41_Test_start_and_stop_measurement) {
    int16_t error;

    error = svm41_start_measurement();
    CHECK_EQUAL_ZERO_TEXT(error, "svm41_start_measurement");

    error = svm41_stop_measurement();
    CHECK_EQUAL_ZERO_TEXT(error, "svm41_stop_measurement");
}

TEST (SVM41_Tests, SVM41_Test_read_measured_values_as_integers) {
    int16_t error;
    int16_t humidity;
    int16_t temperature;
    int16_t voc_index;
    int16_t nox_index;

    error = svm41_start_measurement();
    CHECK_EQUAL_ZERO_TEXT(error, "svm41_start_measurement");

    sensirion_i2c_hal_sleep_usec(1000000);

    error = svm41_read_measured_values_as_integers(&humidity, &temperature,
                                                   &voc_index, &nox_index);
    CHECK_EQUAL_ZERO_TEXT(error, "svm41_read_measured_values_as_integers");
    printf("Humidity: %i\n", humidity);
    printf("Temperature: %i\n", temperature);
    printf("Voc index: %i\n", voc_index);
    printf("Nox index: %i\n", nox_index);

    error = svm41_stop_measurement();
    CHECK_EQUAL_ZERO_TEXT(error, "svm41_stop_measurement");
}

TEST (SVM41_Tests, SVM41_Test_read_measured_raw_values) {
    int16_t error;
    int16_t raw_humidity;
    int16_t raw_temperature;
    uint16_t raw_voc_ticks;
    uint16_t raw_nox_ticks;

    error = svm41_start_measurement();
    CHECK_EQUAL_ZERO_TEXT(error, "svm41_start_measurement");

    sensirion_i2c_hal_sleep_usec(1000000);

    error = svm41_read_measured_raw_values(&raw_humidity, &raw_temperature,
                                           &raw_voc_ticks, &raw_nox_ticks);
    CHECK_EQUAL_ZERO_TEXT(error, "svm41_read_measured_raw_values");
    printf("Raw humidity: %i\n", raw_humidity);
    printf("Raw temperature: %i\n", raw_temperature);
    printf("Raw voc ticks: %u\n", raw_voc_ticks);
    printf("Raw nox ticks: %u\n", raw_nox_ticks);

    error = svm41_stop_measurement();
    CHECK_EQUAL_ZERO_TEXT(error, "svm41_stop_measurement");
}

TEST (SVM41_Tests, SVM41_Test_get_temperature_offset_for_rht_measurements) {
    int16_t error;
    uint8_t t_offset[2];
    uint8_t t_offset_size = 2;
    error = svm41_get_temperature_offset_for_rht_measurements(&t_offset[0],
                                                              t_offset_size);
    CHECK_EQUAL_ZERO_TEXT(error,
                          "svm41_get_temperature_offset_for_rht_measurements");
    printf("T offset: %i\n", t_offset);
}

TEST (SVM41_Tests, SVM41_Test_temperature_offset_for_rht_measurements) {
    int16_t error;
    int16_t expected = 420;
    uint8_t t_offset_buffer[2];
    uint8_t t_offset_size = 2;
    sensirion_common_int16_t_to_bytes(expected, t_offset_buffer);
    error = svm41_set_temperature_offset_for_rht_measurements(
        &t_offset_buffer[0], t_offset_size);
    CHECK_EQUAL_ZERO_TEXT(error,
                          "svm41_set_temperature_offset_for_rht_measurements");

    uint8_t t_offset_actual[2];
    error = svm41_get_temperature_offset_for_rht_measurements(
        &t_offset_actual[0], t_offset_size);
    CHECK_EQUAL_ZERO_TEXT(error,
                          "svm41_get_temperature_offset_for_rht_measurements");
    uint16_t actual = sensirion_common_bytes_to_int16_t(&t_offset_actual[0]);
    CHECK_EQUAL(expected, actual)
}

TEST (SVM41_Tests, SVM41_Test_set_n_get_voc_algorithm_tuning_parameters) {
    int16_t error;
    int16_t exp_voc_index_offset = 101;
    int16_t exp_learning_time_offset_hours = 13;
    int16_t exp_learning_time_gain_hours = 2;
    int16_t exp_gating_max_duration_minutes = 181;
    int16_t exp_std_initial = 51;
    int16_t voc_index_offset = 100;
    int16_t learning_time_offset_hours = 12;
    int16_t learning_time_gain_hours = 100;
    int16_t gating_max_duration_minutes = 180;
    int16_t std_initial = 50;
    error = svm41_set_voc_tuning_parameters(
        exp_voc_index_offset, exp_learning_time_offset_hours,
        exp_learning_time_gain_hours, exp_gating_max_duration_minutes,
        exp_std_initial);
    CHECK_EQUAL_ZERO_TEXT(error, "svm41_set_voc_tuning_parameters");

    sensirion_uart_hal_sleep_usec(10000);

    error = svm41_get_voc_tuning_parameters(
        &voc_index_offset, &learning_time_offset_hours,
        &learning_time_gain_hours, &gating_max_duration_minutes, &std_initial);
    CHECK_EQUAL_ZERO_TEXT(error, "svm41_get_voc_tuning_parameters");
    printf("Voc index offset: %i\n", voc_index_offset);
    printf("Learning time offset hours: %i\n", learning_time_offset_hours);
    printf("Learning time gain hours: %i\n", learning_time_gain_hours);
    printf("Gating max duration minutes: %i\n", gating_max_duration_minutes);
    printf("Std initial: %i\n", std_initial);

    CHECK_TRUE_TEXT(
        voc_index_offset == exp_voc_index_offset,
        "SVM41_Test_set_voc_algorithm_tuning_parameters: voc_index_offset");

    CHECK_TRUE_TEXT(learning_time_offset_hours ==
                        exp_learning_time_offset_hours,
                    "SVM41_Test_set_voc_algorithm_tuning_parameters: "
                    "learning_time_offset_hours");
    CHECK_TRUE_TEXT(learning_time_gain_hours == exp_learning_time_gain_hours,
                    "SVM41_Test_set_voc_algorithm_tuning_parameters: "
                    "learning_time_gain_hours");
    CHECK_TRUE_TEXT(gating_max_duration_minutes ==
                        exp_gating_max_duration_minutes,
                    "SVM41_Test_set_voc_algorithm_tuning_parameters: "
                    "gating_max_duration_minutes");
    CHECK_TRUE_TEXT(
        std_initial == exp_std_initial,
        "SVM41_Test_set_voc_algorithm_tuning_parameters: std_initial");
}

TEST (SVM41_Tests, SVM41_Test_set_n_get_nox_algorithm_tuning_parameters) {
    int16_t error;
    int16_t exp_nox_index_offset = 101;
    int16_t exp_learning_time_offset_hours = 13;
    int16_t exp_learning_time_gain_hours = 2;
    int16_t exp_gating_max_duration_minutes = 181;
    int16_t exp_std_initial = 51;
    int16_t nox_index_offset = 100;
    int16_t learning_time_offset_hours = 12;
    int16_t learning_time_gain_hours = 100;
    int16_t gating_max_duration_minutes = 180;
    int16_t std_initial = 50;
    error = svm41_set_nox_tuning_parameters(
        exp_nox_index_offset, exp_learning_time_offset_hours,
        exp_learning_time_gain_hours, exp_gating_max_duration_minutes,
        exp_std_initial);
    CHECK_EQUAL_ZERO_TEXT(error, "svm41_set_nox_tuning_parameters");

    sensirion_uart_hal_sleep_usec(10000);

    error = svm41_get_nox_tuning_parameters(
        &nox_index_offset, &learning_time_offset_hours,
        &learning_time_gain_hours, &gating_max_duration_minutes, &std_initial);
    CHECK_EQUAL_ZERO_TEXT(error, "svm41_get_nox_tuning_parameters");
    printf("nox index offset: %i\n", nox_index_offset);
    printf("Learning time offset hours: %i\n", learning_time_offset_hours);
    printf("Learning time gain hours: %i\n", learning_time_gain_hours);
    printf("Gating max duration minutes: %i\n", gating_max_duration_minutes);
    printf("Std initial: %i\n", std_initial);

    CHECK_TRUE_TEXT(
        nox_index_offset == exp_nox_index_offset,
        "SVM41_Test_set_nox_algorithm_tuning_parameters: nox_index_offset");

    CHECK_TRUE_TEXT(learning_time_offset_hours ==
                        exp_learning_time_offset_hours,
                    "SVM41_Test_set_nox_algorithm_tuning_parameters: "
                    "learning_time_offset_hours");
    CHECK_TRUE_TEXT(learning_time_gain_hours == exp_learning_time_gain_hours,
                    "SVM41_Test_set_nox_algorithm_tuning_parameters: "
                    "learning_time_gain_hours");
    CHECK_TRUE_TEXT(gating_max_duration_minutes ==
                        exp_gating_max_duration_minutes,
                    "SVM41_Test_set_nox_algorithm_tuning_parameters: "
                    "gating_max_duration_minutes");
    CHECK_TRUE_TEXT(
        std_initial == exp_std_initial,
        "SVM41_Test_set_nox_algorithm_tuning_parameters: std_initial");
}

TEST (SVM41_Tests, SVM41_Test_store_nv_data) {
    int16_t error;
    error = svm41_store_nv_data();
    CHECK_EQUAL_ZERO_TEXT(error, "svm41_store_nv_data");
}

TEST (SVM41_Tests, SVM41_Test_set_voc_algorithm_state) {
    int16_t error;
    uint8_t state[8];
    uint8_t state_size = 8;
    error = svm41_set_voc_state(&state[0], state_size);
    CHECK_EQUAL_ZERO_TEXT(error, "svm41_set_voc_state");
}

TEST (SVM41_Tests, SVM41_Test_set_nox_algorithm_state) {
    int16_t error;
    uint8_t state[8];
    uint8_t state_size = 8;
    error = svm41_set_nox_state(&state[0], state_size);
    CHECK_EQUAL_ZERO_TEXT(error, "svm41_set_nox_state");
}

TEST (SVM41_Tests, SVM41_Test_get_version) {
    int16_t error;
    uint8_t firmware_major;
    uint8_t firmware_minor;
    bool firmware_debug;
    uint8_t hardware_major;
    uint8_t hardware_minor;
    uint8_t protocol_major;
    uint8_t protocol_minor;
    error = svm41_get_version(&firmware_major, &firmware_minor, &firmware_debug,
                              &hardware_major, &hardware_minor, &protocol_major,
                              &protocol_minor);
    CHECK_EQUAL_ZERO_TEXT(error, "svm41_get_version");
    printf("Firmware major: %u\n", firmware_major);
    printf("Firmware minor: %u\n", firmware_minor);
    printf("Firmware debug: %i\n", firmware_debug);
    printf("Hardware major: %u\n", hardware_major);
    printf("Hardware minor: %u\n", hardware_minor);
    printf("Protocol major: %u\n", protocol_major);
    printf("Protocol minor: %u\n", protocol_minor);
}

TEST (SVM41_Tests, SVM41_Test_get_serial_number) {
    int16_t error;
    unsigned char serial_number[32];
    uint8_t serial_number_size = 32;
    error = svm41_get_serial_number(&serial_number[0], serial_number_size);
    CHECK_EQUAL_ZERO_TEXT(error, "svm41_get_serial_number");
    printf("Serial number: %s\n", serial_number);
}

TEST (SVM41_Tests, SVM41_Test_device_reset) {
    int16_t error;
    error = svm41_device_reset();
    CHECK_EQUAL_ZERO_TEXT(error, "svm41_device_reset");
}
