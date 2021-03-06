#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QSettings>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "graphicsview.h"
#include "scene.h"
#include "customrectitem.h"


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
    void ClearStatusLabels();

private slots:
    void on_actionE_xit_triggered();

    void on_action_Close_triggered();

    void on_actionC_lose_All_triggered();

    void on_actionOpen_triggered();

    void on_actionGrid_Settings_triggered();

    void on_actionAbout_Qt_triggered();

    void on_action_New_triggered();

    void on_action_toolBar(QAction *action);

    void on_grid_changed();

    void on_grid_on_off(bool checked);

    void updateStatusPos();

private:
    Ui::MainWindow *ui;
    QSettings settings;
    QMdiSubWindow *subWindow1;
    GraphicsView *view;
    Scene *scene;
    QScrollArea *sa;
    bool gridIsActive;
    int gridStep;
    QColor gridColor;
    QPushButton *btnGrid;
    QLabel *lblZoom;
    QLabel *lblCoor;
};
#endif // MAINWINDOW_H
