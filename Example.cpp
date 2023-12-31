#include <managed_pointer.h>

#include <iostream>
#include <string>

using namespace std;

class Dog {
    std::string _name;

public:
    Dog(std::string name) : _name(name) { std::cout << _name << " is created" << std::endl; }
    ~Dog() { std::cout << _name << " is destroyed" << std::endl; }
    std::string name() const { return _name; }
};

void print(const std::string& text) { std::cout << "> " << text << std::endl; }

int main() {
    print("Creating Fido");
    auto dog = make_managed<Dog>("Fido");

    print("Replacing Fido with Rover via =");
    dog = make_managed<Dog>("Rover");

    print("Calling release()");
    dog.release();
    print("After release");

    print("Creating Lassie");
    dog = make_managed<Dog>("Lassie");
    print("After creating Lassie");

    print("Calling reset()");
    dog.reset(new Dog("Spot"));
    print("After reset");

    print("Calling reset() with nullptr");
    dog.reset(nullptr);
    print("After reset");

    auto* dogPtr = new Dog("Spike");
    print("Creating Spike");
    dog = managed_ptr<Dog>(dogPtr);
    print("After creating Spike");
    dog.reset();
    print("After reset");

    auto* dogPtr2 = new Dog("Dawg");
    print("Creating Dawg");
    dog = managed_ptr<Dog>(dogPtr2);
    print("After creating Dawg");
    dog.reset();
    print("After reset");

    print("Creating Snoopy");
    dog = make_managed<Dog>("Snoopy");
    dog.disable_delete();
    dog.reset();
    print("After reset");

    // Untyped - can be deleted :)
    print("Creating Scooby");
    auto*               dogPtr3 = new Dog("Scooby");
    untyped_managed_ptr scooby  = new managed_ptr<Dog>(dogPtr3);
    print("After creating Scooby");
    print("Deleting untyped Scooby");
    delete scooby;
    print("After delete");

    print("returning...");
    return 0;
}
