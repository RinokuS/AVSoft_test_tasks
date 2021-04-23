#include <string>
#include <vector>

#include "employee.h"

struct enterprise_division {
public:
    std::string name;
    std::vector<employee> staff;

    explicit enterprise_division(const std::string &name) {
        this->name = name;
    }
};
