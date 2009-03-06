/***************************************************************************
 *   servercore.h - Chat server class header file                          *
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


#ifndef SERVERCORE_H
#define SERVERCORE_H
#include <QTcpServer>
#include <QObject>

// class QTcpServer;

class serverCore : public QObject
{
    Q_OBJECT
    public:
        serverCore();
        QString getPort();
        QTcpServer *tcpServer;
        //bool sendMessageS(QString Message);

    private:

    signals:
        void incomingMessageS(QString);
        void newConnectionS();

    private slots:
        void handleNewData();

    public slots:
        void newConnectionSlot() { emit(newConnectionS()); }
        // QString receiveData() { emit(newConnectionS()); }
};


#endif // SERVERCORE_H
