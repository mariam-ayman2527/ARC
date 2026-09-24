

#include "ARCList.h"
#include <shared_mutex>
#include <string>

class ARCCash {
private:
    int capacity;
    double p;

    ARCList T1;
    ARCList T2;
    ARCList B1;
    ARCList B2;

    mutable shared_mutex cache_mutex;

    void handle_ghost(int key, int val);
    void replace(int key);
    void handle_miss(int key, int value);

public:
    explicit ARCCash(int c);

    int request(int key, int val = 0);
    void print_state(const string& action) const;
};

