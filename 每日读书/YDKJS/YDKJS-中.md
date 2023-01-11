[toc]

# 第一部分 类型和语法

## 第一章 类型

ES5.1 规范（http://www.ecma-international.org/ecma-262/5.1/）对此是如何界定的：
本规范中的运算法则所操纵的值均有相应的类型。本节中定义了所有可能出现的类型。ECMAScript 类型又进一步细分为语言类型和规范类型。
ECMAScript 语言中所有的值都有一个对应的语言类型。ECMAScript 语言类型包括 Undefined、Null，Boolean、String、Number 和 Object.

---

Algorithms within this specification manipulate values each of which has an associated type. The possible value types are exactly those defined in this clause. Types are further subclassified into ECMAScript language types and specification type.

An ECMAScript language type corresponds to values that are directly manipulated by an ECMAScript programmer using the ECMAScript language. The ECMAScript language types are Undefined, Null, Boolean, String, Number and Object.

A specification type corresponds to meta-values that are used within algorithms to describe the semantics of ECMAScript language constructs and ECMAScript language types. The specification types are Reference, List, Completion, Property Descriptor, Property Identifier, Lexical Environment, and Environment Record.

在本书中，我们这样来定义类型：对语言引擎和开发人员来说，类型是值的内部特征，它定义了值的行为，以使其区别于其他值

### 1.2 内置类型

Javascript 有七种内置类型：

- 空值（null）
- 未定义（undefined）
- 布尔值（boolean)
- 数字（number）
- 字符串（string）
- 对象（object）
- 符号（symbol，ES6 中新增）
  可以使用 typeof 运算符来查看，其中有两种比较特别：

```js
typeof null === 'object'; //true
typeof function a() {} === 'function'; //true
```

其中 function 是 object 的子类型，具体来说，function 是 callable object。

变量没有类型，但是它们持有的值有类型。类型定义了值的行为特征

undeclared 表示变量还没有被声明过；undefined 表示变量处于已声明未赋值的状态

## 第二章 值

### 2.1 数组

在 JavaScript 中，数组可以容纳任何类型的值

在创建“稀疏”数组（sparse array，即含有空白或空缺单元的数组）时要特别注意，空白单元的值默认为 undefined

类数组->数组  
Array.prototype.slice.call(arrayLike)  
Array.from(arrayLike)

### 2.2 字符串

Javascript 中字符串是不可变的，而数组是可变的。所以我们无法“借用”数组的可变成员函数，如 reverse

### 2.3 数字

JavaScript 只有一种数值类型：number，包含整数和小数  
JavaScript 中的整数就是没有小数的十进制数  
JavaScript 中数字类型是基于 IEEE 754 标准来实现的，该标准通常也被称为浮点数。JavaScript 使用的是“双精度”格式（即 64 位二进制）

toFixed(..)方法可以指定小数部分的显示位数

```js
let a = 42.59;
a.toFixed(0); //43
a.toFixed(1); // 42.6
a.toFixed(3); //42.590
```

toPrecision(..)方法用来指定有效数位的显示位数(字符串形式)

```js
var a = 42.59;
a.toPrecision(1); // '4e+1'
a.toPrecision(2); // '43'
```

使用数字常量调用该方法时，需要特别注意，.运算符会优先被识别为数字常量的一部分，然后才是对象属性访问运算符

```js
//无效语法
42.toPrecision(3); // SyntaxError

// 下面语法都有效
(42).toPrecision(1);
0.42.toFixed(3);
42..toFixed(3);
```

二进制浮点数最大的问题（所有遵循 IEEE 754 规范的语言都是如此），是会出现如下情况：

```js
0.1 + 0.2 === 0.3; // false 0.30000000000000004
```

判断 0.1+0.2 和 0.3 是否相等的方法
最常见的方法就是设置一个误差范围，通常成为“机器精度（machine epsilon），对 JavaScript 的数字来说，这个值通常是 2^-52(2.220446049250313e-16)

```js
function numbersCloseEnoughToEqual(n1, n2) {
  return Math.abs(n1 - n2) < Math.EPSILON;
}

numbersCloseEnoughToEqual(0.1 + 0.2, 0.3);
```

能够被“安全”呈现的最大整数是 2^53 -1，即 9007199254740991，在 ES6 中被定义为 Number.MAX_SAFE_INTEGER。最小的整数是-9007199254740991，在 ES6 中被定义为 Number.MIN_SAFE_INTEGER。

整数检测
Number.isInteger(..)

void 运算符
void 并不改变表达式的结果，只是让表达式不返回值；按惯例我们用 void 0 来获得 undefined

NaN 可以理解为：无效数值、失败数值或者坏数值  
isNaN(..)用来判断一个值是不是 NaN，它有一个严重的缺陷：

```js
var a = 2 / 'abc'; // NaN
var b = 'foo'; // 'foo'

window.isNaN(a); // true
window.isNaN(b); // true 晕
```

判断一个值是否为 NaN
方法一：Number.isNaN(..)
方法二：n !== n
NaN 是 JavaScript 中唯一一个不等于自身的值

加法和减法运算不会得到-0（negative zero)

我们为什么需要负零？

> 有些应用程序中的数据需要以级数形式来表示（比如动画帧的移动速度），数字的符号位（sign）用来代表其它信息（比如移动方向）。此时如果一个值为 0 的变量失去了它的符号，它的方向信息就会丢失。所以保留 0 值的符号位可以防止这种情况的发生

能使用==和===时就尽量不要使用 Object.is()，因为前者效率更高，更为通用

JavaScript 引用指向的是值。如果一个值有 10 个引用，这些引用指向的都是同一个值，它们相互之间没有引用/指向关系

简单值（即标量基本类型，scalar primitive)总是通过值赋值的方式来赋值/传递，包括 null、undefined、字符串、数字、布尔和 symbol  
复合值（compound value)-对象（包括数组和封装对象）和函数，则总是通过引用复制的方式来赋值/传递

由于引用指向的是值本身而非变量，所以一个引用无法更改另一个引用的指向。

### 2.4 特殊数值

#### 2.4.1 不是值的值

undefined 类型只有一个值，即 undefined。null 类型也只有一个值，即 null。它们的名称既是类型也是值。

- null 指空值（empty value)  
  曾经赋过值，但是目前没有值  
  null 是一个特殊关键字，不是标识符。我们不能将其当做变量来使用和赋值
- undefined 指没有值(missing value)  
  从未赋值
  undefined 是一个标识符，可以被当做变量来使用和赋值
- void 运算符
  undfined 是一个内置标识符，它的值是 undefined，通过 void 运算符即可得到该值。
  表达式 void \_\_没有返回值，因此返回结果为 undefined。void 并不改变表达式的结果，只是让表达式不返回值。我们常用 void 0 来获得 undefined

#### 2.4.2 undefined

#### 2.4.3 特殊的数字

1. 不是数字的数字 NaN
   NaN 可以理解为”无效数值“，“失败数值”，或者“坏数值”。NaN 和自身不相等，是唯一一个非自反（reflexive， 即 x === x 不成立)的值。
   内建的全局工具函数 isNaN 有致命缺陷：isNaN('foo') == true
   推荐使用 Number.isNaN
2. 无穷数
   计算结果一旦溢出为无穷数，就无法再得到有穷数。
   ```js
   1 / 0; // Infinity
   -1 / 0; //-Infinity
   Infinity / Infinity; // NaN
   3 / Infinity; //0
   -3 / Infinity; // -0
   ```
3. 零值
   JavaScript 有一个常规的 0（叫做+0）和一个（-0）
   加法和减法运算不会得到负零（negative zero）
   根据规范，对负零进行字符串化会返回“0”
   ```js
   var a = 0 / -3;
   a.toString(); //'0'
   a + ''; //'0'
   String(a); //'0'
   JSON.stringify(a); //'0'
   ```
   从字符串转换为数字，得到的结果会是准确的：
   ```js
   +'-0'; // -0
   Number('-0'); // -0
   JSON.parse('-0'); // -0
   ```
   零和负零的比较总为 true
   ```js
   -0 == 0; //true
   -0 === 0; //true
   0 > -0; //false
   ```

我们为什么需要负零？  
有些应用程序的数据需要以级数形式来表示（比如动画帧的移动速度），数字的符号位（sign）用来代表其它信息（比如移动方向）。此时如果一个值为 0 的变量失去了它的符号，它的方向信息就会丢失。所以保留 0 值的符号位可以防止此类情况发生。

#### 2.4.4 特殊等式

```js
var a  = 2 / 'foo';
var b = -3 * 0;
Object.is(a, NaN)；// true
Object.is(b, -0）； //true

Object.is(b, 0); //false
```

能使用==和===时就尽量不要使用 Object.is，因为前者的效率更高，更为通用。Object.is 主要用来处理特殊的相等比较

### 2.5 值和引用

JavaScript 引用指向的是值。如果一个值有 10 个引用，这些引用给指向的是同一个值，它们相互之间没有引用/指向关系。
简单值（即标量基本类型，scalar primitive)总是通过值赋值的方式来赋值/传递，包括 null、undefined、字符串、数字、布尔和 ES6 中的 symbol
复合值（compound value)- 对象（包括数组和封装对象）和函数，则总是通过引用复制的方式来赋值/传递。
我们无法自行决定使用值复制还是引用复制，一切由值的类型来决定。

```js
function foo(x) {
  x = x + 1;
  x; //3
}
var a = 2;
var b = new Number(a); //Object(a)也一样
foo(b);
b; //2
```

标量基本类型值是不可更改的（字符串和布尔也是如此）。如果一个数字对象的标量基本类型是 2，那么该值就不能更改，除非创建一个包含新值的数字对象。

### 2.6 小结

JavaScript 中的数组是通过数字索引的一组任意类型的值。字符串和数组类似，但是它们的行为特征不同，在将字符作为数组来处理时需要特别小心。JavaScript 中的数字包括整数和浮点型

基本类型中定义了几个特殊的值：
null 类型只有一个值 null  
 undefined 类型只有一个值 undefined  
 所有变量在赋值之前默认值都是 undefined  
 void 运算符返回 undefined

数字类型有几个特殊值

> NaN
> +Infinity
> -Infinity  
> -0

简单标量基本类型值（字符串和数字等）通过值赋值来赋值/传递；而复合值（对象等）通过引用复制来赋值/传递。JavaScript 中的引用和其它语言中的引用/指针不同，它们不能指向别的变量/引用，只能指向值

## 第三章 原生函数

常用的原生函数

- String()
- Number()
- Boolean()
- Array()
- Object()
- Function()
- RegExp()
- Date()
- Error()
- Symbol() - ES6 新加入的

  原生函数可以被当做构造函数来使用，但其构造出来的对象可能会和我们设想的有所出入：

  ```js
  var a = new String('a');
  typeof a; // 'object'
  a instanceof String; //true
  a instancof Object; //true
  Object.prototype.toString.call(a); //"[object String]"
  ```

### 3.1 内部属性[[Class]]

所有 typeof 返回值为'object'的对象（如数组）都包含一个内部属性[[Class]]。这个属性无法直接访问，一般通过 Object.prototype.toString(...)来查看。

```js
Object.prototype.toString.call([1, 2, 3]); //"[object Array]"
Object.prototype.toString.call(/reg-literal/i); //"[object RegExp]"

Object.prototype.toString.call(null); //"[object Null]"
Object.prototype.toString.call(undefined); //"[object Undefined]"

Object.prototype.toString.call('abc'); //"[object String]"
Object.prototype.toString.call(4); //"[object Number]"
Object.prototype.toString.call(true); //"[object Boolean]"
```

### 3.2 封装对象和包装

由于基本类型没有.length 和.toString()这样的属性和方法，需要通过封装对象才能访问，此时 JavaScript 会自动为基本类型值包装一个封装对象.

直接为基本类型创建封装对象不是个好方法，浏览器已经为.length 这样的常见情况做了性能优化，直接使用封装对象来“提前优化”代码反而会降低执行效率

一般情况下，我们不需要直接使用封装对象。最好的办法是让 JavaScript 引擎自己决定啥时候应该使用封装对象。我们应该优先考虑使用基本类型值。

**_封装对象释疑_**

```js
var a = new Boolean(false);
if (!a) {
  console.log('Oops!'); //执行不到这里
}
```

如果想要自行封装基本类型值，可以使用 Object(...)函数（不带 new）

```js
var a = 'abc';
var b = new String(a);
var c = Object(a);

typeof a; //'string'
typeof b; //'object'
typeof c; //'object'

b instanceof String; //true
c instanceof String; //true

Object.prototype.toString.call(b); //"[object String]"
Object.prototype.toString.call(c); //"[object String]
```

### 3.3 拆封

如果想要得到封装对象的基本类型值，可以使用 valueOf()函数。

### 3.4 原生函数作为构造函数

应该尽量避免使用构造函数，因为它们经常会产生意想不到的结果。

#### 3.4.1 Array(..)

我们将包含至少一个“空单元”的数组称为“稀疏数组“。

永远不要创建和使用空单元数组。

#### 3.4.2 Object(..)、Function(..)、RegExp(..)

除非万不得已，否则尽量不要使用 Object(..)/Function(..)/RegExp(..)

强烈建议使用常量形式来定义正则表达式，语法简单且执行效率也更高，因为 JavaScript 引擎在代码执行前会对它们进行预编译和缓存。

#### 3.4.3 Date(..) 和 Error(..)

相较于其它原生构造函数，Date(..)和 Error(..)的用处大很多，因为没有对应的常量形式来作为它们的替代。

创建日期对象必须使用 new Date()。Date(..)可以带参数，用来指定日期和时间，而不带参数的话则使用当前的日期和时间。

如果调用 Date()时不带 new 关键字，则会得到当前日期的的字符串值。

构造函数 Error(..)带不带 new 关键字都可。创建错误对象主要是为了获得当前运行栈的上下文（大部分 JavaScript 引擎通过只读属性.stack 来访问）。栈上下文信息包含函数调用栈信息和产生错误的代码行数，以便于调试。

错误对象通常与 throw 一起使用：throw new Error('...')；通常错误对象至少包含一个 message 属性，有时也不乏其它属性，如 type。最好的办法是调用 toString()来获得经过格式化的便于阅读的错误信息。

除 Error 之外，还有一些针对特定错误类型的原生构造函数，如 EvalError、RangeError、ReferenceError、SyntaxError、TypeError 和 URIError。这些构造函数很少被直接使用，它们在程序发生异常时会被自动调用。

#### 3.4.4 Symbol(..)

Symbol 是具有唯一性的特殊值，用它来命名对象属性不容易导致重名。

Symbol 可以作为属性名，但无法查看和访问它的值

ES6 中有一些预定义符号，以 Symbol 的静态属性出现：Symbol.create、Symbol.iterator 等

可以使用 Symbol(..)原生构造函数来自定义符号。但是不能带 new 关键字，否则会报错。

```js
var mysym = Symbol('my own symbol');
mysym; // Symbol(my own symbol)
```

Symbol 主要用于私有属性。Symbol 并非对象，而是一种简单标量基本类型。

#### 3.4.5 原生类型

原生构造函数有自己的.prototype 对象，如 Array.prototype、String.prototype 等。这些对象包含其对应子类型所特有的行为特征。

```js
typeof Function.prototype; // "function"
Function.prototype(); //空函数

RegExp.prototype.toString(); // “/(?:)/"-空正则表达式

Array.isArray(Array.prototype); //true
```

Function.prototype 是一个空函数
RegExp.prototype 是一个正则表达式
Array.prototype 是一个空数组（length 为 0，但数组内有内容，如 constructor 等）

### 3.5 小结

JavaScript 为基本数据类型值提供了封装对象，称为原生函数（如 String、Number、Boolean 等）。他们为基本数据类型值提供了该子类型所持有的方法和属性。

对于简单标量基本类型值，比如“abc",如果要访问它的 length 属性或 String.prototype 方法，JavaScript 引擎会自动对该值进行封装来实现对这些属性和方法的访问。

## 第四章 强制类型转换

### 4.1 值类型转换

将值从一种类型转换为另一种类型通常称为类型转换（type casting)，这是显式的情况；隐式的情况称为**强制类型转换**（coerction）

JavaScript 中的强制类型转换总是返回标量基本类型值，如字符串、数字和布尔值，不会返回对象和函数。“封装”是为标量基本类型值封装一个响应类型的对象，但这并非严格意义上的强制类型转换。

也可以这样区分：类型转换发生在静态类型语言的编译阶段，而强制类型转换则发生在动态类型语言的运行时（runtime）

然而在 JavaScript 中，通常将它们统称为强制类型转换，可以用“隐式强制类型转换（implicit coerciton)和”显式强制类型转换“（explicit coercion）来区分

区别：显式强制类型转换能从代码中被观察到；而隐式强制类型转换则不明显，通常是某些操作的副作用

```js
var a = 42;
var b = a + ''; //隐式强制类型转换
var c = String(a); //显式强制类型转换
```

### 4.2 抽象值操作

前提：掌握字符串、数字和布尔值之间类型转换的基本规则（ES5 规范第 9 节中有定义一些“抽象操作”，即仅供内部使用的操作和转换规则。）。

#### 4.2.1 toString

规范 9.8 节中定义了抽象操作 toString，它负责处理非字符串到字符串的强制类型转换

基本类型值的字符串化规则：

- null 转换为"null"
- undefined 转换为"undefined"
- true 转换为"true"
- 数字的字符串化遵循通用规则
  极小和极大的数字使用指数形式
  ```js
  var a = 1.07 * 1000 * 1000 * 1000 * 1000 * 1000 * 1000 * 1000;
  a.toString(); //'1.07e+21'
  ```

对普通对象来说，除非自行定义，否则 toString()（Object.prototype.toString())返回内部属性[[Class]]的值，如"[[object Object]]"

如果对象有自己的 toStirng 方法，字符串化时就会调用该方法并使用其返回值

```js
var a = [1, 2, 3];
a.toString(); //"1,2,3"
```

JSON 字符串化
工具函数 JSON.stringify(..)在将 JSON 对象序列化为字符串时也用到了 toString。JSON 字符串化并非严格意义上的强制类型转换，规则：

简单值，JSON 字符串化和 toString()的效果基本相同，只不过序列化的结果总是字符串

```js
JSON.stringify(42); // "42"
JSON.stringify('42'); // ""42""
JSON.stringify(null); // "null"
JSON.stringify(true); // "true"
```

安全的 JSON 值（JSON-safe)都可以使用 JSON.stringity(..)字符串化。安全的 JSON 值是指能够呈现有效 JSON 格式的值。

不安全的 JSON 值

- undefined
- function
- symbol
- 包含循环引用的对象

JSON.stringity 在对象中遇到 undefined、function 和 symbol 时会自动将其忽略，在数组中则会返回 null（以保证单元位置不变）

```js
JSON.stringify(undefined); // undefined
JSON.stringify(function () {}); // undefined
JSON.stringify([1, undefined, function () {}, 4]); // "[1,null,null,4]"
JSON.stringify({ a: 2, b: function () {} }); // "{"a":2}"
```

如果对象中定义了 toJSON()方法，JSON 字符串化时会首先调用该方法，然后用它的返回值来进行序列化。

如果要对含有非法 JSON 值的对象做字符串化，或者对象中的某些值无法被序列化时，就需要定义 toJSON 方法来返回一个安全的 JSON 值

JSON.stringify(..)并不是强制类型转换。但是它涉及 toString 强制类型转换：

1. 字符串、数字、布尔值和 null 的 JSON.stirngify 规则与 toString 基本相同
2. 如果传递给 JSON.stringify 的对象中定义了 toJSON 方法，那么该方法会在字符串化前调用，一遍将对象转换为安全的 JSON 值

#### 4.2.2 toNumber

有时我们需要将非数字值当做数字来使用，比如数学运算。为此 ES5 规范在 9.3 节定义了抽象操作 toNumber：true 转换为 1，false 转换为 0，undefined 转换为 NaN，null 转换为 0

toNumber 对字符串的处理基本遵循数字常量的相关规则/语法。处理失败时返回 NaN。不同之处是**toNumber 对以 0 开头的十六进制数并不按十六进制处理（而是按十进制）**

对象（包括数组）会首先被转换为相应的基本类型值，如果返回的是非数字的基本类型值，则再遵循以上规则将其强制转换为数字。

为了将值转换为相应的基本类型值，抽象操作 toPrimitive 会首先检查该值是否有 valueOf 方法。如果有并且返回基本类型值，就使用该值进行强制类型转换。如果没有就使用 toString 的返回值来进行强制类型转换

如果 valueOf 和 toString 均不返回基本类型值，会产生 TypeError 错误。

从 ES5 开始，使用 Object.create(null)创建的对象[[Prototype]]属性为 null，并且没有 valueOf 和 toString 方法，因此无法进行强制类型转换。

```js
var a = {
  valueOf: function () {
    return '42';
  },
};
var b = {
  toString: function () {
    return '42';
  },
};
var c = [4, 2];
c.toString = function () {
  return this.join('');
};

Number(a); // 42
Number(b); // 42
Number(c); // 42
Number(''); //  0
Nubmer([]); // 0
Number(['abc']); //NaN
```

#### 4.2.3 toBoolean

JavaScript 中有两个关键词 true 和 false，分别代表布尔类型中的真和假。JavaScript 中布尔值和数字是不一样的。

**假值（falsy value)**
JavaScript 中的值可以分为以下两类：

- 可以被强制类型转换为 false 的值
- 其它

ES5 规范定义了抽象操作 toBoolean，列举了布尔强制类型转换所有可能出现的结果。
以下这些是假值：

- undefined
- null
- false
- +0、-0 和 NaN
- ''
  可以理解为：假值列表之外的值都是真值

**假值对象（falsy object)**

```js
var a = new Boolean(false);
var b = new Number(0);
var c = new String('');

var d = Boolean(a && b && c);
d; //true

a && b && c; //String对象，内容为''

if (document.all) {
  /*_it's IE_*/
}
```

**真值（truthy value)**

真值就是假值列表之外的值。

```js
var a = 'false';
var b = '0';
var c = "''";
var d = Boolean(a && b && c);
d; //true

var a1 = [];
var b1 = {};
var c1 = function () {};
var d1 = Boolean(a1 && b1 && c1);
d1; //true
```

### 4.3 显式强制类型转换

显式强制类型转换是那些显而易见的类型转换。

#### 4.3.1 字符串和数字之间的类型转换

两个内建函数：

- String(..)
  遵循 toString 规则
- Number(..)
  遵循 toNumber 规则

它们前面没有 new 关键字，不创建封装对象

其它方法：

- toString
- toNumber
- +c

**日期显式转换为数字**

+可以将日期（Date）对象强制类型转换为数字，返回结果是 Unix 时间戳，以微妙为单位（从 1970 年 1 月 1 日 00:00:00 UTC 到当前时间）

```js
var d = new Date('Mon, 18 Aug 2014 08:53:06 CDT');
+d; // 140xxxxx

var timestap = +new Date();

var timesatp1 = +new Date();

// 替换方案

var ts1 = new Date().getTime();
var ts2 = Date.now(); //ES5引入
```

**奇特的~运算符（非）**

位运算符只适用于 32 位整数，运算符会强制操作数使用 32 位格式。这是通过 toInt32 实现的
toInt32 首先执行 toNumber 强制类型转换，然后在执行 toInt32

```js
0 | -0; // 0
0 | NaN; // 0
0 | Infinity; // 0
0 | -Infinity; // 0
```

以上特殊数字无法以 32 位格式呈现（因为它们来自 64 位 IEEE 754 标准），因此 toInt32 返回 0
~首先将值强制类型转换为 32 位数字，然后执行“非”
~返回 2 的补码

**字位截除**
~~用来解除数字值的小数部分，第一个~执行 toInt32 并反转字位，第二个~再进行一次字位反转，即将所有字位反转为原值，最后得到的还是 toInt32 的结果
注意：

1. ~~只适用于 32 位数字
2. ~~对负数的处理与 Math.floor()不同
   ```js
   Math.floor(-49.6); // -50
   ~~-49.6; // -49
   ```

#### 4.3.2 显式解析数字字符串

解析字符串中的数字和将字符串强制类型转换为数字的返回结果都是数字。但解析和转换区别明显：

```js
var a = '42';
var b = '42px';

Number(a); //42
parseInt(a); //42

Number(b); //isNaN
parseInt(b); // 42
```

**解析**允许字符串含有非数字字符，解析按照从左到右的顺序，如果遇到费数字字符就停止；而**转换** 不允许出现非数字字符，否则会失败并返回 NaN

注意：parseInt 针对的是字符串值

一些奇奇怪怪的栗子：

```js
parseInt(1 / 0, 19); // 18(1/0=>'Infinity'=>字符串首字符I=>18)
parseInt(0.000008); // 0 ('0'来自于'0.000008')
parseInt(0.0000008); // 8 ('8'来自于'8e-7')
parseInt(false, 16); // 250 ('fa'来自于'false')
parseInt(parseInt, 16); // 15 ('f'来自于'function..')
parseInt('0x10'); // 16
parseInt('103', 2); // 2
```

#### 4.3.3 显式转换为布尔值

Boolean(..)，不常用
显式强制类型转换为布尔值最常用的方法是!!

建议使用 Boolean(a)和!!来进行显式强制类型转换。

### 4.4 隐式强制类型转换

隐式强制类型转换指的是那些隐蔽的强制类型转换。

#### 4.4.1 隐式地简化

#### 4.4.2 字符串和数字之间的隐式强制类型转换

如果+的其中一个操作数是字符串（或者通过以上步骤可以得到字符串），则执行字符串拼接；否则执行数字加法。

如果+的其中一个操作数为对象，则首先对其调用 toPrimitive 抽象操作，该抽象操作再调用[[DefaultValue]]，以数字作为上下文

a + '' 和 String(a) 的差别：a + '' 会对 a 调用 valueOf 方法，然后通过 toString 将返回值转换为字符串。而 String(a)则是直接调用 toString

#### 4.4.3 布尔值到数字的隐式强制类型转换

#### 4.4.4 隐式强制类型转换为布尔值

会发生布尔值隐式强制类型转换的情况：

1. if 语句中的条件判断表达式
2. for 语句中的条件判断表达式
3. while 和 do-while 中的条件判断表达式
4. ? : 中的条件判断表达式
5. 逻辑运算符||和&&左边的操作数

以上情况，非布尔值会被隐式强制类型转换为布尔值，遵循 toBoolean 规则

#### 4.4.5 || 和 &&

不应被叫做“逻辑运算符”，而是应该叫“选择器运算符（selector operators)”或者“操作数选择器运算符（operand selector operators)”，因为在 JavaScript 中它们的返回值是两个操作数中的一个（且仅一个）

||和&&首先对第一个操作数执行条件判断，如果其不是布尔值就先进行 toBoolean 强制类型转换，然后再执行条件判断

|| 如果条件判断结果为 true 就返回第一个操作数，否则返回第二个
&& 如果条件判断结果为 true 则返回第二个操作数，否则返回第一个

常用方法（短路机制）：

```js
a = a || 'hello';
b && func();
```

#### 4.4.6 符号的强制类型转换

ES6 允许从 Symbol 到字符串的显式强制类型转换，然而隐式强制类型转回会产生错误。

```js
var s1 = Symbol('cool');
String(s1); // "Symbol(cool)"

s1 + ''; // TypeError: Cannot convert a Symbol value to a string
```

Symbol 不能够被强制类型转换为数字，显式和隐式都会产生错误
Symbol 可以被强制类型转换为布尔值，显示和隐式结果都是 true

### 4.5 宽松相等和严格相等

常见误区：==检查值是否相等，===检查值和类型是否相等
正确解释：==允许在相等比较重进行强制类型转换，而===不允许

#### 4.5.1 相等比较操作的性能

==和===都会检查操作数的类型。区别在于操作数类型不同时它们的处理方式不同
二者性能相差不大

#### 4.5.2 抽象相等

ES5 规范 11.9.3 节的“抽象相等比较算法”定义了==运算符的行为

注意点：

- NaN 不等于 NaN
- +0 等于 -0

**字符串和数字之间的相等比较**

1. 如果 Type(x)是数字，Type(y)是字符串，则返回 x== toNumber(y)的结果
2. 如果 Type(x)是字符串，Type(y)是数字，则返回 toNumber(x) ==y 的结果

**其它类型和布尔类型之间的相等比较**

==最容易出错的一个地方就是 true 和 false 与其它额理性之间的相等比较

## 第五章 语法

# 第二部分 异步和性能

如果要整体了解一个人的核心 JavaScript 技能，我想最重要的是他们会**_如何使用闭包_**以及**_如何充分利用异步_**。

## 第 1 章 异步：现在与将来

核心问题：如何表达和控制持续一段时间的程序行为

这不仅仅是指从 for 循环开始到结束的过程。它是指程序的一部分现在运行，而另一部分则在将来运行 - 现在和将来之间有段间隙，在这段间隙中，程序没有活跃执行。例如：

- 等待用户输入
- 从数据库或文件系统请求数据
- 通过网络发送数据并等待响应
- 以固定时间间隔执行重复任务

在诸如此类的场景中，程序都需要管理这段时间间隙的状态

**_程序中现在运行的部分和将来运行的部分之间的关系就是异步编程的核心 _**

几个重要的问题：

1. 异步到底是如何出现的
2. 异步为什么会出现
3. 处理异步有哪些方法

### 1.1 分块的程序

可以把 JavaScript 程序写在单个的 js 文件中，但是这个程序几乎一定是由多个块构成的。这些块中只有一个是现在执行，其它的则会在将来执行。**_最常见的块单位是函数_**。

多数 JavaScript 新手程序员都会遇到的问题：程序中将来执行的部分不一定是在现在运行的部分执行完之后就立即执行。换句话说，现在无法完成的任务将会异步完成，因此并不会出现人们本能地认为会出现的或希望出现的阻塞行为。
考虑：

```js
// ajax是某个库中提供的某个ajax函数
var data = ajax("http://some.url.1);

console.log(data); // 啊哦！data通常不会包含ajax结果
```

标准 ajax 请求不是同步完成的，这意味着 ajax 函数还没有返回任何值可以赋给变量 data。如果 ajax 能够阻塞到响应返回，那么 data=..的赋值就会正常工作。
但是我们并不是这么使用 ajax 的。现在我们发出一个异步 ajax 请求，然后在将来才能得到返回的结果。

从现在到将来的“等待”，最简单的方法是使用一个通常称为回调函数的函数：

```js
ajax('http://some.url.1', function myCallbackFunc(data) {
  console.log(data); // yeah! 这里得到了一些数据
});
```

可能你已经听说过，可以**_发送同步 ajax 请求。尽管技术上说是这样，但是，在任何情况下都不应该使用这种方式_**，因为它会锁定浏览器 UI（按钮、菜单、滚动条等），并阻塞所有的用户交互。这是一个可怕的想法，一定要避免。
举个例子：

```js
function now() {
  return 21;
}

function later() {
  answer = answer * 2;
  console.log('Meaning of life:', answer);
}

var answer = now();
setTimeout(later, 1000); // Meaning of life: 42
```

这个程序有两个块：现在执行的部分，以及将来执行的部分。
现在：

```js
function now() {
  return 21;
}

function later(){..}

var answer = now();

setTimeout(later, 1000);
```

将来要执行的部分：

```js
answer = answer * 2;
cosnole.log('Meaning of life:', answer);
```

现在这一块在程序运行之后就会立即执行。但是 setTimeout 还设置了一个事件在将来执行，所以 later()的内容会在之后的某个时间（从现在起 1000 毫秒之后）执行。

任何时候，只要把一段代码包装成一个函数，并指定它在响应某个事件（定时器、鼠标点击、ajax 响应等）时执行，你就是在代码中创建了一个将来执行的块，也由此在这个程序中引入了异步机制。

异步控制台

并没啥规范或一组需求指定 console.\*方法族如何工作-它们不是 JavaScript 正式的一部分，而是由**_宿主环境_**添加到 JavaScript 中的。因此，不同的 browser 和 JavaScript 环境可以按照自己的意愿来实现，有时候这会引起混淆。某些条件下，某些 browser 的 cosnole.log 并不会把传入的呢日用立即输出。出现这种情况的主要原因是：在许多程序中，I/O 是非常低速的阻塞部分。所以浏览器在后台异步处理控制台 I/O 能够提高性能，这时用户甚至可能意识不到其发生：

```js
var a = {
  index: 1,
};
console.log(a); // ??

a.index++;
```

有时候程序会显示{index: 2}。到底什么时候控制台 I/O 会延迟，甚至能够被观察到，这都是不确定的。如果在调试的过程中遇到对象在 console.log 语句之后被修改，可你却看到了意料之外的结果，**_要意识到这可能是这种 I/O 的异步化造成的_**。
如果遇到这种少见的情况，最好的选择是在 JavaScript 调试器中使用断点，而不要依赖控制台输出。次优的方案是把对象序列化到一个字符串中，以强制执行一次“快照”，比如通过 JSON.stringify(...)

### 1.2 事件循环

尽管你显然能够编写异步 JavaScript 代码，但直到最近（ES6)，JavaScript 才真正内建有直接的异步概念。
事实上，**_JavaScript 引擎本身所做的只不过是在需要的时候，在给定的任意时刻执行程序中的单个代码块_**。

“需要”，谁的需要？这正是关键所在！

JavaScript 引擎并不是独立运行的，它运行在宿主环境中，对多数开发者来说通常就是 Web 浏览器（目前 js 已经嵌入到了从机器人到电灯泡等各种各样的设备中）。

所有这些环境都有一个共同点，即它们都提供了一种机制来处理程序中多个代码块的执行，且执行每块时调用 JavaScript 引擎，这种机制被称为**_事件循环_**。

JavaScript 引擎本身并没有时间的概念，只是一个按需执行 JavaScript 任意代码片段的环境。“事件”调度总是由包含它的环境进行。举个例子：
如果你的 JS 程序发出一个 Ajax 请求，从服务器获取一些数据，那你就在回调函数中设置好响应代码，然后 JavaScript 引擎会通知宿主环境：“嘿，现在我要暂停执行，你一旦完成网络请求，拿到了数据，就请调用这个函数”。
然后浏览器就会设置侦听来自网络的响应，拿到要给你的数据之后，就会把回调函数插入到事件循环，以此实现对这个回调的调度执行。
事件循环伪代码：

```js
// eventloop是一个用作队列的数组
// FIFO
var eventLoop = [];
var event;

// 永远执行
while (true) {
  // 一次tick
  if (eventLoop.length > 0) {
    // 拿到队列中的下一个event
    event = eventLoop.shift();
    // 现在，执行下一个事件
    try {
      event();
    } catch (err) {
      reportError(err);
    }
  }
}
```

以上代码只用来辅助说明概念。你可以看到，有一个用 while 循环实现的持续运行的循环，循环的每一轮成为一个 tick。对每个 tick 而言，如果在队列中有等待事件，那么就会从队列中摘下一个事件并执行。这些事件就是你的回调函数。

setTimeout 并没有把你的回调函数挂在事件循环队列中。它所做的是设定一个定时器。当定时器到时后，环境会把你的回调函数放在事件循环中，这样在未来的某个时刻的 tick 就会取出并执行这个回调。

如果这时事件循环中已经有 20 个项目了会怎么样呢？你的回调就会等待。它得排在其它项目后面-通常没有抢占式的方式支持直接将其排到队首。这也是 setTimeout 定时器精度不高的原因。大体来说，只能确保你的回调不会在指定的时间间隔之前运行，但可能会在那个时刻运行，也可能在那之后运行，要根据事件队列的状态而定。

所以换句话说就是：程序通常分成了很多小块，在事件循环队列中一个接一个地执行。严格来说，和你的程序不直接相关的其它事件也可能会插入到队列中。

前面提到“直到最近”是指从 ES6 从本质上改变了在哪里管理事件循环。本来它几乎已经是一种正式的技术模型了，但现在 ES6 精确指定了事件循环的工作细节，这意味着在技术上将其纳入了 JavaScript 引擎的势力范围，而不是只由宿主环境来管理。这个改变的一个主要原因就是 ES6 中 Promise 的引入，因为这项技术要求对事件循环队列的调度运行能够直接进行精细控制。

### 1.3 并行线程

“异步”和“并行”是完全不同的概念。**_异步是关于现在和未来的时间间隙；而并行是关于能够同时发生的事情_**。
并行计算最常见的工具就是**_进程和线程_**。进程和线程独立运行，并可能同时运行：在不同的处理器，甚至不同的计算机上，但多个线程能够共享单个进程的内存。
事件循环把自身的工作分为一个个任务并顺序执行，不允许对共享内存的并行访问和修改。通过分立线程中彼此合作的事件循环，并行和顺序执行可以共存。

并行线程的交替执行和异步事件的交替调度，其粒度是完全不同的。

```js
function later() {
  answer = answer * 2;
  console.log('Meaning of life:', answer);
}
```

尽管 later()的所有内容被看做单独的一个事件循环列表项，但如果考虑到这段代码是运行在一个线程中，实际上可能有很多个不同的底层运算。比如 answer = answer \* 2 需要先加载 answer 的当前值，然后把 2 放到某处并执行乘法，取得结果之后保存回 answer 中
在并行系统中，同一个程序中可能有两个不同的线程在运转，这时很可能就会得到不确定的结果。

```js
var a = 20;
function foo() {
  a = a + 1;
}

function bar() {
  a = a * 2;
}
ajax('http://some.url.1', foo);
ajax('http://some.url.2', bar);
```

根据 JavaScript 的单线程特性，a 的值可能为 42 或者 41，具体取决于 foo 和 bar 的执行顺序
如果共享同一数据的 JavaScript 并行执行的话，还可能会出现 44 和 21 的结果

JavaScript 从不跨线程共享数据。

**_完整执行_**

由于 JavaScript 的单线程特性，foo()和 bar()中的代码具有原子性。也就是说，一旦 foo()开始运行，它的所有代码都会在 bar 中的任意代码运行之前完成。这称为**_完整运行（run-to-completion)特性_**。

在 JavaScript 的特性中，这种**_函数顺序的不确定性就是通常所说的竞态条件_**（race condition)，foo()和 bar()相互竞争，看谁先运行。

### 1.4 并发

两个或多个“进程”同时执行就出现了并发，不管组成他们的单个运算是否并行执行（在独立的处理器或处理核心上同时运行）。可以把并发看做“进程”级（或者任务级）的并行，与运算级的并行（不同处理器上的线程）相对。

单线程事件循环是并发的一种形式。

#### 1.4.1 非交互

两个或多个“进程”在同一个程序内并发地交替运行它们的步骤/事件时，如果这些任务彼此不相关，就不一定需要交互。**_如果进程间没有相互影响的话，不确定性是完全可以接受的_**。

```js
var res = {};
function foo(results) {
  res.foo = results;
}

function bar(results) {
  res.bar = results;
}

ajax('http://some.url.1', foo);
ajax('http://some.url.2', bar);
```

foo()和 bar()是两个并发执行的“进程”，按照什么顺序执行时不确定的。但是，我们构建程序的方式使得无论按哪种顺序执行都无所谓，因为它们是独立运行的，不会相互影响。
这并不是竞态条件 bug，因为不管顺序如何，代码总会正常工作。

#### 1.4.1 交互

更常见的情况是：并发的“进程”需要相互交流，通过作用域或 DOM 间接交互。如果出现这样的交互，就需要对它们的交互进行协调以避免竞态的出现。

```js
var res = [];
function response(data) {
  res.push(data);
}
ajax('http://some.url.1', response);
ajax('http://some.url.2', response);
```

这里的并发“进程”是两个用来处理 ajax 响应的 response()调用，它们可能以任意顺序运行。我们假定期望的行为是 res[0]存放 http://some.url.1 的结果，res[1]存放http://some.url.2 的结果。此时就需要协调交互顺序来处理竞态条件

```js
var res = [];
function response(data) {
  if (data.url == 'http://some.url.1') {
    res[0] = data;
  } else if (data.url == 'http://some.url.2') {
    res[1] = data;
  }
}
ajax('http://some.url.1', response);
ajax('http://some.url.2', response);
```

如此就避免了竞态条件引起的不确定性。

#### 1.4.1 协作

还有一中并发合作方式，称为并发协作（cooperative concurrency)。这里的重点不再是通过共享作用域中的值进行交互。这里的目标是取得一个长期运行的“进程”，并将其分割成多个步骤或多批任务，使得其它并发“进程”有机会将自己的运算插入到事件循环队列中交替运行。
考虑一个需要遍历很长的结果列表进行值转换的 ajax 响应处理函数。

```js
var res = [];
// response从ajax调用中取得结果数据
function response(data) {
  // 添加到已有的res数组
  res = res.concat(
    data.map(function (val) {
      return val * 2;
    }),
  );
}

ajax('http://some.url.1', response);
ajax('http://some.url.2', response);
```

如果http://some.url.1首先取得结果，那么整个列表会立刻映射到res中。如果有1000万条记录的话，可能就需要运行相当一段时间了。在此期间，页面上的其它代码都不能运行，包括不能有其它的response调用和UI刷新，甚至是像滚动、输入、按钮点击这样的用户事件。

```js
var res = [];
// response从ajax调用中取得结果数据
function response(data) {
  // 一次处理1000个
  var chunk = data.splice(0, 1000);
  // 添加到已有的res数组
  res = res.concat(
    chunk.map(function (val) {
      return val * 2;
    }),
  );
  // 还有剩下的需要处理吗
  if (data.length > 0) {
    // 异步调度下一次批处理
    setTimeout(function () {
      response(data);
    }, 0);
  }
}

ajax('http://some.url.1', response);
ajax('http://some.url.2', response);
```

我们把数据集合放在最多包含 1000 条项目的块总。这样，就确保了“进程”运行时间会很短，即使这意味着需要更多的后续“进程”，因为事件循环队列的交替运行会提高站点/app 的响应。
这里使用 setTimeout(..0)进行异步调度，基本上它的意思就是“把这个函数插入到当前事件循环队列的结尾处”
严格来说，setTimeout(..0)并不直接把项目插入到事件循环队列。定时器会在有机会的时候插入事件。举例来说：两个连续的 setTimeout(..0)调用不能保证会严格按照调用顺序处理，所以各种情况都可能出现，比如定时器漂移，在这种情况下，这些事件的顺序就不可预测。**_在 Nodejs 中，类似的方法是 process.nextTick(...)_**.

### 1.5 任务

在 ES6 中，有一个新的概念建立在事件循环队列之上，叫做“任务队列（job queue)"。这个概念带来的最大影响可能是 Promise 的异步特性
可以这么理解：job queue 是挂在事件循环队列的每个 tick 之后的一个队列。在事件循环的每个 tick 中，可能出现的异步动作不会导致一个完整的新事件添加到事件循环丢列中，而会在当前 tick 的任务队列末尾添加一个项目（一个任务）
事件循环队列类似于游乐园游戏：玩过了一个游戏之后，需要重新到队尾排队才能再玩儿一次；而任务丢列类似于玩过了游戏之后，插队接着玩儿。

一个 job 可能会引起更多 job 被添加到同一个 queue 末尾。故理论上说，任务循环（job loop)可能无限循环（一个任务总是添加另一个任务），进而导致程序的饿死，无法转移到下一个事件循环 tick

任务与 setTimeout 思路类似，但对顺序的保证性更强：尽可能早的将来

设想一个调度任务 API,schedule

```js
console.log('A');
setTimeout(function () {
  console.log('B');
}, 0);
// 理论上的“任务API"
schedule(function () {
  console.log('C');

  schedule(function () {
    console.log('D');
  });
});
```

可能你认为这里会打印 A B C D，但实际打印的结果是 A C D B。因为任务处理是在当前事件循环 tick 结尾处，且定时器触发是为了调度下一个事件循环 tick

Promise 的异步特性是基于任务的。

### 1.6 语句顺序

代码中语句的顺序和 JavaScript 引擎执行语句的顺序并不一定要一致。

```js
var a, b;
a = 10;
b = 30;

a = a + 1;
b = b + 1;
console.log(a + b);
```

JavaScript 引擎在编译这段代码之后，可能会发现通过重新安排这些语句的顺序有可能提高执行速度。重点是，只要这个重新排序是不可见的，一切都没问题。
比如，引擎可能发现，其实这样更快：

```js
var a, b;
a = 10;
a++;

b = 30;
b++;

console.log(a + b);
```

或者这样

```js
var a, b;

a = 11;
b = 31;

console.log(a + b);
```

甚至这样

```js
console.log(42);
```

以上所有情况中 JavaScript 引擎在编译期间执行的都是安全的优化，最后可见的结果都是一样的。

### 1.7 小结

JavaScript 程序总是至少分为两个块：第一块现在运行；下一块将来执行，以响应某个事件。尽管程序是一块一块执行的，但是所有这些块共享对程序作用域和状态的访问，所以对状态的修改都是在之前积累的修改之上进行的。

一旦有事件需要运行，事件循环就会运行，直到队列清空。事件循环的每一轮称为一个 tick。用户交互、IO 和定时器会向事件队列中加入事件。

任意时刻，一次只能从事件队列中处理一个事件。执行事件的时候，可能直接或者间接地引发一个或多个后续事件。

并发是指两个或多个事件链随时间发展交替执行，以至于从更高的层次看，就像是同时在运行（尽管在任意时刻只能处理一个事件）

通常需要对这些并发执行的“进程”（有别于操作系统中进程的概念）进行某种形式的交互协调，比如需要确保执行顺序或者需要防止竞态出现。这些“进程”也可以通过把自身分割成更小的块，以便其它“进程”插入进来

## 第 2 章 回调

### 2.1 continuation

回调函数包裹或者说封装了程序的延续（continuation）

一旦我们以回调的形式引入了单个 continuation（或者几十个），我们就容许了大脑工作方式和代码执行方式的分歧。一旦两者出现分歧，我们就得面对这样一个事实：代码变得难以理解、追踪、调试和维护

### 2.2 顺序的大脑

我们在假装并行执行多个任务时，实际上极有可能是在进行快速的上下文切换。这和异步事件并发机制类似。

大脑的工作方式有点类似于事件循环队列。

#### 2.2.1 执行与计划

我们的大脑可以看做类似于单线程运行的事件循环队列，就像 JavaScript 引擎那样。

我们大脑的运作方式，**_不是多任务，而是快速的上下文切换_**。

#### 2.2.2 嵌套回调与链式调用

```js
listen('click', function handler(evt) {
  setTimeout(function request() {
    ajax('http://some.url.1', function response(text) {
      if (text == 'hello') {
        handler();
      } else if (text == 'world') {
        request();
      }
    });
  });
});
```

这种代码被称为回调地狱（callback hell），有时也被称为毁灭金字塔（pyramid of doom)

一旦你只定了所有的可能事件和路径，代码就会变得非常复杂，以至于无法维护和更新。这才是回调地狱的真正问题所在。嵌套和缩进只是转移注意力的枝节。

我们的顺序阻塞式的大脑计划行为无法很好的映射到面向回调的异步代码。这就是回调方式的最主要的缺陷：对于它们在代码中表达异步的方式，我们的大脑需要很努力才能同步得上。

### 2.3 信任问题

```js
// A
ajax("..", function(..) {
  // C
});
// B
```

A 和 B 发生在现在，在 JavaScript 主程序的执行控制下。C 会延迟到将来发生，并且是在第三方的控制下，本例中就是函数 ajax 中。

控制转移是回调驱动设计最严重的问题。它以这样一个思路为中心：有时候 ajax(...)（也就是你交付回调 continuation 的第三方）不是你编写的代码，也不在你的直接控制下。多数情况下，它是某个第三方提供的工具。

我们把这称为控制反转（inversion of control），也就是把自己程序一部分的执行控制交给某个第三方。在你的代码和第三方工具之间有一份并没有明确表达的契约。

#### 2.3.1 五个回调的故事

#### 2.3.2 不只是别人的代码

思考：你能够真正新人理论上（在自己的代码库中）你可以控制的工具吗？

多数人都同意：至少在某种程度上我们应该在内部函数中构建一些防御性的输入参数检查，以便减少或阻止无法预料的问题。
过分信任输入：

```js
function addNumbers(x, y) {
  // +是可以重载的，通过类型转换，也可以是字符串连接
  // 所以根据传入参数的不同，这个运算并不是严格安全的
  return x + y;
}
addNumbers(21, 21); //42
```

针对不信任输入的防御性代码：

```js
function addNumbers(x, y) {
  // 确保输入为数字
  if (typeof x != 'number' || typeof y != 'number') {
    throw Error('Bad parameters');
  }
  // 如果到达这里，可以通过+安全地进行数字相加
  return x + y;
}
addNumbers(21, 21); // 42
addNumbers('21', 21); // Error: "Bad parameters"
```

依旧安全但更友好一些

```js
function addNumbers(x, y) {
  // 确保输入为数字
  x = Number(x);
  y = Number(y);
  //+安全地进行数字相加
  return x + y;
}
addNumbers(21, 21); // 42
addNumbers('21', 21); // 42
```

这种类型检查/规范化的过程对于函数输入是很常见的，即使是对于理论上完全可以信任的代码。大体来说就是：**_信任，但要核实_**

对于异步函数回调的组成，我们也应该做同样的事情。但是回调并没有为我们提供任何东西来支持这一点，我们不得不自己构建全部的机制，而且通常为每个异步调用回调重复这样的工作最后都成了负担。

回调最大的问题是控制反转，它会导致信任链的完全断裂。

如果你的代码中使用了回调，尤其是但也不限于使用第三方工具，而且你还没有应用某种逻辑来解决所有这些控制反转导致的信任问题，那你的代码现在已经有了 bug。

确实是地狱

### 2.4 省点回调

回调设计存在几个辩题，意在解决前面讨论的一些信任问题（不是全部！！！）
分离回调：

```js
function success(data) {
  console.log(data);
}

function failure(err) {
  console.error(err);
}

ajax('http://some.url.1', success, failure);
```

以上，API 的出错处理函数 failure 常常是可选的，如果没有提供的话，就是假定这个错误可以吞掉。

"error-first"风格回调：

```js
function response(err, data) {
  if (err) {
    console.error(err);
  } else {
    console.log(data);
  }
}

ajax('http://some.url.1', response);
```

Node.js 都采用这种风格。其中回调的第一个参数保留用作错误对象。如果成功，该参数被清空/置假。否则第一个参数就会被置起/置真。

以上两种方案，都应该注意：

1. 这并没有真正解决主要的信任问题。这并未涉及阻止或过滤不想要的重复调用回调的问题。更糟的是，你还可能同时得到成功或失败的结果，或者都没有，并且你不得不编码处理所有这种情况
2. 以上方式更加冗长和模式化，可复用性不高，所以你还得给应用中每个回调添加此类代码

设置一个超时取消事件，可以构造个工具：

```js
function timeoutify(fn, delay) {
  var intv = setTimeout(function () {
    intv = null;
    fn(new Error('Timeout!'));
  }, delay);

  return function () {
    if (intv) {
      clearTimeout(intv);
      fn.apply(this, arguments);
    }
  };
}
```

以下为使用方式

```js
// error-first
function foo(err, data) {
  if (err) {
    console.error(err);
  } else {
    console.log(data);
  }
}

ajax('http://some.url.1', timeoutify(foo, 500));
```

还有一个问题是过早调用。这可能实际上是指在某个关键任务完成之前调用回调。

有效建议：永远异步调用回调，即使就在事件循环的下一轮，这样，所有回调就都是可预测的异步回调了。

示例代码：

```js
function result() {
  console.log(a);
}
var a = 0;
ajax('..pre-cached-url', result);
a++;
```

asyncify 工具

```js
function asyncify(fn) {
  var orig_fn = fn;
  var intv = setTimeout(function () {
    intv = null;
    if (fn) fn();
  }, 0);

  fn = null;

  return function () {
    // 触发太快，在定时器intv触发指示异步转换发生之前？
    if (intv) {
      fn = orig_fn.bind.apply(
        orig_fn,
        // 把封装器的this添加到bind(..)调用的参数中，
        // 以及科利华所有传入参数
        [this].concat([].slice.call(arguments)),
      );
    }
    // 已经是异步
    else {
      orig_fn.apply(this, arguments);
    }
  };
}
```

### 2.5 小结

回调函数是 JavaScirpt 异步的基本单元。

大脑对于事情的计划方式是线性的、阻塞的、单线程的语义，但是回调表达异步流程的方式是非线性的、非顺序的，这使得正确推导这样的代码难度很大。

我们需要一种更同步、更顺序、更阻塞的方式来表达异步，就像我们的大脑一样。

回调会受到控制反转的影响，因为回调暗中把控制权交给第三方来调用你代码中的 continuation。这种控制转移导致一系列的信任问题，比如回调被调用的次数是否会超出预期。

我们需要一个通用的方案来解决信任问题。无论我们创建多少回调，这一方案都应可以复用，且没有重复代码的开销。

## 第 3 章 Promise

通过回调表达程序异步和管理并发的两个主要缺陷：

1. 缺乏顺序性
2. 缺乏可信任性

首先要解决控制反转的问题：信任很脆弱，也很容易失去

我们用回调函数来封装程序中的 continuation，然后把回调交给第三方，期待其能够调用回调，实现正确的功能。通过这种形式，我们要表达的意思是：这是将来要做的事情，要在当前的步骤完成之后发生。

解决方法：把控制反转再反转回来。不把自己的程序的 continuation 传给第三方，而是期望第三方给我们提供了解其任务何时结束的能力，然后由我们自己的代码来决定下一步做什么

这种范式就成为 Promise。绝大多数 JavaScript/DOM 平台新增的异步 API 都是基于 Promise 构建的。

本章经常会使用“立即”一词，通常用来描述某个 Promise 协议（resolution）动作。但是，基本上在所有的情况下，这个“立即”指任务队列行为方面的意义，而不是严格同步的现在。

### 3.1 什么是 Promise

#### 3.1.1 未来值

IOU(I owe you) Promise

承诺值（value-Promise)

1. 现在值与将来值
   回调：如何处理未来值
   如果有的语句现在完成，有的语句将来完成，那就会在程序中引起混乱
2. Promise 值
   ```js
   function add(xPromise, yPromise) {
     return Promise.all([xPromise, yPromise]).then(function (values) {
       return values[0] + values[1];
     });
   }
   //fetchX()、fetchY()返回响应值的promise，可能已经就绪，也可能以后就绪
   add(fetchX(), fetchY()).then(function (sum) {
     console.log(sum);
   });
   ```
   Promise 的协议结果：
3. 完成值总是编程给出的
4. 拒绝值，通常称为拒绝原因（rejection reason)，可能是程序逻辑直接设置的，也可能是从运行异常隐式得出的值

通过 Promise，调用 then 实际上可以接受两个函数，第一个用于完成情况，第二个用于拒绝情况：

```js
add(fetchX, fetchY).then(
  // 完成处理函数
  function (sum) {
    console.log(sum);
  },
  // 拒绝处理函数
  function (err) {
    console.error(err);
  },
);
```

由于 Promise 封装了依赖于时间的状态-等待底层值的完成或拒绝，所以 Promise 本身是与时间无关的。因此，Promise 可以按照可预测的方式组成，而不用关心时序或底层的结果。

一旦 Promise 决议，它就永远保持在这个状态。此时它就成为了不变值（immutable value)，可以根据需求多次查看。

Promise 是一种封装和组合未来值的易于复用的机制。

#### 3.1.2 完成事件

单独的 Promise 展示了未来值的特性。但也可以从其它角度看待 Promise 的决议：一种在异步任务中作为两个或更多步骤的流程控制机制，时序上的 this-then-that

假定要调用一个函数执行某个任务，我们不知道也不关心它的任何细节。这个函数可能立即完成任务，也可能需要一段时间才能完成。我们只需要知道函数啥时候结束，这样就可以进行下一个任务。换句话说：我们想要通过某种方式在函数完成的时候得到通知，以便可以继续下一步。

在 JavaScript 中，如果需要侦听某个通知，你可能会想到事件。因此可以把对通知的需求重新组织为对函数发出一个完成事件(completion event, 或 continuation)的侦听。

使用回调的话，通知就是任务调用的回调。而使用 Promise 的话，我们把这个关系反转了过来侦听来自函数的事件，然后在得到通知时，根据情况继续。
考虑如下伪代码：

```
foo(x){
  // 开始做点可能耗时的工作
}
foo(42)

on(foo "completion"){
  // 可以进行下一步了
}
on(foo "error") {
  // 出错了
}
```

我们调用 foo(..)，然后建立了两个事件侦听器，一个用于“completion”，一个用于“error”。本质来说，foo(..)不需要了解调用代码订阅了这些事件，这样就实现了“关注点分离“。遗憾的是，这样的代码需要 JavaScript 环境提供某些支持，而这种环境并不存在。
JavaScript 中更自然的表达方法：

```
function foo(x) {
  // 开始做点可能耗时的工作
  // 构建一个listener事件通知处理对象来返回
  return listener;
}
var evt = foo(42);
evt.on("completion", function(){
  // 可以进行下一步了
})
evt.on("error", function(){
  // 出错了
})
```

foo(..)显式创建并返回了一个事件订阅对象，调用代码得到这个对象，并在其上注册了两个事件处理函数。
对比回调的代码，这里的反转显而易见。这里没有把回调传给 foo(..)，而是返回一个名为 evt 的事件注册对象，由它来接受回调。

回调本身就表达了一种控制反转。所以对回调模式的反转实际上是对反转的反转，或称为反控制反转-把控制返还给调用代码。

一个重要的好处：可以把这个事件的侦听对象提供给代码中多个独立的部分，在 foo(..)完成的时候，它们都可以独立地得到通知，以执行下一步：

```js
var evt = foo(42);
// 让bar(..)侦听foo(..)的完成
bar(evt);
// 让baz(..)侦听foo(..)的完成
baz(evt);
```

对控制反转的恢复实现了更好的关注点分离。bar 和 baz 不需要牵扯到 foo 的调用细节，foo 也不需要知道 bar 和 baz 是否存在，或者是否在等待 foo 的完成通知。

本质上说：evt 对象就是分离的关注点之间的一个中立的第三方协商机制

Promise“事件”
事件侦听对象 evt 就是 Promise 的一个模拟。在基于 Promise 的方法中，前面的代码片段会让 foo(..)创建并返回一个 Promise 实例，而且这个 Promise 会被传递给 bar(..)和 baz(..)。

我们侦听的 Promise 协议“事件”严格来说并不算是事件，通常也不叫做“completion”或“error"。事实上，我们通过 then(..)注册一个 then 事件，更准确的说是 then(..)注册”fullfillment“和”rejection“事件。考虑

```js
function foo(x) {
  // 做一些可能耗时的工作
  // 构造并返回一个promise
  return new Promise(function (resolve, reject) {
    // 最终调用resovle(..)或者reject(..)
    // 这是这个promise的协议回调
  });
}

var p = foo(42);
bar(p);
baz(p);
```

new Promise(function(..){..})模式通常称为 revealing constructor。传入的函数会立即执行，它有两个参数，本例中为 resolve 和 reject。这些是 promise 的决议函数。resolve(..)通常标识完成，reject(..)则标识拒绝。

Promise 也可以只作为一种流程控制信号。

一旦 p 决议，不论是现在还是将来，下一个步骤总是相同的。

### 3.2 具有 then 方法的鸭子模型

根据一个值的形态（具有哪些属性）对这个值的类型做出一些假定。这种类型检查（type check）一般用术语鸭子类型（duck typing)来表示-“如果它看起来像只鸭子，叫起来像只鸭子，那它一定就是鸭子。

如果 thenable 鸭子类型误把不是 Promise 的东西识别为了 Promise，可能就是有害的。

### 3.3 Promise 信任问题

回顾一下只用回调编码的信任问题。把一个回调传入工具 foo(...)时可能出现的问题：

- 调用回调过早
- 调用回调过晚
- 回调不被调用
- 未能传递所需的环境和参数
- 吞掉可能出现的错误和异常

Promise 的特性就是专门用来为这些问题提供一个有效的可复用方案。

#### 3.3.1 调用过早

即使是立即完成的 Promise，也无法被同步观察到。也就是说，对一个 Promise 调用 then 的时候，即使这个 Promise 已经决议，提供给 then 的回调也总是会被异步调用

#### 3.3.2 调用过晚

Promise 创建对象调用 resolve(..)或 reject(..)时，这个 promise 的 then 注册的观察回调就会被自动调度。可以确信，这些被调度的回调在下一个异步事件点上一定会被触发。

同步查看是不可能的，故一个同步任务链无法以这种方式运行来实现按照预期有效延迟另一个回调的发生。也就是说，一个 Promise 决议后，这个 Promise 上所有的通过 then 注册的回调都会在下一个异步时机点上被立即调用。这些回调中的任意一个都无法影响或延迟对其它回调的调用。

```js
p.then(function () {
  p.then(function () {
    console.log('C');
  });
  console.log('A');
});
p.then(function () {
  console.log('B');
});
// A B C
```

这里，“C"无法打断或抢占”B"，这是由 Promise 的运作方式决定的。

Promise 调度技巧

两个独立的 Promise 上链接的回调的相对顺序无法可靠预测。

```js
var p3 = new Promise(function (resolve, reject) {
  resolve('B');
});

var p1 = new Promise(function (resolve, reject) {
  resolve(p3);
});

p2 = new Promise(function (resolve, reject) {
  resolve('A');
});

p1.then(function (v) {
  console.log(v);
});

p2.then(function (v) {
  console.log(v);
});
// A B
```

你永远都不应该依赖于不同 Promise 间回调的顺序和调度。

#### 3.3.3 回调未调用

没有任何东西（甚至 JavaScript 错误）能阻止 Promise 向你通知它的决议（如果它决议了的话）。如果你对一个 Promise 注册了一个完成回调和一个拒绝回调，那么 Promise 在决议时总会调用其中一个。

如果你的回调函数本身包含 JavaScript 错误，那可能就会看不到预期的结果，但实际上回调还是会被调用。

如果 Promise 本身永远不会被决议，Promise 也提供了解决方案，其使用了一种成为竞态的高级抽象机制：

```js
// 用于超时一个Promise的工具
function timeoutPromise(delay){
  return new Promise(function(resolve, reject){
    setTimeout(function(){
      reject("Timeout");
    }, delay);
  })
}
// 设置foo()超时
Promise.race(function([foo(), timeoutPromise(3000)]))
.then(function(){
  // foo(..)及时完成
}, function(err) {
  // 或者foo()被拒绝，或者只是没能按时完成
})
```

#### 3.3.4 调用次数过多或过少

Promise 只能被决议一次，所以任何通过 then 注册的回调就只会被调用一次。

#### 3.3.5 未能传递参数/环境值

Promise 至多只能有一个决议值。如果你没有用任何值显式决议，那么这个值就是 undefined。

如果使用多个参数调用 resolve()或者 reject()，第一个参数之后的所有参数都会被默默忽略。如果要传递多个值，你就必须把它们封装在单个值中个传递，比如通过一个数组或对象。

对环境来说，JavaScript 中的函数总是保持其定义所在的作用域的闭包，所以它们当然可以继续访问你提供的环境状态。

#### 3.3.6 吞掉错误或异常

如果拒绝一个 Promise 并给出一个理由，这个值就会被传给拒绝回调。
如果在 Promise 的创建过程中或在查看其决议结果过程中的任何时间点上出现了一个 JavaScript 异常错误，那这个异常就会被捕捉，并且会使这个 Promise 被拒绝。

#### 3.3.7 是可信任的 Promise 吗

Promise 并没有完全摆脱回调。它们只是改变了传递回调的位置。我们并不是把回调传递给 foo(..)，而是从 foo(..)得到某个东西（外观上看是一个真正的 Promise)，然后把回调传给这个东西。

包含在原生 ES6 Promise 实现中的解决方案就是 Promise.resolve(..)。

如果向 Promise.resolve()传递一个非 Promise、非 thenable 的立即值，就会得到一个用这个值填充的 promise。以下 p1 和 p2 的行为是完全一样的

```js
var p1 = new Promise(function (resolve, reject) {
  resolve(42);
});

var p2 = Promise.resolve(42);
```

如果向 Promise.resolve()传递一个真正的 Promise，就只会返回同一个 promise：

```js
var p1 = Promise.resolve(41);

var p2 = Promise.resolve(p1);

p1 === p2; // true
```

Promise.resolve(..)可以接受任何 thenable，将其解封为它的非 thenable 值。从 Promise.resolve()得到的是一个真正的 Promise，是一个可以信任的值。如果你传入的已经是真正的 Promise，那么你就会得到它本身。

#### 3.3.8 建立信任

Promise 这种模式通过可信任的语义把回调作为参数传递，使得这种行为更加合理可靠。通过把回调的控制反转反转回来，我们把控制权放在了一个可信任的系统（Promise)中，这种系统的设计目的就是为了使异步编码更清晰。

## 第 4 章 生成器

## 第 5 章 程序性能

## 第 1 章 性能测试与调优

```

```
