#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Triangle {
private:
    double sideA, sideB, sideC;
    string color;

    // Функція перевірки валідності сторін трикутника
    bool isValidTriangle(double a, double b, double c) {
        return (a > 0 && b > 0 && c > 0 &&
                a + b > c && a + c > b && b + c > a);
    }

public:
    // Конструктор за замовчуванням
    Triangle() : sideA(1), sideB(1), sideC(1), color("білий") {}

    // Конструктор з параметрами
    Triangle(double a, double b, double c, string clr) {
        if (isValidTriangle(a, b, c)) {
            sideA = a;
            sideB = b;
            sideC = c;
            color = clr;
        } else {
            throw invalid_argument("Невірні параметри для сторін трикутника");
        }
    }

    // Функція встановлення значень сторін
    void setSides(double a, double b, double c) {
        if (isValidTriangle(a, b, c)) {
            sideA = a;
            sideB = b;
            sideC = c;
        } else {
            throw invalid_argument("Невірні параметри для сторін трикутника");
        }
    }

    // Функція встановлення кольору
    void setColor(string clr) {
        color = clr;
    }

    // Функції повернення значень
    double getSideA() const { return sideA; }
    double getSideB() const { return sideB; }
    double getSideC() const { return sideC; }
    string getColor() const { return color; }

    // Функція обчислення периметра
    double getPerimeter() const {
        return sideA + sideB + sideC;
    }

    // Функція обчислення площі (за формулою Герона)
    double getArea() const {
        double s = getPerimeter() / 2;
        return sqrt(s * (s - sideA) * (s - sideB) * (s - sideC));
    }

    // Функція друку
    void print() const {
        cout << "Трикутник:\n"
             << "Сторони: " << sideA << ", " << sideB << ", " << sideC << "\n"
             << "Колір: " << color << "\n"
             << "Периметр: " << getPerimeter() << "\n"
             << "Площа: " << getArea() << "\n";
    }
};

// Функція введення даних з клавіатури
Triangle inputFromKeyboard() {
    double a, b, c;
    string color;
    cout << "Введіть сторони трикутника (a, b, c): ";
    cin >> a >> b >> c;
    cout << "Введіть колір трикутника: ";
    cin >> color;
    return Triangle(a, b, c, color);
}

// Функція введення даних з файлу
Triangle inputFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        throw runtime_error("Неможливо відкрити файл");
    }
    double a, b, c;
    string color;
    file >> a >> b >> c >> color;
    file.close();
    return Triangle(a, b, c, color);
}

// Функція генерації трикутника із випадковими параметрами
Triangle generateRandomTriangle() {
    srand(time(0));
    double a, b, c;
    do {
        a = rand() % 20 + 1;
        b = rand() % 20 + 1;
        c = rand() % 20 + 1;
    } while (a + b <= c || a + c <= b || b + c <= a);

    string colors[] = {"червоний", "синій", "зелений", "жовтий", "білий"};
    string color = colors[rand() % 5];
    return Triangle(a, b, c, color);
}

// Тестова програма
int main() {
    try {
        // Введення з клавіатури
        cout << "Введення з клавіатури:\n";
        Triangle t1 = inputFromKeyboard();
        t1.print();

        // Введення з файлу
        cout << "\nВведення з файлу:\n";
        Triangle t2 = inputFromFile("triangle.txt");
        t2.print();

        // Генерація випадкового трикутника
        cout << "\nВипадковий трикутник:\n";
        Triangle t3 = generateRandomTriangle();
        t3.print();
    } catch (const exception& e) {
        cerr << "Помилка: " << e.what() << endl;
    }
    return 0;
}
