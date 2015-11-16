#ifndef ALTA_PARTICIPANTE_H
#define ALTA_PARTICIPANTE_H

#include <QDialog>

namespace Ui {
class alta_participante;
}

class alta_participante : public QDialog
{
    Q_OBJECT

public:

    explicit alta_participante(QWidget *parent = 0);

    ~alta_participante();

private slots:

    void on_pushButton_3_clicked();

private:
    Ui::alta_participante *ui;
};

#endif // ALTA_PARTICIPANTE_H
