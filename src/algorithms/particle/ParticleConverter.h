// Preprocessor command to avoid double definitions of this class during compilation
#pragma once

#include <algorithms/algorithm.h>

#include <edm4eic/TrackCollection.h>
#include <edm4eic/ClusterCollection.h>
#include <edm4eic/TrackClusterMatchCollection.h>
#include <edm4eic/ReconstructedParticleCollection.h>

#include <string>
#include <string_view>

#include "ParticleConverterConfig.h"
#include "algorithms/interfaces/WithPodConfig.h"

// Class definition
namespace eicrecon {
        using ParticleConverterAlgorithm = algorithms::Algorithm<algorithms::Input<edm4eic::TrackCollection, edm4eic::ClusterCollection, edm4eic::TrackClusterMatchCollection>,
                                                                 algorithms::Output<edm4eic::ReconstructedParticleCollection>>;

        class ParticleConverter : public ParticleConverterAlgorithm, public WithPodConfig<ParticleConverterConfig> {
                public:
                        ParticleConverter(std::string_view name) : 
                        ParticleConverterAlgorithm(name, {"inputTracks", "inputClusters", "inputTrackClusterMatches"}, {"outputRecoParticles"} ,"Particles as such (?)") {}; 

                        void init() final{}; // what is the use of making it final?
                        void process(const Input&, const Output&) const final;

                private:
                        // Services and calibrations here!
        };
}