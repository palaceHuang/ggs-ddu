[toc]

# 0 | 前言

先做几道题目试试
+ 1
  ```js
  async function async1(){
    await new Promise((resolve, reject)=>{
        resolve();
    })
    console.log('A')
  }

  async1();

  new Promise((resolve)=>{
    console.log('B');
    resolve();
  }).then(()=>{
    console.log('C')
  }).then(()=>{
    console.log('D')
  })

  // 最终结果B A C D
  ```
+ 2
  ```js
  async function async1(){
    await async2();
    console.log('A');
  }

  async function async2(){
    return new Promise((resolve, reject)=>{
        resolve();
    })
  }

  async1();

  new Promise((resolve)=>{
    console.log('B');
    resolve();
  }).then(()=>{
    console.log('C');
  }).then(()=>{
    console.log('D')
  });

  // 最终结果 B C D A
  ```

# 1 | async函数返回值

在讨论await之前，先说下async函数处理返回值的问题，它会像Promise.prototype.then一样，会对返回值的类型进行辨识

__根据返回值的类型, 会引起JS引擎对返回值处理方式的不同__

结论： async函数在抛出返回值时，会根据返回值类型开启不同数目的微任务
- return结果值： 非thenable、非promise（不等待）
- return结果值： thenable（等待1个then的时间）
- return结果值： promise （等待2个then的时间）

再看几个代码示例
+ 1
  ```js
  async function testA(){
    return 1;
  }
  testA().then(()=>{
    console.log(1);
  })

  Promise.resolve()
  .then(()=>{
    console.log(2);
  }).then(()=>{
    console.log(3);
  })

  // （不等待）最终结果：1 2 3
  ```
+ 2
  ```js
  async function testB(){
    return {
        then (cb)=>{
            cb();
        }
    }
  }

  testB().then(()=>console.log(1));

  Promise.resolve()
    .then(()=>{
        console.log(2);
    })
    .then(()=>console.log(3));

    // (等待一个then)最终结果： 2 1 3

  ```
+ 3
   ```js
  async function testC(){
    return new Promise((resolve, reject)=>{
        resolve();
    })
  }

  testC().then(()=>console.log(1));

  Promise.resolve()
    .then(()=>console.log(2))
    .then(()=>console.log(3));

    // (等待2个then)最终结果： 2 3 1
  ```
+ 4
  ```js
  async function testC(){
    return new Promise((resolve, reject)=>{
        resolve();
    })
  }

  testC().then(()=>console.log(1));

  Promise.resolve()
    .then(()=>console.log(2))
    .then(()=>console.log(3))
    .then(()=>console.log(4));

    // (等待2个then)最终结果： 2 3 1 4
  ```

__做个面试题试试吧__

```js
async function async1(){
    console.log(1);
    await async2();
    console.log('AAA')
}

async2(){
    console.log(3);
    return new Promise((resolve, reject)=>{
        resolve();
        console.log(4);
    })
}

console.log(5);

setTimout(()=>{
    console.log(6);
},0);

async1();

new Promise((resolve)=>{
    console.log(7);
    resolve();
}).then(()=>{
    console.log(8)
}).then(()=>{
    console.log(9)
}).then(()=>{
    console.log(10)
});

console.log(11);
// 最终结果： 5 1 3 4 7 11 8 9 AAA 10 6
```

```
步骤拆分：
0. 先执行同步代码，输出5
1. 执行setTimeout,放入宏任务异步队列中
2. 接着执行async1函数，输出1
3. 执行async2函数，输出3
4. Promise构造器代码属于同步代码，输出4
    async2函数返回值是Promise， 等待2个then
5. async1函数暂时结束，继续往下走，输出7
6. 同步代码，输出11 
7. 执行第一个then，输出8
8. 执行第二个then，输出9
9. 等到了两个then执行完毕，执行async1函数里升下的，输出AAA
10. 在执行最后一个微任务then，输出10
11. 执行最后的宏任务setTimeout, 输出6
```

# 2 | await 右值类型区别

## 2.1 非thenable

+ 1
  ```js
  async function test(){
    console.log(1);
    await 1;
    console.log(2);
  }

  test();

  console.log(3);

  // 最终结果：1 3 2 
  ```
+ 2
  ```js
  function func(){
    console.log(2);
  }

  async function test(){
    console.log(1);
    await func();
    console.log(3);
  }

  test();

  console.log(4);

  // 最终结果： 1 2 4 3
  ```
+ 3
  ```js
  async function test(){
    console.log(1);
    await 123;
    console.log(2);
  }

  test();

  console.log(3);

  Promise.resolve()
  .then(()=>console.log(4))
  .then(()=>console.log(5))
  .then(()=>console.log(6))
  .then(()=>console.log(7));

  // 最终结果： 1 3 2 4 5 6 7 
  ```

  __await后面接非thenable类型，会立即向微任务队列添加一个微任务then，但不需要等待__
  
## 2.2 thenable类型

```js
async function test(){
    console.log(1);
    await {
        then(cb){
            cb();
        },
    }
    console.log(2);
}

test();

console.log(3);

Promise.resolve()
  .then(()=>console.log(4))
  .then(()=>console.log(5))
  .then(()=>console.log(6))
  .then(()=>console.log(7));

  // 最终结果： 1 3 4 2 5 6 7 

```

__await 后面接thenable类型，需要等待一个then的时间之后执行__

## 2.3 Promise类型

```js
async function test(){
    console.log(1);
    await new Promise((resolve, reject)=>{
        resolve();
    });
    console.log(2);
}

test();

console.log(3);

Promise.resolve()
  .then(()=>console.log(4))
  .then(()=>console.log(5))
  .then(()=>console.log(6))
  .then(()=>console.log(7));

// 最终结果：1 3 2 4 5 6 7 
```

？ 为什么表现和非 thenable值不一样呢？为什么不等待2个then的时间呢？

__NOTE__
```
* TC39[ECMAScript标准制定者]对await后面是promise的情况如何处理进行了一次修改，移除了额外的两个微任务，在早起版本，依然会等待两个then的时间
* 有大佬翻译了官方解释：更快的async和promises(),但在这次更新中并没有修改thenable的情况
```

这样可以极大优化await等待的速度
```js
async function func(){
    console.log(1);
    await 1;
    console.log(2);
    await 2;
    console.log(3);
    await 3;
    console.log(4);
}

aysnc function test(){
    console.log(5);
    await func();
    console.log(6);
}

test();

console.log(7);

Promise.resolve()
  .then(()=>console.log(8))
  .then(()=>console.log(9))
  .then(()=>console.log(10))
  .then(()=>console.log(11));

// 最终结果：5 1 7 2 8 3 9 4 10 6 11
```

__NOTE__
```
await 和 Promise.prototype.then 虽然很多时候在时间顺序上能等效，但是它们之间有本质的区别
```

```
* test函数中的await会等待func函数中所有的await取得恢复函数执行的命令并且整个函数执行完毕后才能获得恢复函数执行的命令
* 也就是说，func函数的await此时不能在时间的顺序上等效then，而是要等待到test函数完全执行完毕
* 比如这里的数字6很晚才输出，如果单纯看成then的话，在下一个微任务队列执行时6就应该作为同步代码输出才对
```

所以我们可以合并两个函数的代码
```js
async function test(){
    console.log(5);
    console.log(1);
    await 1;
    console.log(2);
    await 2;
    console.log(3);
    await 3;
    console.log(4);
    await null;
    console.log(6);
}

test();

console.log(7);

Promise.resolve()
  .then(()=>console.log(8))
  .then(()=>console.log(9))
  .then(()=>console.log(10))
  .then(()=>console.log(11));

// 最终结果：5 1 7 2 8 3 9 4 10 6 11
```

此时的await可以等效于Promise.prototype.then，又可以完全等效于
```js
async function test(){
    console.log(5);
    console.log(1);
    Promise.resolve()
    .then(()=>console.log(2))
    .then(()=>console.log(3))
    .then(()=>console.log(4))
    .then(()=>console.log(6))
}

test();

console.log(7);

Promise.resolve()
  .then(()=>console.log(8))
  .then(()=>console.log(9))
  .then(()=>console.log(10))
  .then(()=>console.log(11));
```

以上三种写法在时间顺序上完全一致，所以可以将await后面的代码看做在then里面执行的结果，又因为async函数会返回promise实例，所以还可以等效成：
```js
async function test(){
    console.log(5);
    console.log(1);    
}

test()
    .then(()=>console.log(2))
    .then(()=>console.log(3))
    .then(()=>console.log(4))
    .then(()=>console.log(6))

console.log(7);

Promise.resolve()
  .then(()=>console.log(8))
  .then(()=>console.log(9))
  .then(()=>console.log(10))
  .then(()=>console.log(11));
```