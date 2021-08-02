#include <iostream>
#include <fstream>
#include <cstring>
#include "employee.h"
#include "console.h"

#define PRINT_COLOR "\x1b[38;2;255;69;0m"
#define NORMAL_COLOR "\x1b[39;1m"
#define QUESTION_COLOR "\x1b[38;2;183;172;68m"
#define ERROR_COLOR "\x1b[38;2;223;54;45m"

int spaceCount(const char* text){
    int length = std::strlen(text);
    int spaceNum = 0;
    for(int i = 0;i < length;i++){
        if(text[i] == ' '){
            spaceNum++;
        }
    }
    return spaceNum;
}

void SMS::Console::listAll(SMS::Employee *employees){
    int empNum = SMS::employeeCount(employees);
    for(int i = 0;i < empNum;i++){
        employees[i].printAll();
        std::cout << PRINT_COLOR << "row number : " << NORMAL_COLOR << i+1 << "\n\n";
    }
}

void SMS::Console::listEmp(SMS::Employee *employees){
    int index;
    std::cout  << QUESTION_COLOR << "Enter the row number of employee : " << NORMAL_COLOR;
    std::cin  >> index;
    employees[index].printAll();
}

void SMS::Console::set(SMS::Employee *employees){
    char *properties[] = {"name","surname","position","age","salary"};
    char *property = new char[10];
    int index;
    std::cout << QUESTION_COLOR << "Enter the row number of employee : " << NORMAL_COLOR;
    std::cin >> index;
    index--;
    std::cout << QUESTION_COLOR << "Which property do you want to set? : " << NORMAL_COLOR;
    std::cin >> property;
    int listIndex = 0;
    for(int i = 0;i < 5;i++){
        if(std::strcmp(property,properties[i]) == 0){
            break;
        }else if(i == 4){
            std::cout << ERROR_COLOR << "There is no property as " << property;
            return;
        }else{
            listIndex++;
        }
    }
    if(listIndex == 0){
        std::cout << QUESTION_COLOR << "Enter the new name of employee : " << NORMAL_COLOR;
        char *newName = new char[100];
        std::cin >> newName;
        employees[index].setName(newName);
    }else if(listIndex == 1){
        std::cout << QUESTION_COLOR << "Enter the new surname of employee : " << NORMAL_COLOR;
        char *newSurname = new char[100];
        std::cin >> newSurname;
        employees[index].setSurname(newSurname);
    }else if(listIndex == 2){
        std::cout << QUESTION_COLOR << "Enter the new position of employee : " << NORMAL_COLOR;
        char *newPosition = new char[100];
        std::cin >> newPosition;
        employees[index].setPosition(newPosition);
    }else if(listIndex == 3){
        std::cout << QUESTION_COLOR << "Enter the new age of employee : " << NORMAL_COLOR;
        int newAge;
        std::cin >> newAge;
        employees[index].setAge(newAge);
    }else if(listIndex == 4){
        std::cout << QUESTION_COLOR << "Enter the new salary of employee : " << NORMAL_COLOR;
        int newSalary;
        std::cin >> newSalary;
        employees[index].setSalary(newSalary);
    }else{
        std::cout << ERROR_COLOR << "What the f***?";
    }
}

void SMS::Console::raise(SMS::Employee *employees){
    int index;
    int RPercent;
    std::cout << QUESTION_COLOR << "Enter the row number of employee : " << NORMAL_COLOR;
    std::cin >> index;
    index--;
    std::cout << QUESTION_COLOR << "Enter the raise percent : " << NORMAL_COLOR;
    std::cin  >> RPercent;
    employees[index]>>RPercent;
}

void SMS::Console::discount(SMS::Employee *employees){
    int index;
    int DPercent;
    std::cout << QUESTION_COLOR << "Enter the row number of employee : " << NORMAL_COLOR;
    std::cin >> index;
    index--;
    std::cout << QUESTION_COLOR << "Enter the discount percent : " << NORMAL_COLOR;
    std::cin  >> DPercent;
    employees[index]<<DPercent;
}

void SMS::Console::changeRow(SMS::Employee *employees){
    int index1,index2;
    std::cout << QUESTION_COLOR << "enter the first row : " << NORMAL_COLOR;
    std::cin >> index1;
    index1--;
    std::cout << QUESTION_COLOR << "enter the second row : " << NORMAL_COLOR;
    std::cin >> index2;
    index2--;
    std::cout << "\n\n";
    SMS::Employee temployee(employees[index1].getName(),employees[index1].getSurname(),employees[index1].getPosition(),employees[index1].getAge(),employees[index1].getSalary());
    employees[index1].setName(employees[index2].getName());
    employees[index1].setSurname(employees[index2].getSurname());
    employees[index1].setPosition(employees[index2].getPosition());
    employees[index1].setAge(employees[index2].getAge());
    employees[index1].setSalary(employees[index2].getSalary());

    employees[index2].setName(temployee.getName());
    employees[index2].setSurname(temployee.getSurname());
    employees[index2].setPosition(temployee.getPosition());
    employees[index2].setAge(temployee.getAge());
    employees[index2].setSalary(temployee.getSalary());
}

void SMS::Console::update(SMS::Employee *employees, const char *jsonFile){
    nlohmann::json JSON = SMS::makeJson(employees);
    std::fstream file;
    file.open(jsonFile,std::ios_base::out);
    file.write(JSON.dump().c_str(),JSON.dump().length());
}

void SMS::Console::help(){
    std::cout << PRINT_COLOR << "a temproary help message";
}

void SMS::Console::console(SMS::Employee *employees){
    std::cout << PRINT_COLOR << "Welcome to Salary Management System\n\n" << NORMAL_COLOR;
    //char *commands[] = {"listAll", "listEmp", "set", "raise", "discount", "changeRow", "update", "help", "exit"};
    int exit = 0;
    while(exit == 0){
        char *command = new char[10];
        std::cin >> command;
        if(std::strcmp(command,"listAll")==0){
            SMS::Console::listAll(employees);
        }else if(std::strcmp(command,"listEmp")==0){
            SMS::Console::listEmp(employees);
        }else if(std::strcmp(command,"set")==0){
            SMS::Console::set(employees);
        }else if(std::strcmp(command,"raise")==0){
            SMS::Console::raise(employees);
        }else if(std::strcmp(command,"discount")==0){
            SMS::Console::discount(employees);
        }else if(std::strcmp(command,"changeRow")==0){
            SMS::Console::changeRow(employees);
        }else if(std::strcmp(command,"update")==0){
            SMS::Console::update(employees,"jsn/employees.json");
        }else if(std::strcmp(command,"help")==0){
            SMS::Console::help();
        }else if(std::strcmp(command,"exit")==0){
            exit++;
        }else{
            std::cout << ERROR_COLOR << "wrong command, write help for seeing commands" << NORMAL_COLOR;
        }
    }
}