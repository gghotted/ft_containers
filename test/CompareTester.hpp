#ifndef COMPARETESTER_HPP
#define COMPARETESTER_HPP

#include <string>
#include <iostream>
#include <sstream>

class CompareTester
{
    int               cntPass;
    int               cntRun;
    std::stringstream lhsResult;
    std::stringstream rhsResult;
    bool              printOnPass;

    static const std::string red;
    static const std::string green;
    static const std::string noColor;

    public:
        ~CompareTester();
        CompareTester();
        CompareTester(const CompareTester& ct);
        CompareTester& operator=(const CompareTester& ct);

        template <class LhsFnc, class RhsFnc>
        void run(
            const std::string& testName,
            const std::string& lhsName,
            const std::string& rhsName,
            LhsFnc lhs, RhsFnc rhs)
        {
            ++cntRun;
            std::cout << "\n[ " << testName << " ]";

            lhs(lhsResult);
            rhs(rhsResult);
            if (lhsResult.str().compare(rhsResult.str()) == 0)
                pass(lhsName, rhsName);
            else
                fail(lhsName, rhsName);
            lhsResult.str("");
            rhsResult.str("");
        }

        void printResult(bool pass, const std::string& lhsName, const std::string& rhsName);
        void fail(const std::string& lhsName, const std::string& rhsName);
        void pass(const std::string& lhsName, const std::string& rhsName);
        void setPrintOnPass(bool val);
};

#endif // COMPARETESTER_HPP
