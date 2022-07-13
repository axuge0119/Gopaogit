#ifndef ADDGRADE_H
#define ADDGRADE_H

#include <QDialog>

namespace Ui
{
class AddGrade;
}

class AddGrade : public QDialog
{
    Q_OBJECT

public:
    explicit AddGrade(QWidget *parent = 0);
    ~AddGrade();

public slots:
    void on_receiveGradeTableInfo(int index, int tableRowCnt);

signals:
    void sendGradeInfo(int index, double gradeValue);

private slots:
    void on_pushButton_ok_clicked();

private:
    Ui::AddGrade *ui;
    int m_gradeTableIndex;
};

#endif // ADDGRADE_H
