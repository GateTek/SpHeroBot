/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
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

#include "glwidget.h"
#include "window.h"
#include "mainwindow.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <windows.h>

QT_USE_NAMESPACE

QTextStream stout(stdout);

/**
 * @brief Window::Window costruttore di Window
 * @param mw MainWindow
 */
Window::Window(MainWindow *mw)
    : mainWindow(mw)
{
    glWidget = new GLWidget; // oggetto glwidget

    serial = new Serial("COM5");
    Sleep(3000);

    xSlider = createSlider();
    ySlider = createSlider();
    zSlider = createSlider();

    // connette wdget e slider asse x
    connect(serial, &Serial::rollChanged, glWidget, &GLWidget::setXRotation);
    connect(glWidget, &GLWidget::xRotationChanged, xSlider, &QSlider::setValue);
    // connette wdget e slider asse y
    connect(serial, &Serial::pitchChange, glWidget, &GLWidget::setYRotation);
    connect(glWidget, &GLWidget::yRotationChanged, ySlider, &QSlider::setValue);
    // connette wdget e slider asse z
    connect(serial, &Serial::yawChange, glWidget, &GLWidget::setZRotation);
    connect(glWidget, &GLWidget::zRotationChanged, zSlider, &QSlider::setValue);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;
    container->addWidget(glWidget);
    container->addWidget(xSlider);
    container->addWidget(ySlider);
    container->addWidget(zSlider);

    QWidget *w = new QWidget;
    w->setLayout(container);
    mainLayout->addWidget(w);
    dockBtn = new QPushButton(tr("Undock"), this);
    connect(dockBtn, &QPushButton::clicked, this, &Window::dockUndock);
    mainLayout->addWidget(dockBtn);

    setLayout(mainLayout);

    xSlider->setValue(15 * 16);
    ySlider->setValue(345 * 16);
    zSlider->setValue(0 * 16);

    setWindowTitle(tr("UAU dovrebbe girare"));

}

/**
 * @brief Window::rollChanged evento emette un segnale roll
 * @param roll float che indica la variazione di roll
 */
void Window::rollChanged(float roll){
    emit rollChanged(roll);
    update();
}

/**
 * @brief Window::pitchChanged evento emette un segnale pitch
 * @param pitch float che indica la variazione di pitch
 */
void Window::pitchChanged(float pitch){
    emit pitchChanged(pitch);
    update();
}

/**
 * @brief Window::yawChanged evento emette un segnale yaw
 * @param yaw float che indica la variazione di yaw
 */
void Window::yawChanged(float yaw){
    emit rollChanged(yaw);
    update();
}

/**
 * @brief Window::setValue imposta i valori roll, pitch, yaw e li mostra sulla finestra di comunicazione seriale
 * @param widget GLWidget  passato come puntatore che indica il GLWidget a cui modificare i valori
 */
void Window::setValue(GLWidget *widget){
    float roll= serial->getRoll();
    float pitch= serial->getPitch();
    float yaw= serial->getYaw();

    widget->setXRotation(roll);
    widget->setYRotation(pitch);
    widget->setZRotation(yaw);

    stout << "roll: " << roll << "      ";
    stout << "pitch: " << pitch << "        ";
    stout << "yaw: " << yaw << endl;
}

/**
 * @brief Window::start esgue all'infinito setValue()
 */
void Window::start(){
    while(true){
        setValue(glWidget);
    }
}

/**
 * @brief Window::createSlider costruttore diQSlider
 * @return QSlider
 */
QSlider *Window::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

void Window::keyPressEvent(QKeyEvent *e) // chiudere con ESC è divertente
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}

void Window::dockUndock() // per separare mainwindow da widgetwindow
{
    if (parent()) {
        setParent(0);
        setAttribute(Qt::WA_DeleteOnClose);
        move(QApplication::desktop()->width() / 2 - width() / 2,
             QApplication::desktop()->height() / 2 - height() / 2);
        dockBtn->setText(tr("Dock"));
        show();
    } else {
        if (!mainWindow->centralWidget()) {
            if (mainWindow->isVisible()) {
                setAttribute(Qt::WA_DeleteOnClose, false);
                dockBtn->setText(tr("Undock"));
                mainWindow->setCentralWidget(this);
            } else {
                QMessageBox::information(0, tr("Cannot dock"), tr("Main window already closed"));
            }
        } else {
            QMessageBox::information(0, tr("Cannot dock"), tr("Main window already occupied"));
        }
    }
}
