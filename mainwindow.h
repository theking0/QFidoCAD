#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void CheckMenuCmdEnable();
    void LoadSettings();
    void SaveSettings();

private slots:
    void on_actionE_xit_triggered();

    void on_action_Close_triggered();

    void on_actionC_lose_All_triggered();

    void on_actionOpen_triggered();

    void on_actionGrid_Settings_triggered();

    void on_actionAbout_Qt_triggered();

    void on_action_New_triggered();

    void on_action_toolBar(QAction *action);

private:
    Ui::MainWindow *ui;
    QSettings settings;
    QMdiSubWindow *subWindow1;
};
#endif // MAINWINDOW_H
