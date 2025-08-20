// async JS - promises, async/await, event loop

// basic promise
function delay(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function run() {
    console.log("start");
    await delay(100);
    console.log("after 100ms");
}

run();

// promise chain
function fetchData(id) {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            if (id > 0) resolve({ id, data: `result_${id}` });
            else reject(new Error("invalid id"));
        }, 50);
    });
}

fetchData(1)
    .then(res => {
        console.log(res);
        return fetchData(2);
    })
    .then(res => console.log(res))
    .catch(err => console.error(err.message));

// async/await with error handling
async function getData(id) {
    try {
        const result = await fetchData(id);
        console.log("got:", result);
    } catch (e) {
        console.error("error:", e.message);
    }
}

getData(1);
getData(-1);

// Promise.all - fails fast
async function runAll() {
    const results = await Promise.allSettled([
        fetchData(1),
        fetchData(-1),
        fetchData(2),
    ]);

    for (const r of results) {
        if (r.status === "fulfilled") console.log("ok:", r.value);
        else console.log("fail:", r.reason.message);
    }
}

runAll();

// event loop order
console.log("1");
setTimeout(() => console.log("2 - setTimeout"), 0);
Promise.resolve().then(() => console.log("3 - microtask"));
console.log("4");
// output: 1, 4, 3 - microtask, 2 - setTimeout
// microtask queue has higher priority than callback queue
