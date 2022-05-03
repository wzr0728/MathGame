#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>
#include <string>
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked(){
    ui->textBrowser->setText("");
    QString qsData = ui->data->text();
    std::string alldata = qsData.toStdString();
    int n = 0;
    std::string names[52];
    for(int i = 0;i < alldata.length();i++){
        if(alldata[i] == ' '){
            n+=1;
            continue;
        }
        names[n]+=alldata[i];
    }
    n+=1;
    int nums[52];
    for(int i = 0;i < n;i++){
        nums[i] = std::stoi(names[i]);
    }
    int dp[n][n];
    std::string sequence[n][n];
    for(int i = 0; i < n;i++){
        for(int j = 0;j < n;j++){
            dp[i][j] = 0;
        }
    }

    for(int i = 1;i < n-1;i++){  //選窗口
        for(int left = 1;left < n-i;left++){
            int right = left + i - 1;
            for(int j = left;j < right+1;j++){
                int lValue = dp[left][j-1];
                int rValue = dp[j+1][right];
                int element = (nums[left - 1] + nums[right + 1]) * nums[j];
                int sum = lValue+rValue+element;
                std::string tmpS = sequence[left][j-1] + sequence[j+1][right] + names[j];
                if(sum > dp[left][right]){
                    dp[left][right] = sum;
                    sequence[left][right] = tmpS + " ";
                }
            }
        }
    }
    int allScore = 0;
    int intSequence[100];
    int indexSequence = 1;
    int numLen = 0;
    for(int i = 0;i < sequence[1][n-2].length();i++){
        std::string s = sequence[1][n-2];


        if(s[i] == ' '){
            std::string str = "";
            i -= numLen ;
            for(int j = 0;j < numLen;j++){
                str = str + s[i];
                i+=1;

            }

            intSequence[indexSequence-1] = std::stoi(str);
            indexSequence+=1;

            numLen = 0;
        }else{
            numLen+=1;
        }
    }
    for(int i = 0;i < indexSequence;i++){
        for(int j = 0;j < n;j++){
            if(nums[j] == intSequence[i]){
                int getScore = (nums[j-1]+nums[j+1])*nums[j];
                allScore+=getScore ;
                for (int k = j; k < n-1; ++k) {
                    nums[k] = nums[k + 1];

                }
                n-=1;

                ui->textBrowser->append("移除： "+QString::number(intSequence[i])+"得分： "+QString::number(getScore)+"剩餘： ");
                for(int k = 0; k < n; k++){

                    ui->textBrowser->insertPlainText(QString::number(nums[k])+" ");
                }

            }
        }
    }


    ui->textBrowser->append("總分 "+QString::number(allScore)+"分");


}
