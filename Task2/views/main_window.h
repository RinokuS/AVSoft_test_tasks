#include <QtWidgets>

class QTreeWidget;
class QVBoxLayout;
class QPushButton;

class main_window: public QMainWindow {
Q_OBJECT

private:
    QWidget *central_widget;

    QMenuBar *menu;
    QTreeWidget *tree;
    QVBoxLayout *layout;

    QMenuBar* create_menu();
    void on_tree_item_double_clicked(QTreeWidgetItem *item, int column);

private slots:
    void import();
    void add_division();
    void add_employee();
    void edit();
    void remove();

public:
    explicit main_window(QWidget *parent = nullptr);
    ~main_window() override;
};