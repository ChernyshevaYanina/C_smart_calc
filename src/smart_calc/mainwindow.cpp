#include "mainwindow.h"

#include "../calc.c"
#include "ui_mainwindow.h"

extern "C" {
#include "../smart_calc.h"
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_allClean, SIGNAL(clicked()), this, SLOT(AC_click()));
  connect(ui->pushButton_clean, SIGNAL(clicked()), this, SLOT(C_click()));
  connect(ui->pushButton_br_op, SIGNAL(clicked()), this, SLOT(buttonClicked()));
  connect(ui->pushButton_br_cl, SIGNAL(clicked()), this, SLOT(buttonClicked()));

  QPushButton* buttons[] = {
      ui->pushButton_0,    ui->pushButton_1,    ui->pushButton_2,
      ui->pushButton_3,    ui->pushButton_4,    ui->pushButton_5,
      ui->pushButton_6,    ui->pushButton_7,    ui->pushButton_8,
      ui->pushButton_9,    ui->pushButton_plus, ui->pushButton_minus,
      ui->pushButton_pow,  ui->pushButton_mul,  ui->pushButton_div,
      ui->pushButton_mod,  ui->pushButton_sin,  ui->pushButton_cos,
      ui->pushButton_tan,  ui->pushButton_asin, ui->pushButton_acos,
      ui->pushButton_atan, ui->pushButton_ln,   ui->pushButton_log,
      ui->pushButton_sqrt, ui->pushButton_Dot,  ui->pushButton_x};

  for (QPushButton* button : buttons) {
    connect(button, &QPushButton::clicked, this, &::MainWindow::buttonClicked);
  }

  connect(ui->pushButton_EqSign, &QPushButton::clicked, this,
          &MainWindow::equal_click);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::buttonClicked() {
  QPushButton* button = (QPushButton*)sender();
  QString inputString = ui->label->text();
  QString buttonStr = button->text();
  QChar buttonChar = button->text().at(0);
  if (ui->label->text() == '0') {
    if (!is_operand(buttonChar) || buttonChar == '-') {
      inputString = "";
    }
  } else {
    if (check_error(ui->label->text())) {
      if (buttonChar != '-' && is_operand(buttonChar)) {
        inputString = "0";
      } else {
        inputString = "";
      }
    }
  }

  inputString.append(button->text());
  ui->label->setText(inputString);
  if (inputString.length() > button->text().length() &&
      is_func(button->text())) {
    if (((inputString.at(inputString.length() - (1 + button->text().length()))
              .isDigit()) ||
         inputString.at(inputString.length() - (1 + button->text().length())) ==
             ')' ||
         inputString.at(inputString.length() - (1 + button->text().length())) ==
             'x') &&
        is_func(buttonStr)) {
      inputString.chop(button->text().length());
      inputString.append('*');
      inputString.append(button->text());
    }

    if ((inputString.at(inputString.length() - (1 + button->text().length())) ==
         '.') &&
        is_func(button->text())) {
      inputString.chop(button->text().length() + 1);
      inputString.append(button->text());
    }
  }
  if (is_func(buttonStr)) {
    inputString.append('(');
  }

  if (inputString.length() > 1) {
    if ((inputString.at(inputString.length() - 2).isDigit() ||
         inputString.at(inputString.length() - 2) == 'x') &&
        (!is_operand(inputString.at(inputString.length() - 1)) &&
         (inputString.at(inputString.length() - 1) != ')') &&
         !(inputString.at(inputString.length() - 1).isDigit()) &&
         inputString.at(inputString.length() - 1) != '.')) {
      inputString.chop(1);
      inputString.append('*');
      inputString.append(button->text());
    }
    if ((inputString.at(inputString.length() - 1) == ')' ||
         inputString.at(inputString.length() - 1) == '(') &&
        inputString.at(inputString.length() - 2) == '.') {
      inputString.chop(1);
    }
    if ((inputString.at(inputString.length() - 1) == 'x' &&
         inputString.at(inputString.length() - 2) == '.')) {
      inputString.chop(1);
    }

    if (((inputString.at(inputString.length() - 1).isDigit()) ||
         ((inputString.at(inputString.length() - 1) == 'x'))) &&
        (inputString.at(inputString.length() - 2) == ')')) {
      inputString.chop(1);
      inputString.append('*');
      inputString.append(button->text());
    }
    if (is_operand(inputString.at(inputString.length() - 1)) &&
        (is_operand(inputString.at(inputString.length() - 2)) ||
         inputString.at(inputString.length() - 2) == '.')) {
      inputString.chop(2);
      inputString.append(button->text());
    }
  }
  if (button->text() == '.' && inputString.length() > 1) {
    if ((is_operand(inputString.at(inputString.length() - 2)) ||
         (inputString.at(inputString.length() - 2) == 'x')) ||
        ((inputString.at(inputString.length() - 2) == '(') ||
         (inputString.at(inputString.length() - 2) == ')'))) {
      inputString.chop(1);
    } else {
      int check_point = 0;
      for (int i = inputString.length() - 1; i > 0; i--) {
        if (inputString.at(i) == '.') {
          check_point++;
        }
        if (test_sign(inputString.at(i)) || check_point > 1) {
          i = 0;
          if (check_point > 1) {
            inputString.chop(1);
          }
        }
      }
    }
  }
  if (button->text() == '.' && inputString.length() == 1) {
    inputString = "0" + button->text();
  }
  if (inputString.at(0) == ')') {
    inputString.chop(1);
  }

  ui->label->setText(inputString);
}

bool MainWindow::check_error(QString str) {
  bool result = false;
  if (str == "nan" || ui->label->text() == "inf" ||
      str == "-inf") {
    result = true;
  }
  return result;
}

bool MainWindow::test_sign(const QChar ch) {
  bool result = false;
  if ((static_cast<int>(ch.toLatin1()) >= 42 &&
       static_cast<int>(ch.toLatin1()) <= 45) ||
      static_cast<int>(ch.toLatin1()) == 37 ||
      static_cast<int>(ch.toLatin1()) == 94 ||
      static_cast<int>(ch.toLatin1()) == 47) {
    result = true;
  }
  return result;
}

bool MainWindow::is_func(QString func) {
  bool result = false;

  if (func == "sin" || func == "cos" || func == "tan" || func == "asin" ||
      func == "acos" || func == "atan" || func == "ln" || func == "log" ||
      func == "sqrt") {
    result = true;
  }
  return result;
}

bool MainWindow::is_operand(QChar op) {
  bool result = false;
  if (op == '+' || op == '*' || op == '/' || op == '%' || op == '^' ||
      op == '-') {
    result = true;
  }

  return result;
}

void MainWindow::AC_click() {
  QString inputString = ui->label->text();
  inputString.clear();
  ui->label->setText("0");
}

void MainWindow::C_click() {
  QString inputString = ui->label->text();
  if (eqButtonClicked) {
    inputString.clear();
    ui->label->setText("0");
    eqButtonClicked = false;
  } else {
    if (inputString.at(inputString.length() - 1) == '(') {
      inputString.chop(1);
      QString str_check = inputString.right(4);
      if (str_check == "asin" || str_check == "acos" || str_check == "atan" ||
          str_check == "sqrt") {
        inputString.resize(inputString.size() - 4);
      } else {
        str_check = inputString.right(3);
        if (str_check == "sin" || str_check == "cos" || str_check == "tan" ||
            str_check == "log") {
          inputString.resize(inputString.size() - 3);
        } else {
          str_check = inputString.right(2);
          if (str_check == "ln") {
            inputString.resize(inputString.size() - 2);
          }
        }
      }
      ui->label->setText(inputString);
    } else {
      inputString.chop(1);
      ui->label->setText(inputString);
    }
  }
  if (inputString.length() == 0) {
    ui->label->setText("0");
  }
}

void MainWindow::replase_nan() {
  if (ui->label->text() == "nan" || ui->label->text() == "inf" ||
      ui->label->text() == "-inf") {
    ui->label->setText("Invalid");
  }
}

void MainWindow::equal_click() {
  eqButtonClicked = true;
  QString inputString = ui->label->text();
  if (inputString.contains("Invalid")) {
    ui->label->setText("0");
  } else {
    if (inputString.contains('x')) {
      inputString.replace('x', QString::number(ui->doubleSpinBox->value()));
    }
    int count_op_br = inputString.count('(');
    int count_cl_br = inputString.count(')');
    int count_br = 0;
    int loop_break = 0;
    for(int i = 0; i < inputString.length() - 1 && loop_break == 0; i++){
        if (inputString.at(i) == '('){
            count_br += 1;
        }
        if (inputString.at(i) == ')'){
            count_br -= 1;
        }
        if(count_br < 0){
            loop_break =1;
        }
    }
    if (count_br < 0 || count_op_br != count_cl_br) {
      ui->label->setText("Invalid");
    } else {
      double result = 0.0;
      toQt(inputString.toStdString().c_str(), &result);
      QString ans =QString::number(result, 'f', 7).trimmed();
      while (ans.endsWith('0') && ans.contains('.')){
          ans.chop(1);
      }
      if (ans.endsWith('.')){
          ans.chop(1);
      }
      ui->label->setText(ans);
      replase_nan();
    }
  }
}

void MainWindow::on_toolButton_clicked() {
  ui->graf->clearGraphs();
  ui->graf->addGraph();
  ui->graf->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag);

  QString inputString = ui->label->text();

  double x_min = ui->doubleSpinBox_2->value();
  double x_max = ui->doubleSpinBox_3->value();

  if ((x_min >= -1000000 && x_min <= 1000000) &&
      (x_max >= -1000000 && x_max <= 1000000)) {
    double h = 0.01;
    QVector<double> xData;
    QVector<double> yData;
    if (x_min < x_max) {
      while (x_min <= x_max) {
        QString inputStringX = inputString;
        inputStringX.replace("x", QString::number(x_min, 'f', 7));
        double result = 0.0;
        toQt(inputStringX.toStdString().c_str(), &result);
        xData.append(x_min);
        yData.append(result);
        x_min += h;
      }
      ui->graf->graph(0)->setData(xData, yData);
      ui->graf->xAxis->setRange(xData.first(), xData.last());
      ui->graf->yAxis->setRange(
                *std::min_element(yData.constBegin(), yData.constEnd()),
                *std::max_element(yData.constBegin(), yData.constEnd()));
    } else {
      QMessageBox::warning(this, "Error", "Invalid x");
    }
  } else {
    QMessageBox::warning(this, "Error", "Invalid x");
  }
  QCPAxisRect* rect = ui->graf->axisRect();
  rect->setRangeZoomAxes(ui->graf->xAxis, ui->graf->yAxis);
  rect->setRangeDragAxes(ui->graf->xAxis, ui->graf->yAxis);
  rect->setRangeZoom(Qt::Horizontal | Qt::Vertical);

  ui->graf->replot();
}
