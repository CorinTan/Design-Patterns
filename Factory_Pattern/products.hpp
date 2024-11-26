#include <iostream>
#include <string>



class CellPhone{
public:
    CellPhone(): name{""}, type{"CellPhone"} { }
    virtual void getInfo() = 0;

protected:    
    std::string type;

private:
    std::string name;
};

class Mask{
public:
    Mask(): name{""}, type{"Mask"} { }
    virtual void getInfo() = 0;

protected:    
    std::string type;

private:
    std::string name;
};

class IPhone : public CellPhone {
public:
    IPhone(): CellPhone(), name{"IPhone"} { }
    virtual void getInfo() override {
        std::cout << "This is a " << type << " : " << name << std::endl;
    }

private:
    std::string name;
};

class Huawei : public CellPhone {
public:
    Huawei(): CellPhone(), name{"Huawei"} { }
    virtual void getInfo() override {
        std::cout << "This is a " << type << " : " << name << std::endl;
    }

private:
    std::string name;
};

class N95 : public Mask {
public:
    N95(): Mask(), name{"N95"} { }
    virtual void getInfo() override {
        std::cout << "This is a " << type << " : " << name << std::endl;
    }

private:
    std::string name;
};

class KN90 : public Mask {
public:
    KN90(): Mask(), name{"KN90"} { }
    virtual void getInfo() override {
        std::cout << "This is a " << type << " : " << name << std::endl;
    }

private:
    std::string name;
};