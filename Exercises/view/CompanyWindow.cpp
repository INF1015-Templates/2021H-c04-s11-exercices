
#include <cstddef>
#include <cstdint>

#include <string>

#include <cppitertools/itertools.hpp>

#include <company/Company.hpp>
#include <company/Employee.hpp>
#include <company/Secretary.hpp>
#include <company/Manager.hpp>

#include "CompanyWindow.hpp"
#include "ui_CompanyWindow.h"

using namespace std;
using namespace iter;


namespace view {

CompanyWindow::CompanyWindow(QWidget* parent)
: CompanyWindow(make_unique<Company>(), nullptr, parent) { }

CompanyWindow::CompanyWindow(unique_ptr<Company> company, QWidget* parent)
: CompanyWindow(std::move(company), nullptr, parent) { }

CompanyWindow::CompanyWindow(Company* company, QWidget* parent)
: CompanyWindow(nullptr, company, parent) { }

CompanyWindow::CompanyWindow(unique_ptr<Company> companyRes, Company* company, QWidget* parent)
: QMainWindow(parent),
  ui_(make_unique<Ui::CompanyWindow>()),
  companyRessource_(std::move(companyRes)),
  company_(company != nullptr ? company : companyRessource_.get()) {
	ui_->setupUi(this);

	setupUi();
	setupMenu();

	// On connecte les signaux de notre company aux slots créés localement pour agir suite à ces signaux
	connect(company_, SIGNAL(employeeAdded(Employee*)), this, SLOT(employeeHasBeenAdded(Employee*)));
	connect(company_, SIGNAL(employeeDeleted(Employee*)), this, SLOT(employeeHasBeenDeleted(Employee*)));

	loadEmployees();
}

CompanyWindow::~CompanyWindow() { }

void CompanyWindow::setupMenu() {
	ui_->actionExit->setShortcuts(QKeySequence::Quit);
}

void CompanyWindow::setupUi() {
	// Le sélecteur pour filtrer ce que l'on souhaite dans la liste
	connect(ui_->showCombobox, SIGNAL(currentIndexChanged(int)), this, SLOT(filterList(int)));

	// La liste des employés
	connect(ui_->employeesList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(selectEmployee(QListWidgetItem*)));

	// Le bouton pour congédier tout le monde
	connect(ui_->fireEveryoneButton, SIGNAL(clicked()), this, SLOT(fireEveryone()));

	// Le bouton pour remettre à zéro la vue et créer un nouvel employé
	connect(ui_->hireSomeoneButton, SIGNAL(clicked()), this, SLOT(cleanDisplay()));

	// Boutons radio
	connect(ui_->employeeTypeRadioButtons, SIGNAL(buttonClicked(int)), this, SLOT(changedType(int)));

	// Bouton pour congédier la ou les personne(s) sélectionnée(s) dans la liste
	connect(ui_->fireButton, SIGNAL(clicked()), this, SLOT(fireSelected()));

	// Bouton pour embaucher la personne dont on vient d'entrer les informations
	connect(ui_->hireButton, SIGNAL(clicked()), this, SLOT(createEmployee()));

	// Enfin, on met à jour le titre de la fenêtre
	QString title = "Employee Manager for " + QString(company_->getName().c_str());
	setWindowTitle(title);
}

void CompanyWindow::loadEmployees() {
	// On s'assure que la liste est vide
	ui_->employeesList->clear();
	// Puis, pour tous les employés dans Company
	int max = company_->getNumberEmployees();
	for (int i : range(max)) {
		// On récupère le pointeur vers l'employé
		Employee* employee = company_->getEmployee(i);
		if (employee == nullptr)
			continue;
		// Et on l'ajoute en tant qu'item de la liste:
		// le nom sera affiché, et le pointeur sera contenu
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(employee->getName()), ui_->employeesList);
		item->setData(Qt::UserRole, QVariant::fromValue<Employee*>(employee));
		item->setHidden(filterHide(employee));
	}
}

bool CompanyWindow::filterHide(Employee* employee) {
	switch (currentFilterIndex_) {
	case 1:
		return dynamic_cast<Manager*>(employee) != nullptr;
	case 2:
		return dynamic_cast<Secretary*>(employee) != nullptr;
	case 3:
		return dynamic_cast<Employee*>(employee) != nullptr;
	case 0:
	default:
		return false;
	}
}

void CompanyWindow::filterList(int index) {
	currentFilterIndex_ = index;

	for (int i : range(ui_->employeesList->count())) {
		QListWidgetItem *item = ui_->employeesList->item(i);
		Employee* employee = item->data(Qt::UserRole).value<Employee*>();
		item->setHidden(filterHide(employee));
	}
}

void CompanyWindow::selectEmployee(QListWidgetItem* item) {
	Employee* employee = item->data(Qt::UserRole).value<Employee*>();

	ui_->nameEditor->setDisabled(true);
	ui_->nameEditor->setText(QString::fromStdString(employee->getName()));

	ui_->salaryEditor->setDisabled(true);
	ui_->salaryEditor->setText(QString::number(employee->getSalary()));

	ui_->bonusEditor->setDisabled(true);
	if (typeid(*employee) == typeid(Manager)) {
		ui_->bonusEditor->setText(QString("%1% (included in salary)").arg(((Manager*)employee)->getBonus()));
	} else {
		ui_->bonusEditor->setText("");
	}

	for (auto&& btn : ui_->employeeTypeRadioButtons->buttons()) {
		btn->setDisabled(true);

		bool checked = (typeid(*employee) == typeid(Manager) && btn->text().endsWith("Manager"))
		               || (typeid(*employee) == typeid(Secretary) && btn->text().endsWith("Secretary"))
		               || (typeid(*employee) == typeid(Employee) && btn->text().endsWith("Employee"));

		btn->setChecked(checked);
	}

	ui_->fireButton->setDisabled(false);
	ui_->hireButton->setDisabled(true);
}

void CompanyWindow::cleanDisplay() {
	ui_->nameEditor->setDisabled(false);
	ui_->nameEditor->setText("");

	ui_->salaryEditor->setDisabled(false);
	ui_->salaryEditor->setText("");

	ui_->bonusEditor->setDisabled(true);
	ui_->bonusEditor->setText("");

	for (auto&& btn : ui_->employeeTypeRadioButtons->buttons()) {
		btn->setDisabled(false);
		if (btn->text().endsWith("Employee")) {
			btn->setChecked(true);
		}
	}

	ui_->employeesList->clearSelection();

	ui_->fireButton->setDisabled(true);
	ui_->hireButton->setDisabled(false);

	ui_->nameEditor->setFocus();
}

void CompanyWindow::changedType(int index) {
	if (index == -2) {
		ui_->bonusEditor->setDisabled(false);
	} else {
		ui_->bonusEditor->setDisabled(true);
	}
}

void CompanyWindow::fireEveryone() {
	vector<Employee*> toDelete;
	for (int i = 0; i < ui_->employeesList->count(); ++i) {
		QListWidgetItem *item = ui_->employeesList->item(i);
		toDelete.push_back(item->data(Qt::UserRole).value<Employee*>());
	}

	for (Employee* e : toDelete) {
		company_->delEmployee(e);
	}
}

void CompanyWindow::fireSelected() {
	vector<Employee*> toDelete;
	for (QListWidgetItem *item : ui_->employeesList->selectedItems()) {
		toDelete.push_back(item->data(Qt::UserRole).value<Employee*>());
	}

	for (Employee* e : toDelete) {
		company_->delEmployee(e);
	}
}

void CompanyWindow::createEmployee() {
	// On va créer un nouvel employé que l'on placera dans ce pointeur
	unique_ptr<Employee> newEmployee;

	// On créé le bon type d'employé selon le cas
	QAbstractButton* selectedType = 0;
	for (auto&& btn : ui_->employeeTypeRadioButtons->buttons()) {
		if (btn->isChecked()) {
			selectedType = btn;
			break;
		}
	}

	// On créé le bon type d'employé selon le cas
	if (selectedType->text().endsWith("Manager")) {
		newEmployee = make_unique<Manager>(
			ui_->nameEditor->text().toStdString(),
			ui_->salaryEditor->text().toDouble(),
			ui_->bonusEditor->text().toDouble()
		);
	} else if (selectedType->text().endsWith("Secretary")) {
		newEmployee = make_unique<Secretary>(ui_->nameEditor->text().toStdString(), ui_->salaryEditor->text().toDouble());
	} else {
		newEmployee = make_unique<Employee>(ui_->nameEditor->text().toStdString(), ui_->salaryEditor->text().toDouble());
	}

	// On ajoute le nouvel employé créé à la company
	company_->addEmployee(newEmployee.get());
	// Mais on le stocke aussi localement pour pouvoir le supprimer plus tard
	added_.push_back(std::move(newEmployee));
}

void CompanyWindow::employeeHasBeenAdded(Employee* employee) {
	// On ajoute le nouvel employé comme item de la QListWidget
	QListWidgetItem* item = new QListWidgetItem(
		QString::fromStdString(employee->getName()), ui_->employeesList);
	item->setData(Qt::UserRole, QVariant::fromValue<Employee*>(employee));

	// On change la visibilité de notre nouvel employé selon
	// le filtre actuel
	item->setHidden(filterHide(employee));
}

void CompanyWindow::employeeHasBeenDeleted(Employee* e) {
	// On cherche dans notre QlistWidget l'employé pour lequel le
	// signal a été envoyé, afin de l'en retirer
	for (int i = 0; i < ui_->employeesList->count(); ++i) {
		QListWidgetItem *item = ui_->employeesList->item(i);
		Employee* employee = item->data(Qt::UserRole).value<Employee*>();
		if (employee == e) {
			// delete sur un QlistWidget item va automatiquement le retirer de la liste
			delete item;
			// Si l'employé faisait partie de ceux créés localement, on veut le supprimer.
			auto it = std::find_if(added_.begin(), added_.end(), [&] (auto& arg) { return arg.get() == e; });
			if (it != added_.end()) {
				added_.erase(it);
			}
			// L'employé ne devrait être qu'une fois dans la liste...
			break;
		}
	}
	// On remet à zéro l'affichage de la colonne de gauche étant
	// donné que les employés sélectionnés ont été supprimés
	cleanDisplay();
}

}

Q_DECLARE_METATYPE(company::Employee*)

