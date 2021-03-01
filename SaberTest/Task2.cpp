#include "Task2.h"

void RemoveDups(char* str)
{
  char* resulting_str = str;
  char* iter_str = str;

  while (*iter_str++)
  {
    if (*iter_str != *resulting_str)
      *++resulting_str = *iter_str;
  }
}
