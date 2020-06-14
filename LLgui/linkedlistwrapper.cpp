#include "linkedlistwrapper.h"
#include "LinkedList.h"
#include "ui_mainwindow.h"

LinkedListWrapper::LinkedListWrapper(QObject *parent, Ui::MainWindow *UI)
    : QObject(parent), list(), ui(UI), autoUpdate(false)
{

}

LinkedListWrapper::~LinkedListWrapper()
{

}
void LinkedListWrapper::PushFront()
{
   auto text = ui->NewItemValue->text();
   auto type = ui->NewType->currentIndex();
   auto enumType = Utils::TypeFromInt(type);
   switch (enumType)
   {
       case Types::Integer:
           list.PushFront(text.toInt());
       break;
       case Types::Double:
           list.PushFront(text.toDouble());
       break;
       case Types::String:
           list.PushFront(text.toStdString());
       break;
       default:
       break;
   }
   if (autoUpdate) PopulateList();
}
void LinkedListWrapper::PushBack()
{
    auto text = ui->NewItemValue->text();
    auto type = ui->NewType->currentIndex();
    auto enumType = Utils::TypeFromInt(type);
    switch (enumType)
    {
        case Types::Integer:
            list.PushBack(text.toInt());
        break;
        case Types::Double:
            list.PushBack(text.toDouble());
        break;
        case Types::String:
            list.PushBack(text.toStdString());
        break;
        default:
        break;
    }
   if (autoUpdate) PopulateList();
}
void LinkedListWrapper::Count()
{
    auto count = QString::number(list.Count());
    emit UpdateCount(count);
}
void LinkedListWrapper::DropList()
{
   list.DropList();
   if (autoUpdate) PopulateList();
}
void LinkedListWrapper::FindEraseAll()
{
    auto text = ui->NewItemValue->text();
    auto type = ui->NewType->currentIndex();
    auto enumType = Utils::TypeFromInt(type);
    switch (enumType)
    {
        case Types::Integer:
            list.FindAndEraseAll(text.toInt());
        break;
        case Types::Double:
            list.FindAndEraseAll(text.toDouble());
        break;
        case Types::String:
            list.FindAndEraseAll(text.toStdString());
        break;
        default:
        break;
    }
   if (autoUpdate) PopulateList();
}
void LinkedListWrapper::Read()
{
    if (list.IsEmpty())
        return;
    auto type = list.GetType();
    emit UpdateCurrentType(QString::fromStdString(Utils::GetTypesDesc(type)));
    switch (type)
    {
        case Types::Integer:
            emit  UpdateCurrentView(QString::number(list.TryGetInt()));
        break;
        case Types::Double:
            emit  UpdateCurrentView(QString::number(list.TryGetDouble()));
        break;
        case Types::String:
            emit  UpdateCurrentView(QString::fromStdString(list.TryGetString()));
        break;
        default:
        break;
    }

}
void LinkedListWrapper::Prev()
{
    if (list.IsEmpty())
        return;
    list.MoveBack();
    Read();

}
void LinkedListWrapper::Next()
{
    if (list.IsEmpty())
        return;
    list.MoveForward();
    Read();
}

void LinkedListWrapper::Erase()
{
    if (list.IsEmpty())
        return;
    list.Erase();
    emit Read();
    if (autoUpdate) PopulateList();
}
void LinkedListWrapper::Write()
{
    if (list.IsEmpty()) // create list first
        return;
    auto text = ui->CurrentValue->text();
    auto type = ui->CurrentType->currentIndex();
    auto enumType = Utils::TypeFromInt(type);
    switch (enumType)
    {
        case Types::Integer:
            list.SetValue(text.toInt());
        break;
        case Types::Double:
            list.SetValue(text.toDouble());
        break;
        case Types::String:
            list.SetValue(text.toStdString());
        break;
        default:
        break;
    }
   if (autoUpdate) PopulateList();
}
void LinkedListWrapper::Reset()
{
    Read();
}
void LinkedListWrapper::InsertBefore()
{
    if (list.IsEmpty())
        return;
    auto text = ui->CurrentValue->text();
    auto type = ui->CurrentType->currentIndex();
    auto enumType = Utils::TypeFromInt(type);
    switch (enumType)
    {
        case Types::Integer:
            list.InsertBefore(text.toInt());
        break;
        case Types::Double:
            list.InsertBefore(text.toDouble());
        break;
        case Types::String:
            list.InsertBefore(text.toStdString());
        break;
        default:
        break;
    }
   if (autoUpdate) PopulateList();
}
void LinkedListWrapper::InsertAfter()
{
    if (list.IsEmpty())
        return;
    auto text = ui->CurrentValue->text();
    auto type = ui->CurrentType->currentIndex();
    auto enumType = Utils::TypeFromInt(type);
    switch (enumType)
    {
        case Types::Integer:
            list.InsertAfter(text.toInt());
        break;
        case Types::Double:
            list.InsertAfter(text.toDouble());
        break;
        case Types::String:
            list.InsertAfter(text.toStdString());
        break;
        default:
        break;
    }
   if (autoUpdate) PopulateList();
}
void LinkedListWrapper::Search()
{
    if (list.IsEmpty())
        return;
    auto text = ui->CurrentValue->text();
    auto type = ui->CurrentType->currentIndex();
    auto enumType = Utils::TypeFromInt(type);
    switch (enumType)
    {
        case Types::Integer:
            list.Search(text.toInt());
        break;
        case Types::Double:
            list.Search(text.toDouble());
        break;
        case Types::String:
            list.Search(text.toStdString());
        break;
        default:
        break;
    }

}
void LinkedListWrapper::PopulateList()
{

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->clear();
    if (list.IsEmpty())
        return;
    list.GoHead();
    do
    {
    ui->tableWidget->insertRow ( ui->tableWidget->rowCount() );
    ui->tableWidget->setItem   ( ui->tableWidget->rowCount()-1,
                             0,
                             new QTableWidgetItem(QString::fromStdString(list.ToString())));
    ui->tableWidget->setItem   ( ui->tableWidget->rowCount()-1,
                             1,
                             new QTableWidgetItem(QString::fromStdString(list.GetTypeName())));
    }
    while (list.MoveForward());

}

void LinkedListWrapper::AutoUpdate(int value)
{
    if (value!=Qt::Unchecked)
        autoUpdate =true;
    else
        autoUpdate = false;
}
