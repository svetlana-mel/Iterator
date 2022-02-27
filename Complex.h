#ifndef COMPLEX
#define COMPLEX

class Complex {
public:
    explicit Complex(double real, double imaginary = 0)
        : real_(real), imaginary_(imaginary) {}
    explicit Complex()
        : real_(0), imaginary_(0) {}

    // перегрузки оператора " + " через методы и дружественные функции
    friend const Complex operator+ (const Complex& c1, const Complex& c2);
    friend const Complex operator+ (const Complex& c1, double d);
    friend const Complex operator+ (double d, const Complex& c2);

    // перегрузки оператора " += "
    Complex operator+= (Complex& other) {
        real_ = real_ + other.real_;
        imaginary_ = imaginary_ + other.imaginary_;
        return *this;
    }
    Complex operator+= (double a) {
        real_ = real_ + a;
        return *this;
    }

    // перегрузка оператора " << "
    friend std::ostream& operator<< (std::ostream& os, const Complex& c);

    // перегрузка оператора "++" префикс
    Complex& operator++() {
        ++real_;
        return *this;
    }

    // перегрузка оператора "++" постфикс
    const Complex operator++(int) {
        Complex temp = *this;
        ++(*this);
        return temp;
    }
private:
    double real_, imaginary_;
};

const Complex operator+ (const Complex& c1, const Complex& c2) {
    return Complex(c1.real_ + c2.real_, c1.imaginary_ + c2.imaginary_);
}
const Complex operator+ (const Complex& c1, double d) {
    return Complex(c1.real_ + d, c1.imaginary_);
}
const Complex operator+ (double d, const Complex& c2) {
    return Complex(d + c2.real_, c2.imaginary_);
}

std::ostream& operator<< (std::ostream& os, const Complex& c) {
    os << "(" << c.real_ << "," << c.imaginary_ << ")";
    return os;
}

#endif