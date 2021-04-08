
#include <cstddef>
#include <cstdint>

#include <cassert>
#include <fstream>
#include <filesystem>

#include <QException>
#include <QApplication>
#include <QMessageBox>

#include <view/CompanyWindow.hpp>
#include <utils/List.hpp>
#include <utils/MyClass.hpp>

using namespace std;


int runQtExample(int argc, char* argv[]) {
	struct Application : public QApplication {
		using QApplication::QApplication;

		bool notify(QObject* receiver, QEvent* event) override {
			try {
				return QApplication::notify(receiver, event);
			} catch (exception& e) {
				QMessageBox::critical(
					nullptr,
					tr("Unhandled exception caught."),
					tr(e.what())
				);
				QApplication::exit(EXIT_FAILURE);
				return false;
			}
		}
	};

	Application a(argc, argv);
	view::CompanyWindow w;
	w.show();
	return a.exec();
}

void runListExample() {
	using namespace utils;

	static auto hasDataLeft = [] (istream& file) {
		return not(file.eof() or ws(file).eof());
	};

	try {
		List<int> values;

		filesystem::remove("values.txt");
		ofstream("values.txt") << "1 42 69 popf 9000 popb popb popf popf henlo 42 0xBEEF 0xRAWR";

		ifstream file("values.txt");
		file.exceptions(ios::failbit);
		while (hasDataLeft(file)) {
			try {
				string x;
				file >> x;
				if (x == "popf")
					values.pop_front();
				else if (x == "popb")
					values.pop_back();
				else {
					try {
						values.push_back(stoi(x, nullptr, 0));
					} catch (invalid_argument& e) {
						cout << "Unrecognized value or command: " << x << "\n";
					}
				}
				cout << values << "\n";
			} catch (EmptyListError& e) {
				cout << e.what() << "\n";
			}
		}
	} catch (ios::failure& e) {
		cout << e.what() << "\n" << e.code() << "\n";
	}
}

void runRaiiExample() {
	using namespace utils;

	{
		try {
			cout << "---A---" << "\n";
			unique_ptr<MyClass> foo = make_unique<MyClass>();
			throw 42;
			cout << "---B---" << "\n";
		} catch (...) {
			cout << "---C---" << "\n";
		}
		cout << "---D---" << "\n";
	}
	cout << "- - - - - - - - - - - - - - - - - - -" << "\n";
	{
		struct Spam {
			Spam() : m(make_unique<MyClass>()) {
				printDefCtor("Spam");
				{ throw 42; }
			}
			~Spam() {
				printDtor("Spam");
			}

			unique_ptr<MyClass> m;
		};
		try {
			cout << "---A---" << "\n";
			Spam spam;
			cout << "---B---" << "\n";
		} catch (...) {
			cout << "---C---" << "\n";
		}
		cout << "---D---" << "\n";
	}
}

double fn1_assert(double x, double y) {
	assert(x != y);
	return (x+y)/(x-y);
}

pair<double, bool> fn1_pair(double x, double y) {
	return {(x+y)/(x-y), x != y};
}

optional<double> fn1_opt(double x, double y) {
	if (x == y)
		return {};
	return (x+y)/(x-y);
}

double fn1_except(double x, double y) {
	if (x == y)
		// Erreur dont on peut récupérer.
		throw logic_error("Div by 0");
	return (x+y)/(x-y);
}

void runSimpleExceptExample() {

	auto&& [res, ok] = fn1_pair(5, 5);
	if (ok)
		cout << res << "\n";
	else
		cout << "Numerical error" << "\n";

	optional<double> res2 = fn1_opt(5, 5);
	if (res2)
		cout << *res2 << "\n";
	else
		cout << "Numerical error" << "\n";

	try {
		double res3 = fn1_except(5, 5);
		cout << res3 << "\n";
	} catch (logic_error& e) {
		cout << "Error: " << e.what() << "\n";
	}

	cout << "Ok I'm done" << "\n";
}



int main(int argc, char* argv[]) {
	return runQtExample(argc, argv);

	//try {
	//	runListExample();
	//} catch (system_error& e) {
	//	cout << e.what() << e.code();
	//} catch (exception& e) {
	//	cout << e.what();
	//} catch (...) {
	//	cout << "Unrecognized exception caught" << "\n";
	//}

	//runRaiiExample();
	
	//runSimpleExceptExample();
}
