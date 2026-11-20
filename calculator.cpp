 
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <sstream>

using namespace std;

class Calculator {
private:
    vector<string> history;

    void addToHistory(const string& entry) {
        history.push_back(entry);
    }

public:
    double add(double a, double b)      { return a + b; }
    double subtract(double a, double b) { return a - b; }
    double multiply(double a, double b) { return a * b; }

    bool divide(double a, double b, double& result) {
        if (b == 0) return false;
        result = a / b;
        return true;
    }

    bool modulo(long long a, long long b, long long& result) {
        if (b == 0) return false;
        result = a % b;
        return true;
    }

    double power(double base, double exp) { return pow(base, exp); }

    bool squareRoot(double a, double& result) {
        if (a < 0) return false;
        result = sqrt(a);
        return true;
    } 


    void record(const string& expression, double result) {
        ostringstream oss  ;
        oss << expression << " = " << result;
        addToHistory(oss.str());
    }

    void showHistory() const {
        if (history.empty()) {
            cout << "History is empty.\n";
            return;
        }
        cout << "\n--- History ---\n";
        for (size_t i = 0; i < history.size(); i++)
            cout << i + 1 << ". " << history[i] << "\n";
    }

    void clearHistory() {
        history.clear();
        cout << "History cleared.\n";
    }
};

double readNumber(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) return value;
        cout << "Invalid input, please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void printMenu() {
    cout << "\n===== Calculator =====\n"
         << "1. Add (+)\n"
         << "2. Subtract (-)\n"
         << "3. Multiply (*)\n"
         << "4. Divide (/)\n"
         << "5. Modulo (%)\n"
         << "6. Power (^)\n"
         << "7. Square root\n"
         << "8. Show history\n"
         << "9. Clear history\n"
         << "0. Exit\n"
         << "Choice: ";
}

int main() {
    Calculator calc;
    int choice;

    while (true) {
        printMenu();
        if (!(cin >> choice)) {
            cout << "Invalid choice.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 0) {
            cout << "Goodbye!\n";
            break;
        }

        double a, b, result;
        long long x, y, r;

        switch (choice) {
        case 1:
            a = readNumber("First number: ");
            b = readNumber("Second number: ");
            result = calc.add(a, b);
            cout << "Result: " << result << "\n";
            calc.record(to_string(a) + " + " + to_string(b), result);
            break;
        case 2:
            a = readNumber("First number: ");
            b = readNumber("Second number: ");
            result = calc.subtract(a, b);
            cout << "Result: " << result << "\n";
            calc.record(to_string(a) + " - " + to_string(b), result);
            break;
        case 3:
            a = readNumber("First number: ");
            b = readNumber("Second number: ");
            result = calc.multiply(a, b);
            cout << "Result: " << result << "\n";
            calc.record(to_string(a) + " * " + to_string(b), result);
            break;
        case 4:
            a = readNumber("First number: ");
            b = readNumber("Second number: ");
            if (calc.divide(a, b, result)) {
                cout << "Result: " << result << "\n";
                calc.record(to_string(a) + " / " + to_string(b), result);
            } else {
                cout << "Error: cannot divide by zero.\n";
            }
            break;
        case 5:
            x = (long long)readNumber("First integer: ");
            y = (long long)readNumber("Second integer: ");
            if (calc.modulo(x, y, r)) {
                cout << "Result: " << r << "\n";
                calc.record(to_string(x) + " % " + to_string(y), (double)r);
            } else {
                cout << "Error: modulo by zero.\n";
            }
            break;
        case 6:
            a = readNumber("Base: ");
            b = readNumber("Exponent: ");
            result = calc.power(a, b);
            cout << "Result: " << result << "\n";
            calc.record(to_string(a) + " ^ " + to_string(b), result);
            break;
        case 7:
            a = readNumber("Number: ");
            if (calc.squareRoot(a, result)) {
                cout << "Result: " << result << "\n";
                calc.record("sqrt(" + to_string(a) + ")", result);
            } else {
                cout << "Error: cannot take the square root of a negative number.\n";
            }
            break;
        case 8:
            calc.showHistory();
            break;
        case 9:
            calc.clearHistory();
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    }
    return 0;
}
