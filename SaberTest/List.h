#pragma once

#include <string>

// ��������� ListNode ������������� ������
struct ListNode {
  ListNode* prev;
  ListNode* next;
  ListNode* rand; // ��������� �� ������������ ������� ������� ������, ���� NULL
  std::string data;
};

class List {
public:
  void Serialize(FILE* file);  // ���������� � ���� (���� ������ � ������� fopen(path, "wb"))
  void Deserialize(FILE* file);  // �������� �� ����� (���� ������ � ������� fopen(path, "rb"))

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
