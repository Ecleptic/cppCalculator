#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QStack>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_1,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_7,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_8,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_9,SIGNAL(released()),this,SLOT(digit_pressed()));

    connect(ui->pushButton_Add,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_Subtract,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_Multiply,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pushButton_Divide,SIGNAL(released()),this,SLOT(digit_pressed()));

}

MainWindow::~MainWindow()
{
    delete ui;
}



bool isdigit(QString input)
{
    QRegExp re("\\d*");  // a digit (\d), zero or more times (*)
    if (re.exactMatch(input)){return true;}return false;

}


bool isNumber(QString numberExpression) {
    bool isANumber = false;

    for (QChar i : numberExpression) {
        if (isdigit(i))
            isANumber = true;
    }
    return isANumber;
}


bool isOperator(QString input) {
    return input == "+" || input == "-" || input == "*" || input == "/";
}



QString calc(QVector<QString> postfix) {
    QStack<QString> S;

    for (int x = 0; x != postfix.size(); x++) {
        if (isNumber(postfix[x])) {
            S.push(postfix[x]);
        } else if (isOperator(postfix[x])) {
            int a = S.top().toInt();
            S.pop();
            int b = S.top().toInt();
            S.pop();
            if (postfix[x] == "+") {
                QString result = QString::number(b + a);
//                QString result = to_QString(b + a);
                S.push(result);
            } else if (postfix[x] == "-") {
                QString result = QString::number(b - a);
                S.push(result);
            } else if (postfix[x] == "*") {
                QString result = QString::number(b * a);
                S.push(result);
            } else if (postfix[x] == "/") {
                QString result = QString::number(b / a);
                S.push(result);
            } else {
                qDebug() << "something's wrong...";
            }
        } else {
            qDebug() << "something else is wrong...";
        }
    }
    return S.top();
}


QVector<QString> infixToPostfix(QVector<QString> expression) {

   QStack<QString> S;

    QVector<QString> output;


    for (int x = 0; x != expression.size(); x++) {
        if (isNumber(expression[x])) {
            output.push_back(expression[x]);
        } else if (isOperator(expression[x])) {
           bool checkAgain = true;
            while (checkAgain) {

                if (S.empty()) {
                    S.push(expression[x]);
                    checkAgain = false;
                } else {
                    QString top = S.top();
                    QString op = expression[x];
                    if (op == "*" || op == "/") {
                        if (top == "+" || top == "-") {
                            S.push(op);
                            checkAgain = false;

                        } else if (top == "*" || top == "/") {
                            output.push_back(top);
                            S.pop();
                            S.push(op);
                            checkAgain = false;
                        }
                    } else if (op == "+" || op == "-") {
                        output.push_back(top);
                        S.pop();
                    } else {
                        qDebug() << "I made an error somewhere\n";
                        qDebug() << "Top: " << top << " Op: " << expression[x] << "\n";
                        checkAgain = false;
                    }
                }
            }
        }

        if (x == expression.size() - 1) {
            while (!S.empty()) {
                output.push_back(S.top());
                S.pop();
            }
        }
    }
    return output;
}



QVector<QString> parseInput(QString expression) {
    QVector<QString> inputVector;
    QString tempQString = "";

    for (int i = 0; i < expression.length(); ++i) {
        QChar currentChar = expression[i];

        if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
            inputVector.push_back(tempQString);
            inputVector.push_back(QString(1, currentChar));
            tempQString = "";

        } else if (currentChar == ' ' || currentChar == ',') {
            // do nothing
        } else {
            tempQString += currentChar;
        }
        if (i == expression.length() - 1) {
            inputVector.push_back(tempQString);
        }
    }
    return inputVector;
}





void MainWindow::digit_pressed()
{
//    qDebug() << "Test";
    QPushButton * button = (QPushButton*)sender();

    QString labelNumber;
    QString newLabel;


//    qDebug() << ui->label->text();

    if(ui->label->text() == "0"){
        labelNumber =  button->text();
    }else{
        labelNumber = (ui->label->text() + button->text());

    }

        newLabel = labelNumber;

    ui->label->setText(newLabel);


}

void MainWindow::on_pushButton_decimal_released()
{
    // TODO: not currently checking if there already is a decimal
    ui->label->setText(ui->label->text()+".");
}

void MainWindow::unary_operator_pressed()
{
    QPushButton * button = (QPushButton*)sender();
    double labelNumber;
    QString newLabel;

    if(button->text() == "+/-")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * -1;
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);

    }
    if(button->text() == "%")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * .01;
        newLabel = QString::number(labelNumber,'g',15);
        ui->label->setText(newLabel);

    }
}

void MainWindow::on_pushButton_clear_released()
{
    ui->pushButton_Add->setChecked(false);
    ui->pushButton_Subtract->setChecked(false);
    ui->pushButton_Multiply->setChecked(false);
    ui->pushButton_Divide->setChecked(false);

    ui->label->setText("0");
}

void MainWindow::on_pushButton_equal_released()
{
    std::vector<std::pair<QString, QString>> replacements {
        { "X", "*" },
        { "÷", "/"  },
        { "X", "*" }
    };

   QString label = ui->label->text();
//   ui->label->setText("0");


     qDebug() <<  label;

    for ( auto const &r : replacements) {
        label.replace(r.first, r.second);
    }

    qDebug() <<  label;
    // TODO: Send new label to parse and return it as result

    QVector<QString> input = parseInput(label);
    QVector<QString> postfix = infixToPostfix(input);

    QString calculated =  calc(postfix);

    qDebug() << calculated;
    ui->label->setText(calculated);


}

