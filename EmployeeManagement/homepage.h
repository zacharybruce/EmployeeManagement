#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "login.h"

/*
Home page.
Displays welcome message and allows user
to sign in as employee or admin.
*/

QT_BEGIN_NAMESPACE
namespace Ui { class HomePage; }
QT_END_NAMESPACE

class HomePage : public QMainWindow
{
    Q_OBJECT

public:
    HomePage(QWidget *parent = nullptr);
    ~HomePage();

private slots:
    // Can login as admin or employee
    void login_as_admin();
    void login_as_employee();

private:
    Ui::HomePage *ui;
    Login* loginDialog; // Creates login instance to set login type
    QSqlDatabase mydb;
};
#endif // HOMEPAGE_H
