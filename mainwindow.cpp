#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <BookWindow.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::loginSlot(QNetworkReply *reply)
{

    response_data=reply->readAll();
    //qDebug()<<response_data;
    token="Bearer "+response_data;
    reply->deleteLater();
    postManager->deleteLater();
    BookWindow *objectBookWindow=new BookWindow(this);
    objectBookWindow->setToken(token);
    objectBookWindow->show();

}

void MainWindow::on_btnLogin_clicked()
{
    QJsonObject jsonObj;
    jsonObj.insert("username",ui->textUsername->text());
    jsonObj.insert("password",ui->textPassword->text());

    QString site_url="http://localhost:3000/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    postManager = new QNetworkAccessManager(this);
    connect(postManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply = postManager->post(request, QJsonDocument(jsonObj).toJson());
}



