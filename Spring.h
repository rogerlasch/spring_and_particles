


#ifndef SPRING_H
#define SPRING_H

vector3d fCalculateSpringForce(const vector3d& p1, const vector3d& v1, const vector3d& p2, const vector3d& v2, float restLength, float stiffness, float damping);

struct Spring{
particle* r1;
particle* r2;
float restLength;
float stiffness;
float damping;
Spring(){
r1=NULL;
r2=NULL;
restLength=0.0f;
stiffness=0.0f;
damping=0.0f;
}
void update(){
vector3d f=fCalculateSpringForce(r1->position, r1->velocity, r2->position, r2->velocity, restLength, stiffness, damping);
if(r1->mass>0.0f){
r1->applyForce(f*-1.0f);
}
if(r2->mass>0.0f){
r2->applyForce(f);
}
}
string toString(){
stringstream ss;
ss<<fixed;
ss.precision(2);
ss<<"Showing spring settings..."<<endl;
ss<<"r1:"<<endl<<r1->toString()<<endl;
ss<<"r2:"<<r2->toString()<<endl;
ss<<"restLength: "<<restLength<<endl;
ss<<"stiffness: "<<stiffness<<endl;
ss<<"damping: "<<damping<<endl<<endl;
return ss.str();
}
};

#endif
