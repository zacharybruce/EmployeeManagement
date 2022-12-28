#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QDialog>
#include <QSqlQueryModel>
#include "addemployee.h"

/*
Admin user page.
Window is shown if user is logged in as Admin.
Displays employees and all info. Can search employees by first or last name
Can add or delete employee from database
*/

namespace Ui {
class AdminPage;
}

class AdminPage : public QDialog
{
    Q_OBJECT

public:
    explicit AdminPage(QWidget *parent = nullptr);
    ~AdminPage();

public slots:
    void show_all_data(); // Clears search and shows all employees

private slots:
    void search_for_employee(); // User enters name. Search results update as text in entered in
    void add_employee(); // Displays add employee window when user clicks add employee button
    void delete_employee(); // Deletes selected employee. Row on table view must be highlighted

private:
    Ui::AdminPage *ui;
    AddEmployee* addemployee;
    QSqlQueryModel* model;
};

#endif // ADMINPAGE_H
