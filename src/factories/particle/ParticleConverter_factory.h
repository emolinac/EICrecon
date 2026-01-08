#pragma once

#include <std>

#include "extensions/jana/JOmniFactory.h"

#include <edm4eic/Track.h>
#include <edm4eic/Cluster.h>
#include <edm4eic/TrackClusterMatch.h>
#include <edm4eic/ReconstructedParticle.h>

#include "algorithms/particle/ParticleConverter.h"
#include "algorithms/particle/ParticleConverterConfig.h"

namespace eicrecon {
	class ParticleConverter_factory : public JOmniFactory<ParticleConverter_factory, ParticleConverterConfig> {
		public:
			// Class associated to the algorithm
			using Algo = eicrecon::ParticleConverter;
		private:
			std::unique_ptr<Algo> m_algo;

			// Input collections
			PodioInput<edm4eic::Track> m_tracks_input {this, "Tracks"};
			PodioInput<edm4eic::Cluster> m_clusters_input {this, "Clusters"};
			PodioInput<edm4eic::TrackClusterMatch> m_trackclustermatch_input {this, "TrackClusterMatches"};

			// Output collection
			// - Reconstructed particles
			PodioOutput<edm4eic::ReconstructedParticles> m_recoparticles_output {this};

			// Parameters
			ParameterRef<double> m_tracking_resolution {this, "tracking_resolution", config().tracking_resolution};
			ParameterRef<double> m_calo_resolution {this, "calo_resolution", config().calo_resolution};
			ParameterRef<double> m_calo_energy_norm {this, "calo_energy_norm", config().calo_energy_norm};

			ParameterRef<bool> m_use_resolution_in_ecalc {this, "use_resolution_in_ecalc", config().use_resolution_in_ecalc};

		public:
			void Configure() {
				m_algo = std::make_unique<Algo>(this->GetPrefix());
				m_algo->level((algorithms::LogLevel) logger()->level());
				
				// Pass config object to the algorithm
				m_algo->applyConfig(FactoryT::config());

				m_algo->init();
			};

			void Process(int32_t /* run_number */, uint64_t /* event_number */) {
				m_algo->Process({m_tracks_input(), m_clusters_input(), m_trackclustermatch_input()},
						{m_recoparticles_output().get() /* Outputs defined in private */});
			}
	}
}