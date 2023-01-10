#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // создаем невырвиглазный цвет
    orange.setRgb(255, 102, 0);

// очищаем все
    ui -> pushButton_clear -> click();
    ui -> lineEdit_last_points -> setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// функция, которая проверяет максимум очков
bool MainWindow::checkMaxScore(int value, int parameter)
{
    switch (parameter)
    {
    case 1:
        sumOfPoints = value + dexterity + intelligence + charisma + luck;
        break;
    case 2:
        sumOfPoints = strength + value + intelligence + charisma + luck;
        break;
    case 3:
        sumOfPoints = strength + dexterity + value + charisma + luck;
        break;
    case 4:
        sumOfPoints = strength + dexterity + intelligence + value + luck;
        break;
    case 5:
        sumOfPoints = strength + dexterity + intelligence + charisma + value;
        break;
    }

    if (sumOfPoints > 20)
    {
        QMessageBox::information(this, "Ошибка", "Нельзя потратить больше 20 очков!");
        return false;
    }
    return true;
}

// функция создает палетту для спинбокса и лабеля и устанавливает цвет в соответствии со значением
void MainWindow::changeColor()
{
    QPalette spinboxPalette = spinbox->palette();
    QPalette labelPalette = label->palette();
    if (spinbox->value() >= 8)
    {
        spinboxPalette.setColor(QPalette::Text, Qt::green);
        labelPalette.setColor(QPalette::WindowText, Qt::green);
    }
    else if (spinbox->value() >= 4)
    {
        spinboxPalette.setColor(QPalette::Text, orange);
        labelPalette.setColor(QPalette::WindowText, orange);
    }
    else
    {
        spinboxPalette.setColor(QPalette::Text, Qt::red);
        labelPalette.setColor(QPalette::WindowText, Qt::red);
    }

    spinbox->setPalette(spinboxPalette);
    label->setPalette(labelPalette);
}


// пhоверка имени
bool MainWindow::checkName()
{
    if (ui->lineEdit_name->text().size() < 3 || ui->lineEdit_name->text().size() > 20)
        return false;
    return true;

}

// кнопка создать
void MainWindow::on_pushButton_create_clicked()
{
    // ошибка имени
    if (!checkName())
    {
        QMessageBox::information(this, "Ошибка", "Имя должно быть 3-20 символов", QMessageBox::Ok);
        return;
    }
    else if (ui->lineEdit_last_points->text().toInt() != 0)
    {
        QMessageBox::information(this, "Ошибка", "Потратьте все очки", QMessageBox::Ok);
        return;
    }


    // расчитываем характеристики
    int health = 4 * strength + 2 * dexterity + 1 * intelligence + 1 * luck;
    int mana = 3 * strength + 1 * dexterity + 4 * intelligence + 1 * luck;
    int attack = 5 * strength + 3 * dexterity + 1 * intelligence + 2 * luck;
    int defend = 1 * strength + 3 * dexterity + 4 * intelligence + 2 * luck;

    ui->label_hp_val->setNum(health);
    ui->label_mana_val->setNum(mana);
    ui->label_attack_val->setNum(attack);
    ui->label_defend_val->setNum(defend);

    // считаем класс
    int arrOfChar[4] = {health, mana, attack, defend};
    int maxChar = 0;
    int indexOfMaxChar = 0;
    for (int i = 0; i < (sizeof(arrOfChar)/sizeof(arrOfChar[0])); ++i)
    {
        if (arrOfChar[i] > maxChar)
        {
            maxChar = arrOfChar[i];
            indexOfMaxChar = i;
        }
    }

    // указываем класс
    switch (indexOfMaxChar)
    {
    case 1:
        if (ui->radioButton_sex_m->isChecked())
            ui->label_class_val->setText("Таран");
        else
            ui->label_class_val->setText("Таранщица");
        break;

    case 2:
        if (ui->radioButton_sex_m->isChecked())
            ui->label_class_val->setText("Маг");
        else
            ui->label_class_val->setText("Волшебница");
        break;

    case 3:
        if (ui->radioButton_sex_m->isChecked())
            ui->label_class_val->setText("Воин");
        else
            ui->label_class_val->setText("Воительница");
        break;

    case 4:
        if (ui->radioButton_sex_m->isChecked())
            ui->label_class_val->setText("Защитник");
        else
            ui->label_class_val->setText("Защитница");
        break;
    }
}

// очистка
void MainWindow::on_pushButton_clear_clicked()
{
    // делаем палетты
    QPalette spinboxPalette = ui->spinBox_strength->palette();
    spinboxPalette.setColor(QPalette::Text, Qt::red);
    QPalette labelPallette = ui->label_strength->palette();
    labelPallette.setColor(QPalette::WindowText, Qt::red);

    // задаем палетты
    ui->label_strength->setPalette(labelPallette);
    ui->label_dexterity->setPalette(labelPallette);
    ui->label_intelligence->setPalette(labelPallette);
    ui->label_charisma->setPalette(labelPallette);
    ui->label_luck->setPalette(labelPallette);

    ui->spinBox_strength->setPalette(spinboxPalette);
    ui->spinBox_dexterity->setPalette(spinboxPalette);
    ui->spinBox_intelligence->setPalette(spinboxPalette);
    ui->spinBox_charisma->setPalette(spinboxPalette);
    ui->spinBox_luck->setPalette(spinboxPalette);

    // сбрасываем значения
    ui->spinBox_strength->setValue(1);
    ui->spinBox_dexterity->setValue(1);
    ui->spinBox_intelligence->setValue(1);
    ui->spinBox_charisma->setValue(1);
    ui->spinBox_luck->setValue(1);

    ui->label_hp_val->clear();
    ui->label_mana_val->clear();
    ui->label_defend_val->clear();
    ui->label_attack_val->clear();
    ui->label_class_val->clear();

    ui->lineEdit_name->clear();
    ui->radioButton_sex_m->setChecked(true);

}


// сила
void MainWindow::on_spinBox_strength_valueChanged(int arg1)
{
    // здесь проверяется максимум очков и если  все в порядке, то присваивается значение
    if (!checkMaxScore(arg1, 1))
    {
        ui->spinBox_strength->setValue(strength);
        return;
    }
    strength = arg1;

    // устанавливается новое значение оставшихся очков
    ui->lineEdit_last_points->setText(QString::number(maxPoints - sumOfPoints));
    // меняем цвет
    spinbox = ui->spinBox_strength;
    label = ui->label_strength;
    changeColor();

}


// ловкость
void MainWindow::on_spinBox_dexterity_valueChanged(int arg1)
{
    // здесь проверяется максимум очков и если  все в порядке, то присваивается значение
    if (!checkMaxScore(arg1, 2))
    {
        ui->spinBox_dexterity->setValue(dexterity);
        return;
    }
    dexterity = arg1;
    // устанавливается новое значение оставшихся очков
    ui->lineEdit_last_points->setText(QString::number(maxPoints - sumOfPoints));
    // меняем цвет
    spinbox = ui->spinBox_dexterity;
    label = ui->label_dexterity;
    changeColor();
}


// интеллект
void MainWindow::on_spinBox_intelligence_valueChanged(int arg1)
{
    // здесь проверяется максимум очков и если  все в порядке, то присваивается значение
    if (!checkMaxScore(arg1, 3))
    {
        ui->spinBox_intelligence->setValue(intelligence);
        return;
    }
    intelligence = arg1;

    // устанавливается новое значение оставшихся очков
    ui->lineEdit_last_points->setText(QString::number(maxPoints - sumOfPoints));
    // меняем цвет
    spinbox = ui->spinBox_intelligence;
    label = ui->label_intelligence;
    changeColor();
}


// харизма
void MainWindow::on_spinBox_charisma_valueChanged(int arg1)
{
    // здесь проверяется максимум очков и если  все в порядке, то присваивается значение
    if (!checkMaxScore(arg1, 4))
    {
        ui->spinBox_charisma->setValue(charisma);
        return;
    }
    charisma = arg1;

    // устанавливается новое значение оставшихся очков
    ui->lineEdit_last_points->setText(QString::number(maxPoints - sumOfPoints));
    // меняем цвет
    spinbox = ui->spinBox_charisma;
    label = ui->label_charisma;
    changeColor();
}


// удача
void MainWindow::on_spinBox_luck_valueChanged(int arg1)
{
    // здесь проверяется максимум очков и если  все в порядке, то присваивается значение
    if (!checkMaxScore(arg1, 5))
    {
        ui->spinBox_luck->setValue(luck);
        return;
    }
    luck = arg1;

    // устанавливается новое значение оставшихся очков
    ui->lineEdit_last_points->setText(QString::number(maxPoints - sumOfPoints));
    // меняем цвет
    spinbox = ui->spinBox_luck;
    label = ui->label_luck;
    changeColor();
}


// имя
void MainWindow::on_lineEdit_name_textChanged(const QString &)
{
    // проверка на длину
    if (checkName())
    {
        ui->label_name_error->setVisible(false);
    }
    else
    {
        ui->label_name_error->setVisible(true);
    }
}
