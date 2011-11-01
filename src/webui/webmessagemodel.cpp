#include "webmessagemodel.h"

WebMessageModel::WebMessageModel(WObject *parent, QObject *qparent) :
    MessageModel(qparent),
    WAbstractItemModel(parent)
{
}

void WebMessageModel::insertMessages__(int pos, const QList<Message>& messages)
{
    for(int i = 0; i < messages.count(); i++) {
      _messages.insert(pos, WebMessageModelItem(messages[i]));
      pos++;
    }
}

boost::any WebMessageModel::data(const WModelIndex &index, int role) const
{
    if (role != DisplayRole)
        return boost::any();

    WebMessageModelItem *item = reinterpret_cast<WebMessageModelItem*>(index.internalPointer());
    switch (index.column()) {
    case 0:
        return item->timestamp().toString();
    case 1:
        return item->message().sender();
    case 2:
        return item->message().contents();
    }
    return boost::any();
}
