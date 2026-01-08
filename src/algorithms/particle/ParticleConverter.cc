#include "ParticleConverter.h"

namespace eicrecon {
        void ParticleConverter::process(const Input& input, const Output& output) const {
                // - Here I have to write all the necessary instructions to output a ReconstructedParticlesCollection
                // Check Derek's PR where he conveyed the way to loop through clusters
                
                const auto [tracks, clusters, trackclusters_match] = input;
                auto [out_particles] = output;

                out_particles->setSubsetCollection(); // CHECK: IN THIS REALLY NECESSARY ? (ASK)

                // What PDG to assign subroutine
                // From a trackclustermatch collection I should check if the cluster belongs to hcal or ecal
                //      To check this I should initiate a service of DD4Hep to access the detector information
                //              For further detail check the snippets folder that Derek sent
                //      After checking where the cluster was formed we check if there is an associated track
                //      Supposedly trackclustermatch should have a correspondence with track collections too!
                //              Check if there is an available track
        };

        void ParticleConverter::init() {};
}