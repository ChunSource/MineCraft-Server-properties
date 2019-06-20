#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::About)
{
	ui->setupUi(this);
	QPixmap pixOne(":/resource/1.jpg");
	QPixmap pixTwo(":/resource/2.jpg");
	pixOne = pixOne.scaled(QSize(241, 191), Qt::KeepAspectRatio);
	pixTwo = pixTwo.scaled(QSize(241, 191), Qt::KeepAspectRatio);
	ui->LabelWeChat->setPixmap(pixOne);
	ui->LabelMoney->setPixmap(pixTwo);
	
	ui->ButtonExit->setVisible(false);
	
//	setWindowFlags(Qt::FramelessWindowHint);//无边框
//	setAttribute(Qt::WA_TranslucentBackground);//背景透明
	
	this->setAutoFillBackground(true);
	QPalette palette = this->palette();
	palette.setBrush(QPalette::Window,QBrush(QPixmap(":/resource/timg.jpg").scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));// 使用平滑的缩放方式
	this->setPalette(palette);// 给widget加上背景
//	this->setObjectName("about");
//	this->setStyleSheet("QWidget::about{border-image: url(:/resource/timg.jpg)\;border-radius:15px}");
	
	
	connect(this->ui->ButtonExit,&QPushButton::clicked,this,&About::ButtonExit);
}

About::~About()
{
	delete ui;
}

void About::quitWindows()
{
	this->close();
	this->deleteLater();
}


bool About::eventFilter(QObject *obj, QEvent *e)
{
	if (obj == this->ui->labelTitle)
		{
			if(e->type() == QEvent::MouseButtonDblClick)
				{
					//       on_btnMax_clicked();
					return true;
				}
		}
	return QObject::eventFilter(obj, e);
}

void About::mousePressEvent(QMouseEvent *e)//鼠标按下事件
{
	if (e->button() == Qt::LeftButton)
		{
			this->mDrag = true;
			this->mDragPos = e->globalPos() - pos();
			e->accept();
		}
}

void About::mouseMoveEvent(QMouseEvent *e)//鼠标移动事件
{
	if (this->mDrag && (e->buttons() && Qt::LeftButton))
		{
			move(e->globalPos() - this->mDragPos);
			e->accept();
		}
}

void About::mouseReleaseEvent(QMouseEvent *e)//鼠标释放事件
{
	this->mDrag = false;
}

void About::ButtonExit()
{
	this->close();
}
