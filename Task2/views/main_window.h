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
    QTreeWidget *last_tree;
    QVBoxLayout *layout;

    QMenuBar* create_menu();
    void tree_deep_copy();

private slots:
    void import();
    void add_division();
    void add_employee();
    void edit();
    void remove();
    void cancel_last_changes();

public:
    explicit main_window(QWidget *parent = nullptr);
    ~main_window() override;
};