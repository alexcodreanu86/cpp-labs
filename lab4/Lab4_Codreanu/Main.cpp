#import <iostream>

#import "MapHash.h"

typedef MapHash<std::string, int> container;
typedef void (* action)(container &, std::string);

void printMenu(container &, std::string input) {
    std::cout << "Commands:\n";
    std::cout << "[Add]       To add name with age to container\n";
    std::cout << "[IsEmpty]   Check if container is empty\n";
    std::cout << "[MakeEmpty] Empty container\n";
    std::cout << "[Get]       Get person age\n";
    std::cout << "[Help]      Print this menu\n";
    std::cout << "[EXIT]      To exit the program\n";
}

void addToContainer(container &c, std::string input) {
    std::string name;
    int age;

    std::cout << "Insert name: ";
    std::cin >> name;
    std::cout << "\nInsert age: ";
    std::cin >> age;

    while (age < 0) {
        std::cout << "\nAge must be positive! Please insert age again: ";
        std::cin >> age;
    }

    if (c.put(name, age)) {
        std::cout << "\nAdded " << name << " with age " << age << '\n';
    } else {
        std::cout << "\nWe already have an age record for " << name << '\n';
    }
}

void isContainerEmpty(container &c, std::string) {
    if (c.isEmpty()) {
        std::cout << "Container is empty!\n";
    } else {
        std::cout << "Container is NOT empty!\n";
    }
}

void makeEmpty(container &c, std::string input) {
    c.makeEmpty();
    std::cout << "Removed container contents!\n";
}

void getPersonAge(container &c, std::string) {
    std::string name;
    std::cout << "Insert the name you want to get the age for: ";
    std::cin >> name;
    const int age = c.get(name);
    if (age == -1) {
        std::cout << "\nWe don't know " << name << "'s age\n";
    } else {
        std::cout << '\n' << name << "'s age is " << age << '\n';
    }
}

void invalidAction(container & c, std::string input) {
    std::cout << "\"" << input << "\" is an invalid command!!!\n";

    printMenu(c, input);
}

int main() {
    MapHash<std::string, action> actions(invalidAction);
    actions.put("Help", printMenu);
    actions.put("Add", addToContainer);
    actions.put("IsEmpty", isContainerEmpty);
    actions.put("MakeEmpty", makeEmpty);
    actions.put("MakeEmpty", makeEmpty);
    actions.put("Get", getPersonAge);

    MapHash<std::string, int> map(-1);

    std::string c = "Help";
    std::cout << "We have a container that stores names with their age\n";
    std::cout << "We store the names and ages in a HashMap but this menu is also driven by a HashMap\n";

    while(c != "EXIT") {
        action a =  actions.get(c);
        a(map, c);
        std::cout << "Please insert your next command: ";
        std::cin >> c;
        std::cout << '\n';
    }

    std::cout << "We hope you enjoyed using our little program.\n";
    std::cout << "Good Bye!!!\n";
    std::cout << "\033[0;32m√ All tests have passed!!!\n\033[m";

}