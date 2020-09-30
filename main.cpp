#include <CameraPerspective.h>

#include "Prim.h"
#include "PrimSphere.h"
#include "PrimPlane.h"
#include "PrimTriangle.h"

// Work with Kristian Sterjo

Mat RenderFrame(ICamera& camera)
{
	// scene objects
	// In order to make a correct function Call we have to modify base constructors
	CPrimSphere s1(RGB(1,0,0.4),Vec3f(-2, 1.7f, 0), 2);
	CPrimSphere s2(RGB(0.2,0.6,0.3),Vec3f(1, -1, 1), 2.2f);
	CPrimSphere s3(RGB(0.5,1,0),Vec3f(3, 0.8f, -2), 2);
	CPrimPlane p1(RGB(0.5,0.3,1),Vec3f(0, -1, 0), Vec3f(0, 1, 0));
	
	CPrimTriangle t1(RGB(0.5,0.5,0.4),Vec3f(-2, 3.7f, 0), Vec3f(1, 2, 1), Vec3f(3, 2.8f, -2));
	CPrimTriangle t2(RGB(0.7,0.8,0.3),Vec3f(3, 2, 3), Vec3f(3, 2, -3), Vec3f(-3, 2, -3));
	
	std::vector<CPrim*> primitives = { &s1 , &s2 , &s3 , &p1 , &t1 , &t2 };
	Vec3f col;

	Mat img(camera.getResolution(), CV_32FC3); 	// image array
	Ray ray;                            		// primary ray
	
	for(int y = 0; y< img.rows; y++)
		for (int x = 0; x < img.cols; x++) {
			
			// Initialize your ray here
			if(!camera.InitRay(x,y,ray)){
				continue;
			}
			// Your code	
			Vec3f col = RGB(0, 0, 0); // background color
			
			/*
			 * Find closest intersection with scene
			 * objetcs and calculate color
			 */
			
			// Your code
			for(auto it: primitives) {
			//for(std::vector<CPrim*>::iterator it = primitives.begin(); it != primitives.end(); it++){
				if(it -> Intersect(ray)){
					col = it -> getColor();
				}
			}

			img.at<Vec3f>(y, x) = col; // store pixel color
		}
	
	img.convertTo(img, CV_8UC3, 255);
	return img;
}

int main(int argc, char* argv[])
{
	const Size resolution(800, 600);
	// render three images with different camera settings
	
	CCameraPerspective c1(Vec3f(0, 0, 10), Vec3f(0, 0, -1), Vec3f(0, 1, 0), 60, resolution);
	Mat img1 = RenderFrame(c1);
	imwrite("perspective1.jpg", img1);
	
	CCameraPerspective c2(Vec3f(-8, 3, 8), Vec3f(1, -0.1f, -1), Vec3f(0, 1, 0), 45, resolution);
	Mat img2 = RenderFrame(c2);
	imwrite("perspective2.jpg", img2);
	
	CCameraPerspective c3(Vec3f(-8, 3, 8), Vec3f(1, -0.1f, -1), Vec3f(1, 1, 0), 45, resolution);
	Mat img3 = RenderFrame(c3);
	imwrite("perspective3.jpg", img3);
	return 0;
}
