#include "Mesh.h"

face_materialindex::face_materialindex(Face & f, unsigned int m){
	face = f;
	materialIndex = m;
}

face_materialindex::~face_materialindex(void){
	face.~Face();
}

//-------------------------------------------------------------

Mesh::Mesh(void)
{
	faces = std::vector<face_materialindex>();
	name = "Mesh";
	centerPosition = Point(0,0,0);
	angle = 0.;
	scale = Point(1,1,1);
	materials = std::vector<FaceMaterial>();
}

Mesh::Mesh(std::string objfilename, std::string mtlfilename)
{
	centerPosition = Point(0,0,0);
	angle = 0.;
	scale = Point(1,1,1);
	faces = std::vector<face_materialindex>();
	materials = std::vector<FaceMaterial>();
	loadObjFile(objfilename, mtlfilename);
}

Mesh::Mesh(const Mesh & mesh){
	if(&mesh != this){
		faces = std::vector<face_materialindex>();
		materials = std::vector<FaceMaterial>();
		for(unsigned int i=0; i<mesh.faces.size(); i++){
			faces.push_back(mesh.faces[i]);
		}
		for(unsigned int i=0; i<materials.size(); i++){
			materials.push_back(materials[i]);
		}
	}
}

Mesh & Mesh::operator=(const Mesh & mesh){
	if(&mesh != this){
		faces.clear();
		materials.clear();
		for(unsigned int i=0; i<mesh.faces.size(); i++){
			faces.push_back(mesh.faces[i]);
		}
		for(unsigned int i=0; i<materials.size(); i++){
			materials.push_back(materials[i]);
		}
	}
	return * this;
}

Face & Mesh::operator[](unsigned int i){
	return faces[i].face;
}

void Mesh::draw(){
	for(unsigned int i=0; i<faces.size(); i++){
		materials[faces[i].materialIndex].applyMaterial();
		faces[i].face.draw();
	}
}

void Mesh::rescale(const Point & newsize){
	for(unsigned int i = 0; i<faces.size(); i++){
		faces[i].face.rescale(newsize);
	}
}

void Mesh::rotate(double angledeg, Point & axis){
	Point p = centerPosition;
	setCenterPosition(Point(0,0,0));
	for(unsigned int i=0; i<faces.size();i++){
		faces[i].face.rotate(angledeg, axis);
	}
	setCenterPosition(p);
}

void Mesh::loadObjFile(std::string objfileName, std::string mtlfilename)
{
	//intialize the file input stream to read the mtl file for materials and textures
	std::string line,curname="";
	std::ifstream objifs (mtlfilename.c_str(),std::ios::in);
	if (!objifs) { 
		std::cerr << "Cannot open " << mtlfilename << std::endl; exit(1); 
	}

	//store the mtl materials characteristics and name from the file
	std::map<char *, FaceMaterial> fmaterials = std::map<char *, FaceMaterial>();
	char materialname[255];
	char texturepath[255];

	//reading the mtl file line by line
	while(getline(objifs,line)){
		float r=0,g=0,b=0;
		//getting the material name and storing it in the map
		if(line.find("newmtl")!=std::string::npos){
			sscanf_s(line.c_str(), "%*s %s",&materialname); 
			fmaterials.insert(std::pair<char *, FaceMaterial>(materialname, FaceMaterial()));
		}
		//getting the ambiant characteristics 
		else if(line.substr(0,2)=="Ka"){
			sscanf_s(line.c_str(), "%*s %f %f %f",&r,&g,&b); 
			fmaterials[materialname].setAmbient(r,g,b,1);
		}
		//getting the diffuse characteristics 
		else if(line.substr(0,2)=="Kd"){
			sscanf_s(line.c_str(), "%*s %f %f %f",&r,&g,&b); 
			fmaterials[materialname].setDiffuse(r,g,b,1);
		}
		//getting the specular characteristics 
		else if(line.substr(0,2)=="Ks"){
			sscanf_s(line.c_str(), "%*s %f %f %f",&r,&g,&b); 
			fmaterials[materialname].setSpecular(r,g,b,1);
		}
		//getting the eventual texture file
		else if(line.find("map_")!=std::string::npos){
			//replacing the windows style path if necessary
			replace(line.begin(), line.end(), '\\', '/');
			sscanf_s(line.c_str(),"%*s %s",&texturepath);
			std::string txpath = texturepath;
			fmaterials[materialname].setTexture(Texture(txpath));
		}
	}

	//now reading the obj file for vertexes and faces
	objifs = std::ifstream(objfileName.c_str(),std::ios::in);
	if (!objifs) { 
		std::cerr << "Cannot open " << objfileName << std::endl; exit(1); 
	}

	//storing the vertexes, normal and texture mapping
	std::vector<Point> points = std::vector<Point>();
	std::vector<Point> textureMapping = std::vector<Point>();
	std::vector<Point> normals = std::vector<Point>();

	while(getline(objifs,line)){
		//getting the mesh name
		if(line[0]=='o'){
			sscanf_s(line.c_str(),"o %s",&name);
		}
		//getting the vertex coordiantes
		if(line[0]=='v') 
		{
			float x=0,y=0,z=0;
			sscanf_s(line.c_str(),"%*s %f %f %f",&x,&y,&z);
			if(line[1]==' ') //Vertex
			{
				points.push_back(Point(x,y,z));
			}
			else if(line[1]=='t') //Texture
			{
				textureMapping.push_back(Point(x,y,z));
			}
			else if(line[1]=='n') //Normal
			{
				normals.push_back(Point(x,y,z));
			}
		}
		//for face, getting the corresponding material from the map
		//adding it to the mesh material vector 
		else if(line.find("usemtl")!=std::string::npos){
			sscanf_s(line.c_str(),"%*s %s",&materialname);
			materials.push_back(fmaterials[materialname]);
		}
		//faces
		else if(line[0]=='f'){
			unsigned int p1=0, p2=0, p3=0, p4=0, pt1=0, pt2=0, pt3=0, pt4=0, pn1=0, pn2=0, pn3=0, pn4=0;
			//counting space -> number of vertexes per face
			size_t spaces = std::count(line.begin(), line.end(), ' ');
			//counting slashes -> using nomal or texture mapping
			size_t slashes = std::count(line.begin(), line.end(), '/');
			size_t emptyslashes = std::count(line.begin(), line.end(), '//');
			Face f;
			//now dépending on the number of vertex and the use of mapping,
			//parsing each line and create faces using the vector of vertex.
			if(spaces==4){
				if(slashes==0){ //vertex
					sscanf_s(line.c_str(),"%*s %d %d %d %d",&p1,&p2,&p3,&p4);
					p1--,p2--,p3--,p4--;
					f = Face(points[p1],points[p2],points[p3],points[p4]);
				}
				else if(slashes==4){ //vertex/texture
					sscanf_s(line.c_str(),"%*s %d/%d %d/%d %d/%d %d/%d",
						&p1,&pt1,&p2,&pt2,&p3,&pt3,&p4,&pt4);
					p1--,p2--,p3--,p4--,pt1--,pt2--,pt3--,pt4--;
					f = Face(points[p1],points[p2],points[p3],points[p4]);
					f.addMapping(textureMapping[pt1]);
					f.addMapping(textureMapping[pt2]);
					f.addMapping(textureMapping[pt3]);
					f.addMapping(textureMapping[pt4]);
				}
				else if(emptyslashes==8 && emptyslashes==0){ //vertex/texture/normal
					sscanf_s(line.c_str(),"%*s %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
						&p1,&pt1,&pn1,&p2,&pt2,&pn2,&p3,&pt3,&pn3,&p4,&pt4,&pn4);
					p1--,p2--,p3--,p4--,pt1--,pt2--,pt3--,pt4--,pn1--,pn2--,pn3--,pn4--;
					f = Face(points[p1],points[p2],points[p3],points[p4]);
					f.addMapping(textureMapping[pt1]);
					f.addMapping(textureMapping[pt2]);
					f.addMapping(textureMapping[pt3]);
					f.addMapping(textureMapping[pt4]);
				}
				else if(emptyslashes=8 && emptyslashes>0){ //vertex/-/normal
					sscanf_s(line.c_str(),"%*s %d//%d %d//%d %d//%d %d//%d",
						&p1,&pn1,&p2,&pn2,&p3,&pn3,&p4,&pn4);
					p1--,p2--,p3--,p4--,pn1--,pn2--,pn3--,pn4--;
				}
				faces.push_back(face_materialindex(f, materials.size()-1));
			}
			else{
				if(slashes==0){ //vertex
					sscanf_s(line.c_str(),"%*s %d %d %d",&p1,&p2,&p3);
					p1--,p2--,p3--;
					f = Face(points[p1],points[p2],points[p3],points[p4]);
				}
				else if(slashes==3){ //vertex/texture
					sscanf_s(line.c_str(),"%*s %d/%d %d/%d %d/%d",&p1,&pt1,&p2,&pt2,&p3,&pt3);
					p1--,p2--,p3--,pt1--,pt2--,pt3--;
					f = Face(points[p1],points[p2],points[p3]);
					f.addMapping(textureMapping[pt1]);
					f.addMapping(textureMapping[pt2]);
					f.addMapping(textureMapping[pt3]);
				}
				else if(emptyslashes==6 && emptyslashes==0){ //vertex/texture/normal
					sscanf_s(line.c_str(),"%*s %d/%d/%d %d/%d/%d %d/%d/%d",&p1,&pt1,&pn1,&p2,&pt2,&pn2,&p3,&pt3,&pn3);
					p1--,p2--,p3--,pt1--,pt2--,pt3--,pt4--,pn1--,pn2--,pn3--;
					f = Face(points[p1],points[p2],points[p3]);
					f.addMapping(textureMapping[pt1]);
					f.addMapping(textureMapping[pt2]);
					f.addMapping(textureMapping[pt3]);
				}
				else if(emptyslashes=6 && emptyslashes>0){ //vertex/-/normal
					sscanf_s(line.c_str(),"%*s %d//%d %d//%d %d//%d",&p1,&pn1,&p2,&pn2,&p3,&pn3);
					p1--,p2--,p3--,p4--,pn1--,pn2--,pn3--;
				}
				faces.push_back(face_materialindex(f, materials.size()-1));
			}
		}
	}

	objifs.close();

	//translating the gravity center to 0,0,0
	centerPosition = getGravityCenter();
	setCenterPosition(Point(0,0,0));
}

void Mesh::setCenterPosition(Point & newcenter){
	Point vector = newcenter - centerPosition;
	for(unsigned int i = 0; i < faces.size(); i++){
		for(unsigned int j = 0; j < faces[i].face.getPointsCount(); j++){
			faces[i].face[j] = (faces[i].face[j]) + vector;
		}
	}
	centerPosition = newcenter;
}

Point Mesh::getGravityCenter(void){
	double x = 0., y = 0., z = 0.;
	unsigned int size = faces.size();
	for(unsigned int i=0; i<size; i++){
		x += faces[i].face.getGravityCenter().getX();
		y += faces[i].face.getGravityCenter().getY();
		z += faces[i].face.getGravityCenter().getZ();
	}
	return Point(x/size, y/size, z/size);
}

Mesh::~Mesh(void)
{
	materials.~vector();
	faces.~vector();
}