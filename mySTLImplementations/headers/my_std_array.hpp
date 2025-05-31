#include <memory>
#include <typeinfo>
#include <stdexcept>
#include <initializer_list>
template<typename _Ty, std::size_t I>
class my_array{
    private:
        using ref_type = const _Ty&;
        using ptr_type = const _Ty*;
        using val_type = _Ty;

        class iterator{
            private:
                value_type* it;
            public:
                iterator() : it(nullptr){}
                iterator(value_type* el) : it(el){}
                
                constexpr value_type& operator*() const{ return *it;}
                constexpr value_type* operator->() const{ return it;}
                constexpr iterator& operator++(){ it++; return *this;}
                constexpr iterator& operator+=(std::ptrdiff_t n){ it += n; return *this;} 
                constexpr iterator& operator--(){ it--; return *this;}
                constexpr iterator& operator-=(std::ptrdiff_t n){ it -= n; return *this;}
                constexpr bool operator==(const iterator& other) const{ return this->it == other.it ? true : false;}
                constexpr bool operator!=(const iterator& other) const { return it != other.it;}
                constexpr iterator operator+(std::ptrdiff_t n) const { return iterator(it + n);}
                constexpr iterator operator-(std::ptrdiff_t n) const { return iterator(it - n);}
                constexpr std::ptrdiff_t operator-(const iterator& other) const { return it - other.it;}
                constexpr value_type& operator[](std::ptrdiff_t n) const{ return it[n];}
        };

        class const_iterator{
            private:
                const value_type* it;
            public:
                const_iterator() : it(nullptr){}
                const_iterator(value_type* el) : it(el){}
                
                constexpr const value_type& operator*() const{ return *it;}
                constexpr const value_type* operator->() const{ return it;}
                constexpr const_iterator& operator++(){ it++; return *this;}
                constexpr const_iterator& operator+=(std::ptrdiff_t n){ it += n; return *this;} 
                constexpr const_iterator& operator--(){ it--; return *this;}
                constexpr const_iterator& operator-=(std::ptrdiff_t n){ it -= n; return *this;}
                constexpr bool operator==(const iterator& other) const{ return this->it == other.it ? true : false;}
                constexpr bool operator!=(const iterator& other) const { return it != other.it;}
                constexpr const_iterator operator+(std::ptrdiff_t n) const { return const_iterator(it + n);}
                constexpr const_iterator operator-(std::ptrdiff_t n) const { return const_iterator(it - n);}
                constexpr std::ptrdiff_t operator-(const iterator& other) const { return it - other.it;}
                constexpr const value_type& operator[](std::ptrdiff_t n) const{ return it[n];}
        };
        
        value_type buffer[I];
        std::size_t elem_count;
        
    public:
        //constructers
        my_array() : elem_count(0){}

        my_array(const std::initializer_list<value_type>& il){
            if (il.size() > I) throw std::out_of_range("initializer_list is too large for the array");

            std::copy(il.begin(), il.end(),&buffer[0]);
            elem_count = il.size();
        }

        //opertors
        constexpr inline ref_type operator[](std::size_t i) const{
            return buffer[i];
        }

        constexpr inline value_type& operator[](std::size_t i){
            return buffer[i];
        }

        //functions
        constexpr ref_type at(std::size_t i) const{
            if (i >= elem_count){
                throw std::out_of_range("index is out of bounds");
            }
            return buffer[i];
        }

        constexpr value_type& at(std::size_t i){
            if (i >= elem_count){
                throw std::out_of_range("index is out of bounds");
            }
            return buffer[i];
        }

        constexpr ref_type front() const{
            if (elem_count == 0) throw std::out_of_range("front() called on empty my_array");
            return buffer[0];
        }

        constexpr value_type& front(){
            if (elem_count == 0) throw std::out_of_range("front() called on empty my_array");
            return buffer[0];
        }

        constexpr ref_type back() const{
            if (elem_count == 0) throw std::out_of_range("back() called on empty my_array");
            return buffer[elem_count -1];
        }

        constexpr value_type& back(){
            if (elem_count == 0) throw std::out_of_range("back() called on empty my_array");
            return buffer[elem_count -1];
        }
        
        constexpr inline std::size_t capacity() const{
            return I;
        }

        constexpr inline std::size_t size() const{
            return elem_count;
        }
        
        constexpr inline void fill(const value_type& el){
            for (size_t i = 0; i < elem_count; ++i) 
                buffer[i] = el;
        }

        constexpr iterator begin(){
            return iterator(&buffer[0]);
        }

        constexpr iterator end(){
            return iterator(&buffer[elem_count]);
        }

        constexpr const_iterator begin() const{
            return const_iterator(&buffer[0]);
        }

        constexpr const_iterator end() const{
            return const_iterator(&buffer[elem_count]);
        }

    };
