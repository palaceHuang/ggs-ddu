const fs = require("fs");
var cmdArr = [
  "移动-行首",
  "移动-行尾",
  "插入-行首",
  "插入-行尾",
  "插入-行前",
  "插入-行后",
  "复制整行",
  "粘贴",
  "删除整行",
  "左移",
  "右移",
  "上移",
  "下移",
  "保存",
  "退出",
  "插入-字符前",
  "插入-字符后",
];
for (let i = 0; i < 1000; i++) {
  let num = parseInt(Math.random() * cmdArr.length);
  // console.log(num, i);
  let line = i + " : " + cmdArr[num] + "\n";
  // fs.writeFile("command.txt", line, { flag: "a" }, function (err) {
  //   if (err) {
  //     console.log(err);
  //   }
  // });
  setTimeout(function () {
    console.log(line + "\n");
  }, i * 5000);
}
// fs.close();
