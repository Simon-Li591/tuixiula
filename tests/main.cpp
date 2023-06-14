#include <iostream>
#include <mthread/demo1.h>
#include <fanshe/Singleton.hpp>
#include <fmt/core.h>

// 所有类的基类
class Object
{
public:
    Object() {}
    virtual ~Object() {}

    void SetClassName(const std::string &name) { class_name_ = name; }
    std::string GetClassName() const { return class_name_; }

protected:
    std::string class_name_;
};

class Panel : public Object
{
public:
    Panel() {}
    ~Panel() {}
};



int main(int argc, char const *argv[])
{
    demo1();
    REGISTERPANELCLASS(Panel)
    auto panel = (Object *)ObjectFactory::GetInstance()->CreateObject("Panel");
    std::shared_ptr<Object> ptr(panel);
    auto name = ptr->GetClassName();
    std::cout << name.c_str() << std::endl;
    log("yes");


    fmt::print("new fmt lib use in {}", "today");
    // 
    int a, b;
    while(std::cin >> a >> b) {
        std::cout << a + b << std::endl;
    }
    std::cin.get();

    return 0;
}
