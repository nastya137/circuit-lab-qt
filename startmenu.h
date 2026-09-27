#ifndef STARTMENU_H
#define STARTMENU_H
#include<QMainWindow>
#include<QList>
#include<QPushButton>
#include<QGridLayout>
#include<QLabel>
#include<QString>
#include<schemewindow.h>
#include<capacitorsmeasure.h>
class startMenu: public QDialog {
    Q_OBJECT
public:

  startMenu(){
    setWindowTitle(QString::fromUtf8(u8"Задачи"));
    menu = new QGridLayout;
    QPushButton* WheatstoneBridge=new QPushButton;
    QPushButton* capacitor=new QPushButton;
    QLabel* description=new QLabel;
    QLabel* pic = new QLabel("");
    QPixmap pix;
    pix.load(":/startmenu/bridgelab.png");
    pic->setPixmap(QPixmap(pix));
    WheatstoneBridge->setText(QString::fromUtf8(u8"&Работа 1. Мост Уитстона"));
    capacitor->setText(QString::fromUtf8(u8"&Работа 2. Мост Сотти"));
    description->setText(QString::fromUtf8(u8"Выберите задание: "));
    menu->addWidget(WheatstoneBridge, 1, 1);
    menu->addWidget(capacitor, 2, 1);
    menu->addWidget(description, 0, 1);
    menu->addWidget(pic, 0,2, 3, 3);
    setLayout(menu);

    connect(WheatstoneBridge, SIGNAL(clicked()), SLOT(bridgeWheatstoneR()) );
    connect(capacitor, SIGNAL(clicked()), SLOT(bridgeWheatstoneC()) );
  }
  ~startMenu(){}
  QGridLayout* menu;
public slots:
  void bridgeWheatstoneR(){
    QString* m=new QString[3];
    m[0]=QString::fromUtf8(u8"Сопротивление резистора 1, Ом");
    m[1]=QString::fromUtf8(u8"Сопротивление резистора 2, Ом");
    m[2]=QString::fromUtf8(u8"Сопротивление резисторов 2 и 3, подключенных параллельно, Ом");

    resistanceMeasure* v = new resistanceMeasure(m, 3, QString::fromUtf8(u8"Работа 1. Мост Уитстона"));
    v->theory.setHtml(QString::fromUtf8(u8"<div style='font-size: 16px; font-family: Times New Roman'><p>Классическим методом измерения сопротивлений проводников является метод моста постоянного тока. На рис.1 изображена схема простейшего моста, называемого обычно мостом Уитстона. Он состоит из реостата АВ, чувствительного гальванометра G и двух сопротивлений – известного <i>R</i> и неизвестного <i>R</i><i><sub>x</sub></i><i>.</i> Реохорд представляет собой укрепленную на линейке однородную проволоку, вдоль которой может перемещаться скользящий контакт D.</p><div><tablе align='left'><tbody><tr><td align='left' valign='top'><p><img src=':/startmenu/clip_image002.gif' height='208' width='274' v:shapes='_x0000_i1026' align='absmiddle'></p><div style='font-size: 16px; font-family: Times New Roman'>Рис. 1<p></p></div></td></tr></tbody></table></div><p style='font-size: 16px; font-family: Times New Roman'>Рассмотрим схему без участка ED. Замкнем ключ К, тогда по проволоке АВ потечет ток и вдоль нее будет наблюдаться равномерное падение потенциала от величины φ<sub>А</sub> в точке А до величины φ<i><sub>B</sub></i> в точке В. В цепи АЕВ пойдет ток <i>I</i><sub>1</sub> и будет наблюдаться падение потенциала от φ<i><sub>A</sub></i> до φ<i><sub>E</sub></i> (на сопротивлении <i>R<sub>х</sub></i>) и от φ<i><sub>E</sub></i> до φ<i><sub>B</sub></i> (на сопротивлении <i>R</i>). Очевидно, что в точке Е потенциал имеет промежуточное значение φ<i><sub>E</sub></i> между значениями φ<i><sub>A</sub></i> и φ<i><sub>B</sub></i>. Поэтому на участке АВ всегда можно найти точку D, потенциал которой φ<i><sub>D</sub></i> равен потенциалу φ<i><sub>E</sub></i> в точке Е: φ<i><sub>D</sub></i>&nbsp;=&nbsp;φ<i><sub>E</sub></i>. Если между точками E и D включен гальванометр G, то в этом случае ток через него не пойдет, так как разность потенциалов между этими точками равна нулю.</p><p style='font-size: 16px; font-family: Times New Roman'>Такое положение называется равновесием моста. Покажем, что условие равновесия определяется соотношением:</p><div style='text-align: right;'><img src=':/startmenu/clip_image004.gif' height='45' width='69' v:shapes='_x0000_i1025' align='absmiddle'>              (1)</div><p style='font-size: 16px; font-family: Times New Roman'>Действительно, по закону Ома:</p><div>φ<i><sub>А</sub></i><i> – </i>φ<i><sub>Е</sub> = </i><i>I</i><sub>1</sub><i>R<sub>x</sub></i>            (2)</div><div>φ<i><sub>Е</sub></i><i> –</i>φ<i><sub>В</sub></i><i> = I</i><sub>1</sub><i>R</i>;<sub> </sub> (3)</div><div>φ<i><sub>А</sub></i><i> – </i>φ<i><sub>D</sub> = I</i><sub>2</sub><i>R<sub>AD</sub></i>; φ<i><sub>D</sub> – </i>φ<i><sub>B</sub> = I</i><sub>2</sub><i> R<sub>BD</sub></i>. (4)</div><p style='font-size: 16px; font-family: Times New Roman'>Так как φ<i><sub>D</sub></i><i>&nbsp;=&nbsp;</i>φ<i><sub>E</sub></i>, то последние два выражения можно переписать в виде:</p><div>φ<i><sub>A</sub> –</i>φ<i><sub>E</sub> = I</i><sub>2</sub><i>R<sub>AD</sub></i>   (5)</div><div>φ<i><sub>E</sub> – </i>φ<i><sub>B</sub> = I</i><sub>2</sub><i>R<sub>BD</sub></i>. (6)</div><div style='text-align: right;'><img src=':/startmenu/clip_image006.gif' height='47' width='143'>,&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; (7)</div><p style='font-size: 16px; font-family: Times New Roman'>где <i>L</i> – сопротивление реостата.</p><br></div></div>"));
    v->show();
  }

  void bridgeWheatstoneC(){
    QString* m=new QString[3];
    m[0]=QString::fromUtf8(u8"Ёмкость конденсатора 1, мкФ\n(до 3 знаков после запятой)");
    m[1]=QString::fromUtf8(u8"Ёмкость конденсатора 2, мкФ\n(до 3 знаков после запятой)");
    m[2]=QString::fromUtf8(u8"Ёмкость конденсаторов 1 и 3, подключенных параллельно, мкФ\n(до 3 знаков после запятой)");

    capacityMeasure* v = new capacityMeasure(m, 3, QString::fromUtf8(u8"Работа 2.Измерение ёмкостей конденсаторов"));
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), v, SLOT(update()));
    timer->start();
    v->theory.setHtml(QString::fromUtf8(u8"<div style='font-size: 16px; font-family: Times New Roman'><p>В данной работе емкость измеряется при помощи мостовой схемы – моста Сотти.</p><p><img src=':/startmenu/image042.gif'></p><p><i>С</i><i><sub>э</sub></i><i> – эталонная емкость; <i>С</i><i><sub>x</sub></i><i> – конденсатор, емкость которого надо измерить; источник переменного тока (ε); индикатор нуля (<strong><i>ИН</i></strong>, в данном случае – осциллограф); реохорд (реостат, включенный как потенциометр); <i>R</i><i><sub>1</sub></i><i> и <i>R</i><i><sub>2</sub></i><i> - сопротивления плеч <i>l</i><i><sub>1</sub></i><i> и <i>l</i><i><sub>2</sub></i><i> реостата.</p><p>Если источник тока включен, то в цепи, в том числе и на участке ED, течет ток, а на экране осциллографа видна синусоида. Подбором сопротивлений <i>R</i><i><sub>1</sub></i><i> и <i>R</i><i><sub>2</sub></i><i> (путем перемещения движка реостата) можно добиться равновесия моста, при котором разность потенциалов (<i>φ</i><i><sub>E</sub></i><i> - <i>φ</i><i><sub>D</sub></i><i>) равна нулю (состояние равновесия моста), а на экране осциллографа синусоида сменяется горизонтальной прямой. После перехода через положение равновесия амплитуда синусоиды снова увеличивается.</p><p>При равновесии моста потенциалы точек E и D равны (<i>φ</i><i><sub>E</sub></i><i> = <i>φ</i><i><sub>D</sub></i><i>). Это значит, что разность потенциалов на участке AE по величине равна разности потенциалов на участке AD :</p><p><i>φ</i><i><sub>A</sub></i><i> - <i>φ</i><i><sub>E</sub></i><i> = <i>φ</i><i><sub>A</sub></i><i> - <i>φ</i><i><sub>D</sub></i><i>. (4)</p><p>По аналогичным соображениям:</p><p><i>φ</i><i><sub>E</sub></i><i> - <i>φ</i><i><sub>B</sub></i><i> = <i>φ</i><i><sub>E</sub></i><i> - <i>φ</i><i><sub>D</sub></i><i>. (5)</p><p>Токи в ветвях AE и EB, AB и DB будут равны по величине:</p><p><i>I</i><i><sub>AE</sub></i><i> = <i>I</i><i><sub>EB</sub></i>, (6)</p><p><i>I</i><i><sub>AD</sub></i><i> = <i>I</i><i><sub>DB</sub></i>. (7)</p><p>Сопротивление участка цепи переменного тока, содержащего конденсатор, определяется по формуле</p><p><img src=':/startmenu/image089.gif'>, (8)</p><p>где C – электроемкость конденсатора; <i>ω</i> – циклическая частота.</p><p>К однородным участкам цепи  АЕ, ЕВ, АD и DВ применим закон Ома в виде:</p><p><img src=':/startmenu/image093.gif'>,</p><p>тогда равенства (6) и (7) примут вид:</p><p><img src=':/startmenu/image095.gif'>, (9)</p><p><img src=':/startmenu/image097.gif'>. (10)</p><p>Разделив почленно равенство (9) на (10), учитывая при этом равенства (4), (5) и (8) получим: <img src=':/startmenu/image099.gif'></p><p>. <img src=':/startmenu/image101.gif'>(11)</p></div>"));
    v->show();
  }
};

#endif // STARTMENU_H

