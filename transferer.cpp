#include "transferer.h"
#include <qfiledialog.h>
#include <qmessagebox.h>


using namespace field_transfer;

Transferer::Transferer(QObject* parent):QThread(parent), indicator_max(0){}

auto Transferer::run() -> void {
    this->Transfer();
}

auto Transferer::SetParameta(
        unsigned int x_col_index, unsigned int y_col_index,
        const std::string& before_file_path, const std::string& after_file_path,
        unsigned int width, unsigned int height) -> void
{
    this->x_col_index = x_col_index;
    this->y_col_index = y_col_index;
    this->before_file_path = before_file_path;
    this->after_file_path = after_file_path;
    this->width = width;
    this->height = height;
}

auto Transferer::Transferer::Transfer() -> void {
    std::cout << "transfer start" << std::endl;
    try{

        const auto vector_list_pair =
            CreateVectorListPairFromFile(
                x_col_index, y_col_index,
                before_file_path.c_str(),
                after_file_path.c_str());

        const auto optimized = TernarySearch(
            0, 2*M_PI,
            2*M_PI/1000,
            [&](Number theta)->Number {
                return MakeMeMin(theta, vector_list_pair);
            });

        const auto translated_route = CalcTranslateRoute(vector_list_pair);

        this->raw_field = CreateField(width, height, 1.0);
        if(this->indicator_max == 0){
            std::cout << "indicator max is 0. OK?" << std::endl;
        }
        this->transfered_field =
                TransferVectorList(raw_field, optimized, translated_route,
            [this](unsigned int i){
                emit Indicate(this->indicator_max*i/this->raw_field.Size());
                //this->ui->progressBar->setValue(this->ui->progressBar->maximum()*i/raw_field.Size());
            }
        );

        emit OnFinished(this->width, this->height);


        /*
        QString file_path_qstr = QFileDialog::getSaveFileName(0, "SaveResultFile");
        if(file_path_qstr.isEmpty()){
            return;
        }
        std::ofstream field_file(file_path_qstr.toStdString().c_str());
        OutputFieldFormat(width, height, transfered_field, raw_field, field_file);
        */
    }
    catch(char const* error){
        QMessageBox::information(0, "Error!", error);
        return;
    }

}

void Transferer::SetIndicatorMax(unsigned int max){
    this->indicator_max = max;
}

auto Transferer::GetTransferedField()const -> VectorList {
    return this->transfered_field;
}

auto Transferer::GetRawField()const -> VectorList {
    return this->raw_field;
}
