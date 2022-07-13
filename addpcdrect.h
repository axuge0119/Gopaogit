#ifndef ADDPCDRECT_H
#define ADDPCDRECT_H

#include <QDialog>

namespace Ui
{
class AddPcdRect;
}

class AddPcdRect : public QDialog
{
    Q_OBJECT

public:
    explicit AddPcdRect(QWidget *parent = 0);
    ~AddPcdRect();

signals:
    void sendPcdRectInfo(int x, int y, int width, int height);

private slots:
    void on_pushButton_clicked();

private:
    Ui::AddPcdRect *ui;
};

#endif // ADDPCDRECT_H
