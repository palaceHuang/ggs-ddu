# Module 的语法

## 1. 概述

ES6 之前社区的模块加载方案：

- CommonJS
  用于服务器
- AMD
  用于浏览器

ES6 在语言标准的层面上，实现了模块功能。完全可以取代 CommonJS 和 AMD 规范，成为浏览器和服务器通用的模块解决方案。

ES6 模块的设计思想是尽量的静态化，使得编译时就能确定模块的依赖关系，以及输入和输出的变量。CommonJS 和 AMD 模块，都只能在运行时确定这些东西。  
CommonJS 模块：

```js
// CommonJS模块
let { stat, exists, readfile } = require('fs');
// 等同于
let _fs = require('fs');
let stat = _fs.stat;
let exists = _fs.exists;
let readfile = _fs.readfile;
```

以上代码的实质是整体加载 fs 模块（即加载 fs 所有方法），生成一个对象，然后再从这个对象上读取三个方法。这种加载成为“运行时加载”，因为只有运行时才能得到这个对象，导致完全没办法在编译时做“静态优化”。

ES6 模块不是对象，而是通过 export 命名显式指定输出的代码，再通过 import 命令输入。

```js
// ES6模块
import { stat, exists, readFile } from 'fs';
```

以上代码是从 fs 模块加载 3 个方法，其它方法不加载。这种加载称为“编译时加载”或者静态加载，即 ES6 可以在编译时就完成模块加载，效率比 CommonJS 高。**_这也导致无法引用 ES6 模块本身因为它不是对象_**。

除了静态加载带来的各种好处，ES6 模块还有以下好处：

- 不再需要 UMD 模块格式了，将来服务器和浏览器都会支持 ES6 模块格式
- 将来浏览器的新 API 就能用模块格式提供，不再必须做成全局变量或者 navigator 对象的属性
- 不再需要对象作为命名空间，未来这些功能可以通过模块提供

## 2. 严格模式

ES6 的模块自动采用严格模式，无论是否在模块头部加上"use strict";。  
严格模式主要有以下限制：

- 变量必须声明后再使用
- 函数的参数不能有同名属性，否则报错
- 不能使用 with 语句
- 不能对只读属性赋值，否则报错
- 不能使用前缀 0 表示八进制数，否则报错
- 不能删除变量 delete prop，会报错，只能删除属性 delete global[prop]
- eval 不会在它的外层作用域引入变量
- eval 和 arguments 不能被重新赋值
- arguments 不会自动反应函数参数的变化
- 不能使用 arguments.callee
- 不能使用 arguments.caller
- 禁止 this 指向全局对象
- 不能使用 fn.caller 和 fn.arguments 获取函数调用的堆栈
- 增加了保留字（比如 protected、static、interface)

以上限制，模块都必须遵守。  
其中，尤其需要注意 this 的限制。ES6 模块之中，顶层的 this 指向 undefined，即不应该在顶层代码中使用 this。

## export 命令

模块功能主要由两个命令组成：export 和 import。export 用于规定模块的对外接口，import 用于输入其它模块提供的功能。

一个模块就是一个独立的文件。该文件内部的所有变量，外部无法获取。如果你希望外部能够读取模块内部的某个变量，就必须用 export 输出该变量：

```js
// profile.js
export var firstName = 'Michael';
export var lastName = 'Jackson';
export var year = 1958;
```

以上为 profile.js 文件内容，保存了用户信息。ES6 将其视为一个模块，里面用 export 命令对外输出了三个变量。

换种写法：

```js
// profile.js
var firstName = 'Michael';
var lastName = 'Jackson';
var year = 1958;

export { firstName, lastName, year };
```

export 除了输出变量，还可以输出函数和类

```js
export function multiply(x, y) {
  return x * y;
}
```

export 输出的变量就是本来的名字，可以用 as 重命名

```js
function v1(){...}
function v2(){...}

export {
  v1 as streamV1,
  v2 as streamV2,
  v2 as streamLatestVersion
};
```

export 命令规定的是**_对外的接口_**，必须与模块内部的变量建立一对一对应关系：

```js
export 1; // error

var m = 1;
export m; // error
```

正确的写法

```js
// 写法一
export var m = 1;
// 写法二
var m = 1;
export { m };
// 写法三
var n = 1;
export { n as m };
```

function 和 class 的输出，遵循同样的写法：

```js
function f(){}
export f; // error
// 正确的写法
export function f(){}

export {f};
```

export 语句**_输出的接口，与其对应的值是动态绑定关系_**，即通过该接口，课取到模块内部**_实时的值_**

```js
export var foo = 'bar';
setTimeout(() => {
  foo = 'baz';
}, 500);
```

上面代码输出变量 foo，值为 bar，500 毫秒之后变成 baz。

这一点有 CommonJS 规范完全不同。CommonJS 模块输出的是值的缓存，不存在动态更新。

最后，export 可以出现在模块的任何位置，只要处于模块顶层就可以。如果处于块级作用域内，就会报错。

```js
function foo() {
  export default 'bar'; // SyntaxError
}
foo();
```

## 4. import 命令

使用 export 命令定义了模块的对外接口之后，其它 JS 文件就可以通过 import 命令加载这个模块

```js
import { firstName, lastName, year } from './profile.js';
console.log(year);
```

import 命令接受一对大括号，里面指定要从其它模块导入的变量名。大括号里的变量名，必须与被导入模块对外接口的名称相同。

如果想为输入的变量重新取一个名字，import 命令要使用 as 关键字，将输入的变量重命名。

```js
import { firstName as fn } from './profile.js';
```

import 命令输入的变量都是只读的，因为它们的本质都是输入接口。**_不允许在加载模块的脚本里改写接口_**。

```js
import { a } from './profile.js';
a = {}; // TypeError: Assignment to constant variable
```

如果 a 是一个对象，改写 a 的属性是允许的

```js
import { a } from './profile.js';
a.name = 'huang'; // 合法操作，但不建议这么做
```

import 后面的 from 指定模块文件的位置，可以是相对路径，也可以是绝对路径。如果不带路径，只是一个模块名，那么必须有配置文件，告诉 JavaScript 引擎该模块的位置。

```js
import { myMethod } from 'util';
```

import 命令具有提升效果，会提升到整个模块的头部，首先执行。

```js
foo();
import { foo } from 'my_module';
```

import 的执行早于 foo 的调用。这种行为的本质是：import 命令是编译阶段执行的，在代码运行之前。

由于 import 是静态执行，所以不能使用表达式和变量之类只能在运行时才能得到结果的语法结构。

```js
import {'f' + 'oo' } from 'my_module'; // error
let module = 'my_module';
import { foo } from module; // ERROR

// error
if( x == 1){
  import { foo } from 'module1';
} else {
  import {foo} from 'module2';
}
```

import 语句会执行所加载的模块：

```js
import './bar.js';
```

如果多次重复执行同一 import，那么只会执行一次：

```js
import './bar.js';
import './bar.js';
```

以上代码加载了两次./bar.js，但只会执行一次

```js
import { foo } from 'my_module';
import { bar } from 'my_module';
// 等同于
import { foo, bar } from 'my_module';
```

foo 和 bar 在两个语句中加载，但是它们对应是同一个 my_module 模块。import 语句是 Singleton 模式。

## 5. 模块的整体加载

除了指定加载某个输出值，还可以整体加载。用星号(\*)指定一个对象，所有输出值都加载在这个对象上面：
circle.js

```js
export function area(radius) {
  return Math.PI * radius * radius;
}
export function circumference(radius) {
  return 2 * Math.PI * radius;
}
```

加载上述模块：

```js
import * as circle from './circle';
console.log(circle.area(4));
console.log(circle.circumference(14));
// 以下代码都是不允许的
circle.area = 'hello';
circle.circumference = function () {};
```

## 6. export default

为模块指定默认输出，使用 export default 。其它模块加载该模块时，import 命令可以为该默认输出指定任意名字。
export-default.js

```js
export default function(){...};
// 或者
export default function foo(){...};
```

其它模块加载该模块时，import 命令可以为该匿名函数指定任意名字：

```js
import customName from './export-default';
customName();
```

注意：import 命令后面不使用大括号

默认输出和正常输出对比

```js
// 默认输出
export default function crc32(){...};
import crc32 from './crc32';

// 正常输出
export function crc32(){...};
import {crc32} from './crc32';
```

也可以在一条 import 语句中，同时输入默认方法和其它接口：

```js
import _, { each, forEach } from 'lodash';
```

## 7. export 与 import 的复合写法

如果一个模块中，先输入后输出同一个模块，import 语句可以和 export 语句写在一起。

```js
export { foo, bar } from 'my_module';
```

## 8. 模块的继承

模块之间也可以继承。假设有一个 circleplus 模块，继承了 circle 模块。
circleplus.js

```js
export * from 'circle';
export var e = 2.718;
export default function (x) {
  return Math.exp(x);
}
```

## 9. 跨模块常量

const 声明的常量只在当前代码块有效。如果想要设置跨模块的常量（即跨多个文件），或者说一个值要被多个模块共享，可以采用如下写法：

```js
// constants.js
export const A = 1;
export const B = 3;

// test1.js
import * as contants from './constants.js';
console.log(contants.A);
console.log(contants.B);

// test2.js
import { A, B } from './constants.js';
console.log(A);
```

如果要使用的常量非常多，可以建一个专门的 constants 目录，将各种常量写在不同的文件里面，保存在该目录下：

```js
// constants/db.js
export const db = {
  url: 'http://my.url.cn:5555',
  username: 'admin',
  password: 'password',
};

// constants/users.js
export const users = ['root', 'admin'];
```

然后，将这些文件输出的常量，合并在 index.js 里面

```js
// constants/index.js
export { db } from './db';
export { users } from './users';
```

使用的时候，直接加载 index.js 就可以了。

```js
// script.js
import { db, users } from './constants/index';
```

## 10. import()

### 简介

import 命令会被 JavaScript 引擎静态分析，先于模块内的其它语句执行。所以以下代码会报错：

```js
if (x == 2) {
  import myModule from './myModule';
}
```

以上，引擎处理 import 语句是在编译时，这时不会去分析或执行 if 语句，所以 import 放在 if 代码块中毫无意义，因此会报句法错误，而不是执行错误。import 和 export 只能在模块的顶层出现，不能出现在代码块中。

require 是运行时加载模块，import 是编译时加载模块，import 命令无法替代 require 的动态加载功能

ES2020 提案，引入 import()函数，支持动态加载模块。import(specifier);
import 命令能够接受什么参数，import()就能接受什么参数，两者区别主要是 import()函数为动态加载。

import() 返回一个 Promise 对象。

import()函数可以用在任何地方，不仅仅是模块，非模块的脚本也可以使用。它是运行时执行，也就是说，什么时候代码运行到这一句，就会加载指定的模块  
import()函数与所加载的模块没有静态连接关系，这点也和 import 语句不同  
import()类似于 Node 的 require 方法，区别主要是前者是异步加载，后者是同步加载。

### 适用场合

下面是 import()的一些适用场合：

1. 按需加载
2. 条件加载
3. 动态的模块路径

# Module 的加载实现

## 1. 浏览器加载

### 传统方法

HTML 网页中，浏览器通过标签加载 JavaScript 脚本

```html
<!-- 页面内嵌脚本 -->
<script type="application/javascript">
  // module code
</script>

<!-- 外部脚本 -->
<script type="application/javascript" src="path/to/myModule.js"></script>
```

以上代码中，由于浏览器默认脚本语言是 JavaScript，因此 type="application/javascript"可以省略

默认情况下，浏览器是同步加载 JavaScript 脚本，即渲染引擎遇到 script 标签就会停下来，等到执行万脚本，再继续向下渲染。如果是外部脚本，还必须加入脚本下载的时间。

如果脚本体积很大，下载和执行时间就会很长，因此造成浏览器堵塞，用户感觉浏览器“卡死”，没有任何响应。这是很不好的体验，所以浏览器允许脚本异步加载：

```html
<script src="path/to/myModule.js" defer></script>
<script src="path/to/myModule.js" async></script>
```

以上，脚本会异步加载。渲染引擎遇到这一行命令，就会开始下载外部脚本，但不会等它下载和执行，而是直接执行后面的命令。

defer 与 async 的区别：

- defer
  等到整个页面在内存中正常渲染结束（DOM 结构完全生成，以及其它脚本执行完成），才会执行。“渲染完再执行”。如果有多个 defer 脚本，会按照它们在页面出现的顺序加载
- async  
  一旦下载完，渲染引擎就会终端渲染，执行这个脚本以后，再继续渲染。“下载完就执行”。如果有多个 async 脚本，是不能保证加载顺序的。

### 加载规则

浏览器加载 ES6 模块，也是用 script 标签，但是要加入 type="module"属性

```html
<script type="module" src="./foo.js"></script>
```

浏览器对于带有 type="module"的 script，都是异步加载，不会造成堵塞浏览器，即等到整个页面渲染完，再执行模块脚本，等同于打开了 defer 属性

如果网页中有多个 type="module"的 script，它们会按照在页面上出现的顺序依次执行。

type="module"的 script 的 async 属性也可以打开，这是只要加载完成，渲染引擎就会中断渲染立即执行。执行完成后，再恢复渲染。一旦使用了 async 属性，模块就不会按照在页面中出现的顺序执行，而是只要该模块加载完成，就执行。

ES6 模块允许内嵌在网页中，语法行为与加载外部脚本完全一致

```html
<script type="module">
  import utils from './utils.js';
</script>
```

对于外部的模块脚本，有几点需要注意：

- 代码是在模块作用域之中运行，而不是在全局作用域运行。模块内部的顶层变量，外部不可见
- 模块脚本自动采用严格模式，无论有没有声明 use strict
- 模块之中，可以使用 import 命令加载其它模块(.js 后缀不可省略，需要提供绝对 URL 或相对 URL)，也可以使用 export 输出对外接口
- 模块之中，顶层 this 返回 undefined，而不是指向 window。
- 同一个模块如果加载多次，将只执行一次

利用顶层的 this 等于 undefined 这个语法点，可以侦测当前代码是否在 ES6 模块之中

## 2. ES6 模块与 CommonJS 模块的差异

ES6 与 CommonJS 模块的差异：

- CommonJS 模块输出的是一个值的拷贝，ES6 模块输出的是值的引用  
  CommonJS 模块输出的是值的拷贝，也就是说，一旦输出一个值，模块内部的变化就影响不到这个值
- CommonJS 模块是运行时加载，ES6 模块时编译时输出接口  
  CommonJS 加载的是一个对象（即 module.exports)，该对象只有在脚本运行完才会生成。而 ES6 模块不是对象，它的对外接口只是一中静态定义，在代码静态解析阶段就会生成
- CommonJS 模块的 require()是同步加载模块，ES6 模块的 import 命令是异步加载，有一个独立的模块依赖解析阶段

```js
// lib.js
var counter = 3;
funnction add(){
  counter++;
}
module.exports = {
  get counter(){
    return counter;
  },
  add: add,
}

// main.js
const mod = require("./lib");
console.log(mod.counter); // 3
mod.add();
console.log(mod.counter); // 4
```

以上，输出的 counter 属性实际上是一个取值器函数。执行 main.js，就能正确读取内部变量 counter 的变动。

ES6 模块的运行机制和 CommonJS 不一样。JS 引擎对脚本静态分析的时候，遇到模块加载命令 import，就会生成一个只读引用。等到脚本真正执行时，再根据这个只读引用，到被加载的那个模块里面取值。ES6 的 import 有点像 Unix 系统里的“符号连接”，原始值变了，import 加载的值也会跟着变。因此，ES6 模块时动态引用，并且不会缓存值，模块里面的变量绑定其所在的模块。

由于 ES6 输入的模块变量，只是一个“符号连接”，所以这个变量时只读的，对它进行重新赋值会报错。

## 3. Node.js 的模块加载方法

CommonJS 模块是 Node.js 专用的 ，与 ES6 模块不兼容。

语法差别：

- CommonJS 模块使用 require()和 module.exports
- ES6 模块使用 import 和 export

从 Node.js V13.2 开始，Node.js 已经默认打开了 ES6 模块支持

Node.js 要求 ES6 模块采用.mjs 后缀文件名。也就是说，只要脚本文件里面使用 import 或者 export 命令，那么就必须采用.mjs 后缀名。Node.js 遇到.mjs 文件，就认为它是 ES6 模块，默认启用严格模式，不必在每个模块文件顶部指定“use strict"

如果不希望将后缀名改成.mjs，可以在项目的 package.json 文件中，指定 type 字段为 module。一旦如此设置之后，该项目的 JS 脚本，就被解释成 ES6 模块。如果此时还要使用 CommonJS 模块，那么需要将 CommonJS 脚本的后缀名都改为.cjs。如果没有 type 字段，或者 type 字段为 commonjs，则.js 脚本会被解释成 ComomonJS 模块。

总结：.mjs 文件总是以 ES6 模块加载，.cjs 文件总是以 CommonJS 模块加载，.js 文件的加载取决于 package.json 里面的 type 字段的设置

注意：ES6 模块和 CommonJS 模块尽量不要混用。require 命令不能加载.mjs 文件，会报错，只有 import 命令才可以加载.mjs 文件。

### pakage.json 的 main 字段

package.json 文件有两个字段可以指定模块的入口文件：main 和 exports。比较简单的模块，可以只使用 main 字段：

```js
// ./node_modules/es-module-package/package.json
{
  "type": "module",
  "main": "./src/index.js"
}

// ./my-app.mjs
import {sth} from "es-moudle-package";
 //实际加载的是./node_modules/es-module-package/src/index.js
```

### package.json 的 exports 字段

exports 字段的优先级高于 main 字段。它有多种用法：

1. 子目录别名
   脚本别名
   ```json
   // ./node_modules/es-module-package/package.json
    {
      "exports": { 
        "./submodule": "./src/submodule.js"
      }
    }
    ```
    ```js
    // 加载./node_modules/es-module-package/src/submodule.js
    import submodule from 'es-module-package/submodule';
   ```
   子目录别名
   ```json
   // ./node_modules/es-module-package/package.json
    {
      "exports": { 
        "./features/": "./src/features/"
      }
    }
    ```
    ```js
    // 加载./node_modules/es-module-package/src/features/x.js
    import feature from 'es-module-package/features/x.js';
   ```
2. main 的别名
   exports字段的别名如果是.，就代表模块的主入口，优先级高于main字段，并且可以简写成exports字段的值
   ```json
   {
     "exports":{ 
       ".": "./main.js"
     }
     // 等同于
     "exports": "./main.js"
   }
   ```
   由于exports字段只有支持ES6的Node.js才认识，所以可以用来兼容旧版本的Node.js
   ```json
  {
    "main": "./main-legacy.cjs",
    "exports": {
      ".": "./main-modern.cjs"
    }
  }
   ```
   以上，老版本的Node.js的入口是main-legacy.cjs，新版本的Node.js的入口文件是main-modern.cjs。
3. 条件加载
   利用.这个别名，可以为ES6模块和CommonJS指定不同的入口。目前，这个功能需要在Node.js运行的时候，打开--experimental-conditional-exports标志
   ```json
   {
     "type": "module",
     "exports": {
       ".": {
         "require": "./main.cjs",
         "default": "./main.js"
       }
     }
   }
   ```
以上，别名.的require条件指定require()命令的入口文件，default条件指定其它情况的入口

### CommonJS模块加载ES6模块
CommonJS的require()命令不能加载ES6模块，只能使用import()这个方法加载。
```js
(async ()=>{
  await import('./my-app.mjs');
})();
```
以上代码可以在CommonJS模块中运行。require()不支持ES6的一个原因是：它是异步加载，而ES6模块内部可以使用顶层await命令，导致无法被同步加载。

### ES6模块加载CommonJS模块

ES6模块的import命令可以加载CommonJS模块，但是只能整体加载，不能只加载单一输出项。
```js
// 正确
import packageMain from 'commonjs-package';
// 错误
import {method} from 'commonjs-package;
// 加载单一输出项，可以
import main from 'commonjs-package';
const {method}  = main;
```
### Node.js的内置模块
Node.js的内置模块可以整体加载，也可以加载指定的输出项。
```js
// 整体加载
import EventEmitter from 'events';
const e = new EventEmitter();

// 加载指定的输出项
import {readFile} from 'fs';
readFile(...);
```

### 加载路径
### 内部变量

## 4. 循环加载
