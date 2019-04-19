#include "mainwindow.h"
#include "imageviewer.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QGraphicsPixmapItem>
#include <QTimeLine>
#include <QString>
#include <QTextStream>
#include <sys/stat.h>
#include <QDebug>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->statusBar()->showMessage("Ready");
}

MainWindow::~MainWindow()
{
    delete ui;
}

QGraphicsScene* scene;
QString status;
QString fileName;
QImage image;

void MainWindow::on_toolButton_clicked()
{

    fileName = QFileDialog::getOpenFileName(this, "Open the file", nullptr, "Portable Pixmaps (*.ppm);;All files (*.*)");
    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
            return;
        }
        // QMessageBox::information(this, "Open File...", "You are going to open: " + fileName);

        ui->txtSourcePath->setText(fileName);

        image.load(fileName, Q_NULLPTR);

        status.clear();
        QTextStream(&status) << "Image loaded (" << image.width() << "x" << image.height() << ")";

        this->statusBar()->showMessage(status);

        scene = new QGraphicsScene();
        ui->imageView->setScene(scene);
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
        scene->addItem(item);
        ui->imageView->show();

        ui->imageView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

        ui->btnSave->setEnabled(true);


    }

}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   if (scene != nullptr)
       ui->imageView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}



void MainWindow::on_btnSave_clicked()
{
    struct stat buffer;
    if (stat ("../cli/cont", &buffer) != 0) {
        QMessageBox::critical(this, "Contour Highlighter", "Executable cont_cli is not found in this folder!");
        ui->statusBar->showMessage("Executable ../cli/cont is not found in this folder!");
        return;
    }

    if (ui->txtPostfix->text() == ""){
            QMessageBox::critical(this, "Contour Highlighter", "Please provide output filename postfix");
            ui->statusBar->showMessage("Please provide output filename postfix");
            return;
     }

    QString out_fileName_no_extension = fileName.left(fileName.size() - 4) +"_" + ui->txtPostfix->text();

    QProcess process;
    QByteArray process_stdout;

    QStringList args = { fileName, out_fileName_no_extension + ".ppm"};

    if(ui->cbInterm->checkState())
        args << "-i" << out_fileName_no_extension + "_h.ppm" <<  out_fileName_no_extension + "_v.ppm";

    if (ui->rbFormatP3->isChecked())
        args << "-f" << "P3";
    else if (ui->rbFormatP6->isChecked())
        args << "-f" << "P6";

    int threads_n = ui->txtThreads->text().toInt();
    if (threads_n > 1)
        args << "-t" << ui->txtThreads->text();

    process.start("../cli/cont", args);

    process.waitForFinished(100000);

    if (process.exitCode() != 0) {
        process_stdout = process.readAllStandardError();
        QMessageBox::critical(this, "Contour Highlighter", process_stdout);
        ui->statusBar->showMessage(process_stdout);
        return;
    }

    image.load(out_fileName_no_extension + ".ppm", Q_NULLPTR);
    scene->clear();
    scene->addItem(new QGraphicsPixmapItem(QPixmap::fromImage(image)));
    ui->imageView->show();
    ui->statusBar->showMessage("Highlighting the contour done successfully");

    process_stdout = process.readAllStandardOutput();
    QMessageBox::information(this, "Contour Highlighter", process_stdout);
}
