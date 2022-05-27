# C语言常考问题汇总

### C语言如何对字符串判空
C语言的字符串实质上是以`\0`结尾的char数组。
对于 `char* c` 表示的字符串，我们进行判空需要这样写：
```
bool notEmpty(char* c) {
    return c != NULL && strlen(c);
}
```
如果写成:
```
bool notEmpty(char* c) {
    return c != "";
}
```
则是不对的，因为这样写等号比较的是两者的地址。