
struct robotX{
    static int Bullets;
    void shootBullets(){ }
};
struct roboty{
    static int Missiles;
    void shootMissiles(){ }
};


template<typename Robot> 
void handleEnemies (Robot& r, decltype(Robot::Bullets)* = nullptr) { 
    r.shootBullets(); 
} 

//if robot has member missiles but not bullets or vice versa compiler will try to declare a type of them in parameter 
//and if it cant find the missiles member it will not give an error if robot has bullets type

template<typename Robot> 
void handleEnemies (Robot& r, decltype(Robot::Missiles)* = nullptr) { 
    r.shootMissiles(); 
}

/*
second parameter is just a type-checking mechanism,also nullptr is for you to dont have to pass nullptr explicitly
robot's that have missiles member will use 2. function and ones that have bullets will use 1. one
*/