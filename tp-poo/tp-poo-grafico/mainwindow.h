#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "directorio.h"
#include "archivo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_botonBuscar_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    const char* path;

    Directorio* directorio;
    Archivo** archivos;

    char* ocurrencia;
    int longOcu;

    QByteArray ignorarPreposiciones(QByteArray ocurrencia);
};
#endif // MAINWINDOW_H
