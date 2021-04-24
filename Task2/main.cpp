#include <QApplication>

#include "xml_reader.h"
#include "views/main_window.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    auto main_v = main_window();
    main_v.show();

    return QApplication::exec();
}
