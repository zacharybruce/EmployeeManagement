#ifndef EMPLOYEEPAGE_H
#define EMPLOYEEPAGE_H

#include <QDialog>
#include <QSqlQueryModel>

/*
Employee user page.
Window is shown if user is logged in as employee.
Displays employees and some info (Everything except salary). Can search employees by first or last name
*/

namespace Ui {
class EmployeePage;
}

class EmployeePage : public QDialog
{
    Q_OBJECT

public:
    explicit EmployeePage(QWidget *parent = nullptr);
    ~EmployeePage();

private slots:
    void search_for_employee(); // Search for employee by first or last name.
                                // Search updates after every letter is entered
    void clear_search(); // Clears search and displays every employee

private:
    Ui::EmployeePage *ui;
    QSqlQueryModel* model;
};

#endif // EMPLOYEEPAGE_H
