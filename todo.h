#ifndef TODO_H
#define TODO_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ToDo; }
QT_END_NAMESPACE

class ToDo : public QMainWindow
{
    Q_OBJECT

public:
    ToDo(QWidget *parent = nullptr);
    ~ToDo();

private:
    Ui::ToDo *ui;
};
#endif // TODO_H
