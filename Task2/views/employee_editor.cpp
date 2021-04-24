#include "employee_editor.h"

employee_editor::employee_editor(QTreeWidget *tree, QTreeWidgetItem *parent_item, bool creation_mode, QWidget *parent): QDialog(parent) {
    this->setWindowModality(Qt::ApplicationModal);
    this->setFixedSize(200, 300);

    this->tree = tree;
    this->parent_item = parent_item;

    this->layout = new QVBoxLayout(this);

    this->surname_le = new QLineEdit(this);
    this->surname_le->setPlaceholderText("Employee's surname...");

    this->name_le = new QLineEdit(this);
    this->name_le->setPlaceholderText("Employee's name...");

    this->middle_name = new QLineEdit(this);
    this->middle_name->setPlaceholderText("Employee's middle_name...");

    this->function = new QLineEdit(this);
    this->function->setPlaceholderText("Employee's function...");

    this->salary = new QLineEdit(this);
    this->salary->setPlaceholderText("Employee's salary...");

    if (creation_mode) {
        this->submit_button = new QPushButton("Create");
        connect(this->submit_button, SIGNAL(clicked()), this, SLOT(create()));
    } else {
        this->submit_button = new QPushButton("Edit");
        connect(this->submit_button, SIGNAL(clicked()), this, SLOT(edit()));
    }

    this->layout->addWidget(this->surname_le);
    this->layout->addWidget(this->name_le);
    this->layout->addWidget(this->middle_name);
    this->layout->addWidget(this->function);
    this->layout->addWidget(this->salary);
    this->layout->addWidget(this->submit_button);

    this->setLayout(this->layout);
}

employee_editor::~employee_editor() {
    delete this->surname_le;
    delete this->name_le;
    delete this->middle_name;
    delete this->function;
    delete this->salary;
    delete this->submit_button;

    delete this->layout;
}

void employee_editor::create() {
    bool is_salary_numeric;
    double sal = this->salary->text().toDouble(&is_salary_numeric); // checking if salary input is numeric

    if (this->surname_le->text().isEmpty() || this->name_le->text().isEmpty() ||
            this->middle_name->text().isEmpty() || this->function->text().isEmpty() ||
            this->salary->text().isEmpty()) {
        QMessageBox::critical(this, "Error", "Employee's info can't be empty!");
    } else if (!is_salary_numeric) {
        QMessageBox::critical(this, "Error", "Employee's salary should be a number!");
    } else {
        int last_div_staff_count = parent_item->text(1).toInt();
        double last_div_sum_salary = parent_item->text(2).toDouble() * last_div_staff_count;

        auto temp = new QTreeWidgetItem(); // creating employee node
        temp->setText(0, this->surname_le->text());
        temp->setText(1, this->name_le->text());
        temp->setText(2, this->middle_name->text());
        temp->setText(3, this->function->text());
        temp->setText(4, this->salary->text());

        this->parent_item->addChild(temp); // adding node to his department
        // change departments characteristics (staff number and mean salary)
        this->parent_item->setText(1, QString::number(last_div_staff_count + 1));
        this->parent_item->setText(2,
                                   QString::number((last_div_sum_salary + sal) / (last_div_staff_count + 1)));

        this->close();
    }
}

void employee_editor::edit() {
    bool is_salary_numeric;
    double sal = this->salary->text().toDouble(&is_salary_numeric);

    if (this->surname_le->text().isEmpty() || this->name_le->text().isEmpty() ||
        this->middle_name->text().isEmpty() || this->function->text().isEmpty() ||
        this->salary->text().isEmpty()) {
        QMessageBox::critical(this, "Error", "Employee's info can't be empty!");
    } else if (!is_salary_numeric) {
        QMessageBox::critical(this, "Error", "Employee's salary should be a number!");
    } else {
        int div_staff_count = parent_item->text(1).toInt();
        double last_div_sum_salary = parent_item->text(2).toDouble() * div_staff_count;

        auto temp = tree->selectedItems()[0]; // getting our selected employee
        double last_sal = temp->text(4).toDouble();

        temp->setText(0, this->surname_le->text());
        temp->setText(1, this->name_le->text());
        temp->setText(2, this->middle_name->text());
        temp->setText(3, this->function->text());
        temp->setText(4, this->salary->text());

        // change departments characteristics (mean salary)
        this->parent_item->setText(2,
                                   QString::number((last_div_sum_salary - last_sal + sal) / div_staff_count));

        this->close();
    }
}
