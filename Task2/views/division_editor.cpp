#include "division_editor.h"

division_editor::division_editor(QTreeWidget *tree, bool creation_mode, QWidget *parent): QDialog(parent) {
    this->setWindowModality(Qt::ApplicationModal);
    this->setFixedSize(200, 100);

    this->tree = tree;

    this->layout = new QVBoxLayout(this);

    this->name_le = new QLineEdit(this);
    this->name_le->setPlaceholderText("Division name...");

    if (creation_mode) {
        this->submit_button = new QPushButton("Create");
        connect(this->submit_button, SIGNAL(clicked()), this, SLOT(create()));
    } else {
        this->submit_button = new QPushButton("Edit");
        connect(this->submit_button, SIGNAL(clicked()), this, SLOT(edit()));
    }

    this->layout->addWidget(this->name_le);
    this->layout->addWidget(this->submit_button);

    this->setLayout(this->layout);
}

division_editor::~division_editor() {
    delete this->name_le;
    delete this->submit_button;

    delete this->layout;
}

void division_editor::create() {
    if (this->name_le->text().isEmpty()) {
        QMessageBox::critical(this, "Error", "Division name can't be empty!");
    } else {
        auto temp = new QTreeWidgetItem(); // creating department node
        temp->setText(0, this->name_le->text());
        temp->setText(1, "0");
        temp->setText(2, "0");

        tree->addTopLevelItem(temp); // adding department to the table

        this->close();
    }
}

void division_editor::edit() {
    if (this->name_le->text().isEmpty()) {
        QMessageBox::critical(this, "Error", "Division name can't be empty!");
    } else {
        auto temp = tree->selectedItems()[0]; // getting selected department node
        temp->setText(0, this->name_le->text());

        this->close();
    }
}