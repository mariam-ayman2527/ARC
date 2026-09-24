#pragma once
#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct Node{
    int key,value;
};

class ARCList{

    private:
    list<Node>node_list;
    unordered_map<int,list<Node>::iterator >node_map;

    public:
        ARCList();

        void push_front(int key,int value);
        int pop_back();
        void remove(int key);
        bool contains(int key)const;
        Node get_back()const;
        int get_value(int key)const;
        int size() const;
        void print() const;

};