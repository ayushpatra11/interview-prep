/* 

Question: 

0 - indexed array
each element : [0-9]

triangular sum : 

newNums[i] = nums[i]+nums[i+1] % 10;

5000

*/

// 1, 4, 5, 6, 8, 9
// 5  9  1  4  7 
// 4  0  5  1
// 4  5  6
// 9  1
// 0

//left = 5

#include<iostream>
#include<vector>

using namespace std;

int triangularSum(vector<int> arr){
    int size = arr.size();
    int k=1;
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size-k; j++){
            arr[j] += arr[j+1];
            arr[j]%=10;
        }
        k++;
    }
    return (int)arr[0];
}

int main(){

    vector<int> arr = {5};

    int ans = triangularSum(arr);

    cout<<ans<<endl;
    return 0;
}

// 1, 2, 3, 4, 5

// 3   5   7   9
//   8   2   6

//     0    8
// 8