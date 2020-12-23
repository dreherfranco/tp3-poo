#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ocurrencia.h>
#include "directorio.h"
#include "archivo.h"
#include "gestorarchivobinario.h"
#include "StructIndice.h"
#include "map"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    void on_commandLinkButton_clicked();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonSiCI_clicked();

    void on_buttonNoCI_clicked();

    void on_buttonSiAI_clicked();

    void on_buttonNoAI_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Ocurrencia ocurrencia;
    GestorArchivoBinario gestorBinario;
    Archivo archivoTexto;
    std::vector<Archivo> indices;
    void setearIndices();
    void mostrarIndicesGuardadosEnTableView();
    void mostrarIndicesNoGuardadosEnTableView();
};
#endif // MAINWINDOW_H
