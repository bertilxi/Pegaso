#ifndef POPUP_EXITO_H
#define POPUP_EXITO_H

#include <QDialog>

namespace Ui {
class popup_exito;
}

class popup_exito : public QDialog
{
    Q_OBJECT

public:
    explicit popup_exito(QWidget *parent = 0);
    ~popup_exito();

private:
    Ui::popup_exito *ui;
};

#endif // POPUP_EXITO_H
