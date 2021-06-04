#include <iostream>
#include "list.hpp"
#include <list>
int main()
{
	ft::list<int>	lst(5, 4);
	// lst.push_back(5);

	ft::list<int>::iterator	begin = lst.begin();
	ft::list<int>::iterator end = lst.end();
	// std::cout << &*begin << '\n';
	// std::cout << &*end;
	for (; begin != end; begin++)
		std::cout << *begin << ' ';
}
