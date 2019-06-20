#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	
	//ui
	setWindowFlags(Qt::FramelessWindowHint);//无边框 
	setAttribute(Qt::WA_TranslucentBackground, true);
	this->setWindowOpacity(0.9);
	
	connect(ui->ButtonAbout,&QPushButton::clicked,this,&MainWindow::ActionAbout);
	
	connect(ui->comboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),this,&MainWindow::processChangeItem);
	connect(ui->ButtonImport,&QPushButton::clicked,this,&MainWindow::ButtonImport);
	connect(ui->ButtonClear,&QPushButton::clicked,this,&MainWindow::ButtonClear);
	connect(ui->ButtonExport,&QPushButton::clicked,this,&MainWindow::ButtonExport);
	connect(ui->ButtonExit,&QPushButton::clicked,this,&MainWindow::ButtonExit);
	connect(ui->RadioSecond,&QRadioButton::toggled,this,&MainWindow::processChangeBoolData);
	connect(ui->LineKey,&QLineEdit::textChanged,this,&MainWindow::processChangeStringData);
	connect(ui->horizontalSlider,&QSlider::valueChanged,this,&MainWindow::changeTransparency);
	initProperties();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(event);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *e)
{
	if (obj == ui->LabelTitle)
		{
			if(e->type() == QEvent::MouseButtonDblClick)
				{
					//       on_btnMax_clicked();
					return true;
				}
		}
	return QObject::eventFilter(obj, e);
}

void MainWindow::mousePressEvent(QMouseEvent *e)//鼠标按下事件
{
	if (e->button() == Qt::LeftButton)
		{
			mDrag = true;
			mDragPos = e->globalPos() - pos();
			e->accept();
		}
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)//鼠标移动事件
{
	if (mDrag && (e->buttons() && Qt::LeftButton))
		{
			move(e->globalPos() - mDragPos);
			e->accept();
		}
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)//鼠标释放事件
{
	mDrag = false;
}

void MainWindow::initProperties()
{
	//BOOL
	addBoolMap("允许飞行","allow-flight",false);
	addBoolMap("允许地狱","allow-nether",true);
	addBoolMap("显示成就","announce-player-achievements",true);
	addBoolMap("允许收集游戏信息","enable-query",false);
	addBoolMap("远程访问服务器控制台","enable-rcon",false);
	addBoolMap("强制玩家默认游戏模式","force-gamemode",false);
	addBoolMap("生成村庄","generate-structures",true);
	addBoolMap("生成动物","spawn-animals",true);
	addBoolMap("生成敌对生物","spawn-monsters",true);
	addBoolMap("生成村民","spawn-npcs",true);
	addBoolMap("linux发包优化","use-native-transport",true);
	addBoolMap("服务器极限模式","hardcore",false);
	addBoolMap("正版验证","online-mode",true);
	addBoolMap("使用VPN","prevent-proxy-connections",false);
	addBoolMap("玩家伤害","PVP",true);
	addBoolMap("发送统计数据给MoJang","snooper-enabled",true);
	addBoolMap("白名单","white-list",false);
	addBoolMap("命令方块","enable-command-block",false);
	addBoolMap("踢出非白名单用户","enforce-whitelist",false);
	
	//STRING
	addStringMap("地图类型","level-type","DEFAULT");
	addStringMap("存档名称","level-name","world");
	addStringMap("服务器名称","motd","A Minecraft Server");
	addStringMap("自定义超平坦","generator-settings","");
	addStringMap("远程访问服务器的密码","rcon.password","");
	addStringMap("材质包hash","resource-pack-sha1","");
	addStringMap("服务器ip","server-ip","");
	//INT
	addIntMap("难度","difficulty",1);
	addIntMap("游戏模式","gamemode",0);
	addIntMap("最大建筑高度","max-build-height",256);
	addIntMap("服务器最大人数","max-players",20);
	addIntMap("每个tick最大花费毫秒","max-tick-time",60000);
	addIntMap("世界最大半径值","max-world-size",29999984);
	addIntMap("数据压缩","network-compression-threshold",256);
	addIntMap("OP权限","op-permission-level",4);
	addIntMap("未活动踢出时间","player-idle-timeout",0);
	addIntMap("服务器端口","server-port",25565);
	addIntMap("出生点保护","spawn-protection",16);
	addIntMap("视野距离","view-distance",10);
	addIntMap("設定監聽伺服器的埠號","query.port",25565);
	
	
	QMapIterator<QString, QString> i(log);
	while(i.hasNext())
		{
			QString name = i.next().key();
			ui->comboBox->addItem(name);
		}
	showTextMain();
}

void MainWindow::addBoolMap(QString chinese, QString english, bool key)
{
	log.insert(chinese,english);
	
	Data mydata;
	mydata.name = english;
	mydata.type = BOOL;
	mydata.boolKey = key;
	Map.insert(english,mydata);
}

void MainWindow::addIntMap(QString chinese, QString english, int key)
{
	log.insert(chinese,english);
	
	Data mymydata;
	mymydata.name = english;
	mymydata.type = INT;
	mymydata.intKey = key;
	Map.insert(english,mymydata);
	
}

void MainWindow::addStringMap(QString chinese, QString english, QString key)
{
	log.insert(chinese,english);
	
	Data mydata;
	mydata.name = english;
	mydata.type = STRING;
	mydata.stringkey = key;
	Map.insert(english,mydata);
}

void MainWindow::changData(QString name, QString key)
{
	
	if(turn)
		{
			qDebug()<<"return";
			return;
		}
	Data temp = Map.value(name);
	
	
	switch (temp.type) {
		case INT:
			{
				temp.intKey = key.toInt();
				break;
			}
		case STRING:
			{
				temp.stringkey = key;
				break;
			}
		case BOOL:
			{
				
				if(key == "true")
					{
						qDebug()<<"have true";
						temp.boolKey = true;
					}
				else
					{
						qDebug()<<"dont have true";
						temp.boolKey = false;
					}
				break;
			}
		default:
			{
				qDebug()<<"name : "<<name;
				qDebug()<<"key : "<<key;
				temp.name = name;
				if(key == "true")
					{
						temp.type = BOOL;
						temp.boolKey = true;
						qDebug()<<"type : BOOL";
					}
				else if(key == "false")
					{
						temp.type = BOOL;
						temp.boolKey = false;
						qDebug()<<"type : BOOL";
					}
				else 
					{
						if(MidHelp::isOnlyNumber(key))
							{
								temp.type = INT;
								temp.intKey = key.toInt();
								qDebug()<<"type : INT";
							}
						else
							{
								temp.type = STRING;
								temp.stringkey = key;
								qDebug()<<"type : STRING";
							}
					}
				
				
				
				
				break;
			}
		}
	Map.remove(name);
	Map.insert(name,temp);
}

void MainWindow::importData(QStringList &nameList, QStringList &keyList)
{
	
}

void MainWindow::processChangeItem(int i)
{
	turn = true;
	QString name = ui->comboBox->currentText();
	QString english = log.value(name);
	Data mydata =Map.value(english);
	switch (mydata.type) {
		case STRING:
			{
				
				ui->LineKey->setText(mydata.stringkey);
				ui->RadioFrist->setVisible(false);
				ui->RadioSecond->setVisible(false);
				ui->LineKey->setVisible(true);
				break;
			}
		case INT:
			{
				ui->LineKey->setText(QString::number(mydata.intKey));
				ui->RadioFrist->setVisible(false);
				ui->RadioSecond->setVisible(false);
				ui->LineKey->setVisible(true);
				break;
			}
		case BOOL:
			{
				
				ui->LineKey->setVisible(false);
				ui->RadioSecond->setVisible(true);
				ui->RadioFrist->setVisible(true);
				if(mydata.boolKey)
					{
						ui->RadioFrist->setChecked(true);
					}
				else
					{
						ui->RadioSecond->setChecked(true);
					}
				break;
			}
		default:
			return;
		}
	turn = false;
}

void MainWindow::processChangeBoolData()
{
	
	QString name = ui->comboBox->currentText();
	QString english = log.value(name);
	if(ui->RadioFrist->isChecked())
		{
			qDebug()<<"change to true";
			changData(english,"true");
		}
	else 
		{
			qDebug()<<"change to false";
			changData(english,"false");
		}
	
	showTextMain();
	
}

void MainWindow::processChangeStringData()
{
	QString name = ui->comboBox->currentText();
	QString english = log.value(name);
	
	QString changeCompent = ui->LineKey->text();
	changData(english,changeCompent);
	
	showTextMain();
}

void MainWindow::changeTransparency()
{
	float transparency = (float)ui->horizontalSlider->value() / 100;
	qDebug()<<"current transparency"<<transparency;
	setWindowOpacity(transparency);
}


void MainWindow::showTextMain()
{
	ui->TextMain->clear();
	QMapIterator<QString, Data> i(Map);
	QMapIterator<QString, QString> k(log);
	while(k.hasNext())
		{
			QString english = k.next().value();
		//	while(i.hasNext())
			//	{
					Data mydata;
				//	QString name = i.next().key();
					mydata = Map.value(english);
					
					if(mydata.type == BOOL)
						{
							if(mydata.boolKey)
								{
									
									ui->TextMain->append("<font color=\"#00BFFF\">"+mydata.name+"</font> "+"="+"<font color=\"#0000FF\">true</font> " );
								}
							else
								{
									ui->TextMain->append("<font color=\"#00BFFF\">"+mydata.name+"</font> "+"="+"<font color=\"#FF0000\">false</font> " );
								}
							
						}
					else if(mydata.type == STRING)
						{
							ui->TextMain->append("<font color=\"#00FF7F\">"+mydata.name+"</font> "+"="+"<font color=\"#C71585\">"+mydata.stringkey+"</font> ");
						}
					else if(mydata.type == INT)
						{
							ui->TextMain->append("<font color=\"#6A5ACD\">"+mydata.name+"</font> "+"="+"<font color=\"#2E8B57\">"+QString::number(mydata.intKey)+"</font> ");
						}
			//	}
		}
}

void MainWindow::ButtonImport()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
										   "/",
										   tr("properties (*.properties)"));
	
	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly))
		{
			QMessageBox::information(this,"打开文件失败",file.errorString());
		}
	
	QTextStream in(&file);
	QString fileContent =  in.readAll();
	
	QStringList list = fileContent.split("\n");
	//	QStringList nameList,keyList;
	
	for(int i=0;i<list.size();i++)
		{
			qDebug()<<"\n";
			QString currentText = list.at(i);
			int index = currentText.indexOf("=");
			QString Head = currentText.mid(0,index);
			QString right = currentText.mid(index+1,currentText.size()-index+1);
			qDebug()<<"current head ="<<Head;
			qDebug()<<"current right ="<<right;
			
			//	nameList.append(Head);
			//	keyList.append(right);
			
			changData(Head,right);
		}
	//	importData(nameList,keyList);
	file.close();
	
	showTextMain();
}

void MainWindow::ButtonExport()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
										   "/",
										   tr("properties (*.properties)"));
	
	QFile file(fileName);
	if(!file.open(QIODevice::ReadWrite))
		{
			QMessageBox::information(this,"打开文件失败",file.errorString());
		}
	QTextStream out(&file);
	out << ui->TextMain->toPlainText();
	file.close();
}

void MainWindow::ButtonClear()
{
	ui->TextMain->clear();
}

void MainWindow::ButtonExit()
{
	this->close();
}

void MainWindow::ActionAbout()
{
	About *a = new About();
	a->show();
}

