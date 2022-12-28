#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QComboBox>
#include "employeepage.h"
#include "ui_employeepage.h"

EmployeePage::EmployeePage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeePage)
{
    ui->setupUi(this);

    // Shows all employees at startup of window
    QSqlDatabase db = QSqlDatabase::database("employeesystem");

    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM employee", db);
    ui->tableView_employees->setModel(model);

    if (db.isOpen()){
        db.close();
    }

    // Can search by first or last name
    QStringList search_by = {"First Name", "Last Name"};
    ui->comboBox_searchBy->insertItems(0, search_by);

    connect(ui->lineEdit_nameSearch, &QLineEdit::textEdited, this, &EmployeePage::search_for_employee);
    connect(ui->pushButton_clear, &QPushButton::clicked, this, &EmployeePage::clear_search);
    // Updates search if search by combo box is changed
    connect(ui->comboBox_searchBy, &QComboBox::currentTextChanged, this, &EmployeePage::search_for_employee);
}

EmployeePage::~EmployeePage()
{
    delete ui;
}

void EmployeePage::search_for_employee(){
    QString name = ui->lineEdit_nameSearch->text();
    QSqlDatabase db = QSqlDatabase::database("employeesystem");

    model = new QSqlQueryModel;

    if (ui->comboBox_searchBy->currentText() == "First Name"){
        model->setQuery("SELECT * FROM employee WHERE firstname like '%" + name + "%'", db);
        ui->tableView_employees->setModel(model);
    }
    else if (ui->comboBox_searchBy->currentText() == "Last Name"){
        model->setQuery("SELECT * FROM employee WHERE lastname like '%" + name + "%'", db);
        ui->tableView_employees->setModel(model);
    }

    if (db.isOpen()){
        db.close();
    }
}

void EmployeePage::clear_search(){
    QSqlDatabase db = QSqlDatabase::database("employeesystem");

    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM employee", db);
    ui->tableView_employees->setModel(model);

    if (db.isOpen()){
        db.close();
    }

    ui->lineEdit_nameSearch->clear();
}
