/*
 * @lc app=leetcode id=460 lang=cpp
 *
 * [460] LFU Cache
 */
#include <unordered_map>
#include <map>
#include <iostream>
#include <list>

using namespace std;

// @lc code=start
using DLL = list<int>;
using DLLIter = DLL::iterator;

class Node {
public:
    int key;
    int value;
    int freq;
    DLLIter it;

    Node(int k, int v) : key(k), value(v), freq(1) {}
};

class LFUCache {
public:
    unordered_map<int, unique_ptr<Node>> key_table;
    map<int, DLL> freq_table;
    int size;
    int capacity;
    int min_freq;

    LFUCache(int capacity) : size(0), capacity(capacity), min_freq(0) {}

    void _remove_from_freq(unique_ptr<Node>& node) {
        int freq = node->freq;
        DLL& old_freq_list = freq_table[freq];
        old_freq_list.erase(node->it);
        if (old_freq_list.empty()) {
            freq_table.erase(freq);
            if (min_freq == freq) {
                // two scenarios to update min_freq
                // 1. when a node's frequency is increased
                // In this case, the next min_seq will be min_freq + 1
                // 2. when a node is evicted
                // In this case, we don't know the next min_freq yet
                // But we will set min_freq to 1 when adding a new node
                min_freq++;
            }
        }
    }

    void _add_to_freq(unique_ptr<Node>& node) {
        int freq = node->freq;
        if (freq_table.find(freq) == freq_table.end()) {
            freq_table[freq] = DLL();
        }
        DLL& new_freq_list = freq_table[freq];
        new_freq_list.push_front(node->key);
        node->it = new_freq_list.begin();
    }

    void _update_freq(int key) {
        unique_ptr<Node>& node = key_table[key];

        // remove current node from old freq list
        _remove_from_freq(node);

        // update node's freq
        node->freq++;

        // add current node to new freq list
        _add_to_freq(node);
    }

    int get(int key) {
        if (key_table.find(key) == key_table.end()) {
            return -1;
        }
        _update_freq(key);
        return key_table[key]->value;
    }

    void _evict_least_frequent() {
        DLL& min_freq_list = freq_table[min_freq];
        DLLIter it_to_evict = --min_freq_list.end();
        int key_to_evict = *it_to_evict;
        unique_ptr<Node>& node_to_evict = key_table[key_to_evict];
        _remove_from_freq(node_to_evict);
        key_table.erase(key_to_evict);
        size--;
    }

    void _add_new_node(int key, int value) {
        if (capacity == 0) return;

        if (size == capacity) {
            _evict_least_frequent();
        }

        unique_ptr<Node> new_node = make_unique<Node>(key, value);
        _add_to_freq(new_node);
        key_table[key] = move(new_node);
        min_freq = 1;
        size++;
    }
    
    void put(int key, int value) {
        if (key_table.find(key) == key_table.end()) {
            _add_new_node(key, value);
        } else {
            unique_ptr<Node>& node = key_table[key];
            node->value = value;
            _update_freq(key);
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end
int main() {
    LFUCache lfu(2);
    lfu.put(1, 1);
    lfu.put(2, 2);
    cout << "lfu.get(1): " << lfu.get(1) << endl; // returns 1
    lfu.put(3, 3);              // evicts key 2
    cout << "lfu.get(2): " << lfu.get(2) << endl; // returns -1 (not found)
    cout << "lfu.get(3): " << lfu.get(3) << endl; // returns 3
    lfu.put(4, 4);              // evicts key 1
    cout << "lfu.get(1): " << lfu.get(1) << endl; // returns -1 (not found)
    cout << "lfu.get(3): " << lfu.get(3) << endl; // returns 3
    cout << "lfu.get(4): " << lfu.get(4) << endl; // returns 4
    return 0;
}

