#ifndef CILENT_H
#define CILENT_H

#include <QWidget>
#include<QTcpSocket>
#include<QListWidgetItem>
namespace Ui {
class Cilent;
}

class Cilent : public QWidget
{
    Q_OBJECT

public:
    explicit Cilent(QWidget *parent = 0);
    ~Cilent();
    void mesConfirm();
    bool deleteDirectory(const QString &path);

private slots:
    void on_PbSend_clicked();

    void receiveMessage();

    void on_PbConnect_clicked();

    void closeEvent(QCloseEvent * e);

    void choseFriend(QListWidgetItem *item);

private:
    Ui::Cilent *ui;
    QTcpSocket *socket;
    int socketId;
    bool isOnline=false;
};

#endif // CILENT_H
