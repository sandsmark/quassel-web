#include "webmessageprocessor.h"
#include "messagemodel.h"
#include "client.h"

WebMessageProcessor::WebMessageProcessor(QObject *parent) :
    AbstractMessageProcessor(parent)
{
}

void WebMessageProcessor::reset()
{
}

void WebMessageProcessor::process(const Message &msg)
{
    //TODO: do stuff here
    Client::messageModel()->insertMessage(msg);
}

void WebMessageProcessor::process(QList<Message> &messages)
{
    Q_FOREACH(const Message &message, messages) {
        process(message);
    }
}
