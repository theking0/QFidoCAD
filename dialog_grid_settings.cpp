#include "dialog_grid_settings.h"
#include "ui_dialog_grid_settings.h"
#include <QDebug>
DialogGridSettings::DialogGridSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGridSettings)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    setBtnColorBg(settings.value("grid_color").value<QColor>());
    ui->spinGridStep->setValue(settings.value("grid_step").toInt());
    ui->cbGridStyle->setCurrentIndex(settings.value("grid_style").toInt());
}

DialogGridSettings::~DialogGridSettings()
{
    delete ui;
}

void DialogGridSettings::on_btnCancel_clicked()
{
    this->close();
}

void DialogGridSettings::on_btnOK_clicked()
{
    settings.setValue("grid_color", gridColor);
    settings.setValue("grid_step", ui->spinGridStep->value());
    settings.setValue("grid_style", ui->cbGridStyle->currentIndex());
    emit gridChanged();
    this->close();
}

void DialogGridSettings::on_btnSelectColor_clicked()
{
    gridColor = QColorDialog::getColor(Qt::black, this);
    if(gridColor.isValid())
        setBtnColorBg(gridColor);
}

void DialogGridSettings::setBtnColorBg(QColor color)
{
    if(!color.isValid())
        return;

    gridColor = color;
    QString qss;
    if (gridColor != Qt::black)
        qss = QString("background-color: %1").arg(gridColor.name());
    else
        qss = QString("background-color: %1; color: %2;").arg(gridColor.name()).arg("white");
    ui->btnSelectColor->setStyleSheet(qss);
}
