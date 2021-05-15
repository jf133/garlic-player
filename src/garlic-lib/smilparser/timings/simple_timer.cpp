/*************************************************************************************
    garlic-player: SMIL Player for Digital Signage
    Copyright (C) 2021 Nikolaos Sagiadinos <ns@smil-control.com>
    This file is part of the garlic-player source code

    This program is free software: you can redistribute it and/or  modify
    it under the terms of the GNU Affero General Public License, version 3,
    as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*************************************************************************************/
#include "simple_timer.h"

Timings::SimpleTimer::SimpleTimer(QObject *parent)
{
    Q_UNUSED(parent);
 }

Timings::SimpleTimer::~SimpleTimer()
{
    deleteTimer();
}


void Timings::SimpleTimer::parse(QString attr_value)
{
    if (attr_value == "" || attr_value == "indefinite")
    {
        type = TYPE_INDEFINITE;
    }
    else if (attr_value == "media")
    {
        type = TYPE_MEDIA;
    }
    else
    {
        type = TYPE_CLOCKVALUE;
        MyClockValue.parse(attr_value);
        initTimer();
        clock_in_ms = MyClockValue.getTriggerInMSec();
    }
    return;
}

bool Timings::SimpleTimer::isActive()
{
    if (MyTimer == Q_NULLPTR)
        return false;

    if (type != TYPE_INDEFINITE) // when infinite timer will never end
         return true;

    if (type != TYPE_MEDIA)
         return false;

    return MyTimer->isActive();
}

bool Timings::SimpleTimer::start()
{
    if (MyTimer == Q_NULLPTR || type != TYPE_CLOCKVALUE)
        return false;

    // todo what happens if end !="indefinite"
    if (getType() == TYPE_INDEFINITE)
        return true; // no timer needed on indefinite

    MyTimer->start(clock_in_ms-tolerance);
    return true;
}

void Timings::SimpleTimer::resume()
{
    if (MyTimer == Q_NULLPTR || type != TYPE_CLOCKVALUE)
        return;

    MyTimer->start(remaining);
}


void Timings::SimpleTimer::pause()
{
    if (MyTimer != Q_NULLPTR && MyTimer->isActive())
    {
        remaining = MyTimer->remainingTime();
        MyTimer->stop();
    }
    pause_start = QDateTime::currentMSecsSinceEpoch();
}

void Timings::SimpleTimer::stop()
{
    if (MyTimer != Q_NULLPTR && MyTimer->isActive())
    {
        MyTimer->stop();
    }
    remaining = 0;
}

void Timings::SimpleTimer::setExternCalculatedTimeClock(qint64 new_clock)
{
    clock_in_ms = new_clock;
}


qint64 Timings::SimpleTimer::getOriginalTimeClock()
{
    if (type != TYPE_CLOCKVALUE)
        return type;

    return clock_in_ms;
}

int Timings::SimpleTimer::getRemaining() const
{
    return remaining;
}

void Timings::SimpleTimer::initTimer()
{
    MyTimer = new QTimer(this);
    connect(MyTimer, SIGNAL(timeout()), this, SLOT(emitTimeout()));
    MyTimer->setSingleShot(true);
    MyTimer->setTimerType(Qt::PreciseTimer);
}

void Timings::SimpleTimer::deleteTimer()
{
    if (MyTimer != Q_NULLPTR)
    {
        stop();
        delete MyTimer;
        MyTimer = Q_NULLPTR;
    }
}
void Timings::SimpleTimer::emitTimeout()
{
    emit timeout();
}
