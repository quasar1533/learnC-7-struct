#include <io_utils.h>

// 学习联合体union

// 定义一个联合体
typedef union Operand {
  int int_operand;
  double double_operand;
  char *string_operand;
} Operand;
// 联合体的意义是，内部定义的字段共享一块内存。如：int使用低位四个byte，double则使用完整的8个byte
// 乍一看，联合体似乎没有什么用， 但它在一些场合可以起到独有的作用。 如下

typedef struct Instruction {
  int operator; // 算子
  Operand operand; // 操作数
} Instruction;

// 定义几个算子（运算类型）
#define OP_PRINT_INT 0
#define OP_PRINT_DOUBLE 1
#define OP_PRINT_STRING 2

void Process(Instruction *instruction) {
  switch (instruction->operator) {
    case OP_PRINT_INT:
      PRINT_INT(instruction->operand.int_operand);
      break; // C语言记住要break！！！
    case OP_PRINT_DOUBLE:
      PRINT_DOUBLE(instruction->operand.double_operand);
      break;
    case OP_PRINT_STRING:
      puts(instruction->operand.string_operand);
      break;
    default:
      fprintf(stderr, "undefined operator: %d\n", instruction->operator);
  }
}

void Test(int *array) {
  for (int i = 0; i < 5; ++i) {
    PRINT_INT(*(array + i));
  }
}

int main() {
  PRINT_INT(sizeof(Operand));
  Operand operand = {.int_operand=3, .double_operand=5.0};
  PRINT_INT(operand.int_operand);
  PRINT_DOUBLE(operand.double_operand);

  // 使用一下process程序
  union Operand operand2 = {.string_operand="Hello World!"};
  struct Instruction instruction = {.operator=OP_PRINT_STRING, .operand=operand2};
  Process(&instruction);

  {
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7};
    PRINT_INT(sizeof(array));
    Test(array);
  }
  return 0;
}
