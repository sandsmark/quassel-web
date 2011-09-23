#include "webwindow.h"

#include <Wt/WVBoxLayout>
#include <Wt/WTextEdit>


WebWindow::WebWindow(WContainerWidget &parent) : WContainerWidget(parent)
{
    WVBoxLayout *layout = new WVBoxLayout();
    setLayout(layout, AlignLeft | AlignTop);
    layout->addWidget(new WTextEdit);
}
