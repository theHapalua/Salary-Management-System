#ifndef CONSOLE
#define CONSOLE

#include <iostream>
#include "employee.h"

namespace SMS{
    namespace Console{
        void listAll(SMS::Employee *employees);
        void listEmp(SMS::Employee *employees);
        void set(SMS::Employee *employees);
        void raise(SMS::Employee *employees);
        void discount(SMS::Employee *employees);
        void changeRow(SMS::Employee *employees);
        void add(SMS::Employee *employees);
        void remove(SMS::Employee *employees);
        void update(SMS::Employee *employees, const char *jsonFile);
        void help();
        void console(SMS::Employee *employees);
    }
}

#endif