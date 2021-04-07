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

#include <algorithm>
#include <iostream>
using namespace std;

#include "Company.hpp"
#include "SearchEmployeeByName.hpp"
#include "InsertInMap.hpp"

Company::Company()
	: name_("unknown"), president_(nullptr)
{
}

Company::Company(string name, string presidentName)
	: name_(name), president_(nullptr)
{
	president_ = new Employee(presidentName);
}

Company::Company(const Company& company)
    : QObject(), name_(company.name_),
      president_(nullptr), employees_(company.employees_)
{
	president_ = new Employee(*(company.president_));
}

Company::~Company()
{
	delete president_;
}

string Company::getName() const
{
	return name_;
}

Employee* Company::getPresident() const
{
	return president_;
}

void Company::setPresident(Employee* president)
{
	delete president_;
	president_ = new Employee(president->getName());
}

int Company::getNumberEmployees() const
{
	return employees_.size();
}

bool Company::hasEmployees() const
{
	return (!employees_.empty());
}

Employee* Company::getEmployee(unsigned int index) const
{
	if (index >= 0 && index < employees_.size()) {
		return employees_[index];
	}

	/* Return a nullptr because we didn't
	 * find the Employee we searched for
	 */
	return nullptr;
}

Employee* Company::getEmployee(string name) const
{
	SearchEmployeeByName search(name);

	//auto => vector<Employee*>::const_iterator
	auto it = find_if(employees_.begin(), employees_.end(), search);
	if (it != employees_.end()) {
		return *it;
	}

	/* Return a nullptr because we didn't
	 * find the Employee we searched for
	 */
	return nullptr;
}

void Company::addEmployee(Employee* employee)
{
	// Insert new employee
	employees_.push_back(employee);
    emit employeeAdded(employee);
}

void Company::delEmployee(Employee* employee)
{
	// auto => vector<Employee*>::iterator
	auto it = find(employees_.begin(), employees_.end(), employee);

	if (it != employees_.end()) {
        Employee* e = *it;
		employees_.erase(it);
        emit employeeDeleted(e);
	}
}

// Overcharged operators
Company& Company::operator=(const Company& company)
{
	if (this != &company) {
			delete president_;

		president_ = new Employee(*(company.president_));
		name_ = company.name_;
		employees_ = company.employees_;
	}
	return *this;
}

bool Company::operator==(const Company& company) const
{
	return (name_ == company.name_ &&
		president_ == company.president_ &&
		employees_ == company.employees_);
}

Company& Company::operator+=(Employee *employee)
{
	addEmployee(employee);
	return *this;
}

Company Company::operator+(Employee* employee) const
{
	Company company(name_, president_->getName());
	for (int i = 0; i < getNumberEmployees(); i++) {
		company.addEmployee(getEmployee(i));
	}
	company.addEmployee(employee);
	return company;
}

Company& Company::operator+=(Employee& employee)
{
	addEmployee(&employee);
	return *this;
}

Company Company::operator+(Employee& employee) const
{
	Company company(name_, president_->getName());
	for (int i = 0; i < getNumberEmployees(); i++) {
		company.addEmployee(getEmployee(i));
	}
	company.addEmployee(&employee);
	return company;
}

Company& Company::operator+=(const Company& company)
{
	for (int i = 0; i < company.getNumberEmployees(); i++) {
		addEmployee(company.getEmployee(i));
	}
	return *this;
}

Company Company::operator+(const Company& company) const
{
	Company c2(name_ + " " + company.name_, president_->getName());
	for (int i = 0; i < getNumberEmployees(); i++) {
		c2.addEmployee(getEmployee(i));
	}
	for (int i = 0; i < company.getNumberEmployees(); i++) {
		c2.addEmployee(company.getEmployee(i));
	}
	return c2;
}

ostream& operator<<(ostream& os, const Company& company)
{
	os << "This is the company " << company.getName()
	   << " presided by " << company.getPresident()->getName()
	   << endl;
	if (company.hasEmployees()) {
		os << "This company has "
		   << company.getNumberEmployees()
		   << " employee(s): ";
		for (int i = 0; i < company.getNumberEmployees(); i++)
			os << endl
			   << " - Employee " << i << ": "
			   << company.getEmployee(i)->getName()
			   << ", paid $"
			   << company.getEmployee(i)->getSalary();
	} else {
		os << "This company does not have any employees.";
	}

	return os;
}

multimap<string, Employee*> Company::getEmployeesPerName() const {
    multimap<string, Employee*> employeesPerName;
    for_each(employees_.begin(), employees_.end(), InsertInMap(employeesPerName));

    return employeesPerName;
}
