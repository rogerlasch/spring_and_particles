
#include<functional>
#include<signal.h>
#include <fmod.hpp>
#include<iostream>
#include<memory>
#include<assert.h>
#include<vector>
#include"g_start.h"
#include"vector3d.h"
#include"sound.h"
#include"particle.h"
#include"Spring.h"

using namespace std;

void inputparticles();
void printValues();
vector3d fCalculateSpringForce(const vector3d& p1, const vector3d& v1, const vector3d& p2, const vector3d& v2, float restLength, float stiffness, float damping);
void calcLoads(particle* r);
void eulerUpdate(float dt, particle* r);

vector<shared_ptr<particle>> particles;
Spring spring;
float gravity =0.0f;
float step=0.0f;
int iterations=0;
bool stop=false;
void hsig(int){stop=true;}

int main()
{
signal(SIGTERM, hsig);
signal(SIGINT, hsig);
signal(SIGABRT, hsig);

sound_init();
inputparticles();
printValues();
int x=0;
int64_t start=gettimestamp();
while(x<iterations){
this_thread::sleep_for(chrono::milliseconds(5));
if(stop)break;
int64_t end=gettimestamp();
if((end-start)>=(step*1000)){
start=gettimestamp();
hsystem->update();
x++;
float t=(x*step);
spring.update();
for(auto& it : particles){
calcLoads(it.get());
eulerUpdate(step, it.get());
it->updateSoundPosition();
if(it->mass>0.0f){
_LOG("T={:.2f}, id={}, P={:.2f}:{:.2f}:{:.2f}, vel={:.2f}", t, it->id, it->position.x, it->position.y, it->position.z, it->velocity.length());
}
}
}
}
_LOG_P("End of simulation. Check the {} for results...", _FILENAME);
for(auto& it : particles){
it.reset();
}
hsystem->close();
hsystem->release();
return 0;
}


void inputparticles(){
_LOG_P("During the simulation, press ctrl+c to exit prematurely.");
_LOG_P("The listener position is set to: [50, 50, 50]. Position the particles close to this position so you can hear the sound.");
for(int i=0; i<2; i++){
_LOG_P("Configuring the particle {}", (i+1));
shared_ptr<particle> sf=make_shared<particle>();
sf->id=(i+1);
sf->mass=inputVal<float>("Enter the mass of the particle...");
sf->position.x=inputVal<float>("x position...");
sf->position.y=inputVal<float>("y position...");
sf->position.z=inputVal<float>("z position...");
particles.push_back(sf);
}
_LOG_P("Configuring spring...");
spring.restLength=inputVal<float>("Enter the spring length...");
spring.stiffness=inputVal<float>("Enter the spring stiffness... Note that auto values can make the simulation unstable. A good value would be: 10*((m1+m2)/2), where m1 and m2 are the masses of the objects...");
spring.damping=inputVal<float>("Enter the damping factor... A small value would be good, somewhere between 0 and 1...");
spring.r1=particles[0].get();
spring.r2=particles[1].get();
_LOG_P("Configuring simulation...");
gravity=inputVal<float>("Enter the acceleration due to gravity, enter 0 to deactivate...");
step=inputVal<float>("Enter the time step to use, I recommend 0.2");
iterations=inputVal<int>("Enter the number of iterations to perform...");
particles[0]->addSound("sounds/p1.ogg");
particles[1]->addSound("sounds/p2.ogg");
assert(iterations>0);
assert(step>0.0001f);
}

void printValues(){
_LOG_P("Showing environment configuration...");
_LOG_P(": {:.2f}", gravity);
_LOG_P("Time step: {:.2f}", step);
_LOG_P("Iterations: {}", iterations);
_LOG_P("Showing spring and its properties...");
_LOG_P("{}", spring.toString());
}

void calcLoads(particle* r){
if(r->mass<=0.0f){
r->forces={0,0,0};
return;
}
vector3d f={0, 0, gravity*r->mass};
r->applyForce(f);
}

void eulerUpdate(float dt, particle* r){
if(r->mass<=0.0f)return;
vector3d a=r->forces/r->mass;
r->velocity+=a*dt;
r->position+=r->velocity*dt;
r->forces={0,0,0};
}

vector3d fCalculateSpringForce(const vector3d& p1, const vector3d& v1, const vector3d& p2, const vector3d& v2, float restLength, float stiffness, float damping){
vector3d final;
vector3d dist=p1-p2;
float d=dist.length();
float deformAmount=d-restLength;
float restorativeForce=stiffness*deformAmount;
final=((dist/d)*restorativeForce);
final+=(v1-v2)*damping;
return final;
}
