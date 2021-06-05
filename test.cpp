#include <list>
#include <iostream>

typedef struct{
  int x;
  int y;
}my_struct;

int main()
{
    std::list<my_struct> the_list;
    std::list<my_struct>::iterator the_iter = the_list.begin();

    the_list.erase();
    the_iter.
}
