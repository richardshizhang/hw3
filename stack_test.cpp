#include "stack.h"
#include <iostream>

int main(int argc, char* argv[]){
  Stack<int> s;
  s.push(1);
  s.push(2);
  std::cout<<s.top();
  s.pop();
}