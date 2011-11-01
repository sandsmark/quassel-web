#ifndef WEBMESSAGEMODEL_H
#define WEBMESSAGEMODEL_H

#include "webmessagemodelitem.h"

#include "messagemodel.h"
#include <Wt/WAbstractItemModel>

#include <QList>
using namespace Wt;

class WebMessageModel : public MessageModel, public WAbstractItemModel
{
    Q_OBJECT
public:
    WebMessageModel(WObject *parent, QObject *qparent);

    // Functions for WAbstractItemModel
    int columnCount(const WModelIndex&) const { return 3; }
    int rowCount(const WModelIndex&) const { return _messages.size(); }
    Wt::WModelIndex parent(const WModelIndex&) const { return WModelIndex(); }
    boost::any data(const WModelIndex&, int) const;
    WModelIndex index(int row, int column, const WModelIndex&) const { return WAbstractItemModel::createIndex(row, column, (void*)&_messages[row]); }

    // Functions for MessageModel
    int messageCount() const { return _messages.count(); }
    bool messagesIsEmpty() const { return _messages.isEmpty(); }
    const MessageModelItem* messageItemAt(int i) const { return &_messages.at(i); }
//MessageModelItem* messageItemAt(int i) { return &_messages.at(i); }
    virtual inline MessageModelItem *messageItemAt(int i) { return &_messages[i]; }

    const MessageModelItem* firstMessageItem() const { return &_messages.first(); }
    MessageModelItem* firstMessageItem() { return &_messages.first(); }
    const MessageModelItem* lastMessageItem() const { return &_messages.last(); }
    MessageModelItem* lastMessageItem() { return &_messages.last(); }
    void insertMessage__(int i, const Message& message) { _messages.insert(i, WebMessageModelItem(message)); }
    void insertMessages__(int i, const QList<Message>& messages);
    void removeMessageAt(int i) { _messages.removeAt(i); }
    void removeAllMessages() { _messages.clear(); }
    Message takeMessageAt(int i) { return _messages.takeAt(i).message(); }

private:
    QList<WebMessageModelItem> _messages;
};

#endif // WEBMESSAGEMODEL_H
