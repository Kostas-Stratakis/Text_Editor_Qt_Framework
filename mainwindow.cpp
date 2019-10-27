#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentfile.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename= QFileDialog::getOpenFileName(this,"Open something");

    QFile file (filename);
    currentfile=filename;
    if(!file.open(QIODevice::ReadOnly | QFile:: Text   )){
        QMessageBox::warning(this, "Warningg","cannot op file" +file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text= in.readAll();
    ui->textEdit->setText(text);
    file.close();

}

void MainWindow::on_actionsave_as_triggered()
{
    QString filename=QFileDialog::getSaveFileName(this,"Save it");
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile:: Text   )){
        QMessageBox::warning(this, "Warningg","cannot save file" +file.errorString());
        return;
    }
    currentfile=filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out<<text;
    file.close();

}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Printer Name");
    QPrintDialog pdial(&printer, this);
    if(pdial.exec()==QDialog::Rejected){
        QMessageBox::warning(this, "Warning", "Cannot access printer");
        return;
    }
    ui->textEdit->print(&printer);
}



void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
     ui->textEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
     ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
     ui->textEdit->redo();
}
