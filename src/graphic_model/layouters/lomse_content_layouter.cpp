//---------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------

#include "lomse_content_layouter.h"

#include "lomse_gm_basic.h"
#include "lomse_internal_model.h"
#include "lomse_document_layouter.h"
#include "lomse_sizers.h"
#include "lomse_calligrapher.h"
#include "lomse_shape_text.h"
#include "lomse_box_content_layouter.h"
#include "lomse_score_player_ctrl.h"


namespace lomse
{

//=======================================================================================
// ContentLayouter implementation
//=======================================================================================
ContentLayouter::ContentLayouter(ImoContentObj* pItem, Layouter* pParent,
                                 GraphicModel* pGModel, LibraryScope& libraryScope,
                                 ImoStyles* pStyles)
    : Layouter(pItem, pParent, pGModel, libraryScope, pStyles)
    , m_pContent( dynamic_cast<ImoContent*>(pItem) )
{
}

//---------------------------------------------------------------------------------------
void ContentLayouter::layout_in_box()
{
    set_cursor_and_available_space(m_pItemMainBox);

    TreeNode<ImoObj>::children_iterator it;
    for (it = m_pContent->begin(); it != m_pContent->end(); ++it)
    {
        layout_item( dynamic_cast<ImoContentObj*>( *it ), m_pItemMainBox );
    }
    set_layout_is_finished(true);
}

//---------------------------------------------------------------------------------------
void ContentLayouter::create_main_box(GmoBox* pParentBox, UPoint pos, LUnits width,
                                      LUnits height)
{
    m_pItemMainBox = LOMSE_NEW GmoBoxDocPageContent(m_pContent);
    pParentBox->add_child_box(m_pItemMainBox);

    m_pItemMainBox->set_origin(pos);
    m_pItemMainBox->set_width(width);
    m_pItemMainBox->set_height(height);
}


//=======================================================================================
// MultiColumnLayouter implementation
//=======================================================================================
MultiColumnLayouter::MultiColumnLayouter(ImoContentObj* pItem, Layouter* pParent,
                                 GraphicModel* pGModel, LibraryScope& libraryScope,
                                 ImoStyles* pStyles)
    : Layouter(pItem, pParent, pGModel, libraryScope, pStyles)
    , m_pMultiColumn( dynamic_cast<ImoMultiColumn*>(pItem) )
{
}

//---------------------------------------------------------------------------------------
MultiColumnLayouter::~MultiColumnLayouter()
{
    vector<Layouter*>::iterator it;
    for (it = m_colLayouters.begin(); it != m_colLayouters.end(); ++it)
        delete *it;
    m_colLayouters.clear();
}

//---------------------------------------------------------------------------------------
void MultiColumnLayouter::layout_in_box()
{
    set_cursor_and_available_space(m_pItemMainBox);

    //get total witdh
    LUnits totalWidth = m_pItemMainBox->get_content_width();
    UPoint curPos(m_pItemMainBox->get_content_left(), m_pItemMainBox->get_content_top());

    //create column layouters and assign position and width to each column
    TreeNode<ImoObj>::children_iterator it;
    int iCol;
    for (iCol=0, it = m_pMultiColumn->begin(); it != m_pMultiColumn->end(); ++it, ++iCol)
    {
        //create column layouter and prepare it to layout the column
        ImoContent* pContent = dynamic_cast<ImoContent*>( *it );
        m_colLayouters.push_back( create_layouter(pContent) );
        Layouter* pCurLayouter = m_colLayouters.back();
        pCurLayouter->prepare_to_start_layout();

        //assign width and position to this column
        LUnits width = (totalWidth * m_pMultiColumn->get_column_width(iCol)) / 100.0f;
        m_colWidth.push_back(width);
        m_colPosition.push_back(curPos);
        curPos.x += width;
    }

    //loop to layout columns while at least one column layout not finished
    int numCols = m_pMultiColumn->get_num_columns();
    bool fLayoutFinished = false;
    while(!fLayoutFinished)
    {
        fLayoutFinished = true;        //assume no pagebreaks needed
        for (iCol=0; iCol < numCols; ++iCol)
        {
            Layouter* pCurLayouter = m_colLayouters[iCol];
            //layout this column if not yet finished
            if (!pCurLayouter->is_item_layouted())
            {
                layout_column(pCurLayouter, m_pItemMainBox, m_colWidth[iCol],
                              m_colPosition[iCol]);
                fLayoutFinished &= pCurLayouter->is_item_layouted();
            }
        }

        //start new page if layout not finished
        if (!fLayoutFinished)
        {
            m_pItemMainBox = start_new_page();
            for (int i=0; i < numCols; ++i)
                m_colPosition[i].y = m_pItemMainBox->get_content_top();
        }
    }

    //loop to finish columns
    LUnits bottom = 0.0f;
    LUnits height = 0.0f;
    for (iCol=0; iCol < numCols; ++iCol)
    {
        Layouter* pCurLayouter = m_colLayouters[iCol];
        pCurLayouter->add_end_margins();

        GmoBox* pChildBox = pCurLayouter->get_item_main_box();
        bottom = max(bottom, pChildBox->get_bottom());
        height = max(height, pChildBox->get_height());
    }

    //update cursor and available space
    m_pageCursor.y = bottom;
    m_availableHeight -= height;

    set_layout_is_finished(true);
}

//---------------------------------------------------------------------------------------
void MultiColumnLayouter::create_main_box(GmoBox* pParentBox, UPoint pos, LUnits width,
                                          LUnits height)
{
    m_pItemMainBox = LOMSE_NEW GmoBoxDocPageContent(m_pMultiColumn);
    pParentBox->add_child_box(m_pItemMainBox);

    m_pItemMainBox->set_origin(pos);
    m_pItemMainBox->set_width(width);
    m_pItemMainBox->set_height(height);
}

//---------------------------------------------------------------------------------------
void MultiColumnLayouter::layout_column(Layouter* pColLayouter, GmoBox* pParentBox,
                                        LUnits width, UPoint pos)
{
    pColLayouter->create_main_box(pParentBox, pos, width, m_availableHeight);
    pColLayouter->layout_in_box();
    pColLayouter->set_box_height();
}


////=======================================================================================
//// ControlLayouter implementation
////=======================================================================================
//ControlLayouter::ControlLayouter(ImoContentObj* pItem, Layouter* pParent,
//                             GraphicModel* pGModel, LibraryScope& libraryScope,
//                             ImoStyles* pStyles)
//    : Layouter(pItem, pParent, pGModel, libraryScope, pStyles)
//    , m_pControl( dynamic_cast<ImoControl*>(pItem) )
//{
//}
//
////---------------------------------------------------------------------------------------
//void ControlLayouter::layout_in_box()
//{
//    //Control was layouted when method create_main_box() was invoked. Therefore, the
//    //only thing to do is to update cursor position
//
//    m_pageCursor.x = m_pItemMainBox->get_right();
//    m_pageCursor.y = m_pItemMainBox->get_bottom();
//
//    set_layout_is_finished(true);
//}
//
////---------------------------------------------------------------------------------------
//void ControlLayouter::create_main_box(GmoBox* pParentBox, UPoint pos, LUnits width,
//                                    LUnits height)
//{
//    m_pItemMainBox = m_pControl->layout(m_libraryScope, pos);
//    pParentBox->add_child_box(m_pItemMainBox);
//}



//=======================================================================================
// ListLayouter implementation
//=======================================================================================
ListLayouter::ListLayouter(ImoContentObj* pItem, Layouter* pParent,
                                 GraphicModel* pGModel, LibraryScope& libraryScope,
                                 ImoStyles* pStyles)
    : Layouter(pItem, pParent, pGModel, libraryScope, pStyles)
    , m_pList( dynamic_cast<ImoList*>(pItem) )
    , m_indent(1000.0f)        //1 cm
{
}

//---------------------------------------------------------------------------------------
void ListLayouter::layout_in_box()
{
    set_cursor_and_available_space(m_pItemMainBox);

    TreeNode<ImoObj>::children_iterator it;
    for (it = m_pList->begin(); it != m_pList->end(); ++it)
    {
        layout_item( static_cast<ImoContentObj*>( *it ), m_pItemMainBox );
    }
    set_layout_is_finished(true);
}

//---------------------------------------------------------------------------------------
void ListLayouter::create_main_box(GmoBox* pParentBox, UPoint pos, LUnits width,
                                   LUnits height)
{
    m_pItemMainBox = LOMSE_NEW GmoBoxDocPageContent(m_pList);
    pParentBox->add_child_box(m_pItemMainBox);

    m_pItemMainBox->set_origin(pos.x + m_indent, pos.y);
    m_pItemMainBox->set_width(width - m_indent);
    m_pItemMainBox->set_height(height);
}



//=======================================================================================
// ScorePlayerLayouter implementation
//=======================================================================================
ScorePlayerLayouter::ScorePlayerLayouter(ImoContentObj* pItem, Layouter* pParent,
                                 GraphicModel* pGModel, LibraryScope& libraryScope,
                                 ImoStyles* pStyles)
    : Layouter(pItem, pParent, pGModel, libraryScope, pStyles)
    , m_pPlayer( dynamic_cast<ImoScorePlayer*>(pItem) )
{
}

//---------------------------------------------------------------------------------------
void ScorePlayerLayouter::layout_in_box()
{
    set_cursor_and_available_space(m_pItemMainBox);


    //WordEngrouter engrouter(m_pPlayer, m_libraryScope, "Play");
    //LineReferences refs;

    //GmoShape* pShape = dynamic_cast<GmoShape*>(
    //                        engrouter.create_gm_object(m_pageCursor, refs) );
    //m_pItemMainBox->add_shape(pShape, GmoShape::k_layer_staff);
    //m_pageCursor.x += pShape->get_width();
    //m_pageCursor.y += pShape->get_height() + 500.0f;

    Control* pControl = m_pPlayer->get_player();
    pControl->measure();
    GmoBoxControl* pBox = pControl->layout(m_libraryScope, m_pageCursor);
    m_pItemMainBox->add_child_box(pBox);
    m_pageCursor.x += pBox->get_width();
    m_pageCursor.y += pBox->get_height() + 500.0f;

    set_layout_is_finished(true);
}

//---------------------------------------------------------------------------------------
void ScorePlayerLayouter::create_main_box(GmoBox* pParentBox, UPoint pos, LUnits width,
                                   LUnits height)
{
    m_pItemMainBox = LOMSE_NEW GmoBoxDocPageContent(m_pPlayer);
    pParentBox->add_child_box(m_pItemMainBox);

    m_pItemMainBox->set_origin(pos.x, pos.y);
    m_pItemMainBox->set_width(width);
    m_pItemMainBox->set_height(height);
}



}  //namespace lomse
