#include <string>
#include <vector>

#include <QXmlStreamReader>
#include <QFile>

#include "enterprise_division.h"

class xml_reader {
private:
    QFile *file;
    QXmlStreamReader *xml;
public:
    explicit xml_reader(const QString &file_path) {
        this->file = new QFile(file_path);

        if (!file->open(QIODevice::ReadOnly | QIODevice::Text));

        this->xml = new QXmlStreamReader(this->file);
    }

    ~xml_reader() {
        delete file;
        delete xml;
    }

    std::vector<enterprise_division> read_xml() {
        std::vector<enterprise_division> divisions;

        while (!xml->atEnd()) {
            xml->readNext();

            if (xml->name().toString() == "department" && xml->tokenString() == "StartElement") {
                if (!xml->attributes().empty() && xml->attributes()[0].name().toString() == "name")
                    divisions.emplace_back(xml->attributes()[0].value().toString().toStdString());
                else;
            } else if (xml->name().toString() == "employment" && xml->tokenString() == "StartElement") {
                std::string surname, name, mn, function;
                unsigned int salary;
                int att_counter = 0;

                while (true) {
                    xml->readNext();
                    if (att_counter == 5)
                        break; // stop iteration if we have all 5 attributes

                    if (xml->tokenString() == "StartElement") {
                        QString n = xml->name().toString();
                        xml->readNext();
                        std::string value = xml->text().toString().toStdString();

                        if (n == "surname") {
                            surname = value;
                        } else if (n == "name") {
                            name = value;
                        } else if (n == "middleName") {
                            mn = value;
                        } else if (n == "function") {
                            function = value;
                        } else if (n == "salary") {
                            salary = std::stoi(value);
                        }
                        att_counter++;
                    }
                }

                divisions[divisions.size() - 1].staff.emplace_back(surname, name, mn, function, salary);
            }
        }

        return divisions;
    }
};