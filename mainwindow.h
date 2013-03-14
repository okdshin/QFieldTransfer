#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <qlineedit.h>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <QThread>
#include "transferer.h"

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
    void SetFilePath(QLineEdit* line_edit, const QString& caption, std::string& result_file_path);

public slots:
    void SetBeforeFilePath();
    void SetAfterFilePath();
    void Transfer();
    void OnTransferFinished(unsigned int width, unsigned height)const;

private:
    Ui::MainWindow *ui;
    std::string before_file_path, after_file_path;

    Transferer* transferer;

};

#endif // MAINWINDOW_H
