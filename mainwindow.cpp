#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <random>
#include <algo.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ApplyModel();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ApplyIterator() {
    auto dist = std::distance(deque_model_.items.begin(),deque_model_.iterator);
    ui->list_widget->setCurrentRow(dist);
    if (deque_model_.iterator == deque_model_.items.end()) {
        ui->btn_edit->setDisabled(true);
        ui->btn_right->setDisabled(true);
        ui->btn_erase->setDisabled(true);
        ui->txt_elem_content->setText("");
    } else {
        ui->btn_edit->setDisabled(false);
        ui->btn_right->setDisabled(false);
        ui->btn_erase->setDisabled(false);
        ui->txt_elem_content->setText(QString::fromStdString(*deque_model_.iterator));
    }
    if (deque_model_.iterator == deque_model_.items.begin()) {
        ui->btn_left->setDisabled(true);
    } else {
        ui->btn_left->setDisabled(false);
    }
}

void MainWindow::ApplyModel() {
    if (deque_model_.items.empty()) {
        ui->btn_pop_back->setDisabled(true);
        ui->btn_pop_front->setDisabled(true);
    } else {
        ui->btn_pop_back->setDisabled(false);
        ui->btn_pop_front->setDisabled(false);
    }
    auto preserve_iter = deque_model_.iterator;
    ui->list_widget->clear();
    int number = 0;
    for (const auto& element : deque_model_.items) {
        ui->list_widget->addItem(QString("%1: %2").arg(number).arg(QString::fromStdString(element)));
        number++;
    }
    ui->list_widget->addItem("end");
    deque_model_.iterator = preserve_iter;
    QString count = QString("%1").arg(deque_model_.items.size());
    ui->txt_size->setText(count);
    ApplyIterator();
}
void MainWindow::on_btn_pop_back_clicked()
{
    deque_model_.items.pop_back();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}
void MainWindow::on_btn_push_back_clicked()
{
    auto text = ui->txt_elem_content->text();
    deque_model_.items.push_back(text.toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();

}
void MainWindow::on_btn_clear_clicked()
{
    deque_model_.items.clear();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();

}
void MainWindow::on_btn_tea_clicked()
{
    deque_model_.items = tea;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}
void MainWindow::on_btn_cakes_clicked()
{
    deque_model_.items = cakes;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_list_widget_currentRowChanged(int currentRow)
{
    if (currentRow < deque_model_.items.size() && currentRow >= 0) {
        deque_model_.iterator = deque_model_.items.begin() + currentRow;
    } else if (currentRow < 0 ) {
        deque_model_.iterator = deque_model_.items.begin();
    } else {
        deque_model_.iterator = deque_model_.items.end();
    }
    ApplyIterator();
}

void MainWindow::on_btn_erase_clicked()
{
    deque_model_.items.erase(deque_model_.iterator);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_insert_clicked()
{
    auto text = ui->txt_elem_content->text();
    deque_model_.items.insert(deque_model_.iterator, text.toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_right_clicked()
{
    deque_model_.iterator++;
    ApplyIterator();
}

void MainWindow::on_btn_left_clicked()
{
    deque_model_.iterator--;
    ApplyIterator();
}

void MainWindow::on_btn_begin_clicked()
{
    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}

void MainWindow::on_btn_end_clicked()
{
    deque_model_.iterator = deque_model_.items.end();
    ApplyIterator();
}


void MainWindow::on_btn_edit_clicked()
{
    *deque_model_.iterator = ui->txt_elem_content->text().toStdString();
    ApplyModel();
}


void MainWindow::on_btn_resize_clicked()
{
    bool ok;
    int count = ui->txt_size->text().toInt(&ok);

    if (count <= 1000) {
        deque_model_.items.resize(count);
    }
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_find_clicked()
{
    auto find_text = std::find(deque_model_.items.begin(), deque_model_.items.end(), ui->txt_elem_content->text().toStdString());

    if (find_text != deque_model_.items.end()) {
         deque_model_.iterator = find_text;
    } else {
        deque_model_.iterator = deque_model_.items.end();
    }
    ApplyIterator();
}


void MainWindow::on_btn_count_clicked()
{
    int count_text = std::count(deque_model_.items.begin(), deque_model_.items.end(), ui->le_count->text().toStdString());
    ui->lbl_count->setText(QString("%1").arg(count_text));
}


void MainWindow::on_btn_min_element_clicked()
{
    auto min_elem = std::min_element(deque_model_.items.begin(), deque_model_.items.end());
        deque_model_.iterator = min_elem;
        ApplyIterator();
}


void MainWindow::on_btn_max_element_clicked()
{
    auto max_elem = std::max_element(deque_model_.items.begin(), deque_model_.items.end());
        deque_model_.iterator = max_elem;
        ApplyIterator();
}

void MainWindow::on_btn_sort_clicked()
{
    deque_model_.items = MergeSort(deque_model_.items, [](const std::string& a, const std::string& b) {
        return a < b;
    });

    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_sort_reg_clicked()
{
    deque_model_.items = MergeSort(deque_model_.items, [](const std::string& a, const std::string& b) {
        QString s1 = QString::fromStdString(a);
        QString s2 = QString::fromStdString(b);
        return QString::compare(s1, s2, Qt::CaseInsensitive) < 0;
    });

    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_unique_clicked()
{
    if (std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        auto vec_del = std::unique(deque_model_.items.begin(), deque_model_.items.end());
        deque_model_.items.erase(vec_del, deque_model_.items.end());
        deque_model_.iterator = deque_model_.items.begin();
    }

    ApplyModel();
}


void MainWindow::on_btn_reverse_clicked()
{
    std::reverse(deque_model_.items.begin(), deque_model_.items.end());
    ApplyModel();
}


void MainWindow::on_btn_shuffle_clicked()
{
    std::shuffle(deque_model_.items.begin(), deque_model_.items.end(), gen_shuffle_);
    ApplyModel();

}

void MainWindow::SetRandomGen(const std::mt19937& random_gen) {
    gen_shuffle_ = random_gen;
}


void MainWindow::on_btn_pop_front_clicked()
{
    deque_model_.items.pop_front();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_push_front_clicked()
{
    auto text = ui->txt_elem_content->text();
    deque_model_.items.push_front(text.toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_upper_bound_clicked()
{
    if (std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        auto text = ui->txt_elem_content->text();
        deque_model_.iterator = std::upper_bound(deque_model_.items.begin(), deque_model_.items.end(), text.toStdString() + '{');
        ApplyIterator();
    }
}


void MainWindow::on_btn_lower_bound_clicked()
{
    if (std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        auto text = ui->txt_elem_content->text();
        deque_model_.iterator = std::lower_bound(deque_model_.items.begin(), deque_model_.items.end(), text.toStdString());
        ApplyIterator();
    }
}

