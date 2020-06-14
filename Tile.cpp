/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Tile.h"

Tile::Tile(int x, int y)
{
	this->x = x;
	this->y = y;
	this->neighbor_mine_count = 0;
	//
	this->flags = HIDDEN; /* make sure we init the flags */

}

Tile::~Tile()
{
}

void
Tile::disable_tile()
{
}

void
Tile::reveal()
{
	this->set_flag(REVEALED);
}

Tile *
Tile::get_neighbor(int i)
{
	if (i < 0 || i > 8)
		return nullptr;
	return neighbors[i];
}

