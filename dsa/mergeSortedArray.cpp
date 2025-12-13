#include<iostream>
#include<vector>

using namespace std;

//Question: Merge two arrays till size K

//Example: 
//array 1: 4, 7, 9
//array 2: 1, 2, 6
//K = 6

//res = 1,2,4,6,7,9

vector<int> mergeSortedArrays(vector<int> a, vector<int> b, int K){
    // i = the index of a, j = index of b
    int i = 0, j = 0;
    vector<int> res;
    res.reserve(min<int>(K, a.size()+b.size()));
    int k = 0;
    while(res.size()<K && (i<a.size() || j<b.size())){
        if(i < a.size() && j < b.size()){
            if(a[i] <= b[j]){
                res.push_back(a[i]);
                i++;k++;
            }
            else{
                res.push_back(b[j]);
                j++;k++;
            }
        }
        else if(i < a.size()){
            res.push_back(a[i]);
            i++;k++;
        }
        else{
            res.push_back(b[j]);
            j++; k++;
        }
    }

    return res;
}

int main(){
    vector<int> a = {4, 7, 9};
    vector<int> b = {1, 2, 6};
    int k = 6;
    vector<int> res = mergeSortedArrays(a, b, k);
    for(int num: res)
        cout<<num<<endl;
    return 0;
}