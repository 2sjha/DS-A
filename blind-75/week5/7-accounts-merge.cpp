/*
https://leetcode.com/problems/accounts-merge/

Given a list of accounts where each element accounts[i] is a list of strings, where the first
element accounts[i][0] is a name, and the rest of the elements are emails representing emails of the
account.

Now, we would like to merge these accounts. Two accounts definitely belong to the same person if
there is some common email to both accounts. Note that even if two accounts have the same name, they
may belong to different people as people could have the same name. A person can have any number of
accounts initially, but all of their accounts definitely have the same name.

After merging the accounts, return the accounts in the following format: the first element of each
account is the name, and the rest of the elements are emails in sorted order. The accounts
themselves can be returned in any order.


Example 1:

Input: accounts =
{{"John","johnsmith@mail.com","john_newyork@mail.com"},{"John","johnsmith@mail.com","john00@mail.com"},{"Mary","mary@mail.com"},{"John","johnnybravo@mail.com"]]
Output:
{{"John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"},{"Mary","mary@mail.com"},{"John","johnnybravo@mail.com"]]
Explanation:
The first and second John's are the same person as they have the common email "johnsmith@mail.com".
The third John and Mary are different people as none of their email addresses are used by other
accounts. We could return these lists in any order, for example the answer {{'Mary',
'mary@mail.com'], ['John', 'johnnybravo@mail.com'],
['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.

Example 2:

Input: accounts =
{{"Gabe","Gabe0@m.co","Gabe3@m.co","Gabe1@m.co"},{"Kevin","Kevin3@m.co","Kevin5@m.co","Kevin0@m.co"},{"Ethan","Ethan5@m.co","Ethan4@m.co","Ethan0@m.co"},{"Hanzo","Hanzo3@m.co","Hanzo1@m.co","Hanzo0@m.co"},{"Fern","Fern5@m.co","Fern1@m.co","Fern0@m.co"]]
Output:
{{"Ethan","Ethan0@m.co","Ethan4@m.co","Ethan5@m.co"},{"Gabe","Gabe0@m.co","Gabe1@m.co","Gabe3@m.co"},{"Hanzo","Hanzo0@m.co","Hanzo1@m.co","Hanzo3@m.co"},{"Kevin","Kevin0@m.co","Kevin3@m.co","Kevin5@m.co"},{"Fern","Fern0@m.co","Fern1@m.co","Fern5@m.co"]]


Constraints:

    1 <= accounts.length <= 1000
    2 <= accounts[i].length <= 10
    1 <= accounts[i][j].length <= 30
    accounts[i][0] consists of English letters.
    accounts[i][j] (for j > 0) is a valid email.
*/

#include "./../../cpp-utils/printutils.h"
#include "bits/stdc++.h"
#include <iostream>
using namespace std;

class Solution {
    vector<int> account_sets;
    vector<int> account_sets_ranks;

    int account_sets_find(int i) {
        if (account_sets[i] == i) {
            return i;
        } else {
            return account_sets_find(account_sets[i]);
        }
    }

    void account_sets_union(int big, int small) {
        if (account_sets_ranks[big] >= account_sets_ranks[small]) {
            account_sets[small] = big;
            account_sets_ranks[big]++;
        } else {
            account_sets[big] = small;
            account_sets_ranks[small]++;
        }
    }

    void init_account_sets(int n) {
        for (int i = 0; i < n; ++i) {
            account_sets.push_back(i);
            account_sets_ranks.push_back(1);
        }
    }

  public:
    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts) {
        init_account_sets(accounts.size());
        for (int i = 0; i < accounts.size(); ++i) {
            sort(accounts[i].begin() + 1, accounts[i].end());
        }

        unordered_map<string, vector<int>> name_idx_map;
        for (int i = 0; i < accounts.size(); ++i) {
            if (name_idx_map.find(accounts[i][0]) == name_idx_map.end()) {
                name_idx_map[accounts[i][0]] = vector<int>();
                name_idx_map[accounts[i][0]].push_back(i);
            } else {
                name_idx_map[accounts[i][0]].push_back(i);
            }
        }

        vector<string> emails_intersection;
        for (auto name_idx : name_idx_map) {
            for (int i = 0; i < name_idx.second.size(); ++i) {
                for (int j = i + 1; j < name_idx.second.size(); ++j) {

                    int parent_i = account_sets_find(name_idx.second[i]);
                    int parent_j = account_sets_find(name_idx.second[j]);

                    if (parent_i == parent_j) {
                        continue;
                    }

                    set_intersection(accounts[name_idx.second[i]].begin() + 1,
                                     accounts[name_idx.second[i]].end(),
                                     accounts[name_idx.second[j]].begin() + 1,
                                     accounts[name_idx.second[j]].end(),
                                     back_inserter(emails_intersection));

                    if (!emails_intersection.empty()) {
                        account_sets_union(parent_i, parent_j);
                    }
                    emails_intersection.clear();
                }
            }
        }

        vector<vector<string>> ans;
        unordered_map<int, set<string>> merged_emails;
        set<string> emails;
        vector<string> merged;
        for (auto name_idx : name_idx_map) {
            for (int idx : name_idx.second) {
                int parent_idx = account_sets_find(idx);
                if (merged_emails.find(parent_idx) == merged_emails.end()) {

                    for (int i = 1; i < accounts[idx].size(); ++i) {
                        emails.insert(accounts[idx][i]);
                    }
                    merged_emails[parent_idx] = emails;
                    emails.clear();
                } else {
                    for (int i = 1; i < accounts[idx].size(); ++i) {
                        merged_emails[parent_idx].insert(accounts[idx][i]);
                    }
                }
            }

            for (auto emails : merged_emails) {
                merged.push_back(name_idx.first);

                for (string email : emails.second) {
                    merged.push_back(email);
                }

                ans.push_back(merged);
                merged.clear();
            }

            merged_emails.clear();
        }

        return ans;
    }
};

int main() {
    Solution sol;
    vector<vector<string>> res;

    vector<vector<string>> accounts1 = {{"David", "David5@m.co", "David8@m.co"},
                                        {"David", "David1@m.co", "David1@m.co", "David8@m.co"},
                                        {"David", "David0@m.co", "David0@m.co", "David5@m.co"}};
    res = sol.accountsMerge(accounts1);
    print2Dmatrix(res);

    vector<vector<string>> accounts2 = {{"John", "johnsmith@mail.com", "john_newyork@mail.com"},
                                        {"John", "johnsmith@mail.com", "john00@mail.com"},
                                        {"Mary", "mary@mail.com"},
                                        {"John", "johnnybravo@mail.com"}};
    res = sol.accountsMerge(accounts2);
    print2Dmatrix(res);

    vector<vector<string>> accounts3 = {{"Alex", "Alex5@m.co", "Alex4@m.co", "Alex0@m.co"},
                                        {"Ethan", "Ethan3@m.co", "Ethan3@m.co", "Ethan0@m.co"},
                                        {"Kevin", "Kevin4@m.co", "Kevin2@m.co", "Kevin2@m.co"},
                                        {"Gabe", "Gabe0@m.co", "Gabe3@m.co", "Gabe2@m.co"},
                                        {"Gabe", "Gabe3@m.co", "Gabe4@m.co", "Gabe2@m.co"}};
    res = sol.accountsMerge(accounts3);
    print2Dmatrix(res);

    vector<vector<string>> accounts4 = {{"David", "Avid0@m.co", "David0@m.co", "David1@m.co"},
                                        {"David", "Gvid3@m.co", "David3@m.co", "David4@m.co"},
                                        {"David", "David4@m.co", "David5@m.co"},
                                        {"David", "David2@m.co", "David3@m.co"},
                                        {"David", "David1@m.co", "David2@m.co"}};
    res = sol.accountsMerge(accounts4);
    print2Dmatrix(res);

    vector<vector<string>> accounts5 = {{"David", "David0@m.co", "David4@m.co", "David3@m.co"},
                                        {"David", "David5@m.co", "David5@m.co", "David0@m.co"},
                                        {"David", "David1@m.co", "David4@m.co", "David0@m.co"},
                                        {"David", "David0@m.co", "David1@m.co", "David3@m.co"},
                                        {"David", "David4@m.co", "David1@m.co", "David3@m.co"}};
    res = sol.accountsMerge(accounts5);
    print2Dmatrix(res);

    vector<vector<string>> accounts6 = {{"David", "David0@m.co", "David1@m.co"},
                                        {"David", "David3@m.co", "David4@m.co"},
                                        {"David", "David4@m.co", "David5@m.co"},
                                        {"David", "David2@m.co", "David3@m.co"},
                                        {"David", "David1@m.co", "David2@m.co"}};
    res = sol.accountsMerge(accounts6);
    print2Dmatrix(res);

    return 0;
}