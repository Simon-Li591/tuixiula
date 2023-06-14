#include <mthread/demo1.h>

void foo() {
    std::cout << "Hello C++11" << std::endl;
}

void demo1(){
    std::thread thread(foo);  // 启动线程foo

    thread.join();  // 等待线程执行完成
}