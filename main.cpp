#include <iostream>

#include "src/employee.h"
#include "src/console.h"
#include "src/json.hpp"



int main(){
    SMS::Employee *employees = SMS::makeObjects("jsn/employees.json");
    SMS::Console::console(employees);
    return 0;
}