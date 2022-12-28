#include <QSqlDatabase>
#include <QSqlQuery>
#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    connect(ui->pushButton_cancel, &QPushButton::clicked, this, &Login::close);
    connect(ui->pushButton_signIn, &QPushButton::clicked, this, &Login::signIn);
}

Login::~Login()
{
    delete ui;
}

void Login::signIn(){
    QSqlDatabase db = QSqlDatabase::database("employeesystem");

    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    QSqlQuery query(db);

    // Checks if login is successful
    if (this->get_login_type() == "Admin"){
        query.exec("SELECT * FROM admin WHERE username='" + username +
                   "' AND password='" + password + '\'');
    }
    else if (this->get_login_type() == "Employee"){
        query.exec("SELECT * FROM user WHERE username='" + username +
                   "' AND password='" + password + '\'');
    }

    int count = 0;
    while(query.next()){
        ++count;
    }

    if (count == 1){
        this->hide();

        if (this->get_login_type() == "Admin"){
            adminpage = new AdminPage(this);
            adminpage->resize(1500, 700);
            adminpage->exec();
        }
        else if (this->get_login_type() == "Employee"){
            employeepage = new EmployeePage(this);
            employeepage->resize(1300, 700);
            employeepage->exec();
        }
    }
    else if (count == 0){
        ui->label_status->setText("username and password are incorrect");
    }
    else{
        ui->label_status->setText("Could not sign in");
    }

    if (db.isOpen()){
        db.close();
    }
}

QString Login::get_login_type(){
    return m_login_type;
}

void Login::set_login_type(QString login_type){
    m_login_type = login_type;
}
