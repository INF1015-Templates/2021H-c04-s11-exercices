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

#include "Manager.hpp"

namespace company {

Manager::Manager()
	: Employee(), bonus_(0)
{
}

Manager::Manager(string name, double salary)
	: Employee(name, salary), bonus_(15)
{
}

Manager::Manager(string name, double salary, double bonus)
	: Employee(name, salary), bonus_(bonus)
{
}

string Manager::getName() const {
	return Employee::getName() + " (Manager)";
}

double Manager::getSalary() const {
	return Employee::getSalary() * (1 + (bonus_ / 100.0));
}

double Manager::getBonus() const {
	return bonus_;
}

Employee* Manager::getEmployee(string name) const {
    for (unsigned int i = 0; i < managedEmployees_.size(); i++) {
		if (managedEmployees_[i]->getName() == name) {
			return managedEmployees_[i];
		}
	}

	/* Return a nullptr because we didn't
	 * find the Employee we searched for
	 */
	return nullptr;
}

void Manager::setBonus(double bonus) {
	bonus_ = bonus;
}

void Manager::addEmployee(Employee* employee) {
	managedEmployees_.push_back(employee);
}

}