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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <fx.h>
#include <FXScrollArea.h>
#include <FXMessageBox.h>
#include <algorithm>
#include <string>
#include <fxkeys.h>
#include "Board.h"
#include "icons.h"

class MainWindow : public FXMainWindow
{
	FXDECLARE(MainWindow)

	public:
		explicit MainWindow(FXApp* a);
		~MainWindow();
		virtual void create();

		/* Event system */
		// Messages for our class
		enum {
			UI_Tile       = FXMainWindow::ID_LAST,
			UI_New,
			UI_Timer_Tick,
		};

		/* Event handlers */
		long on_Tile_Click(FXObject *sender, FXSelector sel, void *data);
		long on_New_Click(FXObject *sender, FXSelector sel, void *data);
		long on_Tile_Right_Click(FXObject *sender, FXSelector sel, void *data);
		long on_Timer_Tick(FXObject *sender, FXSelector sel, void *data);
		long on_Key_Press(FXObject *sender, FXSelector sel, void *data);
		long on_Key_Release(FXObject *sender, FXSelector sel, void *data);
		FXApp *get_app(){ return app; };


	protected:
		// Required constructor for FXObject
		MainWindow(){}

	private:
		void create_ui();
		void new_game(int w, int h, int minecount);
		void draw_buttons();
		bool game_over;
		long unsigned int seconds;
		bool ticking;
		int game_count;
		FXHorizontalFrame *contents;                // Content frame
		FXVerticalFrame   *canvasFrame;             // Canvas frame
		FXVerticalFrame   *buttonFrame;             // Button frame
		FXScrollWindow 	*scroll_area;
		FXApp *app;
		Board *board;
		FXMatrix *matrix;
		FXLabel *time_label;
		FXTextField *width_input;
		FXTextField *height_input;
		FXTextField *mine_input;
		FXHorizontalFrame *width_input_frame;
		FXHorizontalFrame *height_input_frame;
		FXHorizontalFrame *mine_input_frame;
		std::vector<std::unique_ptr<FXButton>> tile_buttons;
		/* icons */
		FXIcon *bomb_icon;
		FXIcon *flag_icon;
		FXIcon *empty_icon;
		FXIcon *tile_1_icon;
		FXIcon *tile_2_icon;
		FXIcon *tile_3_icon;
		FXIcon *tile_4_icon;
		FXIcon *tile_5_icon;
		FXIcon *tile_6_icon;
		FXIcon *tile_7_icon;
		FXIcon *tile_8_icon;


};

#endif // MAINWINDOW_H
