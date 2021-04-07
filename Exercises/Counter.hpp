#pragma once


#include <cstddef>
#include <cstdint>

#include <QObject>

using namespace std;


class Counter : public QObject {
	Q_OBJECT

public:
	Counter() = default;

	int getValue() const { return val_; }

public slots:
	void setValue(int value) {
		val_ = value;
		emit valueChanged(value);
	}

	void reset() { setValue(0); }
	void increment() { setValue(val_ + 1); }
	void decrement() { setValue(val_ - 1); }

signals:
	void valueChanged(int newValue);

private:
	int val_ = 0;
};