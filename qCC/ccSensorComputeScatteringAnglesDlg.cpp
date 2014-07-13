//##########################################################################
//#                                                                        #
//#                            CLOUDCOMPARE                                #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; version 2 of the License.               #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#          COPYRIGHT: EDF R&D / TELECOM ParisTech (ENST-TSI)             #
//#                                                                        #
//##########################################################################

#include "ccSensorComputeScatteringAnglesDlg.h"

ccSensorComputeScatteringAnglesDlg::ccSensorComputeScatteringAnglesDlg(QWidget* parent/*=0*/)
	: QDialog(parent)
	, Ui::sensorComputeScatteringAnglesDlg()
{
	setupUi(this);
	setWindowFlags(Qt::Tool/*Qt::Dialog | Qt::WindowStaysOnTopHint*/);
}


bool ccSensorComputeScatteringAnglesDlg::anglesInDegrees() const
{
	return anglesToDegCheckbox->checkState() == Qt::Checked;
}