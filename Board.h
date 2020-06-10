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

#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <memory>
#include <cstdio>
#include "Tile.h"

class Board
{
	public:
		Board(int width, int height);
		~Board();
		int get_tile_count(){ return tilecount; };
		Tile *get_tile_at(int x, int y);
		bool reveal_tile_at(int x, int y);
		void new_game(int x, int y);
	private:
		std::vector<std::shared_ptr<Tile>> tiles;
		int tilecount;
		int width;
		int height;
};
#endif
