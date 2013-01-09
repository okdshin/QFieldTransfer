#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include <qmessagebox.h>
#include "field_transfer/FieldTransfer.h"

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

auto MainWindow::SetFilePath(QLineEdit* line_edit, std::string& result_file_path) -> void {
    QString file_path_qstr = QFileDialog::getOpenFileName(this);
    if(file_path_qstr.isEmpty()){
        return;
    }
    line_edit->setText(file_path_qstr);
    result_file_path = file_path_qstr.toStdString();
}

auto MainWindow::SetBeforeFilePath() -> void {
    SetFilePath(this->ui->before_file_path_line_edit, this->before_file_path);
}

auto MainWindow::SetAfterFilePath() -> void {
    SetFilePath(this->ui->after_file_path_line_edit, this->after_file_path);
}

auto MainWindow::Transfer() -> void {
    if(this->before_file_path.empty()){
        QMessageBox::information(this, "Error!", "please set \"BeforeFile\" path.");
        return;
    }
    else if(this->after_file_path.empty()){
        QMessageBox::information(this, "Error!", "please set \"AfterFile\" path.");
        return;
    }

    const auto vector_list_pair =
        CreateVectorListPairFromFile(
            this->before_file_path.c_str(),
            this->after_file_path.c_str());

    const auto optimized = TernarySearch(
        0, 2*M_PI,
        2*M_PI/360000000,
        [&](Number theta)->Number {
            return MakeMeMin(theta, vector_list_pair);
        });

    const auto translated_route = CalcTranslateRoute(vector_list_pair);
    /*
    std::cout << "TranslateRoute:" << translated_route << std::endl;
    std::cout << "OptimizedTheta:" << 360.0*(optimized/(2*M_PI)) << std::endl;
    */
    const auto raw_field = CreateField(this->ui->width_spin_box->value(), this->ui->width_spin_box->value(), 1.0);
    const auto transfered_field =
        TransferVectorList(raw_field, optimized, translated_route);
    /*
    for(Index i = 0; i < transfered_field.Size(); ++i){
        std::cout << transfered_field(i) << std::endl;
    }
    */
    QString file_path_qstr = QFileDialog::getSaveFileName(this);
    if(file_path_qstr.isEmpty()){
        return;
    }
    std::ofstream field_file(file_path_qstr.toStdString().c_str());
    OutputFieldFormat(transfered_field, field_file);

}

/*
    const auto vector_list_pair =
        CreateVectorListPairFromFile(
            "sample_data/before.csv",
            "sample_data/after.csv");

    const auto optimized = TernarySearch(
        0, 2*M_PI,
        2*M_PI/360000000,
        [&](Number theta)->Number {
            return MakeMeMin(theta, vector_list_pair);
        });

    const auto translated_route = CalcTranslateRoute(vector_list_pair);
    std::cout << "TranslateRoute:" << translated_route << std::endl;
    std::cout << "OptimizedTheta:" << 360.0*(optimized/(2*M_PI)) << std::endl;

    const auto raw_field = CreateField(532, 419, 1);
    const auto transfered_field =
        TransferVectorList(raw_field, optimized, translated_route);
    for(Index i = 0; i < transfered_field.Size(); ++i){
        std::cout << transfered_field(i) << std::endl;
    }

    std::ofstream field_file("result.csv");
    OutputFieldFormat(transfered_field, field_file);

    return 0;
*/

