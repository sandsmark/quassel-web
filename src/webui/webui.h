/***************************************************************************
 *   Copyright (C) 2005-2010 by the Quassel Project                        *
 *   devel@quassel-irc.org                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) version 3.                                           *
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

#ifndef WEBUI_H
#define WEBUI_H


#include "abstractui.h"

#include <Wt/WApplication>

class CoreAccount;
using namespace Wt;

class WebMessageModel;

class WebUi : public AbstractUi
{
  Q_OBJECT

public:
  WebUi(WApplication *app);
  ~WebUi();

  MessageModel* createMessageModel(QObject*);
  AbstractMessageProcessor* createMessageProcessor(QObject*);

  virtual void init() {}

private Q_SLOTS:
    void userAuthenticationRequired(CoreAccount*,bool*,QString);
    void connected();
    void printMsg(QString);

private:
  void connect();
  WTableView *_chatView;
  WLineEdit *_inputWidget;
  WebMessageModel *_messageModel;
  WPushButton *m_loginButton;
  WApplication *m_app;
};

#endif
