#include "UvSphere.h"


UvSphere::UvSphere(void):Mesh()
{
	name = "UvSphere";
	segments = 0;
	rings = 0;
}


UvSphere::~UvSphere(void)
{
}


UvSphere::UvSphere(unsigned int newsegments, unsigned int newrings):Mesh()
{
	segments = newsegments;
	rings = newrings;
	if(segments >= 3 && rings >= 3){
		materials.push_back(FaceMaterial());
		double theta = 0, phi = 0, x = 0., y = 0., z = 0.;
		std::vector<Point> points = std::vector<Point>();

		points.push_back(Point(0.,1.,0.));
		for(unsigned int i = 0; i<rings-1; i++){
			phi -= (M_PI/rings);
			for(unsigned int j = 0; j<segments; j++){
				theta -= (2*M_PI/segments);
				x = cos(theta)*sin(phi);
				z = sin(theta)*sin(phi);
				y = cos(phi);
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


UvSphere::UvSphere(const UvSphere & s):Mesh(s)
{
	rings = s.rings;
	segments = s.segments;
}


UvSphere & UvSphere::operator=(const UvSphere & s)
{
	if(&s != this){
		faces.clear();
		materials.clear();
		segments = s.segments;
		rings = s.rings;
		for(unsigned int i=0; i<s.faces.size(); i++){
			faces.push_back(s.faces[i]);
		}
		for(unsigned int i=0; i<materials.size(); i++){
			materials.push_back(materials[i]);
		}
	}
	return * this;
}
