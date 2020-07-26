/*  This file is part of YUView - The YUV player with advanced analytics toolset
*   <https://github.com/IENT/YUView>
*   Copyright (C) 2015  Institut f�r Nachrichtentechnik, RWTH Aachen University, GERMANY
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 3 of the License, or
*   (at your option) any later version.
*
*   In addition, as a special exception, the copyright holders give
*   permission to link the code of portions of this program with the
*   OpenSSL library under certain conditions as described in each
*   individual source file, and distribute linked combinations including
*   the two.
*   
*   You must obey the GNU General Public License in all respects for all
*   of the code used other than OpenSSL. If you modify file(s) with this
*   exception, you may extend this exception to your version of the
*   file(s), but you are not obligated to do so. If you do not wish to do
*   so, delete this exception statement from your version. If you delete
*   this exception statement from all source files in the program, then
*   also delete it here.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "UserData.h"

#include "parser/common/parserMacros.h"
#include "parser/common/ReaderHelper.h"

namespace MPEG2
{

bool UserData::parse(const QByteArray & parameterSetData, TreeItem * root)
{
  nalPayload = parameterSetData;

  // Create a new TreeItem root for the item
  // The macros will use this variable to add all the parsed variables
  TreeItem *const itemTree = root ? new TreeItem("user_data()", root) : nullptr;

  if (itemTree)
  {
    // Log the user data bytes
    int i=0;
    for (char c : parameterSetData)
    {
      QString code;
      for (int i = 7; i >= 0; i--)
        code += (c & (1 << i)) ? "1" : "0";
       new TreeItem(QString("byte[%1]").arg(i++), c, QString("u(v) -> u(8)"), code, itemTree);
    }
  }
  return true;
}

} // namespace MPEG2