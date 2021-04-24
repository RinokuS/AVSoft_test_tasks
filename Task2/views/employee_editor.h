#include <QtWidgets>

class employee_editor: public QDialog {
Q_OBJECT

private:
    QTreeWidgetItem *parent_item;
    QTreeWidget *tree;

    QVBoxLayout *layout;
    QLineEdit *surname_le, *name_le, *middle_name, *function, *salary;
    QPushButton *submit_button;
private slots:
    void create();
    void edit();
public:
    /*
     * Added creation_mode flag to switch between creation and editing simply
     */
    explicit employee_editor(QTreeWidget *tree, QTreeWidgetItem *parent_item,
                             bool creation_mode = false, QWidget *parent = nullptr);
    ~employee_editor() override;
};
