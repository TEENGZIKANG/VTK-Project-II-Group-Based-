#include "vtkRenderer.h"
#include "vtkPointSet.h"
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
#include "vtkPiecewiseFunction.h"
//#include "vtkColorTransferFunction.h"
#include "vtkVolumeProperty.h"
//#include "vtkVolumeRayCastCompositeFunction.h"
#include "vtkVolumeRayCastMapper.h"
//#include "vtkVolumeRayCastMIPFunction.h"
#include "vtkStructuredPointsReader.h"
#include "vtkThresholdPoints.h"
#include "vtkMaskPoints.h"
#include "vtkConeSource.h"
#include "vtkGlyph3D.h"
#include "vtkLookupTable.h"
#include "vtkCommand.h"
#include "vtkHedgeHog.h"
#include "vtkStreamLine.h"
#include "vtkStreamer.h"
#include "vtkStreamTracer.h"
#include "vtkPoints.h"
#include "vtkTransform.h"
#include "vtkTransformFilter.h"


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



  // Read
	vtkStructuredPointsReader *reader= vtkStructuredPointsReader::New();
	reader->SetFileName("../data/testData1.vtk");
	reader->Update();

  // Hedgehog setup.
	vtkHedgeHog *hhog = vtkHedgeHog::New();
	hhog->SetInputConnection( reader->GetOutputPort() );
	hhog->SetScaleFactor( 4 );

/*
  // Glyph setup
	 vtkGlyph3D* glyh = vtkGlyph3D::New();
	 glyh->SetInputConnection(reader->GetOutputPort());
	 vtkConeSource *cone = vtkConeSource::New();
	 cone->SetRadius(0.2);
	 glyh->SetSourceConnection(cone->GetOutputPort());
	 glyh->SetScaleModeToScaleByVector();
	 glyh->SetScaleFactor(3);
*/

/*
//Part 3 Using Streamline 
 
 //	double origin[3] = { 100.0, 80.0, 1.0 };

 // Use this for the carotid.vtk (uncomment)
	//vtkTransform* transform = vtkTransform::New();
	//transform->Translate(-origin[0], -origin[1], -origin[2]);

	//vtkSmartPointer<vtkTransformFilter> transformFilter =
	//vtkSmartPointer<vtkTransformFilter>::New();
	//transformFilter->SetInputConnection(reader->GetOutputPort());
	//transformFilter->SetTransform(transform);
	//transformFilter->Update();


// vtkStreamLine
	//vtkStreamLine* streamline = vtkStreamLine::New();
	//streamline->SetSource(startPoints);
	//streamline->SetInputConnection(reader->GetOutputPort());
	//streamline->SetStartPosition(45.0,30.0,30.0);

	//vtkStreamTracer* streamLine = vtkStreamTracer::New();

	//vtkPointSet* seedPoint = vtkPointSet::New();
	//vtkPoints* points = vtkPoints::New();

	//testData1
	//int xSize = 36;  // Number of points in x-direction
	//int ySize = 36;  // Number of points in y-direction
	//int zSize = 2;  // Number of points in z-direction

	//int maxX = 36;
	//int minX = 0;
	//int maxY = 36;
	//int minY = 0;
	//int maxZ = 0;
	//int minZ = 0;


// testData2

	int xSize = 150;  // Number of points in x-direction
	int ySize = 150;  // Number of points in y-direction
	int zSize = 2 ;  // Number of points in z-direction

	int maxX = 357;
	int minX = 0;
	int maxY = 357;
	int minY = 0;
	int maxZ = 0;
	int minZ = 0;



//carotid.vtk
	//int xSize = 46;  // Number of points in x-direction
	//int ySize = 29;  // Number of points in y-direction
	//int zSize = 25;  // Number of points in z-direction

	//int maxX = 76;
	//int minX = 0;
	//int maxY = 49;
	//int minY = 0;
	//int maxZ = 45;
	//int minZ = 0;

// Seed Point
    // Compute the spacing between the grid points
	double xSpacing = (maxX - minX) / (xSize - 1);
	double ySpacing = (maxY - minY) / (ySize - 1);
	double zSpacing = (maxZ - minZ) / (zSize - 1);

    // Generate the grid of seed points
	for (int k = 0; k < zSize; k++) {
		for (int j = 0; j < ySize; j++) {
			for (int i = 0; i < xSize; i++) {
				double point[3];
				point[0] = minX + i * xSpacing;
				point[1] = minY + j * ySpacing;
				point[2] = minZ + k * zSpacing;
				points->InsertNextPoint(point);
			}
		}
	}

	seedPoint->SetPoints(points);

//vtkPolyData
	vtkPolyData* polyData = vtkPolyData::New();
	polyData->SetPoints(points);

//vtkStreamTracer
  
  streamLine->SetInputConnection(reader->GetOutputPort());//transformFilter for carotid.vtk
  streamLine->SetSourceData(polyData);
  streamLine->SetStartPosition(10.1, 10.1, 2.5);
  streamLine->SetInitialIntegrationStep(0.5);
  streamLine->SetMaximumPropagation(200);
  streamLine->SetIntegrationDirectionToBoth();
  streamLine->Update();
	
  //Hedgehog Setup - Apply the streamline to the hedgehog method
	vtkHedgeHog* hhog = vtkHedgeHog::New();
	hhog->SetInputConnection(streamLine->GetOutputPort());
	hhog->SetScaleFactor(1);
	hhog->Update();
*/
	// Lookup Table
	vtkLookupTable* lut = vtkLookupTable::New();
	lut->SetHueRange(0.667, 0.0);
	lut->Build();

  // Poly Mapper
	vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
	mapper->SetInputConnection(hhog->GetOutputPort() );//glyh
	mapper->SetScalarRange( 0.0, 1.0 );
	mapper->SetLookupTable( lut );

  // Actor
	vtkActor *actor = vtkActor::New();
    actor->SetMapper( mapper );

  // Actors are added to the renderer. An initial camera view is created.
  // The Dolly() method moves the camera towards the FocalPoint,
  // thereby enlarging the image.
	aRenderer->AddActor(actor);

  // Set a background color for the renderer and set the size of the
  // render window (expressed in pixels).
	aRenderer->SetBackground(0, 0, 0);
	renWin->SetSize(800, 600);

  // Initialize the event loop and then start it.
	iren->Initialize();
	renWin->SetWindowName( "Simple Volume Renderer" );
	renWin->Render();
	iren->Start(); 

	return 0;
}

