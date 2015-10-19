#ifndef POPUP_ALERTA_H
#define POPUP_ALERTA_H

#include <QDialog>

namespace Ui {
class popup_alerta;
}

class popup_alerta : public QDialog
{
    Q_OBJECT

public:
    explicit popup_alerta(QWidget *parent = 0);
    ~popup_alerta();

private:
    Ui::popup_alerta *ui;
};

#endif // POPUP_ALERTA_H
