# App ToDo
Aplicativo de tarefas em QT com C++


##  Motivação
Praticar conhecimentos em QT, produzir uma app próximo ao  mercado em quesito de fundacionalidades é usar um banco  para persistir os dados

##
- Realizei uma lógica para possibilitar o backup dos arquivos gerados do banco de dados
- Armazenei no resources o arquivo db no projeto e copiei este arquivo para máquina local do usuário, assim ele pode realizar um backup se desejar
- Algumas métodos que eram genéricos foi criado no public como o start() e show_data().
- A lógica para realizar copia do arquivo resoucers para a máquina local e simples
- Basicamente verifico se o arquivo existe  na maquina do usuário caso não exista vou copiar o arquivo que esta no resources e colocar no ./config
- Para dar tudo certo usei o comando system para garantir as permissões de execução

``` c ++
//.h
public:

    ToDo(QWidget *parent = nullptr);

    void start(); 
    QString pathHome = getenv("HOME");
    QString dir = ":/todo.db"; 
    QString userFile = pathHome + "/.config/todo.db"; 
    void show_data();  //show e uma palavra reservada por isso show_data;

    QSqlDatabase  db

//============
//.cpp

void ToDo::start(){
     QFile file(userFile);

     if(!file.exists()){
         QFile::copy(dir,userFile);
         system("chmod 600 ~/.config/todo.db");

     }
}

```

## 
- Para popular a tabela segui basicamente as logicas anteriores quando trabalhei com QTableWidget
- Única diferença que apos realizar a consulta e inserção das rowns, deleto as  vazias
- Assim não vai ocorrer de visualmente ter tabelas vazias ou algo do tipo
- Não pode esquecer no whille inserir as rows, quem fara isso no meu exemplo e varaiavel  row
- Se esquecer de preencher as row pode visualmente aparecer coisas que não faz sentido  
- Exemplo as ordens dos dados não aparecem ordenadas mesmo sendo ordenado pelo banco, isto ocorre porque a tabela vai estar sem referência das rows. 
- Para apagar as legendas verticais usei a função verticalHeader


``` c++

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
            ui->table_list->removeRow(row); 
        }

        ui->table_list->verticalHeader()->setVisible(false);
    }

}

```

## 
- Para pegar exatemente o id é o texto editado pelo  usuario quando ele editar ou exclur usei a funcao table_cellClicked
- Ela vai retornar um row e column , no meu caso de uso o row seria a linha que foi clicado e a column seria  o 0 para id e 2 para task
- Toda vez que terminar uma edicao preciso novamente chamar o show_data() para consultar exibir os dados
- Quando a outra ui  ser concluida com o close() retornara para esta classse por isso show_data() foi acionado novmante

``` c++
void ToDo::on_table_list_cellClicked(int row, int column)
{
    int id =  ui->table_list->item(row,0)->text().toInt();
    QString task =  ui->table_list->item(row,2)->text();
    Data_edit data_edit(this,id,task);
    data_edit.exec();
    show_data(); 

}

//==============================
//data_edit.cpp
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


```

## 
- Toda vez que uma célula e clicada e, porque teoricamente usuário deseja editar ou deletar 
- Logica implementada neste caso e que apos ele clicar vai abrir uma nova ui,  essa ui vai receber  esses valores pelo construtor
- Coloquei um valor padrão para essas variáveis para não ocorrer risco de gerar problema na aplicação, caso não receber serão apenas vazias
- As variáveis no Data_edit    não  são ao global, então declarar naquele espoco estarão disponíveis apenas para este escopo


``` c ++

//.h


public:
    explicit Data_edit(QWidget *parent = nullptr,int id=0,QString task =""); 
    QString fieldId = "";
    ~Data_edit();

//==============================
//.cpp
Data_edit::Data_edit(QWidget *parent,int id,QString task) : //quando definir no arquivo .h preciso definir aqui tambem
    QDialog(parent),
    ui(new Ui::Data_edit)
{
    ui->setupUi(this);
    ui->input_task->setText(task);
    ui->label_id->setText("Id task: " + QString::number(id));
    fieldId = QString::number(id);
  

}

```

##

## ScreenShoots
![insertSuces.jpeg](https://github.com/kenjimaeda54/todo-QT/blob/develop/assets/insertSuces.jpeg)
![add.jpeg](https://github.com/kenjimaeda54/todo-QT/blob/develop/assets/add.jpeg)






