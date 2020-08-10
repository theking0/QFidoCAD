#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_grid_settings.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->mdiArea, &QMdiArea::subWindowActivated, this, &MainWindow::CheckMenuCmdEnable);
    connect(ui->toolBar, &QToolBar::actionTriggered, this, &MainWindow::on_action_toolBar);
    //subWindow1 = new QMdiSubWindow(ui->mdiArea);
    //subWindow1->setWidget(new QWidget);
   // subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    //subWindow1->setWindowIcon(QIcon(QPixmap(1,1)));
    //subWindow1->showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CheckMenuCmdEnable()
{
    bool enabled = false;

    if (ui->mdiArea->subWindowList().count() > 0 && ui->mdiArea->activeSubWindow())
        enabled = true;

    ui->action_Save->setEnabled(enabled);
    ui->actionSave_As->setEnabled(enabled);
    ui->action_Close->setEnabled(enabled);
    ui->actionC_lose_All->setEnabled(enabled);
    ui->action_Print->setEnabled(enabled);
}

void MainWindow::LoadSettings()
{

}

void MainWindow::SaveSettings()
{

}

void MainWindow::on_actionE_xit_triggered()
{
    ui->mdiArea->closeAllSubWindows();
    this->close();
}

void MainWindow::on_action_Close_triggered()
{
    ui->mdiArea->closeActiveSubWindow();
}

void MainWindow::on_actionC_lose_All_triggered()
{
    ui->mdiArea->closeAllSubWindows();
}

void MainWindow::on_actionOpen_triggered()
{

}

void MainWindow::on_actionGrid_Settings_triggered()
{
    DialogGridSettings *dl = new DialogGridSettings(this);

    dl->show();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::on_action_New_triggered()
{
    subWindow1 = new QMdiSubWindow(ui->mdiArea);
    subWindow1->setWidget(new QWidget);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    subWindow1->setWindowIcon(QIcon(QPixmap(1,1)));
    subWindow1->setWindowTitle(QString("New Schematic %1 *").arg(ui->mdiArea->subWindowList().count()+1));
    subWindow1->showMaximized();
    ui->mdiArea->addSubWindow(subWindow1)->show();
}

void MainWindow::on_action_toolBar(QAction *action)
{
    const QList<QAction *> lstAct = {
        ui->actionLine, ui->actionRectangle, ui->actionCurve,
        ui->actionB_zier, ui->actionPolygon, ui->actionConnection,
        ui->actionEllipse, ui->actionText, ui->actionSelection
    };

    for(int i = 0; i < lstAct.count(); i++)
    {
        if(lstAct[i] == action)
        {
            for(int j = 0; j < lstAct.count(); j++)
            {
                if(lstAct[j] != action)
                    lstAct[j]->setChecked(false);
            }
        }
    }
}
