#ifndef DIALOG_GRID_SETTINGS_H
#define DIALOG_GRID_SETTINGS_H

#include <QDialog>
#include <QColorDialog>
#include <QSettings>

namespace Ui {
class DialogGridSettings;
}

class DialogGridSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGridSettings(QWidget *parent);
    ~DialogGridSettings();

signals:
    void gridChanged();

private slots:
    void on_btnCancel_clicked();

    void on_btnOK_clicked();

    void on_btnSelectColor_clicked();

private:
    void setBtnColorBg(QColor color);

private:
    Ui::DialogGridSettings *ui;
    QSettings settings;
    QColor gridColor;
};

#endif // DIALOG_GRID_SETTINGS_H
