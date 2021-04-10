#include <io_utils.h>
#include <stdlib.h>

/*常见的C语言数组都是顺序表结构，其有点是访问快，但CRUD操作十分繁琐
 * 而链表可以很好的解决CRUD的问题，灵活度更高*/
// 试用C语言构造一个单链表数据结构,充分运用指针!
// 链表数据结构有其专用的API，如创创建、删除、插入、移出等等

// def
typedef struct ListNode {
  int value;
  struct ListNode *next;
} ListNode;

// create node
ListNode *CreateNode(int value) {
  ListNode *node = malloc(sizeof(ListNode));
  if (!node) exit(1); // important step!
  node->value = value;
  node->next = NULL;   // serious important!

  return node;
}

void DestroyNode(ListNode **node_ptr) {  // trick 要传入指针的指针，否则无法彻底的置空，容易产生野指针
  (*node_ptr)->next = NULL;
  free(*node_ptr);
  *node_ptr = NULL;
}

// create linked_list
ListNode *CreateList(int array[], int length) {
  if (length <= 0) return NULL;  // key step!

  ListNode *head = CreateNode(array[0]);
  ListNode *current = head;
  for (int i = 1; i < length; ++i) {
    current->next = CreateNode(array[i]);
    current = current->next;
  }

  return head;
}

// print a linked list
void PrintList(ListNode *head) {
  while (head) {
    printf("%d  ", head->value);
    head = head->next;
  }
  putchar('\n');
}

// destroy a linked list
void DestroyList(ListNode **head) {
  if (!head || !(*head)) return;   // boundary condition!!!

  ListNode *current = *head;
  while (current) {
    ListNode *to_be_destroy = current;
    current = current->next;
    DestroyNode(&to_be_destroy);
  }

  *head = NULL;    // important!!
}

// insert a node into linked_list
// 这个函数比较复杂，它考虑了当插入节点时，链表本身就不存在，或不够长的情况
// 使用** 也是因为更方便掌控！
void InsertNode(ListNode **head, int value, int index) {
  if (!head || (index < 0)) return;

  ListNode *new_node = CreateNode(value);
  if (index == 0) {
    new_node->next = *head;
    *head = new_node;
  } else {
    if (!(*head)) {  // 需要判断链表本身的情况！！！
      *head = CreateNode(0);  // 节点初始化为0
    }
    ListNode *current = *head;
    while (index > 1) {
      if (!current->next) {
        current->next = CreateNode(0);
      }
      current = current->next;
      --index;
    }
    new_node->next = current->next;
    current->next = new_node;
  }
}

// remove node by index
void RemoveNode(ListNode *head, int index) {
  if (!head || index < 0) return;

  if (index == 0) {
    ListNode *new_head = head->next;  // key!!
    DestroyNode(&head);
    head = new_head;
  } else {
    ListNode *current = head;
    while (index > 1) {
      if (current->next) {
        current = current->next;
      }
      --index;
    }
  }
}

// remove node by value
void RemoveNode_2(ListNode **head, int value) {
  printf("Delete value: %d", value);

  if (!head || !(*head)) return;
  if ((*head)->value == value) {
    ListNode *new_head = (*head)->next;
    DestroyNode(head);
    *head = new_head;
  }
  ListNode *current = *head;
  while (current->next && (current->next->value) != value) { // 判断！！
    current = current->next;
  }
  if (current->next) {
    ListNode *node_to_delete = current->next;
    current->next = current->next->next;
    DestroyNode(&node_to_delete);
  }
}

int main() {
  ListNode *node1 = CreateNode(1);
  DestroyNode(&node1);

  int array[6] = {0, 1, 2, 3, 4, 5};
  ListNode *head = CreateList(array, 6);
  PrintList(head);
  InsertNode(&head, 100, 3);
  InsertNode(&head, 200, 0);
  InsertNode(&head, 300, 10);
  InsertNode(&head, 400, 4);
  PrintList(head);
  DestroyList(&head);
  PRINT_HEX(head);


  return 0;
}
