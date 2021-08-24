/* Citation and Sources...
Final Project Milestone 5
Module:     PreTriage
Filename:   PreTriage.cpp
Version:    1.0
Author:     Pratham Jani
Revision History
-----------------------------------------------------------
Date      Reason
2021/08/03  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include "PreTriage.h"
#include "utils.h"
#include "CovidPatient.h"
#include "TriagePatient.h"


using namespace std;

namespace sdds {

	PreTriage::PreTriage(const char* dataFilename) :
		m_averCovidWait(15),
		m_averTriageWait(5),
		m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2),
		m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2)
	{
		m_dataFilename = nullptr;
		m_dataFilename = new char[strlen(dataFilename) + 1];
		strcpy(m_dataFilename, dataFilename);
		load();
	}

	PreTriage::~PreTriage() {
		ofstream out(m_dataFilename);
		out << m_averCovidWait << "," << m_averTriageWait << endl;
		cout << "Saving Average Wait Times," << endl;
		cout << "   COVID Test: " << m_averCovidWait << endl;
		cout << "   Triage: " << m_averTriageWait << endl;
		cout << "Saving m_lineup..." << endl;

		for (int i = 0; i < m_lineupSize; i++) {
			m_lineup[i]->fileIO(true);
			cout << (i + 1) << "- " << *m_lineup[i] << endl;
			out << *m_lineup[i] << endl;
		}

		for (int i = 0; i < m_lineupSize; i++) {
			delete m_lineup[i];
			m_lineup[i] = nullptr;
		}

		delete[] m_dataFilename;
		m_dataFilename = nullptr;

		cout << "done!" << endl;
	}

	void PreTriage::run(void) {
		int selection;

		while (m_appMenu >> selection) {
			switch (selection) {
			case 1:
				reg();
				break;
			case 2:
				admit();
				break;
			default:
				break;
			}
		}
	}
	
	void PreTriage::reg() {
		if (m_lineupSize == maxNoOfPatients) {
			cout << "Line up full!" << endl;
		}
		else {
			int selection;
			m_pMenu >> selection;

			switch (selection) {
			case 1:
				m_lineup[m_lineupSize] = new CovidPatient();
				break;

			case 2:
				m_lineup[m_lineupSize] = new TriagePatient();
				break;
			default:
				break;
			}

			m_lineup[m_lineupSize]->setArrivalTime(); 
			cout << "Please enter patient information: " << endl;
			m_lineup[m_lineupSize]->fileIO(false);
			cin >> *m_lineup[m_lineupSize]; 
			cout << endl;

			cout << "******************************************" << endl;
			cout << *m_lineup[m_lineupSize]; 
			cout << "Estimated Wait Time: ";  
			cout << getWaitTime(*m_lineup[m_lineupSize]) << endl;
			cout << "******************************************" << endl << endl;
			m_lineupSize++;
		}
	}

	void PreTriage::admit() {
		int selection, num = -1;
		char type = ' ';

		m_pMenu >> selection;
		switch (selection) {
		case 1:
			type = 'C';
			break;
		case 2:
			type = 'T';
			break;
		default:
			break;
		}

		num = indexOfFirstInLine(type);
		if (num != -1) {
			cout << endl;
			cout << "******************************************" << endl;
			m_lineup[num]->fileIO(false);
			cout << "Calling for "; 
			cout << *m_lineup[num];
			cout << "******************************************" << endl << endl;
			setAverageWaitTime(*m_lineup[num]);
			removePatientFromLineup(num);
		}
	}

	const Time PreTriage::getWaitTime(const Patient& p) const {
		unsigned int num = 0;
		for (int i = 0; i < m_lineupSize; i++) {
			if (p == *m_lineup[i]) {
				num++;
			}
		}
		return Time(p) * num;
	}

	void PreTriage::setAverageWaitTime(const Patient& p) {
		int CT = getTime();
		int PTT = Time(p);
		int PTN = p.number();
		if (p == 'C') {
			m_averCovidWait = ((CT - PTT) + (int(m_averCovidWait) * (PTN - 1))) / PTN;
		}
		else if (p == 'T') {
			m_averTriageWait = ((CT - PTT) + (int(m_averTriageWait) * (PTN - 1))) / PTN;
		}
	}

	void PreTriage::removePatientFromLineup(int index) {
		removeDynamicElement(m_lineup, index, m_lineupSize);
	}

	int PreTriage::indexOfFirstInLine(char type) const {
		int i = 0, index = -1;
		while (i < m_lineupSize && index == -1) {
			if (m_lineup[i]->type() == type) {
				index = i;
			}
			i++;
		}
		return index;
	}

	void PreTriage::load() {

		ifstream readfile(m_dataFilename);
		Patient* temp = nullptr;
		char type;
		cout << "Loading data..." << endl;
		readfile >> m_averCovidWait;
		readfile.ignore(1000, ',');
		readfile >> m_averTriageWait;
		readfile.ignore(1000, '\n');

		for (int i = 0; i < maxNoOfPatients && !readfile.eof(); i++)
		{
			type = ' ';
			readfile >> type;
			readfile.ignore(1000, ',');
			if (type == 'C')
			{
				temp = new CovidPatient();
			}
			else if (type == 'T')
			{
				temp = new TriagePatient();
			}
			if (temp != nullptr)
			{
				temp->fileIO(true);
				temp->csvRead(readfile);
				temp->fileIO(false);
				m_lineup[i] = temp;
				temp = nullptr;
				m_lineupSize++;
			}
		}

		if (!readfile.eof())
		{
			cout << "Warning: number of records exceeded " << maxNoOfPatients << endl;
		}
		if (m_lineupSize == 0)
		{
			cout << "No data or bad data file!" << endl << endl;
		}
		else
		{
			cout << m_lineupSize << " Records imported..." << endl << endl;
		}
	}
}