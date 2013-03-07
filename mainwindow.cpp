#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qsound.h>
#include "FieldTransfer/FieldTransfer.h"

using namespace field_transfer;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    try{

        if(this->before_file_path.empty()){
            QMessageBox::information(this, "Error!", "please set \"BeforeFile\" path.");
            return;
        }
        else if(this->after_file_path.empty()){
            QMessageBox::information(this, "Error!", "please set \"AfterFile\" path.");
            return;
        }

        const unsigned int x_col_index = this->ui->x_column_index_spin_box->value();
        const unsigned int y_col_index = this->ui->y_column_index_spin_box->value();
        const auto vector_list_pair =
            CreateVectorListPairFromFile(
                x_col_index, y_col_index,
                this->before_file_path.c_str(),
                this->after_file_path.c_str());

        //OutputVectorList(vector_list_pair.GetBeforeVectorList(), std::cout);
        //OutputVectorList(vector_list_pair.GetAfterVectorList(), std::cout);

        const auto optimized = TernarySearch(
            0, 2*M_PI,
            2*M_PI/1000,
            [&](Number theta)->Number {
                return MakeMeMin(theta, vector_list_pair);
            });

        const auto translated_route = CalcTranslateRoute(vector_list_pair);

        const unsigned int width = this->ui->width_spin_box->value();
        const unsigned int height = this->ui->height_spin_box->value();
        const auto raw_field = CreateField(width, height, 1.0);
        const auto transfered_field =
                TransferVectorList(raw_field, optimized, translated_route,
            [this, &raw_field](unsigned int i){
                this->ui->progressBar->setValue(this->ui->progressBar->maximum()*i/raw_field.Size());
            }
        );

        if(this->ui->checkBox->isChecked()){
            QSound::play(":/sound/tm2_metalhit000.wav");
        }
        QString file_path_qstr = QFileDialog::getSaveFileName(this, "SaveResultFile");
        if(file_path_qstr.isEmpty()){
            return;
        }
        std::ofstream field_file(file_path_qstr.toStdString().c_str());
        OutputFieldFormat(width, height, transfered_field, raw_field, field_file);
    }
    catch(char const* error){
        QMessageBox::information(this, "Error!", error);
        return;
    }

}
