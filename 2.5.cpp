#include <iostream>
#include <stdexcept>

class Vector {
private:
    long* data;        // Вказівник на масив
    size_t size;       // Розмір масиву
    int state;         // Стан об'єкта
    static int count;  // Лічильник об'єктів

public:
    // Конструктор без параметрів
    Vector() : size(1), state(0) {
        try {
            data = new long[size]{0};
            ++count;
        } catch (const std::bad_alloc&) {
            state = 1; // Помилка виділення пам'яті
        }
    }

    // Конструктор з одним параметром (розмір вектора)
    Vector(size_t n) : size(n), state(0) {
        try {
            data = new long[size]{0};
            ++count;
        } catch (const std::bad_alloc&) {
            state = 1;
        }
    }

    // Конструктор з двома параметрами (розмір і значення ініціалізації)
    Vector(size_t n, long init_value) : size(n), state(0) {
        try {
            data = new long[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = init_value;
            }
            ++count;
        } catch (const std::bad_alloc&) {
            state = 1;
        }
    }

    // Конструктор копіювання
    Vector(const Vector& other) : size(other.size), state(other.state) {
        try {
            data = new long[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
            ++count;
        } catch (const std::bad_alloc&) {
            state = 1;
        }
    }

    // Оператор присвоєння
    Vector& operator=(const Vector& other) {
        if (this == &other) return *this; // Захист від самоприсвоєння

        delete[] data; // Звільняємо пам'ять

        size = other.size;
        state = other.state;

        try {
            data = new long[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        } catch (const std::bad_alloc&) {
            state = 1;
        }

        return *this;
    }

    // Деструктор
    ~Vector() {
        delete[] data;
        --count;
    }

    // Присвоєння значення елементу
    void set(size_t index, long value) {
        if (index >= size) {
            state = 2; // Вихід за межі масиву
            return;
        }
        data[index] = value;
    }

    // Отримання значення елемента
    long get(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // Друк вектора
    void print() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << "\n";
    }

    // Додавання векторів
    Vector add(const Vector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vector sizes do not match");
        }
        Vector result(size);
        for (size_t i = 0; i < size; ++i) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    // Віднімання векторів
    Vector subtract(const Vector& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Vector sizes do not match");
        }
        Vector result(size);
        for (size_t i = 0; i < size; ++i) {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    // Множення на ціле число
    Vector multiply(unsigned int scalar) const {
        Vector result(size);
        for (size_t i = 0; i < size; ++i) {
            result.data[i] = data[i] * scalar;
        }
        return result;
    }

    // Порівняння: менше
    bool less(const Vector& other) const {
        if (size != other.size) return false;
        for (size_t i = 0; i < size; ++i) {
            if (data[i] >= other.data[i]) return false;
        }
        return true;
    }

    // Порівняння: рівність
    bool equals(const Vector& other) const {
        if (size != other.size) return false;
        for (size_t i = 0; i < size; ++i) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    // Порівняння: нерівність
    bool not_equals(const Vector& other) const {
        return !equals(other);
    }

    // Отримати стан
    int getState() const {
        return state;
    }

    // Лічильник об'єктів
    static int getObjectCount() {
        return count;
    }
};

// Ініціалізація статичної змінної
int Vector::count = 0;

// Головна функція для тестування
int main() {
    Vector v1;
    Vector v2(5);
    Vector v3(5, 7);

    v1.print();
    v2.print();
    v3.print();

    v2.set(2, 10);
    v2.print();

    Vector v4 = v2.add(v3);
    v4.print();

    Vector v5 = v3.multiply(2);
    v5.print();

    std::cout << "Objects created: " << Vector::getObjectCount() << std::endl;

    return 0;
}
