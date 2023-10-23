


#ifndef PARTICLE_H
#define PARTICLE_H


#define _GRAVITY -9.81f

class particle{
public:
int id;
float mass;
vector3d position;
vector3d velocity;
vector3d forces;
    FMOD::Sound* hsound;
    FMOD::Channel* hchannel;
particle(){
id=0;
mass=1.0f;
position={0,0,0};
velocity={0,0,0};
forces={0,0,0};
hsound=NULL;
hchannel=NULL;
}
~particle(){
hchannel=NULL;
if(hsound!=NULL){
hsound->release();
}
hsound=NULL;
}
void addSound(const std::string& filename){
FMOD_RESULT result =hsystem->createSound(filename.c_str(), FMOD_3D | FMOD_LOOP_NORMAL |FMOD_DEFAULT, nullptr, &hsound);
    if (result != FMOD_OK) {
_LOG_P("Error to load {}.", filename);
return;
    }
    result = hsystem->playSound(hsound, nullptr, true, &hchannel);
updateSoundPosition();
hchannel->setPaused(false);
}
void updateSoundPosition(){
if(hchannel!=NULL){
FMOD_VECTOR p, v;

p.x=position.x;
p.y=position.y;
p.z=position.z;

v.x=velocity.x;
v.y=velocity.z;
v.z=velocity.y;
hchannel->set3DAttributes(&p, &v);
}
}
std::string toString()const{
std::stringstream ss;
ss<<std::fixed;
ss.precision(2);
ss<<"Particle id: "<<id<<std::endl;
ss<<"Mass: "<<mass<<std::endl;
ss<<"Pos: "<<position<<std::endl;
ss<<"Vel: "<<velocity<<std::endl;
ss<<"Forces: "<<forces<<std::endl;
return ss.str();
}
void applyForce(const vector3d& f){
forces+=f;
}
};

#endif
