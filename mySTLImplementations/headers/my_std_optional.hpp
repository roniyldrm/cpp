#include <memory>
#include <typeinfo>
#include <stdexcept>
template<typename _Ty>
class my_optional{
    private:
        using val_type = _Ty;
        using c_ref_type = const _Ty&;

        bool has_value;
        alignas(val_type) char buffer[sizeof(val_type)];

        //constructers
        my_optional() = delete;
        
        template<typename...Types>
        my_optional(Types&&...args) : has_value(true){
            new (&buffer[0]) val_type{ std::forward<Types>(args)...};
        }

        my_optional(val_type&& o) : has_value(true){
            new (&buffer[0]) val_type{ std:forward<val_type>(o)};
        }

        //~my_optional(){}
        
    public:

        //operators
        constexpr bool operator bool(){ return has_value;}
        
        constexpr val_type&& operator*() const{ 
            if (!this->has_value){
                throw std::logic_error("")
            } 
            return static_cast<val_type&&>(buffer[0]);
        }

        constexpr val_type* operator->() const{
            if (!this->has_value){
                throw std::logic_error("")
            }
            return static_cast<val_type*>(&buffer[0]);
        }

        constexpr my_optional& operator=(val_type&& o) const{
            if(!this->has_value){
                new (&buffer[0]) val_type{ std:forward<val_type>(o)};//i thought it as 1 time initialized only 
                                                                    //should be changed via swap() ???
            }
        }


        //functions
        constexpr _construct

        template<typename...Types>
        constexpr val_type& emplace(Types&&...Args) const{
            
        }

        constexpr bool has_value() const{ return has_value;}

        constexpr void reset(){
            if(this->has_value){
              this->has_value = false;  
            } 
        }

        constexpr my_optional& swap(val_type&& o){
            //?? dont know what it could be used for 
        }







};