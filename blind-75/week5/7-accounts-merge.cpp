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

#include "bits/stdc++.h"
#include <iostream>
using namespace std;

template <typename T> void print2Dmatrix(vector<vector<T>> res) {
    if (res.empty()) {
        cout << "Empty!" << endl;
        return;
    }

    int r = res.size();
    int c = res[0].size();

    for (auto row : res) {
        for (auto val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << endl;
}

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

                    set_intersection(accounts[name_idx.second[i]].begin() + 1, accounts[name_idx.second[i]].end(),
                                     accounts[name_idx.second[j]].begin() + 1, accounts[name_idx.second[j]].end(),
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
                merged.push_back( name_idx.first);

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

    // vector<vector<string>> accounts1 = {{"David", "David5@m.co", "David8@m.co"},
    //                                     {"David", "David1@m.co", "David1@m.co", "David8@m.co"},
    //                                     {"David", "David0@m.co", "David0@m.co", "David5@m.co"}};
    // res = sol.accountsMerge(accounts1);
    // print2Dmatrix(res);

    // vector<vector<string>> accounts2 = {{"John", "johnsmith@mail.com", "john_newyork@mail.com"},
    //                                     {"John", "johnsmith@mail.com", "john00@mail.com"},
    //                                     {"Mary", "mary@mail.com"},
    //                                     {"John", "johnnybravo@mail.com"}};
    // res = sol.accountsMerge(accounts2);
    // print2Dmatrix(res);

    // vector<vector<string>> accounts3 = {{"Alex", "Alex5@m.co", "Alex4@m.co", "Alex0@m.co"},
    //                                     {"Ethan", "Ethan3@m.co", "Ethan3@m.co", "Ethan0@m.co"},
    //                                     {"Kevin", "Kevin4@m.co", "Kevin2@m.co", "Kevin2@m.co"},
    //                                     {"Gabe", "Gabe0@m.co", "Gabe3@m.co", "Gabe2@m.co"},
    //                                     {"Gabe", "Gabe3@m.co", "Gabe4@m.co", "Gabe2@m.co"}};
    // res = sol.accountsMerge(accounts3);
    // print2Dmatrix(res);

    vector<vector<string>> accounts4 = {
        {"Alex", "Alex25@m.co", "Alex225@m.co", "Alex226@m.co", "Alex227@m.co", "Alex228@m.co",
         "Alex229@m.co", "Alex230@m.co", "Alex231@m.co", "Alex232@m.co"},
        {"Alex", "Alex7@m.co", "Alex63@m.co", "Alex64@m.co", "Alex65@m.co", "Alex66@m.co",
         "Alex67@m.co", "Alex68@m.co", "Alex69@m.co", "Alex70@m.co"},
        {"Alex", "Alex41@m.co", "Alex369@m.co", "Alex370@m.co", "Alex371@m.co", "Alex372@m.co",
         "Alex373@m.co", "Alex374@m.co", "Alex375@m.co", "Alex376@m.co"},
        {"Alex", "Alex24@m.co", "Alex216@m.co", "Alex217@m.co", "Alex218@m.co", "Alex219@m.co",
         "Alex220@m.co", "Alex221@m.co", "Alex222@m.co", "Alex223@m.co"},
        {"Alex", "Alex20@m.co", "Alex180@m.co", "Alex181@m.co", "Alex182@m.co", "Alex183@m.co",
         "Alex184@m.co", "Alex185@m.co", "Alex186@m.co", "Alex187@m.co"},
        {"Alex", "Alex7@m.co", "Alex63@m.co", "Alex64@m.co", "Alex65@m.co", "Alex66@m.co",
         "Alex67@m.co", "Alex68@m.co", "Alex69@m.co", "Alex70@m.co"},
        {"Alex", "Alex30@m.co", "Alex270@m.co", "Alex271@m.co", "Alex272@m.co", "Alex273@m.co",
         "Alex274@m.co", "Alex275@m.co", "Alex276@m.co", "Alex277@m.co"},
        {"Alex", "Alex6@m.co", "Alex54@m.co", "Alex55@m.co", "Alex56@m.co", "Alex57@m.co",
         "Alex58@m.co", "Alex59@m.co", "Alex60@m.co", "Alex61@m.co"},
        {"Alex", "Alex46@m.co", "Alex414@m.co", "Alex415@m.co", "Alex416@m.co", "Alex417@m.co",
         "Alex418@m.co", "Alex419@m.co", "Alex420@m.co", "Alex421@m.co"},
        {"Alex", "Alex10@m.co", "Alex90@m.co", "Alex91@m.co", "Alex92@m.co", "Alex93@m.co",
         "Alex94@m.co", "Alex95@m.co", "Alex96@m.co", "Alex97@m.co"},
        {"Alex", "Alex58@m.co", "Alex522@m.co", "Alex523@m.co", "Alex524@m.co", "Alex525@m.co",
         "Alex526@m.co", "Alex527@m.co", "Alex528@m.co", "Alex529@m.co"},
        {"Alex", "Alex38@m.co", "Alex342@m.co", "Alex343@m.co", "Alex344@m.co", "Alex345@m.co",
         "Alex346@m.co", "Alex347@m.co", "Alex348@m.co", "Alex349@m.co"},
        {"Alex", "Alex11@m.co", "Alex99@m.co", "Alex100@m.co", "Alex101@m.co", "Alex102@m.co",
         "Alex103@m.co", "Alex104@m.co", "Alex105@m.co", "Alex106@m.co"},
        {"Alex", "Alex39@m.co", "Alex351@m.co", "Alex352@m.co", "Alex353@m.co", "Alex354@m.co",
         "Alex355@m.co", "Alex356@m.co", "Alex357@m.co", "Alex358@m.co"},
        {"Alex", "Alex19@m.co", "Alex171@m.co", "Alex172@m.co", "Alex173@m.co", "Alex174@m.co",
         "Alex175@m.co", "Alex176@m.co", "Alex177@m.co", "Alex178@m.co"},
        {"Alex", "Alex9@m.co", "Alex81@m.co", "Alex82@m.co", "Alex83@m.co", "Alex84@m.co",
         "Alex85@m.co", "Alex86@m.co", "Alex87@m.co", "Alex88@m.co"},
        {"Alex", "Alex66@m.co", "Alex594@m.co", "Alex595@m.co", "Alex596@m.co", "Alex597@m.co",
         "Alex598@m.co", "Alex599@m.co", "Alex600@m.co", "Alex601@m.co"},
        {"Alex", "Alex6@m.co", "Alex54@m.co", "Alex55@m.co", "Alex56@m.co", "Alex57@m.co",
         "Alex58@m.co", "Alex59@m.co", "Alex60@m.co", "Alex61@m.co"},
        {"Alex", "Alex19@m.co", "Alex171@m.co", "Alex172@m.co", "Alex173@m.co", "Alex174@m.co",
         "Alex175@m.co", "Alex176@m.co", "Alex177@m.co", "Alex178@m.co"},
        {"Alex", "Alex22@m.co", "Alex198@m.co", "Alex199@m.co", "Alex200@m.co", "Alex201@m.co",
         "Alex202@m.co", "Alex203@m.co", "Alex204@m.co", "Alex205@m.co"},
        {"Alex", "Alex5@m.co", "Alex45@m.co", "Alex46@m.co", "Alex47@m.co", "Alex48@m.co",
         "Alex49@m.co", "Alex50@m.co", "Alex51@m.co", "Alex52@m.co"},
        {"Alex", "Alex49@m.co", "Alex441@m.co", "Alex442@m.co", "Alex443@m.co", "Alex444@m.co",
         "Alex445@m.co", "Alex446@m.co", "Alex447@m.co", "Alex448@m.co"},
        {"Alex", "Alex50@m.co", "Alex450@m.co", "Alex451@m.co", "Alex452@m.co", "Alex453@m.co",
         "Alex454@m.co", "Alex455@m.co", "Alex456@m.co", "Alex457@m.co"},
        {"Alex", "Alex20@m.co", "Alex180@m.co", "Alex181@m.co", "Alex182@m.co", "Alex183@m.co",
         "Alex184@m.co", "Alex185@m.co", "Alex186@m.co", "Alex187@m.co"},
        {"Alex", "Alex25@m.co", "Alex225@m.co", "Alex226@m.co", "Alex227@m.co", "Alex228@m.co",
         "Alex229@m.co", "Alex230@m.co", "Alex231@m.co", "Alex232@m.co"},
        {"Alex", "Alex43@m.co", "Alex387@m.co", "Alex388@m.co", "Alex389@m.co", "Alex390@m.co",
         "Alex391@m.co", "Alex392@m.co", "Alex393@m.co", "Alex394@m.co"},
        {"Alex", "Alex36@m.co", "Alex324@m.co", "Alex325@m.co", "Alex326@m.co", "Alex327@m.co",
         "Alex328@m.co", "Alex329@m.co", "Alex330@m.co", "Alex331@m.co"},
        {"Alex", "Alex12@m.co", "Alex108@m.co", "Alex109@m.co", "Alex110@m.co", "Alex111@m.co",
         "Alex112@m.co", "Alex113@m.co", "Alex114@m.co", "Alex115@m.co"},
        {"Alex", "Alex0@m.co", "Alex0@m.co", "Alex1@m.co", "Alex2@m.co", "Alex3@m.co", "Alex4@m.co",
         "Alex5@m.co", "Alex6@m.co", "Alex7@m.co"},
        {"Alex", "Alex56@m.co", "Alex504@m.co", "Alex505@m.co", "Alex506@m.co", "Alex507@m.co",
         "Alex508@m.co", "Alex509@m.co", "Alex510@m.co", "Alex511@m.co"},
        {"Alex", "Alex23@m.co", "Alex207@m.co", "Alex208@m.co", "Alex209@m.co", "Alex210@m.co",
         "Alex211@m.co", "Alex212@m.co", "Alex213@m.co", "Alex214@m.co"},
        {"Alex", "Alex2@m.co", "Alex18@m.co", "Alex19@m.co", "Alex20@m.co", "Alex21@m.co",
         "Alex22@m.co", "Alex23@m.co", "Alex24@m.co", "Alex25@m.co"},
        {"Alex", "Alex2@m.co", "Alex18@m.co", "Alex19@m.co", "Alex20@m.co", "Alex21@m.co",
         "Alex22@m.co", "Alex23@m.co", "Alex24@m.co", "Alex25@m.co"},
        {"Alex", "Alex40@m.co", "Alex360@m.co", "Alex361@m.co", "Alex362@m.co", "Alex363@m.co",
         "Alex364@m.co", "Alex365@m.co", "Alex366@m.co", "Alex367@m.co"},
        {"Alex", "Alex13@m.co", "Alex117@m.co", "Alex118@m.co", "Alex119@m.co", "Alex120@m.co",
         "Alex121@m.co", "Alex122@m.co", "Alex123@m.co", "Alex124@m.co"},
        {"Alex", "Alex5@m.co", "Alex45@m.co", "Alex46@m.co", "Alex47@m.co", "Alex48@m.co",
         "Alex49@m.co", "Alex50@m.co", "Alex51@m.co", "Alex52@m.co"},
        {"Alex", "Alex27@m.co", "Alex243@m.co", "Alex244@m.co", "Alex245@m.co", "Alex246@m.co",
         "Alex247@m.co", "Alex248@m.co", "Alex249@m.co", "Alex250@m.co"},
        {"Alex", "Alex1@m.co", "Alex9@m.co", "Alex10@m.co", "Alex11@m.co", "Alex12@m.co",
         "Alex13@m.co", "Alex14@m.co", "Alex15@m.co", "Alex16@m.co"},
        {"Alex", "Alex23@m.co", "Alex207@m.co", "Alex208@m.co", "Alex209@m.co", "Alex210@m.co",
         "Alex211@m.co", "Alex212@m.co", "Alex213@m.co", "Alex214@m.co"},
        {"Alex", "Alex70@m.co", "Alex630@m.co", "Alex631@m.co", "Alex632@m.co", "Alex633@m.co",
         "Alex634@m.co", "Alex635@m.co", "Alex636@m.co", "Alex637@m.co"},
        {"Alex", "Alex32@m.co", "Alex288@m.co", "Alex289@m.co", "Alex290@m.co", "Alex291@m.co",
         "Alex292@m.co", "Alex293@m.co", "Alex294@m.co", "Alex295@m.co"},
        {"Alex", "Alex7@m.co", "Alex63@m.co", "Alex64@m.co", "Alex65@m.co", "Alex66@m.co",
         "Alex67@m.co", "Alex68@m.co", "Alex69@m.co", "Alex70@m.co"},
        {"Alex", "Alex2@m.co", "Alex18@m.co", "Alex19@m.co", "Alex20@m.co", "Alex21@m.co",
         "Alex22@m.co", "Alex23@m.co", "Alex24@m.co", "Alex25@m.co"},
        {"Alex", "Alex67@m.co", "Alex603@m.co", "Alex604@m.co", "Alex605@m.co", "Alex606@m.co",
         "Alex607@m.co", "Alex608@m.co", "Alex609@m.co", "Alex610@m.co"},
        {"Alex", "Alex55@m.co", "Alex495@m.co", "Alex496@m.co", "Alex497@m.co", "Alex498@m.co",
         "Alex499@m.co", "Alex500@m.co", "Alex501@m.co", "Alex502@m.co"},
        {"Alex", "Alex48@m.co", "Alex432@m.co", "Alex433@m.co", "Alex434@m.co", "Alex435@m.co",
         "Alex436@m.co", "Alex437@m.co", "Alex438@m.co", "Alex439@m.co"},
        {"Alex", "Alex28@m.co", "Alex252@m.co", "Alex253@m.co", "Alex254@m.co", "Alex255@m.co",
         "Alex256@m.co", "Alex257@m.co", "Alex258@m.co", "Alex259@m.co"},
        {"Alex", "Alex1@m.co", "Alex9@m.co", "Alex10@m.co", "Alex11@m.co", "Alex12@m.co",
         "Alex13@m.co", "Alex14@m.co", "Alex15@m.co", "Alex16@m.co"},
        {"Alex", "Alex47@m.co", "Alex423@m.co", "Alex424@m.co", "Alex425@m.co", "Alex426@m.co",
         "Alex427@m.co", "Alex428@m.co", "Alex429@m.co", "Alex430@m.co"},
        {"Alex", "Alex57@m.co", "Alex513@m.co", "Alex514@m.co", "Alex515@m.co", "Alex516@m.co",
         "Alex517@m.co", "Alex518@m.co", "Alex519@m.co", "Alex520@m.co"},
        {"Alex", "Alex9@m.co", "Alex81@m.co", "Alex82@m.co", "Alex83@m.co", "Alex84@m.co",
         "Alex85@m.co", "Alex86@m.co", "Alex87@m.co", "Alex88@m.co"},
        {"Alex", "Alex10@m.co", "Alex90@m.co", "Alex91@m.co", "Alex92@m.co", "Alex93@m.co",
         "Alex94@m.co", "Alex95@m.co", "Alex96@m.co", "Alex97@m.co"},
        {"Alex", "Alex1@m.co", "Alex9@m.co", "Alex10@m.co", "Alex11@m.co", "Alex12@m.co",
         "Alex13@m.co", "Alex14@m.co", "Alex15@m.co", "Alex16@m.co"},
        {"Alex", "Alex16@m.co", "Alex144@m.co", "Alex145@m.co", "Alex146@m.co", "Alex147@m.co",
         "Alex148@m.co", "Alex149@m.co", "Alex150@m.co", "Alex151@m.co"},
        {"Alex", "Alex4@m.co", "Alex36@m.co", "Alex37@m.co", "Alex38@m.co", "Alex39@m.co",
         "Alex40@m.co", "Alex41@m.co", "Alex42@m.co", "Alex43@m.co"},
        {"Alex", "Alex28@m.co", "Alex252@m.co", "Alex253@m.co", "Alex254@m.co", "Alex255@m.co",
         "Alex256@m.co", "Alex257@m.co", "Alex258@m.co", "Alex259@m.co"},
        {"Alex", "Alex29@m.co", "Alex261@m.co", "Alex262@m.co", "Alex263@m.co", "Alex264@m.co",
         "Alex265@m.co", "Alex266@m.co", "Alex267@m.co", "Alex268@m.co"},
        {"Alex", "Alex42@m.co", "Alex378@m.co", "Alex379@m.co", "Alex380@m.co", "Alex381@m.co",
         "Alex382@m.co", "Alex383@m.co", "Alex384@m.co", "Alex385@m.co"},
        {"Alex", "Alex18@m.co", "Alex162@m.co", "Alex163@m.co", "Alex164@m.co", "Alex165@m.co",
         "Alex166@m.co", "Alex167@m.co", "Alex168@m.co", "Alex169@m.co"},
        {"Alex", "Alex51@m.co", "Alex459@m.co", "Alex460@m.co", "Alex461@m.co", "Alex462@m.co",
         "Alex463@m.co", "Alex464@m.co", "Alex465@m.co", "Alex466@m.co"},
        {"Alex", "Alex37@m.co", "Alex333@m.co", "Alex334@m.co", "Alex335@m.co", "Alex336@m.co",
         "Alex337@m.co", "Alex338@m.co", "Alex339@m.co", "Alex340@m.co"},
        {"Alex", "Alex29@m.co", "Alex261@m.co", "Alex262@m.co", "Alex263@m.co", "Alex264@m.co",
         "Alex265@m.co", "Alex266@m.co", "Alex267@m.co", "Alex268@m.co"},
        {"Alex", "Alex27@m.co", "Alex243@m.co", "Alex244@m.co", "Alex245@m.co", "Alex246@m.co",
         "Alex247@m.co", "Alex248@m.co", "Alex249@m.co", "Alex250@m.co"},
        {"Alex", "Alex6@m.co", "Alex54@m.co", "Alex55@m.co", "Alex56@m.co", "Alex57@m.co",
         "Alex58@m.co", "Alex59@m.co", "Alex60@m.co", "Alex61@m.co"},
        {"Alex", "Alex34@m.co", "Alex306@m.co", "Alex307@m.co", "Alex308@m.co", "Alex309@m.co",
         "Alex310@m.co", "Alex311@m.co", "Alex312@m.co", "Alex313@m.co"},
        {"Alex", "Alex59@m.co", "Alex531@m.co", "Alex532@m.co", "Alex533@m.co", "Alex534@m.co",
         "Alex535@m.co", "Alex536@m.co", "Alex537@m.co", "Alex538@m.co"},
        {"Alex", "Alex31@m.co", "Alex279@m.co", "Alex280@m.co", "Alex281@m.co", "Alex282@m.co",
         "Alex283@m.co", "Alex284@m.co", "Alex285@m.co", "Alex286@m.co"},
        {"Alex", "Alex3@m.co", "Alex27@m.co", "Alex28@m.co", "Alex29@m.co", "Alex30@m.co",
         "Alex31@m.co", "Alex32@m.co", "Alex33@m.co", "Alex34@m.co"},
        {"Alex", "Alex16@m.co", "Alex144@m.co", "Alex145@m.co", "Alex146@m.co", "Alex147@m.co",
         "Alex148@m.co", "Alex149@m.co", "Alex150@m.co", "Alex151@m.co"},
        {"Alex", "Alex11@m.co", "Alex99@m.co", "Alex100@m.co", "Alex101@m.co", "Alex102@m.co",
         "Alex103@m.co", "Alex104@m.co", "Alex105@m.co", "Alex106@m.co"},
        {"Alex", "Alex3@m.co", "Alex27@m.co", "Alex28@m.co", "Alex29@m.co", "Alex30@m.co",
         "Alex31@m.co", "Alex32@m.co", "Alex33@m.co", "Alex34@m.co"},
        {"Alex", "Alex54@m.co", "Alex486@m.co", "Alex487@m.co", "Alex488@m.co", "Alex489@m.co",
         "Alex490@m.co", "Alex491@m.co", "Alex492@m.co", "Alex493@m.co"},
        {"Alex", "Alex60@m.co", "Alex540@m.co", "Alex541@m.co", "Alex542@m.co", "Alex543@m.co",
         "Alex544@m.co", "Alex545@m.co", "Alex546@m.co", "Alex547@m.co"},
        {"Alex", "Alex14@m.co", "Alex126@m.co", "Alex127@m.co", "Alex128@m.co", "Alex129@m.co",
         "Alex130@m.co", "Alex131@m.co", "Alex132@m.co", "Alex133@m.co"},
        {"Alex", "Alex22@m.co", "Alex198@m.co", "Alex199@m.co", "Alex200@m.co", "Alex201@m.co",
         "Alex202@m.co", "Alex203@m.co", "Alex204@m.co", "Alex205@m.co"},
        {"Alex", "Alex61@m.co", "Alex549@m.co", "Alex550@m.co", "Alex551@m.co", "Alex552@m.co",
         "Alex553@m.co", "Alex554@m.co", "Alex555@m.co", "Alex556@m.co"},
        {"Alex", "Alex68@m.co", "Alex612@m.co", "Alex613@m.co", "Alex614@m.co", "Alex615@m.co",
         "Alex616@m.co", "Alex617@m.co", "Alex618@m.co", "Alex619@m.co"},
        {"Alex", "Alex14@m.co", "Alex126@m.co", "Alex127@m.co", "Alex128@m.co", "Alex129@m.co",
         "Alex130@m.co", "Alex131@m.co", "Alex132@m.co", "Alex133@m.co"},
        {"Alex", "Alex63@m.co", "Alex567@m.co", "Alex568@m.co", "Alex569@m.co", "Alex570@m.co",
         "Alex571@m.co", "Alex572@m.co", "Alex573@m.co", "Alex574@m.co"},
        {"Alex", "Alex0@m.co", "Alex0@m.co", "Alex1@m.co", "Alex2@m.co", "Alex3@m.co", "Alex4@m.co",
         "Alex5@m.co", "Alex6@m.co", "Alex7@m.co"},
        {"Alex", "Alex33@m.co", "Alex297@m.co", "Alex298@m.co", "Alex299@m.co", "Alex300@m.co",
         "Alex301@m.co", "Alex302@m.co", "Alex303@m.co", "Alex304@m.co"},
        {"Alex", "Alex24@m.co", "Alex216@m.co", "Alex217@m.co", "Alex218@m.co", "Alex219@m.co",
         "Alex220@m.co", "Alex221@m.co", "Alex222@m.co", "Alex223@m.co"},
        {"Alex", "Alex21@m.co", "Alex189@m.co", "Alex190@m.co", "Alex191@m.co", "Alex192@m.co",
         "Alex193@m.co", "Alex194@m.co", "Alex195@m.co", "Alex196@m.co"},
        {"Alex", "Alex15@m.co", "Alex135@m.co", "Alex136@m.co", "Alex137@m.co", "Alex138@m.co",
         "Alex139@m.co", "Alex140@m.co", "Alex141@m.co", "Alex142@m.co"},
        {"Alex", "Alex5@m.co", "Alex45@m.co", "Alex46@m.co", "Alex47@m.co", "Alex48@m.co",
         "Alex49@m.co", "Alex50@m.co", "Alex51@m.co", "Alex52@m.co"},
        {"Alex", "Alex4@m.co", "Alex36@m.co", "Alex37@m.co", "Alex38@m.co", "Alex39@m.co",
         "Alex40@m.co", "Alex41@m.co", "Alex42@m.co", "Alex43@m.co"},
        {"Alex", "Alex21@m.co", "Alex189@m.co", "Alex190@m.co", "Alex191@m.co", "Alex192@m.co",
         "Alex193@m.co", "Alex194@m.co", "Alex195@m.co", "Alex196@m.co"},
        {"Alex", "Alex52@m.co", "Alex468@m.co", "Alex469@m.co", "Alex470@m.co", "Alex471@m.co",
         "Alex472@m.co", "Alex473@m.co", "Alex474@m.co", "Alex475@m.co"},
        {"Alex", "Alex3@m.co", "Alex27@m.co", "Alex28@m.co", "Alex29@m.co", "Alex30@m.co",
         "Alex31@m.co", "Alex32@m.co", "Alex33@m.co", "Alex34@m.co"},
        {"Alex", "Alex12@m.co", "Alex108@m.co", "Alex109@m.co", "Alex110@m.co", "Alex111@m.co",
         "Alex112@m.co", "Alex113@m.co", "Alex114@m.co", "Alex115@m.co"},
        {"Alex", "Alex69@m.co", "Alex621@m.co", "Alex622@m.co", "Alex623@m.co", "Alex624@m.co",
         "Alex625@m.co", "Alex626@m.co", "Alex627@m.co", "Alex628@m.co"},
        {"Alex", "Alex0@m.co", "Alex0@m.co", "Alex1@m.co", "Alex2@m.co", "Alex3@m.co", "Alex4@m.co",
         "Alex5@m.co", "Alex6@m.co", "Alex7@m.co"},
        {"Alex", "Alex4@m.co", "Alex36@m.co", "Alex37@m.co", "Alex38@m.co", "Alex39@m.co",
         "Alex40@m.co", "Alex41@m.co", "Alex42@m.co", "Alex43@m.co"},
        {"Alex", "Alex65@m.co", "Alex585@m.co", "Alex586@m.co", "Alex587@m.co", "Alex588@m.co",
         "Alex589@m.co", "Alex590@m.co", "Alex591@m.co", "Alex592@m.co"},
        {"Alex", "Alex0@m.co", "Alex0@m.co", "Alex1@m.co", "Alex2@m.co", "Alex3@m.co", "Alex4@m.co",
         "Alex5@m.co", "Alex6@m.co", "Alex7@m.co"},
        {"Alex", "Alex15@m.co", "Alex135@m.co", "Alex136@m.co", "Alex137@m.co", "Alex138@m.co",
         "Alex139@m.co", "Alex140@m.co", "Alex141@m.co", "Alex142@m.co"},
        {"Alex", "Alex18@m.co", "Alex162@m.co", "Alex163@m.co", "Alex164@m.co", "Alex165@m.co",
         "Alex166@m.co", "Alex167@m.co", "Alex168@m.co", "Alex169@m.co"},
        {"Alex", "Alex64@m.co", "Alex576@m.co", "Alex577@m.co", "Alex578@m.co", "Alex579@m.co",
         "Alex580@m.co", "Alex581@m.co", "Alex582@m.co", "Alex583@m.co"},
        {"Alex", "Alex45@m.co", "Alex405@m.co", "Alex406@m.co", "Alex407@m.co", "Alex408@m.co",
         "Alex409@m.co", "Alex410@m.co", "Alex411@m.co", "Alex412@m.co"},
        {"Alex", "Alex13@m.co", "Alex117@m.co", "Alex118@m.co", "Alex119@m.co", "Alex120@m.co",
         "Alex121@m.co", "Alex122@m.co", "Alex123@m.co", "Alex124@m.co"}};
    // res = sol.accountsMerge(accounts4);
    // print2Dmatrix(res);

    // vector<vector<string>> accounts5 = {{"David", "David0@m.co", "David4@m.co", "David3@m.co"},
    //                                     {"David", "David5@m.co", "David5@m.co", "David0@m.co"},
    //                                     {"David", "David1@m.co", "David4@m.co", "David0@m.co"},
    //                                     {"David", "David0@m.co", "David1@m.co", "David3@m.co"},
    //                                     {"David", "David4@m.co", "David1@m.co", "David3@m.co"}};
    // res = sol.accountsMerge(accounts5);
    // print2Dmatrix(res);

    // vector<vector<string>> accounts6 = {{"David", "David0@m.co", "David1@m.co"},
    //                                     {"David", "David3@m.co", "David4@m.co"},
    //                                     {"David", "David4@m.co", "David5@m.co"},
    //                                     {"David", "David2@m.co", "David3@m.co"},
    //                                     {"David", "David1@m.co", "David2@m.co"}};
    // res = sol.accountsMerge(accounts6);
    // print2Dmatrix(res);

    vector<vector<string>> accounts7 = {{"David", "Avid0@m.co", "David0@m.co", "David1@m.co"},
                                        {"David", "Gvid3@m.co", "David3@m.co", "David4@m.co"},
                                        {"David", "David4@m.co", "David5@m.co"},
                                        {"David", "David2@m.co", "David3@m.co"},
                                        {"David", "David1@m.co", "David2@m.co"}};
    res = sol.accountsMerge(accounts7);
    print2Dmatrix(res);

    return 0;
}