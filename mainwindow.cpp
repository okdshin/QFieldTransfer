#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qsound.h>
//#include "FieldTransfer/FieldTransfer.h"
#include <boost/bind.hpp>
#include "transferer.h"
#include <QThread>

//using namespace field_transfer;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    transferer(new Transferer(this))
{
    ui->setupUi(this);
    QObject::connect(this->transferer, SIGNAL(OnFinished(uint, uint)), this, SLOT(OnTransferFinished(uint, uint)));
    QObject::connect(this->transferer, SIGNAL(Indicate(int)), this->ui->progressBar, SLOT(setValue(int)));

    transferer->SetIndicatorMax(this->ui->progressBar->maximum());
}

MainWindow::~MainWindow()
{
    delete ui;
}

auto MainWindow::SetFilePath(QLineEdit* line_edit, const QString& caption, std::string& result_file_path) -> void {
    QString file_path_qstr = QFileDialog::getOpenFileName(this, caption);
    if(file_path_qstr.isEmpty()){
        return;
    }
    line_edit->setText(file_path_qstr);
    result_file_path = file_path_qstr.toStdString();
}

auto MainWindow::SetBeforeFilePath() -> void {
    SetFilePath(this->ui->before_file_path_line_edit, "OpenBeforeFile", this->before_file_path);
}

auto MainWindow::SetAfterFilePath() -> void {
    SetFilePath(this->ui->after_file_path_line_edit, "OpenAfterFile", this->after_file_path);
}

auto MainWindow::Transfer() -> void {
    this->ui->transfer_button->setEnabled(false);
    if(before_file_path.empty()){
        QMessageBox::information(0, "Error!", "please set \"BeforeFile\" path.");
        return;
    }
    else if(after_file_path.empty()){
        QMessageBox::information(0, "Error!", "please set \"AfterFile\" path.");
        return;
    }

    const unsigned int x_col_index = this->ui->x_column_index_spin_box->value();
    const unsigned int y_col_index = this->ui->y_column_index_spin_box->value();
    const unsigned int width = this->ui->width_spin_box->value();
    const unsigned int height = this->ui->height_spin_box->value();

    this->transferer->SetParameta(x_col_index, y_col_index, this->before_file_path, this->after_file_path, width, height);
    transferer->start();
}

auto MainWindow::OnTransferFinished(unsigned int width, unsigned int height)const -> void {
    const auto raw_field = this->transferer->GetRawField();
    const auto transfered_field = this->transferer->GetTransferedField();
    if(this->ui->checkBox->isChecked()){
        QSound::play(":/sound/tm2_metalhit000.wav");
    }

    QString file_path_qstr = QFileDialog::getSaveFileName(0, "SaveResultFile");
    this->ui->transfer_button->setEnabled(true);
    if(file_path_qstr.isEmpty()){
        this->ui->progressBar->setValue(0);
        return;
    }
    std::ofstream field_file(file_path_qstr.toStdString().c_str());
    field_transfer::OutputFieldFormat(width, height, transfered_field, raw_field, field_file);

    QMessageBox::information(0, "Save finished!", "Save successfully finished!");
    this->ui->progressBar->setValue(0);

}


