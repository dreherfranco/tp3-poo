#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <string>
#include "algorithm"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ocurrencia = nullptr;
    this->directorio = new Directorio();
    this->ui->mostrarArchivo->hide();
    this->ui->tableView->hide();
    this->ui->ocurrenciasFinded->hide();
    this->ui->pushButton->hide();
    this->ui->labelSaveChanges->hide();
    this->ui->buttonSaveChanges->hide();
    this->ui->buttonDontSaveChanges->hide();
    this->ui->labelUnsavedChanges->hide();
    this->ui->labelChangesSaved->hide();
    this->guardarArchivo = false;
    this->actualizarArchivo = false;
    this->ui->labelUpdate->hide();
    this->ui->buttonUpdate->hide();
    this->ui->buttonNoUpdate->hide();
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, "#4f4f4f");
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


bool ordenar(Archivo *archivo1, Archivo *archivo2)
{
    return archivo1->ocurrencia->getTotalOcurrencias() > archivo2->ocurrencia->getTotalOcurrencias();
}


void MainWindow::on_botonBuscar_clicked()
{
     QByteArray ocu, conversionRuta;
     QStandardItemModel * model;
     int tamanio, cantArchivos;
     char** listaArchivos;

    //Limpia la tableView
    this->ui->tableView->reset();
    this->archivos.clear();

    //Tamanio ocurrencia
    this->longOcu = this->ui->ocurrencia->text().length();
    this->ocurrencia = new char[this->longOcu+1];

    //Extrayendo valor ocurrencia
    ocu = this->ui->ocurrencia->text().toLatin1();
    ocu = ignorarPreposiciones(ocu);
    this->ocurrencia = ocu.data();


    //Extraigo el valor del campo del tipo QString y lo convierto a QByteArray para luego manejarlo como char*
    conversionRuta = ui->rutaDirectorio->text().toLatin1();

    tamanio = conversionRuta.length();
    this->path = new char[tamanio+1];

    //Convierto a char* conversionRuta
    this->path = conversionRuta.data();

    //inicializo el directorio
    this->directorio = new Directorio();
    this->directorio->setListaArchivos(path);

    model = new QStandardItemModel();
    model = inicializarModel(model);

    //Obtengo la lista de archivos que se encuentran en el directorio
    listaArchivos = this->directorio->getArchivos();
    cantArchivos = directorio->getCantArchivos();
    delete this->directorio;

    nombreArchivoBinario = new char[strlen(path)+14];
    strcpy(this->nombreArchivoBinario,path);
    strcat(nombreArchivoBinario, "\\archivos.dat");

    if(!fileExist(nombreArchivoBinario)){

        this->filtrarArchivos(listaArchivos,cantArchivos,conversionRuta, ocu);
          if(this->guardarArchivo){
              this->insertarEnBinario();
          }

    }//Si ya existe el archivo binario
    else
    {
        if(this->actualizarArchivo){
            this->filtrarArchivos(listaArchivos,cantArchivos,conversionRuta, ocu);
            this->insertarEnBinario();

        }else{
            this->extraerDeArchivoBinario();
        }

    }


    this->ordenarArchivos();

    //Asigna los archivos de texto a mostrarse en el Model
    model = setModel(model);


    this->ui->tableView->setModel(model);
    //Muestra la tabla
    this->inicializar_BotonBuscar_Clicked();

}

void MainWindow::inicializar_BotonBuscar_Clicked()
{
    //ajusto el largo de las columnas para que se adapten al contenido
    this->ui->tableView->resizeColumnToContents(0);
    this->ui->tableView->resizeColumnToContents(1);
    this->ui->tableView->resizeColumnToContents(2);

    //botones para actualizar o guardar archivo si es que no existe
     if(!this->fileExist(nombreArchivoBinario) && !this->guardarArchivo){
          this->ui->labelSaveChanges->show();
          this->ui->buttonSaveChanges->show();
          this->ui->buttonDontSaveChanges->show();
     }else if(this->fileExist(nombreArchivoBinario) && !this->actualizarArchivo){
          this->ui->labelUpdate->show();
          this->ui->buttonUpdate->show();
          this->ui->buttonNoUpdate->show();
     }
}

QStandardItemModel *MainWindow::inicializarModel(QStandardItemModel *model)
{
    model->setColumnCount(3);
    model->setHorizontalHeaderItem(0, new QStandardItem("Archivos"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Caracteres"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Ocurrencias"));
    return model;
}

void MainWindow::filtrarArchivos(char **listaArchivos, int cantArchivos, QByteArray conversionRuta, QByteArray ocurrencia)
{
    int tamanioNombre, tamanioPath;
    char* nombre;
    char* filename;
    Archivo* archivo;
    QString archivoNombre;

    if(actualizarArchivo){
        char* nombreBinarioOcurrencias = new char[strlen(path)+17];
        strcpy(nombreBinarioOcurrencias, path);
        strcat(nombreBinarioOcurrencias, "\\ocurrencias.dat");
        std::remove(nombreBinarioOcurrencias);
        std::remove(nombreArchivoBinario);
    }

    //Recorro la variables listaArchivos y creo los items de la tabla
    for(int j=0; j<cantArchivos; j++){

        archivoNombre = listaArchivos[j];
        //Instancio objeto de archivo
        archivo= new Archivo();

        //seteo el nombre del archivo que voy a usar para mostrarlo en los item del modelo
        tamanioNombre = archivoNombre.length()+1;
        nombre = new char[tamanioNombre];

        nombre = strcpy(nombre, archivoNombre.toLatin1().data());
        archivo->setNombre(nombre);

        //tamanio del char* , el +2 representa al \\ y al caracter nulo
        tamanioPath = conversionRuta.length() + archivoNombre.length() + 2;

        filename = new char[tamanioPath];
        filename = strcpy(filename, conversionRuta.data() );
        filename = strcat(filename, "\\");
        filename = strcat(filename, archivoNombre.toLatin1().data());

        //Seteo el path del archivo
        archivo->setPath(filename);
        archivo->ocurrencia->setRutaArchivoBinario(this->path);
        //columna de ocurrencias
        archivo->ocurrencia->setTamanioOcu(ocurrencia.length());
        archivo->ocurrencia->setOcurrencia(this->ocurrencia);

        //Le paso true por parametro para que cuente las ocurrencias
        archivo->setearOcurrencias(filename);

        //Asigno el archivo creado por cada iteracion a un indice del arreglo de archivos
        this->archivos.push_back(archivo);

    }

}

void MainWindow::ordenarArchivos()
{
    std::sort(this->archivos.begin(), this->archivos.end(), &ordenar);
}

QStandardItemModel* MainWindow::setModel(QStandardItemModel* model)
{
    int i=0;

    for(std::vector<Archivo*>::iterator it = this->archivos.begin();it < this->archivos.end(); ++it){
        Archivo* archivoIt = *it;
        QString nombreArchivo = archivoIt->getNombre();

          QStandardItem * itemNombreArchivo = new QStandardItem(nombreArchivo);
          model->setItem(i, 0, itemNombreArchivo);
           //Cantidad de caracteres, contando el salto de linea
           int cantCaracteres = archivoIt->getCantidadCaracteres();

           QStandardItem* itemCantidadCarac = new QStandardItem(QString::number(cantCaracteres));
           //Asigno a la columna de cantidad la cantidad de caracteres correspondiente al archivo
           model->setItem(i, 1, itemCantidadCarac);

           archivoIt->ocurrencia->setNombreArchivo(archivoIt->getNombre());
           model->setItem(i, 2, new QStandardItem(QString::number(archivoIt->ocurrencia->getTotalOcurrencias())));
           i++;

    }
    return model;
}



void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    this->inicializar_TableView_DobleClick();

    //Definicion variables
    char* filename;
    int tamanio;
    QString contenidoTablaOcurrencias, total_Lines,nombreArchivo;
     Archivo* archivo;
     QByteArray ocu;
     std::string item;

    //seteo el nombre del archivo en el label superior al QTextEdit("mostrarArchivo")
    nombreArchivo = this->ui->tableView->model()->data(index).toString();

    //Comprueba de que se haga doble click sobre la columna donde esta el nombre del archivo y no en las demas
    if(index.column() == 0){
        this->ui->nombreArchivo->setText(nombreArchivo);
        //Extraer el item de la tabla en formato string
        item = this->ui->tableView->model()->data(index).toString().toStdString();

        filename = nullptr;
        tamanio = this->ui->rutaDirectorio->text().length() + item.length() + 2;

        filename = new char[tamanio];
        //Concatenacion del nombre del archivo, antes de concatenar debo convertirlos a un puntero de char
        filename = strcpy(filename, this->ui->rutaDirectorio->text().toLatin1().data());
        filename = strcat(filename, "\\");
        filename = strcat(filename, item.c_str());

        total_Lines = this->getTextoDeArchivoTxt(filename);

        this->ui->mostrarArchivo->setText(total_Lines);
        this->ui->mostrarArchivo->show();

        //Si se hace doble click en la columna de ocurrencias
        this->longOcu = this->ui->ocurrencia->text().length();
        this->ocurrencia = new char[longOcu+1];
        ocu = this->ui->ocurrencia->text().toLatin1();
        this->ocurrencia = ocu.data();

        //Busca el archivo para poder abrirlo luego
        archivo = this->buscarArchivo(filename);

        contenidoTablaOcurrencias = this->insertarPosicionLineaOcurrencias(archivo);

        this->ui->ocurrenciasFinded->setText(contenidoTablaOcurrencias);
        this->ui->ocurrenciasFinded->show();

    }
}

void MainWindow::inicializar_TableView_DobleClick()
{
    this->ui->labelUnsavedChanges->hide();
    this->ui->labelChangesSaved->hide();
    this->ui->nombreArchivo->show();
    this->ui->pushButton->show();

    this->ui->mostrarArchivo->setText("");
    this->ui->ocurrenciasFinded->setText("");
    this->ui->ocurrenciasFinded->hide();
    this->ui->mostrarArchivo->hide();
}

QString MainWindow::getTextoDeArchivoTxt(char *filename)
{
    char** lines;
    int cantLines;
    Archivo* archivo = new Archivo();
    QString total_Lines;

    //Lineas del archivo de texto contenidas en un char**
    lines = archivo->getLines(filename);

    //Cantidad de lineas del archivo
    cantLines = archivo->getCantLines();


    for(int i=0; i<cantLines; i++){
        //Inserto linea a linea en la variable va a mostrar su contenido por pantalla
        total_Lines.append(lines[i]);
        total_Lines.append("\n");
    }
    return total_Lines;
}

Archivo *MainWindow::buscarArchivo(char *filename)
{
    Archivo* archivo = nullptr;

    for(std::vector<Archivo*>::iterator it = this->archivos.begin();it != this->archivos.end(); ++it){
        archivo = *it;
        if(strcmp(archivo->getPath(), filename)==0)
            break;
    }
    return archivo;
}

QString MainWindow::insertarPosicionLineaOcurrencias(Archivo *archivo)
{
    int totalOcurrencias;
    QString contenidoTablaOcurrencias;
    totalOcurrencias = archivo->ocurrencia->getTotalOcurrencias();

    archivo->ocurrencia->setOcurrencia(this->ocurrencia);
    archivo->ocurrencia->setRutaArchivoBinario(this->path);
    std::vector<ocurrenciaStruct> vecOcurrencias = archivo->ocurrencia->getLinea_yPos(archivo->getNombre());

    if(!vecOcurrencias.empty()){
        for(int i=0; i<totalOcurrencias; i++){
            //Linea y posicion donde se encontro la ocurrencia
            contenidoTablaOcurrencias.prepend(QString::number(vecOcurrencias[i].pos)+"\t"+QString::number(vecOcurrencias[i].linea)+"\n");
        }
    }
    contenidoTablaOcurrencias.prepend("Posicion\tLinea\n");
    return contenidoTablaOcurrencias;
}

void MainWindow::on_pushButton_clicked()
{
    this->ui->tableView->show();
    this->ui->mostrarArchivo->hide();
    this->ui->ocurrenciasFinded->hide();
    this->ui->nombreArchivo->hide();
    this->ui->pushButton->hide();
}


void MainWindow::on_buttonSaveChanges_clicked()
{
    this->guardarArchivo = true;
    this->ocultarGraficosDeGuardado();
    this->ui->labelChangesSaved->show();
    this->ui->botonBuscar->click();
    this->ui->tableView->show();
}

void MainWindow::ocultarGraficosDeGuardado()
{
    this->ui->labelSaveChanges->hide();
    this->ui->buttonSaveChanges->hide();
    this->ui->buttonDontSaveChanges->hide();
}

void MainWindow::on_buttonDontSaveChanges_clicked()
{
    this->guardarArchivo = false;
    this->ocultarGraficosDeGuardado();
    this->ui->labelUnsavedChanges->show();
    this->ui->tableView->show();
}

void MainWindow::on_buttonUpdate_clicked()
{
    actualizarArchivo = true;
    this->ui->labelChangesSaved->show();
    this->ui->labelUnsavedChanges->hide();
    this->ui->botonBuscar->click();
    this->ui->tableView->show();
}

void MainWindow::on_buttonNoUpdate_clicked()
{
    actualizarArchivo = false;
    this->ui->labelUpdate->hide();
    this->ui->buttonUpdate->hide();
    this->ui->buttonNoUpdate->hide();
     this->ui->labelChangesSaved->hide();
    this->ui->labelUnsavedChanges->show();
    this->ui->tableView->show();
}

QByteArray MainWindow::ignorarPreposiciones(QByteArray ocurrencia){
    std::string cadena;
    std::ifstream file;
    file.open("ocurrencias.txt");

    if(file.is_open()){
        while(std::getline(file,cadena))
        {
                ocurrencia.replace(cadena.c_str(), "");
                ocurrencia.append(" ");
                ocurrencia.prepend(" ");
        }
    }
    file.close();

    ocurrencia = ocurrencia.trimmed();
    return ocurrencia;
}

bool MainWindow::fileExist(std::string filename)
{
    std::ifstream file(filename, std::ios::binary);
    bool good = file.good();
    file.close();
    return good;
}

void MainWindow::insertarEnBinario()
{
     std::ofstream binaryFileWrite(nombreArchivoBinario,std::ios::binary | std::ios::out | std::ios::app);
    Archivo* archivo;
     ArchivoStruct structArch;

    for(std::vector<Archivo*>::iterator it = this->archivos.begin(); it != this->archivos.end(); ++it){
        archivo = *it;
        structArch = this->returnStruct(archivo);
        binaryFileWrite.write((char*)&structArch, sizeof(structArch));
    }
    binaryFileWrite.close();
}

void MainWindow::extraerDeArchivoBinario()
{
    std::ifstream file(nombreArchivoBinario, std::ios::binary);
    ArchivoStruct archivoStruct;
    Archivo* archivo;
    while(!file.eof()){
        file.read((char*)&archivoStruct, sizeof(archivoStruct));

        if(!file.eof()){
            if(strcmp(archivoStruct.ocurrencia, this->ocurrencia) == 0){
                archivo= new Archivo();
                archivo->setNombre(archivoStruct);
                archivo->setPath(archivoStruct);
                archivo->ocurrencia->setTotalOcurrencias(archivoStruct.totalOcurrencias);
                archivo->ocurrencia->setOcurrencia(archivoStruct);

                this->archivos.push_back(archivo);
             }
        }
    }
    file.close();
}

ArchivoStruct MainWindow::returnStruct(Archivo *archivo)
{
    ArchivoStruct fileStr;
    strcpy(fileStr.path, archivo->getPath());
    strcpy(fileStr.nombre, archivo->getNombre());
    strcpy(fileStr.ocurrencia, this->ocurrencia);
    fileStr.totalOcurrencias = archivo->ocurrencia->getTotalOcurrencias();
    return fileStr;
}
