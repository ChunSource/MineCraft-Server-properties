#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>

#include <QPainter>
#include <QMouseEvent>
#include <QDesktopWidget>
namespace Ui {
	class About;
}

class About : public QWidget
{
	Q_OBJECT
	
public:
	explicit About(QWidget *parent = 0);
	~About();
	
private:
	Ui::About *ui;
	bool mDrag;             //是否在拖动
	QPoint mDragPos;        //拖动起始点
private slots:
	void quitWindows();
	
	bool eventFilter(QObject *obj, QEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	
	void ButtonExit();
};

#endif // ABOUT_H
