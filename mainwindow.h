#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <qlineedit.h>

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
    void SetFilePath(QLineEdit* line_edit, std::string& result_file_path);

public slots:
    void SetBeforeFilePath();
    void SetAfterFilePath();
    void Transfer();

private:
    Ui::MainWindow *ui;
    std::string before_file_path, after_file_path;

};

#endif // MAINWINDOW_H
