#include "render_cpu.hpp"
#include "render_mt.hpp"
#include "render_gpu.hpp"
#include <vector>
#include <benchmark/benchmark.h>

constexpr int kRGBASize = 4;
constexpr int width = 4800;
constexpr int height = 3200;

void BM_Rendering_cpu(benchmark::State& st)
{
    int stride = width * kRGBASize;
    std::vector<uint8_t> data(height * stride);

    for (auto _ : st)
        render_cpu(data.data(), width, height, stride);

    st.counters["fps"] = benchmark::Counter(st.iterations(), benchmark::Counter::kIsRate);
}

void BM_Rendering_mt(benchmark::State& st)
{
    int stride = width * kRGBASize;
    std::vector<uint8_t> data(height * stride);

    for (auto _ : st)
        render_mt(data.data(), width, height, stride);

    st.counters["fps"] = benchmark::Counter(st.iterations(), benchmark::Counter::kIsRate);
}

void BM_Rendering_gpu(benchmark::State& st)
{
    int stride = width * kRGBASize;
    std::vector<uint8_t> data(height * stride);

    GPURenderer rd;
    for (auto _ : st)
        rd.render_gpu(data.data(), width, height, stride);

    st.counters["fps"] = benchmark::Counter(st.iterations(), benchmark::Counter::kIsRate);
}

BENCHMARK(BM_Rendering_cpu)
->Unit(benchmark::kMillisecond)
->UseRealTime();

BENCHMARK(BM_Rendering_mt)
->Unit(benchmark::kMillisecond)
->UseRealTime();

BENCHMARK(BM_Rendering_gpu)
->Unit(benchmark::kMillisecond)
->UseRealTime();

BENCHMARK_MAIN();
