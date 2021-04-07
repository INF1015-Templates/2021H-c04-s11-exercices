/*
 * Copyright (C) 2015    Raphaël Beamonte <raphael.beamonte@polymtl.ca>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation  and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of any
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * This file has been created for the purpose of the INF1010
 * course of École Polytechnique de Montréal.
 * Version: 14/1.0
 */

#ifndef COMPANY_H
#define COMPANY_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

#include <QObject>

#include "Employee.hpp"

/**
 * @brief The Company class, to describe a company
 */
class Company : public QObject
{
    Q_OBJECT

public:
	// Constructors
	/**
	 * @brief Company Default constructor of the class
	 */
	Company();
	/**
	 * @brief Company Constructor receiving the company name and president names as parameters
	 * @param name The company name
	 * @param presidentName The president name
	 */
	Company(string name, string presidentName);
	/**
	 * @brief Company Copy constructor
	 * @param company The company to copy
	 */
	Company(const Company& company);
	/**
	 * @brief Company Destructor of the class
	 */
	~Company();

	// Getters
	/**
	 * @brief getName To get the company name
	 * @return The company name
	 */
	string getName() const;
	 /**
	 * @brief getPresident To get the president as employee
	 * @return The president to be retrieved
	 */
	Employee* getPresident() const;
	 /**
	 * @brief setPresident To set the employee as president
	 * @param president The president to be set
	 */
	void setPresident(Employee* president);
	/**
	 * @brief getNumberEmployees To get the number of employees in the company
	 * @return The number of employees in the company
	 */
	int getNumberEmployees() const;
	/**
	 * @brief hasEmployees To know if the company has employees
	 * @return Whether or not the company has employees
	 */
	bool hasEmployees() const;
	/**
	 * @brief getEmployee To get an employee using its index in the container
	 * @param index The index of the employee to get
	 * @return The pointer to the employee retrieved, or a null pointer if not found
	 */
    Employee* getEmployee(unsigned int index) const;
	/**
	 * @brief getEmployee To get an employee using its name
	 * @param name The name of the employee to get
	 * @return The pointer to the employee retrieved, or a null pointer if not found
	 */
	Employee* getEmployee(string name) const;
	/**
	 * @brief getEmployeesPerName To get a map of employees with their names as key
	 * @return A multimap of employees with keys as their names
	 */
	multimap<string, Employee*> getEmployeesPerName() const;

	// Setters
	/**
	 * @brief addEmployee To add an employee to the company
	 * @param employee The employee to add
	 */
	void addEmployee(Employee* employee);
	/**
	 * @brief delEmployee To delete an employee to the company
	 * @param employee The employee to delete
	 */
	void delEmployee(Employee* employee);

	// Overcharged operators
	/**
	 * @brief operator= To affect a company to another
	 * @param company the company to affect to the current one
	 */
	Company& operator=(const Company& company);
	/**
	 * @brief operator== To verify if a company is the same as another
	 * @param company the company to which we compare ours
	 */
	bool operator==(const Company& company) const;
	/**
	 * @brief operator+= To add an employee to our current company
	 * @param employee The employee to add
	 */
	Company& operator+=(Employee* employee);
	/**
	 * @brief operator+ To copy our company and add an employee to this new company
	 * @param employee The employee to add
	 */
	Company operator+(Employee* employee) const;
	/**
	 * @brief operator+= To add an employee to our current company
	 * @param employee The employee to add
	 */
	Company& operator+=(Employee& employee);
	/**
	 * @brief operator+ To copy our company and add an employee to this new company
	 * @param employee The employee to add
	 */
	Company operator+(Employee& employee) const;
	/**
	 * @brief operator+= To add all the employees of the given company to ours
	 * @param company The company from which to copy all the employees
	 */
	Company& operator+=(const Company& company);
	/**
	 * @brief operator+ To create a new company with the name and employees of
	 * both our company and the one received in parameter
	 * @param company The other company used to create the new one
	 */
	Company operator+(const Company& company) const;
	/**
	 * @brief operator<< To print a company and its president's name
	 * @param os The output stream to print to
	 * @param company The company to print
	 */
	friend ostream& operator<<(ostream& os, const Company& company);

signals:
    /**
     * @brief employeeAdded Signal sent when an employee is added
     * @param employee The employee that has been added
     */
    void employeeAdded(Employee* employee);
    /**
     * @brief employeeDeleted Signal sent when an employee is deleted
     * @param employee The employee that has been deleted
     */
    void employeeDeleted(Employee* employee);

private:
	// Attributes
	/**
	 * @brief name_ To store the name of the company
	 */
	string name_;
	/**
	 * @brief president_ To store the president of the company
	 */
	Employee* president_;
	/**
	 * @brief employees_ To store the employees of the company
	 */
	vector<Employee*> employees_;
};


/**
 * @brief operator<< To print a company and its president's name
 * @param os The output stream to print to
 * @param company The company to print
 */
ostream& operator<<(ostream& os, const Company& company);

#endif // COMPANY_H
