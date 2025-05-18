#pragma once

// Runs your custom code benchmark at the given optimization level and returns elapsed time in nanoseconds
long long runCustomBenchmark(int optLevel);

// The actual custom code you want to benchmark
void testCustomCode();
