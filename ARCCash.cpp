#include"ARCCash.h"

static mutex global_cout_mutex;
ARCCash::ARCCash(int c) : capacity(c), p(0.0) {}


        int ARCCash::request(int key,int val){
            unique_lock<shared_mutex> lock(cache_mutex);

            if(T1.contains(key)||T2.contains(key)){

                int value=T1.contains(key)?T1.get_value(key):T2.get_value(key);
                if(T1.contains(key)){
                    T1.remove(key);
                }else{
                    T2.remove(key); 
                }

                T2.push_front(key,value);
                return value;

            }
            else if(B1.contains(key) || B2.contains(key)){
                handle_ghost(key,val);
                return val;
            }
            else{
                handle_miss(key, val);
                return val;
            }
        }

        void ARCCash::handle_ghost(int key,int val){
                if(B1.contains(key)){
                    double ratio =max(1.0, (double(B2.size()) / double(B1.size())));
                    p = min(double(capacity), p + ratio);
                    replace(key);
                    B1.remove(key);
                }else{
                    double ratio = max(1.0, (double(B1.size() )/double(B2.size()) ));
                    p = max(0.0, p - ratio);
                    replace(key);
                    B2.remove(key);
                }
                T2.push_front(key, val);
        }

        void ARCCash::replace(int key){
            if ((T1.size() > 0) && ((T1.size() > p) || (B2.contains(key) && T1.size() == p))) {
                int evicted_key = T1.pop_back();
                B1.push_front(evicted_key, 0);
            }else if (T2.size() > 0) {
                int evicted_key=T2.pop_back();
                B2.push_front(evicted_key, 0);
            }
        }

        void ARCCash::handle_miss(int key,int value){

            int L1_size = T1.size() + B1.size();
            int total_size = L1_size + T2.size() + B2.size();
            if (L1_size == capacity) {
                if (T1.size() < capacity) {
                    B1.pop_back();
                    replace(key);
                } else {
                    T1.pop_back();
                }
            }else if (L1_size < capacity && total_size >= capacity) {
                if (total_size >= 2 * capacity) {
                B2.pop_back();
                }
                replace(key);
            }
            T1.push_front(key,value);

        }
        void ARCCash::print_state(const string& action) const{
            shared_lock<shared_mutex> lock(cache_mutex);
            lock_guard<mutex> cout_lock(global_cout_mutex);
            cout << "\n--- " << action << " ---" <<endl;
            cout << "Target Size (p): " << p << " | Capacity (c): "<<capacity<<endl;
    
            cout << "T1 (MRU Cache): ";
            T1.print(); 
            cout << "T2 (MFU Cache): ";
            T2.print();
    
            cout << "B1 (Ghost MRU): ";
            B1.print();
    
            cout << "B2 (Ghost MFU): ";
            B2.print();
            cout << "-----------------------------------" << std::endl;
}

