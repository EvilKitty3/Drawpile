/*
   Drawpile - a collaborative drawing program.

   Copyright (C) 2008-2014 Calle Laakkonen

   Drawpile is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Drawpile is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Drawpile.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "viewstatus.h"

#include <QLabel>
#include <QSlider>
#include <QHBoxLayout>
#include <QAction>

namespace widgets {

ViewStatus::ViewStatus(QWidget *parent)
	: QWidget(parent)
{
	setMinimumHeight(16+2);
	QHBoxLayout *layout = new QHBoxLayout(this);

	layout->setMargin(1);
	layout->setSpacing(4);

	// Zoom level
	QLabel *zlbl = new QLabel(tr("Zoom:"), this);

	_zoomSlider = new QSlider(Qt::Horizontal, this);
	_zoomSlider->setMaximumWidth(120);
	_zoomSlider->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
	_zoomSlider->setMinimum(50);
	_zoomSlider->setMaximum(1600);
	_zoomSlider->setPageStep(50);
	_zoomSlider->setValue(100);
	_zoomSlider->setContextMenuPolicy(Qt::ActionsContextMenu);
	connect(_zoomSlider, &QSlider::valueChanged, [this](int val) { emit zoomChanged(val); });

	_zoom = new QLabel("100%", this);
	_zoom->setFixedWidth(_zoom->fontMetrics().width("9999.9%"));
	_zoom->setContextMenuPolicy(Qt::ActionsContextMenu);

	layout->addWidget(zlbl);
	layout->addWidget(_zoomSlider);
	layout->addWidget(_zoom);

	addZoomShortcut(50);
	addZoomShortcut(100);
	addZoomShortcut(200);
	addZoomShortcut(400);

	// Rotation angle
	layout->addSpacing(10);
	QLabel *rlbl = new QLabel(tr("Angle:"), this);
	_angle = new QLabel(QString::fromUtf8("0°"));
	_angle->setFixedWidth(_angle->fontMetrics().width("9999.9"));
	_angle->setContextMenuPolicy(Qt::ActionsContextMenu);

	_angleSlider = new QSlider(Qt::Horizontal, this);
	_angleSlider->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));
	_angleSlider->setMinimum(-360);
	_angleSlider->setMaximum(360);
	_angleSlider->setPageStep(45);
	_angleSlider->setContextMenuPolicy(Qt::ActionsContextMenu);
	connect(_angleSlider, &QSlider::valueChanged, [this](int val) { emit angleChanged(val); });

	_angleSlider->setToolTip(tr("Drag the view while holding ctrl-space to rotate"));

	layout->addWidget(rlbl);
	layout->addWidget(_angleSlider);
	layout->addWidget(_angle);

	addAngleShortcut(-180);
	addAngleShortcut(-135);
	addAngleShortcut(-90);
	addAngleShortcut(-45);
	addAngleShortcut(0);
	addAngleShortcut(45);
	addAngleShortcut(90);
	addAngleShortcut(135);
	addAngleShortcut(180);
}

void ViewStatus::addZoomShortcut(int zoomLevel)
{
	QAction *a = new QAction(QString("%1%").arg(zoomLevel), this);
	_zoom->addAction(a);
	_zoomSlider->addAction(a);
	connect(a, &QAction::triggered, [this, zoomLevel]() {
		emit zoomChanged(zoomLevel);
	});
}

void ViewStatus::addAngleShortcut(int angle)
{
	QAction *a = new QAction(QString("%1°").arg(angle), this);
	_angle->addAction(a);
	_angleSlider->addAction(a);
	connect(a, &QAction::triggered, [this, angle]() {
		emit angleChanged(angle);
	});
}

void ViewStatus::setTransformation(qreal zoom, qreal angle)
{
	_zoomSlider->setValue(zoom);
	_angleSlider->setValue(angle);
	_zoom->setText(QString::number(zoom, 'f', 0) + "%");
	_angle->setText(QString::number(angle, 'f', 1) + QChar(0xb0));
}

}

