// this keyword, call/apply/bind, prototype chain, class syntax

// this depends on how a function is called, not where it's defined
const obj = {
    name: "Ayush",
    greet() {
        return `hello from ${this.name}`;
    },
    greetArrow: () => {
        // arrow functions capture 'this' from enclosing lexical scope
        // at top level, this === globalThis (undefined in strict mode)
        return `arrow: ${typeof this === "undefined" ? "undefined" : this.name}`;
    }
};

console.log(obj.greet());       // hello from Ayush
console.log(obj.greetArrow());  // arrow: undefined (no own this)

// call / apply / bind
function introduce(greeting, punct) {
    return `${greeting}, I am ${this.name}${punct}`;
}

const person = { name: "Ayush" };
console.log(introduce.call(person, "Hi", "!"));       // Hi, I am Ayush!
console.log(introduce.apply(person, ["Hey", "."]));    // Hey, I am Ayush.
const boundFn = introduce.bind(person, "Hello");
console.log(boundFn("?"));                            // Hello, I am Ayush?

// implementing bind from scratch
Function.prototype.myBind = function(ctx, ...preset) {
    const fn = this;
    return function(...args) {
        return fn.apply(ctx, [...preset, ...args]);
    };
};

const myBoundFn = introduce.myBind(person, "Hey there");
console.log(myBoundFn("!"));  // Hey there, I am Ayush!

// prototype chain
function Animal(name) {
    this.name = name;
}
Animal.prototype.speak = function() {
    return `${this.name} makes a sound`;
};

function Dog(name) {
    Animal.call(this, name);
}
Dog.prototype = Object.create(Animal.prototype);
Dog.prototype.constructor = Dog;
Dog.prototype.bark = function() {
    return `${this.name} barks`;
};

const dog = new Dog("Rex");
console.log(dog.speak());           // Rex makes a sound
console.log(dog.bark());            // Rex barks
console.log(dog instanceof Dog);    // true
console.log(dog instanceof Animal); // true

// class syntax - syntactic sugar over prototype chain
class Vehicle {
    constructor(make) {
        this.make = make;
    }
    describe() {
        return `${this.make} vehicle`;
    }
}

class Car extends Vehicle {
    #model;  // private field
    constructor(make, model) {
        super(make);
        this.#model = model;
    }
    describe() {
        return `${super.describe()}: ${this.#model}`;
    }
}

const car = new Car("Toyota", "Corolla");
console.log(car.describe());     // Toyota vehicle: Corolla
console.log(car instanceof Car); // true
