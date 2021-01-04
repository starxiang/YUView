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

#include "operating_point_information_rbsp.h"

namespace parser::vvc
{

using namespace parser::reader;

void operating_point_information_rbsp::parse(ReaderHelperNew &reader)
{
  ReaderHelperNewSubLevel subLevel(reader, "operating_point_information_rbsp");

  this->opi_ols_info_present_flag  = reader.readFlag("opi_ols_info_present_flag");
  this->opi_htid_info_present_flag = reader.readFlag("opi_htid_info_present_flag");
  if (this->opi_ols_info_present_flag)
  {
    this->opi_ols_idx = reader.readUEV("opi_ols_idx");
  }
  if (this->opi_htid_info_present_flag)
  {
    this->opi_htid_plus1 = reader.readBits("opi_htid_plus1", 3);
  }
  this->opi_extension_flag = reader.readFlag("opi_extension_flag", Options().withCheckEqualTo(0));
  if (this->opi_extension_flag)
  {
    while (reader.more_rbsp_data())
    {
      this->opi_extension_data_flag = reader.readFlag("opi_extension_data_flag");
    }
  }
  this->rbsp_trailing_bits_instance.parse(reader);
}

} // namespace parser::vvc