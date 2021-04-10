#include <stdio.h>
#include <io_utils.h>

// 初识结构体，C语言的复杂聚合类型数据，对象的雏形

int main() {
  /*
   * struct <结构体名> {
   *  <成员类型> <成员名>;
   *  ...
   * } <结构体变量>;
   */
  // struct关键字用于定义、声明结构体类型变量;同时也用于标识一个变量是结构体
  typedef struct Company {
    char *name;
    char *id;
    char *location;
  } Company;

  struct Person {
    char *name;
    int age;
    char *id;
    Company *company1;
    Company company2;
    struct {
      int extra;
      char *extra_str;
    } extra_value;
    struct Person *partner;
  } person; // 可以再定义时声明！

  // 再其他地方复用所定义的结构体类型
  struct Person person1 = {"jky", .id="11256"};
  // 给结构体赋值时，可以像给数组赋值一样，使用成员选择运算符 . ;
  PRINT_INT(person1.age);
  person1.age = 11;

  // 可以定义匿名结构体一次性使用
  struct {
    char *name;
    int age;
    char *id;
  } anonymous_person;

  // 结构体变量也是一个指针，存放其首地址  因此
  struct Person *person_ptr = &person1;
  // 与指针访问运算符*对应， 也存在成员（指针）访问运算符 '->'
  PRINT_INT(person_ptr->age);
  PRINT_INT(sizeof(struct Person));

  // 简化写法，不用每次都加上struct     struct后面定义的大写英文单词是自定义结构体类型名，并不是真正的数据类型
  // C语言typedef 可以自定以类型。
  typedef struct Person Person;
  Person person2 = {.name = "bd", .age = 18,};
  PRINT_INT(person2.age);

  // 可实现嵌套结构  见开头 ↑ 访问他们
  // 1. person.company->name
  // 2. person.extra_value.extra

  {
    // 再次深入指针的理解
    int array[3];
    int *array1;
    int array2[] = {1, 2, 3, 4, 5};
    PRINT_INT(sizeof(array));
    PRINT_INT(sizeof(&array));
    PRINT_INT(sizeof(array1));
    PRINT_INT(sizeof(array2));

    struct A {
      char *name;
      int number;
    };
    struct A aa;
    PRINT_INT(sizeof(aa));
    PRINT_INT(sizeof(&aa));

    struct B {
      int id;
      int number;
    };
    struct B bb;
    PRINT_INT(sizeof(bb));
    PRINT_INT(sizeof(&bb));

    char *name = "aaa";
    PRINT_INT(sizeof(name));
  }


  // 初始化嵌套结构体
  Company company1 = {.name="hx", .id="123456",};
  Person person3 = {.name="quasar", .company1 = &company1,
    .company2 = {
      .name = "hah", .location = "China"
    }
  };
  // 也可以指向自己
  return 0;
}
