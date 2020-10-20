#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "directorio.h"
#include "archivo.h"
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QStandardItemModel* inicializarModel(QStandardItemModel* model);
     QStandardItemModel* setModel(QStandardItemModel* model);
     void ordenarArchivos();
     void inicializar_TableView_DobleClick();
      QString getTextoDeArchivoTxt(char* filename);
      Archivo* buscarArchivo(char* filename);
      QString insertarPosicionLineaOcurrencias(Archivo* archivo);
      void inicializar_BotonBuscar_Clicked();
      void ocultarGraficosDeGuardado();
private slots:
    void on_botonBuscar_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_buttonSaveChanges_clicked();

    void on_buttonDontSaveChanges_clicked();

    void on_buttonUpdate_clicked();

    void on_buttonNoUpdate_clicked();

private:
    Ui::MainWindow *ui;
    char* path;
    Directorio* directorio;
    std::vector<Archivo*> archivos;
    char* ocurrencia;
    int longOcu;
    bool guardarArchivo;
    bool actualizarArchivo;
    char* nombreArchivoBinario;

    QByteArray ignorarPreposiciones(QByteArray ocurrencia);
    bool fileExist(std::string filename);
    void insertarEnBinario();
    void extraerDeArchivoBinario();
    ArchivoStruct returnStruct(Archivo* archivo);    
    void filtrarArchivos(char** listaArchivos, int cantArchivos, QByteArray conversionRuta, QByteArray ocurrencia );
};
#endif // MAINWINDOW_H
