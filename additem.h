#ifndef ADD_ITEM_H
#define ADD_ITEM_H

#include <QDialog>
#include <QItemDelegate>
#include <QTableWidgetItem>
#include <QStandardItem>
#include "qinspectrecipe.h"

namespace Ui
{
class AddItem;
}

class QJudgePatternItemDelegate: public QItemDelegate
{
    Q_OBJECT
public:
    QJudgePatternItemDelegate(QObject *parent = NULL);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setPatternNames(QStringList strPatternNames);
    void setDefectTypes(QStringList strDefectTypes);
    void setDefectColors(QStringList strDefectColors);
    void setConditions(QStringList strConditions);
private:
    QStringList m_strPatternNames;
    QStringList m_strDefectTypes;
    QStringList m_strDefectColors;
    QStringList m_strConditions;
};


class QJudgeConditionItemDelegate: public QItemDelegate
{
    Q_OBJECT
public:
    QJudgeConditionItemDelegate(QObject *parent = NULL);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setFeatures(QStringList strFeatures);
    void setSigns(QStringList strSigns);
    void setConditions(QStringList strConditions);
private:
    QStringList m_strFeatures;
    QStringList m_strSigns;
    QStringList m_strConditions;
};

class AddItem : public QDialog
{
    Q_OBJECT

public:
    explicit AddItem(QWidget *parent = 0);
    ~AddItem();
public:
    bool editClassifyItem(JudgeCondition &judgeCondition);
private:
    void initJudgePatternTable();
    void initJudgeConditionTable();
    void initStringItems();
    void updateJudgePatternTable();
    void updateJudgeConditionTable();
private slots:
    void slt_PatternItemChanged(QStandardItem *item);
    void slt_JudgeItemChanged(QStandardItem *item);
private slots:
    void on_comboBoxReasonName_currentIndexChanged(int index);

    void on_pushButtonAddJudgePatternItem_clicked();

    void on_pushButtonDeleteJudgePatternItem_clicked();

    void on_pushButton_addConditionItem_clicked();

    void on_pushButton_deleteCondition_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_tableViewJudgePattern_clicked(const QModelIndex &index);

    void on_pushButtonCopy_clicked();

private:
    Ui::AddItem *ui;
    QStringList m_strliPatterns;
    QStringList m_strliDefectType;
    QStringList m_strliDefectColor;
    QStringList m_strliCondition;
    QStringList m_strliFeatures;
    QStringList m_strliSign;
    JudgeCondition m_stJudgeCondition;
};

#endif // ADD_ITEM_H
