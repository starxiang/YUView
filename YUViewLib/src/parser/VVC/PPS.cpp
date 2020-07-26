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

#include "PPS.h"
#include "parser/common/parserMacros.h"
#include "parser/common/ReaderHelper.h"

namespace VVC
{

bool PPS::parse(const QByteArray &parameterSetData, TreeItem *root)
{
  nalPayload = parameterSetData;

  ReaderHelper reader(parameterSetData, root, "pic_parameter_set_rbsp()");

  READBITS(pps_pic_parameter_set_id, 6);
  READBITS(pps_seq_parameter_set_id, 4);
  READFLAG(pps_mixed_nalu_types_in_pic_flag);
  READUEV(pps_pic_width_in_luma_samples);
  READUEV(pps_pic_height_in_luma_samples);
  READFLAG(pps_conformance_window_flag);
  if (pps_conformance_window_flag)
  {
    READUEV(pps_conf_win_left_offset);
    READUEV(pps_conf_win_right_offset);
    READUEV(pps_conf_win_top_offset);
    READUEV(pps_conf_win_bottom_offset);
  }
  READFLAG(pps_scaling_window_explicit_signalling_flag);
  if (pps_scaling_window_explicit_signalling_flag)
  {
    READSEV(pps_scaling_win_left_offset);
    READSEV(pps_scaling_win_right_offset);
    READSEV(pps_scaling_win_top_offset);
    READSEV(pps_scaling_win_bottom_offset);
  }

  // ....
  // TODO: There is more to parse. But we don't need more for now.
  return true;
}

} // namespace VVC