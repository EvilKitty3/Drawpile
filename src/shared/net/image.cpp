/*
   Drawpile - a collaborative drawing program.

   Copyright (C) 2013-2014 Calle Laakkonen

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

#include <QtEndian>
#include "image.h"

namespace protocol {

PutImage *PutImage::deserialize(const uchar *data, uint len)
{
	if(len < 19)
		return 0;

	return new PutImage(
		*(data+0),
		*(data+1),
		*(data+2),
		qFromBigEndian<quint32>(data+3),
		qFromBigEndian<quint32>(data+7),
		qFromBigEndian<quint32>(data+11),
		qFromBigEndian<quint32>(data+15),
		QByteArray((const char*)data+19, len-19)
	);
}

int PutImage::payloadLength() const
{
	return 1 + 2 + 4*4 + _image.size();
}

int PutImage::serializePayload(uchar *data) const
{
	uchar *ptr = data;
	*(ptr++) = contextId();
	*(ptr++) = _layer;
	*(ptr++) = _flags;
	qToBigEndian(_x, ptr); ptr += 4;
	qToBigEndian(_y, ptr); ptr += 4;
	qToBigEndian(_w, ptr); ptr += 4;
	qToBigEndian(_h, ptr); ptr += 4;
	memcpy(ptr, _image.constData(), _image.length());
	ptr += _image.length();
	return ptr-data;
}

FillRect *FillRect::deserialize(const uchar *data, uint len)
{
	if(len != 23)
		return 0;

	return new FillRect(
		*(data+0),
		*(data+1),
		*(data+2),
		qFromBigEndian<quint32>(data+3),
		qFromBigEndian<quint32>(data+7),
		qFromBigEndian<quint32>(data+11),
		qFromBigEndian<quint32>(data+15),
		qFromBigEndian<quint32>(data+19)
	);
}

int FillRect::payloadLength() const
{
	return 1 + 2 + 4*4 + 4;
}

int FillRect::serializePayload(uchar *data) const
{
	uchar *ptr = data;
	*(ptr++) = contextId();
	*(ptr++) = _layer;
	*(ptr++) = _blend;
	qToBigEndian(_x, ptr); ptr += 4;
	qToBigEndian(_y, ptr); ptr += 4;
	qToBigEndian(_w, ptr); ptr += 4;
	qToBigEndian(_h, ptr); ptr += 4;
	qToBigEndian(_color, ptr); ptr += 4;

	return ptr-data;
}


}
