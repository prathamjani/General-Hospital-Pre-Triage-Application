/* Citation and Sources...
Final Project Milestone 5
Module:     CovidPatient
Filename:   CovidPatient.cpp
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

#include "CovidPatient.h"
using namespace std;

namespace sdds {
   int nextCovidTicket = 1;

   // passes the nextCovidTicket global variable to the constructor of the base class Patient and then it will increase the value of nextCovidTicket global variable by one.
   CovidPatient::CovidPatient() : Patient(nextCovidTicket) {
       nextCovidTicket++;
   }

   // PURE VIRTUAL FUNCTION OVERRIDES

   // The type() function returns a char, which is C.
   char CovidPatient::type() const {
       return 'C';
   }

   // Reads a comma-separated record of a Patient and sets the global ticket number to the next number after the Patient's ticket number.
   std::istream& CovidPatient::csvRead(std::istream& istr) {
       Patient::csvRead(istr);
       nextCovidTicket = Patient::number() + 1;
       istr.ignore(1000, '\n');

       return istr;
   }

   // Based on the return value of the fileIO method it will either write the patient in a comma-separated format or a descriptive format for screen or ticket.
   std::ostream& CovidPatient::write(std::ostream& ostr) const {
       if (Patient::fileIO()) 
       {
           Patient::csvWrite(ostr);
       }
       else 
       {
           ostr << "COVID TEST" << endl;
           Patient::write(ostr) << endl;
       }
       return ostr;
   }

   // Based on the return value of the fileIO method it will either read the patient in a comma-separated format from istream or perform a fool-proof entry from the console.
   std::istream& CovidPatient::read(std::istream& istr) {
       if (Patient::fileIO())
       {
           csvRead(istr);
       }
       else
       {
           Patient::read(istr);
       }
       return istr;
   }
}