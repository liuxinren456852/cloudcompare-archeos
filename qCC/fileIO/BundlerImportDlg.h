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

#ifndef CC_BUNDLER_IMPORT_DIALOG_HEADER
#define CC_BUNDLER_IMPORT_DIALOG_HEADER

#include <algorithm>

//GUIs generated by Qt Designer
#include <ui_openBundlerFileDlg.h>

//! Dialog for importation of Snavely's Bundler files
class BundlerImportDlg : public QDialog, public Ui::BundlerImportDlg
{
    Q_OBJECT

public:

	//! Default constructor
    BundlerImportDlg(QWidget* parent=0);

	//! Destructor
    virtual ~BundlerImportDlg();

	//! Returns whether keypoints should be imported
	bool importKeypoints() const;
	//! Returns whether alternative keypoints should be used
	bool useAlternativeKeypoints() const;
	//! Returns whether images should be imported
	bool importImages() const;
	//! Returns whether images should be undistorted
	bool undistortImages() const;
	//! Returns whether images should be ortho-rectified as clouds
	bool orthoRectifyImagesAsClouds() const;
	//! Returns whether images should be ortho-rectified as images
	bool orthoRectifyImagesAsImages() const;
	//! Returns whether colored pseudo-DTM should be generated
	bool generateColoredDTM() const;
	//! Returns images should be kept in memory or not
	bool keepImagesInMemory() const;

	//! Sets keypoints count on initialization
	void setKeypointsCount(unsigned count);
	//! Sets cameras count on initialization
	void setCamerasCount(unsigned count);
	//! Sets file version on initialization
	void setVer(unsigned majorVer, unsigned minorVer);

	//! Sets default image list filename (full path)
	void setImageListFilename(const QString& filename);
	//! Gets image list filename (full path)
	QString getImageListFilename() const;

	//! Sets default alternative keypoints filename (full path)
	void setAltKeypointsFilename(const QString& filename);
	//! Gets alternative keypoints filename (full path)
	QString getAltKeypointsFilename() const;

	//! Returns scale factor
	double getScaleFactor() const;

	//! Returns desired number of vertices for DTM
	unsigned getDTMVerticesCount() const;

protected slots:
    void browseImageListFilename();
    void browseAltKeypointsFilename();
    void acceptAndSaveSettings();

protected:

	//! Inits dialog state from persistent settings
	void initFromPersistentSettings();

	//! Saves dialog state from persistent settings
	void saveToPersistentSettings();

};

#endif //CC_BUNDLER_IMPORT_DIALOG_HEADER
