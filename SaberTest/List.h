#pragma once

#include <string>

// структуру ListNode модифицровать нельзя
struct ListNode {
  ListNode* prev;
  ListNode* next;
  ListNode* rand; // указатель на произвольный элемент данного списка, либо NULL
  std::string data;
};

class List {
public:
  void Serialize(FILE* file);  // сохранение в файл (файл открыт с помощью fopen(path, "wb"))
  void Deserialize(FILE* file);  // загрузка из файла (файл открыт с помощью fopen(path, "rb"))

  ~List();

  // Add new elements.
  void PushToFront(std::string newData);
  void PushToEnd(std::string newData);

  // Calculate random list element on which new node will point.
  void FillWithRandomNodes();

  friend std::ostream& operator<< (std::ostream& out, const List& list);
private:
  ListNode* GetRandomListNode(int node_pos);

  ListNode* head;
  ListNode* tail;
  int count;
};
