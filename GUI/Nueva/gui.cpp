#include "gui.h"

void GUI::show()
{
   MainWindow * m = new MainWindow(this,gestorDB);
   m->show();

}
