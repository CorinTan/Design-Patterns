#include <iostream>

// 1. 饿汉式
class Singleton1 {
public:
    Singleton1(const Singleton1 &) = delete;
    Singleton1 &operator=(const Singleton1 &) = delete;
    Singleton1(Singleton1 &&) = delete;
    Singleton1 &operator=(Singleton1 &&) = delete;

    static Singleton1 &getInstance() {
        return instance_;
    }

    void test() {
        std::cout << "Singleton1 test." << std::endl;
    }

    ~Singleton1() {
        delete &instance_;
    }
private:
    Singleton1() = default;
    static Singleton1 &instance_;
};

Singleton1 &Singleton1::instance_ = *(new Singleton1);


// 2. 懒汉式
class Singleton2 {
public:
    Singleton2(const Singleton2 &) = delete;
    Singleton2 &operator=(const Singleton2 &) = delete;
    Singleton2(Singleton2 &&) = delete;
    Singleton2 &operator=(Singleton2 &&) = delete;

    void test() {
        std::cout << "Singleton2 test." << std::endl;
    }

    static Singleton2 &getInstance() {
        static Singleton2 instance;
        return instance;
    }

    ~Singleton2() = default;

private:
    Singleton2() = default;
};

// test
int main() {
    Singleton1 &s1 = Singleton1::getInstance();
    Singleton2 &s2 = Singleton2::getInstance();

    s1.test();
    s2.test();

    return 0;
}