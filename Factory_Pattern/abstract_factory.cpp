#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

#include "products.hpp"

class Factory {
public:
    virtual std::shared_ptr<CellPhone> creatCellPhone() = 0;
    virtual std::shared_ptr<Mask> creatMask() = 0;

    auto getProducedCellPhonesCount() {
        return cellphones_created.size();
    }

    auto getProducedMasksCount() {
        return masks_created.size();
    }

    auto getCellPhoneCountInUse() {
        auto counter = 0;
        for (auto &weak_ptr : cellphones_created)
            if (!weak_ptr.expired())
                ++counter;
        return counter;
    }

    auto getMaskCountInUse() {
        auto counter = 0;
        for (auto &weak_ptr : masks_created)
            if (!weak_ptr.expired())
                ++counter;
        return counter;
    }

protected:
    std::vector<std::weak_ptr<CellPhone>> cellphones_created;
    std::vector<std::weak_ptr<Mask>> masks_created;
};

class USA_Factory : public Factory{
public:
    virtual std::shared_ptr<CellPhone> creatCellPhone() override {
        auto cellphone_ptr = std::make_shared<IPhone>();
        cellphones_created.emplace_back(cellphone_ptr);
        return cellphone_ptr;
    }

    virtual std::shared_ptr<Mask> creatMask() override {
        auto mask_ptr = std::make_shared<N95>();
        masks_created.emplace_back(mask_ptr);
        return mask_ptr;
    }
};

class CN_Factory : public Factory{
public:
    virtual std::shared_ptr<CellPhone> creatCellPhone() override {
        auto cellphone_ptr = std::make_shared<Huawei>();
        cellphones_created.emplace_back(cellphone_ptr);
        return cellphone_ptr;
    }

    virtual std::shared_ptr<Mask> creatMask() override {
        auto mask_ptr = std::make_shared<KN90>();
        masks_created.emplace_back(mask_ptr);
        return mask_ptr;
    }
};

int main() {
    std::unique_ptr<Factory> factory1 = std::make_unique<USA_Factory>();
    auto iphone = factory1->creatCellPhone();
    {
        auto n90 = factory1->creatMask();
        // check:
        iphone->getInfo();
        n90->getInfo();
    }
    std::unique_ptr<Factory> factory2 = std::make_unique<CN_Factory>(); 
    auto kn90 = factory2->creatMask();
    {
        auto huawei = factory2->creatCellPhone();
        // check:
        huawei->getInfo();
        kn90->getInfo(); 
    }

    std::cout << "Factory1 produced " << factory1->getProducedCellPhonesCount() << " cellphones so far and " 
              << factory1->getCellPhoneCountInUse() << " is still in use." << std::endl;
    std::cout << "Factory1 produced " << factory1->getProducedMasksCount() << " masks so far and " 
              << factory1->getMaskCountInUse() << " is still in use." << std::endl;

    std::cout << "Factory2 produced " << factory2->getProducedCellPhonesCount() << " cellphones so far and " 
              << factory2->getCellPhoneCountInUse() << " is still in use." << std::endl;
    std::cout << "Factory2 produced " << factory2->getProducedMasksCount() << " masks so far and " 
              << factory2->getMaskCountInUse() << " is still in use." << std::endl;
    return 0;
}

