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

using namespace Wt;

WebApplication::WebApplication(int &argc, char **argv)
  : QCoreApplication(argc, argv), Quassel(),
    m_argc(argc),
    m_argv(argv)
{
#ifdef Q_OS_MAC
  disableCrashhandler();
#endif /* Q_OS_MAC */

  setRunMode(Quassel::Web);
}

WebApplication::~WebApplication()
{
}

bool WebApplication::init()
{
    //int argc = 4;
    //char *argv[4] = { "quasselweb", "--http-port=8080", "--http-addr=127.0.0.1", "--docroot=/home/cassarossa/itk/sandsmark/tmp/wt-3.2.1" };
    if (Quassel::init()) {
        return Wt::WRun(m_argc, m_argv, &createApplication);
    } else {
        return false;
    }
}

WApplication *WebApplication::createApplication(const WEnvironment& env)
{
    WebUi *app = new WebUi(env);
    return app;
}


