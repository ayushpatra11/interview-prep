// closures and scope practice

// basic closure
function counter() {
    let count = 0;
    return function() {
        return ++count;
    };
}

const inc = counter();
console.log(inc()); // 1
console.log(inc()); // 2

// loop with var vs let gotcha
function varLoop() {
    for (var i = 0; i < 3; i++) {
        setTimeout(function() { console.log(i); }, 100);
    }
    // prints 3 3 3 - var is not block scoped
}

function letLoop() {
    for (let i = 0; i < 3; i++) {
        setTimeout(function() { console.log(i); }, 100);
    }
    // prints 0 1 2 - let is block scoped, each iteration gets its own binding
}

varLoop();
letLoop();

// memoize
function memoize(fn) {
    const cache = {};
    return function(...args) {
        const key = JSON.stringify(args);
        if (key in cache) return cache[key];
        cache[key] = fn(...args);
        return cache[key];
    };
}

function fib(n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}

const memoFib = memoize(fib);
console.log(memoFib(10));

// IIFE
(function() {
    const x = 10;
    console.log("IIFE, x =", x);
})();

// closure factory
function makeMultiplier(factor) {
    return (num) => num * factor;
}

const double = makeMultiplier(2);
const triple = makeMultiplier(3);
console.log(double(5), triple(5));
