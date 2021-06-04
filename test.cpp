class Base
{
    int a;

    public:
        int getA() {return a;}

        Base me() {return *this;};
};

class A : public Base
{
    public:
        A me() {return *this;};
};

int main()
{
    A a;

    A a2 = a.me();
}
