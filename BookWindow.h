#ifndef BOOKWINDOW_H
#define BOOKWINDOW_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class BookWindow;
}

class BookWindow : public QDialog
{
    Q_OBJECT

public:
    explicit BookWindow(QWidget *parent = nullptr);
    ~BookWindow();

    void setToken(const QByteArray &newToken);

private slots:
    void on_btnShowBooks_clicked();
    void showBookSlot (QNetworkReply *reply);

    void on_btnAdd_clicked();
    void addBookSlot (QNetworkReply *reply);

private:
    Ui::BookWindow *ui;
    QByteArray token;
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QNetworkAccessManager *postManager;
};

#endif // BOOKWINDOW_H
