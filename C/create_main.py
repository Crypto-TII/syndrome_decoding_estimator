#!/usr/bin/env python
# Open the file "testall.c" and overwrite the content:
import os
import glob
import re
from pathlib import Path

print("Creating main file\n")

f = open("./main/main.cpp", "w")

f.write('#include <stdio.h>\n')
f.write('#include <string.h>\n')
f.write('#include <ctime>\n')
f.write('#include <cstdint>\n')
src_folders = os.listdir('./src')
tests_folders = os.listdir('./tests')
# tests_folders.remove('testall') # Removing testall folder from the tests_folder list.
benchmarks_folders = os.listdir('./benchmarks')
examples_folders = os.listdir('./examples')

# add C headers

f.write('extern "C" {\n')
for folder in src_folders:
    # tests = glob.glob('tests/' + folder + '/*.h')
    tests = glob.glob('tests/' + folder + '/*.c')
    for t in tests:
        f.write('\t#include "../tests/' + folder + '/' + os.path.splitext(os.path.basename(t))[0] + ".h" + '" \n')

    benchmarks = glob.glob('benchmarks/' + folder + '/*.h')
    for t in benchmarks:
        f.write('\t#include "../benchmarks/' + folder + '/' + os.path.basename(t) + '"\n')

    examples = glob.glob('examples/' + folder + '/*.h')
    for t in examples:
        f.write('\t#include "../examples/' + folder + '/' + os.path.basename(t) + '"\n')

f.write('}\n')

# add C++ headers

for folder in src_folders:
    tests = glob.glob('tests/' + folder + '/*.cpp')
    for t in tests:
        f.write('#include "../tests/' + folder + '/' + os.path.splitext(os.path.basename(t))[0] + ".h" + '"\n')

    benchmarks = glob.glob('benchmarks/' + folder + '/*.cpp')
    for t in benchmarks:
        f.write('#include "../benchmarks/' + folder + '/' + os.path.splitext(os.path.basename(t))[0] + ".h" + '"\n')

    examples = glob.glob('examples/' + folder + '/*.cpp')
    for t in examples:
        f.write('#include "../examples/' + folder + '/' + os.path.splitext(os.path.basename(t))[0] + ".h" + '"\n')

# helper functions

f.write('\n')
f.write('uint64_t rdtsc(){\n')
f.write('    unsigned int lo,hi;\n')
f.write('   __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));\n')
f.write('   return ((uint64_t)hi << 32u) | lo;\n')
f.write('}\n\n')

f.write('\n')
f.write('void pretty_print_benchmark(const char* measured_function, clock_t total_time, uint64_t total_iterations, uint64_t total_cycles){\n')
f.write('   double total_time_in_seconds = (double) total_time /\n')
f.write('   (double) CLOCKS_PER_SEC;\n')
f.write('   double operations_per_second = (double) total_iterations * (double) CLOCKS_PER_SEC/ (double) total_time;\n')
f.write('   double cycles_per_op = (double) total_cycles/ (double) total_iterations;\n')

f.write('   printf("\\r%60s:  %12.2f cycles/op, (%3.2f s, %4.3e ops, %4.3e cycles, %3.2f op/s, %4.3f GHz)\\n", measured_function,\n')
f.write('       cycles_per_op, total_time_in_seconds, (double) total_iterations, (double) total_cycles, operations_per_second, cycles_per_op*operations_per_second/1000000000.);\n')
f.write('}\n\n')


f.write('\n')
f.write('static void print_test_result(int result) {\n')
f.write('    if (result == 0) {\n')
f.write('        printf("PASS\\n");\n')
f.write('    } else {\n')
f.write('        printf("*** FAILED ***\\n");\n')
f.write('    }\n')
f.write('}\n\n')

f.write('\n')
f.write('static void print_benchmark_result(int result) {\n')
f.write('    if (result == 0) {\n')
f.write('        printf("BENCHMARK ENDED SUCCESSFULLY\\n\\n");\n')
f.write('    } else {\n')
f.write('        printf("*** BENCHMARK FAILED ***\\n\\n");\n')
f.write('    }\n')
f.write('}\n\n')

f.write('\n')
f.write('static void print_example_result(int result) {\n')
f.write('    if (result == 0) {\n')
f.write('        printf("EXAMPLE ENDED SUCCESSFULLY\\n\\n");\n')
f.write('    } else {\n')
f.write('        printf("*** EXAMPLE FAILED ***\\n\\n");\n')
f.write('    }\n')
f.write('}\n\n')

f.write('int main(int argc, char **argv) {\n')  # start main
f.write('    int16_t result = 0;\n')
f.write('    int16_t total_failed = 0;\n')
f.write('    if (argc <= 1 || (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {\n')
f.write('        printf("Constant-Time Algorithms for Crypto - follow the instruction below to use.\\n");\n')
f.write('        printf("Usage: %s <arguments>, where you select one of:\\n"\n')
f.write('               "    test-all -> To run all tests.\\n"\n')

f.write('               "    test-unit -> To run all unit tests.\\n"\n')
for folder in tests_folders:
    f.write('               "    test-unit-' + folder + ' -> To run unit tests for the module: ' + folder + '.\\n"\n')

f.write('               "    benchmark-all -> To run all benchmarks.\\n"\n')
for folder in benchmarks_folders:
    f.write('               "    benchmark-' + folder + ' -> To run benchmarks for the module: ' + folder + '.\\n"\n')

f.write('               "    example-all -> To run all examples.\\n"\n')
for folder in examples_folders:
    f.write('               "    example-' + folder + ' -> To print examples for the module: ' + folder + '.\\n"\n')

f.write('               , argv[0]);\n')
f.write('        printf("\\n");\n')
f.write('    }\n')

for folder in tests_folders:
    f.write(
        '    if (argc > 1 && (strcmp(argv[1], "test-all") == 0 || strcmp(argv[1], "test-unit") == 0 || strcmp(argv[1], "test-unit-' + folder + '") == 0)) {\n')
    f.write('        printf("\\nEXECUTING ALL ' + folder + ' TESTS: \\n");\n\n')
    tests = glob.glob('tests/' + folder + '/*.h')
    for t in tests:
        test_name = os.path.basename(t)
        f.write('        printf("\\n===== ' + test_name + ' Tests ===== \\n\\n");\n\n')
        test_content = open('./tests/' + folder + '/' + test_name, "r")
        str = test_content.read()
        tests = [re.search('test_(.+?);', line).group(0)[0:-3] for line in str.split('\n') if 'test_' in line]
        for test in tests:
            f.write('        printf("Executing ' + test + '... ");\n')
            f.write('        result = (int16_t) ' + test + '();\n')
            f.write('        total_failed += result;\n')
            f.write('        print_test_result(result);\n\n')
    f.write('    }\n\n')

for folder in benchmarks_folders:
    f.write(
        '    if (argc > 1 && (strcmp(argv[1], "benchmark-all") == 0 || strcmp(argv[1], "benchmark") == 0 || strcmp(argv[1], "benchmark-' + folder + '") == 0)) {\n')
    f.write('        printf("\\nEXECUTING ALL ' + folder + ' BENCHMARKS: \\n");\n\n')
    benchmarks = glob.glob('benchmarks/' + folder + '/*.h')
    for t in benchmarks:
        benchmark_name = os.path.basename(t)
        f.write('        printf("\\n===== ' + benchmark_name + ' Benchmarks ===== \\n\\n");\n\n')
        benchmark_content = open('./benchmarks/' + folder + '/' + benchmark_name, "r")
        str = benchmark_content.read()
        benchmarks = [re.search('benchmark_(.+?);', line).group(0)[0:-3] for line in str.split('\n') if
                      'benchmark_' in line]
        for benchmark in benchmarks:
            f.write('        printf("Executing ' + benchmark + '... ");\n')
            f.write('        result = (int16_t) ' + benchmark + '();\n')
            f.write('        total_failed += result;\n')
            f.write('        print_benchmark_result(result);\n\n')
    f.write('    }\n\n')

for folder in examples_folders:
    f.write(
        '    if (argc > 1 && (strcmp(argv[1], "example-all") == 0 || strcmp(argv[1], "example-' + folder + '") == 0)) {\n')
    f.write('        printf("\\nEXECUTING ALL ' + folder + ' EXAMPLES: \\n");\n\n')
    examples = glob.glob('examples/' + folder + '/*.h')
    for t in examples:
        example_name = os.path.basename(t)
        f.write('        printf("\\n===== ' + example_name + ' Examples ===== \\n\\n");\n\n')
        example_content = open('./examples/' + folder + '/' + example_name, "r")
        str = example_content.read()
        examples = [re.search('example_(.+?);', line).group(0)[0:-3] for line in str.split('\n') if 'example_' in line]
        for example in examples:
            f.write('        printf("\\nExecuting ' + example + '... ");\n')
            f.write('        result = (int16_t) ' + example + '();\n')
            f.write('        total_failed += result;\n')
            f.write('        print_example_result(result);\n\n')
    f.write('    }\n\n')

f.write('    if (total_failed > 0) {\n')
f.write('        printf("\\n=== OVERALL SCORE: %d FAILURES ===\\n", total_failed);\n')
f.write('    } else {\n')
f.write('        printf("\\n=== OVERALL SCORE: NO FAILURES === \\n");\n')
f.write('    }\n')
f.write('    return 0;\n')

f.write('}\n')  # close main

f.close()
