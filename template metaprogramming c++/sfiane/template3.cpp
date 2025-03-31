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

SensorA sensorA{}; 
auto address = getAddress(sensorA); 