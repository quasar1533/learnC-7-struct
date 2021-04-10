#include <stdio.h>
#include <io_utils.h>
#include <stddef.h>


// 结构体内部会自动实现内存对齐，具体情况根据编译器来实现。

// 使用#pragma来手动指定内存对齐倍数
//#pragma pack(2)
int main() {
  typedef struct Person {
    char *name;
    int age;
    char *id;
  } Person;
  Person person1 = {"jky", 18};
  // 上面例子用来对比一下区别

  // test
  typedef struct {
    char a;
    char b;
    int c;
    short d;
    double e;
  } Align;
  Align align = {.a='a', .b='b', .c=3, .d=4, .e=5.0};
  PRINT_INT(sizeof(align));
  // 经调试，对齐后总共浪费了8个字节空位。

  // 优化一下
  typedef struct {
    char a;
    char b;
    short d;
    int c;
    double e;
  } OptimizesAlign2;
  OptimizesAlign2 optimized_align = {.a='a', .b='b', .c=3, .d=4, .e=5.0};
  PRINT_INT(sizeof(optimized_align)); // 完全没有浪费内存

  // 一些操作内存对齐相关的函数
  // 仍是第一个例子
  typedef struct {
    char a;
    char b;
//    __attribute((aligned(8))) int c; // gcc only 自由设置对齐倍数，gcc更新：如果设置的数值小于变量尺寸长度则无效。
    _Alignas(8) int c;  // c11 only
    short d;
    double e;
  } Align2;
  Align2 align2 = {.a='a', .b='b', .c=3, .d=4, .e=5.0};
  PRINT_INT(_Alignof(align2.c));  // c11 only
  PRINT_INT(offsetof(Align2, c)); // msvc OK 打印c相对于Align2结构体首地址的pi偏移字节数
  PRINT_HEX((Align2 *) 0);
  PRINT_HEX(&(((Align2 *)0)->c)); // !! important
  return 0;
}

// 在msvc中 offsetof的实现很有意思。 struct member
// #define offsetof(s, m) ((size_t)&(((s*)0)->m))
