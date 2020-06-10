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

#include "MainWindow.h"
#include <cstdlib> // rand
#include <memory>
#include <stdio.h>

FXDEFMAP(MainWindow) MainWindow_Map[]=
{
	//________Message_Type____________ID____________Message_Handler_______
	FXMAPFUNC(SEL_COMMAND, MainWindow::UI_Tile, MainWindow::on_Tile_Click),
	FXMAPFUNC(SEL_COMMAND, MainWindow::UI_New, MainWindow::on_New_Click),
};
FXIMPLEMENT(MainWindow, FXMainWindow, MainWindow_Map, ARRAYNUMBER(MainWindow_Map))

MainWindow::MainWindow(FXApp *a)
	: FXMainWindow(a, "MyProgram 0.1", nullptr, nullptr, DECOR_ALL, 0,0,200,150)
{
	board = nullptr;
	matrix = nullptr;
	app = a;
	create_ui();
	int width = 9;
	int height = 9;
	new_game(width, height, 10);
}

MainWindow::~MainWindow()
{
	delete board;
}

void
MainWindow::create()
{
	FXMainWindow::create();
	show(PLACEMENT_SCREEN);
}

void
MainWindow::create_ui()
{
	contents=new FXHorizontalFrame(this, LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

	// LEFT pane to contain the canvas
	canvasFrame=new FXVerticalFrame(contents, FRAME_SUNKEN|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT, 0, 0, 0, 0, 10, 10, 10, 10);

	// Label above the canvas
	new FXLabel(canvasFrame,"foxminesweeper", NULL, JUSTIFY_CENTER_X|LAYOUT_FILL_X);
	// Horizontal divider line
	new FXHorizontalSeparator(canvasFrame, SEPARATOR_GROOVE|LAYOUT_FILL_X);

	scroll_area = new FXScrollWindow(canvasFrame, FX::SCROLLERS_NORMAL|LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_SUNKEN);

	// RIGHT pane for the buttons
	buttonFrame=new FXVerticalFrame(contents, FRAME_SUNKEN|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT, 0, 0, 0, 0, 10, 10, 10, 10);

	// Label above the buttons
	new FXLabel(buttonFrame, "New Game", NULL, JUSTIFY_CENTER_X|LAYOUT_FILL_X);

	// Horizontal divider line
	new FXHorizontalSeparator(buttonFrame, SEPARATOR_RIDGE|LAYOUT_FILL_X);
	FXText *gametxt = new FXText(buttonFrame);
	gametxt->setText("test");

	// Exit button
	new FXButton(buttonFrame, "&Exit", nullptr, app, FXApp::ID_QUIT, BUTTON_NORMAL|LAYOUT_FILL_X);
	new FXButton(buttonFrame, "&New Game", nullptr, this, MainWindow::UI_New, BUTTON_NORMAL|LAYOUT_FILL_X);
	/* create icons */
	bomb_icon = new FXGIFIcon(app, tile_1, IMAGE_KEEP);
	empty_icon = new FXGIFIcon(app, empty, IMAGE_KEEP);
	tile_1_icon = new FXGIFIcon(app, tile_1, IMAGE_KEEP);
	tile_2_icon = new FXGIFIcon(app, tile_2, IMAGE_KEEP);
	tile_3_icon = new FXGIFIcon(app, tile_3, IMAGE_KEEP);
	tile_4_icon = new FXGIFIcon(app, tile_4, IMAGE_KEEP);
	tile_5_icon = new FXGIFIcon(app, tile_5, IMAGE_KEEP);
	tile_6_icon = new FXGIFIcon(app, tile_6, IMAGE_KEEP);
	tile_7_icon = new FXGIFIcon(app, tile_7, IMAGE_KEEP);
	tile_8_icon = new FXGIFIcon(app, tile_8, IMAGE_KEEP);
	bomb_icon->create();
	empty_icon->create();
	tile_1_icon->create();
	tile_2_icon->create();
	tile_3_icon->create();
	tile_4_icon->create();
	tile_5_icon->create();
	tile_6_icon->create();
	tile_7_icon->create();
	tile_8_icon->create();
}

void
MainWindow::new_game(int width, int height, int minecount)
{
	if (board)
		delete board;
	puts("starting new game..");
	int tilecount = width*height;
	tile_buttons.clear();
	board = new Board(width, height);
	matrix = new FXMatrix(scroll_area, width, MATRIX_BY_COLUMNS|LAYOUT_CENTER_Y|LAYOUT_CENTER_X);
	for (int i = 0; i < tilecount; i++)
	{
		std::shared_ptr<FXButton> b(new FXButton(matrix, "ok", nullptr, this, UI_Tile));
		tile_buttons.push_back(b);
		b->setIcon(tile_1_icon);
	}
	printf("rows: %d columns: %d\n", matrix->getNumRows(), matrix->getNumColumns());
	draw_buttons();
}

void
MainWindow::draw_buttons()
{

}

long
MainWindow::on_Tile_Click(FXObject *sender, FXSelector sel, void *data)
{
	int x = 0, y = 0;
	FXButton *button = dynamic_cast<FXButton*>(sender);
	if (!button)
		return 0;
	
	x = matrix->colOfChild(button);
	y = matrix->rowOfChild(button);
	printf("button pressed: x=%d, y=%d\n", x, y);
	board->reveal_tile_at(x, y);
	draw_buttons();
	return 1;
}

long
MainWindow::on_New_Click(FXObject *sender, FXSelector sel, void *data)
{
	if (board)
	{
		new_game(5, 5, 20);
	}
	return 1;
}
