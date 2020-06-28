#include "ExtremePoints.h"
#include <iostream>
#include <QVector2D>
#include <QVector>
#include <QDebug>
#include <QPicture>
#include <QPainter>
using namespace std;

int ExtremePoints::Area(QVector2D p, QVector2D q, QVector2D r){
    return p.x()*q.y() - q.x()*p.y() + q.x()*r.y() - r.x()*q.y() + p.y()*r.x() - p.x()*r.y();
}

bool ExtremePoints::ToLeft(QVector2D p, QVector2D q, QVector2D r){
    int i = Area( p , q , r );
    return i > 0;
}

int ExtremePoints::getMinYPoints(QVector<QVector2D> &points){
    int min_id = 0;
    double Miny = FLT_MAX;
    for( int i = 0 ; i < points.size() ; i ++ ){
        if( points[i].y() < Miny ){
            Miny = points[i].y();
            min_id = i;
        }
    }
    return min_id;
}

void ExtremePoints::getCos(QVector<QVector2D> &points , double *mcos ,int id ){
    double cos;
    for ( int i = 0 ; i < points.size() ; i ++ ){
        if( i == id ){
            mcos[i] = 2;
        }
        else {
            QVector2D diff = points[i] - points[id];
            cos = diff.x() / diff.length();
            mcos[i] = cos;
        }
    }
}

void ExtremePoints::sortPoints(QVector<QVector2D> &points, double *mcos){
    QVector2D tem_points;
    for( int i = 0 ; i < points.size() ; i ++){
        for( int j = 0 ; j < points.size() - i - 1 ; j ++ ){
            if( mcos[j] < mcos[j + 1] ){
                double tem_mcos;
                tem_mcos = mcos[j];
                mcos[j] = mcos[j + 1];
                mcos[j + 1] = tem_mcos;

                tem_points = points[j];
                points[j] = points[j + 1];
                points[j + 1] = tem_points;
            }
        }
    }
}

int ExtremePoints::CCW(QVector2D a, QVector2D b, QVector2D c){
    double area = a.x() * b.y() + b.x() * c.y() + c.x() * a.y() - c.x() * b.y() - b.x() * a.y() - a.x() * c.y();
    if( area < 0 ){
        return  -1;
    }
    else{
        if( area > 0)
            return 1;
        else
            return 0;
    }
}

void ExtremePoints::getOutPoints(QVector<QVector2D> &points, QVector<QVector2D> &outpoint){
    outpoint.push_back(points[0]);
    outpoint.push_back(points[1]);
    int i = 2;
    while ( true) {
        if( i == points.size() ){
            break;
        }
        if( CCW(outpoint[outpoint.size() - 2] , outpoint[outpoint.size() - 1] , points[i]) > 0 ){
            outpoint.push_back(points[i]);
            i = i + 1;
        }
        else {
            outpoint.pop_back();
        }
    }
}
