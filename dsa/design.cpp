// top K frequent elements, bank account system design

#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <iostream>
using namespace std;

// top K frequent - bucket sort O(n)
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int,int> freq;
    for (int n : nums) freq[n]++;
    vector<vector<int>> buckets(nums.size() + 1);
    for (auto& [num, cnt] : freq) buckets[cnt].push_back(num);
    vector<int> out;
    for (int i = (int)buckets.size()-1; i >= 0 && (int)out.size() < k; i--)
        for (int n : buckets[i]) if ((int)out.size() < k) out.push_back(n);
    return out;
}

class BankAccount {
    int id; double balance;
public:
    BankAccount(int id, double init=0) : id(id), balance(init) {}
    void deposit(double amt) {
        if (amt <= 0) throw invalid_argument("positive amount required");
        balance += amt;
    }
    void withdraw(double amt) {
        if (amt > balance) throw runtime_error("insufficient funds");
        balance -= amt;
    }
    double getBalance() const { return balance; }
};

class Bank {
    unordered_map<int, BankAccount*> accs;
    int nextId = 1;
public:
    ~Bank() { for (auto& [id,a] : accs) delete a; }
    int createAccount(double init=0) {
        int id = nextId++;
        accs[id] = new BankAccount(id, init);
        return id;
    }
    void transfer(int from, int to, double amt) {
        if (!accs.count(from) || !accs.count(to))
            throw invalid_argument("account not found");
        accs[from]->withdraw(amt);
        accs[to]->deposit(amt);
    }
    double getBalance(int id) { return accs.at(id)->getBalance(); }
};

int main() {
    vector<int> nums = {1,1,1,2,2,3};
    auto r = topKFrequent(nums, 2);
    for (int x : r) cout << x << " "; cout << "\n";  // 1 2

    Bank bank;
    int a = bank.createAccount(1000), b = bank.createAccount(500);
    bank.transfer(a, b, 200);
    cout << bank.getBalance(a) << " " << bank.getBalance(b) << "\n";  // 800 700
    return 0;
}
