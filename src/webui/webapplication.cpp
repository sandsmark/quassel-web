/***************************************************************************
 *   Copyright (C) 2005-09 by the Quassel Project                          *
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

#include <Wt/WEnvironment>
#include "webapplication.h"
#include "webui.h"
#include "client.h"

#include "wqapplication.h"

using namespace Wt;


// We need this because of the retarded Wt architecture
class WebApplicationSpawner : public Wt::WQApplication
{
public:
    WebApplicationSpawner(Wt::WEnvironment);
    virtual void create();
    virtual void destroy();
private:
    WebUi *m_ui;
};


static WApplication *createApplication(const WEnvironment& env)
{
    WebApplicationSpawner *app = new WebApplicationSpawner(env);
    return app;
}

WebApplication::WebApplication(int &argc, char **argv) :
  //: QCoreApplication(argc, argv),
    Quassel(),
    m_argc(argc),
    m_argv(argv)
{
#ifdef Q_OS_MAC
  disableCrashhandler();
#endif /* Q_OS_MAC */
  setRunMode(Quassel::Web);
  for (int i=0; i<argc; i++) {
      m_arguments.append(QString::fromLocal8Bit(argv[i]));
  }
}

WebApplication::~WebApplication()
{
}

void WebApplicationSpawner::create()
{
    m_ui = new WebUi(this);
}

void WebApplicationSpawner::destroy()
{
    delete m_ui;
}

WebApplicationSpawner::WebApplicationSpawner(WEnvironment env): WQApplication(env)
{
}

bool WebApplication::exec()
{
    return Wt::WRun(m_argc, m_argv, &createApplication);
}

/*bool WebApplicationSpawner::notify(QObject* receiver, QEvent* event)
{
    try {
        return QCoreApplication::notify(receiver, event);
    } catch(Wt::WException e) {
        qWarning() << "Got exception:" << e.what();
    }
}*/
