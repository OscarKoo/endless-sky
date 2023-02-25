/* Font.cpp
Copyright (c) 2014-2020 by Michael Zahniser

Endless Sky is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later version.

Endless Sky is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <https://www.gnu.org/licenses/>.
*/

# include "Font.h"

# include "alignment.hpp"
# include "../Color.h"
# include "DisplayText.h"
# include "../ImageBuffer.h"
# include "../Point.h"
# include "../Preferences.h"
# include "../Screen.h"
# include "truncate.hpp"

# include <algorithm>
# include <cmath>
# include <cstdlib>
# include <cstring>
# include <sstream>
# include <string>
# include <textfrog.h>
# include <imgui.h>
# include <imgui_internal.h>
# include "myimgui.h"
# include <ostream>
extern textfrog tfg ;
using namespace std ;

namespace {
	bool showUnderlines = false ;
}

Font :: Font ( const string & imagePath ) {
	Load ( imagePath ) ;
}

void Font :: Load ( const string & imagePath ) { //empty
	height = 8 ;
	space = 3 ;
}

void Font :: Draw ( const DisplayText & text , const Point & point , const Color & color ) const {
	DrawAliased ( text , round ( point . X ( ) ) , round ( point . Y ( ) ) , color ) ;
}

void Font :: DrawAliased ( const DisplayText & text , double x , double y , const Color & color ) const {
	int width = -1 ;
	const string truncText = TruncateText ( text , width ) ;
	const auto & layout = text . GetLayout ( ) ;
	if ( width >= 0 ) {
		if ( layout . align == Alignment :: CENTER )
		x += ( layout . width - width ) / 2 ;
		else if ( layout . align == Alignment :: RIGHT )
		x += layout . width - width ;
	}
	DrawAliased ( truncText , x , y , color ) ;
}

void Font :: Draw ( const string & str , const Point & point , const Color & color ) const {
	DrawAliased ( str , round ( point . X ( ) ) , round ( point . Y ( ) ) , color ) ;
}

void Font :: DrawAliased ( const string & str , double x , double y , const Color & color ) const {
	DrawWrap ( str , x , y , color , 0 ) ;
}
int Font :: DrawWrap ( const string & str , double x , double y , const Color & color , float wrap_width ) const {
	const char * text = str . c_str ( ) ;
	const float * c = color . Get ( ) ;
	//	ImVec4 col = ImVec4 ( c [ 0 ] , c [ 1 ] , c [ 2 ] , c [ 3 ] ) ;
	if ( Screen :: Width ( ) != screenWidth || Screen :: Height ( ) != screenHeight ) {
		screenWidth = Screen :: Width ( ) ;
		screenHeight = Screen :: Height ( ) ;
	}
	x = x + screenWidth / 2 ;
	y = y - height + 3 + screenHeight / 2 ;
//		ImVec2 pos = ImVec2 ( x , y ) ;
//	 {
//			ostringstream out ;
//			out << "draw [" << str << "] @ " << x << " * " << y << " "
//			<< c [ 0 ] << " " << c [ 1 ] << " " << c [ 2 ] << " " << c [ 3 ]
//			<< endl ;
//			tfg_call ( tfg , "mylog" , 1 , out . str ( ) . c_str ( ) ) ;
//		}
	ImVec2 text_size = ImGui::CalcTextSize(text , text + str . length ( ), false, wrap_width);
	ImGui :: GetForegroundDrawList ( ) -> AddText ( NULL , 0.0f ,
		ImVec2 ( x , y ) , ImColor ( c [ 0 ]   , c [ 1 ]   , c [ 2 ]  ) ,
		text , text + str . length ( ) , wrap_width , NULL ) ;
	ImGui :: Render ( ) ;
	myimgui_render();
	ImGui :: NewFrame ( ) ;
//	myimgui_framestart();
//	ImGui :: GetForegroundDrawList ( )->_ResetForNewFrame();
	return text_size.y;
}

int Font :: Width ( const string & str , char after ) const {
	return WidthRawString ( str . c_str ( ) , after ) ;
}

int Font :: FormattedWidth ( const DisplayText & text , char after ) const {
	int width = -1 ;
	const string truncText = TruncateText ( text , width ) ;
	return width < 0 ? WidthRawString ( truncText . c_str ( ) , after ) : width ;
}

int Font :: Height ( ) const noexcept {
	return height ;
}

int Font :: Space ( ) const noexcept {
	return space ;
}

void Font :: ShowUnderlines ( bool show ) noexcept {
	showUnderlines = show || Preferences :: Has ( "Always underline shortcuts" ) ;
}

int Font :: Glyph ( char c , bool isAfterSpace ) noexcept //fixme
{
	// Curly quotes.
	if ( c == '\'' && isAfterSpace )
	return 96 ;
	if ( c == '"' && isAfterSpace )
	return 97 ;

	return max ( 0 , min ( GLYPHS - 3 , c - 32 ) ) ;
}

void Font :: LoadTexture ( ImageBuffer & image ) { //empty
}

void Font :: CalculateAdvances ( ImageBuffer & image ) //empty
{
}

void Font :: SetUpShader ( float glyphW , float glyphH ) //empty
{
}

int Font :: WidthRawString ( const char * str , char after ) const noexcept //fixme
{
	int len = strlen ( str ) ;
	ImVec2 v2 = ImGui :: CalcTextSize ( str , str + len , false , 9999 ) ;
//	printf ( "[d]len %f[%s]\n" , v2 . x , str ) ;
	return v2 . x ;
}

// Param width will be set to the width of the return value, unless the layout width is negative.
string Font :: TruncateText ( const DisplayText & text , int & width ) const {
	width = -1 ;
	const auto & layout = text . GetLayout ( ) ;
	const string & str = text . GetText ( ) ;
	if ( layout . width < 0 || ( layout . align == Alignment :: LEFT && layout . truncate == Truncate :: NONE ) )
	return str ;
	width = layout . width ;
	switch ( layout . truncate ) {
		case Truncate :: NONE :
		width = WidthRawString ( str . c_str ( ) ) ;
		return str ;
		case Truncate :: FRONT :
		return TruncateFront ( str , width ) ;
		case Truncate :: MIDDLE :
		return TruncateMiddle ( str , width ) ;
		case Truncate :: BACK :
		default :
		return TruncateBack ( str , width ) ;
	}
}

string Font :: TruncateBack ( const string & str , int & width ) const { //fixme
	return str ;
}

string Font :: TruncateFront ( const string & str , int & width ) const { //fixme
	return str ;
}

string Font :: TruncateMiddle ( const string & str , int & width ) const { //fixme
	return str ;
}
