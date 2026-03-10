#include<iostream>
#include<algorithm>


using namespace std;

/*

There are a total of numCourses courses you have to take, 
labeled from 0 to numCourses - 1. You are given an array prerequisites 
where prerequisites[i] = [ai, bi] indicates that you must take course bi 
first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you 
have to first take course 1.

Return true if you can finish all courses. Otherwise, return false.

Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So it is possible.

*/

class CourseSchedule{
public:

    bool checkCourseSchedule(vector<vector<int>> coursePairs, int numCourses){
        vector<vector<int>> adjList(numCourses, vector<int>());
        vector<int> indegree(numCourses);

        for(auto& coursePair : coursePairs){
            int coursePrereq = coursePair[1];
            int course = coursePair[0];
            adjList[coursePrereq].push_back(course);
            indegree[course]++;
        }

        queue<int> q;
        
        //now start BFS from all the indegree 0 ones. 

        for(int i = 0; i<numCourses; i++){
            if(indegree[i] == 0)
            q.push(i);
        }
        
        vector<int> topoSort;

        while(!q.empty()){
            int coursePrereq = q.front();
            topoSort.push_back(coursePrereq);
            q.pop();
            for(int course : adjList[coursePrereq]){
                indegree[course]--;
                if(indegree[course] == 0){
                    q.push(course);
                }
            }
        }

        return numCourses == topoSort.size();
    }

};


#include<shared_mutex>

class RingBuffer{
    vector<int> ringBuffer;
    int start;
    int end;
    int maxCapacity;
    int currentOcc;
    mutex ringBufferLock;

public:
    RingBuffer() : maxCapacity(0), start(0), end(0), currentOcc(0){}
    RingBuffer(int maxCapacity) : maxCapacity(maxCapacity), start(0), end(0), currentOcc(0){
        ringBuffer = vector<int>(maxCapacity); // inits every to 0;
    }

    //addToBuffer

    void readFromBuffer(int numOfElems, vector<int>& readBuffer){
        lock_guard<mutex> lock(ringBufferLock);
        if (maxCapacity == 0) return;
        int elementsToBeRead = min(numOfElems, currentOcc);
        // start marks the start of ring buffer.
        while(elementsToBeRead > 0){
            readBuffer.push_back(ringBuffer[start]);
            start = (start+1) % maxCapacity;
            elementsToBeRead--;
            currentOcc--;
        }
    }

    // writeToBuffer -> num of elements inserted. 

    int writeToBuffer(const vector<int>& writeBuffer){
        lock_guard<mutex> lock(ringBufferLock);
        if (maxCapacity == 0) return 0;
        int numElementsToBeWritten = min(int(writeBuffer.size()), maxCapacity - currentOcc);
        int elementsWritten = 0;
        while(elementsWritten < numElementsToBeWritten){
            ringBuffer[end] = writeBuffer[elementsWritten];
            end = (end+1) % maxCapacity;
            elementsWritten++;
            currentOcc++;
        }
        return numElementsToBeWritten;
    }

    ~RingBuffer(){}
};

int main(){
    

    return 0;
}