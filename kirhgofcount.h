#ifndef KIRHGOFCOUNT_H
#define KIRHGOFCOUNT_H
#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <QWidget>
#include<QString>
#include<QFile>
#include<QTextStream>
#include<QTimer>
#include<QTime>

using namespace std;
class countIUR : public QWidget{//создаётся в качестве виджета, т.к. это позволяет выделить память
  Q_OBJECT
public:
  countIUR(QString, QWidget *parent = 0);
  ~countIUR(){}
  vector <int> path;
  vector<vector <int> > paths;
  vector<bool> used;
  int** connected;//матрица соединений между узлами
  int n;//число узлов
  double s, sourse, time, phase;//ввести напряжение источника
  double** resistance,/*/матрица сопротивлений между узлами*/ **amper, **volt;
  void dfs(int, int, int**, int);
  void findcycle(int, int**);
  double countU();
};
inline countIUR::countIUR(QString filename, QWidget *parent): QWidget(parent){
  QFile f(filename);
  f.open(QIODevice::ReadOnly);
  QTextStream bridge(&f);

  bridge >> n >>s>>time>>phase;
  sourse=s;
  connected = new int*[n];
  for (int i = 0; i < n; i++)
  {
          connected[i] = new int[n];
          for (int j = 0; j < n; j++)
                  bridge>>connected[i][j];
  }

  resistance = new double* [n];
  amper = new double* [n];
  volt = new double* [n];
  for (int i = 0; i < n; i++)
  {
          resistance[i] = new double[n];
          amper[i] = new double[n];
          volt[i] = new double[n];
          for (int j = 0; j < n; j++)
          {
                  bridge >> resistance[i][j];
                  amper[i][j] = 0;
                  volt[i][j] = 0;
          }
  }
  //данные получены!!!
  if(time!=0){
      QTime t = QTime::currentTime();
        sourse=s*sin((6.28*time)*t.second()+phase);
    }
}

inline double countIUR::countU() {
	vector<double> contourampers;

	//найти замкнутые контуры
	findcycle(4, connected);

	//найти потенциалы
	for (unsigned int i = 0; i < paths.size()-1; i++) {
		double sumr=0;//ток в контуре
		for (unsigned int j = 0; j < paths[i].size() - 1; j++) {
			sumr += (resistance[paths[i][j]][paths[i][j + 1]]);//разделить напряжение пропорционально!!!
		}
		contourampers.push_back(sourse/sumr);
		if (/*nobothelements(paths[i], paths[i + 1])*/paths[i].size() == 3) {
			for (unsigned int j = 0; j < paths[i].size() - 1; j++) {

					volt[paths[i][j]][paths[i][j + 1]] = contourampers[i] * resistance[paths[i][j]][paths[i][j + 1]];//разделить напряжение пропорционально!!!
				}
			}
		}
	return (sourse-(volt[0][2]+volt[1][3]));
}
inline void countIUR::dfs(int v, int start, int** graph, int n) {
	if (used[v]) {
		if (v == start) {
			if ((path[path.size() - 1] == 3)&& (path[0] == 0)) {
				paths.push_back(path);
			}
		}
		return;
	}
	used[v] = 1;
	path.push_back(v);
	for (int i = 0; i < n; ++i)
	  {
	    if (graph[v][i])
	      {
		dfs(i, start, graph, n);
	      }
	  }
	used[v] = 0;
	path.pop_back();

}
inline void countIUR::findcycle(int n, int** graph) {

	for (int i = 0; i < n; i++) {
		used.resize(n, 0);
		dfs(i, i, graph, n);
	}
}

#endif // KIRHGOFCOUNT_H

