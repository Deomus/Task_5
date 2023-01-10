#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSpinBox>
#include <QLabel>
#include <QColor>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int maxPoints = 20;
    int strength = 1;
    int dexterity = 1;
    int intelligence = 1;
    int charisma = 1;
    int luck = 1;
    int sumOfPoints = 5;
    QSpinBox *spinbox;
    QLabel *label;
    QColor orange;

private slots:
    bool checkName();

    void changeColor();

    bool checkMaxScore(int value, int parameter);

    void on_pushButton_create_clicked();

    void on_spinBox_strength_valueChanged(int arg1);

    void on_spinBox_dexterity_valueChanged(int arg1);

    void on_spinBox_intelligence_valueChanged(int arg1);

    void on_spinBox_charisma_valueChanged(int arg1);

    void on_spinBox_luck_valueChanged(int arg1);

    void on_lineEdit_name_textChanged(const QString &arg1);

    void on_pushButton_clear_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
