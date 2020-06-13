#include "mainwindow.h"
#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QAbstractItemView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    list = new LinkedListWrapper(this, ui);
    connect(ui->PushBack, SIGNAL(clicked()),
                         list, SLOT(PushBack()));
    connect(ui->PushFront, SIGNAL(clicked()),
                         list, SLOT(PushFront()));
    connect(ui->Count, SIGNAL(clicked()),
                         list, SLOT(Count()));
    connect(list, SIGNAL(UpdateCount(QString)),
                         ui->countView, SLOT(setText(QString)));
    connect(ui->DropList, SIGNAL(clicked()),
                         list, SLOT(DropList()));
    connect(ui->FindErase, SIGNAL(clicked()),
                         list, SLOT(FindEraseAll()));
    connect(ui->Read, SIGNAL(clicked()),
                         list, SLOT(Read()));
    connect(ui->Prev, SIGNAL(clicked()),
                         list, SLOT(Prev()));
    connect(ui->Next, SIGNAL(clicked()),
                         list, SLOT(Next()));
    connect(list, SIGNAL(UpdateCurrentView(QString)),
                         ui->CurrentValue, SLOT(setText(QString)));
    connect(list, SIGNAL(UpdateCurrentType(QString)),
                         ui->CurrentType, SLOT(setCurrentText(QString)));

    connect(ui->Erase, SIGNAL(clicked()),
                         list, SLOT(Erase()));
    connect(ui->Write, SIGNAL(clicked()),
                         list, SLOT(Write()));
    connect(ui->Reset, SIGNAL(clicked()),
                         list, SLOT(Reset()));
    connect(ui->InsertAfter, SIGNAL(clicked()),
                         list, SLOT(InsertAfter()));
    connect(ui->InsertBefore, SIGNAL(clicked()),
                         list, SLOT(InsertBefore()));
    connect(ui->Search, SIGNAL(clicked()),
                         list, SLOT(Search()));
    connect(ui->PopulateList, SIGNAL(clicked()),
                         list, SLOT(PopulateList()));
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

}


MainWindow::~MainWindow()
{
    delete ui;
}

