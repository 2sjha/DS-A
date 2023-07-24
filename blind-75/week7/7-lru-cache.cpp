/*
https://leetcode.com/problems/lru-cache/

Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

    - LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
    - int get(int key) Return the value of the key if the key exists, otherwise return -1.
    - void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the
key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict
the least recently used key.

The functions get and put must each run in O(1) average time complexity.


Example 1:

Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4


Constraints:

    1 <= capacity <= 3000
    0 <= key <= 10^4
    0 <= value <= 10^5
    At most 2 * 10^5 calls will be made to get and put.
*/

// Took a hint from solution that a queue is doable.
// Idea is that when you update a key on use, you push it into the queue & maintain a count of
// copies of the key in the queue.
// While evicting, you keep popping the keys & reducing their q_count values until you've deleted
// the key that was the least recently used, because other more recently used keys would still have
// copies in the back of the queue.

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class LRUCache {
  private:
    queue<int> q;
    unordered_map<int, int> q_count;
    unordered_map<int, int> mp;
    int size = 0;
    int capacity = 0;

    void evict() {
        int key = this->q.front();
        while (this->q_count[key] != 0) {
            key = this->q.front();
            this->q.pop();
            this->q_count[key]--;
        }

        this->mp.erase(key);
        this->q_count.erase(key);
        this->size--;
    }

    void updateOnUse(int key) {
        this->q.push(key);
        this->q_count[key]++;
    }

  public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        this->size = 0;
    }

    int get(int key) {
        if (this->mp.count(key)) {
            updateOnUse(key);
            return this->mp[key];
        }

        return -1;
    }

    void put(int key, int value) {
        if (this->mp.count(key)) {
            updateOnUse(key);
        } else {
            if (this->size == this->capacity) {
                evict();
            }
            this->size++;
            this->q.push(key);
            this->q_count[key] = 1;
        }
        this->mp[key] = value;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() {
    LRUCache *lRUCache;

    lRUCache = new LRUCache(2);
    lRUCache->put(1, 1);              // cache is {1=1}
    lRUCache->put(2, 2);              // cache is {1=1, 2=2}
    cout << lRUCache->get(1) << '\n'; // return 1
    assert(lRUCache->get(1) == 1);
    lRUCache->put(3, 3);              // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    cout << lRUCache->get(2) << '\n'; // returns -1 (not found)
    assert(lRUCache->get(2) == -1);
    lRUCache->put(4, 4);              // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    cout << lRUCache->get(1) << '\n'; // return -1 (not found)
    assert(lRUCache->get(1) == -1);
    cout << lRUCache->get(3) << '\n'; // return 3
    assert(lRUCache->get(3) == 3);
    cout << lRUCache->get(4) << '\n'; // return 4
    assert(lRUCache->get(4) == 4);

    cout << endl;

    lRUCache = new LRUCache(1);
    lRUCache->put(2, 1);              // cache is {2=1}
    cout << lRUCache->get(2) << '\n'; // return 1
    assert(lRUCache->get(2) == 1);
    lRUCache->put(3, 2);              // LRU key was 3, evicts key 2, cache is {3=2}
    cout << lRUCache->get(2) << '\n'; // returns -1 (not found)
    assert(lRUCache->get(2) == -1);
    cout << lRUCache->get(3) << '\n'; // return 2
    assert(lRUCache->get(3) == 2);

    cout << endl;

    lRUCache = new LRUCache(2);
    lRUCache->put(2, 1);              // cache is {2=1}
    lRUCache->put(2, 2);              // cache is {2=2}
    cout << lRUCache->get(2) << '\n'; // return 2
    assert(lRUCache->get(2) == 2);
    lRUCache->put(1, 1);              // cache is {2=2, 1=1}
    lRUCache->put(4, 1);              // 2 is evicted. cache is {1=1, 4=1}
    cout << lRUCache->get(2) << '\n'; // returns -1 (not found)
    assert(lRUCache->get(2) == -1);

    cout << endl;

    lRUCache = new LRUCache(3);
    lRUCache->put(1, 1);
    lRUCache->put(2, 2);
    lRUCache->put(3, 3);
    lRUCache->put(4, 4);
    cout << lRUCache->get(4) << '\n';
    assert(lRUCache->get(4) == 4);
    cout << lRUCache->get(3) << '\n';
    assert(lRUCache->get(3) == 3);
    cout << lRUCache->get(2) << '\n';
    assert(lRUCache->get(2) == 2);
    cout << lRUCache->get(1) << '\n';
    assert(lRUCache->get(1) == -1);
    lRUCache->put(5, 5);
    cout << lRUCache->get(1) << '\n';
    assert(lRUCache->get(1) == -1);
    cout << lRUCache->get(2) << '\n';
    assert(lRUCache->get(2) == 2);
    cout << lRUCache->get(3) << '\n';
    assert(lRUCache->get(3) == 3);
    cout << lRUCache->get(4) << '\n';
    assert(lRUCache->get(4) == -1);
    cout << lRUCache->get(5) << '\n';
    assert(lRUCache->get(5) == 5);

    return 0;
}