/* Citation and Sources...
Final Project Milestone 5
Module:     TriagePatient
Filename:   TriagePatient.cpp
Version:    1.0
Author:     Pratham Jani
Revision History
-----------------------------------------------------------
Date      Reason
2021/07/23  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <cstring>
#include "TriagePatient.h"
#include "utils.h"

using namespace std;

namespace sdds {
    int nextTriageTicket = 1;

    // Default Constructor
    TriagePatient::TriagePatient() : Patient(nextTriageTicket) {
        m_symptoms = nullptr;
        nextTriageTicket++;
    }

    // **** PURE VIRTUAL FUNCTION OVERRIDES ****

    // The type() function returns a char, which is T
    char TriagePatient::type() const {
        return 'T';
    }

    // Adds the symptoms to the comma-separated values of the patient.
    std::ostream& TriagePatient::csvWrite(std::ostream& ostr) const {
        Patient::csvWrite(ostr) << ',' << m_symptoms;
        return ostr;
    }

    // Reads a comma-separated record of a triage Patient and sets the global ticket number to the next number after the Patient's ticket number.
    std::istream& TriagePatient::csvRead(std::istream& istr) {
        string symptoms;

        delete[] m_symptoms;

        Patient::csvRead(istr);

        istr.ignore(1000, ',');

        getline(istr, symptoms, '\n');

        m_symptoms = new char[strlen(symptoms.c_str()) + 1];
        strcpy(m_symptoms, symptoms.c_str());

        nextTriageTicket = Patient::number() + 1;

        return istr;
    }

    // Based on the return value of the fileIO method it will either write the patient in a comma-separated format or a descriptive format for screen or ticket.
    std::ostream& TriagePatient::write(std::ostream& ostr) const {
        if (Patient::fileIO())
        {
            csvWrite(ostr);
        }
        else 
        {
            ostr << "TRIAGE" << endl;
            Patient::write(ostr) << endl;
            ostr << "Symptoms: " << m_symptoms << endl;
        }
        return ostr;
    }

    // If the fileIO member function returns true it will call the csvRead function else it will call the Read function of the base class Patient and Dynamically reads a Cstring (symptoms) from the istream object upto newline character ('\n')
    std::istream& TriagePatient::read(std::istream& istr) {
        if (Patient::fileIO())
        {
            csvRead(istr);
        }
        else
        {
            delete[] m_symptoms;

            Patient::read(istr);

            string symptoms;

            cout << "Symptoms: ";

            getline(istr, symptoms, '\n');

            m_symptoms = new char[strlen(symptoms.c_str()) + 1];
            strcpy(m_symptoms, symptoms.c_str());
        }
        return istr;
    }

    // Destructor
    TriagePatient::~TriagePatient() {
        delete[] m_symptoms;
        m_symptoms = nullptr;
    }
}