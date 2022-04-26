#ifndef DATA_EDIT_H
#define DATA_EDIT_H

#include <QDialog>
#include <QMessageBox>
#include <QtSql>



namespace Ui {
class Data_edit;
}

class Data_edit : public QDialog
{
    Q_OBJECT

public:
    explicit Data_edit(QWidget *parent = nullptr,int id=0,QString task =""); //aqui adiciono parametros que desejo no contrutor
    QString fieldId = "";
    ~Data_edit();

private slots:
    void on_btn_edit_clicked();

    void on_btn_delete_clicked();

private:
    Ui::Data_edit *ui;
};

#endif // DATA_EDIT_H
