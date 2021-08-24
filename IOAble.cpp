/* Citation and Sources...
Final Project Milestone 5
Module:     IOAble
Filename:   IOAble.cpp
Version:    1.0
Author:     Pratham Jani
Revision History
-----------------------------------------------------------
Date      Reason
2021/07/18  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#define _CRT_SECURE_NO_WARNINGS
#include "IOAble.h"

using namespace std;

namespace sdds
{
    std::ostream& operator<<(std::ostream& ostr, const IOAble& src)
    {
        return src.write(ostr);
    }

    std::istream& operator>>(std::istream& istr, IOAble& src)
    {
        return src.read(istr);
    }
}