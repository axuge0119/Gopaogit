#include "additem.h"
#include "ui_additem.h"
#include <algorithm>
#include <QDoubleSpinBox>
#include "judgereasoneditdlg.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMessageBox>
#include "qinspectsettings.h"

AddItem::AddItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddItem)
{
    ui->setupUi(this);
    initStringItems();
    QVector<JudgeReason> vecJudgeReasons = JudgeReasonEditDlg::getJudgeReasons();
    ui->comboBoxReasonName->clear();
    for (int i = 0; i < vecJudgeReasons.size(); i++) {
        ui->comboBoxReasonName->addItem(vecJudgeReasons[i].strName, QVariant::fromValue(vecJudgeReasons[i]));
    }
    QInspectSettings *setting = QInspectSettings::getInstance();
    m_strliPatterns = setting->GetPatternList();
    ui->comboBox_itemGrade->clear();
    ui->comboBox_itemGrade->addItems(setting->GetGradeList());
    initJudgePatternTable();
    initJudgeConditionTable();
}

AddItem::~AddItem()
{
    delete ui;
}

bool AddItem::editClassifyItem(JudgeCondition &judgeCondition)
{
    m_stJudgeCondition = judgeCondition;
    ui->comboBoxReasonName->setCurrentIndex(ui->comboBoxReasonName->findText(m_stJudgeCondition.stJudgeReason.strName));
    ui->comboBox_itembUsed->setCurrentIndex(m_stJudgeCondition.bEnable);
    ui->comboBox_itemPriority->setCurrentIndex(m_stJudgeCondition.nPriority + 1);
    ui->comboBox_itemGrade->setCurrentText(m_stJudgeCondition.strGrade);
    updateJudgePatternTable();
    updateJudgeConditionTable();
    if (exec()) {
        judgeCondition = m_stJudgeCondition;
        return true;
    } else {
        return false;
    }
}

void AddItem::initJudgePatternTable()
{
    QStandardItemModel *model = new QStandardItemModel(ui->tableViewJudgePattern);
    QStringList strHeader;
    strHeader << "画面";
    strHeader << "缺陷类别";
    strHeader << "缺陷颜色";
    strHeader << "逻辑条件";
    model->setHorizontalHeaderLabels(strHeader);
    ui->tableViewJudgePattern->setModel(model);
    QJudgePatternItemDelegate *delegate = new QJudgePatternItemDelegate(ui->tableViewJudgePattern);

    delegate->setPatternNames(m_strliPatterns);

    delegate->setDefectTypes(m_strliDefectType);
    delegate->setDefectColors(m_strliDefectColor);
    delegate->setConditions(m_strliCondition);
    ui->tableViewJudgePattern->setItemDelegate(delegate);
}

void AddItem::initJudgeConditionTable()
{
    QStandardItemModel *model = new QStandardItemModel(ui->tableViewConditions);
    QStringList strHeader;
    strHeader << "特征量";
    strHeader << "判定条件";
    strHeader << "判断值";
    strHeader << "逻辑条件";
    model->setHorizontalHeaderLabels(strHeader);
    ui->tableViewConditions->setModel(model);
    QJudgeConditionItemDelegate *delegate = new QJudgeConditionItemDelegate(ui->tableViewConditions);
    delegate->setFeatures(m_strliFeatures);
    delegate->setSigns(m_strliSign);
    delegate->setConditions(m_strliCondition);
    ui->tableViewConditions->setItemDelegate(delegate);
}

void AddItem::initStringItems()
{
    m_strliDefectType << "Point";
    m_strliDefectType << "LineX";
    m_strliDefectType << "LineY";
    m_strliDefectType << "Mura";
    m_strliDefectType << "Spot";
    m_strliDefectType << "Crack";
    m_strliDefectType << "Smudge";
    m_strliDefectType << "Crush";
    m_strliDefectType << "Scratch";
    m_strliDefectType << "Bump";

    m_strliDefectColor << "Bright";
    m_strliDefectColor << "Dark";
    m_strliDefectColor << "Color";
    m_strliDefectColor << "Any";

    m_strliSign << "=";
    m_strliSign << "!=";
    m_strliSign << ">";
    m_strliSign << "<";
    m_strliSign << "≥";
    m_strliSign << "≤";

    m_strliCondition << "And";
    m_strliCondition << "Or";
    m_strliCondition << "Not";

    //m_strliFeatures << "DefectArea";
    //m_strliFeatures << "BoxArea";
    //m_strliFeatures << "BoxRatio";
    //m_strliFeatures << "SumGV";
    //m_strliFeatures << "MinGV";
    //m_strliFeatures << "MaxGV";
    //m_strliFeatures << "MeanGV";
    //m_strliFeatures << "DiffGV";
    //m_strliFeatures << "BK_GV";
    //m_strliFeatures << "STD_GV";
    //m_strliFeatures << "SEMU";
    //m_strliFeatures << "COMPACTNEES";
    //m_strliFeatures << "MinGV_Ratio";
    //m_strliFeatures << "MaxGV_Ratio";
    //m_strliFeatures << "MeanGV_Ratio";
    //m_strliFeatures << "Perimeter";
    //m_strliFeatures << "Roundness";
    //m_strliFeatures << "Elongation";
    //m_strliFeatures << "Width";
    //m_strliFeatures << "Height";
    //m_strliFeatures << "MinBoxArea";

	m_strliFeatures << "面积";
	m_strliFeatures << "长度";
	m_strliFeatures << "宽度";
	m_strliFeatures << "长宽比";
	m_strliFeatures << "灰度差";
	m_strliFeatures << "最大灰度";
	m_strliFeatures << "平均灰度";
	m_strliFeatures << "最小灰度";
	m_strliFeatures << "总灰度";
	m_strliFeatures << "背景灰度";
	m_strliFeatures << "外接矩形面积";
	m_strliFeatures << "外接矩形比率";
	m_strliFeatures << "标准差";
	m_strliFeatures << "JNCD";
	m_strliFeatures << "周长";
	m_strliFeatures << "圆度";
	m_strliFeatures << "紧凑度";
	m_strliFeatures << "长轴";
	m_strliFeatures << "短轴";
	m_strliFeatures << "轴比率";
	m_strliFeatures << "最小灰度比率";
	m_strliFeatures << "最大灰度比率";
	m_strliFeatures << "灰度差比率";
	m_strliFeatures << "最小外接矩形面积";
	m_strliFeatures << "最小外接矩形比率";
}

void AddItem::updateJudgePatternTable()
{
    QStandardItemModel *model = (QStandardItemModel *)ui->tableViewJudgePattern->model();
    model->setRowCount(m_stJudgeCondition.vecJudgePattern.size());
    for (int i = 0; i < m_stJudgeCondition.vecJudgePattern.size(); i++) {
        model->setItem(i, 0, new QStandardItem(m_stJudgeCondition.vecJudgePattern[i].strPattern));
        model->item(i, 0)->setCheckable(true);
        if (m_stJudgeCondition.vecJudgePattern[i].bEnable) {
            model->item(i, 0)->setCheckState(Qt::Checked);
        } else {
            model->item(i, 0)->setCheckState(Qt::Unchecked);
        }
        model->setItem(i, 1, new QStandardItem(m_strliDefectType[m_stJudgeCondition.vecJudgePattern[i].eDefectType]));
        model->setItem(i, 2, new QStandardItem(m_strliDefectColor[m_stJudgeCondition.vecJudgePattern[i].eDefectColor]));
        model->setItem(i, 3, new QStandardItem(m_strliCondition[m_stJudgeCondition.vecJudgePattern[i].eCondition]));
    }
    connect(model, &QStandardItemModel::itemChanged, this, &AddItem::slt_PatternItemChanged);
}

void AddItem::updateJudgeConditionTable()
{
    QStandardItemModel *model = (QStandardItemModel *)ui->tableViewConditions->model();
    disconnect(model, &QStandardItemModel::itemChanged, this, &AddItem::slt_JudgeItemChanged);
    int idx = ui->tableViewJudgePattern->currentIndex().row();
    if (idx >= 0) {
        model->setRowCount(m_stJudgeCondition.vecJudgePattern[idx].vecJudgement.size());
        for (int i = 0; i < m_stJudgeCondition.vecJudgePattern[idx].vecJudgement.size(); i++) {
            model->setItem(i, 0, new QStandardItem(m_strliFeatures[m_stJudgeCondition.vecJudgePattern[idx].vecJudgement[i].eFeature]));
            model->item(i, 0)->setCheckable(true);
            if (m_stJudgeCondition.vecJudgePattern[idx].vecJudgement[i].bEnable) {
                model->item(i, 0)->setCheckState(Qt::Checked);
            } else {
                model->item(i, 0)->setCheckState(Qt::Unchecked);
            }
            model->setItem(i, 1, new QStandardItem(m_strliSign[m_stJudgeCondition.vecJudgePattern[idx].vecJudgement[i].eSign]));
            model->setItem(i, 2, new QStandardItem(QString::number(m_stJudgeCondition.vecJudgePattern[idx].vecJudgement[i].dValue)));
            model->setItem(i, 3, new QStandardItem(m_strliCondition[m_stJudgeCondition.vecJudgePattern[idx].vecJudgement[i].eCondition]));
        }
    }
    connect(model, &QStandardItemModel::itemChanged, this, &AddItem::slt_JudgeItemChanged);
}

void AddItem::slt_PatternItemChanged(QStandardItem *item)
{
    QModelIndex index = item->index();
    int id = index.row();
    int col = index.column();
    if (id >= 0) {
        if (col == 0) {
            m_stJudgeCondition.vecJudgePattern[id].strPattern =  item->text();
            m_stJudgeCondition.vecJudgePattern[id].bEnable =  item->checkState() == Qt::Checked;
        } else if (col == 1) {
            m_stJudgeCondition.vecJudgePattern[id].eDefectType = (DefectType)m_strliDefectType.indexOf(item->text());
        } else if (col == 2) {
            m_stJudgeCondition.vecJudgePattern[id].eDefectColor = (DefectColor)m_strliDefectColor.indexOf(item->text());
        } else if (col == 3) {
            m_stJudgeCondition.vecJudgePattern[id].eCondition = (ENUM_CONDITION)m_strliCondition.indexOf(item->text());
        }
    }
}

void AddItem::slt_JudgeItemChanged(QStandardItem *item)
{
    int idx = ui->tableViewJudgePattern->currentIndex().row();
    if (idx >= 0) {
        QModelIndex index = item->index();
        int id = index.row();
        int col = index.column();
        if (id >= 0) {
            if (col == 0) {
                m_stJudgeCondition.vecJudgePattern[idx].vecJudgement[id].eFeature = (ENUM_DEFECT_FEATURE)m_strliFeatures.indexOf(item->text());
                m_stJudgeCondition.vecJudgePattern[idx].vecJudgement[id].bEnable =  item->checkState() == Qt::Checked;
            } else if (col == 1) {
                m_stJudgeCondition.vecJudgePattern[idx].vecJudgement[id].eSign = (ENUM_SIGN_OF_INEQUALITY)m_strliSign.indexOf(item->text());
            } else if (col == 2) {
                m_stJudgeCondition.vecJudgePattern[idx].vecJudgement[id].dValue = item->text().toDouble();
            } else if (col == 3) {
                m_stJudgeCondition.vecJudgePattern[idx].vecJudgement[id].eCondition = (ENUM_CONDITION)m_strliCondition.indexOf(item->text());
            }
        }
    }
}



void AddItem::on_comboBoxReasonName_currentIndexChanged(int index)
{
    JudgeReason reason = ui->comboBoxReasonName->currentData().value<JudgeReason>();
    ui->lineEdit_itemCode->setText(reason.strCode);
}



QJudgePatternItemDelegate::QJudgePatternItemDelegate(QObject *parent): QItemDelegate(parent)
{

}

QWidget *QJudgePatternItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 0) {
        QComboBox *editor = new QComboBox(parent);
        editor->addItems(m_strPatternNames);
        return editor;
    } else if (index.column() == 1) {
        QComboBox *editor = new QComboBox(parent);
        editor->addItems(m_strDefectTypes);
        return editor;
    } else if (index.column() == 2) {
        QComboBox *editor = new QComboBox(parent);
        editor->addItems(m_strDefectColors);
        return editor;
    } else if (index.column() == 3) {
        QComboBox *editor = new QComboBox(parent);
        editor->addItems(m_strConditions);
        return editor;
    } else {
        return NULL;
    }
}

void QJudgePatternItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //if(index.column() == 1)
    {
        QComboBox *comboBox = static_cast<QComboBox *>(editor);
        QString str = index.model()->data(index, Qt::EditRole).toString();
        comboBox->setCurrentIndex(comboBox->findText(str));
    }
}

void QJudgePatternItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    //if(index.column() == 1)
    {
        QComboBox *comboBox = static_cast<QComboBox *>(editor);
        model->setData(index, comboBox->currentText(), Qt::EditRole);
    }
}

void QJudgePatternItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void QJudgePatternItemDelegate::setPatternNames(QStringList strPatternNames)
{
    m_strPatternNames = strPatternNames;
}

void QJudgePatternItemDelegate::setDefectTypes(QStringList strDefectTypes)
{
    m_strDefectTypes = strDefectTypes;
}

void QJudgePatternItemDelegate::setDefectColors(QStringList strDefectColors)
{
    m_strDefectColors = strDefectColors;
}

void QJudgePatternItemDelegate::setConditions(QStringList strConditions)
{
    m_strConditions = strConditions;
}

QJudgeConditionItemDelegate::QJudgeConditionItemDelegate(QObject *parent): QItemDelegate(parent)
{

}

QWidget *QJudgeConditionItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 0) {
        QComboBox *editor = new QComboBox(parent);
        editor->addItems(m_strFeatures);
        return editor;
    } else if (index.column() == 1) {
        QComboBox *editor = new QComboBox(parent);
        editor->addItems(m_strSigns);
        return editor;
    } else if (index.column() == 2) {
        if (m_strFeatures.indexOf(index.model()->data(index.model()->index(index.row(), 0)).toString()) == (m_strFeatures.size() - 1)) {
            QLineEdit *editor = new QLineEdit(parent);
            return editor;
        } else {
            QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
            editor->setRange(-INFINITY, INFINITY);
            return editor;
        }
    } else if (index.column() == 3) {
        QComboBox *editor = new QComboBox(parent);
        editor->addItems(m_strConditions);
        return editor;
    } else {
        return NULL;
    }
}

void QJudgeConditionItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.column() != 2) {
        QComboBox *comboBox = static_cast<QComboBox *>(editor);
        QString str = index.model()->data(index, Qt::EditRole).toString();
        comboBox->setCurrentIndex(comboBox->findText(str));
    } else if (index.column() == 2) {
        if (m_strFeatures.indexOf(index.model()->data(index.model()->index(index.row(), 0)).toString()) == (m_strFeatures.size() - 1)) {
            QLineEdit *edit = static_cast<QLineEdit *>(editor);

            QString str = index.model()->data(index, Qt::EditRole).toString();
            edit->setText(str);
        } else {
            QDoubleSpinBox *edit = static_cast<QDoubleSpinBox *>(editor);

            double dValue = index.model()->data(index, Qt::EditRole).toDouble();
            edit->setValue(dValue);
        }
    }
}

void QJudgeConditionItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (index.column() != 2) {
        QComboBox *comboBox = static_cast<QComboBox *>(editor);
        model->setData(index, comboBox->currentText(), Qt::EditRole);
    } else if (index.column() == 2) {
        if (m_strFeatures.indexOf(index.model()->data(index.model()->index(index.row(), 0)).toString()) == (m_strFeatures.size() - 1)) {
            QLineEdit *edit = static_cast<QLineEdit *>(editor);
            model->setData(index, edit->text(), Qt::EditRole);
        } else {
            QDoubleSpinBox *edit = static_cast<QDoubleSpinBox *>(editor);
            model->setData(index, edit->value(), Qt::EditRole);
        }
    }
}

void QJudgeConditionItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void QJudgeConditionItemDelegate::setFeatures(QStringList strFeatures)
{
    m_strFeatures = strFeatures;
}

void QJudgeConditionItemDelegate::setSigns(QStringList strSigns)
{
    m_strSigns = strSigns;
}

void QJudgeConditionItemDelegate::setConditions(QStringList strConditions)
{
    m_strConditions = strConditions;
}

void AddItem::on_pushButtonAddJudgePatternItem_clicked()
{
    m_stJudgeCondition.vecJudgePattern.append(JudgePattern());
    m_stJudgeCondition.vecJudgePattern.last().strPattern = m_strliPatterns[0];
    updateJudgePatternTable();
    ui->tableViewJudgePattern->selectRow(m_stJudgeCondition.vecJudgePattern.size() - 1);
    updateJudgeConditionTable();
//    QStandardItemModel *model = (QStandardItemModel*)ui->tableViewJudgePattern->model();
//    int cnt = model->rowCount();
//    model->setRowCount(cnt+1);
//    model->setItem(cnt,0,new QStandardItem(m_strliPatterns[0]));
//    model->item(cnt,0)->setCheckable(true);
//    model->item(cnt,0)->setCheckState(Qt::Checked);
//    model->setItem(cnt,1,new QStandardItem(m_strliDefectType[0]));
//    model->setItem(cnt,2,new QStandardItem(m_strliDefectColor[0]));
//    model->setItem(cnt,3,new QStandardItem(m_strliCondition[0]));

    //model->item(model->rowCount()-1,0)->setCheckable(true);
    //model->item(model->rowCount()-1,0)->setCheckState(Qt::Checked);
}

void AddItem::on_pushButtonDeleteJudgePatternItem_clicked()
{
    QStandardItemModel *model = (QStandardItemModel *)ui->tableViewJudgePattern->model();
    int idx = ui->tableViewJudgePattern->currentIndex().row();
    if (idx >= 0) {
        m_stJudgeCondition.vecJudgePattern.removeAt(idx);
        updateJudgePatternTable();
        if (idx >= m_stJudgeCondition.vecJudgePattern.size()) {
            ui->tableViewJudgePattern->selectRow(idx - 1);
        } else {
            ui->tableViewJudgePattern->selectRow(idx);
        }
        updateJudgeConditionTable();
    }
}

void AddItem::on_pushButton_addConditionItem_clicked()
{
    int idx = ui->tableViewJudgePattern->currentIndex().row();
    if (idx >= 0) {
        m_stJudgeCondition.vecJudgePattern[idx].vecJudgement.append(Judgement());
        updateJudgeConditionTable();
        ui->tableViewConditions->selectRow(m_stJudgeCondition.vecJudgePattern[idx].vecJudgement.size() - 1);
    }
//    QStandardItemModel *model = (QStandardItemModel*)ui->tableViewConditions->model();
//    int cnt = model->rowCount();
//    model->setRowCount(cnt+1);
//    model->setItem(cnt,0,new QStandardItem(m_strliFeatures[0]));
//    model->item(cnt,0)->setCheckable(true);
//    model->item(cnt,0)->setCheckState(Qt::Checked);
//    model->setItem(cnt,1,new QStandardItem(m_strliSign[0]));
//    model->setItem(cnt,2,new QStandardItem(QString::number(0)));
//    model->setItem(cnt,3,new QStandardItem(m_strliCondition[0]));
}

void AddItem::on_pushButton_deleteCondition_clicked()
{
    int idx = ui->tableViewJudgePattern->currentIndex().row();
    if (idx >= 0) {
        int id = ui->tableViewConditions->currentIndex().row();
        if (id >= 0) {
            m_stJudgeCondition.vecJudgePattern[idx].vecJudgement.removeAt(id);

            updateJudgeConditionTable();
            if (id >= m_stJudgeCondition.vecJudgePattern.size()) {
                ui->tableViewConditions->selectRow(id - 1);
            } else {
                ui->tableViewConditions->selectRow(id);
            }
        }
    }
//    QStandardItemModel *model = (QStandardItemModel*)ui->tableViewConditions->model();
//    if(ui->tableViewConditions->currentIndex().row() >= 0)
//    {
//        model->removeRow(ui->tableViewConditions->currentIndex().row());
//    }
}

void AddItem::on_buttonBox_accepted()
{
    if (ui->comboBoxReasonName->currentIndex() < 0) {
        QMessageBox::critical(this, "参数错误", "未选择缺陷名称，请重新选择");
        return;
    }
    m_stJudgeCondition.bEnable = ui->comboBox_itembUsed->currentIndex();
    m_stJudgeCondition.stJudgeReason = ui->comboBoxReasonName->currentData().value<JudgeReason>();
    m_stJudgeCondition.nPriority = ui->comboBox_itemPriority->currentIndex() - 1;
    m_stJudgeCondition.strGrade = ui->comboBox_itemGrade->currentText();
//    m_stJudgeCondition.vecJudgePattern.clear();
    //m_stJudgeCondition.vecJudgement.clear();
//    QStandardItemModel *model = (QStandardItemModel*)ui->tableViewJudgePattern->model();
//    for(int i = 0;i < model->rowCount();i++)
//    {
//        JudgePattern pattern;
//        pattern.bEnable = model->item(i,0)->checkState()==Qt::Checked;
//        pattern.strPattern = model->item(i,0)->text();
//        pattern.eDefectType = (DefectType)m_strliDefectType.indexOf(model->item(i,1)->text());
//        pattern.eDefectColor = (DefectColor)m_strliDefectColor.indexOf(model->item(i,2)->text());
//        pattern.eCondition = (ENUM_CONDITION)m_strliCondition.indexOf(model->item(i,3)->text());
//        m_stJudgeCondition.vecJudgePattern.push_back(pattern);
//    }
//    model = (QStandardItemModel*)ui->tableViewConditions->model();
//    for(int i = 0;i < model->rowCount();i++)
//    {
//        Judgement judgement;
//        judgement.bEnable = model->item(i,0)->checkState()==Qt::Checked;
//        judgement.eFeature = (ENUM_DEFECT_FEATURE)m_strliFeatures.indexOf(model->item(i,0)->text());
//        judgement.eSign = (ENUM_SIGN_OF_INEQUALITY)m_strliSign.indexOf(model->item(i,1)->text());
//        judgement.dValue = model->item(i,2)->text().toDouble();
//        judgement.eCondition = (ENUM_CONDITION)m_strliCondition.indexOf(model->item(i,3)->text());
//        m_stJudgeCondition.vecJudgement.push_back(judgement);
//    }
    accept();
}

void AddItem::on_buttonBox_rejected()
{
    reject();
}

void AddItem::on_tableViewJudgePattern_clicked(const QModelIndex &index)
{
    int idx = index.row();
    if (idx >= 0) {
        updateJudgeConditionTable();
    }
}

void AddItem::on_pushButtonCopy_clicked()
{
    int idx = ui->tableViewJudgePattern->currentIndex().row();
    if (idx >= 0) {
        m_stJudgeCondition.vecJudgePattern.append(m_stJudgeCondition.vecJudgePattern[idx]);
        updateJudgePatternTable();
        ui->tableViewJudgePattern->selectRow(m_stJudgeCondition.vecJudgePattern.size() - 1);
        updateJudgeConditionTable();
    }
}
