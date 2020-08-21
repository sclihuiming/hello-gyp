const { add } = require('bindings')('add.node')
const { curryAdd } = require('bindings')('curry-add');

console.log(add(1, 2))     // 3
console.log(add(0.1, 0.2)) // 熟悉的 0.3XXXXX


console.log('curry start ***********')
const fn = curryAdd(1, 2, 3);
const fn2 = fn(4);

console.log(fn.valueOf())     // => 6
console.log(fn2.valueOf())    // => 10
console.log(fn2(5).valueOf()) // => 15