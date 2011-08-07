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

#ifndef BACKLOGMANAGER_H
#define BACKLOGMANAGER_H

#include "syncableobject.h"
#include "types.h"

class BacklogManager : public SyncableObject {
  SYNCABLE_OBJECT
  Q_OBJECT

public:
  BacklogManager(QObject *parent = 0) : SyncableObject(parent) {}
  inline virtual const QMetaObject *syncMetaObject() const { return &staticMetaObject; }

public Q_SLOTS:
  virtual QVariantList requestBacklog(BufferId bufferId, MsgId first = -1, MsgId last = -1, int limit = -1, int additional = 0);
  inline virtual void receiveBacklog(BufferId, MsgId, MsgId, int, int, QVariantList) {};

  virtual QVariantList requestBacklogAll(MsgId first = -1, MsgId last = -1, int limit = -1, int additional = 0);
  inline virtual void receiveBacklogAll(MsgId, MsgId, int, int, QVariantList) {};

Q_SIGNALS:
  void backlogRequested(BufferId, MsgId, MsgId, int, int);
  void backlogAllRequested(MsgId, MsgId, int, int);
};

#endif // BACKLOGMANAGER_H
