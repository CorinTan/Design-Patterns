#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

enum class AppleColor{
    RED, GREEN
};

enum class AppleShape {
    BIG, MEDIUM, SMALL
};

class Apple {
friend class AppleFactory;

public:
    void getInfo() {
        std::cout << "This " << getShape() << " apple is " << getColor() << std::endl;
    }

    std::string getColor() { return color_str[color]; }
    std::string getShape() { return shape_str[shape]; } 

private:
    Apple() = default;
    AppleColor color;
    AppleShape shape;
    
    static std::unordered_map<AppleColor, std::string> color_str;
    static std::unordered_map<AppleShape, std::string> shape_str;
};

std::unordered_map<AppleColor, std::string> Apple::color_str = {
    {AppleColor::RED, "red"},
    {AppleColor::GREEN, "green"},
};

std::unordered_map<AppleShape, std::string> Apple::shape_str =  {
    {AppleShape::BIG, "big"},
    {AppleShape::MEDIUM, "medium"},
    {AppleShape::SMALL, "small"}, 
};

class AppleFactory {
public:
    std::shared_ptr<Apple> creatApple(AppleColor color, AppleShape shape) {
        // 可以检查传入参数，并进行错误处理等
        std::shared_ptr<Apple> apple_ptr{new Apple};
        apple_ptr->color = color;
        apple_ptr->shape = shape;
        apples.emplace_back(apple_ptr);
        return apple_ptr;
    }

    auto getProducedAppleCount() {
        return apples.size();
    }

    auto getValidAppleCount() {
        auto counter = 0;
        for (auto &weak_ptr : apples)
            if (!weak_ptr.expired())
                ++counter;
        return counter;
    }
    ~AppleFactory() { } 

protected:
    std::vector<std::weak_ptr<Apple>> apples;
};


int main() {
    AppleFactory apple_factory;
    std::shared_ptr<Apple> green_apple = apple_factory.creatApple(AppleColor::GREEN, AppleShape::SMALL);
    {
        std::shared_ptr<Apple> red_apple = apple_factory.creatApple(AppleColor::RED, AppleShape::BIG);
        // check
        green_apple->getInfo(); 
        red_apple->getInfo();
    }
    
    std::cout << "Produced " << apple_factory.getProducedAppleCount() << " apples so far and " 
              << apple_factory.getValidAppleCount() << " is still fresh." << std::endl;
    return 0;
}

