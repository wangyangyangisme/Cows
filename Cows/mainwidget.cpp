﻿#include "stdafx.h"

#include "mainwidget.h"
#include "ui_mainwindow.h"
#include "tablewidget.h"
#include "AboutDialog.h"
#include "listdatawidget.h"
#include "sqlexecute.h"
#include "RealTimeCurveQChartWidget.h"

#include "comdata.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	signalConnect();

	

	//移除一个多余的没有用的窗体
	ui->stackedWidget->removeWidget(ui->stackedWidget->widget(1));

	cw = new RealTimeCurveQChartWidget;
	ui->stackedWidget->addWidget(cw);

	

	ListDataWidget *ldw = new ListDataWidget;
	ui->stackedWidget->addWidget(ldw);

	ui->stackedWidget->setCurrentIndex(1);

    ComData *data = new ComData(QString("COM2"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::signalConnect()
{
	/*********************QAction*************************/
	//显示Qt版权说明
	connect(ui->action_Qt, &QAction::triggered, qApp, &QApplication::aboutQt);
	
	//退出
	connect(ui->action_exit, &QAction::triggered, qApp, &QApplication::exit);

	//显示关于
	connect(ui->action_about, &QAction::triggered, this, &MainWindow::showAbout);


	/*********************QToolButton*************************/
	connect(ui->action_showchart, &QAction::triggered, this, &MainWindow::showChart);
	connect(ui->action_history, &QAction::triggered, this, &MainWindow::showHistory);

	//导出数据action
	connect(ui->action_export, &QAction::triggered, this, &MainWindow::exportData);
    //导入数据action
    connect(ui->action_import, &QAction::triggered, this, &MainWindow::importData);
}

void MainWindow::showChart()
{
	ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::showAbout()
{
	AboutDialog *about = new AboutDialog(this);
	about->setModal(true);
	about->show();
}

void MainWindow::showHistory()
{
	ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::exportData()
{
	bool ok = false;
	loop:
	QString name = QInputDialog::getText(nullptr, "保存数据", "请输入保存的名字：", QLineEdit::Normal, QString(), &ok);

	if (ok)
	{
		QString table = QString("%1_%2").arg(QDate::currentDate().toString("yyyy-MM-dd")).arg(name);

		if (SQLExecute::getAllTableName().contains(table))
		{
			//保存的表中已经包含了这个表
			if (QMessageBox::Cancel == QMessageBox::question(nullptr, "提示", "名字已经存在，是否追加数据？"))
			{
				//大返回
				goto loop;
			}
		}

		//SQLExecute::exportData(table, tw->getTableModel()->getData());
	}
	else
	{

    }
}

void MainWindow::importData()
{

}
