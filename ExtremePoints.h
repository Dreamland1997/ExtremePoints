#ifndef __CONVEX_H__
#define __CONVEX_H__

#include <QVector2D>
#include <QVector>

class ExtremePoints{
public:
    int Area( QVector2D p , QVector2D q ,QVector2D r );

    bool ToLeft( QVector2D p , QVector2D q ,QVector2D r );

    int getMinYPoints( QVector<QVector2D>  &points );

    void getCos( QVector<QVector2D> &points , double *mcos , int id );

    void sortPoints( QVector<QVector2D> &points , double *mcos );

    int CCW( QVector2D a , QVector2D b , QVector2D c );

    void getOutPoints( QVector<QVector2D> &points , QVector<QVector2D> &outpoint );

};

#endif
