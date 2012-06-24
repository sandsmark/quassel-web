#include "webwindow.h"

#include <Wt/WVBoxLayout>
#include <Wt/WTextEdit>


WebWindow::WebWindow(WContainerWidget &parent) : WContainerWidget(parent)
{
    WVBoxLayout *layout = new WVBoxLayout();
    setLayout(layout, Wt::AlignLeft | Wt::AlignTop);
    layout->addWidget(new WTextEdit);
}
