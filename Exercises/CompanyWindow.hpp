#pragma once

#include <QMainWindow>
#include <QListWidget>
#include <QString>

#include <memory>
#include <vector>

#include "Company.hpp"

using namespace std;


QT_BEGIN_NAMESPACE
namespace Ui { class CompanyWindow; }
QT_END_NAMESPACE


class CompanyWindow : public QMainWindow {
	Q_OBJECT

public:
	CompanyWindow(QWidget* parent = nullptr);
	CompanyWindow(unique_ptr<Company> company, QWidget* parent = nullptr);
	CompanyWindow(Company* company, QWidget* parent = nullptr);

	~CompanyWindow() override;

public slots:
	/**
	 * @brief filterList Slot to filter the list according to the received parameter
	 */
	void filterList(int);
	/**
	 * @brief selectEmployee Slot to select an employee given a QListWidgetItem
	 */
	void selectEmployee(QListWidgetItem*);
	/**
	 * @brief cleanDisplay To clean the editor on the right of the GUI
	 */
	void cleanDisplay();
	/**
	 * @brief changedType To update the editor when we select a different type of employee
	 */
	void changedType(int);
	/**
	 * @brief fireEveryone To fire all the employees
	 */
	void fireEveryone();
	/**
	 * @brief fireSelected To fire only the selected employees
	 */
	void fireSelected();
	/**
	 * @brief createEmployee To create a new employee locally
	 */
	void createEmployee();
	/**
	 * @brief employeeHasBeenAdded To run when an employee has been added
	 */
	void employeeHasBeenAdded(Employee*);
	/**
	 * @brief employeeHasBeenDeleted To run when an employee has been deleted
	 */
	void employeeHasBeenDeleted(Employee*);


private:
	CompanyWindow(unique_ptr<Company> companyRes, Company* company, QWidget* parent);

	void setupMenu();
	void setupUi();
	void loadEmployees();
	bool filterHide(Employee* employee);

	unique_ptr<Ui::CompanyWindow> ui_;
	unique_ptr<Company> companyRessource_;
	Company* company_;
	vector<unique_ptr<Employee>> added_;
	int currentFilterIndex_ = 0;
};
