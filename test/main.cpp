/* containers */
#include "list.hpp"
/* containers */

#include "CompareTester.hpp"
#include "ListTest.hpp"

#include <iostream>
#include <list>

void testList(CompareTester& ct)
{
    typedef std::list<int>  STD;
    typedef ft::list<int>   FT;

    /* constructor */
    LIST_TEST(constructor0);
    LIST_TEST(constructor1);
    LIST_TEST(constructor2);

    LIST_TEST(push_back);
}

int main()
{
    CompareTester ct;
    ct.setPrintOnPass(true);

    testList(ct);
    // system("leaks ft_containers");
}
