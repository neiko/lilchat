/***************************************************************************
 *   lilchat.cpp - Main lilChat GUI code                                   *
 *   Copyright (C) 2009 by Nost                                            *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include "lilchat.h"
#include "ui_lilchat.h"
#include "clientcore.h"
#include "servercore.h"
#include <iostream>
#include <QMessageBox>
#include <QString>
#include <QValidator>
using namespace std;

int iRole = -1; // -1 invalid; 0 server; 1 client

lilChat::lilChat(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::lilChatClass)
{
    ui->setupUi(this);
    setWindowTitle("Little Chat v0.1");
    iRole = 0;
    QIntValidator *portValidator = new QIntValidator( 1, 65535, this );
    ui->txtPort->setValidator(portValidator);
    ui->txtChat->setText("<table><tr><td align=\"right\"><font color=\"gray\">&rarr;</font> \
                     </td><td><font color=\"gray\">Welcome to lilChat v0.1</td></tr>");
}

lilChat::~lilChat()
{
    delete ui;
}

void lilChat::on_btnClient_clicked()
{
    ui->txtHost->setReadOnly(false);
    ui->txtPort->setReadOnly(false);
    iRole = 1;
}

void lilChat::on_btnServer_clicked()
{
    ui->txtHost->setReadOnly(true);
    ui->txtPort->setReadOnly(true);
    iRole = 0;
}

void lilChat::on_btnConnect_clicked()
{
    switch (iRole)
    {
        case 0:
            lilChat::startAsServer();
            break;
        case 1:
            lilChat::startAsClient();
            break;
        default:
            //wtf?
            ;
    }
    ui->txtChat->setText(chat);
}

void lilChat::on_txtMessage_returnPressed()
{
    // sendChatMsg(blblalbalba);
    if (ui->txtMessage->text().compare(""))
    {
        chat.append("<tr><td><b>You:</b></td><td>");
        chat.append(ui->txtMessage->text());
        chat.append("</td></tr>");
    } else {
        // TODO: es realmente necesario este error? :b
        chat.append("<tr><td align=\"right\"><font color=\"gray\">&rarr;</font> \
                    </td><td><font color=\"gray\">Won't send a blank message!</td></tr>");
    }
    ui->txtChat->setText(chat);
    ui->txtMessage->setText("");
}

void lilChat::incomingMessage(QString Message)
{
    // generic? why?
    // TODO: nicknames
    chat.append("<tr><td><b>He:</b></td><td>");
    chat.append(Message);
    chat.append("</td></tr>");
    ui->txtChat->setText(chat);
}

void lilChat::setDisplayPort(int port)
{
    ui->txtPort->setText(QString::number(port));
}

void lilChat::gotConnection()
{
    chat.append("<tr><td align=\"right\"><font color=\"gray\">&rarr;</font> \
             </td><td><font color=\"gray\">Got connection!</td></tr>");
    ui->txtChat->setText(chat);
}

void lilChat::startAsServer()
{
    serverCore *S = new serverCore();
    QObject::connect(S, SIGNAL(incomingMessageS(QString)), this, SLOT(incomingMessage(QString)));
    QObject::connect(S, SIGNAL(newConnectionS()), this, SLOT(gotConnection()));
    chat.append("<tr><td align=\"right\"><font color=\"gray\">&rarr;</font> \
             </td><td><font color=\"gray\">Server created at port ");
    chat.append(S->getPort());
    chat.append("...</td></tr>");
    ui->txtPort->setText(S->getPort());
}

void lilChat::startAsClient()
{
    if (!ui->txtPort->text().compare("") || !ui->txtHost->text().compare(""))
    {
        QMessageBox msgBox;
        msgBox.setText("Host and port fields cannot be empty.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
        return;
    }
    chat.append("<tr><td align=\"right\"><font color=\"gray\">&rarr;</font> \
             </td><td><font color=\"gray\">Attempting to connect to host ");
    chat.append(ui->txtHost->text());
    chat.append(", port ");
    chat.append(ui->txtPort->text());
    chat.append("...</tr></td>");
    // conectarse a host/puerto etc etc
    // si va bien se añade un "muy bien, conexión efectuada a %Q en %Q"
    ui->btnConnect->setDisabled(true);
    ui->btnConnect->setText("Connecting");
}

