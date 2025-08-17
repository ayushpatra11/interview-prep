// execution context, hoisting, var/let/const, block scope

// call stack - each function call creates a new execution context
function outer() {
    console.log("outer start");
    inner();
    console.log("outer end");
}
function inner() {
    console.log("inner");
}
outer();

// var hoisting - declared as undefined before any code runs
console.log(typeof declared);  // undefined (hoisted, not initialised)
var declared = "value";

// function declarations are fully hoisted
greet("world");
function greet(name) {
    console.log("hello,", name);
}

// arrow functions assigned to var are NOT fully hoisted
// console.log(sayHi);  // undefined
// sayHi("x");          // TypeError: sayHi is not a function
var sayHi = (name) => console.log("hi,", name);

// let / const - hoisted but stay in temporal dead zone (TDZ)
// accessing before declaration throws ReferenceError, not undefined
{
    // console.log(x);  // ReferenceError: Cannot access 'x' before initialization
    let x = 10;
    console.log(x);    // 10
}

// block scope
{
    var leaked = "var leaks";
    let contained = "let stays";
}
console.log(leaked);      // "var leaks"
// console.log(contained); // ReferenceError

// shadowing with var vs let
var a = 100;
{
    var a = 10;       // same binding, overwrites
    console.log(a);   // 10
}
console.log(a);       // 10 - modified

let b = 100;
{
    let b = 10;       // new binding, shadows
    console.log(b);   // 10
}
console.log(b);       // 100 - original unchanged

// cannot shadow let with var inside a block
// let c = 1;
// { var c = 2; }  // SyntaxError: Identifier 'c' has already been declared

// undefined vs not-defined
var uninit;
console.log(uninit);   // undefined - declared, no value
// console.log(nope);  // ReferenceError: nope is not defined
