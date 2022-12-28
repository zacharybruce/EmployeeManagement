#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include "addemployee.h"
#include "ui_addemployee.h"

AddEmployee::AddEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEmployee)
{
    ui->setupUi(this);

    connect(ui->pushButton_save, &QPushButton::clicked, this, &AddEmployee::save_employee);
    connect(ui->pushButton_clearform, &QPushButton::clicked, this, &AddEmployee::clear_form);
    connect(ui->pushButton_cancel, &QPushButton::clicked, this, &AddEmployee::close);
}

AddEmployee::~AddEmployee()
{
    delete ui;
}

QPushButton* AddEmployee::get_save_button(){
    return ui->pushButton_save;
}

void AddEmployee::save_employee(){
    // Retrieves employee info from user inputs
    QString firstname = ui->lineEdit_firstname->text();
    QString lastname = ui->lineEdit_lastname->text();
    QString email = ui->lineEdit_email->text();
    QString position = ui->lineEdit_position->text();
    QString supervisor = ui->lineEdit_supervisor->text();
    QString yearsworked = ui->lineEdit_yearsworked->text();
    QString salary = ui->lineEdit_salary->text();

    // Employee must have first name, last name, email, and position title
    if ((firstname == "") || (lastname == "") || (email == "") || (position == "")){
        ui->label_status->setText("Please Fill All Required Fields");
    }

    // Sets yearsworked to NULL if data is empty. Needed for query
    if (yearsworked == ""){
        yearsworked = "NULL";
    }
    // Sets salary to NULL if data is empty. Needed for query
    if (salary == ""){
        salary = "NULL";
    }

    QSqlDatabase db = QSqlDatabase::database("employeesystem");
    QSqlQuery query(db);
    // SQL query to insert new employee into database
    QString statement = "INSERT INTO employee (firstname, lastname, email, position, supervisor, yearsworked, salary) "
                        "VALUES ('" + firstname + "', '" + lastname + "', '" + email + "', '" + position + "', '" +
                        supervisor + "', " + yearsworked + ", " + salary + ')';

    // If query executes successfully, displays message. Else displays error to user
    if (query.exec(statement)){
        ui->label_status->setText("Employee Added Successfully");
    }
    else{
        ui->label_status->setText("Could not save employee");
    }

    if (db.isOpen()){
        db.close();
    }
}

void AddEmployee::clear_form(){
    ui->lineEdit_firstname->clear();
    ui->lineEdit_lastname->clear();
    ui->lineEdit_email->clear();
    ui->lineEdit_position->clear();
    ui->lineEdit_supervisor->clear();
    ui->lineEdit_yearsworked->clear();
    ui->lineEdit_salary->clear();

    ui->label_status->clear();
}
