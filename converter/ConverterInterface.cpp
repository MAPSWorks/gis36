﻿#include <QtGui>
#include <QtXmlPatterns/QXmlQuery>
#include <qlayout.h>
#include "ConverterInterface.h"
#include <iostream>

ConverterInterface::ConverterInterface(QWidget *parent)
    : QDialog(parent){

    labelbox = new QLabel(tr("Выберите файл: "));
    box = new QComboBox(false);
    findButton = new QPushButton(tr("Open..."));
    labelbox->setBuddy(box);

    //stringList << "examplemap.xml" << "mapch.xml";
    //box->addItems(stringList);
    box->setEditable(true);

    connect(findButton, SIGNAL(clicked()), this, SLOT(OnFindButton()));

    okButton = new QPushButton(tr("Do it!"));
    okButton->setDefault(true);
    okButton->setEnabled(true);

    process = new QTextEdit();
    process->setReadOnly(true);
    lib = new ConverterLibrary();

    connect(findButton, SIGNAL(clicked()), process, SLOT(clear()));
   // connect(findButton, SIGNAL(clicked()), box, SLOT(clearEditText()));
    connect(okButton, SIGNAL(clicked()), this, SLOT(OnOkButton()));
    connect(box, SIGNAL(activated(int)), process, SLOT(clear()));

    closeButton = new QPushButton(tr("Close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *upperLayout = new QHBoxLayout;
    upperLayout->addWidget(labelbox);
    upperLayout->addWidget(box);
    upperLayout->addWidget(findButton);


    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addSpacing(180);
    topLayout->addWidget(okButton);
    topLayout->addSpacing(180);

    QVBoxLayout *middleLayout = new QVBoxLayout;
    middleLayout->addLayout(upperLayout);
    middleLayout->addLayout(topLayout);
    middleLayout->addWidget(process);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addSpacing(360);
    bottomLayout->addWidget(closeButton);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(middleLayout);
    mainLayout->addLayout(bottomLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Converter"));
    setFixedSize(QSize(500, 500));
}

void ConverterInterface::OnOkButton(){

    QString str = "";

    if(lib)
    {
        str = QString::QString(lib->Parser(box->currentText()));
    }else
        str = tr("Соедиенение с ConverterLibrary не осуществлено!");

    QTextCursor cursor = process->textCursor();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText(str);
    process->setText(str);
}

void ConverterInterface::OnFindButton(){
    QString fileName = QFileDialog::getOpenFileName(this,
                                                     tr("Выберите файл OSM"),
                                                    "../osm/",
                                                    tr("Файлы OpenStreetMap (*.xml)"));
    int currentInd = box->findText(fileName);

    if (currentInd == -1){

        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::critical(this, tr("Ошибка"),
                                tr("Невозможно открыть файл"),
                                      QMessageBox::Ok);
                return;
            }
            //QString contents = file.readAll().constData();
            box->setEditText(fileName);
            box->addItem(fileName);
            file.close();
        }
    }else{
        box->setEditText(fileName);
    }
}




