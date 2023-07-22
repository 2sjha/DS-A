/*
https://leetcode.com/problems/lru-cache/

Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

    LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
    int get(int key) Return the value of the key if the key exists, otherwise return -1.
    void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.

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
    At most 2 * 105 calls will be made to get and put.
*/

use std::collections::HashMap;
use std::collections::VecDeque;

struct LRUCache {
    mp: HashMap<i32, i32>,
    q: VecDeque<i32>,
    capacity: usize,
    size: usize,
}

impl LRUCache {
    fn new(capacity: i32) -> Self {
        Self {
            mp: HashMap::with_capacity(capacity as usize),
            q: VecDeque::with_capacity(capacity as usize),
            capacity: capacity as usize,
            size: 0,
        }
    }

    fn update_on_use(&mut self, key: i32) {
        let mut rem_idx: usize = 0;
        for i in 0..self.q.len() {
            if key == self.q[i] {
                rem_idx = i;
            }
        }
        self.q.remove(rem_idx);
        self.q.push_back(key);
    }

    fn get(&mut self, key: i32) -> i32 {
        if self.mp.contains_key(&key) {
            self.update_on_use(key);
            return self.mp[&key];
        } else {
            return -1;
        }
    }

    fn evict(&mut self) {
        let evicted: i32 = self.q.pop_front().unwrap();
        self.mp.remove(&evicted);
        self.size -= 1;
    }

    fn put(&mut self, key: i32, value: i32) {
        if !self.mp.contains_key(&key) {
            if self.size == self.capacity {
                self.evict();
            }
            self.size += 1;
            self.q.push_back(key);
        } else {
            self.update_on_use(key);
        }
        self.mp.insert(key, value);
    }
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * let obj = LRUCache::new(capacity);
 * let ret_1: i32 = obj.get(key);
 * obj.put(key, value);
 */

fn main() {
    let mut ret: i32;

    let mut obj1 = LRUCache::new(2);
    obj1.put(1, 1);
    obj1.put(2, 2);
    ret = obj1.get(1);
    assert!(ret == 1);
    obj1.put(3, 3);
    ret = obj1.get(2);
    assert!(ret == -1);
    obj1.put(4, 4);
    ret = obj1.get(1);
    assert!(ret == -1);
    ret = obj1.get(3);
    assert!(ret == 3);
    ret = obj1.get(4);
    assert!(ret == 4);

    let mut obj2 = LRUCache::new(2);
    ret = obj2.get(2);
    assert!(ret == -1);
    obj2.put(2, 6);
    ret = obj2.get(1);
    assert!(ret == -1);
    obj2.put(1, 5);
    obj2.put(1, 2);
    ret = obj2.get(1);
    assert!(ret == 2);
    ret = obj2.get(2);
    assert!(ret == 6);

    let mut obj3 = LRUCache::new(3);
    obj3.put(1, 1);
    obj3.put(2, 2);
    obj3.put(3, 3);
    obj3.put(4, 4);
    ret = obj3.get(4);
    assert!(ret == 4);
    ret = obj3.get(3);
    assert!(ret == 3);
    ret = obj3.get(2);
    assert!(ret == 2);
    ret = obj3.get(1);
    assert!(ret == -1);
    obj3.put(5, 5);
    ret = obj3.get(1);
    assert!(ret == -1);
    ret = obj3.get(2);
    assert!(ret == 2);
    ret = obj3.get(3);
    assert!(ret == 3);
    ret = obj3.get(4);
    assert!(ret == -1);
    ret = obj3.get(5);
    assert!(ret == 5);
}
