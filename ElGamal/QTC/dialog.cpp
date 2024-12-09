#include "dialog.h"
#include "./ui_dialog.h"
#include "ElGamal.h"

#define SIZE 10000

unsigned long long p = 0;
long long g = 0;
unsigned long long a = 0;
unsigned long long g1 = 0;
unsigned long long r = 0;
unsigned long long *cipher = new unsigned long long[SIZE];
unsigned long long key = 1;
int m_size = 0;
bool ed = 0;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
    delete[] cipher;
}

void Dialog::on_pushButton_key_clicked()
{
    p = generateLargePrime();
    g = chooseRandomGenerator(p);
    a = chooseRandomAlpha(p);
    g1 = modPow(g, a, p);
    r = chooseRandomAlpha(p);
    ui->textEdit_p->setText(QString::number(p));
    ui->textEdit_g->setText(QString::number(g));
    ui->textEdit_a->setText(QString::number(a));
    ui->textEdit_g1->setText(QString::number(g1));
    ui->textEdit_r->setText(QString::number(r));
}


void Dialog::on_pushButton_encrypt_clicked()
{
    ed = 1;
    QString m;
    m = ui->textEdit_m->toPlainText();
    key = encryptC1(g, r, p);
    m_size = m.size();
    for (int i = 0; i < m_size; i++)
    {
        cipher[i] = encryptC2(g1, r, p, m[i].unicode());
    }
    QString output;
    for(int i = 0;i < m_size; i++)
    {
        output += "(" + QString::number(key) + "," + QString::number(cipher[i]) + "),";
    }
    ui->textEdit_em->setText(output);
}


void Dialog::on_pushButton_decrypt_clicked()
{
    if(ed == 1)
    {
        QString output;
        for (int i = 0; i < m_size; i++)
        {
            uint decodedValue = static_cast<uint>(decrypt(key, cipher[i], a, p));
            if (decodedValue <= 0xFFFF) {
                output += QChar(decodedValue);
            } else {
                output += QChar(0xFFFD);
            }
        }
        ui->textEdit_dm->setText(output);
        ed = 0;
    }
}

