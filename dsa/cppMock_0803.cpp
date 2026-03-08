/*

Array - Integers -> length of the longest consecutive sequence. 

linear time. 

Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.

set -> (100, 1, 200, 3, 4, 2) 


 check the next -> if present ; skip
 else : check prev, and keep checking till not present. 


 100 -> 101 not present. 
 99 -> not present

 var = 4

*/

#include<iostream>
#include<vector>
#include<unordered_set>

using namespace std;

class FindLongestSub{
    public:
    FindLongestSub(){}

    int findLongSub(vector<int> nums){
        int longestSubCount = 0;
        unordered_set<int> numsSet(nums.begin(), nums.end());

        /*
        Input: nums = [100,4,200,1,3,2]
        set = [100,4,200,1,3,2]

        */

        for(int num : nums){
            // to check whether next element is present 
            if(numsSet.find(num+1) != numsSet.end())
                continue;
            else{
                int numCheck = num - 1, currLongSub = 1;
                while(numsSet.find(numCheck) != numsSet.end()){
                    currLongSub++;
                    numCheck--;
                }
                longestSubCount = max(longestSubCount, currLongSub);
            }
        }

        return longestSubCount;
    }

};

int main(){
    FindLongestSub fls;

    cout<<fls.findLongSub({100, 4, 200, 3, 1, 2});
    return 0;
}