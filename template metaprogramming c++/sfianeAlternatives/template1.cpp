

template<typename T>
bool areEqual(T a, T b) {
    return (a == b);
}


static_assert(areEqual(5,5),"not equal");