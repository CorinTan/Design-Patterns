#include <iostream>
#include <string>
#include <memory>

void printLn(const std::string &msg) {
    std::cout << msg << std::endl;
}

class House {
friend class HouseBuilder;
public:
    void getMaterial() {
        printLn("The house is made of " + material);
    }

    void setMaterial(const std::string &mat) {
       material = mat;
    }

private:
    House() = default;
    std::string material;
};

class HouseBuilder {
public:
    HouseBuilder() : house_ptr(new House) { }
    House *build() {
        build1();
        build2();
        build3();
        build4();
        return house_ptr;
    }

    virtual ~HouseBuilder() { }
protected:
    House *house_ptr;

private:
    virtual void build1() = 0;
    virtual void build2() = 0;
    virtual void build3() = 0;
    virtual void build4() = 0;
};

class StoneHouseBuilder : public HouseBuilder {
public:
    StoneHouseBuilder() = default;
private:
    virtual void build1() override {
        printLn("StoneHouse build1");
        house_ptr->setMaterial("Stone");
    }
    virtual void build2() override {
       printLn("StoneHouse build2"); 
    }
    virtual void build3() override {
       printLn("StoneHouse build3"); 
    }
    virtual void build4()  override {
       printLn("StoneHouse build4"); 
    }
};

class WoodHouseBuilder : public HouseBuilder {
public:
    WoodHouseBuilder() = default;
private:
    virtual void build1() override {
        printLn("WoodHouse build1");
        house_ptr->setMaterial("Wood");
    }
    virtual void build2() override {
       printLn("WoodHouse build2"); 
    }
    virtual void build3() override {
       printLn("WoodHouse build3"); 
    }
    virtual void build4()  override {
       printLn("WoodHouse build4"); 
    }
};

int main() {
    std::unique_ptr<House> stone_house(StoneHouseBuilder().build());
    std::unique_ptr<House> wood_house(WoodHouseBuilder().build());

    // check
    stone_house->getMaterial();
    wood_house->getMaterial();
    
    return 0;
}