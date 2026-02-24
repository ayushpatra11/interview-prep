#include <iostream>
#include <unordered_map>
#include <chrono>
#include <algorithm>
#include <memory>
#include <mutex>

// Abstract base class for rate limiter algorithms
class RateLimiterAlgorithm {
public:
    virtual bool allow(const std::string& userID) = 0;
    virtual ~RateLimiterAlgorithm() = default;
};

// Token Bucket Algorithm
class TokenBucketAlgorithm : public RateLimiterAlgorithm {
private:
    int maxCapacity;
    int refillRate;
    int refillInterval; // in seconds
    std::unordered_map<std::string, int> buckets;               // userID -> tokens
    std::unordered_map<std::string, std::chrono::steady_clock::time_point> lastRefillTime; // userID -> last refill time
    std::mutex mtx; // thread safety

    void createNewBucket(const std::string& userID) {
        buckets[userID] = maxCapacity;
        lastRefillTime[userID] = std::chrono::steady_clock::now();
    }

    void updateBucket(const std::string& userID) {
        auto now = std::chrono::steady_clock::now();
        auto timeDiff = std::chrono::duration_cast<std::chrono::seconds>(now - lastRefillTime[userID]).count();
        int newTokens = (timeDiff / refillInterval) * refillRate;
        buckets[userID] = std::min(buckets[userID] + newTokens, maxCapacity);
        lastRefillTime[userID] = now;
    }

public:
    TokenBucketAlgorithm(int refillRate, int refillInterval, int maxCapacity)
        : refillRate(refillRate), refillInterval(refillInterval), maxCapacity(maxCapacity) {}

    bool allow(const std::string& userID) override {
        std::lock_guard<std::mutex> lock(mtx);

        if (buckets.find(userID) == buckets.end()) {
            createNewBucket(userID);
            buckets[userID] -= 1;
            return true;
        }

        updateBucket(userID);
        if (buckets[userID] > 0) {
            buckets[userID] -= 1;
            return true;
        }

        return false;
    }
};

// Sliding Window Algorithm (stub)
class SlidingWindowAlgorithm : public RateLimiterAlgorithm {
private:
    int limit;
public:
    SlidingWindowAlgorithm(int limit) : limit(limit) {}

    bool allow(const std::string& userID) override {
        // Implementation pending
        return true;
    }
};

// Rate Limiter class
class RateLimiterClass {
private:
    std::shared_ptr<RateLimiterAlgorithm> rateLimitAlgo;
public:
    RateLimiterClass(std::shared_ptr<RateLimiterAlgorithm> algo) : rateLimitAlgo(algo) {}

    bool allow(const std::string& userID) {
        return rateLimitAlgo->allow(userID);
    }

    void changeAlgorithm(std::shared_ptr<RateLimiterAlgorithm> newAlgo) {
        rateLimitAlgo = newAlgo;
    }
};

// Example driver
int main() {
    auto tokenBucket = std::make_shared<TokenBucketAlgorithm>(5, 1, 10); // refillRate=5, refillInterval=1s, maxCapacity=10
    RateLimiterClass rateLimiter(tokenBucket);

    std::string user = "user1";

    for (int i = 0; i < 15; ++i) {
        bool allowed = rateLimiter.allow(user);
        std::cout << "Request " << i+1 << " allowed? " << (allowed ? "Yes" : "No") << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    return 0;
}