#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QItemSelectionModel>
#include <QComboBox>
#include <QMessageBox>
#include "adminpage.h"
#include "ui_adminpage.h"
#include "addemployee.h"

AdminPage::AdminPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminPage)
{
    ui->setupUi(this);

    // Sends employee data to table view at startup of window
    QSqlDatabase db = QSqlDatabase::database("employeesystem");

    if (db.open()){
        QSqlTableModel* model = new QSqlTableModel(this, db);
        model->setTable("employee");
        model->select();
        ui->tableView_employees->setModel(model);
    }

    // User can search by first or last name
    QStringList search_by = {"First Name", "Last Name"};
    ui->comboBox_searchBy->addItems(search_by);

    connect(ui->pushButton_clear, &QPushButton::clicked, this, &AdminPage::show_all_data);
    connect(ui->pushButton_addEmployee, &QPushButton::clicked, this, &AdminPage::add_employee);
    connect(ui->pushButton_deleteEmployee, &QPushButton::clicked, this, &AdminPage::delete_employee);

    // Search results update as text is added or deleted by user
    connect(ui->lineEdit_nameSearch, &QLineEdit::textEdited, this, &AdminPage::search_for_employee);
    // Search is updated if user changes search by combo box
    connect(ui->comboBox_searchBy, &QComboBox::currentTextChanged, this, &AdminPage::search_for_employee);
}

AdminPage::~AdminPage()
{
    delete ui;
}

void AdminPage::search_for_employee(){
    QString name = ui->lineEdit_nameSearch->text();
    QSqlDatabase db = QSqlDatabase::database("employeesystem");

    model = new QSqlQueryModel;

    // Retrieves user data from employee table of database
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

void AdminPage::show_all_data(){
    QSqlDatabase db = QSqlDatabase::database("employeesystem");

    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM employee", db);
    ui->tableView_employees->setModel(model);

    if (db.isOpen()){
        db.close();
    }

    ui->lineEdit_nameSearch->clear();
}

void AdminPage::add_employee(){
    addemployee = new AddEmployee(this);
    connect(addemployee->get_save_button(), &QPushButton::clicked, this, &AdminPage::show_all_data);
    addemployee->setModal(true);
    addemployee->exec();
}

void AdminPage::delete_employee(){
    QItemSelectionModel* select = ui->tableView_employees->selectionModel();
    QModelIndexList rows = select->selectedRows(0); // Get employee id from all selected rows
    QString id;

    // If not employee is selected, display message box
    if (rows.size() == 0){
        QMessageBox::information(this, "Error", "Please select at least one employee to delete");
        return;
    }

    int msgbox = QMessageBox::question(this, "Confirmation", "Are you sure you want to delete employee?");

    // Confirm deletion of employee with message box
    switch (msgbox){
        case QMessageBox::Yes:
        {
            QSqlDatabase db = QSqlDatabase::database("employeesystem");
            QSqlQuery query(db);

            // Deletes every selected employee from database
            for (int i=0; i < rows.size(); ++i){
                id = rows[i].data().toString();
                query.exec("DELETE FROM employee WHERE id=" + id);
            }

            if (db.isOpen()){
                db.close();
            }

            show_all_data();
        }

        case QMessageBox::No:
            return;
    }
}

