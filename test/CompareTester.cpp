#include "CompareTester.hpp"

const std::string CompareTester::red = "\033[31m";
const std::string CompareTester::green = "\033[32m";
const std::string CompareTester::noColor = "\033[0m";

const std::string CompareTester::DontNeedToSame = "don't have to be the same";

CompareTester::~CompareTester()
{
}

CompareTester::CompareTester() : cntPass(0), cntRun(0), printOnPass(false)
{
}

CompareTester::CompareTester(const CompareTester& ct)
{
    *this = ct;
}

CompareTester& CompareTester::operator=(const CompareTester& ct)
{
    cntRun = ct.cntRun;
    cntPass = ct.cntPass;
    lhsResult.clear();
    rhsResult.clear();
    lhsResult.str(ct.lhsResult.str());
    rhsResult.str(ct.rhsResult.str());
    return *this;
}

void CompareTester::printResult(bool pass, const std::string& lhsName, const std::string& rhsName)
{
    if (pass) std::cout << green << " [OK]" << noColor;
    else      std::cout << red   << " [KO]" << noColor;

    if (pass && printOnPass == false)
        return ;
    std::cout << '\n';
    std::cout << lhsName << ": " << lhsResult.str() << '\n';
    std::cout << rhsName << ": " << rhsResult.str() << '\n';
}

void CompareTester::fail(const std::string& lhsName, const std::string& rhsName)
{
    printResult(false, lhsName, rhsName);
}


void CompareTester::pass(const std::string& lhsName, const std::string& rhsName)
{
    printResult(true, lhsName, rhsName);
    ++cntPass;
}

void CompareTester::setPrintOnPass(bool val)
{
    printOnPass = val;
}

void CompareTester::printTotalScore()
{
    std::string color = (cntRun == cntPass) ? green : red;
    std::cout << color << "Total: [ " << cntPass << " / " << cntRun << " ]"
              << noColor << '\n';
}

