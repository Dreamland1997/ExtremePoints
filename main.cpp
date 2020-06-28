#include <iostream>
#include <vector>
#include <math.h>
#include <QDebug>

#include <QPicture>
#include <QPainter>
#include "ExtremePoints.h"
#include <QRandomGenerator>
#include <QTime>

#include "window.h"
#include "renderarea.h"
#include <QApplication>
#include <unordered_map>

#include <QtAlgorithms>


using namespace std;

int main( int argc , char **argv ){
    QApplication app( argc , argv );

    QVector<QVector2D> points;
    QRandomGenerator random;
    random.seed(QTime::currentTime().msecsSinceStartOfDay());
    int maxRandom = 600;
    for( int i = 0 ; i < 20 ; i ++ ){
        points.push_back(QVector2D(random.generateDouble()*maxRandom,
                                   random.generateDouble()*maxRandom));
    }

    ExtremePoints extremepoints;

    QVector<QVector2D> result;

    Q_INIT_RESOURCE(Image);

    Window window;

    qDebug() << "Number of random points :" << points.size();
    for( int i = 0 ; i < points.size() ; i ++ ){
        window.renderArea->points.append(QPointF(points[i].x(),points[i].y()));
        qDebug() << points[i];
    }

    vector<bool> flag( points.size() , false );    //vector initialization ,make the generated points.size() data is false
    for ( int p = 0 ; p < points.size() ; p ++ ){
        for( int q = 0 ; q < points.size() ; q ++ ){
            for( int r = 0 ; r < points.size() ; r ++ ){
                for ( int s = 0 ; s < points.size() ; s ++ ){
                    if( p == q || q == r || r == p )
                        continue;
                    if( s == p || s == q || s == r || flag[s] == true )
                        continue;
                    if( extremepoints.ToLeft(points[p],points[q],points[s])
                            && extremepoints.ToLeft(points[q],points[r],points[s])
                            && extremepoints.ToLeft(points[r],points[p],points[s]))
                        flag[s] = true;
                }
            }
        }
    }
    for( int i = 0 ; i < points.size() ; i++ ){
        qDebug() << flag[i];
        if( flag[i] == false ){
            QVector<double> mcos(points.size());
            extremepoints.getMinYPoints(points);
            extremepoints.getCos(points,mcos.data(),extremepoints.getMinYPoints(points));
            extremepoints.sortPoints(points,mcos.data());
            extremepoints.getOutPoints(points,result);
            qDebug() << result[i].x() << " " << result[i].y();
        }
    }
    for(int i = 0; i < result.size(); i++){
        window.renderArea->convex.append(QPointF(result[i].x(),result[i].y()));
    }

    window.show();
    return  app.exec();
}

