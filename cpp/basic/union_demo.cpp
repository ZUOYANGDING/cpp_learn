#include <iostream>
#include <unistd.h>

/**
 * @brief 
 * 默认访问控制符为 public
可以含有构造函数、析构函数
不能含有引用类型的成员
不能继承自其他类，不能作为基类
不能含有虚函数
匿名 union 在定义所在作用域可直接访问 union 成员
匿名 union 不能包含 protected 成员或 private 成员
全局匿名联合必须是静态（static）的
 */
union union_demo
{
    struct 
    {
        int a, b, c, d;
    }foo;
    long index;
} u;

int main(int argc, const char **argv){
    u.foo.a = 1;
    u.foo.b = 2;
    u.foo.c = 3;
    u.foo.d = 4;
    // replace value in a, b
    // index's memory addr is same as u
    u.index = (long)5;
    printf("%d %d %d %d %ld\n", u.foo.a, u.foo.b, u.foo.c, u.foo.d, u.index);
    pause();
    return 0;
}