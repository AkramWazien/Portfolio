#include <iostream>
std::string getName(){
    std::string name;
    std::cout << "Enter your full name: ";
    std::getline(std::cin, name);
    return name;
}

int main(){
    std::string name = getName();
    if(name.length() > 12 || name.length() <= 0){
        std::cout << "Your inserted name is invalid" << std::endl;
    }
    else{
        std::cout << "Welcome " << name;
    }
}