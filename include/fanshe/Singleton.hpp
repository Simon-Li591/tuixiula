#include <functional>
#include <unordered_map>

template <typename T>
class Singleton
{
    using object_type = T;

public:
    static object_type *GetInstance()
    {
        static object_type instance_;
        return &instance_;
    }

public:
    struct object_creater
    {
        object_creater() { Singleton<T>::GetInstance(); }
    };

    static object_creater creater;
};

template <typename T>
typename Singleton<T>::object_creater Singleton<T>::creater;

using CreateObjectFunc = std::function<void *()>;

struct CreateObjectFuncClass
{
    // 构造函数
    explicit CreateObjectFuncClass(CreateObjectFunc func) : create_func(func) {}
    // 函数指针
    CreateObjectFunc create_func;
};

// objectFactory
class ObjectFactory : public Singleton<ObjectFactory>
{
public:
    void *CreateObject(const std::string &class_name)
    {
        CreateObjectFunc create_obj = nullptr;

        if (create_funcs_map_.find(class_name) != create_funcs_map_.end())
            create_obj = create_funcs_map_.find(class_name)->second->create_func;

        if (create_obj == nullptr)
            return nullptr;

        // 调用函数指针指向的函数 调用REGISTER_CLASS中宏的绑定函数，也就是运行new className代码
        return create_obj();
    }

    void RegisterObject(const std::string &class_name, CreateObjectFunc func)
    {
        auto it = create_funcs_map_.find(class_name);
        if (it != create_funcs_map_.end())
            create_funcs_map_[class_name]->create_func = func;
        else
            create_funcs_map_.insert(std::pair<std::string, CreateObjectFuncClass *>{class_name, new CreateObjectFuncClass(func)});
    }

    ~ObjectFactory()
    {
        for (auto it : create_funcs_map_)
        {
            if (it.second != nullptr)
            {
                delete it.second;
                it.second = nullptr;
            }
        }
        create_funcs_map_.clear();
    }

private:
    std::unordered_map<std::string, CreateObjectFuncClass *> create_funcs_map_;
};

#define REGISTERPANELCLASS(className)                                     \
    class className##PanelHelper                                          \
    {                                                                     \
    public:                                                               \
        className##PanelHelper()                                          \
        {                                                                 \
            ObjectFactory::GetInstance()->RegisterObject(#className, []() \
                                                         { \
            auto* obj = new className(); \
            obj->SetClassName(#className); \
            return obj; });            \
        }                                                                 \
    };                                                                    \
    className##PanelHelper g_##className##_panelhelper; // 初始化一个helper的全局变量，执行构造函数中的RegisterObject执行。