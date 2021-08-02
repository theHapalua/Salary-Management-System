#include <iostream>
#include <fstream>
#include <cstring>
#include "employee.h"
#include "json.hpp"

#define PRINT_COLOR "\x1b[38;2;255;69;0m"
#define NORMAL_COLOR "\x1b[39;1m"
#define QUESTION_COLOR "\x1b[38;2;183;172;68m"
#define ERROR_COLOR "\x1b[38;2;223;54;45m"

char* delQuote(const char* text){
    int length = std::strlen(text);
    char *cleanText = new char[length-1];
    for(int i = 1;i < length-1;i++){
        cleanText[i-1] = text[i];
    }
    cleanText[length-2] = '\0';
    return cleanText;
}

char* file2text(std::fstream &file){
    file.seekg(0,std::ios_base::end);
    int length = file.tellg();
    file.seekg(0,std::fstream::ios_base::beg);
    char *text = new char[length];
    file.read(text,length);
    return text;
}
int SMS::employeeCount(nlohmann::json JSON){
    int eIndex = 0;
    while(true){
        if(JSON["employees"][eIndex].dump().compare("null") == 0){
            return eIndex;
            break;
        }else{
            eIndex++;
        }
    }
}

int SMS::employeeCount(SMS::Employee *employees){
    int eIndex = 0;
    while(true){
        if(!employees[eIndex].is_exists()){
            return eIndex;
            break;
        }else{
            eIndex++;
        }
    }
}

SMS::Employee::Employee(){
    this->check = 1;
    std::strcpy(this->name,"no name");
    std::strcpy(this->surname, "no surname");
    std::strcpy(this->position, "no position");
    this->age = 0;
    this->salary = 5000;
}

SMS::Employee::Employee(const char *name, const char *surname, const char *position, int age, int salary){
    this->check = 1;
    std::strcpy(this->name, name);
    std::strcpy(this->surname, surname);
    std::strcpy(this->position, position);
    this->age = age;
    this->salary = salary;
}

char* SMS::Employee::getName(){
    return this->name;
}

void SMS::Employee::setName(char* name){
    std::strcpy(this->name, name);
}

char* SMS::Employee::getSurname(){
    return this->surname;
}

void SMS::Employee::setSurname(char* surname){
    std::strcpy(this->surname, surname);
}

char* SMS::Employee::getPosition(){
    return this->position;
}

void SMS::Employee::setPosition(char* position){
    std::strcpy(this->position, position);
}

int SMS::Employee::getAge(){
    return this->age;
}

void SMS::Employee::setAge(int age){
    this->age = age;
}

int SMS::Employee::getSalary(){
    return this->salary;
}

void SMS::Employee::setSalary(int salary){
    this->salary = salary;
}

void SMS::Employee::operator>>(int raisePercent){
    this->salary += raisePercent*(this->salary/100);
}

void SMS::Employee::operator<<(int discountPercent){
    this->salary -= discountPercent*(this->salary/100);
}

bool SMS::Employee::is_exists(){
    if(this->check == 0){
        return false;
    }else{
        return true;
    }
}

void SMS::Employee::printAll(){
    std::cout << PRINT_COLOR << "name : " << NORMAL_COLOR << this->name  << "\n";
    std::cout << PRINT_COLOR << "surname : " << NORMAL_COLOR << this->surname  << "\n";
    std::cout << PRINT_COLOR << "position : " << NORMAL_COLOR << this->position  << "\n";
    std::cout << PRINT_COLOR << "age : " << NORMAL_COLOR << this->age  << "\n";
    std::cout << PRINT_COLOR << "salary : " << NORMAL_COLOR << this->salary  << "\n";
}

void SMS::Employee::fromJson(const char* JsonText){
    nlohmann::json JSON = nlohmann::json::parse(JsonText);
    std::strcpy(this->name,delQuote(JSON["name"].dump().c_str()));
    std::strcpy(this->surname,delQuote(JSON["surname"].dump().c_str()));
    std::strcpy(this->position,delQuote(JSON["position"].dump().c_str()));
    this->age = JSON["age"];
    this->salary = JSON["salary"];
}

nlohmann::json SMS::Employee::toJson(){
   nlohmann::json JSON;
   JSON["name"] = this->name;
   JSON["surname"] = this->surname;
   JSON["position"] = this->position;
   JSON["age"] = this->age;
   JSON["salary"] = this->salary;
   return JSON;
}


SMS::Employee* SMS::makeObjects(const char* filename){
    std::fstream jsonFile;
    jsonFile.open(filename,std::ios_base::in);
    if(!jsonFile.is_open()){
        SMS::Employee* employee = new SMS::Employee();
        return employee;
    }else{
        char *text = file2text(jsonFile);
        nlohmann::json JSON = nlohmann::json::parse(text);
        //for(int i = 0;i < employeeCount())
        SMS::Employee *employees = new SMS::Employee[employeeCount(JSON)];//tmp
        for(int i = 0;i < employeeCount(JSON);i++){
            employees[i] = SMS::Employee();
            employees[i].fromJson(JSON["employees"][i].dump().c_str());
        }
        return employees;//tmp
    }   
}

nlohmann::json SMS::makeJson(SMS::Employee *employees){
    int eCount = employeeCount(employees);
    nlohmann::json JSON;
    for(int i = 0;i < eCount;i++){
        JSON["employees"][i] = employees[i].toJson();
    }
    return JSON;
}