#include "Cylinder.h"


Cylinder::Cylinder(void):Mesh()
{
	name = "Cylinder";
	segments = 0;
}

Cylinder::Cylinder(const Cylinder & c):Mesh(c)
{
	segments = c.segments;
}

Cylinder::~Cylinder(void)
{
}

Cylinder::Cylinder(unsigned int newsegments)
{
	segments = newsegments;
		if(segments >= 3){
		materials.push_back(FaceMaterial());
		double theta = 0, x = 0., y = 0., z = 0.;
		std::vector<Point> points = std::vector<Point>();

		points.push_back(Point(0.,1.,0.));
		for(int i = 1; i>-2; i=i-2){
			for(unsigned int j = 0; j<segments; j++){
				theta -= (2*M_PI/segments);
				x = cos(theta);
				z = sin(theta);
				y = i;
				points.push_back(Point(x,y,z));
			}
		}
		points.push_back(Point(0.,-1.,0.));

		for(unsigned int i = 0; i < points.size(); i++){
			if(i>0 && i<segments){
				faces.push_back(face_materialindex(Face(points[0],points[i],points[i+1]),0));
				//faces.push_back(face_materialindex(Face(points[i], points[i+segments], points[i+1+segments], points[i+1]),0));
			}
			else if(i==segments){
				faces.push_back(face_materialindex(Face(points[0],points[i],points[i-segments+1]),0));
				faces.push_back(face_materialindex(Face(points[i], points[i+segments], points[i+1], points[i+1-segments]),0));
			}
			else if(i>segments && i<points.size()-1){
				if(i<points.size()-2){
					if(i%segments!=0){
						faces.push_back(face_materialindex(Face(points[i], points[i-segments], points[i+1-segments], points[i+1]),0));
					}
					else{
						faces.push_back(face_materialindex(Face(points[i], points[i+segments], points[i+1], points[i+1-segments]),0));
					}
				}
				if(i>points.size()-1-segments){
					faces.push_back(face_materialindex(Face(points[i], points[points.size()-1], points[i-1]),0));
				}
			}
			else if(i==points.size()-1){
				faces.push_back(face_materialindex(Face(points[i], points[i-1], points[i-segments]),0));
			}
		}
	}
}

