#ifndef SCHEMEWINDOW_H
#define SCHEMEWINDOW_H

#include<QMainWindow>
#include<QPushButton>
#include<QLabel>
#include<QGridLayout>
#include<QGroupBox>
#include<QLineEdit>
#include<QVector>
#include<QString>
#include<QDialog>
#include<QTextEdit>
#include<QScrollArea>
#include<QMessageBox>
#include<QToolTip>
#include<meterciferblat.h>
#include<kirhgofcount.h>
#include<reostat.h>

using namespace std;

class resistanceMeasure: public QDialog{
  Q_OBJECT
public:
  resistanceMeasure(QString* labelstext, int amount, QString title){
    setWindowTitle(title);
    connections=new bool* [8];
    //resistors=new float* [8];
    for(int i=0; i<8; i++){
        connections[i]=new bool [8];
        //resistors[i]=new float[8];
        for(int j=0; j<8; j++){
            connections[i][j]=0;
            //resistors[i][j]=0;
          }
      }
    view=new QGridLayout;
    for(int i=0; i<amount; i++){
        QLabel* label=new QLabel;
        QLineEdit* answerField=new QLineEdit;
        label->setText(labelstext[i]);
        label->setBuddy(answerField);
        view->addWidget(label, i+4, 0, 1, 4);
        view->addWidget(answerField, i+4, 4, 1, 4);
        keepanswers.push_back(answerField);
        tasks.push_back(label);
      }
    //кнопка ввода
    QPushButton* inputanswers=new QPushButton;
    QPushButton *fortheory=new QPushButton;
    fortheory->setText(QString::fromUtf8("&Показать теорию"));
    inputanswers->setText(QString::fromUtf8("&Ввести и проверить ответы"));
    view->addWidget(inputanswers, amount+4, 0, 1, 4);
    view->addWidget(fortheory, amount+4, 4, 1, 4);
    //Теория, после создания объекта дополнительно потребуется вводить текст теории к каждой работе
    theory.setHtml(QString::fromUtf8("Теория появится позже"));
    theory.setTextInteractionFlags(Qt::TextBrowserInteraction);
    a.setTextInteractionFlags(Qt::TextBrowserInteraction);
    //блок со схемой
    scheme = new QScrollArea;

    QPixmap pix;
    pix.load(":/startmenu/bridgelab.png");
    QPalette p = palette();
    QBrush* brush=new QBrush;
    brush->setTextureImage(QImage(":/startmenu/bridgelab.png"));
    p.setBrush(QPalette::Window, *brush);
    setPalette(p);

    count=new countIUR(QString::fromUtf8(":/startmenu/wbridge.txt"), this);
    startr1=count->resistance[0][2];
    startr2=count->resistance[2][3];

    onoff = new QPushButton(this);
    onoff->setToolTip(QString::fromUtf8("Нажмите на кнопку, чтобы включить/выключить установку.\nВ выключенном состоянии ток в цепи отсутствует.<font color=\"white\">"));
    onoff->setGeometry(461,90,40,40);
    onoff->setStyleSheet(
          "background-color: red; border-style: outset;border-width: 2px; border-radius: 20px; border-color: beige; font: bold 14px; padding: 10px;"
          );
    clock = new MyClock(this);
    clock->setToolTip(QString::fromUtf8("Гальванометр - чувствительный вольтметр.\nВ данной работе служит индикатором нуля."));
    clock->setGeometry(50,50,300,150);
    reo=new reostat(this);
    reo->setToolTip(QString::fromUtf8("Реостат, изменяющий сопротивление от 0 до 120 Ом.\n Для поворота реостата поверните колесо мыши."));
    reo->setGeometry(128,430,125,125);
    ison=false;
    buttonsfields=new QWidget(this);
    buttonsfields->setLayout(view);
    buttonsfields->setGeometry(0,600,pix.width(),250);
    buttonsfields->setStyleSheet("background-color: beige; font: 15px Times New Roman; padding: 10px;");

    theory.resize(pix.width(), pix.height()+250);
    QRect node1(QPoint(294,182), QPoint(304,192));//узлы для подключения прводов
    nodes.push_back(node1);
    QRect node2(QPoint(390,183), QPoint(400,193));
    nodes.push_back(node2);
    QRect node3(QPoint(391,375), QPoint(401,385));
    nodes.push_back(node3);
    QRect node4(QPoint(482,183), QPoint(492,193));
    nodes.push_back(node4);
    QRect node5(QPoint(483,375), QPoint(493,385));
    nodes.push_back(node5);
    QRect node6(QPoint(340,474), QPoint(350,484));
    nodes.push_back(node6);
    QRect node7(QPoint(532,474), QPoint(542,484));
    nodes.push_back(node7);
    QRect node8(QPoint(295,373), QPoint(305,383));
    nodes.push_back(node8);

    resistors=new float* [8];
    for(int i=0; i<8; i++){
        resistors[i]=new float[8];
        for(int j=0; j<8; j++){
            resistors[i][j]=0;
          }
      }

    resistors[2][1]=660;
    resistors[1][2]=660;
    resistors[3][4]=180;
    resistors[4][3]=180;
    resistors[6][5]=90;
    resistors[5][6]=90;
    resistors[0][7]=0.00000000001;
    resistors[7][0]=0.00000000001;
    connections[2][1]=1;
    connections[1][2]=1;
    connections[3][4]=1;
    connections[4][3]=1;
    connections[6][5]=1;
    connections[5][6]=1;
    connections[0][7]=1;
    connections[7][0]=1;

    drawIndicator=0;

    n=new QString[3];
    n[0]="660";
    n[1]="180";
    n[2]="60";

    connect(fortheory, SIGNAL(clicked()), &theory, SLOT(show()));
    connect(onoff, SIGNAL(clicked()), SLOT(onOffChange()));
    connect(inputanswers, SIGNAL(clicked()), SLOT(acceptdialog()));

  }

  ~resistanceMeasure(){}
  bool** connections;
  float** resistors;
  QWidget* buttonsfields;
  QPushButton *onoff;
  QGridLayout* view;
  QTextEdit theory;
  QTextEdit a;
  QScrollArea *scheme;
  QTabBar       *WorkView;
  QMessageBox *msg;
  QString messagecontent;
  QVector<QLineEdit*> keepanswers;
  QVector<QLabel*> tasks;
  MyClock* clock;
  reostat* reo;
  countIUR* count;
  QVector<QRect> nodes;
  QPair<int, int> currentwirepos;
  QString *n;
  bool ison;
  bool drawIndicator;
  double startr1, startr2;
  float x1,y1,x2,y2;
  vector <int> path;
  vector<vector <int>> paths;
  vector<bool> used;
  void wheelEvent(QWheelEvent* event){//при повороте  колеса мыши меняет поворот реостата и, соответственно, показания гальванометра
    reo->k=event->delta()/26.666667;
    reo->numDegrees += reo->k;
    if((reo->numDegrees)>270)
      reo->numDegrees=270;
    else if ((reo->numDegrees)<0)
      reo->numDegrees=0;
    else{
        if(ison){
            paths.clear();
            for (int i = 0; i < 8; i++) {
                used.resize(8, 0);
                dfs(i, i);
              }
            if (paths.empty()){
                QMessageBox m;
                m.setIcon(QMessageBox::Warning);
                m.setText(QString::fromUtf8(u8"Цепь не замкнута!!!"));
                m.exec();
              }
            else {
                count->resistance[0][2]=startr1+reo->numDegrees/2.25;
                count->resistance[2][0]=startr1+reo->numDegrees/2.25;
                count->resistance[2][3]=startr2-reo->numDegrees/2.25;
                count->resistance[3][2]=startr2-reo->numDegrees/2.25;
                if (myRes() > 0.0000001) {count->resistance[1][3]=myRes();}
                if (myRes()<= 0) {
                    QMessageBox m;
                    m.setIcon(QMessageBox::Warning);
                    m.setText(QString::fromUtf8(u8"Цепь не замкнута!!!"));
                    m.exec();
                  }
                count->resistance[3][1]=count->resistance[1][3];
                clock->k=count->countU()*15;
                reo->update();
                clock->update();
              }
          }
      }

  }
  virtual void paintEvent(QPaintEvent*)//рисует провода
  {
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap));
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.begin(this);
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if ((connections[i][j]==1)&&(resistors[i][j]==0))painter.drawLine(QPoint(nodes.at(i).x()+5,nodes.at(i).y()+5),QPoint(nodes.at(j).x()+5,nodes.at(j).y()+5));
          }
      }
    painter.end();
  }
  virtual void mousePressEvent(QMouseEvent *pe)//при нажатии на узел появится точка подключения очередного провода
  {
    if((drawIndicator==0)&&((nodes.at(0).contains(pe->pos(), false))||(nodes.at(1).contains(pe->pos(), false))||(nodes.at(2).contains(pe->pos(), false))||(nodes.at(3).contains(pe->pos(), false))||(nodes.at(4).contains(pe->pos(), false))||(nodes.at(5).contains(pe->pos(), false))||(nodes.at(6).contains(pe->pos(), false))||(nodes.at(7).contains(pe->pos(), false)))){
        x1=pe->x();
        y1=pe->y();
        for(int i=0; i<8; i++){
            if(nodes.at(i).contains(pe->pos(), false)) currentwirepos.first=i;
          }
        update();
        drawIndicator=!drawIndicator;
      }
    else if((drawIndicator==1)&&((nodes.at(0).contains(pe->pos(), false))||(nodes.at(1).contains(pe->pos(), false))||(nodes.at(2).contains(pe->pos(), false))||(nodes.at(3).contains(pe->pos(), false))||(nodes.at(4).contains(pe->pos(), false))||(nodes.at(5).contains(pe->pos(), false))||(nodes.at(6).contains(pe->pos(), false))||(nodes.at(7).contains(pe->pos(), false)))){
        x2=pe->x();
        y2=pe->y();
        for(int i=0; i<8; i++){
            if(nodes.at(i).contains(pe->pos(), false)) currentwirepos.second=i;
          }
        if(currentwirepos.first!=currentwirepos.second){
            connections[currentwirepos.first][currentwirepos.second]=!connections[currentwirepos.first][currentwirepos.second];
            connections[currentwirepos.second][currentwirepos.first]=!connections[currentwirepos.second][currentwirepos.first];
          }
        update();
        drawIndicator=!drawIndicator;
      }
  }
  void mouseMoveEvent(QMouseEvent *event){
    for(int i=0; i<8; i++){
        if(nodes.at(i).contains(event->pos(), false))
          QToolTip::showText(event->pos(), QString::fromUtf8(u8"Нажмите, чтобы присоединить провод"), this);
      }
  }
  inline void dfs(int v, int start) {
    if (used[v]) {
        if (v == start) {
            if ((noboth(paths, path))&&(path[0] == 0)&&(path.size()>=2)) {
                paths.push_back(path);
              }
          }
        return;
      }
    used[v] = 1;
    path.push_back(v);
    for (int i = 0; i < 8; ++i)
      {
        if (connections[v][i])
          {
            dfs(i, start);
          }
      }
    used[v] = 0;
    path.pop_back();
  }
  double myRes(){
    resistors[2][1]=660;
    resistors[1][2]=660;
    resistors[3][4]=180;
    resistors[4][3]=180;
    resistors[6][5]=90;
    resistors[5][6]=90;
//    resistors[0][7]=0.00000000001;
//    resistors[7][0]=0.00000000001;
    float v;
    count->countU();
    v=count->volt[1][3];
    //найти замкнутые контуры
    float amper=0;
    double sumr;
    for (unsigned int i = 0; i < paths.size()-1; i++) {
        sumr=0;//ток в контуре
        if((paths[i].size()>=4)&&(paths[i][paths[i].size() - 1] == 7) && (paths[i][0] == 0)){
            for (unsigned int j = 0; j < paths[i].size() - 1; j++) {
                sumr += (resistors[paths[i][j]][paths[i][j + 1]]);//разделить напряжение пропорционально!!!
              }
            if(sumr>0) amper+=v/sumr;
          }
      }
    return v/amper;
  }
  bool noboth(vector<vector<int>> v,vector<int> v1){
    set<int> s, s1;
    for(int i=0; i<v1.size(); i++){
        s1.insert(v1[i]);
      }
    for(int i=0; i<v.size(); i++){
        if(v[i].size()==v1.size()){
            for(int j=0; j<v[i].size(); j++){
                s.insert(v[i][j]);
              }
            if(s==s1) return false;
            s.clear();
          }
      }

    return true;
  }
public slots:
  void onOffChange(){
    ison=!ison;
  }
  void acceptdialog(){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    QString s="";
    for(int i=0; i<3; i++){
        s=s+this->tasks[i]->text()+QString::fromUtf8(u8"\n Ваш ответ: ")+this->keepanswers[i]->text();
        if(this->keepanswers[i]->text()==n[i]) s=s+QString::fromUtf8(u8" (верно)");
        else s=s+QString::fromUtf8(u8" (неверно)");
        s=s+QString::fromUtf8(u8"\n");
      }
    msgBox.setText(QString::fromUtf8(u8"Проверка ответов"));
    msgBox.setText(s);
    msgBox.exec();
  }
};
#endif // SCHEMEWINDOW_H


