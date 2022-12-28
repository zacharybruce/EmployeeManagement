#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "employeepage.h"
#include "adminpage.h"

/*
Home page.
Displays welcome message and allows user
to sign in as employee or admin.
*/

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    // getters
    QString get_login_type();

    // setters
    void set_login_type(QString login_type);

private slots:
    void signIn();

private:
    Ui::Login *ui;
    EmployeePage* employeepage;
    AdminPage* adminpage;

    QString m_login_type; // Can be "Admin" or "Employee" depending on who is signing in
};

#endif // LOGIN_H
