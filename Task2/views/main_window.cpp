#include <iostream>

#include "main_window.h"
#include "division_editor.h"
#include "employee_editor.h"

#include "../xml_reader.h"

main_window::main_window(QWidget *parent) : QMainWindow(parent) {
    this->layout = new QVBoxLayout();

    this->menu = create_menu();
    this->layout->addWidget(this->menu);
    this->menu->show();

    this->tree = new QTreeWidget();
    this->tree->setColumnCount(5);
    this->tree->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    connect(this->tree, &QTreeWidget::itemDoubleClicked, this, &main_window::on_tree_item_double_clicked);
    layout->addWidget(this->tree);

    this->central_widget = new QWidget();
    this->central_widget->setLayout(layout);
    this->setCentralWidget(this->central_widget);
}

main_window::~main_window() {
    delete this->tree;
    delete this->menu;

    delete this->layout;
    delete this->central_widget;
}
/*
 * Creating menu-bar
 */
QMenuBar* main_window::create_menu() {
    auto created_menu = new QMenuBar();
    // file tab
    auto file_menu = created_menu->addMenu(tr("File"));
    auto import_act = new QAction(tr("Import"), this);
    import_act->setShortcut(Qt::CTRL + Qt::Key_I);
    import_act->setStatusTip(tr("Import tree from .xml file"));
    connect(import_act, &QAction::triggered, this, &main_window::import);
    file_menu->addAction(import_act);
    // table editing tab
    auto edit_menu = created_menu->addMenu(tr("Edit"));
    auto add_division_act = new QAction(tr("Add Division"), this);
    add_division_act->setShortcut(Qt::CTRL + Qt::ALT + Qt::Key_D);
    add_division_act->setStatusTip(tr("Add new division node"));
    connect(add_division_act, &QAction::triggered, this, &main_window::add_division);

    auto add_employee_act = new QAction(tr("Add Employee"), this);
    add_employee_act->setShortcut(Qt::CTRL + Qt::ALT + Qt::Key_E);
    add_employee_act->setStatusTip(tr("Add new employee node to selected division"));
    connect(add_employee_act, &QAction::triggered, this, &main_window::add_employee);

    auto edit_act = new QAction(tr("Edit"), this);
    edit_act->setShortcut(Qt::CTRL + Qt::Key_E);
    edit_act->setStatusTip(tr("Remove selected node"));
    connect(edit_act, &QAction::triggered, this, &main_window::edit);

    auto remove_act = new QAction(tr("Remove"), this);
    remove_act->setShortcut(Qt::CTRL + Qt::Key_D);
    remove_act->setStatusTip(tr("Remove selected node"));
    connect(remove_act, &QAction::triggered, this, &main_window::remove);

    edit_menu->addAction(add_division_act);
    edit_menu->addAction(add_employee_act);
    edit_menu->addSeparator();
    edit_menu->addAction(edit_act);
    edit_menu->addSeparator();
    edit_menu->addAction(remove_act);

    created_menu->addMenu(file_menu);
    created_menu->addMenu(edit_menu);

    return created_menu;
}
/*
 * Some trash-coding
 * I was too lazy to decompose this method, because its components used only here
 */
void main_window::import() {
    QStringList file_names;
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("XML files (*.xml)"));
    dialog.setViewMode(QFileDialog::Detail);
    if (dialog.exec())
        file_names = dialog.selectedFiles();

    for (const auto &file: file_names) { // we can choose several .xml files
        xml_reader xr(file);
        auto res = xr.read_xml(); // reading xml

        for (const auto &div: res) {
            auto temp = new QTreeWidgetItem(); // creating department node
            double sum_salary = 0;
            temp->setText(0, QString::fromStdString(div.name));

            for (const auto &employee: div.staff) {
                auto temp_emp = new QTreeWidgetItem(); // creating employee node

                sum_salary += employee.salary;
                temp_emp->setText(0, QString::fromStdString(employee.surname));
                temp_emp->setText(1, QString::fromStdString(employee.name));
                temp_emp->setText(2, QString::fromStdString(employee.middle_name));
                temp_emp->setText(3, QString::fromStdString(employee.function));
                temp_emp->setText(4, QString::number(employee.salary));

                temp->addChild(temp_emp); // adding employee to his department
            }

            temp->setText(1, QString::number(div.staff.size()));
            temp->setText(2, QString::number(sum_salary / div.staff.size()));

            tree->addTopLevelItem(temp); // adding department to the table
        }
    }
}

void main_window::add_division() {
    division_editor dc(this->tree, true, this);
    dc.exec();
    dc.show();
}

void main_window::add_employee() {
    if (!this->tree->selectedItems().isEmpty() && this->tree->selectedItems()[0]->parent() == nullptr) {
        employee_editor ec(this->tree, this->tree->selectedItems()[0],
                           true, this);
        ec.exec();
        ec.show();
    } else {
        QMessageBox::critical(this, "Error", "Select division to add employee!");
    }
}

void main_window::edit() {
    if (!this->tree->selectedItems().isEmpty()) {
        if (this->tree->selectedItems()[0]->parent() == nullptr) {
            division_editor dc(this->tree, false, this);
            dc.exec();
            dc.show();
        } else {
            employee_editor ec(this->tree, this->tree->selectedItems()[0]->parent(),
                               false, this);
            ec.exec();
            ec.show();
        }
    } else {
        QMessageBox::critical(this, "Error", "Select node to edit!");
    }
}

void main_window::remove() {
    if (!this->tree->selectedItems().isEmpty()) {
        if (this->tree->selectedItems()[0]->parent()) {
            double sal = this->tree->selectedItems()[0]->text(4).toDouble();

            auto parent = this->tree->selectedItems()[0]->parent();
            int last_div_staff_count = parent->text(1).toInt();
            double last_div_sum_salary = parent->text(2).toDouble() * last_div_staff_count;

            parent->setText(1, QString::number(last_div_staff_count - 1));
            QString mean_sal = last_div_staff_count == 1 ? "0" : // evading zero division
                    QString::number((last_div_sum_salary - sal) / (last_div_staff_count - 1));
            parent->setText(2, mean_sal);
        }

        auto temp = this->tree->selectedItems()[0];
        delete temp;
    } else {
        QMessageBox::critical(this, "Error", "Select node to delete!");
    }
}

void main_window::on_tree_item_double_clicked(QTreeWidgetItem *item, int column) {
    this->tree->editItem(item, column);
}
