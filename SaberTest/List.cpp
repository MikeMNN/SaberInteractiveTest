#include <iostream>
#include <map>
#include <random>
#include <vector>

#include "List.h"

void List::Serialize(FILE* file) {
  ListNode* list_iter = head;
  while (list_iter) {
    // Get address of pointers in memory to store link correctly.
    std::uintptr_t current_address =
        reinterpret_cast<std::uintptr_t>(list_iter);
    std::uintptr_t random_address =
        reinterpret_cast<std::uintptr_t>(list_iter->rand);
    size_t str_length = list_iter->data.length();

    // Writing one by one: current element address, random element address,
    // data length and data itself.
    fwrite(&current_address, sizeof(std::uintptr_t), 1, file);
    fwrite(&random_address, sizeof(std::uintptr_t), 1, file);
    fwrite(&str_length, sizeof(size_t), 1, file);
    fwrite(list_iter->data.c_str(), str_length, 1, file);

    list_iter = list_iter->next;
  }
}

void List::Deserialize(FILE* file) {
  std::map<std::uintptr_t, ListNode*> nodes_map;
  std::uintptr_t node_address, rand_node_address;
  size_t str_length;
  std::vector<std::uintptr_t> random_nodes_ordered;

  // Reading node address, address of random node that it was point to,
  // data length and data itself. Associate node address with new list node
  // for correct associating of random node pointer later.
  while (fread(&node_address, sizeof(std::uintptr_t), 1, file) == 1) {
    fread(&rand_node_address, sizeof(std::uintptr_t), 1, file);
    fread(&str_length, sizeof(size_t), 1, file);

    std::vector<char> stored_str(str_length, 0);
    fread(&stored_str[0], 1, str_length, file);

    std::string new_data(stored_str.begin(), stored_str.end());
    PushToEnd(new_data);

    nodes_map[node_address] = tail;
    random_nodes_ordered.push_back(rand_node_address);
  }

  // Linking new lis nodes with random list nodes that they were point to
  // before serializing. 
  ListNode* list_iter = head;
  for (int i = 0; list_iter != nullptr; list_iter = list_iter->next, i++) {
    list_iter->rand = nodes_map[random_nodes_ordered[i]];
  }
}

List::~List() {
  // Clear memory after all.
  while (head)
  {
    tail = head->next;
    delete head;
    head = tail;
  }
}

void List::PushToFront(std::string newData) {
  ListNode* new_node = new ListNode{ nullptr, nullptr, nullptr, newData };

  if (head) {
    head->prev = new_node;
    new_node->next = head;
  } else {
    // Head was nullptr what means that list was empty and we should update
    // tail as well.
    tail = new_node;
  }

  // Set current head to the new node.
  head = new_node;
  count++;
}

void List::PushToEnd(std::string newData) {
  ListNode* new_node = new ListNode{ nullptr, nullptr, nullptr, newData };

  if (tail) {
    tail->next = new_node;
    new_node->prev = tail;
  } else {
    // Tail was nullptr what means that list was empty and we should update
    // head as well.
    head = new_node;
  }

  // Set current tail to the new node.
  tail = new_node;
  count++;
}

void List::FillWithRandomNodes() {
  // Adding random generator to generate node number from head.
  std::default_random_engine gen(std::random_device{}());
  std::uniform_int_distribution<int> uid(0, count);

  ListNode* list_iter = head;
  while (list_iter) {
    int node_pos = uid(gen);
    list_iter->rand = GetRandomListNode(node_pos);

    list_iter = list_iter->next;
  }
}

ListNode* List::GetRandomListNode(int node_pos) {
  // If list is empty or random number is generated equal to list length
  // returning nullptr. Second case needed to simulate case where 'rand' field
  // could contain NULL
  if (!count || node_pos == count)
    return nullptr;

  ListNode* rand_node = head;
  for (int i = 0; i < node_pos; i++)
    rand_node = rand_node->next;

  return rand_node;
}

std::ostream& operator<<(std::ostream& out, const List& list) {
  ListNode* list_iter = list.head;
  out << "Current list state" << std::endl << "------------------" << std::endl;
  while (list_iter) {
    out << "Data: " << list_iter->data <<
        ", Cur elem addr: " << list_iter <<
        ", Prev elem addr: " << list_iter->prev <<
        ", Next elem addr: " << list_iter->next <<
        ", Rand elem addr: " << list_iter->rand <<
        std::endl;
    list_iter = list_iter->next;
  }
  return out;
}
