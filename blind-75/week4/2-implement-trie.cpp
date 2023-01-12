/*
https://leetcode.com/problems/implement-trie-prefix-tree/

A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store and
retrieve keys in a dataset of strings. There are various applications of this data structure, such
as autocomplete and spellchecker.

Implement the Trie class:
    - Trie() Initializes the trie object.
    - void insert(String word) Inserts the string word into the trie.
    - boolean search(String word) Returns true if the string word is in the trie (i.e., was inserted
      before), and false otherwise.
    - boolean startsWith(String prefix) Returns true if there is a
      previously inserted string word that has the prefix prefix, and false otherwise.


Example 1:

Input
["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
Output
[null, null, true, false, true, null, true]

Explanation
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // return True
trie.search("app");     // return False
trie.startsWith("app"); // return True
trie.insert("app");
trie.search("app");     // return True


Constraints:

    1 <= word.length, prefix.length <= 2000
    word and prefix consist only of lowercase English letters.
    At most 3 * 104 calls in total will be made to insert, search, and startsWith.
*/

#include "bits/stdc++.h"
#include <cstring>
#include <iostream>
using namespace std;

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

class Trie {
    struct Node {
        string word;
        bool complete;
        unordered_map<char, Node *> children;

        Node() {
            this->word = "";
            this->complete = true;
            this->children = unordered_map<char, Node *>();
        }

        Node(string word) {
            this->word = word;
            this->complete = false;
            this->children = unordered_map<char, Node *>();
        }
    };

    Node *root;

  private:
    void insert(Node *node, string word, int level) {
        if (node == nullptr or word == "" or level < 0) {
            return;
        }

        if (node->word == word and word.length() == level) {
            node->complete = true;
            return;
        }

        char edge = word[level];
        if (node->children[edge] == nullptr) {
            string intermediate_word = word.substr(0, level + 1);
            node->children[edge] = new Node(intermediate_word);
        }

        insert(node->children[edge], word, level + 1);
    }

    bool search(Node *node, string word, int level) {
        if (node == nullptr or word == "" or level < 0 or level > word.length()) {
            return false;
        }

        if (node->word == word and word.length() == level and node->complete) {
            return true;
        }

        char edge = word[level];
        if (node->children[edge] == nullptr) {
            return false;
        }

        return search(node->children[edge], word, level + 1);
    }

    bool startsWith(Node *node, string word, int level) {
        if (node == nullptr or word == "" or level < 0 or level > word.length()) {
            return false;
        }

        if (node->word == word and word.length() == level) {
            return true;
        }

        char edge = word[level];
        if (node->children[edge] == nullptr) {
            return false;
        }

        return startsWith(node->children[edge], word, level + 1);
    }

  public:
    Trie() { this->root = new Node(); }

    void insert(string word) { insert(this->root, word, 0); }

    bool search(string word) { return search(this->root, word, 0); }

    bool startsWith(string prefix) { return startsWith(this->root, prefix, 0); }
};

int main() {
    Trie t = Trie();
    t.insert("apple");
    t.insert("app");
    t.insert("apply");
    t.insert("applet");
    t.insert("try");
    t.insert("trial");

    cout << t.search("a") << endl;
    cout << t.search("apple") << endl;
    cout << t.search("app") << endl;
    cout << t.search("appley") << endl;
    cout << t.search("base") << endl;
    cout << endl << endl;
    cout << t.startsWith("a") << endl;
    cout << t.startsWith("tr") << endl;
    cout << t.startsWith("appl") << endl;
    cout << t.startsWith("appley") << endl;
    cout << t.startsWith("base") << endl;
    return 0;
}