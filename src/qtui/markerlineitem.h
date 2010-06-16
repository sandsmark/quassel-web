/***************************************************************************
 *   Copyright (C) 2010 by the Quassel Project                             *
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

#ifndef MARKERLINEITEM_H_
#define MARKERLINEITEM_H_

#include <QGraphicsObject>

#include "chatscene.h"

class MarkerLineItem : public QGraphicsObject {
  Q_OBJECT

public:
  MarkerLineItem(qreal sceneWidth, QGraphicsItem *parent = 0);
  virtual inline int type() const { return ChatScene::MarkerLineType; }

  inline QRectF boundingRect() const { return _boundingRect; }

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

public slots:
  void sceneRectChanged(const QRectF &);

private slots:
  void styleChanged();

private:
  QRectF _boundingRect;
  QBrush _brush;
};

#endif