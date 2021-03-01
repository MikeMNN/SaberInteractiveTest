#include <stdio.h>

#include "Task1.h"

void PrintIntAsBin(int n)
{
  for (int i = sizeof(n) * 8 - 1; i >= 0; --i) {
    printf("%d", n & (1 << i) ? 1 : 0);
  }
}
