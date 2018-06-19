/*
 ner_leaderboard_model.cpp     MindForger thinking notebook

 Copyright (C) 2016-2018 Martin Dvorak <martin.dvorak@mindforger.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#include "ner_leaderboard_model.h"

namespace m8r {

using namespace std;

NerLeaderboardModel::NerLeaderboardModel(QWidget* parent)
    : QStandardItemModel(parent)
{
    setColumnCount(3);
    setRowCount(0);
}

NerLeaderboardModel::~NerLeaderboardModel()
{
}

void NerLeaderboardModel::removeAllRows()
{
    QStandardItemModel::clear();

    QStringList tableHeader;
    tableHeader
        << tr("Name")
        << tr("Type")
        << tr("%");

    // IMPROVE set tooltips: items w/ tooltips instead of just strings
    setHorizontalHeaderLabels(tableHeader);
}

void NerLeaderboardModel::addRow(string& entityName, string& entityType, float score)
{
    QList<QStandardItem*> items;
    QStandardItem* item;

    QString html{};
    html += QString::fromStdString(entityName);

    // item
    item = new QStandardItem(html);
    item->setToolTip(html);
    items += item;

    html.clear();
    html += QString::fromStdString(entityType);
    item = new QStandardItem(html);
    item->setToolTip(html);
    items += item;

    // TODO HTML not rendered in table :-Z
    html.clear();
    if(score>0.29) {
        html += "<span style='color: #00";
        if(score>0.69) {
            html += "CC";
        } else if(score>0.49) {
            html += "AA";
        } else if(score>0.39) {
            html += "66";
        } else if(score>0.29) {
            html += "44";
        }
        html += "00'>";
    }
    html += QString::number(score*100.);
    html += "%";
    if(score>0.29) {
        html += "</span>";
    }
    item = new QStandardItem(html);
    item->setData(QVariant::fromValue(score));
    items += item;

    appendRow(items);
}

} // m8r namespace
