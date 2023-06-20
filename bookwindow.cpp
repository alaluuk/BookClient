#include "bookwindow.h"
#include "ui_bookwindow.h"

BookWindow::BookWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookWindow)
{
    ui->setupUi(this);
}

BookWindow::~BookWindow()
{
    delete ui;
}

void BookWindow::on_btnShowBooks_clicked()
{
    QString site_url="http://localhost:3000/book";
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(token));
    //WEBTOKEN LOPPU
    getManager = new QNetworkAccessManager(this);

    connect(getManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(showBookSlot(QNetworkReply*)));

    reply = getManager->get(request);
}

void BookWindow::showBookSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
   // qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString book;
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        book+=QString::number(json_obj["id_book"].toInt())+", "+json_obj["name"].toString()+", "+json_obj["author"].toString()+"\r";
    }

    ui->textBooks->setText(book);

    reply->deleteLater();
    getManager->deleteLater();
}

void BookWindow::setToken(const QByteArray &newToken)
{
    token = newToken;
}


void BookWindow::on_btnAdd_clicked()
{
    qDebug()<<"btnAdd clicked";
    QJsonObject jsonObj;
    jsonObj.insert("name",ui->textName->text());
    jsonObj.insert("author",ui->textAuthor->text());
    jsonObj.insert("isbn",ui->textIsbn->text());

    QString site_url="http://localhost:3000/book";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(token));
    //WEBTOKEN LOPPU

    postManager = new QNetworkAccessManager(this);
    connect(postManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(addBookSlot(QNetworkReply*)));

    reply = postManager->post(request, QJsonDocument(jsonObj).toJson());
}

void BookWindow::addBookSlot(QNetworkReply *reply)
{
    qDebug()<<"addBookSlot";
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    postManager->deleteLater();
    on_btnShowBooks_clicked();
}

