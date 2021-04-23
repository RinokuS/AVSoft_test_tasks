#include <string>

struct employee {
public:
    std::string surname;
    std::string name;
    std::string middle_name;
    std::string function;
    unsigned int salary;

    employee(const std::string &surname, const std::string &name, const std::string &mn,
             const std::string &function, unsigned int salary) {
        this->surname = surname;
        this->name = name;
        this->middle_name = mn;
        this->function = function;
        this->salary = salary;
    }
};
