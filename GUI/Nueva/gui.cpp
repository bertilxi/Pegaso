#include "gui.h"

void GUI::show()
{
    mainWindow(0,this,gestorDB);
    mainWindow->show();
}
