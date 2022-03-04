[toc]

# 第一章 类型

ES5.1 规范（http://www.ecma-international.org/ecma-262/5.1/）对此是如何界定的：
  本规范中的运算法则所操总的值均有相应的类型。本节中定义了所有可能出现的类型。ECMAScript类型又进一步细分为语言类型和规范类型。
  ECMAScript语言中所有的值都有一个对应的语言类型。ECMAScript语言类型包括Undefined、Null，Boolean、String、Number和Object.
***
  Algorithms within this specification manipulate values each of which has an associated type. The possible value types are exactly those defined in this clause. Types are further subclassified into ECMAScript language types and specification type.

  An ECMAScript language type corresponds to values that are directly manipulated by an ECMAScript programmer using the ECMAScript language. The ECMAScript language types are Undefined, Null, Boolean, String, Number and Object.

  A specification type corresponds to meta-values that are used within algorithms to describe the semantics of ECMAScript language constructs and ECMAScript language types. The specification types are Reference, List, Completion, Property Descriptor, Property Identifier, Lexical Environment, and Environment Record.

在本书中，我们这样来定义类型：对语言引擎和开发人员来说，类型是值的内部特征，它定义了值的行为，以使其区别于其他值

## 1.2 内置类型

Javascript有七种内置类型：
* 空值（null）
* 未定义（undefined）
* 布尔值（boolean)
* 数字（number）
* 字符串（string）
* 对象（object）
* 符号（symbol，ES6中新增）
可以使用typeof运算符来查看，其中有两种比较特别：
  ```
  typeof null === "object"; //true
  typeof function a(){} === 'function'; //true
  ```
  其中function是object的子类型，具体来说，function是callable object。

变量没有类型，但是它们持有的值有类型。类型定义了值的行为特征

undeclared表示变量还没有被声明过；undefined表示变量处于已声明未赋值的状态

# 第二章 值

##  2.1 数组

在JavaScript中，数组可以容纳任何类型的值

在创建“稀疏”数组（sparse array，即含有空白或空缺单元的数组）时要特别注意，空白单元的值默认为undefined

类数组->数组
Array.prototype.slice.call(arrayLike)
Array.from(arrayLike)

## 2.2 字符串

Javascript中字符串是不可变的，而数组是可变的。所以我们无法“借用”数组的可变成员函数，如reverse

## 2.3 数字

JavaScript只有一中数值类型：number，包含整数和小数  
JavaScript中的整数就是没有小数的十进制数  
JavaScript中数字类型是基于IEEE 754标准来实现的，该标准通常也被称为浮点数。JavaScript使用的是“双精度”格式（即64位二进制） 

toFixed(..)方法可以指定小数部分的显示位数  
~~~js
  let a = 42.59;
  a.toFixed(0); //43
  a.toFixed(1); // 42.6
  a.toFixed(3); //42.590
  ~~~

  toPrecision(..)方法用来指定有效数位的显示位数(字符串形式)
  ~~~js
  var a = 42.59;
  a.toPrecision(1); // '4e+1'
  a.toPrecision(2); // '43'
  ~~~

  使用数字常量调用该方法时，需要特别注意，.运算符会优先被识别为数字常量的一部分，然后才是对象属性访问运算符
  ~~~js
  //无效语法
42.toPrecision(3); // SyntaxError

// 下面语法都有效
(42).toPrecision(1);
0.42.toFixed(3);
42..toFixed(3);
  ~~~

  二进制浮点数最大的问题（所有遵循IEEE 754规范的语言都是如此），是会出现如下情况：
  ~~~js
  0.1 + 0.2 === 0.3; // false 0.30000000000000004
  ~~~

  判断0.1+0.2和0.3是否相等的方法
  最常见的方法就是设置一个误差范围，通常成为“机器精度（machine epsilon），对JavaScript的数字来说，这个值通常是2^-52(2.220446049250313e-16)
  ~~~js
  function numbersCloseEnoughToEqual(n1, n2) {
    return Math.abs(n1-n2) < Math.EPSILON;
  }

  numbersCloseEnoughToEqual( 0.1+0.2, 0.3);
  ~~~

  整数检测
    Number.isInteger(..)
  
  void运算符
    void 并不改变表达式的结果，只是让表达式不返回值；按惯例我们用void 0来获得undefined

NaN可以理解为：无效数值、失败数值或者坏数值  
isNaN(..)用来判断一个值是不是NaN，它有一个严重的缺陷：
~~~js
var a = 2 / 'abc'; // NaN
var b = 'foo'; // 'foo'

window.isNaN(a); // true
window.isNaN(b); // true 晕
~~~

判断一个值是否为NaN
  方法一：Number.isNaN(..)
  方法二：n !== n 
    NaN是JavaScript中唯一一个不等于自身的值

加法和减法运算不会得到-0（negative zero)

我们为什么需要负零？  
>有些应用程序中的数据需要以级数形式来表示（比如动画帧的移动速度），数字的符号位（sign）用来代表其它信息（比如移动方向）。此时如果一个值为0的变量失去了它的符号，它的方向信息就会丢失。所以保留0值的符号位可以防止这种情况的发生  
  
能使用==和===时就尽量不要使用Object.is()，因为前者效率更高，更为通用  

JavaScript引用指向的是值。如果一个值有10个引用，这些引用指向的都是同一个值，它们相互之间没有引用/指向关系

简单值（即标量基本类型，scalar primitive)总是通过值赋值的方式来赋值/传递，包括null、undefined、字符串、数字、布尔和symbol  
复合值（compound value)-对象（包括数组和封装对象）和函数，则总是通过引用复制的方式来赋值/传递  

由于引用指向的是值本身而非变量，所以一个引用无法更改另一个引用的指向。

### 2.4 小结

JavaScript中的数组是通过数字索引的一组任意类型的值。字符串和数组类似，但是它们的行为特征不同，在将字符作为数组来处理时需要特别小心。JavaScript中的数字包括整数和浮点型

基本类型中定义了几个特殊的值：
  null类型只有一个值null  
  undefined类型只有一个值undefined  
  所有变量在赋值之前默认值都是undefined  
  void运算符返回undefined

数字类型有几个特殊值
  > NaN
  > +Infinity
  > -Infinity  
  > -0

简单标量基本类型值（字符串和数字等）通过值赋值来赋值/传递；而复合值（对象等）通过引用复制来赋值/传递。JavaScript中的引用和其它语言中的引用/指针不同，它们不能指向别的变量/引用，只能指向值










