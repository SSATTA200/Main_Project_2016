/*
=================
- cTreePicker.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cTilePicker.h"

/*
=================================================================
 Defualt Constructor
=================================================================
*/
cTilePicker::cTilePicker()
{
	this->initialiseTileList();
	this->theTilePicked = -1;
}


void cTilePicker::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, cTextureMgr* theTxtMgr, vector<LPCSTR> theTxt)
{
	SDL_Rect tilePosXY;
	tilePosXY = { tileListStartXY.x, tileListStartXY.y, 0, 0 };
	// determine number of rows and columns for array
	int numRows = sizeof(tilePickingList) / sizeof(tilePickingList[0]);
	int numCols = sizeof(tilePickingList[0]) / sizeof(tilePickingList[0][0]);
	int txtToUse = 0;
	for (int row = 0; row < numRows; row++)
	{
		for (int column = 0; column < numCols; column++)
		{
			switch (tilePickingList[row][column])
			{
			case 1:
				txtToUse = 0;
				break;
			case 2:
				txtToUse = 1;
				break;
			case 3:
				txtToUse = 2;
				break;
			case 4:
				txtToUse = 3;
				break;
			case 5:
				txtToUse = 4;
				break;
			case 6:
				txtToUse = 5;
				break;
			}
			this->aTile.setTexture(theTxtMgr->getTexture(theTxt[txtToUse]));
			this->aTile.setSpriteDimensions(theTxtMgr->getTexture(theTxt[txtToUse])->getTWidth(), theTxtMgr->getTexture(theTxt[txtToUse])->getTHeight());
			tilePosXY.w = aTile.getSpritePos().w;
			tilePosXY.h = aTile.getSpritePos().h;
			// Render tile
			aTile.render(theRenderer, &aTile.getSpriteDimensions(), &tilePosXY, aTile.getSpriteRotAngle(), &aTile.getSpriteCentre(), aTile.getSpriteScale());
			tilePosXY.x += aTile.getSpritePos().w;
		}
		tilePosXY.x = tileListStartXY.x;
		tilePosXY.y += aTile.getSpritePos().h;
	}
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cTilePicker::update(SDL_Point theAreaClicked)
{
	SDL_Point areaClicked = theAreaClicked;
	if (areaClicked.x > this->tileListStartXY.x && areaClicked.x < 932 && areaClicked.y > this->tileListStartXY.y && areaClicked.y < 228)
		{
			this->tileClickedRC.x = (int)(areaClicked.x - this->tileListStartXY.x) / this->aTile.getSpriteDimensions().w;
			this->tileClickedRC.y = (int)(areaClicked.y - this->tileListStartXY.y) / this->aTile.getSpriteDimensions().h;
			this->theTilePicked = this->tilePickingList[tileClickedRC.y][tileClickedRC.x];
		}
}

/*
=================================================================
- Set the initial values for the map
=================================================================
*/
void cTilePicker::initialiseTileList()
{
	int tile = 1;
	for (int row = 0; row < 2; row++)
	{
		for (int column = 0; column < 3; column++)
		{
			this->tilePickingList[row][column] = tile;
			tile++;
		}
	}
	 
}

/*
=================================================================
- set start position for tile map
=================================================================
*/
void cTilePicker::setTileListStartXY(SDL_Point startPosXY)
{
	this->tileListStartXY = startPosXY;
}
/*
=================================================================
- get start pposition for tile map
=================================================================
*/
SDL_Point cTilePicker::getTileListStartXY()
{
	return this->tileListStartXY;
}
/*
=================================================================
- set value of tree to be used
=================================================================
*/
void cTilePicker::setTilePicked(int aTilePicked)
{
	this->theTilePicked = aTilePicked;
}
/*
=================================================================
- get value of tree to be used
=================================================================
*/
int cTilePicker::getTilePicked()
{
	return this->theTilePicked;
}