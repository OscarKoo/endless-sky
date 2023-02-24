/* WrappedText.cpp
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

# include "WrappedText.h"

# include "DisplayText.h"
# include "Font.h"

# include <cstring>
# include <textfrog.h>
# include <imgui.h>
extern textfrog tfg ;
using namespace std ;

WrappedText :: WrappedText ( const Font & font ) {
	SetFont ( font ) ;
}

void WrappedText :: SetAlignment ( Alignment align ) {
	alignment = align ;
}

// Set the truncate mode.
void WrappedText :: SetTruncate ( Truncate trunc ) {
	truncate = trunc ;
}

// Set the wrap width. This does not include any margins.
int WrappedText :: WrapWidth ( ) const {
	return wrapWidth ;
}

void WrappedText :: SetWrapWidth ( int width ) {
	wrapWidth = width ;
}

// Set the font to use. This will also set sensible defaults for the tab
// width, line height, and paragraph break. You must specify the wrap width
// and the alignment separately.
void WrappedText :: SetFont ( const Font & font ) {
	this -> font = & font ;

	space = font . Space ( ) ;
	SetTabWidth ( 4 * space ) ;
	SetLineHeight ( font . Height ( ) * 120 / 100 ) ;
	SetParagraphBreak ( font . Height ( ) * 40 / 100 ) ;
}

// Set the width in pixels of a single '\t' character.
int WrappedText :: TabWidth ( ) const {
	return tabWidth ;
}

void WrappedText :: SetTabWidth ( int width ) {
	tabWidth = width ;
}

// Set the height in pixels of one line of text within a paragraph.
int WrappedText :: LineHeight ( ) const {
	return lineHeight ;
}

void WrappedText :: SetLineHeight ( int height ) {
	lineHeight = height ;
}

// Set the extra spacing in pixels to be added in between paragraphs.
int WrappedText :: ParagraphBreak ( ) const {
	return paragraphBreak ;
}

void WrappedText :: SetParagraphBreak ( int height ) {
	paragraphBreak = height ;
}

// Get the word positions when wrapping the given text. The coordinates
// always begin at (0, 0).
void WrappedText :: Wrap ( const string & str ) {
	SetText ( str . data ( ) , str . length ( ) ) ;

	Wrap ( ) ;
}

void WrappedText :: Wrap ( const char * str ) {
	SetText ( str , strlen ( str ) ) ;

	Wrap ( ) ;
}

// Get the height of the wrapped text.
int WrappedText :: Height ( ) const {
	return height ;
}

// Draw the text.
void WrappedText :: Draw ( const Point & topLeft , const Color & color )  {
	font -> DrawWrap ( text , topLeft . X ( ) , topLeft . Y ( ) , color , wrapWidth ) ;
}

size_t WrappedText :: Word :: Index ( ) const {
	return index ;
}

Point WrappedText :: Word :: Pos ( ) const {
	return Point ( x , y ) ;
}

void WrappedText :: SetText ( const char * it , size_t length ) {
	tfg_call ( tfg , "mylog" , 1 , it ) ;
	// Clear any previous word-wrapping data. It becomes invalid as soon as the
	// underlying text buffer changes.
	words . clear ( ) ;
	// Reallocate that buffer.
	text . assign ( it , length ) ;

	ImVec2 text_size = ImGui::CalcTextSize(it , it + length, false, wrapWidth);
	height=text_size.y;
}

void WrappedText :: Wrap ( ) //empty wrapWidth
{
}

void WrappedText :: AdjustLine ( size_t & lineBegin , int & lineWidth , bool isEnd ) {
	//	int wordCount = static_cast<int>(words.size() - lineBegin);
	//	int extraSpace = wrapWidth - lineWidth;
	//
	//	// Figure out how much space is left over. Depending on the alignment, we
	//	// will add that space to the left, to the right, to both sides, or to the
	//	// space in between the words. Exception: the last line of a "justified"
	//	// paragraph is left aligned, not justified.
	//	if(alignment == Alignment::JUSTIFIED && !isEnd && wordCount > 1)
	//	{
	//		for(int i = 0; i < wordCount; ++i)
	//			words[lineBegin + i].x += extraSpace * i / (wordCount - 1);
	//	}
	//	else if(alignment == Alignment::CENTER || alignment == Alignment::RIGHT)
	//	{
	//		int shift = (alignment == Alignment::CENTER) ? extraSpace / 2 : extraSpace;
	//		for(int i = 0; i < wordCount; ++i)
	//			words[lineBegin + i].x += shift;
	//	}
	//
	//	lineBegin = words.size();
	//	lineWidth = 0;
}

int WrappedText :: Space ( char c ) const {
	return ( c == ' ' ) ? space : ( c == '\t' ) ? tabWidth : 0 ;
}
