# C++常考问题汇总

### 在C++中什么是右值引用
参考链接： https://www.cnblogs.com/qicosmos/p/4283455.html

首先我们要明确左值和右值的区别。
```
int i = 0;
int j = 5;
auto f = []{return 5;};
```
通常来说，我们可以简单的认为`=`左边的值为左值；`=`右边的值为右值。两种值最大的区别在于生命周期；右值在表达式结束之后就会被销毁，左值则不会。另一个区别在于左值可以取地址；右值则不可。

常见的右值包括：字面量、lambda表达式、表达式产生的临时变量和非引用返回的临时变量。

```
int i = 0;
int& j = i;
int&& k = 0;
```
c++中采用两个`&`表示右值引用，一个`&`表示左值引用。
引入右值引用主要用于解决：1. 免去临时对象不必要的拷贝操作 2. 在模板中按照参数的实际类型转发。
由于微扰酱目前只理解了第一个目的，第二个目的之后再进行讨论。(TODO)

```
#include <iostream>
using namespace std;

int g_constructCount=0;
int g_copyConstructCount=0;
int g_destructCount=0;
struct A
{
    A(){
        cout<<"construct: "<<++g_constructCount<<endl;    
    }
    
    A(const A& a)
    {
        cout<<"copy construct: "<<++g_copyConstructCount <<endl;
    }
    ~A()
    {
        cout<<"destruct: "<<++g_destructCount<<endl;
    }
};

A GetA()
{
    return A();
}

int main() {
    A a = GetA();
    return 0;
}

Output: 
construct: 1
copy construct: 1
destruct: 1
copy construct: 2
destruct: 2
destruct: 3
```
如果不采用右值引用；则main函数运行时需要进行一次构造函数的调用，并在 GetA返回 和 a 赋值时分别调用一次拷贝构造函数。

```
int main() {
    A&& a = GetA();
    return 0;
}

Output: 
construct: 1
copy construct: 1
destruct: 1
destruct: 2
```
而采用了右值引用后，我们免去了一次对a赋值时产生的拷贝开销；GetA返回的右值并没有在表达式结束后立刻消亡，而是以右值引用的方式继续存活；其生命周期和a相同。


