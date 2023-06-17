#pragma once

namespace muduo {

    // 之所以设置成protected，意味着该类无法产生对象，而只能派生子类

    class copyable {
        protected:
        copyable() = default;
        ~copyable() = default;
    };

}