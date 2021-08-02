#ifndef EMPLOYEE
#define EMPLOYEE

#include "json.hpp"
namespace SMS{
  class Employee{
    private:
      char name[100];
      char surname[100];
      char position[100];
      int age;
      int salary;//dollar (monthly)
      int check =  0;
    public:
      Employee();
      Employee(const char *name, const char *surname, const char *position, const int age, const int salary);
      char* getName();
      void setName(char* name);
      char* getSurname();
      void setSurname(char* surname);
      char* getPosition();
      void setPosition(char* position);
      int getAge();
      void setAge(int age);
      int getSalary();
      void setSalary(int salary);
      void operator >> (int raisePercent);
      void operator << (int discountPercent);
      bool is_exists();
      void fromJson(const char* JsonText);
      void printAll();
      nlohmann::json toJson();
      
  };
  int employeeCount(nlohmann::json JSON);
  int employeeCount(SMS::Employee *employees);
  Employee* makeObjects(const char* filename);
  nlohmann::json makeJson(Employee *employees);
}
#endif
