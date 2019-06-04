/*
 * main.cpp
 *
 *  Created on: 4 jun. 2019
 *      Author: alejandro
 */


#include <opencv2/viz.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>
using namespace cv;
using namespace std;

#include <Osmap.h>
#include <fstream>
#include <cstdlib>

using namespace ORB_SLAM2;

#define N_MAPPOINTS 100	// Number of fake MapPoints in map
#define N_KEYFRAMES 11	// Number of fake KeyFrames in map
#define N_FEATURES 19	// Number of fake features in each KeyFrame

unsigned int MapPoint::nNextId = 0;
unsigned int KeyFrame::nNextId = 0;





int main(int argc, char **argv){

	  System system;
	  system.mpMap = new Map;
	  system.mpKeyFrameDatabase = new KeyFrameDatabase;
	  Osmap osmap(system);

	  // Arguments
	  string filename;
	  if(argc == 1){
		  cout << "Usage: osmap-viewer mapFileName.yaml [options]" << endl;
		  cerr << "No map file provided." << endl;
		  exit(1);
	  }else
		  filename = argv[1];

	  // Options
	  /*if(argc>2)
		  osmap.options = stoi(argv[2]);
	  else
		  osmap.options.set(Osmap::NO_SET_BAD, 1);*/

	  // Load map.  mapLoad clears previous map.
	  osmap.mapLoad(filename);

	  // Put loaded MapPoints into a cloud
	  vector<Vec3f> mapPointsCloud;
	  for(auto pMP : system.mpMap->mspMapPoints)
		  mapPointsCloud.push_back(Vec3f(pMP->mWorldPos));

	  viz::WCloud cloudWidget(mapPointsCloud);

	  viz::Viz3d mapWindow("Osmap viewer");
	  mapWindow.showWidget("Coordinate system", viz::WCoordinateSystem());
	  mapWindow.showWidget("MapPoints cloudWidget", cloudWidget);

	  while(!mapWindow.wasStopped())
		  mapWindow.spinOnce(1, true);

	  return 0;
}
