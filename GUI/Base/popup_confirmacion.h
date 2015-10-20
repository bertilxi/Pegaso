#ifndef POPUP_CONFIRMACION_H
#define POPUP_CONFIRMACION_H

#include <QDialog>

namespace Ui {
class popup_confirmacion;
}

class popup_confirmacion : public QDialog
{
    Q_OBJECT

public:
    explicit popup_confirmacion(QWidget *parent = 0);
    ~popup_confirmacion();

private:
    Ui::popup_confirmacion *ui;
};

#endif // POPUP_CONFIRMACION_H
