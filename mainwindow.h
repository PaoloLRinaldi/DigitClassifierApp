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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>
//#include <QButtonGroup>
#include <QPushButton>
#include <QString>
#include <QStringList>
#include <QLineEdit>
//#include <QPlainTextEdit>
#include "neural_web.h"

class ScribbleArea;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    //void closeEvent(QCloseEvent *event);

private slots:
    //void open();
    //void save();
    void about();
    void recognize();
    void verify_password();


private:
    void createActions();
    void createMenus();
    void createButtons();  //aggiunto io
    //bool maybeSave();
    //bool saveFile(const QByteArray &fileFormat);
    void password_setup();
    void start_all();
    QString web_to_str(unsigned int);


    ScribbleArea *scribbleArea;

    //QMenu *saveAsMenu;
    //QMenu *fileMenu;
    //QMenu *optionMenu;
    QMenu *helpMenu;

    //QAction *openAct;
    //QList<QAction *> saveAsActs;
    //QAction *exitAct;
    //QAction *printAct;
    //QAction *clearScreenAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *recogAct;

    QPushButton *buttonRecog;
    QPushButton *buttonClear;
    QLineEdit *askPass;
    QLineEdit *writePass;
    QPushButton *begin;
    
    bool do_transpose;
    QString web_type;
    QStringList web_types = {"Digits", "Letters (A = a)", "Letters (A != a)", "Digits + letters (A = a)", "Digit + letters (A != a)"};

    NeuralWeb myweb;
};

#endif
