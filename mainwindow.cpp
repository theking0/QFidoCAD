#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_grid_settings.h"
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QGraphicsEllipseItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(ui->mdiArea, &QMdiArea::subWindowActivated, this, &MainWindow::CheckMenuCmdEnable);
    connect(ui->toolBar, &QToolBar::actionTriggered, this, &MainWindow::on_action_toolBar);

    lblZoom = new QLabel(ui->statusbar);
    lblCoor = new QLabel(ui->statusbar);
    btnGrid = new QPushButton(ui->statusbar);

    QWidget *si = new QWidget(ui->statusbar);

    ClearStatusLabels();

    lblZoom->setMinimumHeight(20);

    btnGrid->setCheckable(true);
    btnGrid->setChecked(true);

    connect(btnGrid, &QPushButton::toggled, this, &MainWindow::on_grid_on_off);

    QIcon icon(":/icons/grid.ico");
    btnGrid->setIcon(icon);
    btnGrid->setIconSize(QSize(16,16));
    btnGrid->setMinimumSize(QSize(18,18));
    btnGrid->setMaximumSize(QSize(18,18));
    ui->statusbar->addWidget(si,1);
    ui->statusbar->addWidget(btnGrid,0);
    ui->statusbar->addWidget(lblZoom,0);
    ui->statusbar->addWidget(lblCoor,0);

    ui->toolBar->setVisible(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CheckMenuCmdEnable()
{
    bool enabled = false;
/*
    if (ui->mdiArea->subWindowList().count() > 0 && ui->mdiArea->activeSubWindow())
        enabled = true;
*/
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

void MainWindow::ClearStatusLabels()
{
    lblZoom->setText("*** %");
    lblCoor->setText("X: ***, Y: ***");
}

void MainWindow::on_actionE_xit_triggered()
{
  //  ui->mdiArea->closeAllSubWindows();
    this->close();
}

void MainWindow::on_action_Close_triggered()
{
  //  ui->mdiArea->closeActiveSubWindow();
}

void MainWindow::on_actionC_lose_All_triggered()
{
   // ui->mdiArea->closeAllSubWindows();
}

void MainWindow::on_actionOpen_triggered()
{

}

void MainWindow::on_actionGrid_Settings_triggered()
{
    DialogGridSettings *dl = new DialogGridSettings(this);
    connect(dl, &DialogGridSettings::gridChanged, this, &MainWindow::on_grid_changed);
    dl->show();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}
#include <QGraphicsLineItem>
void MainWindow::on_action_New_triggered()
{/*
    subWindow1 = new QMdiSubWindow(ui->mdiArea);
    subWindow1->setWidget(new QWidget);
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    subWindow1->setWindowIcon(QIcon(QPixmap(1,1)));
    subWindow1->setWindowTitle(QString("New Schematic %1 *").arg(ui->mdiArea->subWindowList().count()+1));
    subWindow1->showMaximized();
    subWindow1->setMinimumSize(200,200);

    sa = new QScrollArea(subWindow1);

    scene = new Scene();
    view = new GraphicsView(scene);
    sa->setMinimumSize(QSize(100,100));
    //view->setMinimumSize(QSize(5000,5000));

    gridIsActive = btnGrid->isChecked();
    view->enableGrid(gridIsActive);

    QGraphicsLineItem *li = new QGraphicsLineItem(0,0,300,300);
    li->setPen(QPen(Qt::black, 3));
    scene->addItem(li);
    sa->setWidget(view);
    subWindow1->setWidget(view);


   // QVBoxLayout *layout = new QVBoxLayout;
    //layout->addWidget(view);
    //subWindow1->setLayout(layout);

    //subWindow1->layout()->addWidget(view);

    ui->mdiArea->addSubWindow(subWindow1)->show();
    //view->show();
    */
    scene = new Scene();
    view = new GraphicsView(scene);
    sa = new QScrollArea(this);

    connect(view, SIGNAL(mousePosChanged), this, SLOT(updateStatusPos));

    gridIsActive = btnGrid->isChecked();
    view->enableGrid(gridIsActive);
/*
    QGraphicsLineItem *li = new QGraphicsLineItem(0,0,200,200);
    li->setPen(QPen(Qt::black, 2));
    li->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
    scene->addItem(li);
*/
    CustomRectItem* rectItem1 = new CustomRectItem(QRect(0,0,80,80));
    rectItem1->setPos(50,50);
    rectItem1->setBrush(Qt::gray);
    scene->addItem(rectItem1);

    CustomRectItem* rectItem2 = new CustomRectItem(QRect(0,0,60,60));
    rectItem2->setPos(160,60);
    rectItem2->setBrush(Qt::magenta);
    scene->addItem(rectItem2);
scene->update();
  //  connect(rectItem1, &CustomRectItem::ItemPositionHasChanged)


    sa->setWidget(view);
    ui->toolBar->setVisible(true);
    int idx = ui->tabMain->addTab(view, "New schematic 1 *");
    ui->tabMain->setCurrentIndex(idx);
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

void MainWindow::on_grid_changed()
{/*
    QList<QMdiSubWindow *> lstWnds = ui->mdiArea->subWindowList();
    QSettings s;
    gridStep = s.value("grid_step").toInt();
    gridColor = s.value("grid_color").value<QColor>();

    for(int i = 0; i < lstWnds.count(); i++)
    {
        QScrollArea *sa = (QScrollArea *)lstWnds[i]->widget();
        GraphicsView *gv = (GraphicsView *)sa->widget();

        gv->setGrid(gridStep,gridColor);
        gv->enableGrid(gridIsActive);
        gv->viewport()->update();
    }*/
}

void MainWindow::on_grid_on_off(bool checked)
{
    gridIsActive = checked;
    this->on_grid_changed();

}

void MainWindow::updateStatusPos()
{
    lblCoor->setText(QString("X: %1, Y: %2").arg(view->getMousePos().x(),view->getMousePos().y()));
}
