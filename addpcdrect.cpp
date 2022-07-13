#include "addpcdrect.h"
#include "ui_addpcdrect.h"

AddPcdRect::AddPcdRect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPcdRect)
{
    ui->setupUi(this);
}

AddPcdRect::~AddPcdRect()
{
    delete ui;
}

void AddPcdRect::on_pushButton_clicked()
{
    int x = ui->lineEdit_pcdLineX->text().toInt();
    int y = ui->lineEdit_pcdLineY->text().toInt();
    int width = ui->lineEdit_pcdLineWidth->text().toInt();
    int height = ui->lineEdit_pcdLineHeight->text().toInt();

    emit sendPcdRectInfo(x, y, width, height);

    this->accept();
}
