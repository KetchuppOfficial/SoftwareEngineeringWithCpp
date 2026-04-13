# Free list allocator benchmark

```bash
build/benchmark/free_list_allocator
# Chain_Allocator::show : m_size = 1024 m_begin = 0x00005555555f1ce0 m_head = 0x00005555555f1ce0
# Chain_Allocator::show : m_size = 1024 m_begin = 0x00005555555f1ce0 m_head = 0x00005555555f1d00
# Chain_Allocator::show : m_size = 1024 m_begin = 0x00005555555f1ce0 m_head = 0x00005555555f1d20
# Chain_Allocator::show : m_size = 1024 m_begin = 0x00005555555f1ce0 m_head = 0x00005555555f1d40
# Chain_Allocator::show : m_size = 1024 m_begin = 0x00005555555f1ce0 m_head = 0x00005555555f1d60
# Chain_Allocator::show : m_size = 1024 m_begin = 0x00005555555f1ce0 m_head = 0x00005555555f1d20 m_head->next = 0x00005555555f1d60
# Chain_Allocator::show : m_size = 1024 m_begin = 0x00005555555f1ce0 m_head = 0x00005555555f1d00 m_head->next = 0x00005555555f1d60
# Chain_Allocator::show : m_size = 1024 m_begin = 0x00005555555f1ce0 m_head = 0x00005555555f1d60
# 2026-04-13T14:53:30+03:00
# Run on (12 X 3000 MHz CPU s)
# CPU Caches:
#   L1 Data 32 KiB (x6)
#   L1 Instruction 32 KiB (x6)
#   L2 Unified 512 KiB (x6)
#   L3 Unified 4096 KiB (x2)
# Load Average: 0.83, 0.72, 0.80
# ***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
# --------------------------------------------------------------------------------------------
# Benchmark                                                  Time             CPU   Iterations
# --------------------------------------------------------------------------------------------
# without_allocator                                    6064772 ns      6064325 ns          114
# find<dts::FreeListAllocator::SearchPolicy::first>    5720403 ns      5719620 ns          122
# find<dts::FreeListAllocator::SearchPolicy::best>     5499897 ns      5499730 ns          126
```

The time spent by the free list allocator with both search policies is approximately the same.
