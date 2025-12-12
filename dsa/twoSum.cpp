#include<iostream>
#include<unordered_map>

using namespace std;

vector<int> getTwoSum(vector<int> arr, int target){
    unordered_map<int, int> hashMap;
    int i = 0;
    for(int num: arr){
        if(hashMap.find(num) != hashMap.end()){
            return {hashMap[num], i};
        }
        hashMap[target-num] = i;
        i++;
    }
    return {-1, -1};
}

int main(){
    vector<int> arr = {3, 12, 4, 2, 1, 5};
    int target = 4;
    vector<int> ans = getTwoSum(arr, target);
    for(int num: ans)
        cout<<num<<endl;
    return 0;
}