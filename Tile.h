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

#ifndef TILE_H
#define TILE_H

class Tile
{
	public:
		Tile(int x, int y);
		~Tile();
		void disable_tile();
		void create();
		int get_x() { return x; };
		int get_y() { return y; };
		void reveal();
		enum STATE
		{
			HIDDEN 		= 1 << 0,
			MINE		= 1 << 1,
			FLAGGED		= 1 << 2,
			REVEALED	= 1 << 3,
		};
		enum STATE get_flags() { return flags; };
		void set_flag(enum STATE flag) { this->flags = (STATE) (this->flags | flag); };
		void clear_flag(enum STATE flag) { this->flags = (STATE) (this->flags & ~flag); };
		void toggle_flag(enum STATE flag) { this->flags = (STATE) (this->flags ^ flag); };
		bool is_mine() { return this->flags & MINE; };
		bool is_flagged() { return this->flags & FLAGGED; };
		bool is_revealed() { return this->flags & REVEALED; };
		int get_neighbor_mine_count() { return this->neighbor_mine_count; };
		void set_neighbor_mine_count(int count) { this->neighbor_mine_count = count; };
		Tile *get_neighbor(int i);

		Tile *neighbors[8]; // one day make private with getters/setters
	private:
		void set_flags(enum STATE flags) { this->flags = flags; };
		int x;
		int y;
		int neighbor_mine_count;
		enum STATE flags;

};

#endif
