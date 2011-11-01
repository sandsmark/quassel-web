#ifndef WEBMESSAGEPROCESSOR_H
#define WEBMESSAGEPROCESSOR_H

#include "abstractmessageprocessor.h"

class WebMessageProcessor : public AbstractMessageProcessor
{
    Q_OBJECT

public:
    WebMessageProcessor(QObject *parent);

    void reset();
    void process(Message &msg) { process(msg); }
    void process(const Message &msg);
    void process(QList<Message>& messages);
};

#endif // WEBMESSAGEPROCESSOR_H
