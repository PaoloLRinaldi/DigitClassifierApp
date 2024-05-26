/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
** 
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>
#include <QFileDialog>
#include <QAction>
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>
#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QFileDialog>
#include <QInputDialog>
#include <QTextStream>
#include <QRect>
#include <QString>
#include <QSize>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <stdexcept>
#include "arr_scale.h"

#include "mainwindow.h"
#include "scribblearea.h"


using std::vector;
using std::ifstream;
using std::cin;
using std::cout;
using std::endl;
using std::clog;
using std::max;
using std::min;
using std::string;

template <typename T>
std::string to_string(T value)
{
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}

vector<vector<double>> transpose(const vector<vector<double>> &v) {
  int sz = v.size();
  vector<vector<double>> ret(sz, vector<double>(sz));
  for (int i = 0; i != sz; ++i)
    for (int j = 0; j != sz; ++j)
      ret[i][j] = v[j][i];
  return ret;
}

MainWindow::MainWindow()
{
    scribbleArea = new ScribbleArea;
    setCentralWidget(scribbleArea);
    
    QFileDialog f(this, tr("Web file"), tr("/storage/emulated/0/Android/data/com.dropbox.android/files/u612100211/scratch/ProgrammiCPaolo/ProgrammiCppPaolo/updated_neural_web_libs/"));
    /*
    f.setOption(QFileDialog::DontUseNativeDialog,true);
    QRect rec = QApplication::desktop()->screenGeometry();
    f.setGeometry(rec);
    */
    f.setOption(QFileDialog::DontUseNativeDialog,true);
    f.setWindowFlags(Qt::Window);
    // f.showFullScreen();
    f.setWindowState(Qt::WindowFullScreen);
    f.exec();
    // f.setWindowState(Qt::WindowMaximized);
    // auto web_file_name = f.getOpenFileName(this, tr("Web file"), tr("/storage/emulated/0/Android/data/com.dropbox.android/files/u612100211/scratch/ProgrammiCPaolo/ProgrammiCppPaolo/updated_neural_web_libs/"), QString(), nullptr, f.options());
    f.setVisible(true);
    auto web_file_name = f.selectedFiles().at(0);
    f.setVisible(false);
    
    try {
      // myweb.load_web("/storage/emulated/0/Android/data/com.dropbox.android/files/u612100211/scratch/ProgrammiCPaolo/ProgrammiCppPaolo/updated_neural_web_libs/perc_87_629808_layersinfo_784_200_27_trainsz_104000_testsz_20800_traininground_15_web.txt");
      myweb.load_web(web_file_name.toLocal8Bit().constData());
    } catch (std::domain_error e) {
      QMessageBox::about(this, tr("Error"), tr(e.what()));
    }
    
    QMessageBox::StandardButton reply;
  reply = QMessageBox::question(this, "Transpose", "Transpose input?",
                                QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) do_transpose = true;
    else do_transpose = false;
    
    QInputDialog ind(this);
    ind.setLabelText(tr("What type of classification?"));
    ind.setComboBoxItems(web_types);
    ind.setWindowFlags(Qt::Window);
    ind.setWindowState(Qt::WindowFullScreen);
    ind.exec();
    ind.setVisible(true);
    web_type = ind.textValue();
    ind.setVisible(false);
    
    // web_type = QInputDialog::getItem(this, tr("What type of classification?"), tr("Yolo"), web_types);
    


    setWindowTitle(tr("Finger Paint"));
    resize(500, 500);


    createActions();
    createMenus();
    createButtons();
    //password_setup();

    double perc = 87.63;
    QMessageBox::about(this, tr("Accuracy"), tr((to_string(perc) + "%").c_str()));

}

/*
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}
*/

/*
void MainWindow::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open File"), QDir::currentPath());
        if (!fileName.isEmpty())
            scribbleArea->openImage(fileName);
    }
}
*/

/*
void MainWindow::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}
*/

QString MainWindow::web_to_str(unsigned int web_out) {
  if (web_type == web_types.at(0)) {
    return tr(to_string(web_out).c_str());
  } else if (web_type == web_types.at(1)) {
    return tr(to_string(static_cast<char>('A' + web_out - 1)).c_str());
  } else if (web_type == web_types.at(2)) {
    
  } else if (web_type == web_types.at(3)) {
    
  } else {
    
  }
  return QString();
}

void MainWindow::recognize() {

    int h = scribbleArea->im_height(),
        w = scribbleArea->im_width();
    int l_max = max (h, w);
    
    vector<vector<double>> unfixed_image(l_max, vector<double>(l_max)), new_image(28, vector<double>(28));
    
    QString msg = tr((to_string(w) + " " + to_string(h)).c_str());
    //QMessageBox::about(this, tr("NUMBER"), msg);
    int x_phase = (l_max - w) / 2,
            y_phase = (l_max - h) / 2;
    for (int i = 0; i != h; ++i)
        for (int j = 0; j != w; ++j)
            unfixed_image[i + y_phase][j + x_phase] = scribbleArea->val(i, j);

    //clog << "Tradotto schermo in matrice" << endl;

    if(!arr_shrink2(new_image, 28, unfixed_image, centered_mat_coords(unfixed_image, l_max, l_max))){
      QMessageBox::about(this, tr("ERROR"), tr("No image found!"));
      return;
    }
    if (do_transpose) new_image = transpose(new_image);
    
    //QMessageBox::about(this, tr("NUMBER"), tr("yo"));

    //clog << "Shrinkato" << endl;
    vector<double> input;

    for (vector<vector<double>>::size_type j = 0; j != new_image.size(); ++j)
        std::copy(new_image[j].begin(), new_image[j].end(), std::back_inserter(input));

    //clog << "Reso vettore monodimensionale" << endl;
    //QMessageBox::about(this, tr("NUMBER"), tr("yo"));

    vector<double> answer = myweb.ask_output_layer(input);
    //QMessageBox::about(this, tr("NUMBER"), tr("yo"));

    //clog << "Preso output" << endl;
    std::map<double, unsigned int> ordered_answer;
    for (unsigned int j = 0; j != answer.size(); ++j)
        ordered_answer[answer[j]] = j;

    //clog << "Messo tutto nella mappa" << endl;
    
    // Questo controllo perché nel caso di Letters A = a ho che
    // il neurone 0 non è niente e se dovesse essere selezionato
    // voglio che la risposta sia la seconda, non la prima
    if (web_type == web_types.at(1) && ordered_answer.rbegin()->second == 0) {
      auto it = ordered_answer.rbegin();
      ++it;
      QMessageBox::about(this, tr("RESULT"), web_to_str(it->second));
    } else {
      QMessageBox::about(this, tr("RESULT"), web_to_str(ordered_answer.rbegin()->second));
    }
    //QMessageBox::about(this, tr("NUMBER"), tr("5"));

    //Ora preparo il messaggio con i vari pesi
    /*
    msg = tr(("0 = " + to_string(std::floor(*answer.begin() * 1000) / 1000) +
              "\n1 = " + to_string(std::floor(*(answer.begin() + 1) * 1000) / 1000) +
              "\n2 = " + to_string(std::floor(*(answer.begin() + 2) * 1000) / 1000) +
              "\n3 = " + to_string(std::floor(*(answer.begin() + 3) * 1000) / 1000) +
              "\n4 = " + to_string(std::floor(*(answer.begin() + 4) * 1000) / 1000) +
              "\n5 = " + to_string(std::floor(*(answer.begin() + 5) * 1000) / 1000) +
              "\n6 = " + to_string(std::floor(*(answer.begin() + 6) * 1000) / 1000) +
              "\n7 = " + to_string(std::floor(*(answer.begin() + 7) * 1000) / 1000) +
              "\n8 = " + to_string(std::floor(*(answer.begin() + 8) * 1000) / 1000) +
              "\n9 = " + to_string(std::floor(*(answer.begin() + 9) * 1000) / 1000)).c_str());
    */
    QString out_lay;
    for (auto it = ordered_answer.rbegin(); it != ordered_answer.rend(); ++it) {
      if (web_type == web_types.at(1) && it->second == 0) continue;
      out_lay += web_to_str(it->second) + tr((" = " + to_string(std::floor(it->first * 1000) / 1000) + "\n").c_str());
    };
    
    QMessageBox::about(this, tr("OUTPUT LAYER"), out_lay);
    
    //clog << "Printo!" << endl;
}



void MainWindow::about()
{
    QMessageBox::about(this, tr("About Scribble"),
            tr("<p>The <b>Scribble</b> example shows how to use QMainWindow as the "
               "base widget for an application, and how to reimplement some of "
               "QWidget's event handlers to receive the events generated for "
               "the application's widgets:</p><p> We reimplement the mouse event "
               "handlers to facilitate drawing, the paint event handler to "
               "update the application and the resize event handler to optimize "
               "the application's appearance. In addition we reimplement the "
               "close event handler to intercept the close events before "
               "terminating the application.</p><p> The example also demonstrates "
               "how to use QPainter to draw an image in real time, as well as "
               "to repaint widgets.</p>"));
}

void MainWindow::createActions()
{
    //openAct = new QAction(tr("&Open..."), this);
    //openAct->setShortcut(tr("Ctrl+O"));
    //connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    /*
    foreach (QByteArray format, QImageWriter::supportedImageFormats()) {
        QString text = tr("%1...").arg(QString(format).toUpper());

        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        saveAsActs.append(action);
    }
    */

    //printAct = new QAction(tr("&Print..."), this);
    //connect(printAct, SIGNAL(triggered()), scribbleArea, SLOT(print()));

    //exitAct = new QAction(tr("E&xit"), this);
    //exitAct->setShortcut(tr("Ctrl+Q"));
    //connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    //clearScreenAct = new QAction(tr("&Clear Screen"), this);
    //clearScreenAct->setShortcut(tr("Ctrl+L"));
    //connect(clearScreenAct, SIGNAL(triggered()),
    //        scribbleArea, SLOT(clearImage()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));


    recogAct = new QAction(tr("&Recognize"), this);
    connect(recogAct, SIGNAL(triggered()), this, SLOT(recognize()));
        
}

void MainWindow::createMenus()
{
    //saveAsMenu = new QMenu(tr("&Save As"), this);
    //foreach (QAction *action, saveAsActs)
    //    saveAsMenu->addAction(action);

    //fileMenu = new QMenu(tr("&File"), this);
    //fileMenu->addAction(openAct);
    //fileMenu->addMenu(saveAsMenu);
    //fileMenu->addAction(printAct);
    //fileMenu->addSeparator();
    //fileMenu->addAction(exitAct);
    //fileMenu->addAction(recogAct);

    //optionMenu = new QMenu(tr("&Options"), this);
    //optionMenu->addAction(clearScreenAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    //menuBar()->addMenu(fileMenu);
    //menuBar()->addMenu(optionMenu);
    //menuBar()->addMenu(helpMenu);  //QUESTA RIGA SERVE PER METTERE IL MENU. L'HO COMMENTATA PERCHE' PER IL MOMENTO NON LO VOLEVO. TOGLIERE IL COMMENTO PER RIMETTERE IL MENU
}

void MainWindow::createButtons() {
    /*
    buttonRecog = new QPushButton(tr("&Recognize"), this);
    buttonRecog->resize(200, 100);
    buttonRecog->move(10, 10);
    connect(buttonRecog, SIGNAL(released()), this, SLOT(recognize()));

    buttonClear = new QPushButton(tr("&Clear"), this);
    buttonClear->resize(200, 100);
    buttonClear->move(500, 10);
    connect(buttonClear, SIGNAL(released()), scribbleArea, SLOT(clearImage()));
    */


    QRect rec = QApplication::desktop()->screenGeometry();
    int ButtonHeight = rec.height() / 12;
    int ButtonWidth = rec.width() / 3;

    //int ButtonHeight = scribbleArea->QWidget::geometry().height() / 15;
    //int ButtonWidth = scribbleArea->QWidget::geometry().width() / 4;
    //int ButtonHeight = scribbleArea->im_height() / 15;
    //int ButtonWidth = scribbleArea->im_width() / 4;
    //QMessageBox::about(this, tr("H W"), tr((to_string(ButtonHeight) + " " + to_string(ButtonWidth)).c_str()));
    buttonRecog = new QPushButton(tr("&Recognize"), this);
    buttonRecog->resize(ButtonWidth, ButtonHeight);
    buttonRecog->move(0, 0);
    connect(buttonRecog, SIGNAL(released()), this, SLOT(recognize()));

    buttonClear = new QPushButton(tr("&Clear"), this);
    buttonClear->resize(ButtonWidth, ButtonHeight);
    buttonClear->move(2 * ButtonWidth, 0);
    connect(buttonClear, SIGNAL(released()), scribbleArea, SLOT(clearImage()));

    /*
    int Height = rec.height();
    int Width = rec.width();

    askPass = new QLineEdit(tr("&Password"));
    //askPass->resize(Width / 2, Height / 20);
    //askPass->move(Width / 4, Height / 2 - 2 * askPass->height());

    askPass->resize(ButtonWidth, ButtonHeight);
    askPass->move(ButtonWidth, 0);

    writePass = new QLineEdit(tr(""));
    writePass->resize(Width / 2, Height / 20);
    writePass->move(Width / 4, Height / 2 + 2 * writePass->height());
*/
}

/*
bool MainWindow::maybeSave()
{
    if (scribbleArea->isModified()) {
       QMessageBox::StandardButton ret;
       ret = QMessageBox::warning(this, tr("Scribble"),
                          tr("The image has been modified.\n"
                             "Do you want to save your changes?"),
                          QMessageBox::Save | QMessageBox::Discard
                          | QMessageBox::Cancel);
        if (ret == QMessageBox::Save) {
            return saveFile("png");
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}
*/

/*
bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(QString(fileFormat.toUpper()))
                               .arg(QString(fileFormat)));
    if (fileName.isEmpty()) {
        return false;
    } else {
        return scribbleArea->saveImage(fileName, fileFormat);
    }
}
*/



void MainWindow::password_setup() {

    buttonRecog->hide();
    buttonClear->hide();
    scribbleArea->make_unprintable();

    QRect rec = QApplication::desktop()->screenGeometry();
    int Height = rec.height();
    int Width = rec.width();

    askPass = new QLineEdit(tr("Insert Password Below"), this);
    askPass->resize(Width, Height / 20);
    askPass->move(0, Height / 2 - 2 * askPass->height());
    askPass->setReadOnly(true);

    writePass = new QLineEdit(tr(""), this);
    writePass->resize(Width / 2, Height / 20);
    writePass->move(Width / 4, Height / 2 + 2 * writePass->height());

    //while (writePass->text() != tr("neuralnetwoRk"));


    begin = new QPushButton(tr("Begin"), this);
    begin->resize(Width / 3, Height / 15);
    begin->move(Width / 4, writePass->pos().y() + 2 * writePass->height());
    //begin->move(Width / 4, Height / 2 + 4 * writePass->height());
    connect(begin, SIGNAL(released()), this, SLOT(verify_password()));

}

void MainWindow::verify_password() {
    if (writePass->text() == tr("0839"))
        start_all();
    else {
        writePass->setText(tr(""));
        QMessageBox::about(this, tr("Wrong"), tr("Ecco."));
    }
}

void MainWindow::start_all() {
    askPass->hide();
    writePass->hide();
    begin->hide();
    buttonClear->show();
    buttonRecog->show();
    scribbleArea->make_printable();
}
