//--------------------------------------------------------------------------------------
//  This file is part of the Lomse library.
//  Copyright (c) 2010-2011 Lomse project
//
//  Lomse is free software; you can redistribute it and/or modify it under the
//  terms of the GNU General Public License as published by the Free Software Foundation,
//  either version 3 of the License, or (at your option) any later version.
//
//  Lomse is distributed in the hope that it will be useful, but WITHOUT ANY
//  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
//  PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License along
//  with Lomse; if not, see <http://www.gnu.org/licenses/>.
//
//  For any comment, suggestion or feature request, please contact the manager of
//  the project at cecilios@users.sourceforge.net
//
//-------------------------------------------------------------------------------------

#include "lomse_ldp_factory.h"

#include <sstream>
#include <iostream>
using namespace std;

namespace lomse
{

class LdpFunctor
{
public:
	LdpFunctor() {}
	virtual ~LdpFunctor() {}
    virtual LdpElement* operator ()() = 0;
};


template<ELdpElement type>
class LdpElementFunctor : public LdpFunctor
{
public:
	LdpElement* operator ()() {  return LdpObject<type>::new_ldp_object(); }
};


LdpFactory::LdpFactory()
{
    //Register all ldp elements

    //simple, generic elements
    m_TypeToName[k_label] = "label";
    m_TypeToName[k_number] = "number";
    m_TypeToName[k_string] = "string";

    //composite elements
    m_TypeToName[k_abbrev] = "abbrev";
    m_TypeToName[k_above] = "above";
    m_TypeToName[k_anchorLine] = "anchorLine";
    m_TypeToName[k_background_color] = "background-color";
    m_TypeToName[k_barline] = "barline";
    m_TypeToName[k_beam] = "beam";
    m_TypeToName[k_below] = "below";
    m_TypeToName[k_bezier] = "bezier";
    m_TypeToName[k_bold] = "bold";
    m_TypeToName[k_bold_italic] = "bold-italic";
    m_TypeToName[k_border] = "border";
    m_TypeToName[k_border_width] = "border-width";
    m_TypeToName[k_border_width_top] = "border-width-top";
    m_TypeToName[k_border_width_right] = "border-width-right";
    m_TypeToName[k_border_width_bottom] = "border-width-bottom";
    m_TypeToName[k_border_width_left] = "border-width-left";
    m_TypeToName[k_brace] = "brace";
    m_TypeToName[k_bracket] = "bracket";
    m_TypeToName[k_bracketType] = "bracketType";
    m_TypeToName[k_center] = "center";
    m_TypeToName[k_chord] = "chord";
    m_TypeToName[k_classid] = "classid";
    m_TypeToName[k_clef] = "clef";
    m_TypeToName[k_color] = "color";
    m_TypeToName[k_content] = "content";
    m_TypeToName[k_creationMode] = "creationMode";
    m_TypeToName[k_ctrol1_x] = "ctrol1-x";
    m_TypeToName[k_ctrol1_y] = "ctrol1-y";
    m_TypeToName[k_ctrol2_x] = "ctrol2-x";
    m_TypeToName[k_ctrol2_y] = "ctrol2-y";
    m_TypeToName[k_cursor] = "cursor";
    m_TypeToName[k_defineStyle] = "defineStyle";
    m_TypeToName[k_down] = "down";
    m_TypeToName[k_displayBracket] = "displayBracket";
    m_TypeToName[k_displayNumber] = "displayNumber";
    m_TypeToName[k_duration] = "duration";
    m_TypeToName[k_dx] = "dx";
    m_TypeToName[k_dy] = "dy";
    m_TypeToName[k_dynamic] = "dynamic";
    m_TypeToName[k_end] = "end";
    m_TypeToName[k_end_x] = "end-x";
    m_TypeToName[k_end_y] = "end-y";
    m_TypeToName[k_endPoint] = "endPoint";
    m_TypeToName[k_fbline] = "fbline";
    m_TypeToName[k_fermata] = "fermata";
    m_TypeToName[k_figuredBass] = "figuredBass";
    m_TypeToName[k_file] = "file";
    m_TypeToName[k_font] = "font";
    m_TypeToName[k_font_name] = "font-name";
    m_TypeToName[k_font_size] = "font-size";
    m_TypeToName[k_font_style] = "font-style";
    m_TypeToName[k_font_weight] = "font-weight";
    m_TypeToName[k_goBack] = "goBack";
    m_TypeToName[k_goFwd] = "goFwd";
    m_TypeToName[k_graphic] = "graphic";
    m_TypeToName[k_group] = "group";
    m_TypeToName[k_hasWidth] = "hasWidth";
    m_TypeToName[k_heading] = "heading";
    m_TypeToName[k_height] = "height";
    m_TypeToName[k_image] = "image";
    m_TypeToName[k_infoMIDI] = "infoMIDI";
    m_TypeToName[k_instrument] = "instrument";
    m_TypeToName[k_italic] = "italic";
    m_TypeToName[k_itemizedlist] = "itemizedlist";
    m_TypeToName[k_joinBarlines] = "joinBarlines";
    m_TypeToName[k_key_signature] = "key";
    m_TypeToName[k_landscape] = "landscape";
    m_TypeToName[k_language] = "language";
    m_TypeToName[k_left] = "left";
    m_TypeToName[k_lenmusdoc] = "lenmusdoc";
    m_TypeToName[k_link] = "link";
    m_TypeToName[k_line] = "line";
    m_TypeToName[k_lineCapEnd] = "lineCapEnd";
    m_TypeToName[k_lineCapStart] = "lineCapStart";
    m_TypeToName[k_lineStyle] = "lineStyle";
    m_TypeToName[k_lineThickness] = "lineThickness";
    m_TypeToName[k_line_height] = "line-height";
    m_TypeToName[k_listitem] = "listitem";
    m_TypeToName[k_margin] = "margin";
    m_TypeToName[k_margin_top] = "margin-top";
    m_TypeToName[k_margin_right] = "margin-right";
    m_TypeToName[k_margin_bottom] = "margin-bottom";
    m_TypeToName[k_margin_left] = "margin-left";
    m_TypeToName[k_meta] = "meta";
    m_TypeToName[k_metronome] = "metronome";
    m_TypeToName[k_musicData] = "musicData";
    m_TypeToName[k_na] = "na";  //note in chord
    m_TypeToName[k_name] = "name";
    m_TypeToName[k_newSystem] = "newSystem";
    m_TypeToName[k_no] = "no";
    m_TypeToName[k_normal] = "normal";
    m_TypeToName[k_note] = "n";   //note
    m_TypeToName[k_opt] = "opt";
    m_TypeToName[k_orderedlist] = "orderedlist";
    m_TypeToName[k_padding] = "padding";
    m_TypeToName[k_padding_top] = "padding-top";
    m_TypeToName[k_padding_right] = "padding-right";
    m_TypeToName[k_padding_bottom] = "padding-bottom";
    m_TypeToName[k_padding_left] = "padding-left";
    m_TypeToName[k_pageLayout] = "pageLayout";
    m_TypeToName[k_pageMargins] = "pageMargins";
    m_TypeToName[k_pageSize] = "pageSize";
    m_TypeToName[k_para] = "para";
    m_TypeToName[k_parameter] = "param";
    m_TypeToName[k_parenthesis] = "parenthesis";
    m_TypeToName[k_pitch] = "pitch";
    m_TypeToName[k_portrait] = "portrait";
    m_TypeToName[k_rest] = "r";   //rest
    m_TypeToName[k_right] = "right";
    m_TypeToName[k_score] = "score";
    m_TypeToName[k_score_player] = "scorePlayer";
    m_TypeToName[k_settings] = "settings";
    m_TypeToName[k_slur] = "slur";
    m_TypeToName[k_size] = "size";
    m_TypeToName[k_spacer] = "spacer";
    m_TypeToName[k_split] = "split";
    m_TypeToName[k_staff] = "staff";
    m_TypeToName[k_staffDistance] = "staffDistance";
    m_TypeToName[k_staffLines] = "staffLines";
    m_TypeToName[k_staffNum] = "staffNum";
    m_TypeToName[k_staffSpacing] = "staffSpacing";
    m_TypeToName[k_staffType] = "staffType";
    m_TypeToName[k_start_x] = "start-x";
    m_TypeToName[k_start_y] = "start-y";
    m_TypeToName[k_startPoint] = "startPoint";
    m_TypeToName[k_styles] = "styles";
    m_TypeToName[k_start] = "start";
    m_TypeToName[k_staves] = "staves";
    m_TypeToName[k_stem] = "stem";
    m_TypeToName[k_style] = "style";
    m_TypeToName[k_styles] = "styles";
    m_TypeToName[k_symbol] = "symbol";
    m_TypeToName[k_symbolSize] = "symbolSize";
    m_TypeToName[k_style] = "style";
    m_TypeToName[k_styles] = "styles";
    m_TypeToName[k_systemLayout] = "systemLayout";
    m_TypeToName[k_systemMargins] = "systemMargins";
    m_TypeToName[k_tuplet] = "t";
    m_TypeToName[k_text] = "text";
    m_TypeToName[k_textbox] = "textbox";
    m_TypeToName[k_text_align] = "text-align";
    m_TypeToName[k_text_decoration] = "text-decoration";
    m_TypeToName[k_tie] = "tie";
    m_TypeToName[k_time_signature] = "time";
    m_TypeToName[k_title] = "title";
    m_TypeToName[k_txt] = "txt";
    m_TypeToName[k_undefined] = "undefined";
    m_TypeToName[k_undoData] = "undoData";
    m_TypeToName[k_up] = "up";
    m_TypeToName[k_url] = "url";
    m_TypeToName[k_vers] = "vers";
    m_TypeToName[k_vertical_align] = "vertical-align";
    m_TypeToName[k_visible] = "visible";
    m_TypeToName[k_voice] = "voice";
    m_TypeToName[k_width] = "width";
    m_TypeToName[k_yes] = "yes";


    //Register all types
    m_NameToFunctor["label"] = LOMSE_NEW LdpElementFunctor<k_label>;
    m_NameToFunctor["number"] = LOMSE_NEW LdpElementFunctor<k_number>;
    m_NameToFunctor["string"] = LOMSE_NEW LdpElementFunctor<k_string>;

    m_NameToFunctor["abbrev"] = LOMSE_NEW LdpElementFunctor<k_abbrev>;
    m_NameToFunctor["above"] = LOMSE_NEW LdpElementFunctor<k_above>;
    m_NameToFunctor["anchorLine"] = LOMSE_NEW LdpElementFunctor<k_anchorLine>;
    m_NameToFunctor["background-color"] = LOMSE_NEW LdpElementFunctor<k_background_color>;
    m_NameToFunctor["barline"] = LOMSE_NEW LdpElementFunctor<k_barline>;
    m_NameToFunctor["beam"] = LOMSE_NEW LdpElementFunctor<k_beam>;
    m_NameToFunctor["below"] = LOMSE_NEW LdpElementFunctor<k_below>;
    m_NameToFunctor["bezier"] = LOMSE_NEW LdpElementFunctor<k_bezier>;
    m_NameToFunctor["bold"] = LOMSE_NEW LdpElementFunctor<k_bold>;
    m_NameToFunctor["bold_italic"] = LOMSE_NEW LdpElementFunctor<k_bold_italic>;
    m_NameToFunctor["border"] = LOMSE_NEW LdpElementFunctor<k_border>;
    m_NameToFunctor["border-width"] = LOMSE_NEW LdpElementFunctor<k_border_width>;
    m_NameToFunctor["border-width-top"] = LOMSE_NEW LdpElementFunctor<k_border_width_top>;
    m_NameToFunctor["border-width-right"] = LOMSE_NEW LdpElementFunctor<k_border_width_right>;
    m_NameToFunctor["border-width-bottom"] = LOMSE_NEW LdpElementFunctor<k_border_width_bottom>;
    m_NameToFunctor["border-width-left"] = LOMSE_NEW LdpElementFunctor<k_border_width_left>;
    m_NameToFunctor["brace"] = LOMSE_NEW LdpElementFunctor<k_brace>;
    m_NameToFunctor["bracket"] = LOMSE_NEW LdpElementFunctor<k_bracket>;
    m_NameToFunctor["bracketType"] = LOMSE_NEW LdpElementFunctor<k_bracketType>;
    m_NameToFunctor["center"] = LOMSE_NEW LdpElementFunctor<k_center>;
    m_NameToFunctor["chord"] = LOMSE_NEW LdpElementFunctor<k_chord>;
    m_NameToFunctor["classid"] = LOMSE_NEW LdpElementFunctor<k_classid>;
    m_NameToFunctor["clef"] = LOMSE_NEW LdpElementFunctor<k_clef>;
    m_NameToFunctor["color"] = LOMSE_NEW LdpElementFunctor<k_color>;
    m_NameToFunctor["content"] = LOMSE_NEW LdpElementFunctor<k_content>;
    m_NameToFunctor["creationMode"] = LOMSE_NEW LdpElementFunctor<k_creationMode>;
    m_NameToFunctor["ctrol1-x"] = LOMSE_NEW LdpElementFunctor<k_ctrol1_x>;
    m_NameToFunctor["ctrol1-y"] = LOMSE_NEW LdpElementFunctor<k_ctrol1_y>;
    m_NameToFunctor["ctrol2-x"] = LOMSE_NEW LdpElementFunctor<k_ctrol2_x>;
    m_NameToFunctor["ctrol2-y"] = LOMSE_NEW LdpElementFunctor<k_ctrol2_y>;
    m_NameToFunctor["cursor"] = LOMSE_NEW LdpElementFunctor<k_cursor>;
    m_NameToFunctor["defineStyle"] = LOMSE_NEW LdpElementFunctor<k_defineStyle>;
    m_NameToFunctor["down"] = LOMSE_NEW LdpElementFunctor<k_down>;
    m_NameToFunctor["duration"] = LOMSE_NEW LdpElementFunctor<k_duration>;
    m_NameToFunctor["displayBracket"] = LOMSE_NEW LdpElementFunctor<k_displayBracket>;
    m_NameToFunctor["displayNumber"] = LOMSE_NEW LdpElementFunctor<k_displayNumber>;
    m_NameToFunctor["dx"] = LOMSE_NEW LdpElementFunctor<k_dx>;
    m_NameToFunctor["dy"] = LOMSE_NEW LdpElementFunctor<k_dy>;
    m_NameToFunctor["dynamic"] = LOMSE_NEW LdpElementFunctor<k_dynamic>;
    m_NameToFunctor["end"] = LOMSE_NEW LdpElementFunctor<k_end>;
    m_NameToFunctor["end-x"] = LOMSE_NEW LdpElementFunctor<k_end_x>;
    m_NameToFunctor["end-y"] = LOMSE_NEW LdpElementFunctor<k_end_y>;
    m_NameToFunctor["endPoint"] = LOMSE_NEW LdpElementFunctor<k_endPoint>;
    m_NameToFunctor["fbline"] = LOMSE_NEW LdpElementFunctor<k_fbline>;
    m_NameToFunctor["fermata"] = LOMSE_NEW LdpElementFunctor<k_fermata>;
    m_NameToFunctor["figuredBass"] = LOMSE_NEW LdpElementFunctor<k_figuredBass>;
    m_NameToFunctor["file"] = LOMSE_NEW LdpElementFunctor<k_file>;
    m_NameToFunctor["font"] = LOMSE_NEW LdpElementFunctor<k_font>;
    m_NameToFunctor["font-name"] = LOMSE_NEW LdpElementFunctor<k_font_name>;
    m_NameToFunctor["font-size"] = LOMSE_NEW LdpElementFunctor<k_font_size>;
    m_NameToFunctor["font-style"] = LOMSE_NEW LdpElementFunctor<k_font_style>;
    m_NameToFunctor["font-weight"] = LOMSE_NEW LdpElementFunctor<k_font_weight>;
    m_NameToFunctor["goBack"] = LOMSE_NEW LdpElementFunctor<k_goBack>;
    m_NameToFunctor["goFwd"] = LOMSE_NEW LdpElementFunctor<k_goFwd>;
    m_NameToFunctor["graphic"] = LOMSE_NEW LdpElementFunctor<k_graphic>;
    m_NameToFunctor["group"] = LOMSE_NEW LdpElementFunctor<k_group>;
    m_NameToFunctor["hasWidth"] = LOMSE_NEW LdpElementFunctor<k_hasWidth>;
    m_NameToFunctor["heading"] = LOMSE_NEW LdpElementFunctor<k_heading>;
    m_NameToFunctor["height"] = LOMSE_NEW LdpElementFunctor<k_height>;
    m_NameToFunctor["image"] = LOMSE_NEW LdpElementFunctor<k_image>;
    m_NameToFunctor["infoMIDI"] = LOMSE_NEW LdpElementFunctor<k_infoMIDI>;
    m_NameToFunctor["instrument"] = LOMSE_NEW LdpElementFunctor<k_instrument>;
    m_NameToFunctor["italic"] = LOMSE_NEW LdpElementFunctor<k_italic>;
    m_NameToFunctor["itemizedlist"] = LOMSE_NEW LdpElementFunctor<k_itemizedlist>;
    m_NameToFunctor["joinBarlines"] = LOMSE_NEW LdpElementFunctor<k_joinBarlines>;
    m_NameToFunctor["key"] = LOMSE_NEW LdpElementFunctor<k_key_signature>;
    m_NameToFunctor["landscape"] = LOMSE_NEW LdpElementFunctor<k_landscape>;
    m_NameToFunctor["language"] = LOMSE_NEW LdpElementFunctor<k_language>;
    m_NameToFunctor["left"] = LOMSE_NEW LdpElementFunctor<k_left>;
    m_NameToFunctor["lenmusdoc"] = LOMSE_NEW LdpElementFunctor<k_lenmusdoc>;
    m_NameToFunctor["link"] = LOMSE_NEW LdpElementFunctor<k_link>;
    m_NameToFunctor["line"] = LOMSE_NEW LdpElementFunctor<k_line>;
    m_NameToFunctor["lineCapEnd"] = LOMSE_NEW LdpElementFunctor<k_lineCapEnd>;
    m_NameToFunctor["lineCapStart"] = LOMSE_NEW LdpElementFunctor<k_lineCapStart>;
    m_NameToFunctor["lineStyle"] = LOMSE_NEW LdpElementFunctor<k_lineStyle>;
    m_NameToFunctor["lineThickness"] = LOMSE_NEW LdpElementFunctor<k_lineThickness>;
    m_NameToFunctor["line-height"] = LOMSE_NEW LdpElementFunctor<k_line_height>;
    m_NameToFunctor["listitem"] = LOMSE_NEW LdpElementFunctor<k_listitem>;
    m_NameToFunctor["margin"] = LOMSE_NEW LdpElementFunctor<k_margin>;
    m_NameToFunctor["margin-top"] = LOMSE_NEW LdpElementFunctor<k_margin_top>;
    m_NameToFunctor["margin-right"] = LOMSE_NEW LdpElementFunctor<k_margin_right>;
    m_NameToFunctor["margin-bottom"] = LOMSE_NEW LdpElementFunctor<k_margin_bottom>;
    m_NameToFunctor["margin-left"] = LOMSE_NEW LdpElementFunctor<k_margin_left>;
    m_NameToFunctor["meta"] = LOMSE_NEW LdpElementFunctor<k_meta>;
    m_NameToFunctor["metronome"] = LOMSE_NEW LdpElementFunctor<k_metronome>;
    m_NameToFunctor["musicData"] = LOMSE_NEW LdpElementFunctor<k_musicData>;
    m_NameToFunctor["n"] = LOMSE_NEW LdpElementFunctor<k_note>;   //note
    m_NameToFunctor["na"] = LOMSE_NEW LdpElementFunctor<k_na>;    //note in chord
    m_NameToFunctor["name"] = LOMSE_NEW LdpElementFunctor<k_name>;
    m_NameToFunctor["newSystem"] = LOMSE_NEW LdpElementFunctor<k_newSystem>;
    m_NameToFunctor["no"] = LOMSE_NEW LdpElementFunctor<k_no>;
    m_NameToFunctor["normal"] = LOMSE_NEW LdpElementFunctor<k_normal>;
    m_NameToFunctor["opt"] = LOMSE_NEW LdpElementFunctor<k_opt>;
    m_NameToFunctor["orderedlist"] = LOMSE_NEW LdpElementFunctor<k_orderedlist>;
    m_NameToFunctor["padding"] = LOMSE_NEW LdpElementFunctor<k_padding>;
    m_NameToFunctor["padding-top"] = LOMSE_NEW LdpElementFunctor<k_padding_top>;
    m_NameToFunctor["padding-right"] = LOMSE_NEW LdpElementFunctor<k_padding_right>;
    m_NameToFunctor["padding-bottom"] = LOMSE_NEW LdpElementFunctor<k_padding_bottom>;
    m_NameToFunctor["padding-left"] = LOMSE_NEW LdpElementFunctor<k_padding_left>;
    m_NameToFunctor["pageLayout"] = LOMSE_NEW LdpElementFunctor<k_pageLayout>;
    m_NameToFunctor["pageMargins"] = LOMSE_NEW LdpElementFunctor<k_pageMargins>;
    m_NameToFunctor["pageSize"] = LOMSE_NEW LdpElementFunctor<k_pageSize>;
    m_NameToFunctor["para"] = LOMSE_NEW LdpElementFunctor<k_para>;
    m_NameToFunctor["param"] = LOMSE_NEW LdpElementFunctor<k_parameter>;
    m_NameToFunctor["parenthesis"] = LOMSE_NEW LdpElementFunctor<k_parenthesis>;
    m_NameToFunctor["pitch"] = LOMSE_NEW LdpElementFunctor<k_pitch>;
    m_NameToFunctor["portrait"] = LOMSE_NEW LdpElementFunctor<k_portrait>;
    m_NameToFunctor["r"] = LOMSE_NEW LdpElementFunctor<k_rest>;   //rest
    m_NameToFunctor["right"] = LOMSE_NEW LdpElementFunctor<k_right>;
    m_NameToFunctor["score"] = LOMSE_NEW LdpElementFunctor<k_score>;
    m_NameToFunctor["scorePlayer"] = LOMSE_NEW LdpElementFunctor<k_score_player>;
    m_NameToFunctor["settings"] = LOMSE_NEW LdpElementFunctor<k_settings>;
    m_NameToFunctor["size"] = LOMSE_NEW LdpElementFunctor<k_size>;
    m_NameToFunctor["slur"] = LOMSE_NEW LdpElementFunctor<k_slur>;
    m_NameToFunctor["spacer"] = LOMSE_NEW LdpElementFunctor<k_spacer>;
    m_NameToFunctor["split"] = LOMSE_NEW LdpElementFunctor<k_split>;
    m_NameToFunctor["staff"] = LOMSE_NEW LdpElementFunctor<k_staff>;
    m_NameToFunctor["staffDistance"] = LOMSE_NEW LdpElementFunctor<k_staffDistance>;
    m_NameToFunctor["staffLines"] = LOMSE_NEW LdpElementFunctor<k_staffLines>;
    m_NameToFunctor["staffNum"] = LOMSE_NEW LdpElementFunctor<k_staffNum>;
    m_NameToFunctor["staffSpacing"] = LOMSE_NEW LdpElementFunctor<k_staffSpacing>;
    m_NameToFunctor["staffType"] = LOMSE_NEW LdpElementFunctor<k_staffType>;
    m_NameToFunctor["start"] = LOMSE_NEW LdpElementFunctor<k_start>;
    m_NameToFunctor["start-x"] = LOMSE_NEW LdpElementFunctor<k_start_x>;
    m_NameToFunctor["start-y"] = LOMSE_NEW LdpElementFunctor<k_start_y>;
    m_NameToFunctor["startPoint"] = LOMSE_NEW LdpElementFunctor<k_startPoint>;
    m_NameToFunctor["staves"] = LOMSE_NEW LdpElementFunctor<k_staves>;
    m_NameToFunctor["stem"] = LOMSE_NEW LdpElementFunctor<k_stem>;
    m_NameToFunctor["style"] = LOMSE_NEW LdpElementFunctor<k_style>;
    m_NameToFunctor["styles"] = LOMSE_NEW LdpElementFunctor<k_styles>;
    m_NameToFunctor["symbol"] = LOMSE_NEW LdpElementFunctor<k_symbol>;
    m_NameToFunctor["symbolSize"] = LOMSE_NEW LdpElementFunctor<k_symbolSize>;
    m_NameToFunctor["systemLayout"] = LOMSE_NEW LdpElementFunctor<k_systemLayout>;
    m_NameToFunctor["systemMargins"] = LOMSE_NEW LdpElementFunctor<k_systemMargins>;
    m_NameToFunctor["t"] = LOMSE_NEW LdpElementFunctor<k_tuplet>;
    m_NameToFunctor["text"] = LOMSE_NEW LdpElementFunctor<k_text>;
    m_NameToFunctor["textbox"] = LOMSE_NEW LdpElementFunctor<k_textbox>;
    m_NameToFunctor["text-align"] = LOMSE_NEW LdpElementFunctor<k_text_align>;
    m_NameToFunctor["text-decoration"] = LOMSE_NEW LdpElementFunctor<k_text_decoration>;
    m_NameToFunctor["tie"] = LOMSE_NEW LdpElementFunctor<k_tie>;
    m_NameToFunctor["time"] = LOMSE_NEW LdpElementFunctor<k_time_signature>;
    m_NameToFunctor["title"] = LOMSE_NEW LdpElementFunctor<k_title>;
    m_NameToFunctor["txt"] = LOMSE_NEW LdpElementFunctor<k_txt>;
    m_NameToFunctor["undefined"] = LOMSE_NEW LdpElementFunctor<k_undefined>;
    m_NameToFunctor["undoData"] = LOMSE_NEW LdpElementFunctor<k_undoData>;
    m_NameToFunctor["up"] = LOMSE_NEW LdpElementFunctor<k_up>;
    m_NameToFunctor["url"] = LOMSE_NEW LdpElementFunctor<k_url>;
    m_NameToFunctor["vers"] = LOMSE_NEW LdpElementFunctor<k_vers>;
    m_NameToFunctor["vertical-align"] = LOMSE_NEW LdpElementFunctor<k_vertical_align>;
    m_NameToFunctor["visible"] = LOMSE_NEW LdpElementFunctor<k_visible>;
    m_NameToFunctor["voice"] = LOMSE_NEW LdpElementFunctor<k_voice>;
    m_NameToFunctor["width"] = LOMSE_NEW LdpElementFunctor<k_width>;
    m_NameToFunctor["yes"] = LOMSE_NEW LdpElementFunctor<k_yes>;

}

LdpFactory::~LdpFactory()
{
	map<std::string, LdpFunctor*>::const_iterator it;
    for (it = m_NameToFunctor.begin(); it != m_NameToFunctor.end(); ++it)
        delete it->second;

    m_NameToFunctor.clear();
    m_TypeToName.clear();
}

LdpElement* LdpFactory::create(const std::string& name, int numLine) const
{
	map<std::string, LdpFunctor*>::const_iterator it
        = m_NameToFunctor.find(name);
	if (it != m_NameToFunctor.end())
    {
		LdpFunctor* f = it->second;
		LdpElement* element = (*f)();
		element->set_name(name);
        element->set_num_line(numLine);
		return element;
	}
    else
    {
        LdpElement* element = create(k_undefined, numLine);
		//element->set_name(name);
        return element;
    }
}

LdpElement* LdpFactory::create(ELdpElement type, int numLine) const
{
	map<ELdpElement, std::string>::const_iterator it = m_TypeToName.find( type );
	if (it != m_TypeToName.end())
		return create(it->second, numLine);

    std::stringstream err;
    err << "LdpFactory::create called with unknown type \""
        << type << "\"" << endl;
    throw std::runtime_error( err.str() );
	return 0;
}

const std::string& LdpFactory::get_name(ELdpElement type) const
{
	map<ELdpElement, std::string>::const_iterator it = m_TypeToName.find( type );
	if (it != m_TypeToName.end())
		return it->second;
    else
        throw std::runtime_error( "[LdpFactory::get_name]. Invalid type" );
}

}   //namespace lomse
