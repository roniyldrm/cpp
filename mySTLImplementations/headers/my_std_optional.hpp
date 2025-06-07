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
        
        template<typename T>
        my_optional(T&& o) : has_value(true){
            new (&buffer[0]) val_type{ std:forward<T>(o)};
        }

        template<typename...Types>
        my_optional(Types&&...args) : has_value(true){
            new (&buffer[0]) val_type{ std::forward<Types>(args)...};
        }
        
    public:
        
        //operators
        constexpr bool operator bool(){ return has_value;}
        
        constexpr val_type& operator*() &{ 
            if (!this->has_value){
                throw std::logic_error("")
            } 
            return *std::launder(reinterpret_cast<val_type&>(buffer[0]));
            //? i used launder to safely inform compiler that a new object was constructed via placement new 
            //? returns pointer to the same type you give it,
            //? but with the guarantee that the compiler knows a new object was created at that memory address.
            
        }

        constexpr val_type&& operator*() && {}
        constexpr const val_type& operator*() const &{}
        constexpr const val_type&& operator*() const &&{}
        //TODO implement all operators for each optional type lv ,rv, const lv, const rv

        constexpr val_type* operator->(); &{
            if (!this->has_value){
                throw std::logic_error("")
            }
            return std::launder(reinterpret_cast<val_type*>(&buffer[0]));
        }

        // constexpr val_type* operator->() &&{}
        // constexpr const val_type* operator->() const &{}
        // constexpr const val_type* operator->() const &&{}


        template<typename T>
        constexpr my_optional& operator=(T&& o) const{
            if(!this->has_value){
                new (&buffer[0]) val_type{ std:forward<T>(o)};//i thought it as 1 time initialized only 
                                                                    //should be changed via swap() ???
            }
        }

        template<typename...Types>
        constexpr my_optional& operator=(Types&&...Args) const{
            if(!this->has_value){
                new (&buffer[0]) val_type{ std::forward<Types>(Args)...};
            }
        }



        //functions
        template<typename...Types>
        constexpr val_type& emplace(Types&&...Args) const{
            new (&buffer[0]) val_type{ std::forward<Types>(Args)...};
        }

        constexpr bool has_value() const{ return has_value;}

        constexpr void reset(){
            if(this->has_value){
              this->has_value = false;  
            } 
        }

        template<typename T>
        constexpr void swap(T&& o){
            val_type copy = this->operator*();
            if constexpr (is_same_v<T::val_type,val_type>){
                new (&buffer[0]) val_type{ *(std::forward<T>(o))};
                new (&t.buffer[0]) val_type{*(std::move(copy))};
            }

        }


};