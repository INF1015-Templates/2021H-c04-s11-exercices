#pragma once

#include <QMainWindow>

#include <memory>

#include "Counter.hpp"

using namespace std;


QT_BEGIN_NAMESPACE
namespace Ui { class CounterWindow; }
QT_END_NAMESPACE


class CounterWindow : public QMainWindow {
	Q_OBJECT

public:
	CounterWindow(QWidget* parent = nullptr);
	~CounterWindow() override;

private:
	void setupButtons();
	void setupActions();

	unique_ptr<Ui::CounterWindow> ui_;
	Counter counter_;
};
