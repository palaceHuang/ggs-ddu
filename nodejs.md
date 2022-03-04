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
