#include "cilent.h"
#include "ui_cilent.h"
#include<QByteArray>
#include<QDebug>
#include<QThread>
#include<QCloseEvent>
#include<QFile>
#include<QDateTime>
#include<QDir>
#include<QDialog>
#include<QMessageBox>
Cilent::Cilent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cilent)
{
    ui->setupUi(this);
}

Cilent::~Cilent()
{
    delete ui;
}

//消息确认时间
//接收消息后，发送该指令，告诉服务器可以发送下条指令了
//数据格式：9
void Cilent::mesConfirm()
{
   QString str("9");
   QByteArray mes=str.toUtf8();
   socket->write(mes);
   socket->waitForBytesWritten();
}



//发送消息事件
//点击按钮时，发送消息
//数据格式：3 本机socketId 本机姓名 接受方名称 消息内容
void Cilent::on_PbSend_clicked()
{
    QListWidgetItem *item=ui->LwShowFriend->currentItem();
    if(item!=0){
        QString mes("3 ");;
        QString data;
        QString selfName=ui->LeName->text();

        QString receiverName=item->text();
        QString text=ui->TeSendMessage->toPlainText();
        if(text==""){
             QMessageBox::information(this,"警告！","发送内容不能为空！");
             return;
        }

        data.setNum(socketId);
        mes=mes+data+" "+selfName+" "+receiverName+" "+text;
        QByteArray sendmes=mes.toUtf8();
        socket->write(sendmes);

        QDateTime dateTime(QDateTime::currentDateTime());
        QString temp = dateTime.toString("yy-MM-dd hh:mm::ss")+'\n';
        QByteArray time=temp.toUtf8();

        QString content=selfName+" "+text;
        QFile file("./"+ui->LeName->text()+"Record"+"./"+receiverName+".txt");
        file.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Append);
        file.write(time);
        file.flush();
        file.write(content.toUtf8()+'\n');
        file.flush();

        choseFriend(item);
    }else{
        QMessageBox::information(this,"警告！","未选择信息接收者！");
        return;
    }
}

//上线连接事件
//点击按钮连接时，发送姓名并更新他人的好友列表
//消息格式:1 name
void Cilent::on_PbConnect_clicked()
{
    socket =new QTcpSocket(this);
    socket->connectToHost("47.115.211.246",8080);

    //发送连接者姓名
    QString str("1 "+ui->LeName->text());
    QByteArray sendUsername=str.toUtf8();
    int flag=socket->write(sendUsername);

    if(flag==0){
        ui->LwLog->addItem("服务器连接失败----");
    }else{
         ui->LwLog->addItem("服务器连接成功！");
        //绑定网络连接
        connect(socket,SIGNAL(readyRead()),this,SLOT(receiveMessage()));
        //绑定刷新好友列表
        connect(ui->LwShowFriend,&QListWidget::itemClicked,this,&choseFriend);
        //创建聊天记录保存目录
        QDir dir;
        if(!dir.mkdir("./"+ui->LeName->text()+"Record/text.txt")){
            dir.mkpath("./"+ui->LeName->text()+"Record");
        }else{
            deleteDirectory("./"+ui->LeName->text()+"Record");
            dir.mkpath("./"+ui->LeName->text()+"Record");
        }
        isOnline=true;
    }
}



//关闭窗口事件
//关闭窗口时，发送消息，告诉服务器此人已下线，并更新他人好友列表
//消息格式:2 name
void Cilent::closeEvent(QCloseEvent *e)
{
    if(isOnline){
        QString str("2 "+ui->LeName->text());
        QByteArray sendExitUsername=str.toUtf8();

        int id=socket->write(sendExitUsername);
        socket->waitForBytesWritten();//等待socket发送完成在关闭窗口
        deleteDirectory("./"+ui->LeName->text()+"Record");
        e->accept();
    }
}



//刷新聊天记录
void Cilent::choseFriend(QListWidgetItem *item)
{

    qDebug()<<"refresh...."<<endl;
    QString friendName=item->text();
    QFile file("./"+ui->LeName->text()+"Record"+"/"+friendName+".txt");
    ui->LwShowMessage->clear();
    if(file.open(QIODevice::ReadOnly)){
        while(!file.atEnd()){
            QString date=file.readLine().data();
            QString str=file.readLine().data();
            QStringList temp=str.split(" ");
            QString mes=temp[0]+" : "+temp[1];
            ui->LwShowMessage->addItem(date+mes);
        }
         ui->LwShowMessage->scrollToBottom();//设置默认在最新的一行上
    }else{
        qDebug()<<"file open failed"<<endl;
    }

}



//接收消息事件
//用于接收服务器端传来的数据
//消息格式:type=1发送日志 type=2 发送消息 type=3更新好友列表  type=4接收本机socketId  type=5接收转发消息
void Cilent::receiveMessage()
{
    QByteArray arr=socket->readAll();
    QString data=arr.data();
    qDebug()<<"receive from server:"<<data<<endl;
    switch (arr[0]) {
    case '1':
        ui->LwLog->addItem(data.mid(2));
        ui->LwLog->scrollToBottom();
        break;
    case '3':{
        ui->LwShowFriend->clear();//删除所有列表项
        QStringList userNames=data.split(" ");
        bool flag=true;
        for(const QString& name:userNames ){
           if(flag){
               flag=false;
               continue;
           }
           if(name=="")continue;
           QListWidgetItem *item=new QListWidgetItem();
           item->setText(name);
           ui->LwShowFriend->addItem(item);
        }
        ui->LwShowFriend->scrollToBottom();
        break;
    }
    case '4':
        socketId=data.mid(2).toInt();
        break;
    case '5':
    {
        QStringList list = data.split(" ");//QString字符串分割函数
        QString senderName=list.at(1);
        QString mes=list.at(2);
        QString demo=senderName+" "+mes+'\n';
        QByteArray text=demo.toUtf8();


        QDateTime dateTime(QDateTime::currentDateTime());
        QString temp = dateTime.toString("yy-MM-dd hh:mm:ss")+'\n';
        QByteArray time=temp.toUtf8();


        QFile file("./"+ui->LeName->text()+"Record"+"/"+senderName+".txt");
        file.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Append);
        file.write(time);
        file.flush();
        file.write(text);
        file.flush();
        QListWidgetItem *item=ui->LwShowFriend->currentItem();
        if(item!=0){
            qDebug()<<"diaoyong ++++"<<endl;
             choseFriend(item);
        }
    }        
    }
    mesConfirm();//告诉服务器 此次消息已经处理完毕 可以发送下一条了
}



//删除指定文件目录
bool Cilent::deleteDirectory(const QString &path)
{
    if (path.isEmpty())
        return false;

    QDir dir(path);
    if(!dir.exists())
        return true;

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo fi, fileList)
    {
        if (fi.isFile())
            fi.dir().remove(fi.fileName());
        else
            deleteDirectory(fi.absoluteFilePath());
    }
    return dir.rmpath(dir.absolutePath());
}

