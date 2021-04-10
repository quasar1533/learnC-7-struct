#include <io_utils.h>

// 学习案例，判断字节序
// 大端序--与人类阅读顺序一致（网络传输）， 小端序则相反（CPU处理）
// 联合体的第二个应用    联合体的特点就是，可以在一块内存中写内容，但可以以不同的方式去读这个内容。

// 定义一个判断编译器是否为大端序的函数
int IsBigEndian() {
  union {
    char c[2];
    short s;
  } value = {.s=0x100};

  return value.c[0] == 1;
}

// 定义一个字节序转换程序，因为某些语言如Java是大端序的
int ToggleEndian(int original) {
  union {
    char c[4];
    int i;
  } value = {.i=original};

  char temp = value.c[0];
  value.c[0] = value.c[3];
  value.c[3] = temp;
  temp = value.c[1];
  value.c[1] = value.c[2];
  value.c[2] = temp;

  return value.i;
}

// 指针版本的函数
int IsBigEndianPtr(void) {
  short s = 0x100;
  char *p = (char *) &s;

  return p[0] == 1;
}

int ToggleEndianPtr(int original) {
  char *p = (char *)&original;

  char temp = p[0];
  p[0] = p[3];
  p[3] = temp;
  temp = p[1];
  p[1] = p[2];
  p[2] = temp;

  return original;
}


int main() {
  PRINT_INT(IsBigEndian());

  int original = 0x12345678;
  PRINT_HEX(ToggleEndian(original));
  PRINT_HEX(ToggleEndian(ToggleEndian(original)));

  // 指针版本

  return 0;
}
