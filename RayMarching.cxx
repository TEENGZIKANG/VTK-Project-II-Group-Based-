
// Modified from a modified version of the file described in the following comment...
//    -Chris

/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: Medical1.cxx,v $
  Language:  C++
  Date:      $Date: 2002/11/27 16:06:38 $
  Version:   $Revision: 1.2 $

  Copyright (c) 1993-2002 Ken Martin, Will Schroeder, Bill Lorensen 
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/


#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkVolume16Reader.h"
#include "vtkPolyDataMapper.h"
#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkOutlineFilter.h"
#include "vtkCamera.h"
#include "vtkProperty.h"
#include "vtkPolyDataNormals.h"
#include "vtkContourFilter.h"
#include "vtkStructuredPointsReader.h"
#include "vtkMarchingCubes.h"
#include "vtkRecursiveDividingCubes.h"
#include "vtkScalarBarWidget.h"
#include "vtkScalarBarActor.h"
#include "vtkSmartVolumeMapper.h"
#include "vtkPiecewiseFunction.h"
#include "vtkColorTransferFunction.h"
#include "vtkVolumeProperty.h"
#include "vtkVolumeRayCastCompositeFunction.h"
#include "vtkVolumeRayCastMapper.h"
#include "vtkVolumeRayCastMIPFunction.h"

class KeyInterpreter : public vtkCommand {
public:
	// Allocator
	static KeyInterpreter* New(void) { return new KeyInterpreter; }

	// Internal data.  This needs to be set immediately after allocation.
	vtkSmartVolumeMapper* map;
	vtkContourFilter* contourExtractor1;
	vtkContourFilter* contourExtractor2;
	vtkRenderer* renderer;
	vtkActor* outline;
	vtkActor* contour1;
	vtkActor* contour2;
	vtkVolume* volume;
	vtkColorTransferFunction* colorTransferFunction;
	vtkPiecewiseFunction* opacityTransferFunction;
	vtkColorTransferFunction* volumeColorTransferFunction;
	vtkPiecewiseFunction* volumeOpacityTransferFunction;

	// Variables for iso-value and ray step size
	double stepSize;
	double isoValue1 = 1500;
	double isoValue2 = 2750;

	KeyInterpreter() {
		stepSize = 1.0; // Initial step size
	}

	int mode = 0;

	// Called upon the registered event (i.e., a key press)
	void Execute(vtkObject* caller, unsigned long eventId, void* callData) {
		double dist;
		//int point;
		vtkRenderWindowInteractor* iren =
			reinterpret_cast<vtkRenderWindowInteractor*>(caller);
		switch (iren->GetKeyCode()) {
		case '+':
		case '=':
			if (mode == 0) {
				dist = map->GetSampleDistance();
				dist += 1;
				map->SetSampleDistance(dist);
				cout << "abc" << endl;
			}
			break;
		case '-':
		case '_':
			if (mode == 0) {
				dist = map->GetSampleDistance();
				if (dist > 1) {
					dist -= 1;
					map->SetSampleDistance(dist);
				}
			}
			break;
		case 'I':
			if (mode == 1) {
				isoValue1 += 100.0; // Increase iso-value for contourExtractor1
				contourExtractor1->SetValue(0, isoValue1);
				cout << isoValue1 << endl;
			}
			break;
		case 'i':
			if (mode == 1) {
				isoValue1 -= 100.0; // Decrease iso-value for contourExtractor1
				if (isoValue1 < 0.0) isoValue1 = 0.0; // Ensure it doesn't go below 0
				contourExtractor1->SetValue(0, isoValue1);
				cout << isoValue1 << endl;
			}
			break;
		case 'K':
			if (mode == 1) {
				isoValue2 += 100.0; // Increase iso-value for contourExtractor2
				contourExtractor2->SetValue(0, isoValue2);
				cout << isoValue2 << endl;
			}
			break;
		case 'k':
			if (mode == 1) {
				isoValue2 -= 100.0; // Decrease iso-value for contourExtractor2
				if (isoValue2 < 0.0) isoValue2 = 0.0; // Ensure it doesn't go below 0
				contourExtractor2->SetValue(0, isoValue2);
				cout << isoValue2 << endl;
			}
			break;
			iren->Render();
		}
	}
	};

int main (int argc, char **argv)
{

  // Create the renderer, the render window, and the interactor. The renderer
  // draws into the render window, the interactor enables mouse- and 
  // keyboard-based interaction with the data within the render window.
	vtkRenderer *aRenderer = vtkRenderer::New();
	vtkRenderWindow *renWin = vtkRenderWindow::New();
	renWin->AddRenderer(aRenderer);
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);


  // vtkVolumeReader16 reads in the head CT data set.  
	vtkVolume16Reader *reader= vtkVolume16Reader::New();
    reader->SetDataDimensions (256,256);
    //reader->SetImageRange (1,93);
	reader->SetImageRange(1, 178);
	//reader->SetImageRange(1, 93);
    reader->SetDataByteOrderToLittleEndian();
	reader->SetFilePrefix("../data/teapot/teapot");
	//reader->SetFilePrefix("../data/headsq/quarter");
	//reader->SetFilePrefix("../data/headsq/quarter");
	//reader->SetFilePrefix("../data/aneurism/aneurism");
	//reader->SetFilePrefix("../data/teapot/teapot");
    //reader->SetDataSpacing (3.2, 3.2, 1.5);
	//reader->SetDataSpacing(1, 1, 2.2);
	reader->SetDataSpacing(1, 1, 2.2);


  // This part creates the colorMap function to the volume rendering.
  vtkPiecewiseFunction* opacityTransferFunction = vtkPiecewiseFunction::New();
	opacityTransferFunction->AddPoint(20, 0.0);
	opacityTransferFunction->AddPoint(40, 0.0);
	opacityTransferFunction->AddPoint(60, 0.3);
	opacityTransferFunction->AddPoint(80,0.5);
	opacityTransferFunction->AddPoint(100, 0.9); 


  vtkColorTransferFunction* colorTransferFunction = vtkColorTransferFunction::New();
	colorTransferFunction->AddRGBPoint(0.0, 0.0, 0.0, 0.0);
	colorTransferFunction->AddRGBPoint(500.0, 1.0, 0.6, 0.0);
	colorTransferFunction->AddRGBPoint(700.0, 1.0, 0.6, 0.0);
	colorTransferFunction->AddRGBPoint(800.0, 1.0, 0.0, 0.0);
	colorTransferFunction->AddRGBPoint(1150.0, 0.9, 0.9, 0.9);
	
  // The property describes how the data will look
  vtkVolumeProperty* volumeProperty = vtkVolumeProperty::New();
	volumeProperty->SetColor(colorTransferFunction);
	volumeProperty->SetScalarOpacity(opacityTransferFunction);
	volumeProperty->ShadeOn();
	volumeProperty->SetInterpolationTypeToLinear();

  // vtkVolumeRay Functions
	//vtkVolumeRayCastCompositeFunction* compositeFunction = vtkVolumeRayCastCompositeFunction::New();
 	//vtkVolumeRayCastMIPFunction* compositeFunction = vtkVolumeRayCastMIPFunction::New();

	//vtkVolumeRayCastMapper* volumeMapper = vtkVolumeRayCastMapper::New();
	//volumeMapper->SetVolumeRayCastFunction(compositeFunction);
	//volumeMapper->SetInputData(reader->GetOutput());
	//vtkNew<vtkStructuredPointsReader>reader;
	//reader->SetFileName();
	//reader->Update();

	vtkNew<vtkSmartVolumeMapper> volumeMapper;
	volumeMapper->SetInputConnection(reader->GetOutputPort());


  // Set the sampling rate
	volumeMapper->SetSampleDistance(1.0);



  // The volume holds the mapper and the property and
	// can be used to position/orient the volume
	vtkVolume* volume = vtkVolume::New();
	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);

 // An outline provides context around the data.
  vtkOutlineFilter *outlineData = vtkOutlineFilter::New();
    outlineData->SetInputData((vtkDataSet *) reader->GetOutput());
  vtkPolyDataMapper *mapOutline = vtkPolyDataMapper::New();
    mapOutline->SetInputData(outlineData->GetOutput());
  vtkActor *outline = vtkActor::New();
    outline->SetMapper(mapOutline);
    outline->GetProperty()->SetColor(0,0,0);

	KeyInterpreter* key = KeyInterpreter::New();
	key->renderer = aRenderer;
	key->map = volumeMapper;
	//key->contourExtractor1 = contourExtractor;
	//key->contourExtractor2 = contourExtractor2;
	key->outline = outline;
	//key->contour1 = contour;
	//key->contour2 = contour2;
	key->volume = volume;
	key->colorTransferFunction = colorTransferFunction;
	key->opacityTransferFunction = opacityTransferFunction;
	key->volumeColorTransferFunction = colorTransferFunction;
	key->volumeOpacityTransferFunction = opacityTransferFunction;
	//key->isoValue1 = isoValue1;
	//key->isoValue2 = isoValue2;
	//key->assignMaxNum();
	iren->AddObserver(vtkCommand::KeyPressEvent, key);

  // It is convenient to create an initial view of the data. The FocalPoint
  // and Position form a vector direction. Later on (ResetCamera() method)
  // this vector is used to position the camera to look at the data in
  // this direction.
  vtkCamera *aCamera = vtkCamera::New();
    aCamera->SetViewUp (0, 0, -1);
    aCamera->SetPosition (0, 1, 0);
    aCamera->SetFocalPoint (0, 0, 0);
    aCamera->ComputeViewPlaneNormal();

  // Actors are added to the renderer. An initial camera view is created.
  // The Dolly() method moves the camera towards the FocalPoint,
  // thereby enlarging the image.
  aRenderer->AddActor(outline);
  aRenderer->AddVolume(volume);
  aRenderer->SetActiveCamera(aCamera);
  aRenderer->ResetCamera ();
  aCamera->Dolly(1.5);

  // Set a background color for the renderer and set the size of the
  // render window (expressed in pixels).
  aRenderer->SetBackground(1,1,1);
  renWin->SetSize(800, 600);

  // Note that when camera movement occurs (as it does in the Dolly()
  // method), the clipping planes often need adjusting. Clipping planes
  // consist of two planes: near and far along the view direction. The 
  // near plane clips out objects in front of the plane; the far plane
  // clips out objects behind the plane. This way only what is drawn
  // between the planes is actually rendered.
  aRenderer->ResetCameraClippingRange();


  vtkScalarBarWidget *scalarWidget = vtkScalarBarWidget::New();
  scalarWidget->SetInteractor(iren);
  scalarWidget->GetScalarBarActor()->SetTitle("Transfer Function");
  scalarWidget->GetScalarBarActor()->SetLookupTable(colorTransferFunction);


  // Initialize the event loop and then start it.
  iren->Initialize();
  renWin->SetWindowName( "Simple Volume Renderer" );
  renWin->Render();
  scalarWidget->EnabledOn();
  iren->Start(); 

  return 0;
}
