#include "homepage.h"
#include "./ui_homepage.h"
#include "login.h"

HomePage::HomePage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HomePage)
{
    ui->setupUi(this);

    // Datbase set up and connection test
    mydb = QSqlDatabase::addDatabase("QSQLITE", "employeesystem");
    mydb.setDatabaseName("C:/sqlite_dbs/EmployeeManagement/employeesystem.db");
    mydb.open();

    // Displays message if connection to database is successful or unsuccessful
    if (mydb.isOpen()){
        ui->statusbar->showMessage("Connection Successful");
        ui->statusbar->setStyleSheet("background:rgba(0,150,0,255)");
    }
    else{
        ui->statusbar->showMessage("Unable to connect to database");
        ui->statusbar->setStyleSheet("background:rgba(200,0,0,255)");
    }
    mydb.close();

    connect(ui->pushButton_Admin, &QPushButton::clicked, this, &HomePage::login_as_admin);
    connect(ui->pushButton_Employee, &QPushButton::clicked, this, &HomePage::login_as_employee);
}

HomePage::~HomePage()
{
    delete ui;
}

void HomePage::login_as_admin(){
    loginDialog = new Login(this);
    loginDialog->set_login_type("Admin");

    loginDialog->setModal(true);
    loginDialog->resize(600,200);

    loginDialog->exec();
}

void HomePage::login_as_employee(){
    loginDialog = new Login(this);
    loginDialog->set_login_type("Employee");

    loginDialog->setModal(true);
    loginDialog->resize(600,200);

    loginDialog->exec();
}
