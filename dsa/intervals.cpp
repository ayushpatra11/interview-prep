// merge intervals, meeting rooms II

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

// merge overlapping intervals - sort then scan
vector<vector<int>> merge(vector<vector<int>>& iv) {
    sort(iv.begin(), iv.end());
    vector<vector<int>> out = {iv[0]};
    for (int i = 1; i < (int)iv.size(); i++) {
        if (iv[i][0] <= out.back()[1])
            out.back()[1] = max(out.back()[1], iv[i][1]);
        else
            out.push_back(iv[i]);
    }
    return out;
}

// minimum rooms for meetings - two pointer on sorted starts/ends
int minMeetingRooms(vector<vector<int>>& iv) {
    int n = iv.size();
    vector<int> starts(n), ends(n);
    for (int i = 0; i < n; i++) { starts[i] = iv[i][0]; ends[i] = iv[i][1]; }
    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());
    int rooms = 0, maxR = 0, j = 0;
    for (int i = 0; i < n; i++) {
        if (starts[i] < ends[j]) rooms++;
        else j++;
        maxR = max(maxR, rooms);
    }
    return maxR;
}

int main() {
    vector<vector<int>> iv = {{1,3},{2,6},{8,10},{15,18}};
    auto r = merge(iv);
    for (auto& v : r) cout << "[" << v[0] << "," << v[1] << "] ";
    cout << "\n";  // [1,6] [8,10] [15,18]

    vector<vector<int>> m = {{0,30},{5,10},{15,20}};
    cout << minMeetingRooms(m) << "\n";  // 2
    return 0;
}
