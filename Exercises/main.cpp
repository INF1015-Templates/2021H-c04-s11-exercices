
#include <cstddef>
#include <cstdint>

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
				exit(EXIT_FAILURE);
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

	auto hasDataLeft = [] (istream& file) {
		return not(file.eof() or ws(file).eof());
	};

	try {
		List<int> values;
		filesystem::remove("values.txt");
		ofstream("values.txt") << "1 42 69 popf 9000 popb popb popf popf 42 0xBEEF 0xRAWR";
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
	{
		try {
			cout << "---A---" << "\n";
			MyClass foo;
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
			Spam() : m(new MyClass) {
				printDefCtor("Spam");
				throw 42;
			}
			~Spam() {
				delete m;
				printDtor("Spam");
			}

			MyClass* m;
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


int main(int argc, char* argv[]) {
	//return runQtExample(argc, argv);
	//runListExample();
	runRaiiExample();
}
