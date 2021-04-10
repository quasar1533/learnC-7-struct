#include <io_utils.h>

// 学习枚举数据类型
// 枚举数据类型在C语言中，以一个不严格的有序组的形式存储，里面的每个元素相当于一个整数。

typedef enum FileFormat {
  JPEG, PNG = 11, BMP = 14, UNKNOWN
} FileFormat;

// 定义一个读取文件并返回文件类型的函数
FileFormat GuessFormat(char *file_path) {
  FILE *file = fopen(file_path, "rb"); // 操作文件的结构体
  FileFormat file_format = UNKNOWN;

  if (file) {
    char buffer[8] = {0};
    size_t bytes_count = fread(buffer, 1, 8, file);

    if (bytes_count == 8) {
      // bmp: 42 4D        // file signature  C语言二进制小端序存储
      // png: 89 50 4E 47 0D 0A 1A 0A
      // jpeg: FF D8 FF E0
      if (*((short *) buffer) == 0x4D42) file_format = BMP;
      if (*((long *) buffer) == 0x0A1A0A0D474E5089) file_format = PNG;
      if (*((int *) buffer) == 0xE0FFD8FF) file_format = JPEG;
    }
  }

  return file_format;
}

int main() {
  FileFormat file_format = PNG;

  FileFormat file_format2 = 10;  // 无严格限制
  // 测试一下枚举类型的实质
  PRINT_INT(GuessFormat("images/c.png"));
  PRINT_INT(GuessFormat("images/c.jpeg"));
  PRINT_INT(GuessFormat("images/c.bmp"));
  PRINT_INT(GuessFormat("images/c.webp"));
  // 按数组的顺序以及规则赋予连续的整数值

  // 可以自行修改enum体中的数值
  return 0;
}
