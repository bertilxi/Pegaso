#include "gui.h"

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1)*33) ^ str[h];
}

void GUI::show()
{
    MainWindow * m = new MainWindow(this,gestorDB);
    m->show();

}

void GUI::handle(char* control)
{
    switch (str2int(control)) {
    case str2int("main.pantallaUsuario"):

        int i =0;
        for(;i<3;i++){
            // hacer funcion de validacion para el usuario de la db
            bool valido = true;
            Usuario u = gestorUsuarios->getActual();
            if(){
                // conseguir nombre del usuario del gestor de usuarios
                QString user = gestorUsuarios->getActual().getNombre();
                qDebug()<<"Usuario "<<user<<" se ha logeado";

                //hacer auditoria del usuario
                //

                pantallaUsuario = new pantalla_usuario();
                //pantallaUsuario->setModal(true);
                pantallaUsuario->show();


            }
            else
                //mostrar mensaje de error con numero de intentos y posibles errores
                ;
        }
        break;
    //default:
        //break;
    }
}
