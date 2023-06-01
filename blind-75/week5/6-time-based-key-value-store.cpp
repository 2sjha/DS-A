/*
https://leetcode.com/problems/time-based-key-value-store/

Design a time-based key-value data structure that can store multiple values for the same key at
different time stamps and retrieve the key's value at a certain timestamp.

Implement the TimeMap class:

    TimeMap() Initializes the object of the data structure.
    void set(String key, String value, int timestamp) Stores the key key with the value value at the
given time timestamp. String get(String key, int timestamp) Returns a value such that set was called
previously, with timestamp_prev <= timestamp. If there are multiple such values, it returns the
value associated with the largest timestamp_prev. If there are no values, it returns "".


Example 1:

Input
["TimeMap", "set", "get", "get", "set", "get", "get"]
[[], ["foo", "bar", 1], ["foo", 1], ["foo", 3], ["foo", "bar2", 4], ["foo", 4], ["foo", 5]]
Output
[null, null, "bar", "bar", null, "bar2", "bar2"]

Explanation
TimeMap timeMap = new TimeMap();
timeMap.set("foo", "bar", 1);  // store the key "foo" and value "bar" along with timestamp = 1.
timeMap.get("foo", 1);         // return "bar"
timeMap.get("foo", 3);         // return "bar", since there is no value corresponding to foo at
timestamp 3
                               // and timestamp 2, then the only value is at timestamp 1 is "bar".
timeMap.set("foo", "bar2", 4); // store the key "foo" and value "bar2" along with timestamp = 4.
timeMap.get("foo", 4);         // return "bar2"
timeMap.get("foo", 5);         // return "bar2"


Constraints:

    1 <= key.length, value.length <= 100
    key and value consist of lowercase English letters and digits.
    1 <= timestamp <= 107
    All the timestamps timestamp of set are strictly increasing.
    At most 2 * 105 calls will be made to set and get.
 */

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */

#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class TmapValue {
    set<int> timestamps;
    unordered_map<int, string> ts_value_pairs;

  public:
    TmapValue() {
        timestamps = set<int>();
        ts_value_pairs = unordered_map<int, string>();
    }

    void insert(string value, int timestamp) {
        timestamps.insert(timestamp);
        ts_value_pairs[timestamp] = value;
    }

    string get(int timestamp) {
        if (ts_value_pairs.find(timestamp) == ts_value_pairs.end()) {
            set<int>::iterator closest = timestamps.lower_bound(timestamp);
            if (closest == timestamps.end()) {
                return ts_value_pairs[*timestamps.rbegin()];
            } else if (closest == timestamps.begin()) {
                return "";
            } else {
                closest--;
                return ts_value_pairs[*closest];
            }
        } else {
            return ts_value_pairs[timestamp];
        }
    }

    bool empty() { return timestamps.empty() && ts_value_pairs.empty(); }
    friend class TimeMap;
};

class TimeMap {
    unordered_map<string, TmapValue> tmap;

  public:
    TimeMap() { tmap = unordered_map<string, TmapValue>(); }

    void set(string key, string value, int timestamp) {
        if (tmap.find(key) == tmap.end()) {
            tmap[key] = TmapValue();
        }

        tmap[key].insert(value, timestamp);
    }

    string get(string key, int timestamp) {
        if (tmap.find(key) == tmap.end()) {
            return "";
        } else if (tmap[key].empty()) {
            return "";
        } else {
            return tmap[key].get(timestamp);
        }
    }
};

int main() {

    TimeMap *timeMap = new TimeMap();
    timeMap->set("foo", "bar", 1);
    assert(timeMap->get("foo", 1) == "bar");
    assert(timeMap->get("foo", 3) == "bar");
    timeMap->set("foo", "bar2", 4);
    assert(timeMap->get("foo", 4) == "bar2");
    assert(timeMap->get("foo", 5) == "bar2");

    TimeMap *timeMap2 = new TimeMap();
    timeMap2->set("love", "high", 10);
    timeMap2->set("love", "low", 20);
    assert(timeMap2->get("love", 5) == "");
    assert(timeMap2->get("love", 10) == "high");
    assert(timeMap2->get("love", 15) == "high");
    assert(timeMap2->get("love", 20) == "low");
    assert(timeMap2->get("love", 25) == "low");
    return 0;
}