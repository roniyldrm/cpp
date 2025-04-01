struct SensorA { 
    struct IpV4 { int address{}; }; 
    IpV4 ipV4{}; 
}; 

/*
    template<typename S>
    auto getAddress(S& sensor) -> decltype(sensor.ipV4) { 
        return sensor.ipV4;
    }

    template<typename S>
    auto getAddress(S& sensor) -> decltype(sensor.ipV6) { 
        return sensor.ipV6; 
    }
    could also used this rather than typename  
*/
/*
    and the reason you cant use decltype directly is

        template<typename S>
        decltype(sensor.ipV4) getAddress(S& sensor) { 
            return sensor.ipV4;
        }

    The issue here is that sensor does not exist at the point where the function signature is being parsed.

    Problem: decltype(sensor.ipV4) tries to access sensor before it's declared.

    Solution: We use trailing return type syntax (auto ... -> decltype(...)) 
        because in this form, sensor is already declared when decltype(sensor.ipV4) is evaluated.


    decltype can only be used on existing variables
*/

template<typename S> 
typename S::IpV4 getAddress (S& sensor) { 
    return sensor.ipV4; 
} 

template<typename S> 
typename S::IpV6 getAddress (S& sensor) { //
    return sensor.ipV6; 
} 

/*
Yes, exactly! If you write T::something, the compiler treats something as a dependent name because its meaning depends on T, which is a template parameter. Until the template is instantiated with a concrete type, the compiler does not know what T::something refers to.

What Does the Compiler Assume?
When the compiler sees T::something, it does not assume that:

T::something is a type → You must explicitly say typename T::something.

S is unknown and S::ipv6 could be a type,static variable because of ipv6 depends on S its a dependent name and
you should use typename if its a type before using it 
*/



SensorA sensorA{}; 
auto address = getAddress(sensorA); 