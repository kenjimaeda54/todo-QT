#include "todo.h"
#include "ui_todo.h"

ToDo::ToDo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ToDo)
{
    ui->setupUi(this);
    start();
    db.setDatabaseName(userFile);// apos a funcao start ser executada nao sera mais o banco de dados setado no resource por isso setDatabaseNmae
    if(db.open()){
        show_data(); //se o databse estiver aberto ai chama o show_data , se nao comparar isso vai gerar erro,primeiro tem que estar ok banco para depois consultar
    }
    ui->table_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

ToDo::~ToDo()
{
    delete ui;
}




void ToDo::start(){
     QFile file(userFile);

     if(!file.exists()){
         QFile::copy(dir,userFile);//estou copiando o banco de dados que esta no resource e envindo para HOME/.config/todo.db
         system("chmod 600 ~/.config/todo.db");

     }



}

int test =0;
void ToDo::show_data() {
    QSqlQuery  query;
    QString comand = "  SELECT * FROM todos ORDER BY id DESC";
    query.prepare(comand);


    if(query.exec()){
        int row = 0;
        ui->table_list->setColumnCount(3);




        while(query.next()){
            ui->table_list->insertRow(row);

            ui->table_list->setItem(row,0,new QTableWidgetItem(query.value(0).toString()));
            ui->table_list->setItem(row,1,new QTableWidgetItem(query.value(1).toString()));
            ui->table_list->setItem(row,2,new QTableWidgetItem(query.value(2).toString()));

            row ++; //cuidado essencial somar o numero de linhas para alterar o insertRow
        }


        QStringList headers {"ID", "DATE/TIME", "TASK"};

        ui->table_list->setHorizontalHeaderLabels(headers);

        ui->table_list->setColumnWidth(0, 50);
        ui->table_list->setColumnWidth(1, 250);
        ui->table_list->setColumnWidth(2, 750);

        while( row < ui->table_list->rowCount()  ){
            ui->table_list->removeRow(row); //preciso apagar para poder nao aparecer linhas vazias ou linhas a mais visualmente;
        }

        ui->table_list->verticalHeader()->setVisible(false);
    }

}


void ToDo::on_action_out_triggered()
{
    this->close();
}


void ToDo::on_action_about_triggered()
{
   QMessageBox::about(this,"About program","About this project,<h2>ToDo 1.0.0</h2>"
                                           "<p>Develop: Ricardo Kenji</p></br>"
                                           "Copyright 2008-2020"
                                           "<p><a href='https://github.com/kenjimaeda54/todo-QT'>Github</p></br>"
                                           "<p>The program is <i> provided AS IS with NO WARRANTY OF ANY KIND,"
                                           "INCLUDING THE WARRANTY OF DESING, MERCHANTABILITY"
                                           "AND FITNESS FOR A PARTICULAR PORPOSE</i></p>");//para concatenar usar o ''
}


void ToDo::on_pushButton_clicked()
{
      QString task = ui->input_task->text();

      if(task.isEmpty()){
          QMessageBox::warning(this,"Attention","Can't save field empty");
          return;

      }

      if(!db.open()){
          QMessageBox::critical(this,"Error","I can`t open dabatabese");
          return;

      }

      QSqlQuery query;
      QString comand = "INSERT INTO todos( text  )  VALUES( '" +task+ "' )";
      query.prepare(comand);

      if(query.exec()){

          ui->statusbar->showMessage("Data saved successfully");
          QTimer::singleShot(2000,this,[&](){ui->statusbar->close();});//depois de 200 milisegundos vai fechar o statusbar;
          ui->input_task->clear();
          ui->input_task->setFocus();
          show_data();

      }


}


void ToDo::on_table_list_cellClicked(int row, int column)
{
    int id =  ui->table_list->item(row,0)->text().toInt();// estou usando a coluna 0 porque e aonde esta o id da tarefa
    QString task =  ui->table_list->item(row,2)->text();
    Data_edit data_edit(this,id,task);
    data_edit.exec();
    show_data(); //assim que terminar da classe data_edit ser executada isto entrara em acao,por isso estou chamando o show_data()

}

