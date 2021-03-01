#include <stdio.h>
#include <iostream>
#include <conio.h>

#include "List.h"
#include "Task1.h"
#include "Task2.h"

// To use fopen instead of fopen_s
#pragma warning(disable: 4996)

const char file_for_list[] = "file_fo_list.bin";

int main()
{
  // Task 1 test
  int n;
  std::cin >> n;
  PrintIntAsBin(n);
  std::cout << "\n--------------------------------------------------" << std::endl;
  //--------------------------------------------------
  _getch();

  // Task 2 test
  char s[] = "ABB AAA SS11";
  RemoveDups(s);
  printf("%s\n", s);
  std::cout << "--------------------------------------------------" << std::endl;
  //--------------------------------------------------
  _getch();

  // Task 3 test
  List* list = new List();
  // Init list
  for (int i = 4; i >= 0; --i) {
    list->PushToFront(std::to_string(i));
  }

  for(int i = 5; i < 10; i++) {
    list->PushToEnd(std::to_string(i));
  }

  /*list->PushToEnd("abc");
  list->PushToEnd("asdfav");
  list->PushToEnd("asdfc");
  list->PushToEnd("asdffdfdff");
  list->PushToEnd("sdccccc");
  list->PushToEnd("tyuioo");
  list->PushToEnd("sdfqqq");
  list->PushToEnd("123545566");
  list->PushToEnd("aaaaaa");
  list->PushToEnd("nbnm,,,");
  list->PushToEnd("aaaqqq");*/


  list->FillWithRandomNodes();

  // Print list
  std::cout << "List to store:" << std::endl;
  std::cout << *list << std::endl;

  FILE* file = fopen(file_for_list, "wb");
  if (file) {
    list->Serialize(file);
    fclose(file);
  }

  delete list;

  file = fopen(file_for_list, "rb");
  if (file != nullptr) {
    List* restored_list = new List();
    // Deserilized it
    restored_list->Deserialize(file);
    fclose(file);

    // Print new list
    std::cout << "Restored list:" << std::endl;
    std::cout << *restored_list << std::endl;
    delete restored_list;
  }
  _getch();

  return 0;
}
