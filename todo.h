#ifndef TODO_H
#define TODO_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtSql>
#include <QFileInfo>



QT_BEGIN_NAMESPACE
namespace Ui { class ToDo; }
QT_END_NAMESPACE

class ToDo : public QMainWindow
{
    Q_OBJECT

public:
    ToDo(QWidget *parent = nullptr);

    void start();  //essa funcao vai verificar se o caminho do user existe se nao exister vamos jogar o :/todo.db para o user,assim ele pode gerar um backup
    QString pathHome = getenv("HOME");
    QString dir = ":/todo.db";  //colocamos o database como source
    QString userFile = pathHome + "/.config/todo.db"; //caminho que vai ficar backup do banco
    void show_data();  //show e uma palavra reservada por isso show_data;

    QSqlDatabase  db =  QSqlDatabase::addDatabase("QSQLITE");
    ~ToDo();

private slots:
    void on_action_out_triggered();

    void on_action_about_triggered();

    void on_pushButton_clicked();

private:
    Ui::ToDo *ui;
};
#endif // TODO_H
