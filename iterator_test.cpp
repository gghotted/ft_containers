#include <vector>
#include <iostream>
#include <type_traits>

typedef std::vector<int> vector;

void iter_const_nonConst()
{
    vector v;
    const vector cv;

    std::cout << (v.begin() == cv.begin());
    std::cout << (v.begin() != cv.begin());
    std::cout << (v.begin() < cv.begin());
    std::cout << (v.begin() > cv.begin());

    std::cout << (cv.begin() == v.begin());
    std::cout << (cv.begin() != v.begin());
    std::cout << (cv.begin() < v.begin());
    std::cout << (cv.begin() > v.begin());
}

void iter_reverse_nonReverse()
{
    // vector v;

    // std::cout << (v.begin() == v.rbegin());
    // std::cout << (v.rbegin() == v.begin());
}

void iter_reverse_constReverse()
{
    vector v;
    const vector cv;

    std::cout << (v.rbegin() == cv.rbegin());
    std::cout << (v.rbegin() != cv.rbegin());
    std::cout << (v.rbegin() < cv.rbegin());
    std::cout << (v.rbegin() > cv.rbegin());

    std::cout << (cv.rbegin() == v.rbegin());
    std::cout << (cv.rbegin() != v.rbegin());
    std::cout << (cv.rbegin() < v.rbegin());
    std::cout << (cv.rbegin() > v.rbegin());
}

void iter_const_nonConst_diff()
{
    vector v;
    const vector cv;

    std::cout << (v.begin() - cv.begin());
    std::cout << (cv.begin() - v.begin());

    std::cout << (v.begin() - cv.begin());
    std::cout << (cv.begin() - v.begin());

    (void)(v.begin() - 1);
    (void)(cv.begin() - 1);
    (void)(1 + v.begin());
    (void)(1 + cv.begin());

    (void)(v.rbegin() - 1);
    (void)(cv.rbegin() - 1);
    (void)(1 + v.rbegin());
    (void)(1 + cv.rbegin());
}

void const_nonConst()
{
    vector v;
    const vector cv;

    std::cout << (v == cv);
    std::cout << (v != cv);
    std::cout << (v < cv);
    std::cout << (v > cv);

    std::cout << (cv == v);
    std::cout << (cv != v);
    std::cout << (cv < v);
    std::cout << (cv > v);
}

void sub_reverse_constReverse()
{
    vector v;
    const vector cv;

    std::cout << (v.rbegin() - cv.rbegin());
}

int main()
{
    iter_const_nonConst();
    const_nonConst();
    iter_reverse_constReverse();
    iter_const_nonConst_diff();
    sub_reverse_constReverse();
}
