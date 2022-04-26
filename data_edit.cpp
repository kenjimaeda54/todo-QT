#include "data_edit.h"
#include "ui_data_edit.h"

Data_edit::Data_edit(QWidget *parent,int id,QString task) : //quando definir no arquivo .h preciso definir aqui tambem
    QDialog(parent),
    ui(new Ui::Data_edit)
{
    ui->setupUi(this);
    ui->input_task->setText(task);
    ui->label_id->setText("Id task: " + QString::number(id));
    fieldId = QString::number(id);
    //as varaiveis aqui nao sao globais,e se precisar alterar os valroes do campo de forma dinamica e refletir,precisar fazer no escpo,no cao de editar precisa retribuir essa variavel la

}



Data_edit::~Data_edit()
{
    delete ui;
}

void Data_edit::on_btn_edit_clicked()
{

    QString newTask = ui->input_task->text();

    if(newTask.isEmpty()){
       QMessageBox::warning(this,"Attention","Can't update data is empty");
       return;

    }

    QSqlQuery query;
    QString comand = "UPDATE todos SET text='" + newTask + "' WHERE id=' " +fieldId+ " ' ";
    query.prepare(comand);

    if(query.exec()){
        this->close(); //apos fechar essa tela vai voltar para a inicial
        return;
    }

}


void Data_edit::on_btn_delete_clicked()
{


     QSqlQuery query;
     QString comand = "DELETE FROM todos WHERE id=' "+fieldId+"' ";
     query.prepare(comand);

     if(query.exec()){
       this->close();

    }

}

