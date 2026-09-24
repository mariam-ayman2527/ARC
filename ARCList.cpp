
#include "ARCList.h"

ARCList::ARCList(){}

void ARCList::push_front(int key,int value){
    if(contains(key)){
        remove(key);
    }
    node_list.push_front({key,value});
    node_map[key]=node_list.begin();

}
bool ARCList::contains(int key)const{
    return node_map.find(key)!=node_map.end();
    
}

void ARCList::remove(int key){

    if(!(contains(key)))return;
    auto it=node_map[key];
    node_list.erase(it);
    node_map.erase(key);
}

int ARCList::pop_back(){
    if(node_list.empty())return -1;
    int last_key = node_list.back().key;
    node_list.pop_back();
    node_map.erase(last_key);
    return last_key;

}

Node ARCList::get_back() const{
    return node_list.back();
}

int ARCList::get_value(int key)const{
    auto it=node_map.find(key);
    if (it != node_map.end()) {
        return it->second->value;
    }
    return -1;
}

int ARCList::size()const {
    return static_cast<int>(node_list.size());
}

void ARCList::print() const{
    cout << "[ ";
    for (const auto& node : node_list) {
        cout << "(" << node.key << ":" << node.value << ") ";
    }
    cout << "]" << endl;
}

