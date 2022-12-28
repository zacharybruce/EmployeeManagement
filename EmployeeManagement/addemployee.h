#ifndef ADDEMPLOYEE_H
#define ADDEMPLOYEE_H

#include <QDialog>

/*
Add Employee Page.
Window prompts the user to input new employee info.
User can then save employee, cancel and exit page, or clear fields to re-input
*/

namespace Ui {
class AddEmployee;
}

class AddEmployee : public QDialog
{
    Q_OBJECT

public:
    explicit AddEmployee(QWidget *parent = nullptr);
    ~AddEmployee();

    QPushButton* get_save_button(); // Returns save button when pressed



private slots:
    void save_employee(); // Saves employee and displays it on admin page
    void clear_form(); // Clears form if button is pressed

private:
    Ui::AddEmployee *ui;
};

#endif // ADDEMPLOYEE_H
