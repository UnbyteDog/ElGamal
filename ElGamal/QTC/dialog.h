#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "ui_dialog.h"
#include "ElGamal.h"

// QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
// QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_key_clicked();

    void on_pushButton_encrypt_clicked();

    void on_pushButton_decrypt_clicked();

private:
    Ui::Dialog *ui;
    unsigned long long p;
    long long g;
    unsigned long long a;
    unsigned long long g1;
    unsigned long long r;
    unsigned long long *cipher;
    int m_size;
    bool ed;
};
#endif // DIALOG_H
