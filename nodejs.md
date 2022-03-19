# 疑问代码
```js
function AppFrame() {  
    events.EventEmitter.call(this);  
  ...
}
util.inherits(AppFrame, events.EventEmitter);    
```
AppFrame中的events.EventEmitter.call(this)用于实现对EventEmitter的初始化  
```js
function EventEmitter(opts) {
  EventEmitter.init.call(this, opts);
}

EventEmitter.init = function(opts) {

  if (this._events === undefined ||
      this._events === ObjectGetPrototypeOf(this)._events) {
    this._events = ObjectCreate(null);
    this._eventsCount = 0;
  }

  this._maxListeners = this._maxListeners || undefined;


  if (opts && opts.captureRejections) {
    if (typeof opts.captureRejections !== 'boolean') {
      throw new ERR_INVALID_ARG_TYPE('options.captureRejections',
                                     'boolean', opts.captureRejections);
    }
    this[kCapture] = Boolean(opts.captureRejections);
  } else {
    // Assigning the kCapture property directly saves an expensive
    // prototype lookup in a very sensitive hot path.
    this[kCapture] = EventEmitter.prototype[kCapture];
  }
};
```

# Node中使用import报错（cannot use import outside a module)

Node.js has two module systems: CommonJs modules and ECMAScript modules. By Default, Node.js will treat the following as CommonJS modules:
- Files with  .cjs extension
- Files with a .js extension when the nearest parent package.json file contains a top-level field "type" with a value of "commonjs"
- Files with a .js extension when the nearest parent package.json file doesn't contain a top-level field "type".
- Files with an extendsion that is not .mjs, .cjs, .json, .node or .js

Determining module systems
Node.js will treat the following  as ES modules when passed to node as the initial input, or when referenced by import statements or import() expressions:
- Files with an .mjs extension
- FIles with a .js extension when the nearest parent package.json file contains a top-level "type" field with a value of "module"
- Strings passed in as an argument to --eval, or piped to node via STDIN, with the flag --input-type=module

# Node全局对象

Node.js中的全局变量区别于浏览器中的window对象，是global对象；  

html中：
~~~js
let a = 1;
window.a // undefined

var b = 2;
window.b // 2

c = 3;
window.c // 3
~~~

NodeJS中，单个文件中只要是var、let声明的变量全部是局部变量，不会挂在global上。这是因为NodeJS是模块化管理机制，一个js文件默认为一个模块。global凌驾于所有js文件之上，要想将变量挂在全局就要使用默认全局变量，不声明直接用。所以Node中
~~~js
let a = 1;
global.a // undefined

var b = 2;
global.b // undefined

c = 3;
global.c // 3
~~~
