template<typename T>
struct is_class {
private:
    template<typename C>
    static char test(int C::*);  // works only if C is a class type

    template<typename C>
    static int test();        // fallback for non-class types

public:
    static constexpr bool value = sizeof(test<T>(0)) == sizeof(char);
};

/*
    🔧 Explanation
    int C::* is a pointer-to-member type.

    This expression is valid only if C is a class or union.

    So the first overload of test() is chosen if T is a class.

    If not, the substitution fails, and SFINAE makes the compiler fall back to the second version.
*/
/*
    struct MyClass {
        void hello() { std::cout << "Hello!\n"; }
    };

    void (MyClass::* funcPtr)() = &MyClass::hello;

    MyClass obj;
    (obj.*funcPtr)();  // calls obj.hello()
*/

/*
    C::* — Pointer-to-member syntax
    C::* is the type of a pointer to a member (either a member variable or a member function) of class C.

    ?It is not a pointer to an object, but a pointer to a member within an object of type C.
---------
    struct MyClass {
    int x;
    };

    int MyClass::* ptr = &MyClass::x;  // pointer to member variable
    
    ?int MyClass::* is a pointer-to-member-of-MyClass that points to an int.
    --------
*/
