/* containers */
#include "list.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "map.hpp"
/* containers */

#include "CompareTester.hpp"
#include "ListTest.hpp"
#include "VectorTest.hpp"
#include "StackTest.hpp"
#include "QueueTest.hpp"
#include "MapTest.hpp"
#include "IteratorRelationTest.hpp"

#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <map>

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
    LIST_TEST(reverse);
    LIST_TEST(sort0);
    LIST_TEST(sort1);

    /* non member */
    LIST_TEST(nonMemberSwap);
    LIST_TEST(relationOperation);
    LIST_TEST(iteratorRelationOperation);
}

void testListDouble(CompareTester& ct)
{
    typedef std::list<double>  STD;
    typedef ft::list<double>   FT;

    LIST_TEST(merge1);
}

void testVector(CompareTester& ct)
{
    typedef std::vector<int>  STD;
    typedef ft::vector<int>   FT;

    /* constructor */
    VECTOR_TEST(constructor0);
    VECTOR_TEST(constructor1);
    VECTOR_TEST(constructor2);
    VECTOR_TEST(copyConstructor);

    /* operator */
    VECTOR_TEST(assignation);

    /* iterator */
    VECTOR_TEST(begin_end);
    VECTOR_TEST(rbegin_rend);

    /* capacity */
    VECTOR_TEST(size_capacity);
    VECTOR_TEST(max_size);
    VECTOR_TEST(resize);
    VECTOR_TEST(empty);
    VECTOR_TEST(reserve);
    VECTOR_TEST(reserveExcept);

    /* element access */
    VECTOR_TEST(accessOperator);
    VECTOR_TEST(at);
    VECTOR_TEST(atExcept);
    VECTOR_TEST(front_back);

    /* modifiers */
    VECTOR_TEST(assign0);
    VECTOR_TEST(assign1);
    VECTOR_TEST(push_back);
    VECTOR_TEST(pop_back);
    VECTOR_TEST(insert0);
    VECTOR_TEST(insert1);
    VECTOR_TEST(insert2);
    VECTOR_TEST(erase0);
    VECTOR_TEST(erase1);
    VECTOR_TEST(swap);
    VECTOR_TEST(clear);

    /* non member */
    VECTOR_TEST(nonMemberSwap);
    VECTOR_TEST(relationOperation);
    VECTOR_TEST(iteratorRelationOperation);
}

void testStack(CompareTester& ct)
{
    typedef std::stack<int> STD;
    typedef ft::stack<int>  FT;

    STACK_TEST(constructor);
    STACK_TEST(copyConstructor);
    STACK_TEST(assignation);
    STACK_TEST(capacity);
    STACK_TEST(push_pop);
    STACK_TEST(relationOperation);
}

void testQueue(CompareTester& ct)
{
    typedef std::queue<int> STD;
    typedef ft::queue<int>  FT;

    QUEUE_TEST(constructor);
    QUEUE_TEST(copyConstructor);
    QUEUE_TEST(assignation);
    QUEUE_TEST(capacity);
    QUEUE_TEST(push_pop);
    QUEUE_TEST(relationOperation);
}

void testMap(CompareTester& ct)
{
    typedef std::map<int, int>  STD;
    typedef ft::map<int, int>   FT;

    /* constructor */
    MAP_TEST(constructor0);
    MAP_TEST(constructor1);
    MAP_TEST(copyConstructor);

    // /* operator */
    MAP_TEST(assignation);

    // /* iterator */
    MAP_TEST(begin_end);
    MAP_TEST(rbegin_rend);

    // /* capacity */
    MAP_TEST(empty);
    MAP_TEST(size);
    MAP_TEST(max_size);

    /* element access */
    MAP_TEST(accessOperator);

    // /* modifiers */
    MAP_TEST(insert0);
    MAP_TEST(insert1);
    MAP_TEST(insert2);
    MAP_TEST(erase0);
    MAP_TEST(erase0_0);
    MAP_TEST(erase1);
    MAP_TEST(erase2);
    MAP_TEST(swap);
    MAP_TEST(clear);

    /* observer */
    MAP_TEST(key_comp);
    MAP_TEST(value_comp);

    // /* operations */
    MAP_TEST(find);
    MAP_TEST(count);
    MAP_TEST(lower_bound);
    MAP_TEST(upper_bound);
    MAP_TEST(equal_range);

    // /* non member */
    MAP_TEST(nonMemberSwap);
    MAP_TEST(relationOperation);
    MAP_TEST(iteratorRelationOperation);

    /* random case */
    MAP_TEST(erase_random_case);
    MAP_TEST(insert_random_case0);
    MAP_TEST(insert_random_case1);
}

int main()
{
    srand(time(0));
    CompareTester ct;
    ct.setPrintOnPass(true);

    testList(ct);
    testListDouble(ct);
    testVector(ct);
    testStack(ct);
    testQueue(ct);
    testMap(ct);

    ct.printTotalScore();
    system("leaks ft_containers");
}
