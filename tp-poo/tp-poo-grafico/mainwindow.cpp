#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <string>
#include <QStandardItemModel>
#include "pila.h"
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
    /*QPalette Pal(palette());
    Pal.setColor(QPalette::Background, "#4f4f4f");
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
    this->show();*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool ordenar(Archivo *archivo1, Archivo *archivo2)
{
    return archivo1->ocurrencia->getCantOcurrencias() > archivo2->ocurrencia->getCantOcurrencias();
}


void MainWindow::on_botonBuscar_clicked()
{
    if(!this->fileExist("indices.dat") && !this->guardarArchivo){
        this->ui->labelSaveChanges->show();
        this->ui->buttonSaveChanges->show();
        this->ui->buttonDontSaveChanges->show();
    }

    //Limpia la tableView
    this->ui->tableView->reset();
    this->archivos.clear();

    //Tamanio ocurrencia
    this->longOcu = this->ui->ocurrencia->text().length();
    this->ocurrencia = new char[this->longOcu+1];

    //Extrayendo valor ocurrencia
    QByteArray ocu = this->ui->ocurrencia->text().toLatin1();
    ocu = ignorarPreposiciones(ocu);
    this->ocurrencia = ocu.data();

    int i = 0;
    //Extraigo el valor del campo del tipo QString y lo convierto a QByteArray para luego manejarlo como char*
    QByteArray conversionRuta = ui->rutaDirectorio->text().toLatin1();

    //reservo memoria para path
    int tamanio = conversionRuta.length();
    this->path = new char[tamanio+1];
    //Convierto a char* conversionRuta y se lo asigno a path
    this->path = conversionRuta.data();

    //inicializo el directorio a mostrar ...
    this->directorio = new Directorio();
    this->directorio->setListaArchivos(path);

    QStandardItemModel * model = new QStandardItemModel();
    //Columnas del modelo de la tabla
    model->setColumnCount(3);
    model->setHorizontalHeaderItem(0, new QStandardItem("Archivos"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Caracteres"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Ocurrencias"));

    //Obtengo la lista de archivos que se encuentran en el directorio
    char** listaArchivos = this->directorio->getArchivos();
    int cantArchivos = directorio->getCantArchivos();
    delete this->directorio;

    if(!fileExist("indices.dat")){

        //Recorro la variables listaArchivos y creo los items de la tabla
        for(int j=0; j<cantArchivos; j++){

            QString archivoNombre = listaArchivos[j];
            //Instancio objeto de archivo
            Archivo* archivo= new Archivo();

            //seteo el nombre del archivo que voy a usar para mostrarlo en los item del modelo
            int tamanioNombre = archivoNombre.length()+1;
            char* nombre = new char[tamanioNombre];

            nombre = strcpy(nombre, archivoNombre.toLatin1().data());
            archivo->setNombre(nombre);

            //tamanio del char* , el +2 representa al \\ y al caracter nulo
            int tamanioPath = conversionRuta.length() + archivoNombre.length() + 2;

            //Reservar memoria a char* filename y concatenacion del nombre del archivo
            char* filename ;

            filename = new char[tamanioPath];
            filename = strcpy(filename, conversionRuta.data() );
            filename = strcat(filename, "\\");
            filename = strcat(filename, archivoNombre.toLatin1().data());

            //Seteo el path del archivo
            archivo->setPath(filename);

            //columna de ocurrencias
            archivo->ocurrencia->setTamanioOcu(ocu.length());
            archivo->ocurrencia->setOcurrencia(this->ocurrencia);

            //Le paso true por parametro para que cuente las ocurrencias
            archivo->setearOcurrencias(filename);

            //Asigno el archivo creado por cada iteracion a un indice del arreglo de archivos
            this->archivos.push_back(archivo);

        }

          if(this->guardarArchivo){
              this->insertarEnBinario();
          }



    }else{
        this->extraerDeArchivoBinario();
    }


    std::sort(this->archivos.begin(), this->archivos.end(), &ordenar);

        i=0;

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
               model->setItem(i, 2, new QStandardItem(QString::number(archivoIt->ocurrencia->getCantOcurrencias())));
               i++;

        }


    this->ui->tableView->setModel(model);
        //ajusto el largo de las columnas para que se adapten al contenido
    this->ui->tableView->resizeColumnToContents(0);
    this->ui->tableView->resizeColumnToContents(1);
    this->ui->tableView->resizeColumnToContents(2);
    this->ui->tableView->show();

}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    this->ui->labelUnsavedChanges->hide();
    this->ui->labelChangesSaved->hide();
    this->ui->nombreArchivo->show();
    this->ui->pushButton->show();
    //seteo vacio el QTextEdit por si quiero abrir otro archivo de texto a mostrar
    this->ui->mostrarArchivo->setText("");
    this->ui->ocurrenciasFinded->setText("");
    this->ui->ocurrenciasFinded->hide();
    this->ui->mostrarArchivo->hide();
    //seteo el nombre del archivo en el label superior al QTextEdit("mostrarArchivo")
    QString nombreArchivo = this->ui->tableView->model()->data(index).toString();

    //Comprueba de que se haga doble click sobre la columna donde esta el nombre del archivo y no en las demas
    if(index.column() == 0){
        this->ui->nombreArchivo->setText(nombreArchivo);
        //Extraer el item de la tabla en formato string
        std::string item = this->ui->tableView->model()->data(index).toString().toStdString();

        //Defino filename y reservo memoria con el tamanio que va a ocupar el arreglo de char
        char* filename = nullptr;
        int tamanio = this->ui->rutaDirectorio->text().length() + item.length() + 2;

        filename = new char[tamanio];
        //Concatenacion del nombre del archivo, antes de concatenar debo convertirlos a un puntero de char
        filename = strcpy(filename, this->ui->rutaDirectorio->text().toLatin1().data());
        filename = strcat(filename, "\\");
        filename = strcat(filename, item.c_str());

        Archivo* archivo = new Archivo();

        //Lineas del archivo de texto contenidas en un char**
        char** lines = archivo->getLines(filename);

        //Cantidad de lineas del archivo
        int cantLines = archivo->getCantLines();

        QString total_Lines;
        for(int i=0; i<cantLines; i++){
            //Inserto linea a linea en la variable va a mostrar su contenido por pantalla
            total_Lines.append(lines[i]);
            total_Lines.append("\n");
        }

        this->ui->mostrarArchivo->setText(total_Lines);
        this->ui->mostrarArchivo->show();

        //Si se hace doble click en la columna de ocurrencias
        this->longOcu = this->ui->ocurrencia->text().length();
        this->ocurrencia = new char[longOcu+1];
        QByteArray ocu = this->ui->ocurrencia->text().toLatin1();
        this->ocurrencia = ocu.data();

        //Busca el archivo para poder abrirlo luego
        for(std::vector<Archivo*>::iterator it = this->archivos.begin();it < this->archivos.end(); ++it){
            Archivo* archivoIt = *it;
            if(strcmp(archivoIt->getPath(), filename)==0){
                archivo = archivoIt;
                break;
            }
        }


        QString aInsertar;
        int cantNodos = archivo->ocurrencia->getCantOcurrencias();

        archivo->ocurrencia->setOcurrencia(this->ocurrencia);
        std::vector<ocurrenciaStruct> vecOcurrencias = archivo->ocurrencia->getLinea_yPos(archivo->getNombre());

        if(!vecOcurrencias.empty()){
            for(int i=0; i<cantNodos; i++){
                //Linea y posicion donde se encontro la ocurrencia
                aInsertar.prepend(QString::number(vecOcurrencias[i].pos)+"\t"+QString::number(vecOcurrencias[i].linea)+"\n");
            }
        }
        aInsertar.prepend("Posicion\tLinea\n");

        this->ui->ocurrenciasFinded->setText(aInsertar);
        this->ui->ocurrenciasFinded->show();
    }
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
     std::ofstream binaryFileWrite("indices.dat",std::ios::binary | std::ios::out | std::ios::app);
    Archivo* archivo;

    for(std::vector<Archivo*>::iterator it = this->archivos.begin(); it != this->archivos.end(); ++it){
        archivo = *it;
        ArchivoStruct structArch = this->returnStruct(archivo);
        binaryFileWrite.write((char*)&structArch, sizeof(structArch));
    }
    binaryFileWrite.close();
}

void MainWindow::extraerDeArchivoBinario()
{
    std::ifstream file("indices.dat", std::ios::binary);
    ArchivoStruct archivoStruct;

    while(!file.eof()){
        file.read((char*)&archivoStruct, sizeof(archivoStruct));

        if(!file.eof()){
            if(strcmp(archivoStruct.ocurrencia, this->ocurrencia) == 0){
                Archivo* archivo= new Archivo();
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
    fileStr.totalOcurrencias = archivo->ocurrencia->getCantOcurrencias();
    return fileStr;
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
}
