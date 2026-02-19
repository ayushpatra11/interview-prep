/*
class : 2 functions: get and put

keeps track of anagrams: 

i/p string
o/p: anagrams of the string.

get:

10^9

eat
tea

aet

dog god

dgo


0-25 

int arr[26];

0#0#

1Dog

1oDg





key#val


1goD


0-9 0-9
a-z 10 - 35
A-Z 36 - 61


*/

#include <iostream>
#include<un


using namespace std;


class Anagrams{
    private: 
        unordered_map<string, vector<string>> groupOfAnagrams;

    public:
        string getKey(string word){

            // ab1
            vector<int> arr(62, 0);

            // 0-9 a-z
            //a -> 10 
            //b -> 11
            //1 -> 1
            for(char c: word){
                int tempVal;
                if(is_num(c)){
                    tempVal = c-'0';
                }
                else{
                    char temp = to_lower(c);
                    tempVal = temp-'a'+10;
                }
                arr[tempVal]++;
            }

            string key;

            for(int num: arr){
                key += num;
                key+= '#';
            }
            return key;
        }
        void putAnagram(string word){
            string key = getKey(word);

            groupOfAnagrams[key].push_back(word);
        }

        vector<string> getAnagrams(string word){
            string key = getKey(word);
            if(groupOfAnagrams.find(key) != groupOfAnagrams.end()){
                return groupOfAnagrams[key];
            }
            return {};
        }

}

int main(){
    return 0;
}