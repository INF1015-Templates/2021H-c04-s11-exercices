#include "CounterWindow.hpp"
#include "ui_CounterWindow.h"


CounterWindow::CounterWindow(QWidget* parent)
: QMainWindow(parent),
  ui_(new Ui::CounterWindow) {
	ui_->setupUi(this);

	setupButtons();
	setupActions();

	counter_.reset();
}

CounterWindow::~CounterWindow() { }

void CounterWindow::setupButtons() {
	connect(ui_->btnPlus, SIGNAL(clicked()), &counter_, SLOT(increment()));
	connect(ui_->btnMinus, SIGNAL(clicked()), &counter_, SLOT(decrement()));
	connect(ui_->btnZero, SIGNAL(clicked()), &counter_, SLOT(reset()));
	connect(&counter_, SIGNAL(valueChanged(int)), ui_->labelCounter, SLOT(setNum(int)));
}

void CounterWindow::setupActions() {
	connect(ui_->actionPlus, SIGNAL(triggered()), &counter_, SLOT(increment()));
	connect(ui_->actionMinus, SIGNAL(triggered()), &counter_, SLOT(decrement()));
	connect(ui_->actionReset, SIGNAL(triggered()), &counter_, SLOT(reset()));
	addAction(ui_->actionPlus);
	addAction(ui_->actionMinus);
	addAction(ui_->actionReset);
}
