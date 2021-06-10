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
    LIST_TEST(copyConstructor);

    /* operator */
    LIST_TEST(assignation);

    /* iterator */
    LIST_TEST(begin_end);
    LIST_TEST(rbegin_rend);

    /* capacity */
    LIST_TEST(empty);
    LIST_TEST(max_size);

    /* modifiers */
    LIST_TEST(assign0);
    LIST_TEST(assign1);
    LIST_TEST(push_front);
    LIST_TEST(pop_front);
    LIST_TEST(push_back);
    LIST_TEST(pop_back);
    LIST_TEST(insert0);
    LIST_TEST(insert1);
    LIST_TEST(insert2);
    LIST_TEST(erase0);
    LIST_TEST(erase1);
    LIST_TEST(swap);
    LIST_TEST(resize);
    LIST_TEST(clear);

    /* operations */
    LIST_TEST(splice0);
    LIST_TEST(splice1);
    LIST_TEST(splice2);
    LIST_TEST(remove);
    LIST_TEST(remove_if);
    LIST_TEST(unique0);
    LIST_TEST(unique1);
    LIST_TEST(merge0);
}

void testListDouble(CompareTester& ct)
{
    typedef std::list<double>  STD;
    typedef ft::list<double>   FT;

    LIST_TEST(merge1);
}

int main()
{
    CompareTester ct;
    ct.setPrintOnPass(true);

    testList(ct);
    testListDouble(ct);
    ct.printTotalScore();
    system("leaks ft_containers");
}
