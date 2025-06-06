#include "Enemy.h"

Enemy::Enemy(QObject* parent): m_x(rand() % 1450), m_y(-40), ySpeed(1), m_index(rand()%5)
{
   // m_index = rand() % 5;
    connect(&eTime, &QTimer::timeout, this, &Enemy::updateEnemy);
    eTime.start(30);
}

void Enemy::updateEnemy()
{
    setY(m_y + ySpeed);
}

