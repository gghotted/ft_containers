#include <vector>
#include <iostream>
#include <type_traits>

int main()
{
    typedef std::vector<int> vector;
    vector v;
    const vector cv;

    std::cout << (v.begin() == cv.begin());
    std::cout << (v.begin() != cv.begin());

    void* dummy = 0;
    void();
}
