#include "Player.h"
#include <QQmlEngine>
#include "Tile.h"
#include "DeckBuilder.h"
#include "Logger.h"

Player::Player(QColor _color, QString _name, QObject *parent)
    : QObject(parent), color(_color), active(false), name(_name)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    turnTimer.setTimerType(Qt::VeryCoarseTimer);
    connect(&turnTimer, &QTimer::timeout, this, [this](){
        currentTurnSeconds++;
        emit currentTurnSecondsChanged();
    });
}

Player::Player(Player &&other) noexcept
    : color(other.color), name(other.name)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

QColor Player::getColor() const
{
    return color;
}

bool Player::isActive() const
{
    return active;
}

void Player::setActive(bool value)
{
    if (active != value)
    {
        active = value;
        emit isActiveChanged();

        if (active)
        {
            turnTimer.start(1000);
        }
        else
        {
            turnTimer.stop();

            addToPreviousTime(currentTurnSeconds);
            currentTurnSeconds = 0;
            emit currentTurnSecondsChanged();
        }
    }
}

void Player::createAbbeyTile()
{
    abbeyTile = DeckBuilder::createAbbeyTile("img/pnp/tiles", "png");
}

Tile* Player::getAbbeyTile()
{
    return abbeyTile.get();
}

void Player::scorePoints(int points)
{
    setScore(getScore() + points);
    Logger::instance()->log(std::make_shared<ScoringLogRecord>(color, name, points));
}

int Player::getScore() const
{
    return score;
}

int Player::getWheat() const
{
    return wheat;
}

int Player::getBarrels() const
{
    return barrels;
}

int Player::getCloth() const
{
    return cloth;
}

void Player::setWheatLead(bool value)
{
    if (wheatLead != value)
    {
        wheatLead = value;
        emit wheatLeadChanged();
    }
}

void Player::setBarrelsLead(bool value)
{
    if (barrelsLead != value)
    {
        barrelsLead = value;
        emit barrelsLeadChanged();
    }
}

void Player::setClothLead(bool value)
{
    if (clothLead != value)
    {
        clothLead = value;
        emit clothLeadChanged();
    }
}

int Player::getBiggestTown() const
{
    return biggestTown;
}

int Player::getBiggestRoad() const
{
    return biggestRoad;
}

bool Player::getWheatLead() const
{
    return wheatLead;
}

bool Player::getBarrelsLead() const
{
    return barrelsLead;
}

bool Player::getClothLead() const
{
    return clothLead;
}

void Player::addWheat(int amount)
{
    setWheat(wheat + amount);
}

void Player::addBarrels(int amount)
{
    setBarrels(barrels + amount);
}

void Player::addCloth(int amount)
{
    setCloth(cloth + amount);
}

void Player::setTownLead(bool value)
{
    if (townLead != value)
    {
        townLead = value;
        emit townLeadChanged();
    }
}

bool Player::getTownLead() const
{
    return townLead;
}

void Player::setRoadLead(bool value)
{
    if (roadLead != value)
    {
        roadLead = value;
        emit roadLeadChanged();
    }
}

bool Player::getRoadLead() const
{
    return roadLead;
}

QString Player::getName() const
{
    return name;
}

void Player::setPlace(int value)
{
    if (place != value)
    {
        place = value;
        emit placeChanged();
    }
}

int Player::getPlace() const
{
    return place;
}

void Player::addToPreviousTime(int seconds)
{
    if (seconds != 0)
    {
        prevTurnsSeconds += seconds;
        emit prevTurnsSecondsChanged();
    }
}

void Player::setScore(int value)
{
    if (score != value)
    {
        score = value;
        emit scoreChanged();
    }
}

void Player::setWheat(int value)
{
    if (wheat != value)
    {
        wheat= value;
        emit wheatChanged();
    }
}

void Player::setBarrels(int value)
{
    if (barrels != value)
    {
        barrels = value;
        emit barrelsChanged();
    }
}

void Player::setCloth(int value)
{
    if (cloth != value)
    {
        cloth = value;
        emit clothChanged();
    }
}

void Player::setBiggestTown(int value)
{
    if (biggestTown != value)
    {
        biggestTown = value;
        emit biggestTownChanged();
    }
}

void Player::setBiggestRoad(int value)
{
    if (biggestRoad != value)
    {
        biggestRoad = value;
        emit biggestRoadChanged();
    }
}
