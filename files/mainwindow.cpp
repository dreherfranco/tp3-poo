#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QStandardItemModel>
#include <iostream>
#include <fstream>
#include "string.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->labelCI->hide();
    this->ui->labelAI->hide();
    this->ui->labelCG->hide();
    this->ui->labelCNG->hide();
    this->ui->buttonSiCI->hide();
    this->ui->buttonNoCI->hide();
    this->ui->buttonSiAI->hide();
    this->ui->buttonNoAI->hide();
}

MainWindow::~MainWindow(){
    delete ui;
}

bool sortVec (std::pair<std::string,int> i, std::pair<std::string, int> j){
    return (i.second > j.second);
}

bool mayorOcurrencias (structInd i, structInd j){
    return (i.cantOcu > j.cantOcu);
}

void MainWindow::on_pushButton_clicked(){

    this->ui->labelCI->hide();
    this->ui->labelAI->hide();
    this->ui->buttonSiCI->hide();
    this->ui->buttonNoCI->hide();
    this->ui->buttonSiAI->hide();
    this->ui->buttonNoAI->hide();
    std::string rutaDirectorio = this->ui->lineEdit->text().toStdString();

    std::string nombreArchivoBinario = rutaDirectorio + "\\Indice.dat";
    std::fstream archivoBinario (nombreArchivoBinario);

    if(!archivoBinario.good()){
        this->ui->labelCI->show();
        this->ui->buttonSiCI->show();
        this->ui->buttonNoCI->show();
    }
    else{
        this->ui->labelAI->show();
        this->ui->buttonSiAI->show();
        this->ui->buttonNoAI->show();
    }
}

void MainWindow::setearIndices()
{

        std::string rutaDirectorio = this->ui->lineEdit->text().toStdString();
        Directorio directorio(rutaDirectorio);

        QStringList archivos = directorio.getArchivos();

        std::string archivoPreposiciones =  this->ui->lineEdit_2->text().toStdString();

        foreach(QString filename, archivos) {
            std::string addressFile = rutaDirectorio + "\\" + filename.toStdString();
            Archivo archivo;
            archivo.setName(filename.toStdString());
            archivo.setIndices(addressFile, archivoPreposiciones);
            this->indices.push_back(archivo);
        }
}

void MainWindow::mostrarIndicesGuardadosEnTableView()
{
    QStandardItemModel * model = new QStandardItemModel();
    model->setColumnCount(2);
    model->setHorizontalHeaderItem(0, new QStandardItem("Archivos"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Cantidad"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Palabras"));
    indices.clear();
    std::vector<structInd> indices = this->gestorBinario.leerArchivoPorOcurrencia(this->ui->lineEdit->text().toStdString(), this->ui->lineEdit_3->text().toStdString());

    std::sort(indices.begin() ,indices.end(), mayorOcurrencias);
    int i = 0;

    for(auto f = indices.begin(); f != indices.end(); ++f){
         model->setItem(i, 0, new QStandardItem(QString::fromStdString(f->NombreArchivo)));
         model->setItem(i, 1, new QStandardItem(QString::number(f->cantOcu)));
         model->setItem(i, 2, new QStandardItem(QString::fromStdString(f->palabra)));
         i++;
    }

    this->ui->tableView->setModel(model);
    this->ui->tableView->resizeColumnToContents(0);
    this->ui->tableView->resizeColumnToContents(1);
    this->ui->tableView->show();
}

void MainWindow::mostrarIndicesNoGuardadosEnTableView()
{
    QStandardItemModel * model = new QStandardItemModel();
    model->setColumnCount(2);
    model->setHorizontalHeaderItem(0, new QStandardItem("Archivos"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Cantidad"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Palabras"));
    //indices.clear();
    std::string rutaDirectorio = this->ui->lineEdit->text().toStdString();

    Directorio directorio(rutaDirectorio);
    QStringList archivos = directorio.getArchivos();

    std::string archivoPreposiciones =  this->ui->lineEdit_2->text().toStdString();
    std::string wordFind = ocurrencia.deletePrep((this->ui->lineEdit_3->text()).toStdString().data(), archivoPreposiciones);
    std::vector<structInd> indices;
    structInd indiceStruct;
    int cantOcu;
    foreach(QString filename, archivos) {
       std::string addressFile = rutaDirectorio + "\\" + filename.toStdString();
       Archivo archivo;
       archivo.setName(filename.toStdString());
       archivo.setIndices(addressFile, archivoPreposiciones);
       this->indices.push_back(archivo);

       cantOcu = ocurrencia.getCantOcu(addressFile, wordFind);
       indiceStruct.cantOcu = cantOcu;
       strcpy(indiceStruct.palabra, wordFind.c_str());
       strcpy(indiceStruct.NombreArchivo,filename.toStdString().c_str());
      indices.push_back(indiceStruct);
    }

    std::sort(indices.begin() ,indices.end(), mayorOcurrencias);
    int i = 0;

    for(auto f = indices.begin(); f != indices.end(); ++f){
         model->setItem(i, 0, new QStandardItem(QString::fromStdString(f->NombreArchivo)));
         model->setItem(i, 1, new QStandardItem(QString::number(f->cantOcu)));
         model->setItem(i, 2, new QStandardItem(QString::fromStdString(f->palabra)));
         i++;
    }

    this->ui->tableView->setModel(model);
    this->ui->tableView->resizeColumnToContents(0);
    this->ui->tableView->resizeColumnToContents(1);
    this->ui->tableView->show();
}

void MainWindow::on_buttonSiCI_clicked()
{
    this->ui->labelCI->hide();
    this->ui->buttonSiCI->hide();
    this->ui->buttonNoCI->hide();
    this->ui->labelCNG->hide();

    std::string directorio = this->ui->lineEdit->text().toStdString();
    setearIndices();
    this->gestorBinario.crearIndice(directorio,this->indices);
    mostrarIndicesGuardadosEnTableView();
    this->ui->labelCG->show();
}

void MainWindow::on_buttonNoCI_clicked()
{
    this->ui->labelCG->hide();
    this->ui->labelCI->hide();
    this->ui->buttonSiCI->hide();
    this->ui->buttonNoCI->hide();
    this->ui->labelCNG->show();
    mostrarIndicesNoGuardadosEnTableView();
}

void MainWindow::on_buttonSiAI_clicked()
{
    this->ui->labelAI->hide();
    this->ui->buttonSiAI->hide();
    this->ui->buttonNoAI->hide();
    this->ui->labelCNG->hide();

    setearIndices();
    std::string directorio = this->ui->lineEdit->text().toStdString();
    this->gestorBinario.actualizarIndice(directorio, this->indices);
    mostrarIndicesGuardadosEnTableView();

    this->ui->labelCG->show();
}

void MainWindow::on_buttonNoAI_clicked()
{
    this->ui->labelCG->hide();
    this->ui->labelAI->hide();
    this->ui->buttonSiAI->hide();
    this->ui->buttonNoAI->hide();

    mostrarIndicesGuardadosEnTableView();
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    QVariant item = this->ui->tableView->model()->data(index);
    QString fileName = this->ui->lineEdit->text() + "\\" + item.toString();

    archivoTexto.setFileTxt(fileName.toStdString());
    std::string fileTxt = archivoTexto.getFileTxt();
    this->ui->textEdit->setText(QString(fileTxt.c_str()));
}

void MainWindow::on_pushButton_2_clicked()
{
    QStandardItemModel * model = new QStandardItemModel();
    model->setColumnCount(2);
    model->setHorizontalHeaderItem(0, new QStandardItem("Archivos"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Cantidad"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Palabras"));
    indices.clear();
    std::vector<structInd> indices = this->gestorBinario.leerTodoElContenidoDelArchivo(this->ui->lineEdit->text().toStdString());

    std::sort(indices.begin() ,indices.end(), mayorOcurrencias);
    int i = 0;

    for(auto f = indices.begin(); f != indices.end(); ++f){
         model->setItem(i, 0, new QStandardItem(QString::fromStdString(f->NombreArchivo)));
         model->setItem(i, 1, new QStandardItem(QString::number(f->cantOcu)));
         model->setItem(i, 2, new QStandardItem(QString::fromStdString(f->palabra)));
         i++;
    }

    this->ui->tableView_2->setModel(model);
    this->ui->tableView_2->resizeColumnToContents(0);
    this->ui->tableView_2->resizeColumnToContents(1);
    this->ui->tableView_2->resizeColumnToContents(2);
    this->ui->tableView_2->show();

}
