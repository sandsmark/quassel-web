#ifndef WEBMESSAGEMODELITEM_H
#define WEBMESSAGEMODELITEM_H
#include "messagemodel.h"


class Message;

class WebMessageModelItem : public MessageModelItem
{
public:
    WebMessageModelItem(Message m);

    const Message &message() const { return _message; }
    const QDateTime &timestamp() const { return _message.timestamp(); }
    const MsgId &msgId() const { return _message.msgId(); }
    const BufferId &bufferId() const { return _message.bufferId(); }
    void setBufferId(BufferId bufferId) { _message.setBufferId(bufferId); }
    Message::Type msgType() const { return _message.type(); }
    Message::Flags msgFlags() const { return _message.flags(); }

private:
    Message _message;
};

#endif // WEBMESSAGEMODELITEM_H
