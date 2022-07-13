#include "addgrade.h"
#include "ui_addgrade.h"

AddGrade::AddGrade(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddGrade)
{
    ui->setupUi(this);
}

AddGrade::~AddGrade()
{
    delete ui;
}

void AddGrade::on_pushButton_ok_clicked()
{
    double gradeValue = ui->lineEdit_gradeValue->text().toDouble();
    emit sendGradeInfo(m_gradeTableIndex, gradeValue);

    this->accept();
}


void AddGrade::on_receiveGradeTableInfo(int index, int tableRowCnt)
{
    if (index == 0)
        ui->label_gradeValue->setText("Number: ");
    else if (index == 1)
        ui->label_gradeValue->setText("Area: ");

    m_gradeTableIndex = index;
    ui->lineEdit_grade->setText(QString("%1").arg(tableRowCnt));
}
