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

#pragma once

#include <string>
#include <vector>

#include "Employee.hpp"
using namespace std;

namespace company {

/**
 * @brief The Manager class, a special type of Employee
 */
class Manager : public Employee
{
public:
	// Constructors
	/**
	* @brief Manager The default constructor
	*/
	Manager();
	/**
	* @brief Manager Constructor
	* @param name The name of the manager
	* @param salary The salary of the manager
	*/
	Manager(string name, double salary);
	/**
	* @brief Manager Constructor
	* @param name The name of the manager
	* @param salary The salary of the manager
	* @param bonus The bonus (in percent) of the manager
	*/
	Manager(string name, double salary, double bonus);

	// Getters
	/**
	* @brief getName To get the name of the manager
	* @return The name of the manager, and its status (Manager)
	*/
	virtual string getName() const;
	/**
	* @brief getSalary To get the salary of the manager
	* @return The salary of the manager, including its bonus
	*/
	virtual double getSalary() const;
	/**
	* @brief getBonus To get the bonus of the manager
	* @return The bonus of the manager (in percent)
	*/
	double getBonus() const;
	/**
	* @brief getEmployee To get an employee of the manager
	* @param name The name of the employee to get
	* @return The employee of that name, or a nullptr if not found
	*/
	Employee* getEmployee(string name) const;

	// Setters
	/**
	* @brief setBonus To change the bonus of the manager
	* @param bonus The new bonus (in percent)
	*/
	void setBonus(double bonus);
	/**
	* @brief addEmployee To add an employee to the manager
	* @param employee The employee to add
	*/
	void addEmployee(Employee* employee);	

private:
	// Attributes
	/**
	* @brief bonus_ To store the bonus of the manager
	*/
	double bonus_;
	/**
	* @brief managedEmployees_ To store the employees managed by the manager
	*/
	vector<Employee*> managedEmployees_;
};

}

