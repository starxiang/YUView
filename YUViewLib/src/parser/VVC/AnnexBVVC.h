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

#pragma once

#include <QSharedPointer>

#include "../AnnexB.h"
#include "NalUnitVVC.h"
#include "video/videoHandlerYUV.h"

using namespace YUV_Internals;

namespace parser
{

// This class knows how to parse the bitrstream of VVC annexB files
class AnnexBVVC : public AnnexB
{
  Q_OBJECT

public:
  AnnexBVVC(QObject *parent = nullptr) : AnnexB(parent)
  {
    curFrameFileStartEndPos = pairUint64(-1, -1);
  }
  ~AnnexBVVC(){};

  // Get some properties
  double         getFramerate() const override;
  QSize          getSequenceSizeSamples() const override;
  yuvPixelFormat getPixelFormat() const override;

  QList<QByteArray> getSeekFrameParamerSets(int iFrameNr, uint64_t &filePos) override;
  QByteArray        getExtradata() override;
  QPair<int, int>   getProfileLevel() override;
  Ratio             getSampleAspectRatio() override;

  ParseResult parseAndAddNALUnit(int                                           nalID,
                                 QByteArray                                    data,
                                 std::optional<BitratePlotModel::BitrateEntry> bitrateEntry,
                                 std::optional<pairUint64> nalStartEndPosFile = {},
                                 TreeItem *                parent             = nullptr) override;

protected:
  std::optional<pairUint64>
      curFrameFileStartEndPos; //< Save the file start/end position of the current frame (in case
                               //the frame has multiple NAL units)

  size_t counterAU{0};
  size_t sizeCurrentAU{0};

  using NalMap = std::map<unsigned, std::shared_ptr<vvc::NalUnitVVC>>;

  struct ActiveParameterSets
  {
    NalMap vpsMap;
    NalMap spsMap;
    NalMap ppsMap;
  };
  ActiveParameterSets activeParameterSets;

};

} // namespace parser