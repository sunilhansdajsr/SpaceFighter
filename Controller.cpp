#include "Controller.h"

Controller::Controller(QObject* parent): m_x(1450/2 - 50), m_y(922/2 - 50), xSpeed(10), minX(0), maxX(1450), bottomY(782-100)
{
    connect(&time, &QTimer::timeout, this, &Controller::updateState);
    time.start(16);

    connect(&move, &QTimer::timeout, this, &Controller::updateMovement);
    move.start(16);

    connect(&startE, &QTimer::timeout, this, &Controller::createEnemies);
    startE.start(1000 + rand() % 2000);
}

void Controller::moveLeft()
{
    moveDirection = -1;

    if( !move.isActive())
    {
        move.start();
    }
  //  setX(m_x - xSpe
   // if(m_x < minX)
   // {
    //    setX(minX);
    //}
}

void Controller:: stopMovement()
{
    moveDirection = 0;
    move.stop();
}

QString Controller::showScore()
{
    return QString::number(score());
}

void Controller::restartGame()
{
    for(Enemy* e: enemyList)
    {
        delete e;
    }
    enemyList.clear();

    for(Bullet* b: bulletList)
    {
        delete b;
    }
    bulletList.clear();

   emit enemyChanged();
   emit bulletChanged();

    setX(1488/2 - 50);
    setY(922/2 - 50);

    setScore(0);
    emit scoreChanged();

   emit xChanged();
   emit yChanged();
}

void Controller:: moveRight()
{
    moveDirection = 1;

    if( !move.isActive())
    {
        move.start();
    }
    //{
  //      setX(m_x + xSpeed);
    //    if(m_x > maxX)
      //  {
     //   setX(maxX);
       // }
   // }
}

void Controller::applyThrust()
{
    ySpeed = maxThrust;
    if(m_y < bottomY/1.5)
    {
        ySpeed = 0;
    }
}

 void Controller::fireBullet()
{
    Bullet* newBullet = new Bullet(this, this);
    newBullet->setX(m_x);
    newBullet->setY(m_y);
    bulletList.append(newBullet);
    emit bulletChanged();
    qInfo()<<"Fired bullet";
}

void Controller::createEnemies()
{
    Enemy* newEnemy = new Enemy();
    newEnemy->setX(rand() % 1450);
    newEnemy->setY(-40);
    enemyList.append(newEnemy);

    startE.start(1000 + rand() % 2000);
    emit enemyChanged();
}

void Controller::updateState()
{
    m_y += ySpeed;
    ySpeed += gravity;

    if(m_y > bottomY)
    {
        m_y = bottomY;
    }

 checkCollison();

    for(Enemy* e : enemyList)
    {
        if(e->y() > bottomY)
        {
            emit gameOver();
            qInfo()<<"game over";
            return;
        }

        double enemyLeft = e->x();
        double enemyRight = e->x() + 50;
        double enemyTop = e->y();
        double enemyBottom = e->y() + 50;

            double playerLeft = m_x;
            double playerRight = m_x + 50;
            double playerTop = m_y;
            double playerBottom = m_y + 50;

            if(enemyRight > playerLeft && enemyLeft < playerRight && enemyTop < playerBottom && enemyBottom > playerTop)
            {
                emit gameOver();
                qInfo()<<"game over";
                return;
            }
    }

    emit yChanged();
}

void Controller::deleteBullet(Bullet *bullet)
{
    int index = bulletList.indexOf(bullet);
    if(index != -1)
    {
        delete bulletList[index];
        bulletList.removeAt(index);
        emit bulletChanged();
        qInfo()<<"Bullet Destroyed";
    }
}

void Controller::deleteEnemy(Enemy *enemy)
{
    int index = enemyList.indexOf(enemy);
    if(index != -1)
    {
        delete enemyList[index];
        enemyList.removeAt(index);
        emit enemyChanged();
        qInfo()<<"Enemy Destroyed";
    }
}

void Controller::checkCollison()
{
    for(int i = bulletList.size() -1; i>=0; i--)
    {
        Bullet* bullet = bulletList[i];

        for(int j = enemyList.size()-1; j>=0; j--)
        {
            Enemy* enemy = enemyList[j];

            double bulletLeft = bullet->x();
            double bulletRight = bullet->x() + 10;
            double bulletTop = bullet->y();
            double bulletBottom = bullet->y() + 30;

            double enemyLeft = enemy->x();
            double enemyRight = enemy->x() + 50;
            double enemyTop = enemy->y();
            double enemyBottom = enemy->y() + 50;

            if(bulletRight > enemyLeft && bulletLeft < enemyRight && bulletTop < enemyBottom && bulletBottom > enemyTop)
            {
                deleteBullet(bullet);
                deleteEnemy(enemy);
                setScore(score() + 10);
                emit scoreChanged();
            }
        }
    }
}

void Controller::updateMovement()
{
    if(moveDirection == -1 && m_x > minX)
    {
        setX(m_x - xSpeed);
    }

    if(moveDirection == 1 && m_x < maxX)
    {
        setX(m_x + xSpeed);
    }

    if(moveDirection == 0)
    {
        setX(m_x);
    }
}

