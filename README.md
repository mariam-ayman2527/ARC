# Adaptive Replacement Cache (ARC) in C++

A high-performance, thread-safe C++ implementation of the **Adaptive Replacement Cache (ARC)** algorithm. This project includes a custom dynamic doubly-linked list with hash map lookups (`ARCList`) and a robust multi-threaded test runner to verify performance and thread safety under high contention.

---

##  Features

- **Dynamic Self-Tuning:** Dynamically balances between **Recency** (LRU) and **Frequency** (LFU) by tuning the target size parameter ($p$) based on cache hits in ghost lists ($B_1$ and $B_2$).
- **Thread-Safe Architecture:** Built using `std::shared_mutex` to allow concurrent operations safely across multiple threads.
- **Custom Data Structure:** Uses an efficient $O(1)$ Hash Map + Doubly-Linked List implementation (`ARCList`) for instant cache lookups and updates.
- **Stress-Tested:** Includes a multi-threaded stress testing suite simulating simultaneous heavy read/write operations without deadlocks or data races.

---

##  Architecture & Algorithm Overview

The ARC algorithm manages cache items across four distinct internal lists:

| List | Description |
| :--- | :--- |
| **$T_1$** | Most Recently Used (MRU) items (contains key-value pairs) |
| **$T_2$** | Most Frequently Used (MFU) items (contains key-value pairs) |
| **$B_1$** | Ghost MRU list (tracks recently evicted keys from $T_1$) |
| **$B_2$** | Ghost MFU list (tracks recently evicted keys from $T_2$) |

---

##  Getting Started

### Prerequisites

- C++17 compatible compiler (e.g., `g++` or `clang++`)
- POSIX Threads library (`pthread`)

### Compilation

Clone the repository and compile all source files using `g++`:

```bash
git clone https://github.com/mariam-ayman2527/ARC.git
cd ARC
g++ -std=c++17 Main.cpp Test.cpp ARCCash.cpp ARCList.cpp -o run_tests -pthread
```
Running Tests
Execute the compiled binary to run the test suite:

```bash
./run_tests
```

## Testing Suite Overview

The project comes with a comprehensive testing framework covering:

1. **Basic Cache Operations:** Tests cache hits, misses, and insertions.
2. **ARC Adaptation Logic:** Verifies parameter `p` tuning when hits occur in ghost lists (`B1` / `B2`).
3. **Multi-Threaded Stress Test:** Launches 8 parallel threads performing over 400,000 operations synchronized with an atomic barrier (`std::atomic<bool>`) to stress-test locks under heavy contention.

---

##  Example Usage

```cpp
#include "ARCCash.h"
#include <iostream>

int main() {
    // Create an ARC cache with capacity 3
    ARCCash cache(3);

    // Request keys (Insertions / Misses)
    cache.request(1, 100);
    cache.request(2, 200);

    // Cache Hit (Promotes Key 1 to T2 MFU list)
    int value = cache.request(1, 100);

    // Print internal cache state
    cache.print_state("Current State");

    return 0;
}
```

