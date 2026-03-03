#include<iostream>
#include<unordered_map>
#include<ctime>
#include<algorithm>


using namespace std;

/*

Writing code for the rate limiter LLD. 

Requirements:

1/ Should be able to switch between different Algos. 
2/ Should be rate limiting based on the client ID and more. 
3/ The rate limiter should be configurable for a particular limit. 
4/ The rate limiter sould be thread safe

*/

enum class HTTP_CODES{
    SUCCESS = 200,
    FAILURE = 429
};

// abstract class for the algorithms
class RateLimitAlgo{
    public:
    virtual HTTP_CODES allow(int clientID) = 0;
};


// class for the token bucket algo

//      - class for the bucket that will be used within the algo

class Bucket{
    time_t timeOfLastFill;
    int rateOfRefill;
    int currentTokens;
    int maxCapacity;
public:

    Bucket(): maxCapacity(300), currentTokens(300), rateOfRefill(5){}

    Bucket(int maxCapacity, int rateOfRefill) : currentTokens(maxCapacity), maxCapacity(maxCapacity), rateOfRefill(rateOfRefill){
        timeOfLastFill = time(NULL);    // check if this is correct. 
    }

    void updateBucket(time_t timeOfUpdate){
        currentTokens = min(int(difftime(timeOfUpdate, timeOfLastFill))*rateOfRefill+currentTokens, maxCapacity);
        timeOfLastFill = timeOfUpdate;
    }

    HTTP_CODES allow(time_t timeOfReq){
        updateBucket(timeOfReq);
        if(currentTokens > 0){
            currentTokens--;
            return HTTP_CODES::SUCCESS;
        }
        return HTTP_CODES::FAILURE;
    }
};

class TokenBucketAlgo : public RateLimitAlgo {
    unordered_map<int, Bucket> algoMap;
    int maxCapacity;
    int refillRate;
public:

    TokenBucketAlgo(int maxCapacity, int refillRate): maxCapacity(maxCapacity), refillRate(refillRate){
        // no action required
    }

    HTTP_CODES allow(int clientID){
        // if client is alread present, then call the allow function for that in 
        // the bucket object. 
        
        time_t timeOfReq = time(NULL);  // check if this is how time is calculated 

        if(algoMap.find(clientID) != algoMap.end()){
            Bucket& clientBucket = algoMap[clientID];
            return clientBucket.allow(timeOfReq);
        }

        // if not present already then, create bucket and call allow. 
        
        
        algoMap.insert({clientID, Bucket(maxCapacity, refillRate)});
        return algoMap[clientID].allow(timeOfReq);
    }

};

// class for the sliding window algo

// class for the rate limiter that will be exposed to the client. 

class RateLimiter{
    RateLimitAlgo& rateLimitAlgo;
public:

    RateLimiter(RateLimitAlgo& algo) : rateLimitAlgo(algo){
    }
    HTTP_CODES allow(int clientID){
        return rateLimitAlgo.allow(clientID);
    }
};

//driver code. 

int main(){
    TokenBucketAlgo tl(5, 3);
    RateLimiter rl(tl);

    cout<<int(rl.allow(123))<<endl;
    cout<<int(rl.allow(123))<<endl;
    cout<<int(rl.allow(123))<<endl;
    cout<<int(rl.allow(123))<<endl;
    cout<<int(rl.allow(123))<<endl;
    cout<<int(rl.allow(123))<<endl;
    cout<<int(rl.allow(123))<<endl;
    cout<<int(rl.allow(123))<<endl;

    return 0;
}