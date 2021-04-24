#include <QtWidgets>

class division_editor: public QDialog {
Q_OBJECT

private:
    QTreeWidget *tree;

    QVBoxLayout *layout;
    QLineEdit *name_le;
    QPushButton *submit_button;
private slots:
    void create();
    void edit();

public:
    /*
     * Added creation_mode flag to switch between creation and editing simply
     */
    explicit division_editor(QTreeWidget *tree, bool creation_mode = false, QWidget *parent = nullptr);
    ~division_editor() override;
};
