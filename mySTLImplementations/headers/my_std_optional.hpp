#include <memory>
#include <typeinfo>
#include <stdexcept>
template<typename _Ty>
class my_optional{
    private:
        using val_type = _Ty;
        
        alignas(val_type) char buffer[sizeof(val_type)];
        bool initialized;

        my_optional() : initialized()

    public:
};