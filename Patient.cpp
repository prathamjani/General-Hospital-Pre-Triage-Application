/* Citation and Sources...
Final Project Milestone 5
Module:     Patient
Filename:   Patient.cpp
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
#include <string>
#include <cstring>
#include "Patient.h"
#include "utils.h"

using namespace std;

namespace sdds
{
    Patient::Patient(int ticketNumber, bool fileIO) {
        m_ticket = ticketNumber;
        m_fileIO = fileIO;
    }

    Patient::~Patient() {
        delete[] m_name;
        m_name = nullptr;
    }

    const bool Patient::fileIO() const {
        return m_fileIO;
    }

    void Patient::fileIO(bool boolValue) {
        m_fileIO = boolValue;
    }

    bool Patient::operator==(const char character) const {
        return type() == character;
    }

    bool Patient::operator==(const Patient& patients) const {
        return this->type() == patients.type();
    }

    void Patient::setArrivalTime() {
        m_ticket.resetTime();
    }

    Patient::operator Time() const {
        return Time(m_ticket);
    }

    int Patient::number() const {
        return m_ticket.number();
    }

    std::ostream& Patient::csvWrite(std::ostream& ostr) const {
        ostr << type() << ',' << m_name << ',' << m_number << ',';

        m_ticket.csvWrite(ostr);

        return ostr;
    }

    std::istream& Patient::csvRead(std::istream& istr) {
        string str;
        char comma;

        getline(istr, str, ',');

        if (m_name) {
            delete[] m_name;
            m_name = nullptr;
        }

        m_name = new char[strlen(str.c_str()) + 1];

        strcpy(m_name, str.c_str());

        istr >> m_number >> comma;

        m_ticket.csvRead(istr);

        return istr;
    }

    std::istream& Patient::read(std::istream& istr) {

        char* str = getcstr("Name: ", istr);

        if (m_name) {
            delete[] m_name;
            m_name = nullptr;
        }

        m_name = new char[strlen(str) + 1];
        strcpy(m_name, str);

        delete[] str;

        m_number = getInt(100000000, 999999999, "OHIP: ", "Invalid OHIP Number, ");

        return istr;
    }

    std::ostream& Patient::write(std::ostream& ostr) const {
       
        ostr << "Ticket No: " << m_ticket.number() << ", Issued at: " << Time(*this) << endl;

        if (strlen(m_name) <= 25) {
            ostr << m_name;
        }
        else {
            for (int i = 0; i < 25; i++) {
                ostr << m_name[i];
            }
        }

        ostr << ", OHIP: " << m_number;

        return ostr;
    }

    
}