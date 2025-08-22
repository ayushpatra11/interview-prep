// higher order functions - map, filter, reduce

const users = [
    { name: 'Ayush', age: 25, dept: 'engineering' },
    { name: 'Alice', age: 30, dept: 'management' },
    { name: 'Bob',   age: 22, dept: 'engineering' },
    { name: 'Carol', age: 28, dept: 'design' },
    { name: 'Dave',  age: 26, dept: 'engineering' },
];

// map
const names = users.map(u => u.name);
console.log(names);

// filter
const engineers = users.filter(u => u.dept === 'engineering');
console.log(engineers.length);

// reduce - group by dept
const byDept = users.reduce((acc, u) => {
    if (!acc[u.dept]) acc[u.dept] = [];
    acc[u.dept].push(u.name);
    return acc;
}, {});
console.log(byDept);

// chaining
const avgAge = users
    .filter(u => u.dept === 'engineering')
    .map(u => u.age)
    .reduce((sum, age, _, arr) => sum + age / arr.length, 0);
console.log("avg engineer age:", avgAge);

// implementing map from scratch
Array.prototype.myMap = function(fn) {
    const out = [];
    for (let i = 0; i < this.length; i++) {
        out.push(fn(this[i], i, this));
    }
    return out;
};

console.log([1, 2, 3].myMap(x => x * x));

// function composition
const compose = (...fns) => x => fns.reduceRight((v, f) => f(v), x);
const pipe    = (...fns) => x => fns.reduce((v, f) => f(v), x);

const add1  = x => x + 1;
const mul2  = x => x * 2;
const sub3  = x => x - 3;

const transform = pipe(add1, mul2, sub3);
console.log(transform(5));  // (5+1)*2-3 = 9

// currying
function curry(fn) {
    return function curried(...args) {
        if (args.length >= fn.length) return fn(...args);
        return (...more) => curried(...args, ...more);
    };
}

const add = curry((a, b, c) => a + b + c);
console.log(add(1)(2)(3));
console.log(add(1, 2)(3));
console.log(add(1)(2, 3));
