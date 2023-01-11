1. parseInt 遇到map
   ```js
   ["1", "2", "3"].map(parseInt)

    // A. ["1", "2", "3"]
    // B. [1, 2, 3]
    // C. [0, 1, 2]
    // D. other
    ```
2. 神奇的null
    ```js
    [typeof null, null instanceof Object]

    // A. ["object", false]
    // B. [null, false]
    // C. ["object", true]
    // D. other
    ```
3. 愤怒的reduce
    ```js
    [ [3,2,1].reduce(Math.pow), [].reduce(Math.pow) ]

    // A. an error
    // B. [9, 0]
    // C. [9, NaN]
    // D. [9, undefined]
    ```
4. 该死的优先级
    ```js
    var val = 'smtg';
    console.log('Value is ' + (val === 'smtg') ? 'Something' : 'Nothing');

    // A. Value is Something
    // B. Value is Nothing
    // C. NaN
    // D. other
    ```
5. 神鬼莫测之变量提升
    ```js
    var name = 'World!';
    (function () {
        if (typeof name === 'undefined') {
        var name = 'Jack';
        console.log('Goodbye ' + name);
        } else {
        console.log('Hello ' + name);
        }
    })();

    // A. Goodbye Jack
    // B. Hello Jack
    // C. Hello undefined
    // D. Hello World
    ```
6. 死循环陷阱
    ```js
    var END = Math.pow(2, 53);
    var START = END - 100;
    var count = 0;
    for (var i = START; i <= END; i++) { 
        count++;
    }
    console.log(count);

    // A. 0
    // B. 100
    // C. 101
    // D. other
    ```
7. 过滤器魔法
    ```js
    var ary = [0,1,2];
    ary[10] = 10;
    ary.filter(function(x) {
        return x === undefined;
    });

    // A. [undefined x 7]
    // B. [0, 1, 2, 10]
    // C. []
    // D. [undefined]
    ```
8. 警惕IEEE 754标准
    ```js
    var two = 0.2;
    var one = 0.1;
    var eight = 0.8;
    var six = 0.6;

    [two - one == one, eight - six == two]

    // A. [true, false]
    // B. [false, false]
    // C. [true, false]
    // D. other
    ```
9. 字符串陷阱
    ```js
    function showCase(value) {
        switch(value) {
            case 'A':
                console.log('Case A');
                break;
            case 'B':
                console.log('Case B');
                break;
            case undefined:
                console.log('undefined');
                break;
            default:
                console.log('Do not know!');
        }
     }
     showCase(new String('A'));

     // A. Case A
     // B. Case B
     // C. Do not know!
     // D. undefined
    ```
10. 再一次的字符串陷阱
    ```js
    function showCase(value) {
        switch(value) {
            case 'A':
                console.log('Case A');
                break;
            case 'B':
                console.log('Case B');
                break;
            case undefined:
                console.log('undefined');
                break;
            default:
                console.log('Do not know!');
        }
    }
    showCase(String('A'));

    // A. Case A
    // B. Case B
    // C. Do not know!
    // D. undefined
    ```
11. 并非都是奇偶
    ```js
    function isOdd(num) {
        return num % 2 == 1;
    }

    function isEven(num) {
        return num % 2 == 0;
    }

    function isSane(num) {
        return isEven(num) || isOdd(num);
    }

    var values = [7, 4, "13", -9, Infinity];
    values.map(isSane);

    // A. [true, true, true, true, true]
    // B. [true, true, true, true, false]
    // C. [true, true, true, false, false]
    // D. [true, true, false, false, false]
    ```
12. parseInt小贼
    ```js
    parseInt(3, 8);
    parseInt(3, 2);
    parseInt(3, 0);

    // A. 3, 3, 3
    // B. 3, 3, NaN
    // C. 3, NaN, NaN
    // D. other
    ```
13. 数组原型是数组
    ```js
    Array.isArray( Array.prototype )

    // A. true
    // B. false
    // C. error
    // D. other
    ```
14. 一言难尽的强制转换
    ```js
    var a = [0];
    if ([0]) {
    console.log(a == true);
    } else {
    console.log("wut");
    }

    // A. true
    // B. false
    // C. "wut"
    // D. other
    ```
15. 撒旦之子"=="
    ```js
    []==[]

    // A. true
    // B. false
    // C. error
    // D. other
    ```
16. 加号 VS 减号
    ```js
    '5' + 3;
    '5' - 3;

    // A. "53", 2
    // B. 8, 2
    // C. error
    // D. other
    ```
17. 打死那个疯子
    ```js
    1 + - + + + - + 1

    // A. 2
    // B. 1
    // C. error
    // D. other
    ```
18. 淘气的map
    ```js
    var ary = Array(3);
    ary[0] = 2;
    ary.map(function(elem) {
    return "1";
    });

    // A. [2, 1, 1]
    // B. ["1", "1", "1"]
    // C. [2, "1", "1"]
    // D. other
    ```
17. 打死那个疯子
    ```js

    ```
17. 打死那个疯子
    ```js

    ```
17. 打死那个疯子
    ```js

    ```
17. 打死那个疯子
    ```js

    ```
17. 打死那个疯子
    ```js

    ```
17. 打死那个疯子
    ```js

    ```