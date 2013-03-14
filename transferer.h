#ifndef TRANSFERER_H
#define TRANSFERER_H

#include <QThread>
#include "FieldTransfer/FieldTransfer.h"

class Transferer : public QThread
{
    Q_OBJECT
public:
    explicit Transferer(QObject *parent = 0);

    void SetIndicatorMax(unsigned int max);

signals:
    void Indicate(int i);
    void OnFinished(uint width, uint height);

public slots:
    void run();

    void SetParameta(
            unsigned int x_col_index, unsigned int y_col_index,
            const std::string& before_file_path, const std::string& after_file_path,
            unsigned int width, unsigned int height);

    field_transfer::VectorList GetTransferedField()const;
    field_transfer::VectorList GetRawField()const;

private:
    void Transfer();

private:
    unsigned int x_col_index;
    unsigned int y_col_index;
    std::string before_file_path;
    std::string after_file_path;
    unsigned int width;
    unsigned int height;

    field_transfer::VectorList transfered_field;
    field_transfer::VectorList raw_field;

    unsigned int indicator_max;
};

#endif // TRANSFERER_H
