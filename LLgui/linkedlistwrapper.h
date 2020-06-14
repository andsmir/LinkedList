#pragma once
#ifndef LINKEDLISTWRAPPER_H
#define LINKEDLISTWRAPPER_H

#include <QObject>
#include "LinkedList.h"
#include "ui_mainwindow.h"


class LinkedListWrapper : public QObject
{
    Q_OBJECT
public:
    explicit LinkedListWrapper(QObject *parent, Ui::MainWindow * UI);
    ~LinkedListWrapper();
private:
    LinkedList list;
    Ui::MainWindow *ui;
    bool autoUpdate;

signals:
    void UpdateCount(QString);
    void UpdateCurrentView(QString);
    void UpdateCurrentType(QString);

public slots:
    // Generic list manipulations
    void PushFront();
    void PushBack();
    void Count();
    void DropList();
    void FindEraseAll();

    // Current item manipulations
    void Read();
    void Prev();
    void Next();
    void Erase();
    void Write();
    void Reset();
    void InsertBefore();
    void InsertAfter();
    void Search();
    void PopulateList();
    void AutoUpdate(int);

private slots:

};

#endif // LINKEDLISTWRAPPER_H
