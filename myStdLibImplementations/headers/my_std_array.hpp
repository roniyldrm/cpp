#include <memory>
#include <typeinfo>
#include <initializer_list>
template<typename _Ty, std::size_t I>
class my_array{
    private:
        using ref_type = const _Ty&;
        using ptr_type = const _Ty*;
        using value_type = _Ty;
        using max_count = I;

        class iterator{
            private:
                value_type* it;
            public:
                iterator();
                iterator(ptr_type el);
                
                constexpr value_type& operator*() const;
                constexpr value_type* operator->() const;
                constexpr iterator& operator++() ;
                constexpr iterator& operator+=() ; 
                constexpr iterator& operator--() ; 
                constexpr iterator& operator-=() ; 
                constexpr bool operator==(const iterator& other) const;
                constexpr value_type& operator[](const iterator& other) const; 
        };
        
        value_type buffer[max_count];
        std::size_t elem_count;
        
    public:
    //constructers
        my_array();
        my_array(const std::initializer_list<value_type>& il);

    //opertors
        constexpr ref_type operator[](std::size_t i) const;
        constexpr ptr_type operator bool() const;

    //functions
        constexpr ref_type at(std::size_t i);
        constexpr ref_type front();
        constexpr ref_type back();

        constexpr inline max_count capacity() const;
        constexpr std::size_t size() const;

        constexpr void fill(const value_type& el);
        //!constexpr void fill(value_type&& el);//forward each el
        constexpr my_array::iterator begin() ;
        constexpr my_array::iterator end();
};
