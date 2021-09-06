// ======================================
// == Classification: TII UNCLASSIFIED ==
// ======================================

#include <stdio.h>
#include <string.h>
#include <ctime>
#include <cstdint>
extern "C" {
}
#include "../tests/sd_estimator/test_sd_estimator.h"

uint64_t rdtsc(){
    unsigned int lo,hi;
   __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
   return ((uint64_t)hi << 32u) | lo;
}


void pretty_print_benchmark(const char* measured_function, clock_t total_time, uint64_t total_iterations, uint64_t total_cycles){
   double total_time_in_seconds = (double) total_time /
   (double) CLOCKS_PER_SEC;
   double operations_per_second = (double) total_iterations * (double) CLOCKS_PER_SEC/ (double) total_time;
   double cycles_per_op = (double) total_cycles/ (double) total_iterations;
   printf("\r%60s:  %12.2f cycles/op, (%3.2f s, %4.3e ops, %4.3e cycles, %3.2f op/s, %4.3f GHz)\n", measured_function,
       cycles_per_op, total_time_in_seconds, (double) total_iterations, (double) total_cycles, operations_per_second, cycles_per_op*operations_per_second/1000000000.);
}


static void print_test_result(int result) {
    if (result == 0) {
        printf("PASS\n");
    } else {
        printf("*** FAILED ***\n");
    }
}


static void print_benchmark_result(int result) {
    if (result == 0) {
        printf("BENCHMARK ENDED SUCCESSFULLY\n\n");
    } else {
        printf("*** BENCHMARK FAILED ***\n\n");
    }
}


static void print_example_result(int result) {
    if (result == 0) {
        printf("EXAMPLE ENDED SUCCESSFULLY\n\n");
    } else {
        printf("*** EXAMPLE FAILED ***\n\n");
    }
}

int main(int argc, char **argv) {
    int16_t result = 0;
    int16_t total_failed = 0;
    if (argc <= 1 || (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        printf("Constant-Time Algorithms for Crypto - follow the instruction below to use.\n");
        printf("Usage: %s <arguments>, where you select one of:\n"
               "    test-all -> To run all tests.\n"
               "    test-unit -> To run all unit tests.\n"
               "    test-unit-sd_estimator -> To run unit tests for the module: sd_estimator.\n"
               "    benchmark-all -> To run all benchmarks.\n"
               "    example-all -> To run all examples.\n"
               , argv[0]);
        printf("\n");
    }
    if (argc > 1 && (strcmp(argv[1], "test-all") == 0 || strcmp(argv[1], "test-unit") == 0 || strcmp(argv[1], "test-unit-sd_estimator") == 0)) {
        printf("\nEXECUTING ALL sd_estimator TESTS: \n");

        printf("\n===== test_sd_estimator.h Tests ===== \n\n");

        printf("Executing test_sd_estimator_bm_d2... ");
        result = (int16_t) test_sd_estimator_bm_d2();
        total_failed += result;
        print_test_result(result);

        printf("Executing test_sd_estimator_stern... ");
        result = (int16_t) test_sd_estimator_stern();
        total_failed += result;
        print_test_result(result);

        printf("Executing test_sd_estimator_dumer... ");
        result = (int16_t) test_sd_estimator_dumer();
        total_failed += result;
        print_test_result(result);

        printf("Executing test_sd_estimator_mo... ");
        result = (int16_t) test_sd_estimator_mo();
        total_failed += result;
        print_test_result(result);

        printf("Executing test_sd_estimator_bjmm... ");
        result = (int16_t) test_sd_estimator_bjmm();
        total_failed += result;
        print_test_result(result);

        printf("Executing test_sd_estimator_ball_collision... ");
        result = (int16_t) test_sd_estimator_ball_collision();
        total_failed += result;
        print_test_result(result);

    }

    if (total_failed > 0) {
        printf("\n=== OVERALL SCORE: %d FAILURES ===\n", total_failed);
    } else {
        printf("\n=== OVERALL SCORE: NO FAILURES === \n");
    }
    return 0;
}
