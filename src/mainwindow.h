#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollBar>
#include <QPainter>
#include <QMouseEvent>
#include <QDesktopWidget>
#include "midhelp.h"
#include "about.h"
namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	
private:
	enum Type{STRING,BOOL,INT,null};
	Ui::MainWindow *ui;
	
	struct Data
	{
		QString name;
		
		Type type = null;		//判断是什么数据类型
		
		QString stringkey;
		int	intKey;
		bool boolKey;
	};
	
	
	QMap<QString,Data> Map;
	QMap<QString,QString> log;
//	QList<QString,Data> Map;
	bool turn = false;
	
	
	bool mDrag;             //是否在拖动
	QPoint mDragPos;        //拖动起始点
	
	
private slots:
	void initProperties();		//初始化记载server.properties各种选项
	void addBoolMap(QString chinese, QString english, bool key);	
	void addIntMap(QString chinese, QString english,int key);
	void addStringMap(QString chinese, QString english,QString key);
	
	void changData(QString name,QString key);
	void importData(QStringList& nameList,QStringList& keyList);
	
	void processChangeItem(int i);		//切换Combox
	void processChangeBoolData();			//处理需要更改的  BOOL
	void processChangeStringData();		//处理需要更改的  String
	void changeTransparency();
	void showTextMain();    //刷新一遍TextEdit
	
	void ButtonImport();
	void ButtonExport();
	void ButtonClear();
	void ButtonExit();
	
	void ActionAbout();
	
	
	//overwrite
	void paintEvent(QPaintEvent *event);
	
	
	bool eventFilter(QObject *obj, QEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
