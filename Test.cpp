#include "Test.h"
#include "ARCCash.h"
#include <thread>
#include <vector>
#include <iostream>
#include <random>
#include <atomic>

using namespace std;

static int total_tests = 0;
static int passed_tests = 0;

static void EXPECT_EQUAL(int actual, int expected, const string& test_name) {
    total_tests++;
    if (actual == expected) {
        cout << "  [PASS] " << test_name << endl;
        passed_tests++;
    } else {
        cout << "  [FAIL] " << test_name 
             << " (Expected: " << expected << ", Got: " << actual << ")" << endl;
    }
}

void test_basic_operations() {
    cout << "\n=== Running: Basic Operations Test ===" << endl;
    ARCCash cache(3);

    cache.request(1, 100);
    cache.request(2, 200);

    int val1 = cache.request(1, 100);
    EXPECT_EQUAL(val1, 100, "Key 1 Hit should return 100");

    int val3 = cache.request(3, 300);
    EXPECT_EQUAL(val3, 300, "Key 3 Miss should return 300");
}

void test_arc_adaptation() {
    cout << "\n=== Running: ARC Adaptation Test ===" << endl;
    ARCCash cache(2);

    cache.request(10, 1000);
    cache.request(20, 2000);

    cache.request(30, 3000); 

    int val = cache.request(10, 1000);
    EXPECT_EQUAL(val, 1000, "Key 10 Ghost Hit should return original value");
}

void test_concurrent_stress() {
    cout << "\n=== Running: Concurrent Stress Test ===" << endl;

    const int cache_capacity = 20;
    const int num_threads = 8;
    const int ops_per_thread = 50000;

    ARCCash cache(cache_capacity);
    vector<thread> workers;

    atomic<bool> start_signal{false}; 

    auto worker_task = [&cache, &start_signal](int thread_id, int total_ops) {
        while (!start_signal.load()) {} 

        mt19937 rng(thread_id + 42);
        uniform_int_distribution<int> key_dist(1, 50);

        for (int i = 0; i < total_ops; ++i) {
            int key = key_dist(rng);
            cache.request(key, key * 10); 
        }
    };

    for (int i = 0; i < num_threads; ++i) {
        workers.emplace_back(worker_task, i, ops_per_thread);
    }

    start_signal.store(true);

    for (auto& t : workers) {
        t.join();
    }

    total_tests++;
    passed_tests++;
    cout << "  [PASS] Executed " << (num_threads * ops_per_thread) 
         << " ops concurrently without crash!" << endl;
}

void run_all_tests() {
    test_basic_operations();
    test_arc_adaptation();
    test_concurrent_stress();

    cout << "\n==========================================" << endl;
    cout << "SUMMARY: " << passed_tests << "/" << total_tests << " tests passed." << endl;
    cout << "==========================================" << endl;
}