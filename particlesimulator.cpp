#include "particlesimulator.h"

ParticleSimulator::ParticleSimulator()
{    
    num_particles = 100;
    par = new Particle[100];
    blackhole = new Particle(1000);
    whitehole = new Particle();
    dt = 100;
    mode = 2;
}

ParticleSimulator::ParticleSimulator(int n)
{
    num_particles = n;
    par = new Particle[n];
    blackhole = new Particle(500);
    whitehole = new Particle();
    dt = 1;
    mode = 2;
}

void ParticleSimulator::set_num_particles(int n){
    num_particles = n;
}

unsigned int ParticleSimulator::get_num_particles(){
    return num_particles;
}

void ParticleSimulator::set_mode(int n){
    mode = n;
}

unsigned int ParticleSimulator::get_mode(){
    return mode;
}

void ParticleSimulator::Gravitation(){
    for(unsigned int i; i < num_particles; i++){
        /* Clear the old value of result force */
        par[i].result_force = QVector3D(0.0, 0.0, 0.0);
        /*
         * Apply the Universal Gravitation in vector form
         * Fr = (m1 m2 R) / |R|³
         */
        for (unsigned int j = 0; j < num_particles; j++){
            /* An body don't interact with itself */            
            if(i != j){
                par[i].result_force +=
                        (par[i].Get_Mass() * par[j].Get_Mass() * (par[j].Get_Position() - par[i].Get_Position())
                        /pow((par[j].Get_Position() - par[i].Get_Position()).length(), 3));
            }
        }
        par[i].result_force +=
                (par[i].Get_Mass() * blackhole->Get_Mass() * (blackhole->Get_Position() - par[i].Get_Position()))/pow((blackhole->Get_Position() - par[i].Get_Position()).length(), 3);
    }
}

void ParticleSimulator::MoveParticles(){
    QVector3D a, s;

    for(unsigned int i = 0; i < num_particles; i++){

        /* F = m a -> a = F / m */
        a = par[i].result_force / par[i].Get_Mass();

        /*
         * S = S0 + V0t + 1/2 a dt² ->
         * S = S0 +  0  + 1/2 a dt² ->
         * S = S0 + 1/2 a dt²
         */
        s = (par[i].Get_Position() + 0.5 * a * dt*dt);
        par[i].SetPosition(s);
    }
}

void ParticleSimulator::GoB(){
    QVector3D s;
    GLfloat f;
    for(unsigned int i = 0; i < num_particles; i++){
        if (mode == 1){
            s = -(par[i].Get_Position() - blackhole->Get_Position());
            f = 1 / s.length();
            s = (s / s.length()) * f;
            par[i].SetPosition(par[i].Get_Position() + s);
        }
        else if(mode == 2){
            s = (-par[i].Get_Position() + blackhole->Get_Position());
            f = 1 / s.length();
            s = (s / s.length()) * f;
            par[i].SetPosition(par[i].Get_Position() + s / 100);
            if (((par[i].Get_Position().x() > 1.9) && (par[i].Get_Position().y() > 1.9) && (par[i].Get_Position().z() > 1.9)) ||
                ((par[i].Get_Position().x() > 1.9) && (par[i].Get_Position().y() > 1.9)) ||
                ((par[i].Get_Position().x() > 1.9) && (par[i].Get_Position().z() > 1.9)) ||
                ((par[i].Get_Position().y() > 1.9) && (par[i].Get_Position().z() > 1.9))
                )
                par[i].SetPosition(QVector3D(-1,-1,-1));
        }
        else{
            if (i%8 == 0)
                par[i].SetPosition(QVector3D(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX));
            else if(i%8 == 1)
                par[i].SetPosition(QVector3D(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX)*
                                        QVector3D(1,1,-1));
            else if(i%8 == 2)
                    par[i].SetPosition(QVector3D(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX)*
                                            QVector3D(1,-1,1));
            else if(i%8 == 3)
                    par[i].SetPosition(QVector3D(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX)*
                                            QVector3D(1,-1,-1));
            else if(i%8 == 4)
                    par[i].SetPosition(QVector3D(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX)*
                                            QVector3D(-1,1,1));
            else if(i%8 == 5)
                    par[i].SetPosition(QVector3D(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX)*
                                            QVector3D(-1,1,-1));
            else if(i%8 == 6)
                    par[i].SetPosition(QVector3D(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX)*
                                            QVector3D(-1,-1,1));
            else if(i%8 == 7)
                    par[i].SetPosition(QVector3D(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX)*
                                            QVector3D(-1,-1,-1));
        }
    }
}

void ParticleSimulator::WhiteHole(){
    /* If a particle get close the blackhole, it's ejected by whitehole */
    for (unsigned int i = 0; i < num_particles; i++){
        if (((par[i].Get_Position().x() > 1.9) && (par[i].Get_Position().y() > 1.9) && (par[i].Get_Position().z() > 1.9)) ||
            ((par[i].Get_Position().x() > 1.9) && (par[i].Get_Position().y() > 1.9)) ||
            ((par[i].Get_Position().x() > 1.9) && (par[i].Get_Position().z() > 1.9)) ||
            ((par[i].Get_Position().y() > 1.9) && (par[i].Get_Position().z() > 1.9))
            )
            par[i].SetPosition(whitehole->Get_Position());
    }
}
